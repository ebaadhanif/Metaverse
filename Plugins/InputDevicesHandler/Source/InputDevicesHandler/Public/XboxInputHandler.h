// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ADevicesHandler.h"
#include "XboxInputHandler.generated.h"

UCLASS()
class INPUTDEVICESHANDLER_API AXboxInputHandler : public AADevicesHandler
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXboxInputHandler();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void CreateInputActions() override;
	virtual void MapKeys() override;
	~AXboxInputHandler();

	//Right ThumbStick
	UPROPERTY()
	UInputAction* IA_Gamepad_Right_Thumbstick_X = nullptr;
	UPROPERTY()
	UInputAction* IA_Gamepad_Right_Thumbstick_Y = nullptr;

	//Left ThumbStick
	UPROPERTY()
	UInputAction* IA_Gamepad_Left_Thumbstick_Y = nullptr;
	UPROPERTY()
	UInputAction* IA_Gamepad_Left_Thumbstick_X = nullptr;

	//D-pad
	UPROPERTY()
	UInputAction* IA_Gamepad_Dpad_Right = nullptr;
	UPROPERTY()
	UInputAction* IA_Gamepad_Dpad_Left = nullptr;
	UPROPERTY()
	UInputAction* IA_Gamepad_Dpad_Up = nullptr;
	UPROPERTY()
	UInputAction* IA_Gamepad_Dpad_Down = nullptr;

	//Face Button
	UPROPERTY()
	UInputAction* IA_Gamepad_Face_Button_Right = nullptr;
	UPROPERTY()
	UInputAction* IA_Gamepad_Face_Button_Left = nullptr;
	UPROPERTY()
	UInputAction* IA_Gamepad_Face_Button_Top = nullptr;
	UPROPERTY()
	UInputAction* IA_Gamepad_Face_Button_Bottom = nullptr;

	//Shoulder
	UPROPERTY()
	UInputAction* IA_Gamepad_Right_Shoulder = nullptr;
	UPROPERTY()
	UInputAction* IA_Gamepad_Left_Shoulder = nullptr;

	//Special Buttons
	UPROPERTY()
	UInputAction* IA_Gamepad_Special_Right = nullptr;
	UPROPERTY()
	UInputAction* IA_Gamepad_Special_Left = nullptr;

	//Trigger Axis
	UPROPERTY()
	UInputAction* IA_Gamepad_Right_Trigger_Axis = nullptr;
	UPROPERTY()
	UInputAction* IA_Gamepad_Left_Trigger_Axis = nullptr;

};
