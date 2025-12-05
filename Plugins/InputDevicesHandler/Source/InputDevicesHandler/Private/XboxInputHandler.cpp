// Fill out your copyright notice in the Description page of Project Settings.


#include "XboxInputHandler.h"

// Sets default values
AXboxInputHandler::AXboxInputHandler()
{
	CreateInputActions();

}

// Called when the game starts or when spawned
void AXboxInputHandler::BeginPlay()
{
	Super::BeginPlay();
	MapKeys();
	
}

void AXboxInputHandler::CreateInputActions()
{
	//Right ThumbStick
	if (!IA_Gamepad_Right_Thumbstick_X)
	{
		IA_Gamepad_Right_Thumbstick_X = CreateDefaultSubobject<UInputAction>(TEXT("IA_Gamepad_Right_Thumbstick_X"));
		IA_Gamepad_Right_Thumbstick_X->ValueType = EInputActionValueType::Axis1D;
	}

	if (!IA_Gamepad_Right_Thumbstick_Y)
	{
		IA_Gamepad_Right_Thumbstick_Y = CreateDefaultSubobject<UInputAction>(TEXT("IA_Gamepad_Right_Thumbstick_Y"));
		IA_Gamepad_Right_Thumbstick_Y->ValueType = EInputActionValueType::Axis1D;
	}

	//Left ThumbStick
	if (!IA_Gamepad_Left_Thumbstick_Y)
	{
		IA_Gamepad_Left_Thumbstick_Y = CreateDefaultSubobject<UInputAction>(TEXT("IA_Gamepad_Left_Thumbstick_Y"));
		IA_Gamepad_Left_Thumbstick_Y->ValueType = EInputActionValueType::Axis1D;
	}

	if (!IA_Gamepad_Left_Thumbstick_X)
	{
		IA_Gamepad_Left_Thumbstick_X = CreateDefaultSubobject<UInputAction>(TEXT("IA_Gamepad_Left_Thumbstick_X"));
		IA_Gamepad_Left_Thumbstick_X->ValueType = EInputActionValueType::Axis1D;
	}

	//D-pad
	if (!IA_Gamepad_Dpad_Right)
	{
		IA_Gamepad_Dpad_Right = CreateDefaultSubobject<UInputAction>(TEXT("IA_Gamepad_Dpad_Right"));
		IA_Gamepad_Dpad_Right->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_Gamepad_Dpad_Left)
	{
		IA_Gamepad_Dpad_Left = CreateDefaultSubobject<UInputAction>(TEXT("IA_Gamepad_Dpad_Left"));
		IA_Gamepad_Dpad_Left->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_Gamepad_Dpad_Up)
	{
		IA_Gamepad_Dpad_Up = CreateDefaultSubobject<UInputAction>(TEXT("IA_Gamepad_Dpad_Up"));
		IA_Gamepad_Dpad_Up->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_Gamepad_Dpad_Down)
	{
		IA_Gamepad_Dpad_Down = CreateDefaultSubobject<UInputAction>(TEXT("IA_Gamepad_Dpad_Down"));
		IA_Gamepad_Dpad_Down->ValueType = EInputActionValueType::Boolean;
	}

	//Face Button
	if (!IA_Gamepad_Face_Button_Right)
	{
		IA_Gamepad_Face_Button_Right = CreateDefaultSubobject<UInputAction>(TEXT("IA_Gamepad_Face_Button_Right"));
		IA_Gamepad_Face_Button_Right->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_Gamepad_Face_Button_Left)
	{
		IA_Gamepad_Face_Button_Left = CreateDefaultSubobject<UInputAction>(TEXT("IA_Gamepad_Face_Button_Left"));
		IA_Gamepad_Face_Button_Left->ValueType = EInputActionValueType::Boolean;
	}

	if (!IA_Gamepad_Face_Button_Bottom)
	{
		IA_Gamepad_Face_Button_Bottom = CreateDefaultSubobject<UInputAction>(TEXT("IA_Gamepad_Face_Button_Bottom"));
		IA_Gamepad_Face_Button_Bottom->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_Gamepad_Face_Button_Top)
	{
		IA_Gamepad_Face_Button_Top = CreateDefaultSubobject<UInputAction>(TEXT("IA_Gamepad_Face_Button_Top"));
		IA_Gamepad_Face_Button_Top->ValueType = EInputActionValueType::Boolean;
	}

	//Shoulder
	if (!IA_Gamepad_Right_Shoulder)
	{
		IA_Gamepad_Right_Shoulder = CreateDefaultSubobject<UInputAction>(TEXT("IA_Gamepad_Right_Shoulder"));
		IA_Gamepad_Right_Shoulder->ValueType = EInputActionValueType::Boolean;
	}

	if (!IA_Gamepad_Left_Shoulder)
	{
		IA_Gamepad_Left_Shoulder = CreateDefaultSubobject<UInputAction>(TEXT("IA_Gamepad_Left_Shoulder"));
		IA_Gamepad_Left_Shoulder->ValueType = EInputActionValueType::Boolean;
	}

}

void AXboxInputHandler::MapKeys()
{
	if (MappingContext)
	{
		//Right ThumbStick
		MappingContext->MapKey(IA_Gamepad_Right_Thumbstick_X, EKeys::Gamepad_RightX);
		MappingContext->MapKey(IA_Gamepad_Right_Thumbstick_Y, EKeys::Gamepad_RightY);

		//Left ThumbStick
		MappingContext->MapKey(IA_Gamepad_Left_Thumbstick_Y, EKeys::Gamepad_LeftY);
		MappingContext->MapKey(IA_Gamepad_Left_Thumbstick_X, EKeys::Gamepad_LeftX);

		//Face button
		MappingContext->MapKey(IA_Gamepad_Face_Button_Right, EKeys::Gamepad_FaceButton_Right);
		MappingContext->MapKey(IA_Gamepad_Face_Button_Left, EKeys::Gamepad_FaceButton_Left);
		MappingContext->MapKey(IA_Gamepad_Face_Button_Top, EKeys::Gamepad_FaceButton_Top);
		MappingContext->MapKey(IA_Gamepad_Face_Button_Bottom, EKeys::Gamepad_FaceButton_Bottom);

		//D-pad Button
		MappingContext->MapKey(IA_Gamepad_Dpad_Right, EKeys::Gamepad_DPad_Right);
		MappingContext->MapKey(IA_Gamepad_Dpad_Left, EKeys::Gamepad_DPad_Left);
		MappingContext->MapKey(IA_Gamepad_Dpad_Up, EKeys::Gamepad_DPad_Up);
		MappingContext->MapKey(IA_Gamepad_Dpad_Down, EKeys::Gamepad_DPad_Down);

		//Shoulders
		MappingContext->MapKey(IA_Gamepad_Left_Shoulder, EKeys::Gamepad_LeftShoulder);
		MappingContext->MapKey(IA_Gamepad_Right_Shoulder, EKeys::Gamepad_RightShoulder);
	}

}

AXboxInputHandler::~AXboxInputHandler()
{

}


