// Fill out your copyright notice in the Description page of Project Settings.

#include "RemoteFixedWingAircraft.h"
#include "Kismet/GameplayStatics.h"
#include "../Team RenderStorm/NiagaraLockLineActor.h"
#include "../Team RenderStorm/NiagaraLockLineRedActor.h"
#include "../Team RenderStorm/TrailController.h"
#include "Components/ChildActorComponent.h"
#include "../Team RenderStorm/GroundVectorActor.h"
#include "../Team RenderStorm/ForwardVectorActor.h"
#include "../Team RenderStorm/UpwardVector.h"
#include "../Team Visioneers/Menus/SettingsDropDown.h"
#include <Metaverse/Team Visioneers/DisplayManager.h>
#include <NiagaraFunctionLibrary.h>
#include <Metaverse/Team RenderStorm/ModeManager.h>



// Sets default values
ARemoteFixedWingAircraft::ARemoteFixedWingAircraft()
{
	LeftWingCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftWingCube"));
	LeftWingCube->SetupAttachment(RootComponent);
	LeftWingCube->SetRelativeLocation(FVector(-1500, -horizontalTrailWidth, 0));
	LeftWingCube->SetVisibility(false);
	LeftWingCube->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RightWingCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightWingCube"));
	RightWingCube->SetupAttachment(RootComponent);
	RightWingCube->SetRelativeLocation(FVector(-1500, horizontalTrailWidth, 0));
	RightWingCube->SetVisibility(false);
	RightWingCube->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> StartMat(TEXT("Material'/Game/Materials/LockLine/ForwardVector.ForwardVector'"));
	if (StartMat.Succeeded()) { ForwardvectorMaterial = StartMat.Object; }

	ForwardBeamCAC = CreateDefaultSubobject<UChildActorComponent>(TEXT("ForwardBeamCAC"));
	ForwardBeamCAC->SetupAttachment(GetRootComponent());
	ForwardBeamCAC->SetChildActorClass(AForwardVectorActor::StaticClass());

	UpwardBeamCAC = CreateDefaultSubobject<UChildActorComponent>(TEXT("UpwardBeamCAC"));
	UpwardBeamCAC->SetupAttachment(GetRootComponent());
	UpwardBeamCAC->SetChildActorClass(AUpwardVector::StaticClass());


	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> BeamSysAsset(TEXT("/Game/VigilanteContent/Vehicles/West_Tank_M1A1Abrams/FX/AircraftSmoke.AircraftSmoke"));
	if (BeamSysAsset.Succeeded())
	{
		SmokeNiagaraSystem = BeamSysAsset.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load Beam Niagara System"));
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> BeamAfterBurnerSysAsset(TEXT("/Game/VigilanteContent/Vehicles/West_Tank_M1A1Abrams/FX/AfterBurner_2.AfterBurner_2"));
	if (BeamAfterBurnerSysAsset.Succeeded())
	{
		AfterBurnerNiagaraSystem = BeamAfterBurnerSysAsset.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load Beam Niagara System"));
	}

	PrimaryActorTick.bCanEverTick = true;
}

//Setting the trail parameters
void ARemoteFixedWingAircraft::SetRibbonmesh(float DeltaTime)
{
	if (!RibbonActor)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		RibbonActor = GetWorld()->SpawnActor<ARibbonMeshActor>(
			ARibbonMeshActor::StaticClass(),
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			SpawnParams
		);
		RibbonActor->SetOwner(this);

	}

	const FVector JetDirRaw = GetVelocity().GetSafeNormal();
	const FVector JetDir = (!JetDirRaw.IsNearlyZero() ? JetDirRaw : LastJetDir);
	if (!JetDirRaw.IsNearlyZero()) { LastJetDir = JetDirRaw; }

	FVector CurrLeft = LeftWingCube->GetComponentLocation();
	FVector CurrRight = RightWingCube->GetComponentLocation();
	CurrLeft.Z += 10;
	CurrRight.Z += 10;

	if (!RibbonActor) return;

	if (!bHasPreviousPoints)
	{
		PrevLeft = CurrLeft;
		PrevRight = CurrRight;
		bHasPreviousPoints = true;

		PrevActorRot = GetActorRotation();
		bHavePrevRot = true;

		TimeSinceStraightRibbon = 0.f;
		FramesSinceTurnRibbon = 0;
		return;
	}

	const FRotator CurrActorRot = GetActorRotation();
	float AngularSpeedDegPerSec = 0.f;
	if (bHavePrevRot)
	{
		const FRotator DeltaRot = (CurrActorRot - PrevActorRot).GetNormalized();
		const float DeltaMagDeg = FMath::Abs(DeltaRot.Roll) + FMath::Abs(DeltaRot.Pitch) + FMath::Abs(DeltaRot.Yaw);
		AngularSpeedDegPerSec = (DeltaTime > SMALL_NUMBER) ? (DeltaMagDeg / DeltaTime) : 0.f;
	}
	bHavePrevRot = true;

	const bool bTurning = (AngularSpeedDegPerSec > TurnRateThresholdDegPerSec);

	const bool bMovedEnough =
		(!CurrLeft.Equals(PrevLeft, MinWingPointDelta) ||
			!CurrRight.Equals(PrevRight, MinWingPointDelta));

	bool bEmitNow = false;
	if (bTurning)
	{
		FramesSinceTurnRibbon++;
		if (FramesSinceTurnRibbon >= TurnRibbonFrameInterval && bMovedEnough)
		{
			bEmitNow = true;
			FramesSinceTurnRibbon = 0;
			TimeSinceStraightRibbon = 0.f;
		}
	}
	else
	{
		TimeSinceStraightRibbon += DeltaTime;
		if (TimeSinceStraightRibbon >= StraightRibbonInterval && bMovedEnough)
		{
			bEmitNow = true;
			TimeSinceStraightRibbon = 0.f;
		}
		else
		{
			RibbonActor->stretchPreviousPoints(CurrLeft, CurrRight);
		}
	}

	if (bEmitNow)
	{
		RibbonActor->AddRibbonSegment(CurrLeft, CurrRight);
		PrevLeft = CurrLeft;
		PrevRight = CurrRight;
	}

	PrevActorRot = CurrActorRot;
}

//Setting the VERTICAL trail parameters
void ARemoteFixedWingAircraft::SetVerticalTrail(float DeltaTime)
{
	if (!VerticalTrailActor)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		VerticalTrailActor = GetWorld()->SpawnActor<AVerticalRibbonMeshActor>(
			AVerticalRibbonMeshActor::StaticClass(),
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			SpawnParams
		);
		VerticalTrailActor->SetOwner(this);
	}

	const FVector JetDirRaw = GetVelocity().GetSafeNormal();
	if (!JetDirRaw.IsNearlyZero()) { LastJetDir = JetDirRaw; }
	const FVector JetLocation = GetActorLocation() - FVector(0, 0, 200);

	const FVector3d LhSeaLevel(this->GeodeticLocation.Y, this->GeodeticLocation.X, 0.0);
	const FVector3d UnrealPos = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(LhSeaLevel);
	const FVector End = UnrealPos;

	if (!bHasPrevVertical)
	{
		PrevJetLocation = JetLocation;
		PrevGroundHit = End;
		bHasPrevVertical = true;

		const float height = FMath::Max(0.f, JetLocation.Z - End.Z);

		const FVector L = End;
		const FVector R = End + FVector::UpVector * height;
		const float distanceFromCamera = FVector::Dist(GetActorLocation(), ADisplayManager::GetInstance()->CameraLocation);
		//VerticalTrailActor->AddRibbonSegment(JetLocation, End, distanceFromCamera);

		PrevActorRot = GetActorRotation();
		bHavePrevRot = true;

		TimeSinceStraightVerticalRibbon = 0.f;
		FramesSinceTurnVerticalRibbon = 0;
		return;
	}

	// Angular speed (deg/sec)
	const FRotator CurrActorRot = GetActorRotation();
	float AngularSpeedDegPerSec = 0.f;
	if (bHavePrevRot)
	{
		const FRotator DeltaRot = (CurrActorRot - PrevActorRot).GetNormalized();
		const float DeltaMagDeg = FMath::Abs(DeltaRot.Roll) + FMath::Abs(DeltaRot.Pitch) + FMath::Abs(DeltaRot.Yaw);
		AngularSpeedDegPerSec = (DeltaTime > SMALL_NUMBER) ? (DeltaMagDeg / DeltaTime) : 0.f;
	}
	bHavePrevRot = true;

	const bool bTurning = (AngularSpeedDegPerSec > TurnRateVerticalThresholdDegPerSec);

	// Enough motion?
	const bool bMovedEnough =
		(!JetLocation.Equals(PrevLeft, MinWingPointDelta) ||
			!End.Equals(PrevRight, MinWingPointDelta));

	bool bEmitNow = false;
	if (bTurning)
	{
		FramesSinceTurnVerticalRibbon++;
		if (FramesSinceTurnVerticalRibbon >= TurnVerticalRibbonFrameInterval && bMovedEnough)
		{
			bEmitNow = true;
			FramesSinceTurnVerticalRibbon = 0;
			TimeSinceStraightVerticalRibbon = 0.f;
		}
	}
	else
	{
		TimeSinceStraightVerticalRibbon += DeltaTime;
		if (TimeSinceStraightVerticalRibbon >= StraightVerticalRibbonInterval && bMovedEnough)
		{
			bEmitNow = true;
			TimeSinceStraightVerticalRibbon = 0.f;
		}
		else
		{
			// While waiting to emit, stretch ONLY the newest middle slice (Start/End fixed)
			const float distanceFromCamera = FVector::Dist(GetActorLocation(), ADisplayManager::GetInstance()->CameraLocation);
			VerticalTrailActor->stretchPreviousPoints(JetLocation, End, distanceFromCamera);
		}
	}

	if (bEmitNow)
	{
		const float height = FMath::Max(0.f, JetLocation.Z - End.Z);

		const FVector L = End;
		const FVector R = End + FVector::UpVector * height;

		const float distanceFromCamera = FVector::Dist(GetActorLocation(), ADisplayManager::GetInstance()->CameraLocation);
		VerticalTrailActor->AddRibbonSegment(JetLocation, End, distanceFromCamera);

		PrevJetLocation = JetLocation;
		PrevGroundHit = End;
	}

	PrevActorRot = CurrActorRot;

}



void ARemoteFixedWingAircraft::setRibbon()
{
	if (RibbonActor)
	{
		RibbonActor->setForceType(GetForceType());
	}
}

void ARemoteFixedWingAircraft::setVerticalRibbon()
{
	if (VerticalTrailActor)
	{
		VerticalTrailActor->setForceType(GetForceType());
	}
}

void ARemoteFixedWingAircraft::setForwardVector() {
	if (ForwardBeamActor)
	{
		ForwardBeamActor->setForceType(GetForceType());
	}
}

void ARemoteFixedWingAircraft::ResetTrails()
{
	delete VerticalTrailActor;
	VerticalTrailActor = nullptr;

	delete RibbonActor;
	RibbonActor = nullptr;
}



void ARemoteFixedWingAircraft::BeginPlay()
{
	Super::BeginPlay();
	RemoteEntityType = ERemoteEntityType::FIXEDWING_AIRCRAFT;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	RibbonActor = GetWorld()->SpawnActor<ARibbonMeshActor>(
		ARibbonMeshActor::StaticClass(),
		FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams
	);
	RibbonActor->SetOwner(this);



	VerticalTrailActor = GetWorld()->SpawnActor<AVerticalRibbonMeshActor>(
		AVerticalRibbonMeshActor::StaticClass(),
		FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams
	);
	VerticalTrailActor->SetOwner(this);

	ForwardBeamActor = ForwardBeamCAC ? Cast<AForwardVectorActor>(ForwardBeamCAC->GetChildActor()) : nullptr;

	UpwardBeamActor = UpwardBeamCAC ? Cast<AUpwardVector>(UpwardBeamCAC->GetChildActor()) : nullptr;


	if (!AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::VerticalTrail).FeatureActive)
	{
		VerticalTrailActor->SetActorHiddenInGame(true);
		VerticalTrailActor->SetTrailVisibility(false);
	}
	if (!AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::HorizontalTrail).FeatureActive)
	{
		RibbonActor->SetActorHiddenInGame(true);
		RibbonActor->SetTrailVisibility(false);
	}

	if (!AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::HeadingVector).FeatureActive)
	{
		ForwardBeamActor->SetActorHiddenInGame(true);
		ForwardBeamActor->SetVectorVisibility(false);
	}
	if (!AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::DownVector).FeatureActive)
	{
		GroundBeamActor->SetActorHiddenInGame(true);
		GroundBeamActor->SetVectorVisibility(false);
	}
	if (!AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::UpVector).FeatureActive)
	{
		UpwardBeamActor->SetActorHiddenInGame(true);
		UpwardBeamActor->SetVectorVisibility(false);
	}

	if ((AModeManager::getInstance()->getActiveMode() != AModeManager::getInstance()->MetaverseModes.FindRef(FName("ISR"))) && AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::VisualGraphics).FeatureActive)
	{
		//FVector relativeOffset(-550.f, 150.f, 0.f);
		//FVector relativeSmokeOffsetLeft(-550.f, -350.f, 0.f);
		//SmokeNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(SmokeNiagaraSystem, GetRootComponent(), NAME_None, relativeOffset, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, true);
		//FVector relativeOffsetRight(-850.f, 0.f, 25.f);
		//SmokeLeftNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(SmokeNiagaraSystem, GetRootComponent(), NAME_None, relativeSmokeOffsetLeft, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, true);

		//AfterBurnerNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(AfterBurnerNiagaraSystem, GetRootComponent(), NAME_None, relativeOffsetRight, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, true);
		//if (SmokeNiagaraComponent && SmokeLeftNiagaraComponent && AfterBurnerNiagaraComponent)
		//{
		//	SmokeLeftNiagaraComponent->SetAutoActivate(true);
		//	SmokeNiagaraComponent->SetAutoActivate(true);
		//	AfterBurnerNiagaraComponent->SetAutoActivate(true);
		//}
	}
}

void ARemoteFixedWingAircraft::ApplyMode() {
	VerticalTrailActor->SetActorHiddenInGame(!AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::VerticalTrail).FeatureActive);
	VerticalTrailActor->SetTrailVisibility(AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::VerticalTrail).FeatureActive);

	RibbonActor->SetActorHiddenInGame(!AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::HorizontalTrail).FeatureActive);
	RibbonActor->SetTrailVisibility(AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::HorizontalTrail).FeatureActive);

	ForwardBeamActor->SetActorHiddenInGame(AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::HeadingVector).FeatureActive);
	ForwardBeamActor->SetVectorVisibility(!AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::HeadingVector).FeatureActive);

	GroundBeamActor->SetActorHiddenInGame(!AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::DownVector).FeatureActive);
	GroundBeamActor->SetVectorVisibility(AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::DownVector).FeatureActive);

	UpwardBeamActor->SetActorHiddenInGame(!AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::UpVector).FeatureActive);
	UpwardBeamActor->SetVectorVisibility(AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::UpVector).FeatureActive);
}

// Called every frame
void ARemoteFixedWingAircraft::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);




	FEntityState entityState = EntityManager::GetEntityManagerInstance()->UpdateEntity(EntityId);
	SetEntityState(entityState);


	const FVector JetLocation = GetActorLocation();
	SetForwardVector(entityState);
	UpdateGroundBeam(DeltaTime, JetLocation);

	//Upward Vector
	const FVector CameraPosition = ADisplayManager::GetInstance()->CameraLocation;
	const float Distance = FVector::Dist(JetLocation, CameraPosition);
	const FVector JetUpward = GetActorUpVector();
	const float distanceToAdd = FMath::Clamp((Distance / 10.0f), 0.0f, 700000.f);
	const float offsetMultiplier = FMath::Clamp((Distance / 20), 500.f, 25000.f);
	const FVector JetLocationWithOffset = JetLocation + JetUpward * offsetMultiplier;
	const FVector UpwardTarget = JetLocation + JetUpward * (1000 + distanceToAdd);
	UpwardBeamActor->SetBeamEndpoints(JetLocationWithOffset, UpwardTarget);

	//UpdateLods();
	if (GroundBeamActor)
	{
		if (Distance > 20000000)

			GroundBeamActor->SetActorHiddenInGame(true);
		else
			GroundBeamActor->SetActorHiddenInGame(false);
	}

	//UpdateModelOnHealth();


	if (AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::HorizontalTrail).FeatureActive && AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::HorizontalTrail).buttonVisibility)
	{
		SetRibbonmesh(DeltaTime);
		SetVerticalTrail(DeltaTime);
	}



	if (this->GetHealth() == ELocalHealth::DESTROYED)
	{
		this->ForwardBeamActor->SetActorHiddenInGame(true);
		this->UpwardBeamActor->SetActorHiddenInGame(true);
		this->RibbonActor->SetActorHiddenInGame(true);
		this->VerticalTrailActor->SetActorHiddenInGame(true);
		this->destroyLockLines();
		//		SetActorTickEnabled(false);
	}
	else {
		this->ForwardBeamActor->SetActorHiddenInGame(false);
		this->UpwardBeamActor->SetActorHiddenInGame(false);
		this->RibbonActor->SetActorHiddenInGame(false);
		this->VerticalTrailActor->SetActorHiddenInGame(false);
	}
}


void ARemoteFixedWingAircraft::SetGroundRingSpacingMeters(float SpacingMeters)
{
	GroundRingSpacing = FMath::Max(0.f, SpacingMeters * 100.f);
	if (GroundBeamActor)
	{
		GroundBeamActor->RingSpacing = GroundRingSpacing;
	}
}

void ARemoteFixedWingAircraft::SetForwardVector(FEntityState entityState) {

	const FVector JetForward = GetActorForwardVector().GetSafeNormal();
	const FVector ActorPosition = GetActorLocation();
	const FVector CameraPosition = ADisplayManager::GetInstance()->CameraLocation;
	const float Distance = FVector::Dist(ActorPosition, CameraPosition);
	const float offsetMultiplier = FMath::Clamp((Distance / 20), 800.f, 40000.f);
	const FVector JetLocation = GetActorLocation() + JetForward * offsetMultiplier;
	const float SpeedNmPerHour = entityState.speedInKnots;

	const float Beamlength_cm = FMath::Clamp(SpeedNmPerHour, 200.f, 700.f);
	const float distanceToAdd = FMath::Clamp((Distance / 10.0f), 0.0f, 700000.f);

	const float Beamlengthcentimeters = (Beamlength_cm)+(distanceToAdd);
	const FVector ForwardTarget = JetLocation + JetForward * (Beamlengthcentimeters);

	ForwardBeamActor->SetBeamEndpoints(JetLocation, ForwardTarget);
}

void ARemoteFixedWingAircraft::ApplyGroundBeamConfigMeters(float SpacingMeters, float RadiusMeters, float ThicknessMeters, int32 MaxRings)
{
	GroundRingSpacing = FMath::Max(0.f, SpacingMeters * 100.f);
	GroundRingRadius = FMath::Max(0.f, RadiusMeters * 100.f);
	GroundRingThicknessCm = FMath::Max(0.f, ThicknessMeters * 100.f);
	GroundMaxRings = FMath::Max(0, MaxRings);

	if (GroundBeamActor)
	{
		GroundBeamActor->RingSpacing = GroundRingSpacing;
		GroundBeamActor->RingRadius = GroundRingRadius;
		GroundBeamActor->RingThicknessCm = GroundRingThicknessCm;
		GroundBeamActor->MaxRings = GroundMaxRings;
	}
}




void ARemoteFixedWingAircraft::EndPlay(const EEndPlayReason::Type EEndPlayReason)
{
	Super::EndPlay(EEndPlayReason);
	if (RibbonActor)
	{
		RibbonActor->Destroy();
		RibbonActor = nullptr;
	}
	if (ForwardBeamActor)
	{
		ForwardBeamActor->Destroy();
		ForwardBeamActor = nullptr;
	}
	if (VerticalTrailActor)
	{
		VerticalTrailActor->Destroy();
		VerticalTrailActor = nullptr;
	}
	if (GroundBeamActor)
	{
		GroundBeamActor->Destroy();
		GroundBeamActor = nullptr;
	}
	if (UpwardBeamActor)
	{
		UpwardBeamActor->Destroy();
		UpwardBeamActor = nullptr;
	}
}


