#pragma once
#include "CoreMinimal.h"
#include "TerrainAssets.h"


struct Struct_CesiumTileMapServiceRasterOverlay {
    FString Name;
    FString Url;
    int32 MinZoom;
    int32 MaxZoom;
    FString MaterialLayerKey;
    bool bSpecifyZoomLevel;
};


struct Struct_CesiumWebMapServiceRasterOverlay {
    FString Name;
    FString BaseUrl;
    FString Layers;
    FString MaterialLayerKey;
};

struct Struct_CesiumWebMapTileServiceRasterOverlay {
    FString Name;
    FString BaseUrl;
    FString Layers;
    FString Format;
    FString TileMatrixSetID;
    FString TileMatrixSetLabelPrefix;
    bool bSpecifyZoomLevel;
    int32 MinZoom;
    int32 MaxZoom;
    FString MaterialLayerKey;
    FString Projection;
};

struct Struct_SplatMapData
{
    FString Name;
    TArray<FString> ShpFilePaths;
};
class TERRAINSYSTEMCONFIG_API Blank_3D_Tileset : public TerrainAssets
{
public:

    FString Blank_3D_Tileset_Url;
    TArray<Struct_CesiumTileMapServiceRasterOverlay> TMSOverlays;
    TArray<Struct_CesiumWebMapServiceRasterOverlay> WMSOverlays;
    TArray<Struct_CesiumWebMapTileServiceRasterOverlay> WMTSOverlays;


    TArray<UCesiumTileMapServiceRasterOverlay*> UTMSOverlays;
    TArray<UCesiumWebMapServiceRasterOverlay*> UWMSOverlays;
    TArray<UCesiumWebMapTileServiceRasterOverlay*> UWMTSOverlays;

    Struct_SplatMapData splatmapdata;
    bool bAssetHasOverlays;
	Blank_3D_Tileset();
	~Blank_3D_Tileset();
    virtual void InitializeAssetCongifs(const FXmlNode* AssetNode, UWorld* World) override;
    virtual void InitializeTerrainAssets(UWorld* World) override;

 
};
