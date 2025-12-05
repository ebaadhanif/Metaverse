// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CameraChannel.h"
#include "LaserTracker.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SYSTEMS_API ULaserTracker : public USceneComponent
{
	GENERATED_BODY()

private:
	int laserCode;
	int sensorRange;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraChannel* sensorOpticalCamera;
public:	
	// Sets default values for this component's properties
	ULaserTracker();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Initialize(UCameraChannel* opticalCamera, int range, int code);
	AActor* Scan();
	bool isInFOV(FVector SensorCameraLoc, FVector SensorCameraForward, FVector TargetLoc);
		
};
