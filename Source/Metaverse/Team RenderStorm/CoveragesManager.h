// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Team SimBridge/EntityBase.h"
#include "CoveragesManager.generated.h"

// Central log category for this class
DECLARE_LOG_CATEGORY_EXTERN(LogCoveragesManager, Log, All);

UENUM(BlueprintType)
enum class ECoverage : uint8
{
    Radar      UMETA(DisplayName = "Radar"),
    SSS        UMETA(DisplayName = "SSS"),
    FighterAircraft   UMETA(DisplayName = "Aircraft")
};

USTRUCT(BlueprintType)
struct FCoverageColors
{
    GENERATED_BODY();

    UPROPERTY(BlueprintReadWrite) FVector4f ThinRing = FVector4f(1, 1, 1, 1);
    UPROPERTY(BlueprintReadWrite) FVector4f ThickRing = FVector4f(1, 1, 1, 1);
    UPROPERTY(BlueprintReadWrite) FVector4f Dome = FVector4f(1, 1, 1, 1);
};

USTRUCT()
struct FCoverageMaterialPaths
{
    GENERATED_BODY();

    // Up to 3 material slots (Thin, Dome, Thick). Some coverage types use 2 mats.
    FString ThinPath;
    FString DomePath;
    FString ThickPath; // optional
    bool HasThick() const { return !ThickPath.IsEmpty(); }
};

UCLASS()
class METAVERSE_API UCoveragesManager : public UObject
{
    GENERATED_BODY()

public:
    /** Lightweight singleton to keep your current usage pattern intact. */
    static UCoveragesManager* GetInstance();

    int32 CalcDomeSortPriority(AEntityBase* Entity);

    /** Set the world once during startup (e.g., from GameMode or similar). */
    void SetWorld(UWorld* InWorld);

    /** Adds an entity and attaches its coverage mesh + optional footprint. */
    void AddEntityToCoveragesList(AEntityBase* Entity);


    FVector GetCoverageScale(AEntityBase* Entity);

    /** Draw 2D footprint for a radar entity (separate from 3D mesh). */
    void AttachCoverageFootPrint(AEntityBase* Entity);

    /** Global toggles */
    void ToggleVisibility(bool bVisible);
    void ToggleFootPrintsVisibility(bool bVisible);



    void ToggleVisibilityOfCoveragesByRemoteEntityType(bool bVisible, ERemoteEntityType RemoteEntityType);

    void ToggleFootPrintsVisibilityForEntity(AEntityBase* Entity, bool bVisible);

    void ToggleHorizontalRings(bool bVisible);


    /** Returns the tracked entities (prunes nulls before returning). */
    TArray<AEntityBase*> GetEntitiesCoveragesList();

    /** Count of currently tracked, valid entities. */
    int32 GetNumberofCoverageEntities();

    /** Call when shutting down the manager (e.g., map unload). */
    void Shutdown();


    /** Remove an entity from the manager and destroy all coverage artifacts. */
    bool RemoveEntity(AEntityBase* Entity);

    /** Convenience: remove by FEntityID (returns true if found & removed). */
    bool RemoveEntityById(const FEntityID& Id);

    void SpawnProceduralRingsOnDome(AEntityBase* DomeActor, UStaticMeshComponent* DomeComp, float IntervalMeters, int32 Segments, float RingWidthMeters, float RingHeightMeters, float SurfacePushCm, FName TagForCleanup, bool, bool bIgnoreOtherDomes);

    UStaticMeshComponent* FindDomeComp(AActor* DomeActor) const;

    void UpdateProceduralRingIntervalForActor(AActor* DomeActor, float NewIntervalMetersFromTop, int32 Segments, float RingWidthMeters, float RingHeightMeters, float SurfacePushCm, FName TagForCleanup);

    void UpdateProceduralRingIntervalForAll(float NewIntervalMeters, int32 Segments, float RingWidthMeters, float RingHeightMeters, float SurfacePushCm, FName TagForCleanup);

    void ToggleAircraftsDefaultAndOriginal(bool isTrueScale);

private:
    // === Internal helpers ===
    void AttachCoverageMesh(AEntityBase* Entity);
    FVector GetDefaultScale(AEntityBase* Entity);

    void ApplyCustomMaterial(AEntityBase* Entity);
    FCoverageColors GetEntityTypeColor(EForceType Type) const;
    ECoverage GetCoverageKindForEntity(AEntityBase* Entity);

    /** Centralized asset paths for each coverage kind. */
    const FCoverageMaterialPaths& GetMaterialPaths(ECoverage Kind) const;
    const FString& GetMeshPath(ECoverage Kind) const;

    /** Loads and caches mesh/material assets. */
    UStaticMesh* LoadCoverageMesh(ECoverage Kind);
    UMaterialInterface* LoadMaterial(const FString& Path);
    void                          EnsureAssetsCached(ECoverage Kind);

    void PruneNullActors();

    UMaterialInterface* RingMat = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/MyModels/CoverageModels/Radar/M_Ring.M_Ring'"));


    void ClearAll();
private:
    // Keep your SSS type for comparison (initialized once).
    FEntityType SSS;

    /** Tracked entities; we keep raw pointers to preserve your external API. */
    TArray<AEntityBase*> ActorList;

    /** Simple singleton storage. */
    static UCoveragesManager* Instance;

    /** We keep a ref to world (set once). */
    UPROPERTY() UWorld* World = nullptr;

    // === Cached assets ===
    TMap<ECoverage, UStaticMesh*> CachedMeshes;
    TMap<FString, UMaterialInterface*> CachedMaterials;

    // === Constants ===
    static constexpr float CM_PER_NM = 185200.0f; // 1 nautical mile = 1852m = 185200cm
    static constexpr float M_PER_NM = 1852.0f; // 1 nautical mile = 1852m = 185200cm
    static constexpr float DEFAULT_FOOTPRINT_ALT_M = 25000.0f;
    static constexpr float FOOTPRINT_LINE_WIDTH = 100.0f;
    static constexpr float FOOTPRINT_LINE_HEIGHT = 100.0f;

    // Parameter FNames (avoid re-allocations)
    static const FName NAME_Color;
    static const FName NAME_Opacity;


    /** Internal: destroy footprint, mesh/component, and clear refs on the entity. */
    void CleanupCoverageForEntity(AEntityBase* Entity);

    void CleanupExistingRings(AActor* DomeActor, FName TagForCleanup);


};
