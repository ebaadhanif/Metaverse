#include "BeamVectorActorBase.h"
#include <Metaverse/Team Visioneers/DisplayManager.h>
#include "ModeManager.h"

ABeamVectorActorBase::ABeamVectorActorBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	BeamComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("BeamNiagara"));
	BeamComp->SetupAttachment(Root);
	BeamComp->bAutoActivate = true;
	BeamComp->SetAutoDestroy(false);

	BeamComp->SetCullDistance(20000000);
	
}

void ABeamVectorActorBase::BeginPlay()
{
	Super::BeginPlay();

	// If set in C++ or BP, assign the system once
	if ((BeamSystem && BeamComp->GetAsset() != BeamSystem))
	{
		BeamComp->SetAsset(BeamSystem);
		BeamComp->Activate(true);
	}

}

void ABeamVectorActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FrameTime += DeltaTime;

	if (!BeamComp) return;

	FVector Start, End;
	if (bUseRawPositions)
	{
		if (RawStart == FVector::ZeroVector || RawEnd == FVector::ZeroVector) return;
		Start = RawStart;
		End = RawEnd;
	}
	else
	{
		if (!Source || !Destination) return;
		Start = Source->GetActorLocation();
		End = Destination->GetActorLocation();
	}
	const FVector ActorPosition = GetActorLocation();
	const FVector CameraPosition = ADisplayManager::GetInstance()->CameraLocation;

	const float Distance = FVector::Dist(ActorPosition, CameraPosition);
	float ScaleFactor = FMath::Clamp((Distance / 300.0f), 1.0f, 15000.0f);
	float radius = FMath::Clamp((Distance / 80.0f), 20.f, 20000.0f);
	float thickness = FMath::Clamp((Distance / 100.0f), 200.f, 20000.0f);

	BeamComp->SetVectorParameter(TEXT("BeamStart"), Start);
	BeamComp->SetVectorParameter(TEXT("BeamEnd"), End);
	BeamComp->SetFloatParameter(FName("BeamWidth"), ScaleFactor);

	if (AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::HeightVectorRings).FeatureActive)
	{
		OnAfterBeamUpdated(DeltaTime, Start, End, radius, thickness);
	}
	else {
		clearRings();
	}

	if (isHeightRingVisible)
	{
		UpdateHeightRing(Start, End, radius, thickness);
	}


		
}

void ABeamVectorActorBase::EndPlay(const EEndPlayReason::Type EEndPlayReason)
{
	if (BeamComp)
	{
		BeamComp->DeactivateImmediate();
	}
	Super::EndPlay(EEndPlayReason);
}

void ABeamVectorActorBase::SetJetEndpoints(AActor* InSource, AActor* InDestination)
{
	if (InSource && InDestination)
	{
		Source = InSource;
		Destination = InDestination;
		bUseRawPositions = false;
	}
}

void ABeamVectorActorBase::SetBeamEndpoints(const FVector& InStart, const FVector& InEnd)
{
	if (InStart == FVector::ZeroVector || InEnd == FVector::ZeroVector)
		return;

	if ((ForceType!= EForceType::FRIENDLY) && (BeamComp->GetAsset() != BeamSystemRed || BeamComp->GetAsset() != BeamSystemOther || BeamComp->GetAsset() != BeamSystemNeutral))
	{

		if ((BeamSystemRed && BeamComp->GetAsset() != BeamSystemRed) && ForceType == EForceType::OPPOSING) {
			BeamComp->SetAsset(BeamSystemRed);
			BeamComp->Activate(true);
		}
		else if ((BeamSystemRed && BeamComp->GetAsset() != BeamSystemOther) && ForceType == EForceType::OTHERS) {
			BeamComp->SetAsset(BeamSystemOther);
			BeamComp->Activate(true);
		}
		else if ((BeamSystemRed && BeamComp->GetAsset() != BeamSystemNeutral) && ForceType == EForceType::NEUTRAL) {
			BeamComp->SetAsset(BeamSystemNeutral);
			BeamComp->Activate(true);
		}
	}
	RawStart = InStart;
	RawEnd = InEnd;
	bUseRawPositions = true;
}

void ABeamVectorActorBase::SetVectorVisibility(bool bVisible)
{
	if (!BeamComp) return;
	BeamComp->SetVisibility(bVisible, true);
	BeamComp->SetHiddenInGame(!bVisible);
	if (bVisible) BeamComp->Activate(true);
}
