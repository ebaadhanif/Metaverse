#include "ARCGisSystem.h"
#include "ARCGIS_Tileset_Asset.h"
ARCGisSystem::ARCGisSystem()
{
}

ARCGisSystem::~ARCGisSystem()
{
}

void ARCGisSystem::InitializeTerrainConfigs(const FXmlNode* TerrainNode, UWorld* World)
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

        if (AssetType.Equals(TEXT("ARCGIS_Tileset_Asset"), ESearchCase::IgnoreCase)) {
            TerrainAssetsPtr = new ARCGIS_Tileset_Asset();
        }
        if (TerrainAssetsPtr) {
            TerrainAssetsPtr->InitializeAssetCongifs(AssetNode, World);
            TerrainAssetsList.Add(TerrainAssetsPtr);
        }
    }
}

void ARCGisSystem::InitializeTerrainSystem(UWorld* World)
{
    for (TerrainAssets* Asset : TerrainAssetsList) {
        if (Asset && (Asset->TilesetAssetType == "ARCGIS_Tileset")) {
            Asset->InitializeTerrainAssets(World);
        }
    }
   
}
