// Fill out your copyright notice in the Description page of Project Settings.


#include "RemoteMissile.h"
#include "../Team Visioneers/Menus/SettingsDropDown.h"
#include <Metaverse/Team Visioneers/DisplayManager.h>
#include <Metaverse/Team RenderStorm/ModeManager.h>


// Sets default values
ARemoteMissile::ARemoteMissile()
{
	LeftWingCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftWingCube"));
	LeftWingCube->SetupAttachment(RootComponent);
	LeftWingCube->SetRelativeLocation(FVector(-350, -horizontalTrailWidth, 0));
	LeftWingCube->SetVisibility(false);
	LeftWingCube->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RightWingCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightWingCube"));
	RightWingCube->SetupAttachment(RootComponent);
	RightWingCube->SetRelativeLocation(FVector(-350, horizontalTrailWidth, 0));
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

	PrimaryActorTick.bCanEverTick = true;
}

//Setting the trail parameters
void ARemoteMissile::SetRibbonmesh(float DeltaTime)
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
void ARemoteMissile::SetVerticalTrail(float DeltaTime)
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


void ARemoteMissile::ApplyMode() {
	VerticalTrailActor->SetActorHiddenInGame(!AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::VerticalTrail).FeatureActive);
	VerticalTrailActor->SetTrailVisibility(AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::VerticalTrail).FeatureActive);

	RibbonActor->SetActorHiddenInGame(!AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::HorizontalTrail).FeatureActive);
	RibbonActor->SetTrailVisibility(AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::HorizontalTrail).FeatureActive);

	ForwardBeamActor->SetActorHiddenInGame(!AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::HeadingVector).FeatureActive);
	ForwardBeamActor->SetVectorVisibility(AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::HeadingVector).FeatureActive);

	GroundBeamActor->SetActorHiddenInGame(!AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::DownVector).FeatureActive);
	GroundBeamActor->SetVectorVisibility(AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::DownVector).FeatureActive);

	UpwardBeamActor->SetActorHiddenInGame(!AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::UpVector).FeatureActive);
	UpwardBeamActor->SetVectorVisibility(AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::UpVector).FeatureActive);
}


void ARemoteMissile::setRibbon()
{
	if (RibbonActor)
	{
		RibbonActor->setForceType(GetForceType());
	}
}

void ARemoteMissile::setVerticalRibbon()
{
	if (VerticalTrailActor)
	{
		VerticalTrailActor->setForceType(GetForceType());
	}
}

void ARemoteMissile::setForwardVector() {
	if (ForwardBeamActor)
	{
		ForwardBeamActor->setForceType(GetForceType());
	}
}

void ARemoteMissile::ResetTrails()
{
	delete VerticalTrailActor;
	VerticalTrailActor = nullptr;

	delete RibbonActor;
	RibbonActor = nullptr;
}



void ARemoteMissile::BeginPlay()
{
	Super::BeginPlay();
	RemoteEntityType = ERemoteEntityType::MISSILE;

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


	if (!UIManager::GetInstance()->ButtonSates.bIsVerticalTrail)
	{
		VerticalTrailActor->SetActorHiddenInGame(true);
		VerticalTrailActor->SetTrailVisibility(false);
	}
	if (!UIManager::GetInstance()->ButtonSates.bIsHorizontalTrail)
	{
		RibbonActor->SetActorHiddenInGame(true);
		RibbonActor->SetTrailVisibility(false);
	}

	if (!UIManager::GetInstance()->ButtonSates.bIsHeadingVector)
	{
		ForwardBeamActor->SetActorHiddenInGame(true);
		ForwardBeamActor->SetVectorVisibility(false);
	}
	if (!UIManager::GetInstance()->ButtonSates.bIsDownVector)
	{
		GroundBeamActor->SetActorHiddenInGame(true);
		GroundBeamActor->SetVectorVisibility(false);
	}
	if (!UIManager::GetInstance()->ButtonSates.bIsUpVector)
	{
		UpwardBeamActor->SetActorHiddenInGame(true);
		UpwardBeamActor->SetVectorVisibility(false);
	}


}

// Called every frame
void ARemoteMissile::Tick(float DeltaTime)
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
	const float distanceToAdd = FMath::Clamp((Distance / 10.0f), 0.0f, 1000000.f);
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



	SetRibbonmesh(DeltaTime);
	SetVerticalTrail(DeltaTime);


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


void ARemoteMissile::SetGroundRingSpacingMeters(float SpacingMeters)
{
	GroundRingSpacing = FMath::Max(0.f, SpacingMeters * 100.f);
	if (GroundBeamActor)
	{
		GroundBeamActor->RingSpacing = GroundRingSpacing;
	}
}

void ARemoteMissile::SetForwardVector(FEntityState entityState) {

	const FVector JetForward = GetActorForwardVector().GetSafeNormal();
	const FVector ActorPosition = GetActorLocation();
	const FVector CameraPosition = ADisplayManager::GetInstance()->CameraLocation;
	const float Distance = FVector::Dist(ActorPosition, CameraPosition);
	const float offsetMultiplier = FMath::Clamp((Distance / 20), 800.f, 40000.f);
	const FVector JetLocation = GetActorLocation() + JetForward * offsetMultiplier;
	const float SpeedNmPerHour = entityState.speedInKnots;

	const float Beamlength_cm = FMath::Clamp(SpeedNmPerHour, 200.f, 700.f);
	const float distanceToAdd = FMath::Clamp((Distance / 10.0f), 0.0f, 1000000.f);

	const float Beamlengthcentimeters = (Beamlength_cm)+(distanceToAdd);
	const FVector ForwardTarget = JetLocation + JetForward * (Beamlengthcentimeters);

	ForwardBeamActor->SetBeamEndpoints(JetLocation, ForwardTarget);
}

void ARemoteMissile::ApplyGroundBeamConfigMeters(float SpacingMeters, float RadiusMeters, float ThicknessMeters, int32 MaxRings)
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




void ARemoteMissile::EndPlay(const EEndPlayReason::Type EEndPlayReason)
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