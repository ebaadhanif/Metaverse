#include "PCGManager.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "PCGPointContent.h"
#include "PCGPolygonContent.h"
#include "FShapeFileReader.h"
#include "Engine/World.h" 
#include "GridStreamingManager.h"
#include "PCGLoadTracker.h"
#include "PcgSQLiteSubsystem.h"

APCGManager* APCGManager::Instance = nullptr;


APCGManager* APCGManager::GetInstance()
{
	return Instance;
}

void APCGManager::InitializeDatabase()
{
	// Ensure subsystem is available and DB is opened
	if (GetGameInstance())
	{
		UPcgSQLiteSubsystem* DBSubsystem = GetGameInstance()->GetSubsystem<UPcgSQLiteSubsystem>();
		if (!DBSubsystem)
		{
			UE_LOG(LogTemp, Error, TEXT("APCGManager::BeginPlay - DB subsystem not available."));
			return;
		}
		if (!DBSubsystem->IsOpen())
		{
			if (!DBSubsystem->OpenDatabase()) {
				UE_LOG(LogTemp, Error, TEXT("APCGManager::BeginPlay - Failed to open DB via subsystem."));
				return;
			}
		}

		// Create tables once (moved from previous InitializeDatabase implementation)
		const FString CreatePointsTableSQL = TEXT(R"(
            CREATE TABLE IF NOT EXISTS PolygonPoints (
                ShapefileID TEXT,
                PolygonID INTEGER,
                PointIndex INTEGER,
                Latitude NUMERIC,
                Longitude NUMERIC,
                Elevation NUMERIC,
                MeshID TEXT,
                Seed NUMERIC,
                PRIMARY KEY(ShapefileID, PolygonID, PointIndex)
            );
        )");


		FString CreateFeaturesTableSQL = TEXT(R"(
    CREATE TABLE IF NOT EXISTS PolygonFeatures (
        ShapefileID TEXT,
        PolygonID INTEGER,
        Name TEXT,
        Type TEXT,
        Scale REAL,
        Model TEXT,
        State TEXT,
        Foliage TEXT,
        Density REAL,
        Area REAL,
        Pnts REAL,
        KindID INTEGER,
        KindDesc TEXT,
        DomainID INTEGER,
        DomainDesc TEXT,
        CountryID INTEGER,
        CountryDes TEXT,
        CategoryID INTEGER,
        CategoryDe TEXT,
        SubCategID INTEGER,
        SubCategDe TEXT,
        SpecificID INTEGER,
        SpecificDe TEXT,
        EntityEnum TEXT,
        BoxExtentX REAL,  
        BoxExtentY REAL,  
        BoxExtentZ REAL,  
        CenterLat NUMERIC,
        CenterLong NUMERIC,
        CenterElev NUMERIC,
        PRIMARY KEY(ShapefileID, PolygonID)
    );
)");

		const FString CreatePointDataTableSQL = TEXT(R"(
    CREATE TABLE IF NOT EXISTS PointsData (
        ShapefileID TEXT,
        PointID INTEGER,  
        Latitude NUMERIC(20,12),
        Longitude NUMERIC(20,12),
        ELevation NUMERIC(20,12),
        Name TEXT,
        Scale REAL,
        Rotation REAL,
        Model TEXT,
        State TEXT,
        PRIMARY KEY(ShapefileID, PointID)
    );
)");


		const FString CreateMetadataTableSQL = TEXT(R"(
            CREATE TABLE IF NOT EXISTS ShapefileMetadata (
                ShapefileID TEXT PRIMARY KEY,
                Type TEXT,
                LastModified INT
            );
        )");

		const FString idx_PointsData_Shapefile = TEXT(R"(CREATE INDEX IF NOT EXISTS idx_PointsData_Shapefile ON PointsData(ShapefileID);)");
		const FString idx_PointsData_Lat_Lon = TEXT(R"(CREATE INDEX IF NOT EXISTS idx_PointsData_Lat_Lon ON PointsData(Latitude, Longitude); )");
		const FString idx_PointsData_Tile = TEXT(R"(CREATE INDEX IF NOT EXISTS idx_PointsData_Tile ON PointsData(TileX, TileY); )");

		DBSubsystem->Execute(CreatePointsTableSQL);
		DBSubsystem->Execute(CreateFeaturesTableSQL);
		DBSubsystem->Execute(CreatePointDataTableSQL);
		DBSubsystem->Execute(CreateMetadataTableSQL);

		DBSubsystem->Execute(idx_PointsData_Shapefile);
		DBSubsystem->Execute(idx_PointsData_Lat_Lon);
		DBSubsystem->Execute(idx_PointsData_Tile);

		UE_LOG(LogTemp, Log, TEXT("APCGManager: Database initialized (via subsystem)"));
	}

}

APCGManager::APCGManager()
{
	// PrimaryActorTick.bCanEverTick = true;

}

void APCGManager::BeginPlay()
{
	Super::BeginPlay();
	if (Instance == nullptr)
	{
		Instance = this;
	}
	GI = GetWorld() ? GetWorld()->GetGameInstance() : nullptr;
	LoadTracker = GI->GetSubsystem<UPCGLoadTracker>();

	InitializeDatabase();
	ShapeFilesFolderPath = GetPCGShapeFilesPath();


	LoadDataforPCGPoint();
	//LoadDataforPCGPolygon();

	LoadTracker->OnAllShapefilesLoaded.AddDynamic(this, &APCGManager::HandleAllPolygonDataLoaded);

}

void APCGManager::LoadDataforPCGPoint()
{
	FShapeFileReader::LoadDllForGDAL();

	//FString ShapefileFolder = FPaths::ProjectContentDir() / TEXT("Shapefiles/PointData/");
	FString ShapefileFolder = ShapeFilesFolderPath + TEXT("/PointData/");
	FPaths::NormalizeFilename(ShapefileFolder);
	TArray<FString> ShapefilePaths;
	IFileManager::Get().FindFilesRecursive(ShapefilePaths, *ShapefileFolder, TEXT("*.shp"), true, false);

	// Get the SQLite subsystem from GameInstance
	UPcgSQLiteSubsystem* SQLite = GetGameInstance()->GetSubsystem<UPcgSQLiteSubsystem>();
	if (!SQLite)
	{
		UE_LOG(LogTemp, Error, TEXT("SQLite subsystem not available!"));
		return;
	}

	// --- Remove deleted shapefiles from DB ---
	TArray<FString> DBShapefiles;
	const FString ListSQL = TEXT("SELECT ShapefileID FROM ShapefileMetadata WHERE Type = 'Point';");
	SQLite->ExecuteWithCallback(ListSQL, [&](const FSQLitePreparedStatement& Statement) -> ESQLitePreparedStatementExecuteRowResult
		{
			FString ShapefileID;
			Statement.GetColumnValueByName(TEXT("ShapefileID"), ShapefileID);
			DBShapefiles.Add(ShapefileID);
			return ESQLitePreparedStatementExecuteRowResult::Continue;
		});

	TArray<FString> AllShapefiles;
	IFileManager::Get().FindFilesRecursive(AllShapefiles, *ShapefileFolder, TEXT("*.shp"), true, false);



	for (const FString& DBFile : DBShapefiles)
	{
		bool bFileExists = AllShapefiles.ContainsByPredicate([&](const FString& FoundFile)
			{
				return FPaths::GetBaseFilename(FoundFile) == DBFile;
			});

		if (!bFileExists)
		{
			const FString DeletePointsSQL = FString::Printf(TEXT("DELETE FROM PointsData WHERE ShapefileID='%s';"), *DBFile);
			const FString DeleteMetaSQL = FString::Printf(TEXT("DELETE FROM ShapefileMetadata WHERE ShapefileID='%s' AND Type = 'Point';"), *DBFile);

			SQLite->ExecuteWithCallback(DeletePointsSQL, [](const FSQLitePreparedStatement&) { return ESQLitePreparedStatementExecuteRowResult::Continue; });
			SQLite->ExecuteWithCallback(DeleteMetaSQL, [](const FSQLitePreparedStatement&) { return ESQLitePreparedStatementExecuteRowResult::Continue; });

			UE_LOG(LogTemp, Log, TEXT("Deleted DB entries for removed shapefile: %s"), *DBFile);
		}
	}
	if (ShapefilePaths.Num() > 0) {
		PCGPointParent = GetWorld()->SpawnActor<AActor>();
		if (PCGPointParent)
		{
#if WITH_EDITOR
			PCGPointParent->SetActorLabel(TEXT("PCG Point Parent"));
#endif
		}
		if (!PCGPointParent)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create PCGPointContentParentActor."));
			return;
		}
	}
	// --- Process each shapefile ---
	for (const FString& ShapefilePath : ShapefilePaths)
	{
		const FString ShapefileName = FPaths::GetBaseFilename(ShapefilePath);
		const int64 FileTimestamp = IFileManager::Get().GetTimeStamp(*ShapefilePath).ToUnixTimestamp();
		bool bNeedsGeneration = true;

		// Check last modified timestamp in DB
		const FString CheckSQL = FString::Printf(TEXT("SELECT LastModified FROM ShapefileMetadata WHERE ShapefileID='%s' AND Type = 'Point';"), *ShapefileName);
		SQLite->ExecuteWithCallback(CheckSQL, [&](const FSQLitePreparedStatement& Statement) -> ESQLitePreparedStatementExecuteRowResult
			{
				int64 SavedTimestamp = 0;
				Statement.GetColumnValueByName(TEXT("LastModified"), SavedTimestamp);

				UE_LOG(LogTemp, Log, TEXT("SavedTimestamp: %lld"), SavedTimestamp);
				UE_LOG(LogTemp, Log, TEXT("FileTimestamp: %lld"), FileTimestamp);

				if (SavedTimestamp == FileTimestamp)
				{
					bNeedsGeneration = false;
				}
				else
				{
					const FString DeletePointsSQL = FString::Printf(TEXT("DELETE FROM PointsData WHERE ShapefileID='%s';"), *ShapefileName);
					SQLite->ExecuteWithCallback(DeletePointsSQL, [](const FSQLitePreparedStatement&) { return ESQLitePreparedStatementExecuteRowResult::Continue; });
					UE_LOG(LogTemp, Log, TEXT("Deleted old DB points for modified shapefile: %s"), *ShapefileName);
				}

				return ESQLitePreparedStatementExecuteRowResult::Continue;
			});

		// --- Spawn and process Point content ---

		FActorSpawnParameters SpawnParams;
		const FName ActorName(*ShapefileName);
		SpawnParams.Name = ActorName;
		APCGPointContent* PointContent = GetWorld()->SpawnActor<APCGPointContent>(APCGPointContent::StaticClass(), FVector::ZeroVector,
			FRotator::ZeroRotator, SpawnParams);
		if (!PointContent)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create APCGPointContent for file: %s"), *ShapefilePath);
			continue;
		}
		PointContent->AttachToComponent(PCGPointParent->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
#if WITH_EDITOR
		PointContent->SetActorLabel(ShapefileName);
#endif

		UE_LOG(LogTemp, Error, TEXT("Self %s"), *PointContent->GetName());
		//UE_LOG(LogTemp, Error, TEXT("Parent %s"), *PointContent->GetParentActor()->GetName());


		PointContents.Add(PointContent);

		if (bNeedsGeneration)
		{
			// Read shapefile raw data
			FShapeRawData RawData = FShapeFileReader::ReadShapefileRawData(ShapefilePath);

			// Insert/Update metadata
			const FString UpdateMetaSQL = FString::Printf(
				TEXT("INSERT OR REPLACE INTO ShapefileMetadata (ShapefileID, Type, LastModified) VALUES ('%s','Point', %lld);"),
				*ShapefileName, FileTimestamp);

			SQLite->ExecuteWithCallback(UpdateMetaSQL, [](const FSQLitePreparedStatement&) { return ESQLitePreparedStatementExecuteRowResult::Continue; });
			PointContent->InitializePCGPointData(RawData);
			//PointContent->SpawnPCGPointData();
			PointContent->SpawnPCGPointData_CesiumSamplerBatched();
		}
		else
		{
			 PointContent->InitializeContent();
			//PointContent->LoadPointDataFromDatabase(ShapefileName);
			 PointContent->SetStreamingShapeFileId(ShapefileName);
			 PointContent->EnableStreaming(true, 5.0f, 3.0f);

		}
	}
}

void APCGManager::Testing() {
	//GetWorldTimerManager().SetTimer(
	//	DelayTimeHandle,
	//	this,
	//	&APCGManager::Testing,
	//	10.0f,
	//	false
	//);
	SetPCGPolygonDataVisibility(false);
}

void APCGManager::LoadDataforPCGPolygon()
{
	FShapeFileReader::LoadDllForGDAL();

	// FString ShapefileFolder = TEXT("//200.0.0.2/StorageSpace/28- Metaverse/2- PAF Metraverse/Shapefiles/PolygonData/");
	FString ShapefileFolder = ShapeFilesFolderPath + TEXT("/PolygonData/");
	FPaths::NormalizeFilename(ShapefileFolder);
	TArray<FString> ShapefilePaths;
	IFileManager::Get().FindFilesRecursive(ShapefilePaths, *ShapefileFolder, TEXT("*.shp"), true, false);

	// Get the SQLite subsystem from GameInstance
	UPcgSQLiteSubsystem* SQLite = GetGameInstance()->GetSubsystem<UPcgSQLiteSubsystem>();
	if (!SQLite)
	{
		UE_LOG(LogTemp, Error, TEXT("SQLite subsystem not available!"));
		return;
	}

	// --- Remove deleted shapefiles from DB ---
	TArray<FString> DBShapefiles;
	const FString ListSQL = TEXT("SELECT ShapefileID FROM ShapefileMetadata WHERE Type = 'Polygon';");
	SQLite->ExecuteWithCallback(ListSQL, [&](const FSQLitePreparedStatement& Statement) -> ESQLitePreparedStatementExecuteRowResult
		{
			FString ShapefileID;
			Statement.GetColumnValueByName(TEXT("ShapefileID"), ShapefileID);
			DBShapefiles.Add(ShapefileID);
			return ESQLitePreparedStatementExecuteRowResult::Continue;
		});

	TArray<FString> AllShapefiles;
	IFileManager::Get().FindFilesRecursive(AllShapefiles, *ShapefileFolder, TEXT("*.shp"), true, false);

	for (const FString& DBFile : DBShapefiles)
	{
		bool bFileExists = AllShapefiles.ContainsByPredicate([&](const FString& FoundFile)
			{
				UE_LOG(LogTemp, Log, TEXT("DB File: %s"), *DBFile);
				UE_LOG(LogTemp, Log, TEXT("FoundFile: %s"), *FPaths::GetBaseFilename(FoundFile));
				return FPaths::GetBaseFilename(FoundFile) == DBFile;
			});

		if (!bFileExists)
		{
			const FString DeletePointsSQL = FString::Printf(TEXT("DELETE FROM PolygonPoints WHERE ShapefileID='%s';"), *DBFile);
			const FString DeleteMetaSQL = FString::Printf(TEXT("DELETE FROM ShapefileMetadata WHERE ShapefileID='%s' AND Type = 'Polygon';"), *DBFile);
			const FString DeleteFeaturesSQL = FString::Printf(TEXT("DELETE FROM PolygonFeatures WHERE ShapefileID='%s';"), *DBFile);

			SQLite->ExecuteWithCallback(DeletePointsSQL, [](const FSQLitePreparedStatement&) { return ESQLitePreparedStatementExecuteRowResult::Continue; });
			SQLite->ExecuteWithCallback(DeleteMetaSQL, [](const FSQLitePreparedStatement&) { return ESQLitePreparedStatementExecuteRowResult::Continue; });
			SQLite->ExecuteWithCallback(DeleteFeaturesSQL, [](const FSQLitePreparedStatement&) { return ESQLitePreparedStatementExecuteRowResult::Continue; });

			UE_LOG(LogTemp, Log, TEXT("Deleted DB entries for removed shapefile: %s"), *DBFile);
		}
	}

	// --- Process each shapefile ---
	for (const FString& ShapefilePath : ShapefilePaths)
	{
		const FString ShapefileName = FPaths::GetBaseFilename(ShapefilePath);
		const int64 FileTimestamp = IFileManager::Get().GetTimeStamp(*ShapefilePath).ToUnixTimestamp();
		bool bNeedsGeneration = true;

		// Check last modified timestamp in DB
		const FString CheckSQL = FString::Printf(TEXT("SELECT LastModified FROM ShapefileMetadata WHERE ShapefileID='%s' AND Type = 'Polygon';"), *ShapefileName);
		SQLite->ExecuteWithCallback(CheckSQL, [&](const FSQLitePreparedStatement& Statement) -> ESQLitePreparedStatementExecuteRowResult
			{
				int64 SavedTimestamp = 0;
				Statement.GetColumnValueByName(TEXT("LastModified"), SavedTimestamp);

				UE_LOG(LogTemp, Log, TEXT("SavedTimestamp: %lld"), SavedTimestamp);
				UE_LOG(LogTemp, Log, TEXT("FileTimestamp: %lld"), FileTimestamp);

				if (SavedTimestamp == FileTimestamp)
				{
					bNeedsGeneration = false;
				}
				else
				{
					const FString DeletePointsSQL = FString::Printf(TEXT("DELETE FROM PolygonPoints WHERE ShapefileID='%s';"), *ShapefileName);
					SQLite->ExecuteWithCallback(DeletePointsSQL, [](const FSQLitePreparedStatement&) { return ESQLitePreparedStatementExecuteRowResult::Continue; });
					UE_LOG(LogTemp, Log, TEXT("Deleted old DB points for modified shapefile: %s"), *ShapefileName);
				}

				return ESQLitePreparedStatementExecuteRowResult::Continue;
			});

		// --- Spawn and process polygon content ---
		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.Name = FName(*ShapefileName);
		APCGPolygonContent* PolygonContent = GetWorld()->SpawnActor<APCGPolygonContent>(
			APCGPolygonContent::StaticClass(),
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			Params);

#if WITH_EDITOR
		PolygonContent->SetActorLabel(ShapefileName);
#endif
		PolygonContents.Add(PolygonContent);
		if (bNeedsGeneration)
		{
			// Read shapefile raw data
			FShapeRawData RawData = FShapeFileReader::ReadShapefileRawData(ShapefilePath);

			// Insert/Update metadata
			const FString UpdateMetaSQL = FString::Printf(
				TEXT("INSERT OR REPLACE INTO ShapefileMetadata (ShapefileID, Type, LastModified) VALUES ('%s','Polygon', %lld);"),
				*ShapefileName, FileTimestamp);

			SQLite->ExecuteWithCallback(UpdateMetaSQL, [](const FSQLitePreparedStatement&) { return ESQLitePreparedStatementExecuteRowResult::Continue; });

			// Initialize polygon data and spawn
			PolygonContent->InitializeContent();
			PolygonContent->InitializePCGPolygonData(RawData);
			// PolygonContent->InsertPolygonsFeaturesToDB(RawData.CollectionName);
			PolygonContent->SpawnPCGPolygonData();
		}
		else
		{
			PolygonContent->InitializeContent();
			PolygonContent->LoadPolygonDataFromDatabase(ShapefileName);
		}
	}
}

void APCGManager::HandleAllPolygonDataLoaded() {


}

void APCGManager::SetPCGDataVisibility(bool bVisible)
{
	SetPCGPointDataVisibility(bVisible);
	SetPCGPolygonDataVisibility(bVisible);
}

void APCGManager::SetPCGPointDataVisibility(bool bVisible)
{
	for (APCGPointContent* PointContent : PointContents) {
		PointContent->ToggleVisibility(bVisible);
	}
}

void APCGManager::SetPCGPolygonDataVisibility(bool bVisible)
{
	for (APCGPolygonContent* PolygonContent : PolygonContents) {
		PolygonContent->ToggleVisibility(bVisible);
	}
}

FString APCGManager::GetPCGShapeFilesPath()
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
				FXmlNode* ShapeFilePathNode = RootNode->FindChildNode(TEXT("ShapeFilesPath"));
				if (ShapeFilePathNode)
				{
					FString ShapeFilePathValueStr = ShapeFilePathNode->GetContent().TrimStartAndEnd();
					return ShapeFilePathValueStr;
				}
			}
		}
	}

	return FString("Invalid");
}


void APCGManager::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	if (Instance == this) {
		Instance = nullptr;
	}
	Super::EndPlay(EndPlayReason);
}

void APCGManager::SetCullDistance(float distanceInMeters) {
	for (APCGPointContent* PointContent : PointContents) {
		PointContent->SetCullDistance(distanceInMeters);
	}
}

//void APCGManager::LoadDataforPCGPoint()
//{
//    FShapeFileReader::LoadDllForGDAL();
//
//    FString ShapefileFolder = FPaths::ProjectContentDir() + TEXT("Shapefiles/PointData/");
//    FPaths::NormalizeDirectoryName(ShapefileFolder);
//
//    if (!FPaths::DirectoryExists(ShapefileFolder))
//    {
//        UE_LOG(LogTemp, Error, TEXT("Shapefile folder does not exist: %s"), *ShapefileFolder);
//        return;
//    }
//
//    TArray<FString> ShapefilePaths;
//    IFileManager::Get().FindFilesRecursive(ShapefilePaths, *ShapefileFolder, TEXT("*.shp"), true, false);
//
//    if (ShapefilePaths.Num() == 0)
//    {
//        UE_LOG(LogTemp, Warning, TEXT(" No shapefiles found in directory: %s"), *ShapefileFolder);
//        return;
//    }
//
//    for (const FString& ShapefilePath : ShapefilePaths)
//    {
//        UE_LOG(LogTemp, Log, TEXT(" Loading shapefile: %s"), *ShapefilePath);
//
//        FShapeRawData RawData = FShapeFileReader::ReadShapefileRawData(ShapefilePath);
//
//        // APCGPointContent* PointContent = NewObject<APCGPointContent>(this, APCGPointContent::StaticClass());
//        APCGPointContent* PointContent = GetWorld()->SpawnActor<APCGPointContent>();
//        if (!PointContent)
//        {
//            UE_LOG(LogTemp, Error, TEXT("Failed to create APCGPointContent for file: %s"), *ShapefilePath);
//            continue;
//        }
//
//        PointContent->InitializePCGPointData(RawData);
//        PointContent->SpawnPCGPointData();
//    }
//}