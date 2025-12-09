// Fill out your copyright notice in the Description page of Project Settings.


#include "RemoteStructure.h"

// Sets default values
ARemoteStructure::ARemoteStructure()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isGroundEntity = true;

}

// Called when the game starts or when spawned
void ARemoteStructure::BeginPlay()
{
	Super::BeginPlay();
	RemoteEntityType = ERemoteEntityType::STRUCTURE;

}

// Called every frame
void ARemoteStructure::Tick(float DeltaTime)
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

