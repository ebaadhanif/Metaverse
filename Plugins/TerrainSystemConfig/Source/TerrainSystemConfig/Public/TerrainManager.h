#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TerrainSystem.h"
#include "Misc/Paths.h"
#include "TerrainManager.generated.h"

UCLASS()
class TERRAINSYSTEMCONFIG_API ATerrainManager : public AActor
{
    GENERATED_BODY()

private:
    static ATerrainManager* Instance;

public:
    enum TerrainTypes {
        Empty,
        CESIUM,
        ARCGIS

    };
    static bool bhasConfigured; 
    FString XmlFilePath = FPaths::ProjectDir() + TEXT("Content/Archive/TerrainConfigs.xml");
    void LoadTerrainConfigurations(const FString& ConfigFilePath, UWorld* World);
    void ConfigureTerrain(const FXmlNode* TerrainNode, UWorld* World);
    void InitializeActiveTerrain(UWorld* World);
    TerrainSystem* GetSpecificTerrainSystemPtr(FString TerrainType);
    void ClearUpPreviousCachedTileset(UWorld* World);
    void ShiftToShadedReleif(bool isShadedOn);
    void ToggleInternationalBorder(bool isBorderOn);
    TArray<TerrainSystem*> TerrainSystemList; // List of terrain systems
    TerrainSystem* ActiveTerrainSystem;   // The active terrain system
    ATerrainManager();
    void BeginPlay();
    void OnConstruction(const FTransform& Transform);
    static ATerrainManager* GetInstance();
    void ToggleContour(bool isBorderOn);
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


};
