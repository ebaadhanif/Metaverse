#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ADevicesHandler.h"
#include "HtcVIVEInputHandler.generated.h"

UCLASS()
class INPUTDEVICESHANDLER_API AHtcVIVEInputHandler : public AADevicesHandler
{
GENERATED_BODY()

public:
    AHtcVIVEInputHandler();
    virtual void BeginPlay() override;
    virtual void CreateInputActions() override;
    virtual void MapKeys() override;


    UPROPERTY()
    UInputAction* IA_Vive_Right_System_Click;
    UPROPERTY()
    UInputAction* IA_Vive_Right_Grip_Click;
    UPROPERTY()
    UInputAction* IA_Vive_Right_Menu_Click;
    UPROPERTY()
    UInputAction* IA_Vive_Right_Trigger_Click;
    UPROPERTY()
    UInputAction* IA_Vive_Right_Trigger_Axis;
    UPROPERTY()
    UInputAction* IA_Vive_Right_Trackpad_2D;
    UPROPERTY()
    UInputAction* IA_Vive_Right_Trackpad_X;
    UPROPERTY()
    UInputAction* IA_Vive_Right_Trackpad_Y;
    UPROPERTY()
    UInputAction* IA_Vive_Right_Trackpad_Click;
    UPROPERTY()
    UInputAction* IA_Vive_Right_Trackpad_Touch;
    UPROPERTY()
    UInputAction* IA_Vive_Right_Trackpad_Up;
    UPROPERTY()
    UInputAction* IA_Vive_Right_Trackpad_Down;
    UPROPERTY()
    UInputAction* IA_Vive_Right_Trackpad_Left;
    UPROPERTY()
    UInputAction* IA_Vive_Right_Trackpad_Right;




    UPROPERTY()
    UInputAction* IA_Vive_Left_System_Click;
    UPROPERTY()
    UInputAction* IA_Vive_Left_Grip_Click;
    UPROPERTY()
    UInputAction* IA_Vive_Left_Menu_Click;
    UPROPERTY()
    UInputAction* IA_Vive_Left_Trigger_Click;
    UPROPERTY()
    UInputAction* IA_Vive_Left_Trigger_Axis;
    UPROPERTY()
    UInputAction* IA_Vive_Left_Trackpad_2D;
    UPROPERTY()
    UInputAction* IA_Vive_Left_Trackpad_X;
    UPROPERTY()
    UInputAction* IA_Vive_Left_Trackpad_Y;
    UPROPERTY()
    UInputAction* IA_Vive_Left_Trackpad_Click;
    UPROPERTY()
    UInputAction* IA_Vive_Left_Trackpad_Touch;
    UPROPERTY()
    UInputAction* IA_Vive_Left_Trackpad_Up;
    UPROPERTY()
    UInputAction* IA_Vive_Left_Trackpad_Down;
    UPROPERTY()
    UInputAction* IA_Vive_Left_Trackpad_Left;
    UPROPERTY()
    UInputAction* IA_Vive_Left_Trackpad_Right;

};

