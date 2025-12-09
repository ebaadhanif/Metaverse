#include "RibbonMeshActor.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInterface.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "AppConstEnumStruct.h"
#include <Metaverse/Team Visioneers/DisplayManager.h>
#include "ModeManager.h"

ARibbonMeshActor::ARibbonMeshActor()
{
    PrimaryActorTick.bCanEverTick = false;

    RibbonMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("RibbonMesh"));
    RootComponent = RibbonMesh;
    RibbonMesh->bUseAsyncCooking = true;
    RibbonMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    RibbonMesh->SetVisibility(true);
    RibbonMesh->SetWorldScale3D(FVector(1.0f));

    RibbonMesh->SetCullDistance(20000000);

    // Materials
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> StartMat(TEXT("Material'/Game/Materials/Trail/StartMaterial.StartMaterial'"));
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> MiddleMat(TEXT("Material'/Game/Materials/Trail/MiddleMaterial.MiddleMaterial'"));
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> EndMat(TEXT("Material'/Game/Materials/Trail/EndMaterial.EndMaterial'"));
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> StartRedMat(TEXT("Material'/Game/Materials/Trail/StartMaterial_Red.StartMaterial_Red'"));
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> MiddleRedMat(TEXT("Material'/Game/Materials/Trail/MiddleMaterial_Red.MiddleMaterial_Red'"));
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> EndRedMat(TEXT("Material'/Game/Materials/Trail/EndMaterial_Red.EndMaterial_Red'"));
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> DottedMat(TEXT("Material'/Game/Materials/Trail/BorderMaterial/BorderMaterial.BorderMaterial'"));
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> NeutralMat(TEXT("Material'/Game/Materials/Trail/Neutralmaterial.Neutralmaterial'"));
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> NeutralStartMat(TEXT("Material'/Game/Materials/Trail/NeutralmaterialStart.NeutralmaterialStart'"));
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> NeutralEndMat(TEXT("Material'/Game/Materials/Trail/NeutralmaterialEnd.NeutralmaterialEnd'")); 

    static ConstructorHelpers::FObjectFinder<UMaterialInterface> OthersMat(TEXT("Material'/Game/Materials/Trail/OthersMaterial.OthersMaterial'"));

    if (StartMat.Succeeded())     StartMaterial = StartMat.Object;
    if (MiddleMat.Succeeded())    MiddleMaterial = MiddleMat.Object;
    if (EndMat.Succeeded())       EndMaterial = EndMat.Object;
    if (StartRedMat.Succeeded())  StartRedMaterial = StartRedMat.Object;
    if (MiddleRedMat.Succeeded()) MiddleRedMaterial = MiddleRedMat.Object;
    if (EndRedMat.Succeeded())    EndRedMaterial = EndRedMat.Object;
    if (DottedMat.Succeeded())    DottedMaterial = DottedMat.Object;
    if (NeutralMat.Succeeded())    NeutralMaterial = NeutralMat.Object;
    if (OthersMat.Succeeded())    OthersMaterial = OthersMat.Object;
    if (NeutralStartMat.Succeeded())    NeutralStartMaterial = NeutralStartMat.Object;
    if (NeutralEndMat.Succeeded())    NeutralEndMaterial = NeutralEndMat.Object;
    

    // Initialize arrays minimally
    for (int s = 0; s < 3; ++s)
    {
        SecVerts[s].Reserve(256);
        SecTris[s].Reserve(384);
        SecNormals[s].Reserve(256);
        SecUVs[s].Reserve(256);
        SecColors[s].Reserve(256);
    }
}

void ARibbonMeshActor::BeginPlay()
{
    Super::BeginPlay();
    RibbonMesh->SetBoundsScale(100.0f);

    if (AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::HorizontalTrail30Sec).FeatureActive)
    {
        TrailMode = ERibbonTrailMode::Last30Seconds;
    }
    else if (AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::HorizontalTrail1Min).FeatureActive) {
        TrailMode = ERibbonTrailMode::Last60Seconds;
    }
    else if (AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::HorizontalTrailLifetime).FeatureActive) {
        TrailMode = ERibbonTrailMode::Lifetime;
    }
    else {
        TrailMode = ERibbonTrailMode::Lifetime;
    }
}

void ARibbonMeshActor::setForceType(EForceType force)
{
    ForceType = force;
}

void ARibbonMeshActor::SetTrailMode(ERibbonTrailMode NewMode)
{
    TrailMode = NewMode;

    // Choose reference time
    const float CurrentTime =
        (LifetimeSegments.Num() > 0)
        ? LifetimeSegments.Last().TimeStamp
        : GetWorld()->GetTimeSeconds();

    // Rebuild caches once
    //Last30sSegments.Reset();
    //Last60sSegments.Reset();

    //if (LifetimeSegments.Num() > 0)
    //{
    //    Last30sSegments.Reserve(LifetimeSegments.Num());
    //    Last60sSegments.Reserve(LifetimeSegments.Num());

    //    for (const FRibbonSegment& Seg : LifetimeSegments)
    //    {
    //        const float Age = CurrentTime - Seg.TimeStamp;
    //        if (Age <= 60.f)
    //        {
    //            Last60sSegments.Add(Seg);
    //            if (Age <= 30.f) Last30sSegments.Add(Seg);
    //        }
    //    }
    //}

    // Force a rebuild (ignore cooldown for explicit mode change)
    RebuildCooldownTimer = 0.f;
    PendingNewSegments = 0;
    RebuildActiveTrail();
}

void ARibbonMeshActor::SetTrailVisibility(bool bVisible)
{
    if (RibbonMesh)
    {
        RibbonMesh->SetVisibility(bVisible, true);
        RibbonMesh->SetHiddenInGame(!bVisible);
    }
}

static FORCEINLINE float OpacityRamp(int32 VertexCounter, int32 SegmentCount)
{
    if (SegmentCount <= 0) return 1.f;
    const float T = static_cast<float>(VertexCounter) / static_cast<float>(SegmentCount);
    float O = 1.f - 0.8f * FMath::Pow(2.f * T - 1.f, 2.f);
    return FMath::Clamp(O, 0.2f, 1.f);
}

void ARibbonMeshActor::ComputeSectionSplit(int32 SegmentCount, int32& OutMiddleStart, int32& OutMiddleEnd) const
{
    OutMiddleStart = FixedLightCount;
    OutMiddleEnd = SegmentCount - FixedLightCount;

    if (SegmentCount < (FixedLightCount * 2))
    {
        OutMiddleStart = SegmentCount / 2;
        OutMiddleEnd = SegmentCount / 2;
    }
}

void ARibbonMeshActor::RebuildActiveTrail()
{
    const TArray<FRibbonSegment>* Active = nullptr;
    switch (TrailMode)
    {
    case ERibbonTrailMode::Last30Seconds: Active = &Last30sSegments;  break;
    case ERibbonTrailMode::Last60Seconds: Active = &Last60sSegments;  break;
    case ERibbonTrailMode::Lifetime:      Active = &LifetimeSegments; break;
    }
    if (!Active) return;
    RebuildMeshFromTrail(*Active);
}

void ARibbonMeshActor::RebuildMeshFromTrail(const TArray<FRibbonSegment>& Trail)
{
    const int32 SegmentCount = Trail.Num();
    if (SegmentCount < 2)
    {
        RibbonMesh->ClearAllMeshSections();
        bMeshInitialized = false;
        LastBuiltSegmentCount = SegmentCount;
        TailSectionIndex = -1;
        TailVertStartIdx = -1;
        return;
    }

    TArray<float> SliceU;
    SliceU.SetNumUninitialized(SegmentCount);

    auto SliceCenter = [&](const FRibbonSegment& S) -> FVector
        {
            return (S.Left + S.Right) * 0.5f;
        };

    SliceU[0] = 0.f;
    for (int32 i = 1; i < SegmentCount; ++i)
    {
        const FVector CPrev = SliceCenter(Trail[i - 1]);
        const FVector CCurr = SliceCenter(Trail[i]);
        const float   StepDist = (CCurr - CPrev).Size();
        SliceU[i] = SliceU[i - 1] + (StepDist / FMath::Max(10000, 1.f));
    }
    // Reset section buffers
    for (int s = 0; s < 3; ++s)
    {
        SecVerts[s].Reset();
        SecTris[s].Reset();
        SecNormals[s].Reset();
        SecUVs[s].Reset();
        SecColors[s].Reset();

        SecVerts[s].Reserve(SegmentCount * 2);
        SecTris[s].Reserve(SegmentCount * 6);
        SecNormals[s].Reserve(SegmentCount * 2);
        SecUVs[s].Reserve(SegmentCount * 2);
        SecColors[s].Reserve(SegmentCount * 2);
    }

    int32 MiddleStart = 0, MiddleEnd = 0;
    ComputeSectionSplit(SegmentCount, MiddleStart, MiddleEnd);

    auto SeedBoundary = [&](int32 SectionIndex, int32 IndexInTrail)
        {
            if (IndexInTrail < 0 || IndexInTrail >= SegmentCount) return;
            const FRibbonSegment& S = Trail[IndexInTrail];

            SecVerts[SectionIndex].Add(S.Left);
            SecVerts[SectionIndex].Add(S.Right);


            SecUVs[SectionIndex].Add(FVector2D(0, 1));
            SecUVs[SectionIndex].Add(FVector2D(0, 1));
            //const float Uraw = SliceU[IndexInTrail];
            //SecUVs[SectionIndex].Add(FVector2D(0, Uraw)); // Left
            //SecUVs[SectionIndex].Add(FVector2D(1, Uraw)); // Right

            const float O = OpacityRamp(SecVerts[SectionIndex].Num() / 2, SegmentCount);
            const float T = static_cast<float>(SecVerts[SectionIndex].Num() / 2) / FMath::Max(1, SegmentCount);
            const FLinearColor C(T, O, 0, O);
            SecColors[SectionIndex].Add(C);
            SecColors[SectionIndex].Add(C);
            SecNormals[SectionIndex].Add(FVector::UpVector);
            SecNormals[SectionIndex].Add(FVector::UpVector);
        };

    if (MiddleStart > 0 && SegmentCount > MiddleStart) SeedBoundary(1, MiddleStart - 1);
    if (MiddleEnd > 0 && SegmentCount > MiddleEnd)   SeedBoundary(2, MiddleEnd - 1);

    auto AddSlice = [&](int32 SectionIndex, const FRibbonSegment& Seg, int32 TrailIdx)
        {
            const int32 StartIdx = SecVerts[SectionIndex].Num();

            SecVerts[SectionIndex].Add(Seg.Left);
            SecVerts[SectionIndex].Add(Seg.Right);

            float VCoord = 1.f;
            if (SectionIndex == 0)
            {
                VCoord = FMath::Clamp(static_cast<float>(TrailIdx) / static_cast<float>(FixedLightCount), 0.f, 1.f);
            }
            else if (SectionIndex == 2)
            {
                const int32 EndSectionStart = SegmentCount - FixedLightCount;
                const int32 RelativeIndex = TrailIdx - EndSectionStart;
                VCoord = FMath::Clamp(static_cast<float>(FixedLightCount - RelativeIndex - 1) / static_cast<float>(FixedLightCount), 0.f, 1.f);
            }
            SecUVs[SectionIndex].Add(FVector2D(0, VCoord));
            SecUVs[SectionIndex].Add(FVector2D(1, VCoord));

            //const float Uraw = SliceU[TrailIdx];
            //SecUVs[SectionIndex].Add(FVector2D(0, Uraw)); // Left
            //SecUVs[SectionIndex].Add(FVector2D(1, Uraw)); // Right

            const float O = OpacityRamp(SecVerts[SectionIndex].Num() / 2, SegmentCount);
            const float T = static_cast<float>(SecVerts[SectionIndex].Num() / 2) / FMath::Max(1, SegmentCount);
            const FLinearColor C(T, O, 0, O);
            SecColors[SectionIndex].Add(C);
            SecColors[SectionIndex].Add(C);

            SecNormals[SectionIndex].Add(FVector::UpVector);
            SecNormals[SectionIndex].Add(FVector::UpVector);

            if (StartIdx >= 2)
            {
                SecTris[SectionIndex].Append({
                    StartIdx - 2, StartIdx - 1, StartIdx,
                    StartIdx - 1, StartIdx + 1, StartIdx
                    });
            }
        };

    // Build all
    for (int32 i = 0; i < SegmentCount; ++i)
    {
        const int32 Sec = (i < MiddleStart) ? 0 : (i >= MiddleEnd ? 2 : 1);
        AddSlice(Sec, Trail[i], i);

        // Track tail’s section + starting vertex index (for fast stretch updates)
        if (i == SegmentCount - 1)
        {
            TailSectionIndex = Sec;
            TailVertStartIdx = SecVerts[Sec].Num() - 2; // pair start
        }
    }

    // Push to mesh
    RibbonMesh->ClearAllMeshSections();
    for (int s = 0; s < 3; ++s)
    {
        if (SecVerts[s].Num() > 0)
        {
            RibbonMesh->CreateMeshSection_LinearColor(
                s, SecVerts[s], SecTris[s], SecNormals[s], SecUVs[s], SecColors[s],
                /*Tangents*/{}, /*bCreateCollision*/ false, /*bCalcNormalTangent*/ true);
        }
    }

    // Materials
    if (ForceType == EForceType::FRIENDLY)
    {
        if (StartMaterial)  RibbonMesh->SetMaterial(0, StartMaterial);
        if (MiddleMaterial) RibbonMesh->SetMaterial(1, MiddleMaterial);
        if (EndMaterial)    RibbonMesh->SetMaterial(2, EndMaterial);
    }
    else if (ForceType == EForceType::OPPOSING)
    {
        if (StartRedMaterial)  RibbonMesh->SetMaterial(0, StartRedMaterial);
        if (MiddleRedMaterial) RibbonMesh->SetMaterial(1, MiddleRedMaterial);
        if (EndRedMaterial)    RibbonMesh->SetMaterial(2, EndRedMaterial);
    }
    else if(ForceType == EForceType::OTHERS)
    {
        if (OthersMaterial)  RibbonMesh->SetMaterial(0, OthersMaterial);
        if (OthersMaterial) RibbonMesh->SetMaterial(1, OthersMaterial);
        if (OthersMaterial)    RibbonMesh->SetMaterial(2, OthersMaterial);
    }
    else {
        if (NeutralStartMaterial)  RibbonMesh->SetMaterial(0, NeutralStartMaterial);
        if (NeutralMaterial) RibbonMesh->SetMaterial(1, NeutralMaterial);
        if (NeutralEndMaterial)    RibbonMesh->SetMaterial(2, NeutralEndMaterial);
    }

    bMeshInitialized = true;
    LastBuiltSegmentCount = SegmentCount;
}

void ARibbonMeshActor::UpdateTailInPlace()
{
    if (!bMeshInitialized || TailSectionIndex < 0 || TailVertStartIdx < 0) return;

    // We only touch the last two verts (pair) in the tail section
    // NOTE: SecNormals/UVs/Colors don’t change for a stretch
    RibbonMesh->UpdateMeshSection_LinearColor(
        TailSectionIndex,
        SecVerts[TailSectionIndex],
        SecNormals[TailSectionIndex],
        SecUVs[TailSectionIndex],
        SecColors[TailSectionIndex],
        /*Tangents*/{}
    );
}

void ARibbonMeshActor::stretchPreviousPoints(const FVector& CLeft, const FVector& CRight)
{
    // Update last in Lifetime (source of truth)
    if (LifetimeSegments.Num() == 0) return;
    LifetimeSegments.Last().Left = CLeft;
    LifetimeSegments.Last().Right = CRight;

    // If we have a mesh, try a cheap in-place tail update
    if (bMeshInitialized && TailSectionIndex >= 0 && TailVertStartIdx >= 0)
    {
        // Guard against array races
        if (SecVerts[TailSectionIndex].IsValidIndex(TailVertStartIdx) &&
            SecVerts[TailSectionIndex].IsValidIndex(TailVertStartIdx + 1))
        {
            SecVerts[TailSectionIndex][TailVertStartIdx] = CLeft;
            SecVerts[TailSectionIndex][TailVertStartIdx + 1] = CRight;
            UpdateTailInPlace();
            return;
        }
    }

    // Fallback (rare): full rebuild if structure not initialized yet
    RebuildActiveTrail();
}

void ARibbonMeshActor::AddRibbonSegment(const FVector& Left, const FVector& Right)
{
    // First call just seeds
    if (LifetimeSegments.Num() == 0)
    {
        FRibbonSegment Seed; Seed.Left = Left; Seed.Right = Right; Seed.TimeStamp = GetWorld()->GetTimeSeconds();
        LifetimeSegments.Add(Seed);
        Last30sSegments.Add(Seed);
        Last60sSegments.Add(Seed);
        // Nothing to draw yet (need at least 2)
        bMeshInitialized = false;
        LastBuiltSegmentCount = 0;
        TailSectionIndex = -1; TailVertStartIdx = -1;
        return;
    }

    FRibbonSegment NewSeg;
    NewSeg.Left = Left;
    NewSeg.Right = Right;
    NewSeg.TimeStamp = GetWorld()->GetTimeSeconds();
    LifetimeSegments.Add(NewSeg);
    Last30sSegments.Add(NewSeg);
    Last60sSegments.Add(NewSeg);

    ++PendingNewSegments;


    const float currentTime = NewSeg.TimeStamp;
    for (int i = 0; i < Last30sSegments.Num(); i++)
    {
        if (currentTime - Last30sSegments[i].TimeStamp > 30)
            Last30sSegments.RemoveAt(i);
        else
            break;
    }

    for (int i = 0; i < Last60sSegments.Num(); i++)
    {
        if (currentTime - Last60sSegments[i].TimeStamp > 60)
            Last60sSegments.RemoveAt(i);
        else
            break;
    }


    //Last30sSegments.Reset();
    //Last60sSegments.Reset();

    //for (const FRibbonSegment& Seg : LifetimeSegments)
    //{
    //    const float Age = currentTime - Seg.TimeStamp;
    //    if (Age <= 60.f)
    //    {
    //        Last60sSegments.Add(Seg);
    //        if (Age <= 30.f) Last30sSegments.Add(Seg);
    //    }
    //}

    // Throttle full rebuilds
    RebuildCooldownTimer += GetWorld()->GetDeltaSeconds();
    const bool bShouldRebuild =
        (RebuildCooldownTimer >= RebuildCooldownSeconds) || (PendingNewSegments >= 4);

    if (!bMeshInitialized || bShouldRebuild)
    {
        RebuildActiveTrail();
        RebuildCooldownTimer = 0.f;
        PendingNewSegments = 0;
        return;
    }

    // If we decide not to full rebuild yet, we can still stretch the new tail
    // by setting Tail refs appropriately and doing an in-place update.
    // But since a *new* segment adds triangles, we need a rebuild soon anyway,
    // so we simply wait for the next throttled rebuild.
}

float ARibbonMeshActor::ComputeSegmentAngle(const FVector& A1, const FVector& A2, const FVector& B1, const FVector& B2)
{
    const FVector Dir1 = (A2 - A1).GetSafeNormal();
    const FVector Dir2 = (B2 - B1).GetSafeNormal();
    const float Dot = FVector::DotProduct(Dir1, Dir2);
    return FMath::Acos(FMath::Clamp(Dot, -1.f, 1.f)) * (180.0f / PI);
}
