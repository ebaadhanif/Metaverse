#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "AppConstEnumStruct.h"
#include "RibbonMeshActor.generated.h"

UENUM(BlueprintType)
enum class ERibbonTrailMode : uint8
{
    Last30Seconds,
    Last60Seconds,
    Lifetime
};

USTRUCT()
struct FRibbonSegment
{
    GENERATED_BODY()

    FVector Left = FVector::ZeroVector;
    FVector Right = FVector::ZeroVector;
    float   TimeStamp = 0.f;
};

UCLASS()
class METAVERSE_API ARibbonMeshActor : public AActor
{
    GENERATED_BODY()

public:
    ARibbonMeshActor();

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable)
    void SetTrailMode(ERibbonTrailMode NewMode);

    void setForceType(EForceType force);

    void AddRibbonSegment(const FVector& Left, const FVector& Right);

    void stretchPreviousPoints(const FVector& CLeft, const FVector& CRight);

    UFUNCTION(BlueprintCallable)
    void SetTrailVisibility(bool bVisible);

    // Debug helper
    static float ComputeSegmentAngle(const FVector& A1, const FVector& A2, const FVector& B1, const FVector& B2);

private:
    void RebuildMeshFromTrail(const TArray<FRibbonSegment>& Trail);
    void RebuildActiveTrail();                
    void UpdateTailInPlace();                 
    void ComputeSectionSplit(int32 SegmentCount, int32& OutMiddleStart, int32& OutMiddleEnd) const;

private:
    UPROPERTY(VisibleAnywhere)
    UProceduralMeshComponent* RibbonMesh = nullptr;

    // Materials
    UPROPERTY() UMaterialInterface* StartMaterial = nullptr;
    UPROPERTY() UMaterialInterface* MiddleMaterial = nullptr;
    UPROPERTY() UMaterialInterface* EndMaterial = nullptr;
    UPROPERTY() UMaterialInterface* StartRedMaterial = nullptr;
    UPROPERTY() UMaterialInterface* MiddleRedMaterial = nullptr;
    UPROPERTY() UMaterialInterface* EndRedMaterial = nullptr;
    UPROPERTY() UMaterialInterface* DottedMaterial = nullptr;
    UPROPERTY() UMaterialInterface* OthersMaterial = nullptr;
    UPROPERTY() UMaterialInterface* NeutralMaterial = nullptr;
    UPROPERTY() UMaterialInterface* NeutralStartMaterial = nullptr;
    UPROPERTY() UMaterialInterface* NeutralEndMaterial = nullptr;

    UPROPERTY(EditAnywhere)
    ERibbonTrailMode TrailMode = ERibbonTrailMode::Lifetime;


    EForceType ForceType = EForceType::FRIENDLY;

    TArray<FRibbonSegment> LifetimeSegments;
    TArray<FRibbonSegment> Last60sSegments;
    TArray<FRibbonSegment> Last30sSegments;


    TArray<FVector>       SecVerts[3];
    TArray<int32>         SecTris[3];
    TArray<FVector>       SecNormals[3];
    TArray<FVector2D>     SecUVs[3];
    TArray<FLinearColor>  SecColors[3];

    bool  bMeshInitialized = false;
    int32 LastBuiltSegmentCount = 0;
    int32 TailSectionIndex = -1;      // 0=start, 1=mid, 2=end for the *last* segment
    int32 TailVertStartIdx = -1;      // index in SecVerts[TailSectionIndex] where last pair begins

    // Throttling (to avoid rebuilding every call)
    UPROPERTY(EditAnywhere, Category = "Perf")
    float RebuildCooldownSeconds = 0.05f; // 20 Hz max

    float RebuildCooldownTimer = 0.f;
    int32 PendingNewSegments = 0;         // count since last rebuild

    // For SetTrailMode() cache calc
    static constexpr int32 FixedLightCount = 6;
};
