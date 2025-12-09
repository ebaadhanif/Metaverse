// Fill out your copyright notice in the Description page of Project Settings.


#include "RemoteArmoredVehicle.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include <Metaverse/Team RenderStorm/ModeManager.h>

// Sets default values
ARemoteArmoredVehicle::ARemoteArmoredVehicle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isGroundEntity = true;
	GroundClamp = true;

	//static ConstructorHelpers::FObjectFinder<UNiagaraSystem> BeamSysAsset(TEXT("/Game/VigilanteContent/Vehicles/West_Tank_M1A1Abrams/FX/Dust_.Dust_"));
	//if (BeamSysAsset.Succeeded())
	//{
	//	DustSystemLeft = BeamSysAsset.Object;
	//	DustSystemRight = BeamSysAsset.Object;
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Error, TEXT("Failed to load Beam Niagara System"));
	//}


	//static ConstructorHelpers::FObjectFinder<UNiagaraSystem> BeamSysDestroyAsset(TEXT("/Game/VigilanteContent/Vehicles/West_Tank_M1A1Abrams/FX/EntityDestroy.EntityDestroy"));
	//if (BeamSysDestroyAsset.Succeeded())
	//{
	//	DestroyNiagaraSystem = BeamSysDestroyAsset.Object;
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Error, TEXT("Failed to load Beam Niagara System"));
	//}

	//static ConstructorHelpers::FObjectFinder<UNiagaraSystem> BeamSysFireAsset(TEXT("/Game/VigilanteContent/Vehicles/West_Tank_M1A1Abrams/FX/FireEffect.FireEffect")); 
	//if (BeamSysFireAsset.Succeeded())
	//{
	//	FireNiagaraSystem = BeamSysFireAsset.Object;
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Error, TEXT("Failed to load Beam Niagara System"));
	//}
}



// Called when the game starts or when spawned
void ARemoteArmoredVehicle::BeginPlay()
{
	Super::BeginPlay();
	RemoteEntityType = ERemoteEntityType::ARMORED_VEHICLE;
	if (UAudioComponent** Found = SoundRegistry.Find(FName("Entity_Sound")))
	{
		if (UAudioComponent* Comp = *Found) {
			EntitySound = Comp;
		}
	}

	spawnAndAttachDust();

}

void ARemoteArmoredVehicle::spawnAndAttachDust()
{
	/*if (!DustSystemLeft || !DustSystemRight)
	{
		UE_LOG(LogTemp, Error, TEXT("Niagara System not assigned"));
		return;
	}
	FVector relativeOffsetRight(150.f, 130.f, -10.f);
	FVector relativeOffsetLeft(150.f, -130.f, -10.f);
	FVector relativeOffsetTop(-30.f, 0.f, 150.f);
	FVector relativeOffsetFire(550.f, 0.f, 200.f);*/

	//DustCompLeft = UNiagaraFunctionLibrary::SpawnSystemAttached(DustSystemLeft, GetRootComponent(), NAME_None, relativeOffsetLeft, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, false);
	//DustCompRight = UNiagaraFunctionLibrary::SpawnSystemAttached(DustSystemRight, GetRootComponent(), NAME_None, relativeOffsetRight, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, false);
	//DestroNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(DestroyNiagaraSystem, GetRootComponent(), NAME_None, relativeOffsetTop, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, false);
	//FireNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(FireNiagaraSystem, GetRootComponent(), NAME_None, relativeOffsetFire, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, true);
	//if (DustCompLeft && DustCompRight)
	//{
	//	DustCompLeft->SetAutoActivate(true);
	//	DustCompRight->SetAutoActivate(true);
	//	DestroNiagaraComponent->SetAutoActivate(true);
	//	UE_LOG(LogTemp, Error, TEXT("Niagara System assigned"));
	//}
	//if (FireNiagaraComponent)
	//{
	//	FireNiagaraComponent->SetAutoActivate(true);
	//}
}

// Called every frame
void ARemoteArmoredVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FEntityState entityState;
	entityState = EntityManager::GetEntityManagerInstance()->UpdateEntity(EntityId);
	SetEntityState(entityState);

	//if (!DustCompLeft || !DustCompRight || !DestroNiagaraComponent)
	//{
	//	spawnAndAttachDust();
	//}


	//if (DustCompLeft && DustCompRight)
	//{
	//	if (this->speedInKnots > 1)
	//	{
	//		DustCompLeft->SetAutoActivate(true);
	//		DustCompRight->SetAutoActivate(true);
	//		DustCompLeft->SetActive(true);
	//		DustCompRight->SetActive(true);
	//		DustCompLeft->Activate();
	//		DustCompRight->Activate();
	//	}
	//	else {
	//		DustCompLeft->SetAutoActivate(false);
	//		DustCompRight->SetAutoActivate(false);
	//		DustCompLeft->SetActive(false);
	//		DustCompRight->SetActive(false);
	//		DustCompLeft->Deactivate();
	//		DustCompRight->Deactivate();
	//	}
	//}



	//if (DestroNiagaraComponent)
	//{
	//	if (this->GetHealth() == ELocalHealth::DESTROYED)
	//	{
	//		DestroNiagaraComponent->SetAutoActivate(true);
	//		DestroNiagaraComponent->SetActive(true);
	//	}
	//	else {
	//		DestroNiagaraComponent->SetActive(false);
	//	}
	//}

	/*
	if (WidgetComponent)
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if (PC && PC->PlayerCameraManager)
		{
			FVector CameraLoc = PC->PlayerCameraManager->GetCameraLocation();
			LabelManager::UpdateLabelFacingCamera(this, CameraLoc);
			LabelManager::UpadteLabelScaleBasedOnDistance(this);

		}
	}
	UpdateBillboardSize();*/


	/*UpdateModelOnHealth();
	if (!bisBattlespaceModeEnabled && !bisDestroyed)
	{
		float distance = FVector::Dist(GetActorLocation(), CameraManager->GetCameraLocation());
		if (distance <= 5000 && bisOnLOD1)
		{
			bisOnLOD0 = true;
			bisOnLOD1 = false;
			ShowLOD0Actors();
		}
		else if (distance > 5000 && bisOnLOD0)
		{
			bisOnLOD0 = false;
			bisOnLOD1 = true;
			ShowLOD1Actors();
		}

	}*/


	if (UNiagaraComponent** Found = EffectsRegistry.Find(FName("fx_tchdwn1")))
	{
		if (UNiagaraComponent* Comp = *Found) {
			if ((this->speedInKnots > 1) && AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::VisualGraphics).FeatureActive)
			{	
				Comp->SetActive(true);
			}
			else {
				Comp->SetActive(false);
			}
		}
	}

	if (UNiagaraComponent** Found = EffectsRegistry.Find(FName("fx_tchdwn2")))
	{
		if (UNiagaraComponent* Comp = *Found) {
			if ((this->speedInKnots > 1) && AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::VisualGraphics).FeatureActive)
			{
				Comp->SetActive(true);
			}
			else {
				Comp->SetActive(false);
			}
		}
	}

	if (UNiagaraComponent** Found = EffectsRegistry.Find(FName("EntityDestroy")))
	{
		if (UNiagaraComponent* Comp = *Found) {
			if ((this->GetHealth() == ELocalHealth::DESTROYED) && AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::VisualGraphics).FeatureActive)
			{
				Comp->SetActive(true);
			}
			else {
				Comp->SetActive(false);
			}
		}
	}


}

