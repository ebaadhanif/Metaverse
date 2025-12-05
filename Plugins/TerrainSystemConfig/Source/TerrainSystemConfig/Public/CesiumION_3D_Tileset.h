#pragma once
#include "CoreMinimal.h"
#include "TerrainAssets.h"

class TERRAINSYSTEMCONFIG_API CesiumION_3D_Tileset : public TerrainAssets
{
public:
	int32 Cesium_ION_AssetID;
	FString Cesium_ION_AccessToken;
	CesiumION_3D_Tileset();
	~CesiumION_3D_Tileset();
	virtual void InitializeAssetCongifs(const FXmlNode* AssetNode, UWorld* World) override;
	virtual void InitializeTerrainAssets(UWorld* World) override;
};
