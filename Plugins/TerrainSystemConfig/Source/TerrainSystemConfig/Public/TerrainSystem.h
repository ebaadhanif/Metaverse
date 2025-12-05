#pragma once
#include "CoreMinimal.h"
#include "TerrainAssets.h"
class TERRAINSYSTEMCONFIG_API TerrainSystem
{
public:

	int32 TerrainID;
	FString TerrainName;
	FString TerrainType;
	FVector Georeference;
	TArray<TerrainAssets*> TerrainAssetsList; // Dynamic list of Terrain assets
	TerrainSystem();
	virtual ~TerrainSystem() = default;
	virtual void InitializeTerrainConfigs(const FXmlNode* TerrainNode, UWorld* World) PURE_VIRTUAL(TerrainSystem::InitializeTerrainConfigs, );
	virtual void InitializeTerrainSystem(UWorld* World) PURE_VIRTUAL(TerrainSystem::InitializeTerrainSystem, );

};