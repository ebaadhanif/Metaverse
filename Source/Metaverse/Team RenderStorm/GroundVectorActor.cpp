// GroundVectorActor.cpp
#include "GroundVectorActor.h"
#include "NiagaraSystem.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include <Kismet/KismetMathLibrary.h>

AGroundVectorActor::AGroundVectorActor()
{
	// Set Niagara beam asset
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> BeamSysAsset(
		TEXT("/Game/VFX/LockLine/GroundVector.GroundVector"));
	if (BeamSysAsset.Succeeded())
	{
		BeamSystem = BeamSysAsset.Object; // base will apply
	}

	// Default ring visuals
	static ConstructorHelpers::FObjectFinder<UStaticMesh> RingMeshAsset(TEXT("/Game/Materials/LockLine/Ring.Ring"));
	if (RingMeshAsset.Succeeded())
	{
		RingMesh = RingMeshAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> RingMat(TEXT("Material'/Game/Materials/LockLine/Ring1.Ring1'"));
	if (RingMat.Succeeded())
	{
		RingMaterial = RingMat.Object;
	}

	//RingISM->SetCullDistance(20000000);
}

void AGroundVectorActor::BeginPlay()
{
	Super::BeginPlay();
	EnsureRingISM();

	if (!HeightRing)
	{
		HeightRing = NewObject<UStaticMeshComponent>(this, TEXT("HeightRing"));
		HeightRing->SetUsingAbsoluteLocation(true);
		HeightRing->SetUsingAbsoluteRotation(true);
		HeightRing->SetUsingAbsoluteScale(true);
		HeightRing->SetWorldTransform(FTransform::Identity);
		HeightRing->SetMobility(EComponentMobility::Movable);
		HeightRing->SetCastShadow(false);
		HeightRing->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		HeightRing->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
		HeightRing->RegisterComponent();
	}

	if (RingMesh && HeightRing->GetStaticMesh() != RingMesh) { 
		HeightRing->SetStaticMesh(RingMesh);
	}
	if (RingMaterial) {
		HeightRing->SetMaterial(0, RingMaterial);
	}

	HeightRing->SetWorldLocation(RawStart);
}

void AGroundVectorActor::OnAfterBeamUpdated(float DeltaTime, const FVector& Start, const FVector& End, float radius, float thickness)
{
	UpdateRings(Start, End, radius, thickness);
}

void AGroundVectorActor::EnsureRingISM()
{
	if (!RingISM)
	{
		RingISM = NewObject<UInstancedStaticMeshComponent>(this, TEXT("LockBeam_RingsISM"));
		RingISM->SetUsingAbsoluteLocation(true);
		RingISM->SetUsingAbsoluteRotation(true);
		RingISM->SetUsingAbsoluteScale(true);
		RingISM->SetWorldTransform(FTransform::Identity);
		RingISM->SetMobility(EComponentMobility::Movable);
		RingISM->SetCastShadow(false);
		RingISM->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		RingISM->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		RingISM->RegisterComponent();
	}

	if (RingMesh && RingISM->GetStaticMesh() != RingMesh) { RingISM->SetStaticMesh(RingMesh); }
	if (RingMaterial && RingISM->GetMaterial(0) != RingMaterial) { RingISM->SetMaterial(0, RingMaterial); }
}

void AGroundVectorActor::UpdateRings(const FVector& Start, const FVector& End, float radius, float thickness)
{
	EnsureRingISM();
	if (!RingISM || !RingISM->IsRegistered()) return;

	if (RingSpacing <= KINDA_SMALL_NUMBER || !FMath::IsFinite(RingSpacing))
	{
		RingISM->ClearInstances();
		return;
	}

	const FVector Delta = End - Start;
	const float DistCm = Delta.Size();
	if (DistCm <= KINDA_SMALL_NUMBER)
	{
		RingISM->ClearInstances();
		return;
	}

	const FVector Dir = Delta / DistCm;
	const int32 Needed = FMath::Clamp(FMath::FloorToInt(DistCm / RingSpacing), 0, MaxRings);

	TArray<FTransform> Xforms;
	Xforms.Reserve(Needed);

	const FRotator BaseRot = UKismetMathLibrary::MakeRotFromZ(Dir);
	const FVector PlateScale(
		FMath::Max((2.f * radius) / 100.f, 0.01f),
		FMath::Max((2.f * radius) / 100.f, 0.01f),
		FMath::Max(thickness / 100.f, 0.01f)
	);

	for (int32 i = 1; i <= Needed; ++i)
	{
		const FVector Pos = Start + Dir * (i * RingSpacing);
		Xforms.Emplace(BaseRot, Pos, PlateScale);
	}

	const int32 Existing = RingISM->GetInstanceCount();
	if (Existing == Xforms.Num() && Existing > 0)
	{
		RingISM->BatchUpdateInstancesTransforms(0, Xforms, /*bWorldSpace*/true, /*bMarkRenderStateDirty*/true, /*bTeleport*/true);
	}
	else
	{
		RingISM->ClearInstances();
		RingISM->PreAllocateInstancesMemory(Xforms.Num());
		RingISM->AddInstances(Xforms, /*bReturnIndices*/ false, /*bWorldSpace*/ true, /*bMarkRenderStateDirty*/ true);
	}



}

void AGroundVectorActor::UpdateHeightRing(const FVector& Start, const FVector& End, float radius, float thickness) {
	if (HeightRing)
	{
		const FVector Delta = End - Start;
		const float DistCm = Delta.Size();

		const FVector Dir = Delta / DistCm;
		const FVector Loc = Start + Dir * (100);
		const FRotator BaseRot = UKismetMathLibrary::MakeRotFromZ(Dir);
		const FVector PlateScale(
			FMath::Max((2.f * radius) / 100.f, 0.01f),
			FMath::Max((2.f * radius) / 100.f, 0.01f),
			FMath::Max(thickness / 100.f, 0.01f)
		);
		const FTransform StartTransform(BaseRot, Loc, PlateScale);
		HeightRing->SetWorldTransform(StartTransform, false, nullptr, ETeleportType::TeleportPhysics);

		//HeightRing->SetHiddenInGame(false);
		//HeightRing->SetVisibility(true, true);
	}
}

void AGroundVectorActor::ToggleHeightRingVisibility(bool bIsVisible) {
	HeightRing->SetHiddenInGame(!bIsVisible);
	HeightRing->SetVisibility(bIsVisible, bIsVisible);
	isHeightRingVisible = bIsVisible;
}

void AGroundVectorActor::clearRings()
{
	RingISM->ClearInstances();
}
