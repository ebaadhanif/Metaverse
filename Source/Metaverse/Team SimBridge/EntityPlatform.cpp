// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityPlatform.h"

// Sets default values
AEntityPlatform::AEntityPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEntityPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEntityPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

