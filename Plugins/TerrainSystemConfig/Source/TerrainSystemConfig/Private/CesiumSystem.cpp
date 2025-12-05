#include "CesiumSystem.h"
#include "Blank_3D_Tileset.h"
#include "CesiumION_3D_Tileset.h"
CesiumSystem::CesiumSystem()
{
}

CesiumSystem::~CesiumSystem()
{
}

void CesiumSystem::InitializeTerrainConfigs(const FXmlNode* TerrainNode, UWorld* World)
{
    TerrainID = FCString::Atoi(*TerrainNode->FindChildNode(TEXT("ID"))->GetContent());
    TerrainName = TerrainNode->FindChildNode(TEXT("Name"))->GetContent();
    TerrainType = TerrainNode->FindChildNode(TEXT("Type"))->GetContent();

    const FXmlNode* GeoreferenceNode = TerrainNode->FindChildNode(TEXT("Georeference"));
    if (GeoreferenceNode) {
        Georeference.X = FCString::Atod(*GeoreferenceNode->FindChildNode(TEXT("Longitude"))->GetContent());
        Georeference.Y = FCString::Atod(*GeoreferenceNode->FindChildNode(TEXT("Latitude"))->GetContent());
        Georeference.Z = FCString::Atod(*GeoreferenceNode->FindChildNode(TEXT("Height"))->GetContent());
    }

    for (const FXmlNode* AssetNode : TerrainNode->GetChildrenNodes()) {
        if (AssetNode->GetTag() != TEXT("Asset")) continue;

        FString AssetType = AssetNode->FindChildNode(TEXT("Type"))->GetContent();
        TerrainAssets* TerrainAssetsPtr = nullptr;

        if (AssetType.Equals(TEXT("Blank_3D_Tileset"), ESearchCase::IgnoreCase)) {
            TerrainAssetsPtr = new Blank_3D_Tileset();
        }
        else if (AssetType.Equals(TEXT("CesiumION_3D_Tileset"), ESearchCase::IgnoreCase)) {
            TerrainAssetsPtr = new CesiumION_3D_Tileset();
        }

        if (TerrainAssetsPtr) {
            TerrainAssetsPtr->InitializeAssetCongifs(AssetNode,World);
            TerrainAssetsList.Add(TerrainAssetsPtr);
        }
    }
}



void CesiumSystem::InitializeTerrainSystem(UWorld* World) {
    // Remove existing Tilesets
    for (TActorIterator<ACesium3DTileset> It(World); It; ++It) {
        ACesium3DTileset* Tileset = *It;
        if (Tileset) {
            Tileset->Destroy();
        }
    }
    for (TerrainAssets* Asset : TerrainAssetsList) {
        if (Asset && (Asset->TilesetAssetType== "CesiumION_3D_Tileset" || Asset->TilesetAssetType == "Blank_3D_Tileset")) {
            Asset->InitializeTerrainAssets(World);
            if (Asset->TilesetAssetVisibility.Equals(TEXT("true"), ESearchCase::IgnoreCase))
            {
                Asset->Tileset->SetActorHiddenInGame(false);
            }
            else if (Asset->TilesetAssetVisibility.Equals(TEXT("false"), ESearchCase::IgnoreCase))
            {
                Asset->Tileset->SetActorHiddenInGame(true);
#if WITH_EDITOR
                Asset->Tileset->SetIsTemporarilyHiddenInEditor(true);
#endif

            }
        }
    }

    SetCesiumGeoRefference(World);
   
}

void CesiumSystem::SetCesiumGeoRefference(UWorld* World)
{
    ACesiumGeoreference* GeoreferenceActor = nullptr;
    for (TActorIterator<ACesiumGeoreference> It(World); It; ++It) {
        GeoreferenceActor = *It;
        break;
    }
    if (GeoreferenceActor) {
        GeoreferenceActor->SetOriginLongitudeLatitudeHeight(Georeference);
        UE_LOG(LogTemp, Log, TEXT("Set CesiumGeoreference origin to Longitude: %f, Latitude: %f, Height: %f"),
            Georeference.X, Georeference.Y, Georeference.Z);
    }
}




