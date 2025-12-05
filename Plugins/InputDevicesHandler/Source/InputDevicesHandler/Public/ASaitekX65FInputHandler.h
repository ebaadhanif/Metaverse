// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ADevicesHandler.h"
#include "ASaitekX65FInputHandler.generated.h"

UCLASS()
class INPUTDEVICESHANDLER_API AASaitekX65FInputHandler : public AADevicesHandler
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AASaitekX65FInputHandler();
	virtual void BeginPlay() override;
	virtual void CreateInputActions() override;
	virtual void MapKeys() override;

	UPROPERTY()
	UInputAction* IA_Trigger_Press = nullptr;

	UPROPERTY()
	UInputAction* IA_CastleHat_Left_Press = nullptr;
	UPROPERTY()
	UInputAction* IA_CastleHat_Right_Press = nullptr;
	UPROPERTY()
	UInputAction* IA_CastleHat_UP_Press = nullptr;
	UPROPERTY()
	UInputAction* IA_CastleHat_Down_Press = nullptr;

	UPROPERTY()
	UInputAction* IA_BowlHat_Left_Press = nullptr;
	UPROPERTY()
	UInputAction* IA_BowlHat_Right_Press = nullptr;
	UPROPERTY()
	UInputAction* IA_BowlHat_UP_Press = nullptr;
	UPROPERTY()
	UInputAction* IA_BowlHat_Down_Press = nullptr;

	UPROPERTY()
	UInputAction* IA_POVHat_ValueChange = nullptr;

	UPROPERTY()
	UInputAction* IA_HHat_Left_Press = nullptr;
	UPROPERTY()
	UInputAction* IA_HHat_Right_Press = nullptr;
	UPROPERTY()
	UInputAction* IA_HHat_UP_Press = nullptr;
	UPROPERTY()
	UInputAction* IA_HHat_Down_Press = nullptr;

	UPROPERTY()
	UInputAction* IA_Hat4_Left_Press = nullptr;
	UPROPERTY()		  
	UInputAction* IA_Hat4_Right_Press = nullptr;
	UPROPERTY()		  
	UInputAction* IA_Hat4_UP_Press = nullptr;
	UPROPERTY()		  
	UInputAction* IA_Hat4_Down_Press = nullptr;

	UPROPERTY()
	UInputAction* IA_Hat5_Left_Press = nullptr;
	UPROPERTY()		  	
	UInputAction* IA_Hat5_Right_Press = nullptr;
	UPROPERTY()		  	
	UInputAction* IA_Hat5_UP_Press = nullptr;
	UPROPERTY()		  	
	UInputAction* IA_Hat5_Down_Press = nullptr;

	UPROPERTY()
	UInputAction* IA_Hat6_Left_Press = nullptr;
	UPROPERTY()		  	
	UInputAction* IA_Hat6_Right_Press = nullptr;
	UPROPERTY()		  	
	UInputAction* IA_Hat6_UP_Press = nullptr;
	UPROPERTY()		  	
	UInputAction* IA_Hat6_Down_Press = nullptr;

	UPROPERTY()
	UInputAction* IA_Hat7_Left_Press = nullptr;
	UPROPERTY()		  	
	UInputAction* IA_Hat7_Right_Press = nullptr;
	UPROPERTY()		  	
	UInputAction* IA_Hat7_UP_Press = nullptr;
	UPROPERTY()		  	
	UInputAction* IA_Hat7_Down_Press = nullptr;

	UPROPERTY()
	UInputAction* IA_A_Button_Press = nullptr;
	UPROPERTY()
	UInputAction* IA_B_Button_Press = nullptr;
	UPROPERTY()
	UInputAction* IA_FlyingPinkieSwitch_Press = nullptr;
	UPROPERTY()
	UInputAction* IA_Pinkie_Button_Press = nullptr;
	UPROPERTY()
	UInputAction* IA_E_Button_Press = nullptr;
	UPROPERTY()
	UInputAction* IA_F_Button_Press = nullptr;
	UPROPERTY()
	UInputAction* IA_D_Button_Press = nullptr;
	UPROPERTY()
	UInputAction* IA_Rotary_1_ValueChange = nullptr;
	UPROPERTY()
	UInputAction* IA_Rotary_2_ValueChange = nullptr;
	UPROPERTY()
	UInputAction* IA_Slider_ValueChange = nullptr;
	UPROPERTY()
	UInputAction* IA_Throttle_Z_ValueChange = nullptr;

	UPROPERTY()
	UInputAction* IA_Stick_X_ValueChange = nullptr;
	UPROPERTY()
	UInputAction* IA_Stick_Y_ValueChange = nullptr;

	UPROPERTY()
	UInputAction* IA_KSwitch_Down_Press = nullptr;
	UPROPERTY()
	UInputAction* IA_KSwitch_Up_Press = nullptr;

	UPROPERTY()
	UInputAction* IA_MinMouse_X = nullptr;
	UPROPERTY()
	UInputAction* IA_MinMouse_Y = nullptr;

	UPROPERTY()
	UInputAction* IA_ScrollWheel_Forward = nullptr;
	UPROPERTY()
	UInputAction* IA_ScrollWheel_Back = nullptr;



};
