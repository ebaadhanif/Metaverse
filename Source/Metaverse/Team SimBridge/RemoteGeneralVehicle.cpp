// Fill out your copyright notice in the Description page of Project Settings.


#include "RemoteGeneralVehicle.h"

// Sets default values
ARemoteGeneralVehicle::ARemoteGeneralVehicle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isGroundEntity = true;
	GroundClamp = true;
}

// Called when the game starts or when spawned
void ARemoteGeneralVehicle::BeginPlay()
{
	Super::BeginPlay();
	RemoteEntityType = ERemoteEntityType::GENERAL_VEHICLE;
}

// Called every frame
void ARemoteGeneralVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FEntityState entityState;
	entityState = EntityManager::GetEntityManagerInstance()->UpdateEntity(EntityId);
	SetEntityState(entityState);
	/*
	if (WidgetComponent)
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if (PC && PC->PlayerCameraManager)
		{
			FVector CameraLoc = PC->PlayerCameraManager->GetCameraLocation();
			LabelManager::UpdateLabelFacingCamera(this, CameraLoc);
			//LabelManager::UpdateWidgetScale(CameraLoc);

		}
	}
	UpdateBillboardSize();*/

}

