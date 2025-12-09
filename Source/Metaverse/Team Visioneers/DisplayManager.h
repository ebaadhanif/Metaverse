// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "xmlfile.h"
#include "../Public/FreeCameraPawn.h"
#include "MetaverseXRInputManager.h"
#include "DisplayManager.generated.h"

UCLASS()
class METAVERSE_API ADisplayManager : public AActor
{
	GENERATED_BODY()

public:
	double HeightOfCamera = 0;

	struct DisplayStruct
	{
		int32 fov;
		int32 camAngle;
		int32 height;
		int32 width;
		int32 targetDisplay;
		int32 fullScreenType;
		bool active;
	};
	// Sets default values for this actor's properties
	ADisplayManager();
	AHanTracking* HandTrackingActor = nullptr;
	AControllerTracking* ControllerTrackingActor = nullptr;
	AMetaverseXRInputManager* MetaverseXRInputManager = nullptr;
	FString DisplayMode = "";
	FString AllowDisplayModeChange = "";
	TArray<DisplayStruct> Displays;
	static ADisplayManager* GetInstance();
	FVector CameraLocation;
	APlayerController* PC;
	AFreeCameraPawn* FreeCamPawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void LoadDisplayConfigurations(const FString& ConfigFilePath);

	bool isVRMode;

private:
	FString XmlFilePath = FPaths::ProjectDir() + TEXT("Content/Archive/DisplayConfigs.xml");
	static ADisplayManager* Instance;

};
