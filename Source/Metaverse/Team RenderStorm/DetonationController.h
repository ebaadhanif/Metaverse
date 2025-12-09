// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#undef OPAQUE
#include "CesiumGeoreference.h"
#include "Cesium3DTileset.h"
#include "Engine/World.h"
#include "CesiumPolygonRasterOverlay.h"
#include "NiagaraComponent.h"
#include "DetonationController.generated.h"

//class ACesiumPlotMeshActor;
class ACesium3DTileset;
class ACesiumGeoreference;

UCLASS()
class METAVERSE_API UDetonationController : public UObject
{
    GENERATED_BODY()

public:
    static UDetonationController* Get();
    void SpawnDetonationEffectsOnTerrain(const TArray<FVector>& LatLonPoints);
    void InitializeOverlay();
    void SpawnDetonationEffectOnTerrain(double Lat, double Lon);
    void Shutdown();

    UPROPERTY()
    UCesiumPolygonRasterOverlay* SharedRasterOverlay;

    void SetWorldVariable(UWorld* InWorld);
    UWorld* GetStoredWorld();

    static void SetGeoreference(ACesiumGeoreference* InGeoref);
    static ACesiumGeoreference* GetGeoreference();
    static void SetTileset(ACesium3DTileset* InTileset);
    static ACesium3DTileset* GetTileset();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Beam")
    UNiagaraComponent* DetonationNiagaraSystem = nullptr;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Beam")
    UNiagaraComponent* DetonationNiagaraComponent = nullptr;


protected:
    static ACesiumGeoreference* Georeference;
    static ACesium3DTileset* Tileset;
    UWorld* m_World;

    FTimerHandle UpdatePlotMeshTimerHandle;

private:
    UFUNCTION()
    void ClearDetonations();

   // UPROPERTY()
  //  TArray<ACesiumPlotMeshActor*> SpawnedPlotActors;

    float MinDistanceBetweenDetonations = 15000.0f;

    static UDetonationController* Instance;


    UPROPERTY()
    AActor* DetonationsRoot = nullptr;
    AActor* EnsureDetonationsRoot();
    static FString MakeDetonationLabel(double Lat, double Lon);





};


