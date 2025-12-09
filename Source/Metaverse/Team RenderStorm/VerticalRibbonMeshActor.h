#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "AppConstEnumStruct.h"
#include "VerticalRibbonMeshActor.generated.h"

UENUM(BlueprintType)
enum class EVerticalRibbonTrailMode : uint8
{
    Last30Seconds,
    Last60Seconds,
    Lifetime
};

USTRUCT()
struct FVerticalRibbonSegment
{
    GENERATED_BODY()

    FVector Left = FVector::ZeroVector;
    FVector Right = FVector::ZeroVector;
    float   TimeStamp = 0.f;
};

UCLASS()
class METAVERSE_API AVerticalRibbonMeshActor : public AActor
{
    GENERATED_BODY()

public:
    AVerticalRibbonMeshActor();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable)
    void SetTrailMode(EVerticalRibbonTrailMode NewMode);

    void setForceType(EForceType force);

    void AddRibbonSegment(const FVector& Left, const FVector& Right, float DistanceFromCamera);
    void SetTrailVisibility(bool bVisible);


    void stretchPreviousPoints(const FVector& CLeft, const FVector& CRight, float DistanceFromCamera);

    static float ComputeSegmentAngle(const FVector& A1, const FVector& A2, const FVector& B1, const FVector& B2);

    virtual void OnConstruction(const FTransform& Transform) override;


private:

    void RebuildActiveTrail();
    void RebuildMeshFromTrail(const TArray<FVerticalRibbonSegment>& Trail);
    void RebuildCompleteTrail(const TArray<FVerticalRibbonSegment>& Trail);


    void UpdateTailInPlace();

    void ComputeSectionSplit(int32 SegmentCount, int32& OutMiddleStart, int32& OutMiddleEnd) const;


    UFUNCTION(BlueprintCallable, Category = "Ribbon")
    void SetStripeInterval(float NewIntervalCM);
private:
    UPROPERTY(VisibleAnywhere)
    UProceduralMeshComponent* RibbonMesh = nullptr;
    UProceduralMeshComponent* RibbonMesh30Seconds = nullptr;
    UProceduralMeshComponent* RibbonMesh60Seconds = nullptr;

    UPROPERTY() UMaterialInterface* FriendlyMaterial = nullptr;
    UPROPERTY() UMaterialInterface* OpposingMaterial = nullptr;
    UPROPERTY() UMaterialInterface* NeutralMaterial = nullptr;
    UPROPERTY() UMaterialInterface* OthersMaterial = nullptr;


    UPROPERTY() UMaterialInterface* FriendlyMaterialLod2 = nullptr;
    UPROPERTY() UMaterialInterface* OpposingMaterialLod2 = nullptr;
    UPROPERTY() UMaterialInterface* NeutralMaterialLod2 = nullptr;

    UMaterialInterface* UseMat = nullptr;

    UPROPERTY(EditAnywhere, Category = "Ribbon|Appearance", meta = (ClampMin = "1.0"))
    float StripeIntervalCM = 8000.f; 

    UPROPERTY(EditAnywhere, Category = "Ribbon|Appearance", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float VWidthScale = 1.f;

    float DistanceFromCamera;

    UPROPERTY(EditAnywhere)
    EVerticalRibbonTrailMode TrailMode = EVerticalRibbonTrailMode::Lifetime;

    EForceType ForceType = EForceType::FRIENDLY;


    // Cached editor values to auto-rebuild on tweak
    float CachedStripeIntervalCM = -1.f;
    float CachedVWidthScale = -1.f;

    TArray<FVerticalRibbonSegment> LifetimeSegments;
    TArray<FVerticalRibbonSegment> Last60sSegments;
    TArray<FVerticalRibbonSegment> Last30sSegments;
    TArray<FVerticalRibbonSegment> CurrentSectionSegments;

    //TArray<FVector>       SecVerts[3];
    //TArray<int32>         SecTris[3];
    //TArray<FVector>       SecNormals[3];
    //TArray<FVector2D>     SecUVs[3];
    //TArray<FLinearColor>  SecColors[3];
    // Single section buffers
    TArray<FVector>        SecVerts;
    TArray<int32>          SecTris;
    TArray<FVector>        SecNormals;
    TArray<FVector2D>      SecUVs;
    TArray<FLinearColor>   SecColors;



    bool  bMeshInitialized = false;
    int32 LastBuiltSegmentCount = 0;
    int32 TailSectionIndex = -1;
    int32 TailVertStartIdx = -1;

    // throttling
    UPROPERTY(EditAnywhere, Category = "Perf")
    float RebuildCooldownSeconds = 0.05f; // max ~20Hz

    float RebuildCooldownTimer = 0.f;
    int32 PendingNewSegments = 0;

    static constexpr int32 FixedLightCount = 80; 

    int32 sectionIndex = 0;
    int32 MaxSegmentPerSection = 300;


};


