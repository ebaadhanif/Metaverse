#include "PcgSQLiteSubsystem.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "Interfaces//IPluginManager.h"


void UPcgSQLiteSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    DbPathFull = GetPCGDatabaseFilePath();
    OpenDatabase();
}

void UPcgSQLiteSubsystem::Deinitialize()
{
    CloseDatabase();
    Super::Deinitialize();
}

bool UPcgSQLiteSubsystem::OpenDatabase(const FString& InRelativePath)
{
    FString Relative = InRelativePath;
    if (Relative.StartsWith(TEXT("/")) || Relative.StartsWith(TEXT("\\")))
    {
        Relative = Relative.RightChop(1);
    }

   // FString DBPath = IPluginManager::Get().FindPlugin(TEXT("CustomPCG"))->GetBaseDir() / TEXT("Content") / Relative;
    FString DBPath = DbPathFull / Relative;
    FPaths::NormalizeFilename(DBPath) ;
    DbPathFull = DBPath;

    //Lock();
    bool bOk = DB.Open(*DBPath, OpenMode);
    const FString error = DB.GetLastError();
    UE_LOG(LogTemp, Error, TEXT("DB error %s"), *error);
    //Unlock();

    if (!bOk)
    {
        UE_LOG(LogTemp, Error, TEXT("PcgSQLiteSubsystem: Failed to open/create DB at %s"), *DBPath);
        return false;
    }

    UE_LOG(LogTemp, Log, TEXT("PcgSQLiteSubsystem: DB opened at %s"), *DBPath);
    return true;
}

void UPcgSQLiteSubsystem::CloseDatabase()
{
    //Lock();
    if (DB.IsValid())
    {
        DB.Close();
        UE_LOG(LogTemp, Log, TEXT("PcgSQLiteSubsystem: DB closed"));
    }
    //Unlock();
}

bool UPcgSQLiteSubsystem::IsOpen() const
{
    //Lock();
    bool b = DB.IsValid();
    //Unlock();
    return b;
}

bool UPcgSQLiteSubsystem::Execute(const FString& Sql)
{
  //  Lock();
    bool bOk = DB.Execute(*Sql);
    if (!bOk)
    {
        UE_LOG(LogTemp, Error, TEXT("PcgSQLiteSubsystem::Execute failed: %s"), *Sql);
    }
  //  Unlock();
    return bOk;
}

bool UPcgSQLiteSubsystem::ExecuteWithCallback(
    const FString& Sql,
    TFunctionRef<ESQLitePreparedStatementExecuteRowResult(const FSQLitePreparedStatement&)> RowCallback)
{
    //Lock();

    FSQLitePreparedStatement Statement;
    if (!Statement.Create(DB, *Sql))
    {
        //Unlock();
        UE_LOG(LogTemp, Error, TEXT("Failed to create SQLite statement: %s"), *Sql);
        return false;
    }

    int64 Result = Statement.Execute([&](const FSQLitePreparedStatement& Stmt) -> ESQLitePreparedStatementExecuteRowResult
        {
            return RowCallback(Stmt);
        });

    Statement.Destroy();
    //Unlock();

    if (Result == INDEX_NONE)
    {
        UE_LOG(LogTemp, Error, TEXT("PcgSQLiteSubsystem::ExecuteWithCallback failed: %s"), *Sql);
        return false;
    }

    return true;
}

bool UPcgSQLiteSubsystem::BeginTransaction()
{
    return Execute(TEXT("BEGIN TRANSACTION;"));
}

bool UPcgSQLiteSubsystem::CommitTransaction()
{
    return Execute(TEXT("COMMIT;"));
}

bool UPcgSQLiteSubsystem::RollbackTransaction()
{
    return Execute(TEXT("ROLLBACK;"));
}

FSQLiteDatabase& UPcgSQLiteSubsystem::GetDatabase()
{
   return DB;
}


FString UPcgSQLiteSubsystem::GetPCGDatabaseFilePath()
{
    FString XmlContent;
    FString Path = FPaths::ProjectContentDir() / TEXT("Archive/AppConfig.xml");
    if (FFileHelper::LoadFileToString(XmlContent, *Path))
    {
        XmlContent.TrimStartAndEndInline(); // Remove BOM or stray spaces
        FXmlFile XmlFile(XmlContent, EConstructMethod::ConstructFromBuffer);

        if (XmlFile.IsValid())
        {
            FXmlNode* RootNode = XmlFile.GetRootNode();
            if (RootNode && RootNode->GetTag() == TEXT("AppConfig")) // Case-sensitive!
            {
                FXmlNode* PCGDbFilePathNode = RootNode->FindChildNode(TEXT("PCGLocalDBFilePath"));
                if (PCGDbFilePathNode)
                {
                    //FString PCGDBFilePathValueStr = FPaths::ProjectDir() / PCGDbFilePathNode->GetContent().TrimStartAndEnd();
                    FString PCGDBFilePathValueStr = PCGDbFilePathNode->GetContent().TrimStartAndEnd();
                    if (!PCGDBFilePathValueStr.StartsWith("\\"))
                    {
                        PCGDBFilePathValueStr = FPaths::ProjectDir() / PCGDbFilePathNode->GetContent().TrimStartAndEnd();
                    }
                    return PCGDBFilePathValueStr;
                }
            }
        }
    }

    return FString("Invalid");
}

