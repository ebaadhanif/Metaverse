// Fill out your copyright notice in the Description page of Project Settings.


#include "RemoteVegetation.h"

// Sets default values
ARemoteVegetation::ARemoteVegetation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isGroundEntity = true;
	GroundClamp = true;
}

// Called when the game starts or when spawned
void ARemoteVegetation::BeginPlay()
{
	Super::BeginPlay();
	RemoteEntityType = ERemoteEntityType::VEGETATION;
}

// Called every frame
void ARemoteVegetation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

