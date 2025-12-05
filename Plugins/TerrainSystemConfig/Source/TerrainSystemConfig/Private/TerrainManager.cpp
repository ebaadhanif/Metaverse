#include "TerrainManager.h"
#include "CesiumSystem.h"
#include "ARCGisSystem.h"
#include "Blank_3D_Tileset.h"

bool ATerrainManager::bhasConfigured = false; 

ATerrainManager* ATerrainManager::Instance = nullptr;

ATerrainManager::ATerrainManager()
{	
	PrimaryActorTick.bCanEverTick = false;
}

void ATerrainManager::BeginPlay()
{
	Super::BeginPlay();
    if (Instance == nullptr)
    {
        Instance = this;
    }
    ClearUpPreviousCachedTileset(GetWorld());
    LoadTerrainConfigurations(XmlFilePath, GetWorld());
    InitializeActiveTerrain(GetWorld());
}

void ATerrainManager::OnConstruction(const FTransform& Transform)
{
    if (bhasConfigured)
    {
        return;
    }
    else
    {
        ClearUpPreviousCachedTileset(GetWorld());
        LoadTerrainConfigurations(XmlFilePath,GetWorld());
        InitializeActiveTerrain(GetWorld());
        bhasConfigured = true;
       
    }
}

void ATerrainManager::LoadTerrainConfigurations(const FString& ConfigFilePath, UWorld* World) {
    FXmlFile ConfigFile(ConfigFilePath);
    if (!ConfigFile.IsValid()) {
        UE_LOG(LogTemp, Error, TEXT("Failed to load configuration file: %s"), *ConfigFilePath);
        return;
    }

    const FXmlNode* RootNode = ConfigFile.GetRootNode();
    if (!RootNode) {
        UE_LOG(LogTemp, Error, TEXT("Invalid XML structure: Root node missing."));
        return;
    }

    const FXmlNode* ActiveConfigNode = RootNode->FindChildNode(TEXT("ActiveConfiguration"));
    int32 ActiveTerrainID = ActiveConfigNode && ActiveConfigNode->FindChildNode(TEXT("ActiveTerrainID")) ?
        FCString::Atoi(*ActiveConfigNode->FindChildNode(TEXT("ActiveTerrainID"))->GetContent()) : -1;

    for (const FXmlNode* TerrainNode : RootNode->GetChildrenNodes()) {
        if (TerrainNode->GetTag() != TEXT("Terrain")) continue;

        ConfigureTerrain(TerrainNode, World);

        int32 TerrainID = FCString::Atoi(*TerrainNode->FindChildNode(TEXT("ID"))->GetContent());
        if (TerrainID == ActiveTerrainID && TerrainSystemList.Num() > 0) {
            ActiveTerrainSystem = TerrainSystemList.Last();
        }
    }

    if (!ActiveTerrainSystem) {
        UE_LOG(LogTemp, Warning, TEXT("No active terrain system found for ID: %d"), ActiveTerrainID);
    }
}

void ATerrainManager::ConfigureTerrain(const FXmlNode* TerrainNode, UWorld* World) {
    FString TerrainType = TerrainNode->FindChildNode(TEXT("Type"))->GetContent();

    TerrainSystem* tempTerrainSystem = nullptr;
    
    // * function  * //
    if (TerrainType.Equals(TEXT("CESIUM"), ESearchCase::IgnoreCase)) {
        //tempTerrainSystem = new CesiumSystem();
        tempTerrainSystem = GetSpecificTerrainSystemPtr("CESIUM");
    }
    else if (TerrainType.Equals(TEXT("ARCGIS"), ESearchCase::IgnoreCase))
    {
        //tempTerrainSystem = new ARCGisSystem();
        tempTerrainSystem = GetSpecificTerrainSystemPtr("ARCGIS");
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Unsupported terrain type: %s"), *TerrainType);
        return;
    }

    if (tempTerrainSystem) {
        tempTerrainSystem->InitializeTerrainConfigs(TerrainNode, World);
        TerrainSystemList.Add(tempTerrainSystem);

        UE_LOG(LogTemp, Log, TEXT("Initialized terrain: %s"), *tempTerrainSystem->TerrainName);
    }
}

void ATerrainManager::InitializeActiveTerrain(UWorld* World) {
    if (ActiveTerrainSystem) {
        ActiveTerrainSystem->InitializeTerrainSystem(World);
        UE_LOG(LogTemp, Log, TEXT("Added tileset for active terrain: %s"), *ActiveTerrainSystem->TerrainName);
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("No active terrain system to add."));
    }
}

TerrainSystem* ATerrainManager::GetSpecificTerrainSystemPtr(FString TerrainType)
{
    TerrainSystem* tempTerrainSystem = nullptr;
    if (TerrainType.Equals(TEXT("CESIUM"), ESearchCase::IgnoreCase)) {
        tempTerrainSystem= new CesiumSystem();
    }
    else if (TerrainType.Equals(TEXT("ARCGIS"), ESearchCase::IgnoreCase))
    {
        tempTerrainSystem= new ARCGisSystem();
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Unsupported terrain type: %s"), *TerrainType);
      
    }
    return tempTerrainSystem;
}

void ATerrainManager::ClearUpPreviousCachedTileset(UWorld* World) {
    // Remove existing Tilesets
    for (TActorIterator<ACesium3DTileset> It(World); It; ++It) {
        ACesium3DTileset* Tileset = *It;
        if (Tileset) {
            Tileset->Destroy();
        }
    }
}

void ATerrainManager::ShiftToShadedReleif(bool isShadedOn) {
    if (isShadedOn)
    {
        for (TerrainAssets* Asset : ActiveTerrainSystem->TerrainAssetsList) {
            if (Asset && Asset->TilesetAssetName == "Shaded Releif") {
                Asset->Tileset->SetActorHiddenInGame(false);
            }
            else
            {
                Asset->Tileset->SetActorHiddenInGame(true);
            }
        }
    }
    else
    {
        for (TerrainAssets* Asset : ActiveTerrainSystem->TerrainAssetsList) {
            if (Asset && Asset->TilesetAssetName == "Shaded Releif") {
                Asset->Tileset->SetActorHiddenInGame(true);
            }
            else
            {
                Asset->Tileset->SetActorHiddenInGame(false);
            }
        }
    }
}

void ATerrainManager::ToggleInternationalBorder(bool isBorderOn) {
    for (TerrainAssets* Asset : ActiveTerrainSystem->TerrainAssetsList) {
        if (Blank_3D_Tileset* Tileset = static_cast<Blank_3D_Tileset*>(Asset)) {
            for (UCesiumWebMapServiceRasterOverlay* Overlay : Tileset->UWMSOverlays) {
                if (Overlay->GetName() == "InternationalBorder CesiumWebMapServiceRasterOverlay") {
                    if (isBorderOn && Overlay) {
                        Overlay->Activate(true);
                        Overlay->SetComponentTickEnabled(true);
                        //CWMSRO->RegisterComponent();
                        //Asset->Tileset->Modify();
                    }
                    else {
                        Overlay->Deactivate();
                        Overlay->SetComponentTickEnabled(false);
                        //CWMSRO->RemoveFromTileset();
                        //CWMSRO->UnregisterComponent();
                        //Asset->Tileset->Modify();
                    }
                }
            }
        }
    }
}

void ATerrainManager::ToggleContour(bool isBorderOn) {
    for (TerrainAssets* Asset : ActiveTerrainSystem->TerrainAssetsList) {
        if (Blank_3D_Tileset* Tileset = static_cast<Blank_3D_Tileset*>(Asset)) {
            for (UCesiumWebMapServiceRasterOverlay* Overlay : Tileset->UWMSOverlays) {
                if (Overlay->GetName() == "Contours CesiumWebMapServiceRasterOverlay") {
                    if (isBorderOn && Overlay) {
                        Overlay->Activate(true);
                        Overlay->SetComponentTickEnabled(true);
                        //CWMSRO->RegisterComponent();
                        //Asset->Tileset->Modify();
                    }
                    else {
                        Overlay->Deactivate();
                        Overlay->SetComponentTickEnabled(false);
                        //CWMSRO->RemoveFromTileset();
                        //CWMSRO->UnregisterComponent();
                        //Asset->Tileset->Modify();
                    }
                }
            }
        }
    }
}

void ATerrainManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (Instance == this) {
        Instance = nullptr;
    }
    Super::EndPlay(EndPlayReason);
}

ATerrainManager* ATerrainManager::GetInstance()
{
    return Instance;
}



//for (TerrainAssets* Asset : ActiveTerrainSystem->TerrainAssetsList) {
//    if (Asset->Tileset->GetComponentByClass<UCesiumWebMapServiceRasterOverlay>()) {
//        UCesiumWebMapServiceRasterOverlay* CWMSRO = Asset->Tileset->FindComponentByClass<UCesiumWebMapServiceRasterOverlay>();
//        UE_LOG(LogTemp, Warning, TEXT("Border Name: %s"), *CWMSRO->GetName());
//        if (CWMSRO->GetName() == "Contours CesiumWebMapServiceRasterOverlay") {
//            if (isBorderOn && CWMSRO) {
//                CWMSRO->Activate(true);
//                CWMSRO->SetComponentTickEnabled(true);
//            }
//            else {
//                CWMSRO->Deactivate();
//                CWMSRO->SetComponentTickEnabled(false);
//            }
//        }
//    }
//}