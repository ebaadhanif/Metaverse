// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserTracker.h"

// Sets default values for this component's properties
ULaserTracker::ULaserTracker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULaserTracker::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULaserTracker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULaserTracker::Initialize(UCameraChannel* opticalCamera, int range, int code)
{
	sensorOpticalCamera = opticalCamera;
	sensorRange = range;
	laserCode = code;
}

AActor* ULaserTracker::Scan()
{
	AActor* laserSpot = nullptr;
	UWorld* world = GetWorld();
	if (!world || !sensorOpticalCamera)
		return nullptr;

	FVector SensorCameraLoc = sensorOpticalCamera->GetCameraComponent()->GetComponentLocation();
	FVector SensorCameraForward = sensorOpticalCamera->GetCameraComponent()->GetForwardVector();

	TArray<AActor*>AllFoundActorsArray;
	UGameplayStatics::GetAllActorsOfClass(world, AActor::StaticClass(), AllFoundActorsArray);

	for (AActor* Actor : AllFoundActorsArray)
	{
		FVector actorLoc = Actor->GetActorLocation();
		float distanceOfActor = FVector::DistSquared(SensorCameraLoc, actorLoc);

		if (distanceOfActor <= sensorRange)
		{
			//if laserCode==ActorCode 

			bool bInFOV = isInFOV(SensorCameraLoc, SensorCameraForward, actorLoc);
			if (bInFOV)
			{
				laserSpot = Actor;
			}

		}
	}
	return laserSpot;
}

bool ULaserTracker::isInFOV(FVector SensorCameraLoc, FVector SensorCameraForward, FVector TargetLoc)
{
	FVector ToTarget = TargetLoc - SensorCameraLoc;
	if (!ToTarget.Normalize())
	{
		return true; //basically same location
	}

	float DotProduct = FVector::DotProduct(SensorCameraForward, ToTarget);
	float HalfFOVRad = FMath::DegreesToRadians(sensorOpticalCamera->GetcurrentFOV()*0.5f);
	float CosHalfFOV = FMath::Cos(HalfFOVRad);


	return DotProduct>=CosHalfFOV;
}

