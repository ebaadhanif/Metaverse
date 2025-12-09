// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "InputActionValue.h"
#include "../Team SimBridge/EntityManager.h"
#include "LoadingManager.h"
//#include "../Team SimBridge/UModel3DAssetManager.h"

#include "../Team SimBridge/BRITEStarWidget.h"
#include "ISRHUD.h"
#include <ASaitekX65FInputHandler.h>







//#include "GameFramework/InputDeviceId.h"
#include "Camera/CameraComponent.h"
#include "ISRPawn.generated.h"
class UModel3DAssetManager;


USTRUCT(BlueprintType)
struct FSimpleRawInputDeviceHelper
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, Category = "RawInput")
	int32 Handle = 0;
	UPROPERTY(BlueprintReadOnly, Category = "RawInput")
	int32 VenderID = 0;
	UPROPERTY(BlueprintReadOnly, Category = "RawInput")
	int32 ProductID = 0;
	UPROPERTY(BlueprintReadOnly, Category = "RawInput")
    FString DeviceName = "";




};


UCLASS()
class METAVERSE_API AISRPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AISRPawn();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera");
	UCameraComponent* Camera=nullptr;
	void RefreshDevices();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void LogAllHIDDevices();
	UBRITEStarWidget* BRITEStarWidgetRef = nullptr;
	UModel3DAssetManager* obj;
	ALoadingManager* _loadingManager;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void BindSpecificDeviceInputActionsToFunctions();
	void BindX65FInputActionsToFunctions();
	void RotateCamX(const FInputActionValue& Value);
	void RotateCamY(const FInputActionValue& Value);
	void RotateCamXX65FDevice(const FInputActionValue& Value);
	void RotateCamYX65FDevice(const FInputActionValue& Value);
	void ZoomIn(const FInputActionValue& Value);
	void ZoomOut(const FInputActionValue& Value);
	void PrevFOV(const FInputActionValue& Value);
	void NextFOV(const FInputActionValue& Value);
	void SwitchToCageMode(const FInputActionValue& Value);
	void SwitchToStowMode(const FInputActionValue& Value);
	float NormalizeAngleTo360(float Angle);
	void ToggleIRMode(const FInputActionValue& Value);
	void SwitchToTVMode(const FInputActionValue& Value);
	void ToggleLaser(const FInputActionValue& Value);
	void ToggleCameraLock(const FInputActionValue& Value);
	void ToggleLockBox();
	void SetOwnLatLong(const FInputActionValue& Value);
	void UpdateTrgtLatLong();
	void UpdateTargetAltitude();
	void UpdateTargetDistance();
	void SetAzimuthAngle(float camPitch);
	void SetElevationCarret(double PositionX);
	void SetAzimuthCarret(double PositionX);
	void UpdateNortPointer(float Yaw);
	void SetLOSStrip(double Position);
	void SetLOS(double LOS);
	float MapAngleToRange(float AngleDegrees);
	float MapAngleToRangeLeftRight(float AngleDegrees,float Left, float Right);
	float MapAngleToRangeTopBottom(float AngleDegrees, float Top, float Bottom);
	void UpdateAzimuth();
	void  CalculateAzimuth(float InputValue);
	void CalculateElevation(float InputValue);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void UpdateIRTexture();
	APlayerController* PlayerControllerRef = nullptr;

	float Yaw = -90;
	float Pitch = 0;
	float FOV = 0.0f;
	double Latitute=0.0f;
	double Longitude = 0.0f;

	float AzimuthAngle=0.0f;
	float ElevationAngle = 0.0f;
	float LOSValue = 0;
	
	float CarretPositionX = 440.0f;
	float HeadingStripPositionX = -57.0f;
	float ElevCarretPositionY = 559.0f;
	float ElvCarretPositionY = 0.0f;
	bool Forward = true;
	float UperLimit = 0;
	float LeftX;
	float RightX;
	float TopY;
	float BottomY;
	float StripLeftX;
	float StripRightX;
	float CamSpeed = 1.0f;
	bool Intrpt = true;
	bool LckBoxVisible = true;
	FVector2D Size;
	FVector2D StripSize;
	FVector2D Position;
	FVector2D azimuthBarMinus180Position;
	FVector2D azimuthBarPlus180Position;

	FVector2D StripPosition;
	UPROPERTY()
	UMaterialInterface* IRMaterial = nullptr;
	UPROPERTY()
	UMaterialInstanceDynamic* IRMaterialInstance = nullptr;
	bool isWHot = true;
	UModel3DAssetManager* _uModel3DAssetManager;
};
