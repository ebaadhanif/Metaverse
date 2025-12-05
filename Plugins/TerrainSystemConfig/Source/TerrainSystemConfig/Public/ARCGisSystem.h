#pragma once
#include "CoreMinimal.h"
#include "TerrainSystem.h"
class TERRAINSYSTEMCONFIG_API ARCGisSystem : public TerrainSystem
{
public:
	ARCGisSystem();
	~ARCGisSystem();
public:
	virtual void InitializeTerrainConfigs(const FXmlNode* TerrainNode, UWorld* World) override;
	virtual void InitializeTerrainSystem(UWorld* World) override;
};
