#include "HtcVIVEInputHandler.h"

AHtcVIVEInputHandler::AHtcVIVEInputHandler()
{
	CreateInputActions();

}

void AHtcVIVEInputHandler::BeginPlay()
{
	Super::BeginPlay();
	MapKeys();
	
}

void AHtcVIVEInputHandler::CreateInputActions()
{
    // LEFT CONTROLLER

    // Grip Click
    if (!IA_Vive_Left_Grip_Click)
    {
        IA_Vive_Left_Grip_Click = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Left_Grip_Click"));
        IA_Vive_Left_Grip_Click->ValueType = EInputActionValueType::Boolean;
    }

    // Menu Click
    if (!IA_Vive_Left_Menu_Click)
    {
        IA_Vive_Left_Menu_Click = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Left_Menu_Click"));
        IA_Vive_Left_Menu_Click->ValueType = EInputActionValueType::Boolean;
    }

    // System Click
    if (!IA_Vive_Left_System_Click)
    {
        IA_Vive_Left_System_Click = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Left_System_Click"));
        IA_Vive_Left_System_Click->ValueType = EInputActionValueType::Boolean;
    }

    // Trackpad 2D
    if (!IA_Vive_Left_Trackpad_2D)
    {
        IA_Vive_Left_Trackpad_2D = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Left_Trackpad_2D"));
        IA_Vive_Left_Trackpad_2D->ValueType = EInputActionValueType::Axis2D;
    }

    // Trackpad Click
    if (!IA_Vive_Left_Trackpad_Click)
    {
        IA_Vive_Left_Trackpad_Click = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Left_Trackpad_Click"));
        IA_Vive_Left_Trackpad_Click->ValueType = EInputActionValueType::Boolean;
    }

    // Trackpad Touch
    if (!IA_Vive_Left_Trackpad_Touch)
    {
        IA_Vive_Left_Trackpad_Touch = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Left_Trackpad_Touch"));
        IA_Vive_Left_Trackpad_Touch->ValueType = EInputActionValueType::Boolean;
    }

    // Trackpad Up
    if (!IA_Vive_Left_Trackpad_Up)
    {
        IA_Vive_Left_Trackpad_Up = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Left_Trackpad_Up"));
        IA_Vive_Left_Trackpad_Up->ValueType = EInputActionValueType::Boolean;
    }

    // Trackpad Down
    if (!IA_Vive_Left_Trackpad_Down)
    {
        IA_Vive_Left_Trackpad_Down = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Left_Trackpad_Down"));
        IA_Vive_Left_Trackpad_Down->ValueType = EInputActionValueType::Boolean;
    }

    // Trackpad Left
    if (!IA_Vive_Left_Trackpad_Left)
    {
        IA_Vive_Left_Trackpad_Left = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Left_Trackpad_Left"));
        IA_Vive_Left_Trackpad_Left->ValueType = EInputActionValueType::Boolean;
    }

    // Trackpad Right
    if (!IA_Vive_Left_Trackpad_Right)
    {
        IA_Vive_Left_Trackpad_Right = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Left_Trackpad_Right"));
        IA_Vive_Left_Trackpad_Right->ValueType = EInputActionValueType::Boolean;
    }

    // Trackpad X Axis (single axis)
    if (!IA_Vive_Left_Trackpad_X)
    {
        IA_Vive_Left_Trackpad_X = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Left_Trackpad_X"));
        IA_Vive_Left_Trackpad_X->ValueType = EInputActionValueType::Axis1D;
    }

    // Trackpad Y Axis (single axis)
    if (!IA_Vive_Left_Trackpad_Y)
    {
        IA_Vive_Left_Trackpad_Y = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Left_Trackpad_Y"));
        IA_Vive_Left_Trackpad_Y->ValueType = EInputActionValueType::Axis1D;
    }

    // Trigger Axis (analog)
    if (!IA_Vive_Left_Trigger_Axis)
    {
        IA_Vive_Left_Trigger_Axis = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Left_Trigger_Axis"));
        IA_Vive_Left_Trigger_Axis->ValueType = EInputActionValueType::Axis1D;
    }

    // Trigger Click
    if (!IA_Vive_Left_Trigger_Click)
    {
        IA_Vive_Left_Trigger_Click = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Left_Trigger_Click"));
        IA_Vive_Left_Trigger_Click->ValueType = EInputActionValueType::Boolean;
    }

    // RIGHT CONTROLLER

    // Grip Click
    if (!IA_Vive_Right_Grip_Click)
    {
        IA_Vive_Right_Grip_Click = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Right_Grip_Click"));
        IA_Vive_Right_Grip_Click->ValueType = EInputActionValueType::Boolean;
    }

    // Menu Click
    if (!IA_Vive_Right_Menu_Click)
    {
        IA_Vive_Right_Menu_Click = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Right_Menu_Click"));
        IA_Vive_Right_Menu_Click->ValueType = EInputActionValueType::Boolean;
    }

    // System Click
    if (!IA_Vive_Right_System_Click)
    {
        IA_Vive_Right_System_Click = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Right_System_Click"));
        IA_Vive_Right_System_Click->ValueType = EInputActionValueType::Boolean;
    }

    // Trackpad 2D
    if (!IA_Vive_Right_Trackpad_2D)
    {
        IA_Vive_Right_Trackpad_2D = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Right_Trackpad_2D"));
        IA_Vive_Right_Trackpad_2D->ValueType = EInputActionValueType::Axis2D;
    }

    // Trackpad Click
    if (!IA_Vive_Right_Trackpad_Click)
    {
        IA_Vive_Right_Trackpad_Click = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Right_Trackpad_Click"));
        IA_Vive_Right_Trackpad_Click->ValueType = EInputActionValueType::Boolean;
    }

    // Trackpad Touch
    if (!IA_Vive_Right_Trackpad_Touch)
    {
        IA_Vive_Right_Trackpad_Touch = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Right_Trackpad_Touch"));
        IA_Vive_Right_Trackpad_Touch->ValueType = EInputActionValueType::Boolean;
    }

    // Trackpad Up
    if (!IA_Vive_Right_Trackpad_Up)
    {
        IA_Vive_Right_Trackpad_Up = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Right_Trackpad_Up"));
        IA_Vive_Right_Trackpad_Up->ValueType = EInputActionValueType::Boolean;
    }

    // Trackpad Down
    if (!IA_Vive_Right_Trackpad_Down)
    {
        IA_Vive_Right_Trackpad_Down = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Right_Trackpad_Down"));
        IA_Vive_Right_Trackpad_Down->ValueType = EInputActionValueType::Boolean;
    }

    // Trackpad Left
    if (!IA_Vive_Right_Trackpad_Left)
    {
        IA_Vive_Right_Trackpad_Left = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Right_Trackpad_Left"));
        IA_Vive_Right_Trackpad_Left->ValueType = EInputActionValueType::Boolean;
    }

    // Trackpad Right
    if (!IA_Vive_Right_Trackpad_Right)
    {
        IA_Vive_Right_Trackpad_Right = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Right_Trackpad_Right"));
        IA_Vive_Right_Trackpad_Right->ValueType = EInputActionValueType::Boolean;
    }

    // Trackpad X Axis (single axis)
    if (!IA_Vive_Right_Trackpad_X)
    {
        IA_Vive_Right_Trackpad_X = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Right_Trackpad_X"));
        IA_Vive_Right_Trackpad_X->ValueType = EInputActionValueType::Axis1D;
    }

    // Trackpad Y Axis (single axis)
    if (!IA_Vive_Right_Trackpad_Y)
    {
        IA_Vive_Right_Trackpad_Y = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Right_Trackpad_Y"));
        IA_Vive_Right_Trackpad_Y->ValueType = EInputActionValueType::Axis1D;
    }

    // Trigger Axis (analog)
    if (!IA_Vive_Right_Trigger_Axis)
    {
        IA_Vive_Right_Trigger_Axis = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Right_Trigger_Axis"));
        IA_Vive_Right_Trigger_Axis->ValueType = EInputActionValueType::Axis1D;
    }

    // Trigger Click
    if (!IA_Vive_Right_Trigger_Click)
    {
        IA_Vive_Right_Trigger_Click = CreateDefaultSubobject<UInputAction>(TEXT("IA_Vive_Right_Trigger_Click"));
        IA_Vive_Right_Trigger_Click->ValueType = EInputActionValueType::Boolean;
    }
}


void AHtcVIVEInputHandler::MapKeys()
{
    // Right 
    //MappingContext->MapKey(IA_Vive_Right_System_Click, EKeys::Vive_Right_System_Click);
    MappingContext->MapKey(IA_Vive_Right_Grip_Click, EKeys::Vive_Right_Grip_Click);
    MappingContext->MapKey(IA_Vive_Right_Menu_Click, EKeys::Vive_Right_Menu_Click);
    MappingContext->MapKey(IA_Vive_Right_Trigger_Click, EKeys::Vive_Right_Trigger_Click);
    MappingContext->MapKey(IA_Vive_Right_Trigger_Axis, EKeys::Vive_Right_Trigger_Axis);
    MappingContext->MapKey(IA_Vive_Right_Trackpad_2D, EKeys::Vive_Right_Trackpad_2D);
    MappingContext->MapKey(IA_Vive_Right_Trackpad_X, EKeys::Vive_Right_Trackpad_X);
    MappingContext->MapKey(IA_Vive_Right_Trackpad_Y, EKeys::Vive_Right_Trackpad_Y);
    MappingContext->MapKey(IA_Vive_Right_Trackpad_Click, EKeys::Vive_Right_Trackpad_Click);
    MappingContext->MapKey(IA_Vive_Right_Trackpad_Touch, EKeys::Vive_Right_Trackpad_Touch);
    MappingContext->MapKey(IA_Vive_Right_Trackpad_Up, EKeys::Vive_Right_Trackpad_Up);
    MappingContext->MapKey(IA_Vive_Right_Trackpad_Down, EKeys::Vive_Right_Trackpad_Down);
    MappingContext->MapKey(IA_Vive_Right_Trackpad_Left, EKeys::Vive_Right_Trackpad_Left);
    MappingContext->MapKey(IA_Vive_Right_Trackpad_Right, EKeys::Vive_Right_Trackpad_Right);
    // Left
    //MappingContext->MapKey(IA_Vive_Left_System_Click, EKeys::Vive_Left_System_Click);
    MappingContext->MapKey(IA_Vive_Left_Grip_Click, EKeys::Vive_Left_Grip_Click);
    MappingContext->MapKey(IA_Vive_Left_Menu_Click, EKeys::Vive_Left_Menu_Click);
    MappingContext->MapKey(IA_Vive_Left_Trigger_Click, EKeys::Vive_Left_Trigger_Click);
    MappingContext->MapKey(IA_Vive_Left_Trigger_Axis, EKeys::Vive_Left_Trigger_Axis);
    MappingContext->MapKey(IA_Vive_Left_Trackpad_2D, EKeys::Vive_Left_Trackpad_2D);
    MappingContext->MapKey(IA_Vive_Left_Trackpad_X, EKeys::Vive_Left_Trackpad_X);
    MappingContext->MapKey(IA_Vive_Left_Trackpad_Y, EKeys::Vive_Left_Trackpad_Y);
    MappingContext->MapKey(IA_Vive_Left_Trackpad_Click, EKeys::Vive_Left_Trackpad_Click);
    MappingContext->MapKey(IA_Vive_Left_Trackpad_Touch, EKeys::Vive_Left_Trackpad_Touch);
    MappingContext->MapKey(IA_Vive_Left_Trackpad_Up, EKeys::Vive_Left_Trackpad_Up);
    MappingContext->MapKey(IA_Vive_Left_Trackpad_Down, EKeys::Vive_Left_Trackpad_Down);
    MappingContext->MapKey(IA_Vive_Left_Trackpad_Left, EKeys::Vive_Left_Trackpad_Left);
    MappingContext->MapKey(IA_Vive_Left_Trackpad_Right, EKeys::Vive_Left_Trackpad_Right);
}

