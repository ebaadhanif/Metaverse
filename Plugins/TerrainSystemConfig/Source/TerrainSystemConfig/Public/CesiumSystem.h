#pragma once
#include "CoreMinimal.h"
#include "TerrainSystem.h"
class TERRAINSYSTEMCONFIG_API CesiumSystem : public TerrainSystem
{
public:
	CesiumSystem();
	~CesiumSystem();
public:
    virtual void InitializeTerrainConfigs(const FXmlNode* TerrainNode , UWorld* World) override;
    virtual void InitializeTerrainSystem(UWorld* World) override;
    void SetCesiumGeoRefference(UWorld* World);


};
