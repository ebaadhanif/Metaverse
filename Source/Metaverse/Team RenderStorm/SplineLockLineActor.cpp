#include "../Team RenderStorm/SplineLockLineActor.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInterface.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"

ASplineLockLineActor::ASplineLockLineActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SplineComp = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComp"));
	RootComponent = SplineComp;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BeamMeshAsset(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	if (BeamMeshAsset.Succeeded())
	{
		BeamMesh = BeamMeshAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> BeamMatAsset(TEXT("/Game/Materials/LockLine/M_lockline.M_lockline"));
	if (BeamMatAsset.Succeeded())
	{
		BeamMaterial = BeamMatAsset.Object;
	}
}

void ASplineLockLineActor::BeginPlay()
{
	Super::BeginPlay();

	
	/*TArray<AActor*> FoundCubes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStaticMeshActor::StaticClass(), FoundCubes);

	if (FoundCubes.Num() >= 2)
	{
		SetJetEndpoints(FoundCubes[0], FoundCubes[1]);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not enough cube actors found to set Jet endpoints."));
	}
	*/

	if (!BeamMesh) return;

	SplineMeshComp = NewObject<USplineMeshComponent>(this);
	SplineMeshComp->RegisterComponent();
	SplineMeshComp->AttachToComponent(SplineComp, FAttachmentTransformRules::KeepRelativeTransform);

	SplineMeshComp->SetStaticMesh(BeamMesh);

	if (BeamMaterial)
	{
		SplineMeshComp->SetMaterial(0, BeamMaterial);
	}

	SplineMeshComp->SetForwardAxis(ESplineMeshAxis::X);

	FVector2D BeamScale(0.03f, 0.03f);
	SplineMeshComp->SetStartScale(BeamScale);
	SplineMeshComp->SetEndScale(BeamScale);

	UpdateSpline();
}

void ASplineLockLineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateSpline();
}

void ASplineLockLineActor::SetJetEndpoints(AActor* JetA, AActor* JetB)
{
	Source = JetA;
	Destination = JetB;
	UpdateSpline();
}

void ASplineLockLineActor::UpdateSpline()
{
	if (!Source || !Destination || !SplineMeshComp) return;

	FVector Start = Source->GetActorLocation();
	FVector End = Destination->GetActorLocation();
	FVector Tangent = (End - Start) * 0.1f;

	SplineComp->ClearSplinePoints(false);
	SplineComp->AddSplinePoint(Start, ESplineCoordinateSpace::World, false);
	SplineComp->AddSplinePoint(End, ESplineCoordinateSpace::World, false);
	SplineComp->UpdateSpline();

	SplineMeshComp->SetStartAndEnd(Start, Tangent, End, Tangent);
}

void ASplineLockLineActor::ShowLockLine()
{
	if (SplineMeshComp)
	{
		SplineMeshComp->SetVisibility(true, true); 
		SplineMeshComp->SetHiddenInGame(false, true);
	}
}

void ASplineLockLineActor::HideLockLine()
{
	if (SplineMeshComp)
	{
		SplineMeshComp->SetVisibility(false, true);
		SplineMeshComp->SetHiddenInGame(true, true);
	}
}

