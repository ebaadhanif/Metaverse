// Fill out your copyright notice in the Description page of Project Settings.


#include "ModeManager.h"



AModeManager* AModeManager::instance = nullptr;
// Sets default values
AModeManager::AModeManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    const FString ConfigPath = FPaths::Combine(FPaths::ProjectContentDir(), TEXT("Archive/AppConfig.xml"));
    const FString ConfigModeFolderPath = FPaths::Combine(FPaths::ProjectContentDir(), TEXT("Archive/Modes"));
    if (!LoadModesFromConfig(ConfigModeFolderPath, ConfigPath)) {
        return;
    }

}

// Called when the game starts or when spawned
void AModeManager::BeginPlay()
{
	Super::BeginPlay();
    instance = this;
	
}

// Called every frame
void AModeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



AModeManager* AModeManager::getInstance()
{
    return instance;
}

bool AModeManager::LoadModesFromConfig(const FString& ConfigFileFolder, const FString& AppConfigFile)
{
    FXmlFile AppConfigXmlFile(AppConfigFile);
    const FXmlNode* RootNode = AppConfigXmlFile.GetRootNode();
    if (!RootNode || RootNode->GetTag() != TEXT("AppConfig"))
    {
        return false;
    }

    FString RequestedActiveModeName;
    if (const FXmlNode* ActiveModeNode = RootNode->FindChildNode(TEXT("ActiveMode")))
    {
        if (const FXmlNode* ActiveTypeNode = ActiveModeNode->FindChildNode(TEXT("ActiveUIType")))
        {
            RequestedActiveModeName = ActiveTypeNode->GetContent().TrimStartAndEnd();
        }
    }
    if (RequestedActiveModeName.IsEmpty())
    {
        return false;
    }

    //MetaverseModes.Empty();
    //ActiveMode = nullptr;

    IFileManager& FileManager = IFileManager::Get();
    TArray<FString> xmlFiles;

    const FString SearchPattern = ConfigFileFolder / TEXT("*.xml");
    FileManager.FindFiles(xmlFiles, *SearchPattern, true, false);
    const FXmlNode* MatchedModeNode = nullptr;
    if (xmlFiles.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("No xml files found in folder: %s"), *ConfigFileFolder); 
        return false;
    }

    for (const FString& FileName : xmlFiles)
    {
        const FString FullPath = ConfigFileFolder / FileName;
        FXmlFile XmlFile(FullPath);

        if (!XmlFile.IsValid())
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to load xml: %s"), *FullPath);
            return false;
        }

        const FXmlNode* RootNodeMode = XmlFile.GetRootNode();
        if (!RootNodeMode || RootNodeMode->GetTag() != TEXT("Mode"))
        {
            continue;
        }
        const FXmlNode* NameNode = RootNodeMode->FindChildNode(TEXT("ModeName"));
        if (!NameNode)
        {
            continue;
        }
        const FString ThisModeName = NameNode->GetContent().TrimStartAndEnd();
        UMetaverseMode* Mode = NewObject<UMetaverseMode>(GetTransientPackage());
        Mode->AddToRoot();
        if (!Mode->InitFromXmlModeNode(RootNodeMode))
        {
            return false;
        }
        ;
        MetaverseModes.Add(FName(ThisModeName), Mode);
        if (ThisModeName.Equals(RequestedActiveModeName, ESearchCase::IgnoreCase))
        {
            MatchedModeNode = RootNodeMode;
            //break;
        }
    }

    if (!MatchedModeNode)
    {
        return false;
    }
    //UMetaverseMode** ActiveModeReference = MetaverseModes.Find(FName(MatchedModeNode->GetContent().TrimStartAndEnd()));

    if (UMetaverseMode** Found = MetaverseModes.Find(FName(RequestedActiveModeName)))
    {
        if (UMetaverseMode* Comp = *Found) {
            ActiveMode = Comp;
        }
    }
    if (!ActiveMode)
    {
        return false;
    }

    return true;
}

UMetaverseMode* AModeManager::getActiveMode() {
    return ActiveMode;
}


void AModeManager::setActiveMode(UMetaverseMode* Mode) {
    ActiveMode = Mode;
}


