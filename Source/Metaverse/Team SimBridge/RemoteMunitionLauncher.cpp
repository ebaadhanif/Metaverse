// Fill out your copyright notice in the Description page of Project Settings.


#include "RemoteMunitionLauncher.h"

// Sets default values
ARemoteMunitionLauncher::ARemoteMunitionLauncher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isGroundEntity = true;
	GroundClamp = true;
}

// Called when the game starts or when spawned
void ARemoteMunitionLauncher::BeginPlay()
{
	Super::BeginPlay();
	RemoteEntityType = ERemoteEntityType::MUNITION_LAUNCHER;

}

// Called every frame
void ARemoteMunitionLauncher::Tick(float DeltaTime)
{
	    Super::Tick(DeltaTime);
		FEntityState entityState;
		entityState = EntityManager::GetEntityManagerInstance()->UpdateEntity(EntityId);
		SetEntityState(entityState);

		//if (WidgetComponent)
		//{
		//	APlayerController* PC = GetWorld()->GetFirstPlayerController();
		//	if (PC && PC->PlayerCameraManager)
		//	{
		//		FVector CameraLoc = PC->PlayerCameraManager->GetCameraLocation();
		//		LabelManager::UpdateLabelFacingCamera(this, CameraLoc);
		//		//LabelManager::UpdateWidgetScale(CameraLoc);

		//	}
		//}
	
}

