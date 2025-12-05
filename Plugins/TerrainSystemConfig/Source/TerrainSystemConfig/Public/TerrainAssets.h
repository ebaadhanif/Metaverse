#pragma once
#include "CoreMinimal.h"
#include "windows/WindowsWindow.h"
#undef OPAQUE
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "Cesium3DTileset.h"
#include "XmlFile.h"
#include "CesiumGeoreference.h"
#include "CesiumTileMapServiceRasterOverlay.h"
#include "CesiumWebMapServiceRasterOverlay.h"
#include "CesiumWebMapTileServiceRasterOverlay.h"
#include "EngineUtils.h"


class TERRAINSYSTEMCONFIG_API TerrainAssets
{
public:
	TerrainAssets();
	virtual ~TerrainAssets() = default;
	int32 TilesetAssetID;
	FString TilesetAssetName;
	FString TilesetAssetType;
	FString TilesetAssetVisibility;
	ACesium3DTileset* Tileset;
	ETilesetSource TilesetAssetSource;
	virtual void InitializeAssetCongifs(const FXmlNode* AssetNode, UWorld* World) PURE_VIRTUAL(TerrainAssets::InitializeAssetCongifs, );
	virtual void InitializeTerrainAssets(UWorld* World) PURE_VIRTUAL(TerrainAssets::InitializeTerrainAssets, );
};
