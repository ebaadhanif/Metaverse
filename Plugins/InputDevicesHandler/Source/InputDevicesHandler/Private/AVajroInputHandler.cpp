#include "AVajroInputHandler.h"

AAVajroInputHandler::AAVajroInputHandler()
{
    CreateInputActions();
}

void AAVajroInputHandler::BeginPlay()
{
    Super::BeginPlay();
    MapKeys();
}

void AAVajroInputHandler::CreateInputActions()
{
    // LEFT//
    if (!IA_VarjoController_Left_A_Click)
    {
        IA_VarjoController_Left_A_Click = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Left_A_Click"));
        IA_VarjoController_Left_A_Click->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_VarjoController_Left_B_Click)
    {
        IA_VarjoController_Left_B_Click = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Left_B_Click"));
        IA_VarjoController_Left_B_Click->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_VarjoController_Left_A_Touch)
    {
        IA_VarjoController_Left_A_Touch = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Left_A_Touch"));
        IA_VarjoController_Left_A_Touch->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_VarjoController_Left_B_Touch)
    {
        IA_VarjoController_Left_B_Touch = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Left_B_Touch"));
        IA_VarjoController_Left_B_Touch->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_VarjoController_Left_System_Click)
    {
        IA_VarjoController_Left_System_Click = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Left_System_Click"));
        IA_VarjoController_Left_System_Click->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_VarjoController_Left_Grip_Click)
    {
        IA_VarjoController_Left_Grip_Click = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Left_Grip_Click"));
        IA_VarjoController_Left_Grip_Click->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_VarjoController_Left_Grip_Touch)
    {
        IA_VarjoController_Left_Grip_Touch = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Left_Grip_Touch"));
        IA_VarjoController_Left_Grip_Touch->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_VarjoController_Left_Trigger_Touch)
    {
        IA_VarjoController_Left_Trigger_Touch = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Left_Trigger_Touch"));
        IA_VarjoController_Left_Trigger_Touch->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_VarjoController_Left_Trigger_Axis)
    {
        IA_VarjoController_Left_Trigger_Axis = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Left_Trigger_Axis"));
        IA_VarjoController_Left_Trigger_Axis->ValueType = EInputActionValueType::Axis1D;
    }
    if (!IA_VarjoController_Left_Thumbstick_X)
    {
        IA_VarjoController_Left_Thumbstick_X = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Left_Thumbstick_X"));
        IA_VarjoController_Left_Thumbstick_X->ValueType = EInputActionValueType::Axis1D;
    }
    if (!IA_VarjoController_Left_Thumbstick_Y)
    {
        IA_VarjoController_Left_Thumbstick_Y = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Left_Thumbstick_Y"));
        IA_VarjoController_Left_Thumbstick_Y->ValueType = EInputActionValueType::Axis1D;
    }
    if (!IA_VarjoController_Left_Thumbstick_2D)
    {
        IA_VarjoController_Left_Thumbstick_2D = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Left_Thumbstick_2D"));
        IA_VarjoController_Left_Thumbstick_2D->ValueType = EInputActionValueType::Axis2D;
    }
    if (!IA_VarjoController_Left_Thumbstick_Click)
    {
        IA_VarjoController_Left_Thumbstick_Click = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Left_Thumbstick_Click"));
        IA_VarjoController_Left_Thumbstick_Click->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_VarjoController_Left_Thumbstick_Touch)
    {
        IA_VarjoController_Left_Thumbstick_Touch = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Left_Thumbstick_Touch"));
        IA_VarjoController_Left_Thumbstick_Touch->ValueType = EInputActionValueType::Boolean;
    }

    // RIGHT // 
    if (!IA_VarjoController_Right_A_Click)
    {
        IA_VarjoController_Right_A_Click = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Right_A_Click"));
        IA_VarjoController_Right_A_Click->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_VarjoController_Right_B_Click)
    {
        IA_VarjoController_Right_B_Click = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Right_B_Click"));
        IA_VarjoController_Right_B_Click->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_VarjoController_Right_A_Touch)
    {
        IA_VarjoController_Right_A_Touch = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Right_A_Touch"));
        IA_VarjoController_Right_A_Touch->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_VarjoController_Right_B_Touch)
    {
        IA_VarjoController_Right_B_Touch = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Right_B_Touch"));
        IA_VarjoController_Right_B_Touch->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_VarjoController_Right_System_Click)
    {
        IA_VarjoController_Right_System_Click = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Right_System_Click"));
        IA_VarjoController_Right_System_Click->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_VarjoController_Right_Grip_Click)
    {
        IA_VarjoController_Right_Grip_Click = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Right_Grip_Click"));
        IA_VarjoController_Right_Grip_Click->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_VarjoController_Right_Grip_Touch)
    {
        IA_VarjoController_Right_Grip_Touch = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Right_Grip_Touch"));
        IA_VarjoController_Right_Grip_Touch->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_VarjoController_Right_Trigger_Touch)
    {
        IA_VarjoController_Right_Trigger_Touch = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Right_Trigger_Touch"));
        IA_VarjoController_Right_Trigger_Touch->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_VarjoController_Right_Trigger_Axis)
    {
        IA_VarjoController_Right_Trigger_Axis = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Right_Trigger_Axis"));
        IA_VarjoController_Right_Trigger_Axis->ValueType = EInputActionValueType::Axis1D;
    }
    if (!IA_VarjoController_Right_Thumbstick_X)
    {
        IA_VarjoController_Right_Thumbstick_X = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Right_Thumbstick_X"));
        IA_VarjoController_Right_Thumbstick_X->ValueType = EInputActionValueType::Axis1D;
    }
    if (!IA_VarjoController_Right_Thumbstick_Y)
    {
        IA_VarjoController_Right_Thumbstick_Y = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Right_Thumbstick_Y"));
        IA_VarjoController_Right_Thumbstick_Y->ValueType = EInputActionValueType::Axis1D;
    }
    if (!IA_VarjoController_Right_Thumbstick_2D)
    {
        IA_VarjoController_Right_Thumbstick_2D = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Right_Thumbstick_2D"));
        IA_VarjoController_Right_Thumbstick_2D->ValueType = EInputActionValueType::Axis2D;
    }
    if (!IA_VarjoController_Right_Thumbstick_Click)
    {
        IA_VarjoController_Right_Thumbstick_Click = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Right_Thumbstick_Click"));
        IA_VarjoController_Right_Thumbstick_Click->ValueType = EInputActionValueType::Boolean;
    }
    if (!IA_VarjoController_Right_Thumbstick_Touch)
    {
        IA_VarjoController_Right_Thumbstick_Touch = CreateDefaultSubobject<UInputAction>(TEXT("IA_VarjoController_Right_Thumbstick_Touch"));
        IA_VarjoController_Right_Thumbstick_Touch->ValueType = EInputActionValueType::Boolean;
    }

}

void AAVajroInputHandler::MapKeys()
{
    //LEFT//
    MappingContext->MapKey(IA_VarjoController_Left_A_Click, VarjoController_Left_A_Click);
    MappingContext->MapKey(IA_VarjoController_Left_B_Click, VarjoController_Left_B_Click);
    MappingContext->MapKey(IA_VarjoController_Left_A_Touch, VarjoController_Left_A_Touch);
    MappingContext->MapKey(IA_VarjoController_Left_B_Touch, VarjoController_Left_B_Touch);
    MappingContext->MapKey(IA_VarjoController_Left_System_Click, VarjoController_Left_System_Click);
    MappingContext->MapKey(IA_VarjoController_Left_Grip_Click, VarjoController_Left_Grip_Click);
    MappingContext->MapKey(IA_VarjoController_Left_Grip_Touch, VarjoController_Left_Grip_Touch);
    MappingContext->MapKey(IA_VarjoController_Left_Trigger_Touch, VarjoController_Left_Trigger_Touch);
    MappingContext->MapKey(IA_VarjoController_Left_Trigger_Axis, VarjoController_Left_Trigger_Axis);
    MappingContext->MapKey(IA_VarjoController_Left_Thumbstick_X, VarjoController_Left_Thumbstick_X);
    MappingContext->MapKey(IA_VarjoController_Left_Thumbstick_Y, VarjoController_Left_Thumbstick_Y);
    MappingContext->MapKey(IA_VarjoController_Left_Thumbstick_2D, VarjoController_Left_Thumbstick_2D);
    MappingContext->MapKey(IA_VarjoController_Left_Thumbstick_Click, VarjoController_Left_Thumbstick_Click);
    MappingContext->MapKey(IA_VarjoController_Left_Thumbstick_Touch, VarjoController_Left_Thumbstick_Touch);
    //RIGHT//
    MappingContext->MapKey(IA_VarjoController_Right_A_Click, VarjoController_Right_A_Click);
    MappingContext->MapKey(IA_VarjoController_Right_B_Click, VarjoController_Right_B_Click);
    MappingContext->MapKey(IA_VarjoController_Right_A_Touch, VarjoController_Right_A_Touch);
    MappingContext->MapKey(IA_VarjoController_Right_B_Touch, VarjoController_Right_B_Touch);
    MappingContext->MapKey(IA_VarjoController_Right_System_Click, VarjoController_Right_System_Click);
    MappingContext->MapKey(IA_VarjoController_Right_Grip_Click, VarjoController_Right_Grip_Click);
    MappingContext->MapKey(IA_VarjoController_Right_Grip_Touch, VarjoController_Right_Grip_Touch);
    MappingContext->MapKey(IA_VarjoController_Right_Trigger_Touch, VarjoController_Right_Trigger_Touch);
    MappingContext->MapKey(IA_VarjoController_Right_Trigger_Axis, VarjoController_Right_Trigger_Axis);
    MappingContext->MapKey(IA_VarjoController_Right_Thumbstick_X, VarjoController_Right_Thumbstick_X);
    MappingContext->MapKey(IA_VarjoController_Right_Thumbstick_Y, VarjoController_Right_Thumbstick_Y);
    MappingContext->MapKey(IA_VarjoController_Right_Thumbstick_2D, VarjoController_Right_Thumbstick_2D);
    MappingContext->MapKey(IA_VarjoController_Right_Thumbstick_Click, VarjoController_Right_Thumbstick_Click);
    MappingContext->MapKey(IA_VarjoController_Right_Thumbstick_Touch, VarjoController_Right_Thumbstick_Touch);
}





