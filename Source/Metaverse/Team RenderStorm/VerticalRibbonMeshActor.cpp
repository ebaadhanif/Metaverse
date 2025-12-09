// VerticalRibbonMeshActor.cpp

#include "VerticalRibbonMeshActor.h" // fixed include name/case
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInterface.h"
#include "Engine/CollisionProfile.h"
#include "Kismet/KismetMathLibrary.h"
#include <Metaverse/Team Visioneers/DisplayManager.h>
#include "ModeManager.h"

// Smooth-ish opacity ramp down the trail
//static FORCEINLINE float OpacityRamp(int32 SliceIndex, int32 SegmentCount)
//{
//	if (SegmentCount <= 0) return 1.f;
//	const float T = static_cast<float>(SliceIndex) / static_cast<float>(SegmentCount);
//	float O = 1.f - 0.8f * FMath::Pow(2.f * T - 1.f, 2.f);
//	return FMath::Clamp(O, 0.2f, 1.f);
//}

AVerticalRibbonMeshActor::AVerticalRibbonMeshActor()
{
	PrimaryActorTick.bCanEverTick = false;

	RibbonMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("RibbonMesh"));
	SetRootComponent(RibbonMesh);

	// Stability / no-cull setup
	//RibbonMesh->SetMobility(EComponentMobility::Movable);
	//RibbonMesh->bUseAsyncCooking = true;
	//RibbonMesh->bNeverDistanceCull = true;
	//RibbonMesh->bAllowCullDistanceVolume = false;
	//RibbonMesh->bUseAttachParentBound = false;
	//RibbonMesh->SetBoundsScale(10000.0f);

	//RibbonMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//RibbonMesh->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	//RibbonMesh->SetVisibility(true);
	//RibbonMesh->SetCastShadow(false);
	//RibbonMesh->SetReceivesDecals(false);
	RibbonMesh->SetTranslucentSortPriority(10);
	RibbonMesh->SetCullDistance(20000000);
		
	// Default materials (replace with your paths or set in editor)
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MatFriendly(
		TEXT("Material'/Game/Materials/Trail/VerticalTrail.VerticalTrail'"));
	if (MatFriendly.Succeeded()) FriendlyMaterial = MatFriendly.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MatOpposing(
		TEXT("Material'/Game/Materials/Trail/VerticalTrailRed.VerticalTrailRed'"));
	if (MatOpposing.Succeeded()) OpposingMaterial = MatOpposing.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MatNeutral(
		TEXT("Material'/Game/Materials/Trail/VerticalTrailNeutral.VerticalTrailNeutral'"));
	if (MatNeutral.Succeeded()) NeutralMaterial = MatNeutral.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MatOthers(
		TEXT("Material'/Game/Materials/Trail/VerticalTrailOthers.VerticalTrailOthers'"));
	if (MatOthers.Succeeded()) OthersMaterial = MatOthers.Object;


	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MatFriendlyLod2(
		TEXT("Material'/Game/Materials/Trail/VerticalTrailLod2.VerticalTrailLod2'"));
	if (MatFriendlyLod2.Succeeded()) FriendlyMaterialLod2 = MatFriendlyLod2.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MatOpposingLod2(
		TEXT("Material'/Game/Materials/Trail/VerticalTrailRedLod2.VerticalTrailRedLod2'"));
	if (MatOpposingLod2.Succeeded()) OpposingMaterialLod2 = MatOpposingLod2.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MatNeutralLod2(
		TEXT("Material'/Game/Materials/Trail/VerticalTrailNeutralLod2.VerticalTrailNeutralLod2'"));
	if (MatNeutralLod2.Succeeded()) NeutralMaterialLod2 = MatNeutralLod2.Object;

	// Pre-allocate a bit
	SecVerts.Reserve(512);
	SecTris.Reserve(1024);
	SecNormals.Reserve(512);
	SecUVs.Reserve(512);
	SecColors.Reserve(512);

	sectionIndex = 0;
	MaxSegmentPerSection = 300;
}

void AVerticalRibbonMeshActor::BeginPlay()
{
	Super::BeginPlay();
	RibbonMesh->SetBoundsScale(1000.0f);

	CachedStripeIntervalCM = StripeIntervalCM;
	CachedVWidthScale = VWidthScale;
	if (AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::VerticalTrail30Sec).FeatureActive)
	{
		TrailMode = EVerticalRibbonTrailMode::Last30Seconds;
	}
	else if (AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::VerticalTrail1Min).FeatureActive) {
		TrailMode = EVerticalRibbonTrailMode::Last60Seconds;
	}
	else if (AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::VerticalTrailLifetime).FeatureActive) {
		TrailMode = EVerticalRibbonTrailMode::Lifetime;
	}
	else {
		TrailMode = EVerticalRibbonTrailMode::Lifetime;
	}
}

void AVerticalRibbonMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const FVector ActorPosition = GetActorLocation();
	const FVector CameraPosition = ADisplayManager::GetInstance()->CameraLocation;

	DistanceFromCamera = FVector::Dist(ActorPosition, CameraPosition);
}

void AVerticalRibbonMeshActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (!FMath::IsNearlyEqual(CachedStripeIntervalCM, StripeIntervalCM, 0.001f) ||
		!FMath::IsNearlyEqual(CachedVWidthScale, VWidthScale, 0.001f))
	{
		CachedStripeIntervalCM = StripeIntervalCM;
		CachedVWidthScale = VWidthScale;
		RebuildActiveTrail();
	}
}

void AVerticalRibbonMeshActor::setForceType(EForceType force)
{
	ForceType = force;
}

void AVerticalRibbonMeshActor::SetStripeInterval(float NewIntervalCM)
{
	StripeIntervalCM = FMath::Max(NewIntervalCM, 1.f);
	RebuildActiveTrail();
}

void AVerticalRibbonMeshActor::SetTrailMode(EVerticalRibbonTrailMode NewMode)
{
	TrailMode = NewMode;

	float CurrentTime =
		(LifetimeSegments.Num() > 0)
		? LifetimeSegments.Last().TimeStamp
		: GetWorld()->GetTimeSeconds();
	int32 NumSections = RibbonMesh->GetNumSections();


	UE_LOG(LogTemp, Warning, TEXT("Sections: %d"),
		NumSections);
	if (TrailMode == EVerticalRibbonTrailMode::Lifetime)
	{
		RebuildCompleteTrail(LifetimeSegments);
	}

	else {

		//CurrentSectionSegments.Empty();
		if (TrailMode == EVerticalRibbonTrailMode::Last30Seconds && Last30sSegments.Num() > 1) {
			RibbonMesh->ClearAllMeshSections();
			RebuildMeshFromTrail(Last30sSegments);
		}
		else if (TrailMode == EVerticalRibbonTrailMode::Last60Seconds && Last60sSegments.Num() > 1) {
			RibbonMesh->ClearAllMeshSections();
			RebuildMeshFromTrail(Last60sSegments);
		}
	}

	//Last30sSegments.Reset();
	//Last60sSegments.Reset();

	//if (LifetimeSegments.Num() > 0)
	//{
	//	Last30sSegments.Reserve(LifetimeSegments.Num());
	//	Last60sSegments.Reserve(LifetimeSegments.Num());

	//	for (const FVerticalRibbonSegment& Seg : LifetimeSegments)
	//	{
	//		const float Age = CurrentTime - Seg.TimeStamp;
	//		if (Age <= 60.f)
	//		{
	//			Last60sSegments.Add(Seg);
	//			if (Age <= 30.f) Last30sSegments.Add(Seg);
	//		}
	//	}
	//}

	// Force a rebuild (ignore cooldown for explicit mode change)
	//RibbonMesh->ClearAllMeshSections();
	//CurrentSectionSegments.Empty();
	RebuildCooldownTimer = 0.f;
	PendingNewSegments = 0;
	//RebuildActiveTrail();
}

void AVerticalRibbonMeshActor::RebuildActiveTrail()
{
	const TArray<FVerticalRibbonSegment>* Active = nullptr;

	switch (TrailMode)
	{
	case EVerticalRibbonTrailMode::Last30Seconds:
		if (Last30sSegments.Num() > 1)
		{
			RibbonMesh->ClearAllMeshSections();
			RebuildMeshFromTrail(Last30sSegments);

		}

		break;
	case EVerticalRibbonTrailMode::Last60Seconds:
		if (Last60sSegments.Num() > 1)
		{
			RibbonMesh->ClearAllMeshSections();
			RebuildMeshFromTrail(Last60sSegments);
		}

		break;
	case EVerticalRibbonTrailMode::Lifetime:
		if (CurrentSectionSegments.Num() > 1)
		{
			RebuildMeshFromTrail(CurrentSectionSegments);
		}

		break;
	default:
		break;
	}

}

void AVerticalRibbonMeshActor::RebuildMeshFromTrail(const TArray<FVerticalRibbonSegment>& Trail)
{
	const int32 SegmentCount = Trail.Num();
	if (SegmentCount < 2)
	{
		//RibbonMesh->ClearAllMeshSections();
		bMeshInitialized = false;
		LastBuiltSegmentCount = SegmentCount;
		TailVertStartIdx = -1;
		return;
	}
	const TArray<FVerticalRibbonSegment>* Active = nullptr;

	TArray<float> SliceU;
	SliceU.SetNumUninitialized(SegmentCount);

	auto SliceCenter = [&](const FVerticalRibbonSegment& S) -> FVector
		{
			return (S.Left + S.Right) * 0.5f;
		};

	SliceU[0] = 0.f;

	for (int32 i = 1; i < SegmentCount; ++i)
	{
		const FVector CPrev = SliceCenter(Trail[i - 1]);
		const FVector CCurr = SliceCenter(Trail[i]);
		const float   StepDist = (CCurr - CPrev).Size();
		SliceU[i] = SliceU[i - 1] + (StepDist / FMath::Max(StripeIntervalCM, 1.f)); 
	}

	SecVerts.Reset();
	SecTris.Reset();
	SecNormals.Reset();
	SecUVs.Reset();
	SecColors.Reset();

	SecVerts.Reserve(SegmentCount * 2);
	SecTris.Reserve(SegmentCount * 6);
	SecNormals.Reserve(SegmentCount * 2);
	SecUVs.Reserve(SegmentCount * 2);
	SecColors.Reserve(SegmentCount * 2);

	auto ShrinkSlice = [&](const FVector& L, const FVector& R) -> TPair<FVector, FVector>
		{
			const FVector C = (L + R) * 0.5f;
			const float S = FMath::Clamp(VWidthScale, 0.f, 1.f);
			return TPair<FVector, FVector>(
				FMath::Lerp(C, L, S), 
				FMath::Lerp(C, R, S)  
			);
		};

	for (int32 i = 0; i < SegmentCount; ++i)
	{
		const FVerticalRibbonSegment& Seg = Trail[i];

		const TPair<FVector, FVector> Shrunk = ShrinkSlice(Seg.Left, Seg.Right);
		const FVector Lp = Shrunk.Key;
		const FVector Rp = Shrunk.Value;

		const int32 StartIdx = SecVerts.Num();

		// verts
		SecVerts.Add(Lp);
		SecVerts.Add(Rp);

		const float Uraw = SliceU[i];
		SecUVs.Add(FVector2D(Uraw, 0.f)); // Left
		SecUVs.Add(FVector2D(Uraw, 1.f)); // Right

		//const float O = OpacityRamp(i, SegmentCount);
		const float T = static_cast<float>(i) / FMath::Max(1, SegmentCount);
		const FLinearColor C(T, 1, 0, 1);
		SecColors.Add(C);
		SecColors.Add(C);

		SecNormals.Add(FVector::UpVector);
		SecNormals.Add(FVector::UpVector);

		if (StartIdx >= 2)
		{
			SecTris.Append({
				StartIdx - 2, StartIdx - 1, StartIdx,
				StartIdx - 1, StartIdx + 1, StartIdx
				});
		}

		if (i == SegmentCount - 1)
		{
			TailVertStartIdx = StartIdx;
		}
	}

	//RibbonMesh->ClearAllMeshSections();
	
	RibbonMesh->CreateMeshSection_LinearColor(
		sectionIndex, SecVerts, SecTris, SecNormals, SecUVs, SecColors,
		/*Tangents*/{}, /*bCreateCollision*/ false, /*bCalcNormalTangent*/ true);
	UseMat = OthersMaterial;
	//UMaterialInterface* UseMat = ForceType == EForceType::FRIENDLY ? (ForceType == EForceType::OPPOSING ? (ForceType == EForceType::NEUTRAL ? FriendlyMaterial: OpposingMaterial) : NeutralMaterial ): OthersMaterial;
	if (ForceType == EForceType::FRIENDLY)
	{
		if (DistanceFromCamera < 2000000)
			UseMat = FriendlyMaterial;
		else
			UseMat = FriendlyMaterial;

	}
	if (ForceType == EForceType::OPPOSING)
	{
		if (DistanceFromCamera < 2000000)
			UseMat = OpposingMaterial;
		else
			UseMat = OpposingMaterial;
	}
	if (ForceType == EForceType::NEUTRAL)
	{
		if (DistanceFromCamera < 2000000)
			UseMat = NeutralMaterial;
		else
			UseMat = NeutralMaterial;
	}
	if (ForceType == EForceType::OTHERS)
	{
		UseMat = OthersMaterial;

	}

	if (UseMat)
	{
		RibbonMesh->SetMaterial(sectionIndex, UseMat);
	}
	bMeshInitialized = true;
	LastBuiltSegmentCount = SegmentCount;
}

void AVerticalRibbonMeshActor::RebuildCompleteTrail(const TArray<FVerticalRibbonSegment>& Trail)
{
	const int32 SegmentCount = Trail.Num();
	if (SegmentCount < 2)
	{
		//RibbonMesh->ClearAllMeshSections();
		bMeshInitialized = false;
		LastBuiltSegmentCount = SegmentCount;
		TailVertStartIdx = -1;
		return;
	}
	const TArray<FVerticalRibbonSegment>* Active = nullptr;



	auto SliceCenter = [&](const FVerticalRibbonSegment& S) -> FVector
		{
			return (S.Left + S.Right) * 0.5f;
		};



	const int32 numSections = FMath::CeilToInt((float)SegmentCount / MaxSegmentPerSection);
	int32 globalSectionIndex = 1;

	for (int32 sectionIdx = 0; sectionIdx < numSections; sectionIdx++)
	{
		SecVerts.Reset();
		SecTris.Reset();
		SecNormals.Reset();
		SecUVs.Reset();
		SecColors.Reset();

		SecVerts.Reserve(SegmentCount * 2);
		SecTris.Reserve(SegmentCount * 6);
		SecNormals.Reserve(SegmentCount * 2);
		SecUVs.Reserve(SegmentCount * 2);
		SecColors.Reserve(SegmentCount * 2);


		const int32 sectionStart = sectionIdx * MaxSegmentPerSection;
		const int32 sectionEnd = FMath::Min((sectionIdx + 1) * MaxSegmentPerSection, SegmentCount);
		const int32 SectionSegmentCount = sectionEnd - sectionStart;

		TArray<float> SliceU;
		SliceU.SetNumUninitialized(SegmentCount);
		SliceU[0] = 0.f;


		for (int32 i = 1; i < SectionSegmentCount; ++i)
		{
			const FVector CPrev = SliceCenter(Trail[sectionStart + i - 1]);
			const FVector CCurr = SliceCenter(Trail[sectionStart + i]);
			const float   StepDist = (CCurr - CPrev).Size();
			SliceU[i] = SliceU[i - 1] + (StepDist / FMath::Max(StripeIntervalCM, 1.f));
		}

		auto ShrinkSlice = [&](const FVector& L, const FVector& R) -> TPair<FVector, FVector>
			{
				const FVector C = (L + R) * 0.5f;
				const float S = FMath::Clamp(VWidthScale, 0.f, 1.f);
				return TPair<FVector, FVector>(
					FMath::Lerp(C, L, S),
					FMath::Lerp(C, R, S)
				);
			};

		for (int32 i = 0; i < SectionSegmentCount; ++i)
		{
			const FVerticalRibbonSegment& Seg = Trail[sectionStart + i];

			const TPair<FVector, FVector> Shrunk = ShrinkSlice(Seg.Left, Seg.Right);
			const FVector Lp = Shrunk.Key;
			const FVector Rp = Shrunk.Value;

			const int32 StartIdx = SecVerts.Num();

			// verts
			SecVerts.Add(Lp);
			SecVerts.Add(Rp);

			const float Uraw = SliceU[i];
			SecUVs.Add(FVector2D(Uraw, 0.f)); // Left
			SecUVs.Add(FVector2D(Uraw, 1.f)); // Right

			//const float O = OpacityRamp(i, SegmentCount);
			const float T = static_cast<float>(i) / FMath::Max(1, SegmentCount);
			const FLinearColor C(T, 1, 0, 1);
			SecColors.Add(C);
			SecColors.Add(C);

			SecNormals.Add(FVector::UpVector);
			SecNormals.Add(FVector::UpVector);

			if (StartIdx >= 2)
			{
				SecTris.Append({
					StartIdx - 2, StartIdx - 1, StartIdx,
					StartIdx - 1, StartIdx + 1, StartIdx
					});
			}

			if (i == SectionSegmentCount - 1)
			{
				TailVertStartIdx = StartIdx;
			}

			globalSectionIndex++;
		}


		//RibbonMesh->ClearAllMeshSections();

		RibbonMesh->CreateMeshSection_LinearColor(
			sectionIdx, SecVerts, SecTris, SecNormals, SecUVs, SecColors,
			/*Tangents*/{}, /*bCreateCollision*/ false, /*bCalcNormalTangent*/ true);
		UseMat = OthersMaterial;
		//UMaterialInterface* UseMat = ForceType == EForceType::FRIENDLY ? (ForceType == EForceType::OPPOSING ? (ForceType == EForceType::NEUTRAL ? FriendlyMaterial: OpposingMaterial) : NeutralMaterial ): OthersMaterial;
		if (ForceType == EForceType::FRIENDLY)
		{
			if (DistanceFromCamera < 2000000)
				UseMat = FriendlyMaterial;
			else
				UseMat = FriendlyMaterial;

		}
		if (ForceType == EForceType::OPPOSING)
		{
			if (DistanceFromCamera < 2000000)
				UseMat = OpposingMaterial;
			else
				UseMat = OpposingMaterial;
		}
		if (ForceType == EForceType::NEUTRAL)
		{
			if (DistanceFromCamera < 2000000)
				UseMat = NeutralMaterial;
			else
				UseMat = NeutralMaterial;
		}
		if (ForceType == EForceType::OTHERS)
		{
			UseMat = OthersMaterial;

		}

		if (UseMat)
		{
			RibbonMesh->SetMaterial(sectionIdx, UseMat);
		}
		bMeshInitialized = true;
		LastBuiltSegmentCount = SegmentCount;

	}
	sectionIndex = numSections - 1;
}

void AVerticalRibbonMeshActor::UpdateTailInPlace()
{
	if (!bMeshInitialized || TailVertStartIdx < 0) return;

	RibbonMesh->UpdateMeshSection_LinearColor(
		sectionIndex, SecVerts, SecNormals, SecUVs, SecColors, /*Tangents*/{}
	);
}


void AVerticalRibbonMeshActor::AddRibbonSegment(const FVector& Left, const FVector& Right, float Distance)
{
	DistanceFromCamera = Distance;
	if (LifetimeSegments.Num() == 0)
	{
		FVerticalRibbonSegment Seed;
		Seed.Left = Left;
		Seed.Right = Right;
		Seed.TimeStamp = GetWorld()->GetTimeSeconds();

		LifetimeSegments.Add(Seed);
		Last30sSegments.Add(Seed);
		Last60sSegments.Add(Seed);
		CurrentSectionSegments.Add(Seed);

		bMeshInitialized = false;
		LastBuiltSegmentCount = 0;
		TailVertStartIdx = -1;


		return;
	}

	FVerticalRibbonSegment NewSegment;
	NewSegment.Left = Left;
	NewSegment.Right = Right;
	NewSegment.TimeStamp = GetWorld()->GetTimeSeconds();
	LifetimeSegments.Add(NewSegment);

	Last30sSegments.Add(NewSegment);
	Last60sSegments.Add(NewSegment);
	CurrentSectionSegments.Add(NewSegment);
	++PendingNewSegments;

	const float currentTime = NewSegment.TimeStamp;

	//Last30sSegments.Reset();
	//Last60sSegments.Reset();

	//for (const FVerticalRibbonSegment& Seg : LifetimeSegments)
	//		{
	//			const float Age = currentTime - Seg.TimeStamp;
	//			if (Age <= 60.f)
	//			{
	//				Last60sSegments.Add(Seg);
	//				if (Age <= 30.f) Last30sSegments.Add(Seg);
	//			}
	//		}


	if (currentTime - Last30sSegments[0].TimeStamp > 30)
		Last30sSegments.RemoveAt(0);


	if (currentTime - Last60sSegments[0].TimeStamp > 60)
		Last60sSegments.RemoveAt(0);


	// throttle full rebuilds
	RebuildCooldownTimer += GetWorld()->GetDeltaSeconds();
	const bool bShouldRebuild =
		(RebuildCooldownTimer >= RebuildCooldownSeconds) || (PendingNewSegments >= 4);

	if (!bMeshInitialized || bShouldRebuild)
	{

		if (CurrentSectionSegments.Num() > MaxSegmentPerSection)
		{
			sectionIndex++;
			FVerticalRibbonSegment temp = CurrentSectionSegments[CurrentSectionSegments.Num() - 1];
			FVerticalRibbonSegment temp2 = CurrentSectionSegments[CurrentSectionSegments.Num() - 2];
			CurrentSectionSegments.Empty();
			CurrentSectionSegments.Add(temp);
			CurrentSectionSegments.Add(temp);
			CurrentSectionSegments.Add(NewSegment);
			int32 NumSections = RibbonMesh->GetNumSections();
			UE_LOG(LogTemp, Warning, TEXT("Sections: %d"),
				NumSections);
		}
		RebuildActiveTrail();
		RebuildCooldownTimer = 0.f;
		PendingNewSegments = 0;
		return;
	}

}

void AVerticalRibbonMeshActor::SetTrailVisibility(bool bVisible)
{
	if (RibbonMesh)
	{
		RibbonMesh->SetVisibility(bVisible, true);
		RibbonMesh->SetHiddenInGame(!bVisible);
	}
}


void AVerticalRibbonMeshActor::stretchPreviousPoints(const FVector& CLeft, const FVector& CRight, float Distance)
{
	DistanceFromCamera = Distance;
	if (LifetimeSegments.Num() == 0) return;
	LifetimeSegments.Last().Left = CLeft;
	LifetimeSegments.Last().Right = CRight;

	Last30sSegments.Last().Left = CLeft;
	Last30sSegments.Last().Right = CRight;

	Last60sSegments.Last().Left = CLeft;
	Last60sSegments.Last().Right = CRight;

	RebuildActiveTrail();
}
