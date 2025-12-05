// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Interfaces/IPluginManager.h"
#include "LaserRanging.generated.h"

#define KM_TO_CM 100000;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SYSTEMS_API ULaserRanging : public USceneComponent
{
	GENERATED_BODY()

private:
	FString Title;
	int laserRange;
	bool bIsActive;
	FRotator Rotation;
	FVector Position;
	float RangeError = 1.6f;
public:
	// Sets default values for this component's properties
	ULaserRanging();
	void Initialize();
	void Initialize(int range, FRotator rotation, FVector position);
	int Activate();
	FString GetTitle() { return Title; }
	int GetLaserRange() { return laserRange; }
	bool GetIsActive() { return bIsActive; }
	FRotator GetRotation() { return Rotation; }
	FVector GetPosition() { return Position; }
	void GetDefaultValuesFromXML(FString title);
	int CalculateError(float Dist);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
