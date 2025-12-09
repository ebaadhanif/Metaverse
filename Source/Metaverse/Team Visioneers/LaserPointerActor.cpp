#include "LaserPointerActor.h"

ALaserPointerActor::ALaserPointerActor()
{
	PrimaryActorTick.bCanEverTick = true;

	BeamMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BeamMesh"));
	RootComponent = BeamMesh;

	BeamMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BeamMesh->SetCastShadow(false);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderMesh(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	if (CylinderMesh.Succeeded()) {
		BeamMesh->SetStaticMesh(CylinderMesh.Object);
	}

	UMaterialInterface* BaseMat = LoadObject<UMaterialInterface> (nullptr, TEXT("/Game/Materials/M_Beam.M_Beam"));
	if (BaseMat) {
		UMaterialInstanceDynamic* DyeMaterial = UMaterialInstanceDynamic::Create(BaseMat, this);
		BeamMesh->SetMaterial(0, BaseMat);

		DyeMaterial->SetVectorParameterValue("BeamColor" , FVector(0.0f,1.0f,1.0f));
	}

	MeshHalfHeight = 50.0;
	MeshRadius = 50.0f;
	TargetStart = TargetEnd = CurrentStart = CurrentEnd = FVector::ZeroVector;

}

void ALaserPointerActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (BeamMesh && BeamMesh->GetStaticMesh()) {

		const FBoxSphereBounds Bounds = BeamMesh->GetStaticMesh()->GetBounds();
		MeshHalfHeight = Bounds.BoxExtent.Z;
		MeshRadius = Bounds.BoxExtent.X;
		if (MeshHalfHeight <= KINDA_SMALL_NUMBER) MeshHalfHeight = 50.0f;
		if (MeshRadius <= KINDA_SMALL_NUMBER) MeshRadius = 50.0f;

	}

	CurrentStart = GetActorLocation();
	CurrentEnd = CurrentStart + GetActorForwardVector() * 100.f;
	TargetStart = CurrentStart;
	TargetEnd = CurrentEnd;
}

void ALaserPointerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bSmooth) {
		CurrentStart = FMath::VInterpTo(CurrentStart, TargetStart, DeltaTime, PositionInterpSpeed);
		CurrentEnd = FMath::VInterpTo(CurrentEnd, TargetEnd, DeltaTime, PositionInterpSpeed);
	}
	else {
		CurrentStart = TargetStart;
		CurrentEnd = TargetEnd;
	}

	UpdateVisual();
}

void ALaserPointerActor::SetBeamTarget(const FVector& InStart, const FVector& InEnd)
{
	TargetStart = InStart;
	TargetEnd = InEnd;
}

void ALaserPointerActor::UpdateVisual()
{
	FVector Dir = CurrentEnd - CurrentStart;
	float Length = Dir.Size();
	if (Length <= KINDA_SMALL_NUMBER) {
		Length = 1.0f;
	}

	const FVector MidPoint = CurrentStart + Dir * 0.5f;
	SetActorLocation(MidPoint);

	const FVector NormalDir = Dir.GetSafeNormal();
	const FQuat RotQuat = FQuat::FindBetweenNormals(FVector::UpVector, NormalDir);
	SetActorRotation(RotQuat);

	const float FullMeshHeight = MeshHalfHeight * 2.f;
	const float ScaleZ = (FullMeshHeight > KINDA_SMALL_NUMBER) ? (Length / FullMeshHeight) : 1.0f;
	const float ScaleXY = (MeshRadius > KINDA_SMALL_NUMBER) ? (BeamRadius / MeshRadius) : 0.01f;

	BeamMesh->SetRelativeScale3D(FVector(ScaleXY, ScaleXY, ScaleZ));
	
}

