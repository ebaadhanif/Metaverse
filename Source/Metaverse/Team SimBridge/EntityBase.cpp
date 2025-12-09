// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityBase.h"
#include "ProceduralMeshComponent.h"
#include "LoadingManager.h"
#include "MetaverseHUD.h"
#include "Model3DAssetManager.h"
#include "FreeCameraPawn.h"
#include "../Team Visioneers/DisplayManager.h"
#include <Metaverse/Team RenderStorm/ModeManager.h>

// Sets default values
AEntityBase::AEntityBase()
{
	PrimaryActorTick.bCanEverTick = false;
	FrameTime = 0.0f;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	GlobeAnchor = CreateDefaultSubobject<UCesiumGlobeAnchorComponent>(TEXT("GlobeAnchor"));
	BillbordMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/Billboard/M_BillboardMat.M_BillboardMat"));
	WidgetComponent = nullptr;
	GroundClamp = false;
	BattlespaceMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/BattleSpace/M_ForcedBasedMat.M_ForcedBasedMat"));


	// ChildActorComponents for Ground & Forward beams
	GroundBeamCAC = CreateDefaultSubobject<UChildActorComponent>(TEXT("GroundBeamCAC"));
	GroundBeamCAC->SetupAttachment(GetRootComponent());
	GroundBeamCAC->SetChildActorClass(AGroundVectorActor::StaticClass());

	CesiumTileset = Cast<ACesium3DTileset>(UGameplayStatics::GetActorOfClass(GetWorld(), ACesium3DTileset::StaticClass()));


}

void AEntityBase::Initialize(FEntityState entityState, int radarRange)
{
	BillboardVisibilityState = true;
	EntityId = entityState.Id;
	CallSign = entityState.CallSign;
	entityType = entityState.entityType;
	ForceType = entityState.forceType;
	RadarRange = radarRange;
	//speedInKnots = entityState.speedInKnots;
	BattlespaceDynamicInstanceMaterial = UMaterialInstanceDynamic::Create(BattlespaceMaterial, nullptr);
	bisBattlespaceModeEnabled = EntityManager::GetEntityManagerInstance()->IsInBattlespaceMode();
	CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	SetEntityState(entityState);
	Billboard = NewObject<UMaterialBillboardComponent>(this);
	Billboard->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	Billboard->SetMobility(EComponentMobility::Movable);
	if (Billboard) {
		BillboardDynamicMaterial = Mil2525Manager::GetMil2525ManagerInstance()->SetupMil2525Material(entityType, ForceType);
		Billboard->SetupAttachment(RootComponent);
		Billboard->RegisterComponent();
		AddInstanceComponent(Billboard);
		SpriteElement.Material = BillboardDynamicMaterial;
		SpriteElement.BaseSizeX = 1000.0f;
		SpriteElement.BaseSizeY = 1000.0f;
		Billboard->Elements.Empty();
		Billboard->Elements.Add(SpriteElement);
		Billboard->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
		Billboard->SetWorldScale3D(FVector(1));
	}
}

void AEntityBase::SetEntityState(FEntityState entityState)
{
	if (isGroundEntity)
	{
		GroundClampEntity(entityState);
	}
	else
	{
		isLandingGearExtended = entityState.isLandingGearExtended;
		WeightOnWheels = entityState.WeightOnWheels;
		isNavLightsOn = entityState.isNavLightsOn;
		if (WeightOnWheels == 1)
		{
			GroundClampEntity(entityState);
		}
		else
		{
			SetEntityPosition(entityState.GeodeticLocation);
		}
	}


	GeodeticLocation = entityState.GeodeticLocation;
	WorldOrientation = ConvertAndNormalizeRadToDeg(entityState.Orientation);
	Health = entityState.health;
	isSensorOn = entityState.isSensorOn;
	speedInKnots = entityState.speedInKnots;
	WorldLocation = GetActorLocation();
	SetActorRotation(WorldOrientation);
	
	//TrackedEntitiesList = entityState.TrackedEntitiesList;
	LockedEntitiesList = entityState.LockedEntitiesList;
}

void AEntityBase::SetEntityPosition(FVector entityPosition)
{
	FVector cesiumGeodaticStandard;
	entityPosition.Z = entityPosition.Z / FEETS_PER_METER; //conversion from feet to meters
	cesiumGeodaticStandard = FVector(entityPosition.Y, entityPosition.X, entityPosition.Z);
	GlobeAnchor->MoveToLongitudeLatitudeHeight(cesiumGeodaticStandard);
}

void AEntityBase::GroundClampEntity(FEntityState entityState)
{
	float cameraDistance = FVector::Dist(CameraManager->GetCameraLocation(), GetActorLocation()) / 100000;
	if (speedInKnots != 0)
	{
		bIsPositioned = false;
		if (cameraDistance < 1.0f)
		{
			GroundClamp = true;
		}
	}

	else if (((GetWorld()->GetTimeSeconds() - lastClampTime) > 15))
	{
		GroundClamp = true;
		bIsPositioned = false;
	}

	if (GroundClamp)
	{
		//WorldLocation = SurfaceClamper::GetSurfaceClamperInstance()->GroundClampEntity(GetActorLocation(), this, GetWorld());
		FCesiumSampleHeightMostDetailedCallback Callback;
		TArray<FVector>worldLocationsArray;

		FVector cesiumGeodaticStandard;
		cesiumGeodaticStandard = FVector(entityState.GeodeticLocation.Y, entityState.GeodeticLocation.X, entityState.GeodeticLocation.Z);

		worldLocationsArray.Add(cesiumGeodaticStandard);
		Callback.BindLambda([this](ACesium3DTileset* Tileset, const TArray<FCesiumSampleHeightResult>& Results, const TArray<FString>& Warnings)
			{
				/*if (!Results.IsEmpty())
				{
					GlobeAnchor->MoveToLongitudeLatitudeHeight(FVector(GeodeticLocation.Y, GeodeticLocation.X, Results[0].LongitudeLatitudeHeight.Z));
				}*/
				this->GroundEntityHeightValueFromGround =GlobeAnchor->ResolveGeoreference()->TransformLongitudeLatitudeHeightPositionToUnreal(FVector(GeodeticLocation.Y, GeodeticLocation.X, Results[0].LongitudeLatitudeHeight.Z)).Z;
			});
		CesiumTileset->SampleHeightMostDetailed(worldLocationsArray, Callback);
		lastClampTime = GetWorld()->GetTimeSeconds();
		AlignmentToGround();
		SetEntityPosition(entityState.GeodeticLocation);
		SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GroundEntityHeightValueFromGround));
		GroundClamp = false;
		bIsPositioned = true;

	}

	if (!bIsPositioned)
	{
		SetEntityPosition(entityState.GeodeticLocation);
		bIsPositioned = true;
	}
}

FEntityType AEntityBase::GetEntityType() {
	return entityType;
}

void AEntityBase::setRibbon()
{
}

void AEntityBase::setVerticalRibbon()
{
}

void AEntityBase::setForwardVector()
{
}
void AEntityBase::ApplyMode()
{
}

void AEntityBase::ResetTrails()
{
}


void AEntityBase::toggleTrail(bool IsVisble)
{
	showTrail = IsVisble;
}

void AEntityBase::toggleVerticalTrail(bool IsVisble)
{
	showVerticalTrail = IsVisble;
}

void AEntityBase::HandleLODsandHealthStates()
{

	float distance = FVector::Dist(GetActorLocation(), CameraManager->GetCameraLocation());

	for (int i = 0; i < LODParentActors.Num(); i++)
	{
		if (distance < LodShiftDistance * (i + 1))
		{
			activeLODIndex = i;
			break;
		}
	}
	ModelVisualMode Mode = EntityManager::GetEntityManagerInstance()->GetModeVisualMode();

	if (PreviousVisualMode != Mode || !bisFirstTimeModeCheck || PreviousHealthState != Health)
	{
		bisFirstTimeModeCheck = true;
		PreviousVisualMode = Mode;

		switch (Mode)
		{
		case ModelVisualMode::BattleSpaceMode:
		{
			UE_LOG(LogTemp, Warning, TEXT("BattleSpaceMode"));
			SetVisibleModel(BattlespceChildActors, true);
			SetVisibleModel(DefaultChildActors, true);
			HandleLODs(-1);
			SetVisibleModel(DamagedActors, false);
			SetVisibleModel(DestroyedActors, false);
			if (Battlespace_Actor) Battlespace_Actor->SetActorHiddenInGame(false);
			if (DefaultPaperMesh) DefaultPaperMesh->SetActorHiddenInGame(false);
			SetMil2525Visibility(false);
			SetForceBasedMaterial();
			bisFirstTimeHealthCheck = false;
			if (Health == ELocalHealth::DESTROYED)
			{
				if (CoffinMeshActor)
					CoffinMeshActor->SetActorHiddenInGame(false);
			}
			else
				if (CoffinMeshActor)
					CoffinMeshActor->SetActorHiddenInGame(true);
			break;
		}
		case ModelVisualMode::Mil2525Mode:
		{
			UE_LOG(LogTemp, Warning, TEXT("Mil2525Mode"));

			SetMil2525Visibility(true);
			HandleLODs(-1);
			SetVisibleModel(DamagedActors, false);
			SetVisibleModel(DefaultChildActors, false);
			SetVisibleModel(BattlespceChildActors, false);
			SetVisibleModel(DestroyedActors, false);
			if (DefaultPaperMesh) DefaultPaperMesh->SetActorHiddenInGame(true);
			if (Battlespace_Actor) Battlespace_Actor->SetActorHiddenInGame(true);
			if (CoffinMeshActor)
				CoffinMeshActor->SetActorHiddenInGame(true);
			bisFirstTimeHealthCheck = false;

			break;
		}
		case ModelVisualMode::TexturedMode:
		{
			UE_LOG(LogTemp, Warning, TEXT("TexturedMode"));

			if (DefaultPaperMesh) DefaultPaperMesh->SetActorHiddenInGame(false);
			break;
		}

		}
	}


	//if (PreviousHealthState != Health || !bisFirstTimeHealthCheck || distance < LodShiftDistance && bisOnLOD1 || distance > LodShiftDistance && bisOnLOD0)
	if (PreviousHealthState != Health || !bisFirstTimeHealthCheck || previousActiveLODIndex != activeLODIndex)
	{
		PreviousHealthState = Health;
		previousActiveLODIndex = activeLODIndex;

		if (ModelVisualMode::TexturedMode == Mode)
		{
			bisFirstTimeHealthCheck = true;
			bisFirstTimeModeCheck = false;
			switch (Health)
			{
			case ELocalHealth::NO_DAMAGE:

				SetVisibleModel(DefaultChildActors, true);
				SetVisibleModel(DamagedActors, false);
				SetVisibleModel(BattlespceChildActors, false);
				SetVisibleModel(DestroyedActors, false);
				if (CoffinMeshActor)CoffinMeshActor->SetActorHiddenInGame(true);
				SetMil2525Visibility(false);
				if (Battlespace_Actor) Battlespace_Actor->SetActorHiddenInGame(true);
				HandleLODs(activeLODIndex);

				//if (bisOnLOD1)
				//{
				//	bisOnLOD0 = true;
				//	bisOnLOD1 = false;
				//	SetVisibleModel(LOD0_actors, true);
				//	SetVisibleModel(LOD1_actors, false);
				//}
				//else if (bisOnLOD0)
				//{
				//	bisOnLOD0 = false;
				//	bisOnLOD1 = true;
				//	SetVisibleModel(LOD0_actors, false);
				//	SetVisibleModel(LOD1_actors, true);
				//}
				break;
			case ELocalHealth::MINOR_DAMAGE:

				HandleLODs(-1);
				SetVisibleModel(DefaultChildActors, true);
				SetVisibleModel(DamagedActors, true);
				SetVisibleModel(BattlespceChildActors, false);
				SetVisibleModel(DestroyedActors, false);
				if (CoffinMeshActor)
					CoffinMeshActor->SetActorHiddenInGame(true);
				SetMil2525Visibility(false);
				if (Battlespace_Actor) Battlespace_Actor->SetActorHiddenInGame(true);

				break;
			case ELocalHealth::MEDIUM_DAMAGE:
				HandleLODs(-1);
				SetVisibleModel(DefaultChildActors, true);
				SetVisibleModel(DamagedActors, true);
				SetVisibleModel(BattlespceChildActors, false);
				SetVisibleModel(DestroyedActors, false);
				if (CoffinMeshActor)
					CoffinMeshActor->SetActorHiddenInGame(true);
				SetMil2525Visibility(false);
				if (Battlespace_Actor) Battlespace_Actor->SetActorHiddenInGame(true);

				break;
			case ELocalHealth::MAJOR_DAMAGE:
				HandleLODs(-1);
				SetVisibleModel(DefaultChildActors, true);
				SetVisibleModel(DamagedActors, true);
				SetVisibleModel(BattlespceChildActors, false);
				SetVisibleModel(DestroyedActors, false);
				if (CoffinMeshActor)
					CoffinMeshActor->SetActorHiddenInGame(true);
				SetMil2525Visibility(false);
				if (Battlespace_Actor) Battlespace_Actor->SetActorHiddenInGame(true);

				break;
			case ELocalHealth::DESTROYED:
				//StartBlink(1.f, 0.1f);
				HandleLODs(-1);
  				SetVisibleModel(DefaultChildActors, true);
				SetVisibleModel(DamagedActors, false);
				SetVisibleModel(BattlespceChildActors, false);
				SetVisibleModel(DestroyedActors, true);
				SetMil2525Visibility(false);
				if (Battlespace_Actor) Battlespace_Actor->SetActorHiddenInGame(true);
				if (CoffinMeshActor)CoffinMeshActor->SetActorHiddenInGame(false);
				break;
			default:
				break;
			}
		}

	}




}

void AEntityBase::BeginPlay()
{
	Super::BeginPlay();

	Georeference = ACesiumGeoreference::GetDefaultGeoreference(GetWorld());
	APlayerController* PC = ADisplayManager::GetInstance()->PC;// UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC) return;
	playerController = GetWorld()->GetFirstPlayerController();
	if ((!AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::AllLocklines).FeatureActive) &&
		(!AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::OpposingLockline).FeatureActive)&&
		(!AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::SameLockline).FeatureActive))
	{
		showLockLines = false;
	}

	GroundBeamActor = GroundBeamCAC ? Cast<AGroundVectorActor>(GroundBeamCAC->GetChildActor()) : nullptr;
	//GroundBeamActor->SetOwner(this);


	if (GroundBeamActor)
	{
		GroundBeamActor->RingSpacing = GroundRingSpacing;
		GroundBeamActor->RingRadius = GroundRingRadius;
		GroundBeamActor->RingThicknessCm = GroundRingThicknessCm;
		GroundBeamActor->MaxRings = GroundMaxRings;
	}

	if (UNiagaraComponent** Found = EffectsRegistry.Find(FName("TankFireVFX1")))
	{
		if (UNiagaraComponent* Comp = *Found) {
			FireNiagaraComponent = Comp;
		}
	}

	if (UAudioComponent** Found = SoundRegistry.Find(FName("TankFireVFX1")))
	{
		if (UAudioComponent* Comp = *Found) {
			FireSound = Comp;
		}
	}


	if (UAudioComponent** Found = SoundRegistry.Find(FName("Entity_Sound")))
	{
		if (UAudioComponent* Comp = *Found) {
			EntitySoundd = Comp;
		}
	}

	_loadingManager = Cast<ALoadingManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ALoadingManager::StaticClass()));
	_uModel3DAssetManager = _loadingManager->GetUModel3DAssetManager();
	//onEntitySpawn();
	if (AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::Blink).FeatureActive)
	{
		StartBlink(1.f, 0.1f);
	}

	//LockLineType = EntityManager::GetEntityManagerInstance()->GLockLineType;
	UCoveragesManager::GetInstance()->ToggleVisibility(AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::GroundCoverages).FeatureActive);
	UCoveragesManager::GetInstance()->ToggleVisibilityOfCoveragesByRemoteEntityType(AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::AircraftCoverage).FeatureActive, ERemoteEntityType::FIXEDWING_AIRCRAFT);
}
float ElapsedTime = 0;

void AEntityBase::Fire()
{
	if (!FireNiagaraComponent)
	{
		if (UNiagaraComponent** Found = EffectsRegistry.Find(FName("TankFireVFX1")))
		{
			if (UNiagaraComponent* Comp = *Found) {
				FireNiagaraComponent = Comp;
			}
		}
		if (UAudioComponent** Found = SoundRegistry.Find(FName("TankFireVFX1")))
		{
			if (UAudioComponent* Comp = *Found) {
				FireSound = Comp;
			}
		}

		if ((FireNiagaraComponent) && AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::VisualGraphics).FeatureActive) {
			FireNiagaraComponent->Activate(true);
			if (FireSound)
			{
				FireSound->Play();
			}
			UE_LOG(LogTemp, Error, TEXT("Firing"));
		}
	}

	if ((FireNiagaraComponent) && AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::VisualGraphics).FeatureActive) {
		FireNiagaraComponent->Activate(true);
		if (FireSound)
		{
			FireSound->Play();
		}
		UE_LOG(LogTemp, Error, TEXT("Firing"));
	}

}

FEntityID AEntityBase::GetEntityId()
{
	return EntityId;
}

void AEntityBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FramesTime += DeltaTime;

	ModelVisualMode Mode = EntityManager::GetEntityManagerInstance()->GetModeVisualMode();

	if (FramesTime > FPS_5)
	{
		if (Mode == ModelVisualMode::Mil2525Mode) {
			UpdateBillboardSize();
		}
		else
		{
			SetEntityScale(AScalingManager::GetInstance()->ScaleActorBasedOnDistance(this, EActorType::EntityModel, ADisplayManager::GetInstance()->CameraLocation));
		}
		FramesTime = 0.0f;
		HandleLODsandHealthStates();

	}

	ElapsedTime += DeltaTime;

	if (ElapsedTime > 0.5) {

		LabelManager::UpdateLabelFacingCamera(this, ADisplayManager::GetInstance()->CameraLocation);
		WidgetComponent->SetWorldScale3D(FVector(AScalingManager::GetInstance()->ScaleActorBasedOnDistance(this, EActorType::EntityLabel, ADisplayManager::GetInstance()->CameraLocation)));
		//TextBlock->SetFont(FSlateFontInfo(FCoreStyle::GetDefaultFontStyle("Regular",24)));
		FVector LabelOffSet = FVector(0.f, 0.f, (AScalingManager::GetInstance()->ScaleActorBasedOnDistance(this, EActorType::EntityLabel, ADisplayManager::GetInstance()->CameraLocation) * 200));
		FVector WidgetTargetWorldPosition = GetActorLocation() + FVector(0.0f, 0.0f, LabelOffSet.Z * AScalingManager::GetInstance()->entityLabelOffsetMultiplier);
		WidgetComponent->SetRelativeLocation(WidgetTargetWorldPosition);

		if (AScalingManager::GetInstance() != nullptr)
			WidgetComponent->SetVisibility(AScalingManager::GetInstance()->isShowLabel);

		ElapsedTime = 0;
	}


	if (Health != PreHealth)
	{
		Mil2525Manager::GetMil2525ManagerInstance()->UpdateMil2525Symbol(BillboardDynamicMaterial, Health);
		PreHealth = Health;
	}
	if (isGroundEntity)
	{
		if (Mode == ModelVisualMode::Mil2525Mode) {
			UpdateGroundBeam(DeltaTime, this->Billboard->GetComponentLocation());
		}
		else {
			this->GroundBeamActor->ToggleHeightRingVisibility(false);
			this->GroundBeamActor->SetVectorVisibility(false);
		}
	}
	else {
		if (Mode == ModelVisualMode::Mil2525Mode) {
			this->GroundBeamActor->ToggleHeightRingVisibility(true);
		}
		else {
			this->GroundBeamActor->ToggleHeightRingVisibility(false);
		}
		UpdateGroundBeam(DeltaTime, this->GetActorLocation());
	}
	
	//Locklines
	if ((!AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::AllLocklines).FeatureActive) &&
		(!AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::OpposingLockline).FeatureActive) &&
		(!AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::SameLockline).FeatureActive))
	{
		if (!isLockLineDestroyed)
			destroyLockLines();
	}
	else {
		(this->GetForceType() == EForceType::FRIENDLY) ?
			setLockLines() : setRedLockLines();
	}


	EntitySoundd = SoundRegistry.FindRef(FName("Entity_Sound"));
	if (EntitySoundd)
	{
		if (this->GetHealth() != ELocalHealth::DESTROYED && AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::VisualGraphics).FeatureActive)
		{
			if (!EntitySoundd->IsPlaying())
			{
				EntitySoundd->Play();
			}

		}
		else {
			if (EntitySoundd->IsPlaying())
			{
				EntitySoundd->Stop();
			}

		}
	}

	//PlayEntitySound();


	//EffectsRegistry.Find(FName("fx_tchdwn1"))->


	//onEntitySpawnAndDestroy();
}



void AEntityBase::CreateDefaultMesh()
{

	AActor* Parent = EntityManager::GetEntityManagerInstance()->getEntityById(EntityId);
	DefaultPaperMesh = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), FTransform::Identity);

	if (DefaultPaperMesh)
	{
		USceneComponent* sceneCom = NewObject<USceneComponent>(DefaultPaperMesh);
		sceneCom->RegisterComponent();
		//sceneCom->AttachToComponent(NodeActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DefaultPaperMesh->SetRootComponent(sceneCom);

		bisUsingPaperMesh = true;
		UStaticMeshComponent* StaticMeshComponent = NewObject<UStaticMeshComponent>(DefaultPaperMesh, TEXT("StaticMeshComponent"));
		if (StaticMeshComponent)
		{
			StaticMeshComponent->SetupAttachment(RootComponent);
			StaticMeshComponent->RegisterComponent();
			UStaticMesh* MeshAsset = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/MyModels/Default/default.default"));
			if (MeshAsset)
			{
				StaticMeshComponent->SetStaticMesh(MeshAsset);
			}
			StaticMeshComponent->SetWorldScale3D(FVector(0.5f));
		}
	}

	if (Parent->GetRootComponent())
	{
		DefaultPaperMesh->AttachToActor(Parent, FAttachmentTransformRules::KeepRelativeTransform);
		DefaultPaperMesh->AttachToComponent(Parent->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	}

}


void AEntityBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ADisplayManager::GetInstance() != NULL) {
	    if (ADisplayManager::GetInstance()->FreeCamPawn->IsHooked)
		   ADisplayManager::GetInstance()->FreeCamPawn->ToggleHook(this, false);
	}
	
	DestroyeModel();
}

void AEntityBase::DestroyeModel()
{
	TArray<AActor*> tempArr;
	FindAllChildActors(this, tempArr);

	for (AActor* ac : tempArr)
	{
		ac->Destroy();
	}
	this->destroyLockLines();
}
void AEntityBase::FindAllChildActors(AActor* Parent, TArray<AActor*>& OutMeshes)
{
	if (!Parent) return;

	TArray<AActor*> DirectChildren;
	Parent->GetAttachedActors(DirectChildren);
	for (AActor* Child : DirectChildren)
	{
		if (Child)
		{
			OutMeshes.Add(Child);

			// Recursively go deeper
			FindAllChildActors(Child, OutMeshes);
		}
	}
}



void AEntityBase::SetEntityScale(float scaleValue)
{
	if (GetActorScale3D().X <= 1 && GetActorScale3D().Y <= 1 && GetActorScale3D().Z <= 1 && scaleValue < 1) return;

	if(ModelParent)
		ModelParent->SetActorScale3D(FVector(scaleValue));
	


}

void AEntityBase::ResetEntityScale()
{
	/*if (LOD0_Parent)
		LOD0_Parent->SetActorScale3D(FVector(1));
	if (LOD1_Parent)
		LOD1_Parent->SetActorScale3D(FVector(1));*/
	if (DestroyedActors_Parent)
		DestroyedActors_Parent->SetActorScale3D(FVector(1));
	if (DamagedActors_Parent)
		DamagedActors_Parent->SetActorScale3D(FVector(1));
	if (Battlespace_Actor)
		Battlespace_Actor->SetActorScale3D(FVector(1));
}


void AEntityBase::SetForceBasedMaterial()
{
	BattlespaceDynamicInstanceMaterial = UMaterialInstanceDynamic::Create(BattlespaceMaterial, nullptr);
	FColor Color = FColor(255, 128, 64, 255);
	switch (ForceType)
	{
	case EForceType::OTHERS:
		Color = FColor(229, 212, 21, 255);//yellow
		break;
	case EForceType::FRIENDLY:
		Color = FColor(0, 54, 255, 255);//blue
		break;
	case EForceType::OPPOSING:
		Color = FColor(255, 71, 71, 255);//red
		break;
	case EForceType::NEUTRAL:
		Color = FColor(55, 229, 21, 255);//green
		break;
	default:
		Color = FColor(229, 212, 21, 255);//yellow
		break;
	}
		BattlespaceDynamicInstanceMaterial->SetVectorParameterValue("ForceColor", Color);

	if (Battlespace_Actor)
	{

		UProceduralMeshComponent* meshComp = Cast<UProceduralMeshComponent>(Battlespace_Actor->GetComponentByClass(UProceduralMeshComponent::StaticClass()));
		if (meshComp)
		{
			meshComp->SetMaterial(0, BattlespaceDynamicInstanceMaterial);
		}
		for (AActor* actor : BattlespceChildActors)
		{
			UProceduralMeshComponent* childComp = Cast<UProceduralMeshComponent>(actor->GetComponentByClass(UProceduralMeshComponent::StaticClass()));
			if (childComp)
			{
				childComp->SetMaterial(0, BattlespaceDynamicInstanceMaterial);
			}
		}
	}
	else
	{
	}

	if (!DefaultChildActors.IsEmpty())
	{
		for (AActor* actor : DefaultChildActors)
		{
			UProceduralMeshComponent* meshComp = Cast<UProceduralMeshComponent>(actor->GetComponentByClass(UProceduralMeshComponent::StaticClass()));
			if (meshComp)
			{
				meshComp->SetMaterial(0, BattlespaceDynamicInstanceMaterial);
			}
		}
	}

	if (bisUsingPaperMesh)
	{
		UStaticMeshComponent* meshComp = Cast<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()));
		if (meshComp)
		{
			meshComp->SetMaterial(0, BattlespaceDynamicInstanceMaterial);
		}
	}
	if (CoffinMeshActor)
	{

		UStaticMeshComponent* meshComp = Cast<UStaticMeshComponent>(CoffinMeshActor->GetComponentByClass(UStaticMeshComponent::StaticClass()));
		if (meshComp)
		{
			meshComp->SetMaterial(0, BattlespaceDynamicInstanceMaterial);
		}

	}
}


void AEntityBase::ImportEntityModel()
{
	if (_uModel3DAssetManager)
		_uModel3DAssetManager->ImportBaseModel(this);
	CreateCoffinMesh();

}

void AEntityBase::UpdateBillboardSize()
{
	if (!CameraManager || !Billboard) return;

	if (!GEngine || !GEngine->GameViewport) return;

	GEngine->GameViewport->GetViewportSize(ViewportSize);

	FVector CameraLocation = CameraManager->GetCameraLocation();
	float Distance = FVector::Dist(CameraLocation, Billboard->GetComponentLocation());
	float FOV = CameraManager->GetFOVAngle();
	float ScreenHeight = ViewportSize.Y;
	float PixelPerUU = (ScreenHeight / 2.0f) / FMath::Tan(FMath::DegreesToRadians(FOV / 2.0f)) / Distance;
	float TargetSizeUU = DesiredScreenSize / PixelPerUU;
	float orignalMeshHeightUU = 0.4f;
	float scale = TargetSizeUU / orignalMeshHeightUU;


	Billboard->SetWorldScale3D(FVector(scale));
	Billboard->Elements[0].BaseSizeX = scale * orignalMeshHeightUU;

	Billboard->Elements[0].BaseSizeY = scale * orignalMeshHeightUU;
	float halfHeight = Billboard->Elements[0].BaseSizeY * 0.9f;

	FVector TargetWorldPosition = GetActorLocation() + FVector(0.0f, 0.0f, halfHeight + Mil2525Height);
	Billboard->SetWorldLocation(TargetWorldPosition);
	Billboard->MarkRenderStateDirty();
}
void AEntityBase::SetMil2525Visibility(bool isVisible)
{
	Billboard->bHiddenInGame = !isVisible;
	Billboard->MarkRenderStateDirty();
}

void AEntityBase::SetMil2525Opacity(float OpacityValue)
{
	OpacityValue = FMath::Clamp(OpacityValue, 0.0f, 1.0f);
	if (OpacityValue >= 0.0f && OpacityValue <= 1.0f) {
		BillboardDynamicMaterial->SetScalarParameterValue("BillboardOpacity", OpacityValue);
		SpriteElement.Material = BillboardDynamicMaterial;
		Billboard->Elements.Empty();
		Billboard->Elements.Add(SpriteElement);
	}
}
void AEntityBase::SetMil2525Scale(float Scale)
{
	Scale = FMath::Clamp(Scale, 5, 20);
	Scale += 0.1f;
	DesiredScreenSize = Scale;
}

void AEntityBase::HideActor()
{
}

void AEntityBase::CreateCoffinMesh()
{
	//if (bisDestroyed) return;
	if (CoffinMeshActor)
	{
		//CoffinMeshActor->SetActorHiddenInGame(true);
		return;
	}
	//if (!bisBattlespaceModeEnabled) return;
	FTransform childTransfrom = GetActorTransform();
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;

	CoffinMeshActor = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), childTransfrom, spawnParams);

	USceneComponent* sceneComp = NewObject<USceneComponent>(CoffinMeshActor);
	sceneComp->RegisterComponent();
	CoffinMeshActor->SetRootComponent(sceneComp);


	if (CoffinMeshActor)
	{
		CoffinMeshActor->SetActorScale3D(FVector(entityLength, entityWidth, entityHeight));
		DestroyedActors_ParentCoffinStaticMeshComponent = NewObject<UStaticMeshComponent>(CoffinMeshActor, TEXT("DestroyedStaticCoffinMesh"));
		DestroyedActors_ParentCoffinStaticMeshComponent->RegisterComponent();
		DestroyedActors_ParentCoffinStaticMeshComponent->AttachToComponent(CoffinMeshActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		UStaticMesh* MeshAsset = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/MyModels/DestroyedCoffin/DestroyedCoff.DestroyedCoff"));
		DestroyedActors_ParentCoffinStaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		DestroyedActors_ParentCoffinStaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		if (MeshAsset)
		{
			DestroyedActors_ParentCoffinStaticMeshComponent->SetStaticMesh(MeshAsset);
		}
	}

	TArray<AActor*> arr;
	GetAttachedActors(arr);

	if (!arr.IsEmpty())
		CoffinMeshActor->AttachToActor(arr[0], FAttachmentTransformRules::KeepRelativeTransform);
	else
		CoffinMeshActor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

#if WITH_EDITOR
	CoffinMeshActor->SetActorLabel(FString::Printf(TEXT("coffin mesh actor ")));
#endif

	FVector originEntity = FVector();
	FVector extentEntity = FVector();
	FVector originCoffin = FVector();
	FVector extentCoffin = FVector();
	UStaticMeshComponent* smesh = nullptr;
	if (CoffinMeshActor)
	{
		CoffinMeshActor->SetActorHiddenInGame(true);
	}

}

void AEntityBase::SetVisibleModel(const TArray<AActor*> actors, bool isVisible)
{
	for (AActor* actor : actors)
	{
		if (IsValid(actor))
		{


			actor->SetActorHiddenInGame(!isVisible);
		}
	}
}




//Locklines
// This templated helper handles add/remove for both blue/red lockline maps using a predicate.
template<typename TLockActor>
static void UpdateLockLinesMap(
	UWorld* World,
	USceneComponent* ParentRoot,
	const TSet<AEntityBase*>& CurrentSet,
	TMap<AEntityBase*, TLockActor*>& Map,
	TSubclassOf<TLockActor> ActorClass,
	EForceType SelfForce,
	AEntityBase* Owner,
	TFunctionRef<bool(EForceType /*TargetForce*/)> ShouldInclude

)
{
	// Remove actors whose entities are no longer tracked (single pass)
	for (auto It = Map.CreateIterator(); It; ++It)
	{
		if (!CurrentSet.Contains(It.Key()))
		{
			if (It.Value()) { It.Value()->Destroy(); }
			It.RemoveCurrent();
		}
	}

	// Add any new entities that pass the filter
	for (AEntityBase* Entity : CurrentSet)
	{
		if (!Entity || Map.Contains(Entity)) continue;

		const EForceType TargetForce = Entity->GetForceType();
		if (!ShouldInclude(TargetForce))
			continue;

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		TLockActor* Beam = World->SpawnActor<TLockActor>(ActorClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		if (!Beam) continue;

		Beam->AttachToComponent(ParentRoot, FAttachmentTransformRules::KeepRelativeTransform);
		Beam->setForceType(SelfForce);
		Beam->SetJetEndpoints(Owner, Cast<AActor>(Entity));

		Beam->SetActorHiddenInGame(false);
		Beam->SetActorTickEnabled(true);

		Map.Add(Entity, Beam);
	}

	//Beam->BeamComp->SetVectorParameter(FName("BeamStart"), Owner->GetActorLocation());
	//Beam->BeamComp->SetVectorParameter(FName("BeamEnd"), Cast<AActor>(Entity)->GetActorLocation());
}




void AEntityBase::SetLockLinesEnabled(bool bEnable)
{
	showLockLines = bEnable;
	if (!bEnable)
	{
		destroyLockLines();
	}
}



void AEntityBase::SetLockLineType(ELockLineType NewType)
{
	LockLineType = NewType;
}

void AEntityBase::SetLockLineVisibility(bool bVisible)
{
	showLockLines = bVisible;
	if (!bVisible)
	{
		destroyLockLines();
	}
}

//Destroy LockLines
void AEntityBase::destroyLockLines()
{
	for (const TPair<AEntityBase*, ANiagaraLockLineActor*>& Elem : LockBeams)
	{
		if (Elem.Value) { Elem.Value->Destroy(); }
	}
	LockBeams.Empty();

	for (const TPair<AEntityBase*, ANiagaraLockLineRedActor*>& Elem : RedLockBeams)
	{
		if (Elem.Value) { Elem.Value->Destroy(); }
	}
	RedLockBeams.Empty();

	isLockLineDestroyed = true;
}

void AEntityBase::StartBlink(float durationSeconds, float intervalSeconds)
{
	StopBlink(false);
	bBlinkHiddenState = false;
	bIsBlinking = true;
	SetActorHiddenInGame(false);

	GetWorldTimerManager().SetTimer(
		BlinkToggleHandle,
		this,
		&AEntityBase::toggleBlink,
		intervalSeconds,
		true
	);

	//FTimerDelegate EndDel;
	//EndDel.BindLambda([this]()
	//	{
	//		StopBlink(true);
	//	}
	//);
	GetWorldTimerManager().SetTimer(
		BlinkEndHandle,
		this,
		&AEntityBase::OnBlinkEnd,
		durationSeconds,
		false
	);
}

void AEntityBase::StopBlink(bool bEnsureVisible)
{
	bIsBlinking = false;
	GetWorldTimerManager().ClearTimer(BlinkToggleHandle);
	GetWorldTimerManager().ClearTimer(BlinkEndHandle);

	if (bEnsureVisible)
	{
		bBlinkHiddenState = false;
		SetActorHiddenInGame(false);
	}

}

void AEntityBase::toggleBlink()
{
	if (!bIsBlinking)
		return;
	bBlinkHiddenState = !bBlinkHiddenState;
	SetActorHiddenInGame(bBlinkHiddenState);

}

void AEntityBase::OnBlinkEnd() {
	StopBlink(true);
}

void AEntityBase::PlayEntitySound()
{

	if (UAudioComponent** Found = SoundRegistry.Find(FName("Entity_Sound")))
	{
		if (UAudioComponent* Comp = *Found) {
			EntitySoundd = Comp;
		}
	}
	EntitySoundd = SoundRegistry.FindRef(FName("Entity_Sound"));
	if (AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::VisualGraphics).FeatureActive)
	{
		if (EntitySoundd)
		{
			if (this->GetHealth() != ELocalHealth::DESTROYED)
			{
				EntitySoundd->Play();
			}
			else {
				EntitySoundd->Stop();
			}
		}
		else {
			if (UAudioComponent** Found = SoundRegistry.Find(FName("Entity_Sound")))
			{
				if (UAudioComponent* Comp = *Found) {
					EntitySoundd = Comp;
				}
			}
			if (EntitySoundd)
			{
				if (this->GetHealth() != ELocalHealth::DESTROYED)
				{
					EntitySoundd->Play();
				}
				else {
					EntitySoundd->Stop();
				}
			}
		}

	}
	else {
		if (EntitySoundd)
		{
			EntitySoundd->Stop();
		}
		else {
			if (UAudioComponent** Found = SoundRegistry.Find(FName("Entity_Sound")))
			{
				if (UAudioComponent* Comp = *Found) {
					EntitySoundd = Comp;
				}
			}
			if (EntitySoundd)
			{
				EntitySoundd->Stop();
			}
		}

	}


}

void AEntityBase::StopEntitySound()
{
}

void AEntityBase::setLockLines()
{
	UpdateLockLinesInternal(/*bUseRed=*/false);
}

void AEntityBase::setRedLockLines()
{
	UpdateLockLinesInternal(/*bUseRed=*/true);
}

void AEntityBase::UpdateLockLinesInternal(bool bUseRed)
{
	// Build the current tracked set
	TSet<AEntityBase*> CurrentSet;
	CurrentSet.Reserve(LockedEntitiesList.Num());
	for (const FEntityID LockedEnityID : LockedEntitiesList)
	{
		if (AEntityBase* LockedEntity = EntityManager::GetEntityManagerInstance()->getEntityById(LockedEnityID))
		{
			CurrentSet.Add(LockedEntity);
		}
	}

	const EForceType SelfForce = GetForceType();

	// Decide inclusion based on the UI-selected LockLineType
	auto ShouldInclude = [this, SelfForce](EForceType TargetForce) -> bool
		{
			ELockLineType locktest = EntityManager::GetEntityManagerInstance()->GLockLineType;
			switch (EntityManager::GetEntityManagerInstance()->GLockLineType)
			{
			case ELockLineType::OpposingOnly: return TargetForce != SelfForce;
			case ELockLineType::SameOnly:     return TargetForce == SelfForce;
			case ELockLineType::All:
			default:                          return true;
			}
		};

	if (bUseRed)
	{
		UpdateLockLinesMap<ANiagaraLockLineRedActor>(
			GetWorld(),
			RootComponent,
			CurrentSet,
			RedLockBeams,
			ANiagaraLockLineRedActor::StaticClass(),
			SelfForce,
			this,
			ShouldInclude
		);
	}
	else
	{
		UpdateLockLinesMap<ANiagaraLockLineActor>(
			GetWorld(),
			RootComponent,
			CurrentSet,
			LockBeams,
			ANiagaraLockLineActor::StaticClass(),
			SelfForce,
			this,
			ShouldInclude
		);
	}

	isLockLineDestroyed = false;
}

void AEntityBase::onEntitySpawn() {
	for (int32 i = 0; i < showHideTracker; i++)
	{
		if (i % 10 == 0)
			this->SetActorHiddenInGame(true);
		else
			this->SetActorHiddenInGame(false);

		if (i == 201)
			this->SetActorHiddenInGame(false);
	}

}

void AEntityBase::onEntityDestroy() {

	if (Health == ELocalHealth::DESTROYED) {
		for (int i = 0; i < showHideTrackerOnDestroy; i++)
		{
			if (showHideTrackerOnDestroy % 10 == 0)
				this->SetActorHiddenInGame(true);
			else
				this->SetActorHiddenInGame(false);

			if (showHideTrackerOnDestroy == 101)
				this->SetActorHiddenInGame(false);

		}

	}
}

void AEntityBase::UpdateGroundBeam(float DeltaTime, const FVector& JetLocation)
{
	if (!GroundBeamActor) return;

	const FVector3d LhSeaLevel(this->GeodeticLocation.Y, this->GeodeticLocation.X, 0.0);
	const FVector3d UnrealPos = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(LhSeaLevel);
	const FVector End = UnrealPos;

	if (bApplyGroundBeamConfigEveryTick)
	{
		GroundBeamActor->RingSpacing = GroundRingSpacing;
		GroundBeamActor->RingRadius = GroundRingRadius;
		GroundBeamActor->RingThicknessCm = GroundRingThicknessCm;
		GroundBeamActor->MaxRings = GroundMaxRings;
	}

	GroundBeamActor->SetBeamEndpoints(JetLocation, End);

#if WITH_EDITOR
	static float Accum = 0.f; Accum += DeltaTime;
	if (Accum > 0.25f)
	{
		const float DistanceCm = (End - JetLocation).Size();
		const float DistanceM = DistanceCm / 100.f;
		const float SpacingCm = GroundBeamActor->RingSpacing;
		const int32 PredictedRings = (SpacingCm > KINDA_SMALL_NUMBER)
			? FMath::FloorToInt(DistanceCm / SpacingCm)
			: 0;
		//UE_LOG(LogTemp, Warning, TEXT("BeamLen: %.0f m | Spacing: %.0f cm | Rings: %d"),
		//	DistanceM, SpacingCm, PredictedRings);
		Accum = 0.f;
	}
#endif
}

void AEntityBase::HandleLODs(int id)
{
	UE_LOG(LogTemp, Warning, TEXT("LOD %d"), id);

	for (int i = 0; i < LODParentActors.Num(); i++)
	{
		if (id == i)
		{
			for (AActor* actor : LODsChilds[i])
			{
				actor->SetActorHiddenInGame(false);

			}
		}
		else
		{
			for (AActor* actor : LODsChilds[i])
			{
				actor->SetActorHiddenInGame(true);
			}
		}
	}
}

void AEntityBase::AlignmentToGround()
{

	if (!GlobeAnchor) return;

	ACesiumGeoreference* GeoRef = GlobeAnchor->ResolveGeoreference();
	if (!GeoRef) return;

	if (!CesiumTileset) return;


	FVector3d Carto = GlobeAnchor->GetLongitudeLatitudeHeight();
	double lon = Carto.X;
	double lat = Carto.Y;

	float pi = 3.14;

	float actorRotRad = GetActorRotation().Yaw * (pi / 180);

	FRotator rotation = GetActorRotation();
	FVector  farwordRot = rotation.Vector();
	FVector  rightRot = FRotationMatrix(rotation).GetScaledAxis(EAxis::Y);

	FVector front = GetActorLocation() + farwordRot * 150;
	FVector back = GetActorLocation() - farwordRot * 150;
	FVector left = GetActorLocation() + rightRot * 150;
	FVector right = GetActorLocation() - rightRot * 150;

	FVector frontLL = GeoRef->TransformUnrealPositionToLongitudeLatitudeHeight(front);
	FVector backLL = GeoRef->TransformUnrealPositionToLongitudeLatitudeHeight(back);
	FVector rightLL = GeoRef->TransformUnrealPositionToLongitudeLatitudeHeight(right);
	FVector leftLL = GeoRef->TransformUnrealPositionToLongitudeLatitudeHeight(left);

	TArray<FVector3d> samplePoints =
	{
		frontLL,
		backLL,
		rightLL,
		leftLL
	};

	FHitResult fronthitResult;
	FHitResult backhitResult;
	FHitResult rightResult;
	FHitResult lefthitResult;

	FVector frontendPoint = front - FVector(0, 0, 1000);
	FVector backendPoint = back - FVector(0, 0, 1000);
	FVector rightendPoint = right - FVector(0, 0, 1000);
	FVector leftendPoint = left - FVector(0, 0, 1000);

	FCollisionQueryParams colParams;
	colParams.AddIgnoredActor(this);

	UE_LOG(LogTemp, Error, TEXT("Ht in Ray is F  %f, B %f, R %f, L %f"), fronthitResult.Location.Z, backhitResult.Location.Z, rightResult.Location.Z, lefthitResult.Location.Z);

	FCesiumSampleHeightMostDetailedCallback sCallback;

	sCallback.BindLambda([this, Carto, GeoRef, front,
		back,
		right,
		left]
		(ACesium3DTileset* Tileset, const TArray<FCesiumSampleHeightResult>& Heights, const TArray<FString>& Warnings)
		{
			if (Heights.Num() < 4)return;
			//if (Heights[0].IsSet() || Heights[1].IsSet() || Heights[2].IsSet() || Heights[3].IsSet()) return;

			double HFront = Heights[0].LongitudeLatitudeHeight.Z * 100.0f;
			double HBack = Heights[1].LongitudeLatitudeHeight.Z * 100.0f;
			double HRight = Heights[2].LongitudeLatitudeHeight.Z * 100.0f;
			double HLeft = Heights[3].LongitudeLatitudeHeight.Z * 100.0f;


			float angleXaxis = FMath::RadiansToDegrees(FMath::Atan2(HFront - HBack, 300));
			float angleYaxis = FMath::RadiansToDegrees(FMath::Atan2(HRight - HLeft, 300));
			//UE_LOG(LogTemp, Error, TEXT("angle is X  %f, Y %f"), angleXaxis, angleYaxis);
			//UE_LOG(LogTemp, Error, TEXT("Ht in Cesium is F  %f, B %f, R %f, L %f"), HFront, HBack, HRight, HLeft);

			/*DrawDebugLine(GetWorld(), front, front - FVector(0, 0, HFront), FColor::Green, true, 3.0f, 0, 5.0f);
			DrawDebugLine(GetWorld(), back, back - FVector(0, 0, HBack), FColor::Red, true, 3.0f, 0, 5.0f);
			DrawDebugLine(GetWorld(), right, right - FVector(0, 0, HRight), FColor::Yellow, true, 3.0f, 0, 5.0f);
			DrawDebugLine(GetWorld(), left, left - FVector(0, 0, HLeft), FColor::White, true, 3.0f, 0, 5.0f);*/


			if (ModelParent)
				ModelParent->SetActorRotation(FRotator(angleXaxis, GetActorRotation().Yaw, angleYaxis + 360));

		});

	CesiumTileset->SampleHeightMostDetailed
	(
		samplePoints, sCallback
	);
}


