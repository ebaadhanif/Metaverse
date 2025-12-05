#include "CesiumION_3D_Tileset.h"
#include "GameFramework/Actor.h"

CesiumION_3D_Tileset::CesiumION_3D_Tileset()
{
}

CesiumION_3D_Tileset::~CesiumION_3D_Tileset()
{
}

void CesiumION_3D_Tileset::InitializeAssetCongifs(const FXmlNode* AssetNode, UWorld* World) {
    TilesetAssetName = AssetNode->FindChildNode(TEXT("Name"))->GetContent();
    TilesetAssetType = AssetNode->FindChildNode(TEXT("Type"))->GetContent();
    TilesetAssetSource = ETilesetSource::FromCesiumIon;
    const FXmlNode* DetailsNode = AssetNode->FindChildNode(TEXT("Cesium_ION"));
    if (DetailsNode) {
        Cesium_ION_AssetID = FCString::Atoi(*DetailsNode->FindChildNode(TEXT("Cesium_ION_AssetID"))->GetContent());
        Cesium_ION_AccessToken = DetailsNode->FindChildNode(TEXT("Cesium_ION_AccessToken"))->GetContent();
    }
}

void CesiumION_3D_Tileset::InitializeTerrainAssets(UWorld* World) {
    //FActorSpawnParameters SpawnParams;
    //SpawnParams.Name = FName(TilesetAssetName);
    //ACesium3DTileset* Tileset = World->SpawnActor<ACesium3DTileset>(ACesium3DTileset::StaticClass(), SpawnParams);
     Tileset = World->SpawnActor<ACesium3DTileset>();
    if (Tileset) {
        ACesiumGeoreference* GeoreferenceActor = nullptr;
        for (TActorIterator<ACesiumGeoreference> It(World); It; ++It) {
            GeoreferenceActor = *It;
            break;
        }
        Tileset->SetTilesetSource(ETilesetSource::FromCesiumIon);
        Tileset->AttachToActor(GeoreferenceActor, FAttachmentTransformRules::KeepRelativeTransform);
#if WITH_EDITOR
        Tileset->SetActorLabel(TilesetAssetName); 
#endif
        

        Tileset->SetIonAssetID(Cesium_ION_AssetID);
        Tileset->SetIonAccessToken(Cesium_ION_AccessToken);

        //Tileset->MaximumCachedBytes = 10000000000000; //  cache (Adjust as needed)

        //// ✅ Load More Tiles Simultaneously
        //Tileset->LoadingDescendantLimit = 10000; // Increase number of tiles loaded at once

        //// ✅ Disable Frustum Culling (Loads all tiles, even outside view)
        //Tileset->EnableFrustumCulling = false;

        //// ✅ Disable Fog Culling (Prevents tiles from disappearing in fog)
        //Tileset->EnableFogCulling = false;

        //// ✅ Force High-Resolution Tile Loading

        //Tileset->MaximumScreenSpaceError = 5.0; // Lower values = better detail, more memory usage

        //Tileset->MaximumSimultaneousTileLoads = 100000;
        //Tileset->bEnableAutoLODGeneration = false;
 
        //Tileset->SetActorHiddenInGame(true);
    }
}
