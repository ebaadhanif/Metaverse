#pragma once
#include "CoreMinimal.h"
#include "TerrainAssets.h"

class TERRAINSYSTEMCONFIG_API ARCGIS_Tileset_Asset : public TerrainAssets
{
public:
	ARCGIS_Tileset_Asset();
	~ARCGIS_Tileset_Asset();
	virtual void InitializeAssetCongifs(const FXmlNode* AssetNode, UWorld* World) override;
	virtual void InitializeTerrainAssets(UWorld* World) override;
};
