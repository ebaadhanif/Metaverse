// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Camera/CameraComponent.h>
#include <Kismet/GameplayStatics.h>
#include "Interfaces/IPluginManager.h"

#include "CameraChannel.generated.h"

struct CameraData
{
	FString Title;
	TArray<float> FOVs;
	FVector Position = FVector(0);
	FRotator Rotation = FRotator(0);
	float FarPlane = 0;
	float NearPlane = 0;
	float BlurIntensity = 0;
};
UCLASS()
class SYSTEMS_API UCameraChannel :public UCameraComponent
{
	GENERATED_BODY()

private:
	FString Title;
	TArray<float> FOVData;
	TArray<CameraData> CamerasData;
	float farPlane = 1000;
	float nearPlane = 1;
	float blurIntensity = 0;
	float currentFOV = 60;

	FVector camPosition = FVector(0);
	FRotator camRotation = FRotator(0);

protected:
	UPROPERTY()
	UMaterialInstanceDynamic* IRMaterialInstanceTest;


public:



public:
	UCameraChannel();
	~UCameraChannel();

	virtual void Initialize(AActor* actor) ;
	virtual void Initialize(AActor* actor, TArray<float> fovArr, float fPlane, float nPlane, float blurValue, FVector pos, FRotator rot);
	void ZoomOut();
	void ZoomIn();
	void PrevFOV();
	void NextFOV();
	void IncBlur();
	void DecBlur();
	UCameraComponent* GetCameraComponent();
	float GetcurrentFOV() { return currentFOV; };

private:
	void SetupCameraComponent(AActor* actor);
	void AssignData(int n);
	void AssignDataToCamera();
	void ReadXmlFile();
	void SetFOVDataToCamera(float);
	int FindNearestFovFromArray(float cFov);
	UCameraComponent* CreateCameraComponent(AActor* actor);
	TArray<FString> GetTagValues(FString& Source, FString Tag);

protected:
	void CreateIRMaterialInstance();

};
