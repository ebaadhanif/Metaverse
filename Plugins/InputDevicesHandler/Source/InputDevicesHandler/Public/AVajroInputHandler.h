#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ADevicesHandler.h"
#include "AVajroInputHandler.generated.h"

UCLASS()
class INPUTDEVICESHANDLER_API AAVajroInputHandler : public AADevicesHandler
{
	GENERATED_BODY()
	
public:
    AAVajroInputHandler();
    virtual void BeginPlay() override;
    virtual void CreateInputActions() override;
    virtual void MapKeys() override;
    // LEFT //
    UPROPERTY()
    UInputAction* IA_VarjoController_Left_A_Click;
    UPROPERTY()
    UInputAction* IA_VarjoController_Left_B_Click;
    UPROPERTY()
    UInputAction* IA_VarjoController_Left_A_Touch;
    UPROPERTY()
    UInputAction* IA_VarjoController_Left_B_Touch;
    UPROPERTY()
    UInputAction* IA_VarjoController_Left_System_Click;
    UPROPERTY()
    UInputAction* IA_VarjoController_Left_Grip_Click;
    UPROPERTY()
    UInputAction* IA_VarjoController_Left_Grip_Touch;
    UPROPERTY()
    UInputAction* IA_VarjoController_Left_Trigger_Touch;
    UPROPERTY()
    UInputAction* IA_VarjoController_Left_Trigger_Axis;
    UPROPERTY()
    UInputAction* IA_VarjoController_Left_Thumbstick_X;
    UPROPERTY()
    UInputAction* IA_VarjoController_Left_Thumbstick_Y;
    UPROPERTY()
    UInputAction* IA_VarjoController_Left_Thumbstick_2D;
    UPROPERTY()
    UInputAction* IA_VarjoController_Left_Thumbstick_Click;
    UPROPERTY()
    UInputAction* IA_VarjoController_Left_Thumbstick_Touch;
    // RIGHT // 
    UPROPERTY()
    UInputAction* IA_VarjoController_Right_A_Click;
    UPROPERTY()
    UInputAction* IA_VarjoController_Right_B_Click;
    UPROPERTY()
    UInputAction* IA_VarjoController_Right_A_Touch;
    UPROPERTY()
    UInputAction* IA_VarjoController_Right_B_Touch;
    UPROPERTY()
    UInputAction* IA_VarjoController_Right_System_Click;
    UPROPERTY()
    UInputAction* IA_VarjoController_Right_Grip_Click;
    UPROPERTY()
    UInputAction* IA_VarjoController_Right_Grip_Touch;
    UPROPERTY()
    UInputAction* IA_VarjoController_Right_Trigger_Touch;
    UPROPERTY()
    UInputAction* IA_VarjoController_Right_Trigger_Axis;
    UPROPERTY()
    UInputAction* IA_VarjoController_Right_Thumbstick_X;
    UPROPERTY()
    UInputAction* IA_VarjoController_Right_Thumbstick_Y;
    UPROPERTY()
    UInputAction* IA_VarjoController_Right_Thumbstick_2D;
    UPROPERTY()
    UInputAction* IA_VarjoController_Right_Thumbstick_Click;
    UPROPERTY()
    UInputAction* IA_VarjoController_Right_Thumbstick_Touch;


    // Creating Keys as Varjo Keys cant be directly accessed using EKeys , adding the Varjo XR Plugin give support for varjo controller keys but still we cant acces these keys using "EKeys::" , so we explicitly create them using the exaxt name as defined in VarjoController.cpp
    // Left
    FKey VarjoController_Left_A_Click = FKey(FName("VarjoController_Left_A_Click"));
    FKey VarjoController_Left_B_Click = FKey(FName("VarjoController_Left_B_Click"));
    FKey VarjoController_Left_A_Touch = FKey(FName("VarjoController_Left_A_Touch"));
    FKey VarjoController_Left_B_Touch = FKey(FName("VarjoController_Left_B_Touch"));
    FKey VarjoController_Left_System_Click = FKey(FName("VarjoController_Left_System_Click"));
    FKey VarjoController_Left_Grip_Click = FKey(FName("VarjoController_Left_Grip_Click"));
    FKey VarjoController_Left_Grip_Touch = FKey(FName("VarjoController_Left_Grip_Touch"));
    FKey VarjoController_Left_Trigger_Touch = FKey(FName("VarjoController_Left_Trigger_Touch"));
    FKey VarjoController_Left_Trigger_Axis = FKey(FName("VarjoController_Left_Trigger_Axis"));
    FKey VarjoController_Left_Thumbstick_X = FKey(FName("VarjoController_Left_Thumbstick_X"));
    FKey VarjoController_Left_Thumbstick_Y = FKey(FName("VarjoController_Left_Thumbstick_Y"));
    FKey VarjoController_Left_Thumbstick_2D = FKey(FName("VarjoController_Left_Thumbstick_2D"));
    FKey VarjoController_Left_Thumbstick_Click = FKey(FName("VarjoController_Left_Thumbstick_Click"));
    FKey VarjoController_Left_Thumbstick_Touch = FKey(FName("VarjoController_Left_Thumbstick_Touch"));

    //Right
    FKey VarjoController_Right_A_Click = FKey(FName("VarjoController_Right_A_Click"));
    FKey VarjoController_Right_B_Click = FKey(FName("VarjoController_Right_B_Click"));
    FKey VarjoController_Right_A_Touch = FKey(FName("VarjoController_Right_A_Touch"));
    FKey VarjoController_Right_B_Touch = FKey(FName("VarjoController_Right_B_Touch"));
    FKey VarjoController_Right_System_Click = FKey(FName("VarjoController_Right_System_Click"));
    FKey VarjoController_Right_Grip_Click = FKey(FName("VarjoController_Right_Grip_Click"));
    FKey VarjoController_Right_Grip_Touch = FKey(FName("VarjoController_Right_Grip_Touch"));
    FKey VarjoController_Right_Trigger_Touch = FKey(FName("VarjoController_Right_Trigger_Touch"));
    FKey VarjoController_Right_Trigger_Axis = FKey(FName("VarjoController_Right_Trigger_Axis"));
    FKey VarjoController_Right_Thumbstick_X = FKey(FName("VarjoController_Right_Thumbstick_X"));
    FKey VarjoController_Right_Thumbstick_Y = FKey(FName("VarjoController_Right_Thumbstick_Y"));
    FKey VarjoController_Right_Thumbstick_2D = FKey(FName("VarjoController_Right_Thumbstick_2D"));
    FKey VarjoController_Right_Thumbstick_Click = FKey(FName("VarjoController_Right_Thumbstick_Click"));
    FKey VarjoController_Right_Thumbstick_Touch = FKey(FName("VarjoController_Right_Thumbstick_Touch"));
};
