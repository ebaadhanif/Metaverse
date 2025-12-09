// Fill out your copyright notice in the Description page of Project Settings.


#include "RemoteHuman.h"
#include "../Team Visioneers/ScalingManager.h"

// Sets default values
ARemoteHuman::ARemoteHuman()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isGroundEntity = true;
	GroundClamp = true;
}

// Called when the game starts or when spawned
void ARemoteHuman::BeginPlay()
{
	Super::BeginPlay();
	RemoteEntityType = ERemoteEntityType::HUMAN;
}

// Called every frame
void ARemoteHuman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FEntityState entityState;
	entityState = EntityManager::GetEntityManagerInstance()->UpdateEntity(EntityId);
	SetEntityState(entityState);

	/*if (WidgetComponent)
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if (PC && PC->PlayerCameraManager)
		{
			FVector CameraLoc = PC->PlayerCameraManager->GetCameraLocation();
			LabelManager::UpdateLabelFacingCamera(this, CameraLoc);
			LabelManager::UpdateWidgetScale(CameraLoc);
			AScalingManager::GetInstance()->ScaleActorBasedOnDistance(this, EActorType::Type1, CameraLoc);
		}
	}
	UpdateBillboardSize();*/




}

