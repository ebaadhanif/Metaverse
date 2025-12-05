// Fill out your copyright notice in the Description page of Project Settings.


#include "ASaitekX65FInputHandler.h"

// Sets default values
AASaitekX65FInputHandler::AASaitekX65FInputHandler()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CreateInputActions();
}

// Called when the game starts or when spawned
void AASaitekX65FInputHandler::BeginPlay()
{
	Super::BeginPlay();
	MapKeys();
}

void AASaitekX65FInputHandler::CreateInputActions()
{
	if (!IA_Trigger_Press)
	{
		IA_Trigger_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Trigger_Press"));
		IA_Trigger_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_CastleHat_Left_Press)
	{
		IA_CastleHat_Left_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_CastleHat_Left_Press"));
		IA_CastleHat_Left_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_CastleHat_Right_Press)
	{
		IA_CastleHat_Right_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_CastleHat_Right_Press"));
		IA_CastleHat_Right_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_CastleHat_UP_Press)
	{
		IA_CastleHat_UP_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_CastleHat_UP_Press"));
		IA_CastleHat_UP_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_CastleHat_Down_Press)
	{
		IA_CastleHat_Down_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_CastleHat_Down_Press"));
		IA_CastleHat_Down_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_HHat_Left_Press)
	{
		IA_HHat_Left_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_HHat_Left_Press"));
		IA_HHat_Left_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_HHat_Right_Press)
	{
		IA_HHat_Right_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_HHat_Right_Press"));
		IA_HHat_Right_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_HHat_UP_Press)
	{
		IA_HHat_UP_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_HHat_UP_Press"));
		IA_HHat_UP_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_HHat_Down_Press)
	{
		IA_HHat_Down_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_HHat_Down_Press"));
		IA_HHat_Down_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_Hat4_Left_Press)
	{
		IA_Hat4_Left_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Hat4_Left_Press"));
		IA_Hat4_Left_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_Hat4_Right_Press)
	{
		IA_Hat4_Right_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Hat4_Right_Press"));
		IA_Hat4_Right_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_Hat4_UP_Press)
	{
		IA_Hat4_UP_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Hat4_UP_Press"));
		IA_Hat4_UP_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_Hat4_Down_Press)
	{
		IA_Hat4_Down_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Hat4_Down_Press"));
		IA_Hat4_Down_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_Hat5_Left_Press)
	{
		IA_Hat5_Left_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Hat5_Left_Press"));
		IA_Hat5_Left_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_Hat5_Right_Press)
	{
		IA_Hat5_Right_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Hat5_Right_Press"));
		IA_Hat5_Right_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_Hat5_UP_Press)
	{
		IA_Hat5_UP_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Hat5_UP_Press"));
		IA_Hat5_UP_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_Hat5_Down_Press)
	{
		IA_Hat5_Down_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Hat5_Down_Press"));
		IA_Hat5_Down_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_Hat6_Left_Press)
	{
		IA_Hat6_Left_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Hat6_Left_Press"));
		IA_Hat6_Left_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_Hat6_Right_Press)
	{
		IA_Hat6_Right_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Hat6_Right_Press"));
		IA_Hat6_Right_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_Hat6_UP_Press)
	{
		IA_Hat6_UP_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Hat6_UP_Press"));
		IA_Hat6_UP_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_Hat6_Down_Press)
	{
		IA_Hat6_Down_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Hat6_Down_Press"));
		IA_Hat6_Down_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_BowlHat_Left_Press)
	{
		IA_BowlHat_Left_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_BowlHat_Left_Press"));
		IA_BowlHat_Left_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_BowlHat_Right_Press)
	{
		IA_BowlHat_Right_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_BowlHat_Right_Press"));
		IA_BowlHat_Right_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_BowlHat_UP_Press)
	{
		IA_BowlHat_UP_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_BowlHat_UP_Press"));
		IA_BowlHat_UP_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_BowlHat_Down_Press)
	{
		IA_BowlHat_Down_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_BowlHat_Down_Press"));
		IA_BowlHat_Down_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_Hat7_Left_Press)
	{
		IA_Hat7_Left_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Hat7_Left_Press"));
		IA_Hat7_Left_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_Hat7_Right_Press)
	{
		IA_Hat7_Right_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Hat7_Right_Press"));
		IA_Hat7_Right_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_Hat7_UP_Press)
	{
		IA_Hat7_UP_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Hat7_UP_Press"));
		IA_Hat7_UP_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_Hat7_Down_Press)
	{
		IA_Hat7_Down_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Hat7_Down_Press"));
		IA_Hat7_Down_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_A_Button_Press)
	{
		IA_A_Button_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_A_Button_Press"));
		IA_A_Button_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_B_Button_Press)
	{
		IA_B_Button_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_B_Button_Press"));
		IA_B_Button_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_FlyingPinkieSwitch_Press)
	{
		IA_FlyingPinkieSwitch_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_FlyingPinkieSwitch_Press"));
		IA_FlyingPinkieSwitch_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_Pinkie_Button_Press)
	{
		IA_Pinkie_Button_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_Pinkie_Button_Press"));
		IA_Pinkie_Button_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_E_Button_Press)
	{
		IA_E_Button_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_E_Button_Press"));
		IA_E_Button_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_F_Button_Press)
	{
		IA_F_Button_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_F_Button_Press"));
		IA_F_Button_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_D_Button_Press)
	{
		IA_D_Button_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_D_Button_Press"));
		IA_D_Button_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_KSwitch_Down_Press)
	{
		IA_KSwitch_Down_Press = CreateDefaultSubobject<UInputAction>(TEXT("IA_KSwitch_Press"));
		IA_KSwitch_Down_Press->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_Rotary_1_ValueChange)
	{
		IA_Rotary_1_ValueChange = CreateDefaultSubobject<UInputAction>(TEXT("IA_Rotary_1_ValueChange"));
		IA_Rotary_1_ValueChange->ValueType = EInputActionValueType::Axis1D;
	}
	if (!IA_Rotary_2_ValueChange)
	{
		IA_Rotary_2_ValueChange = CreateDefaultSubobject<UInputAction>(TEXT("IA_Rotary_2_ValueChange"));
		IA_Rotary_2_ValueChange->ValueType = EInputActionValueType::Axis1D;
	}
	if (!IA_Slider_ValueChange)
	{
		IA_Slider_ValueChange = CreateDefaultSubobject<UInputAction>(TEXT("IA_Slider_ValueChange"));
		IA_Slider_ValueChange->ValueType = EInputActionValueType::Axis1D;
	}
	if (!IA_Throttle_Z_ValueChange)
	{
		IA_Throttle_Z_ValueChange = CreateDefaultSubobject<UInputAction>(TEXT("IA_Throttle_Z_ValueChange"));
		IA_Throttle_Z_ValueChange->ValueType = EInputActionValueType::Axis1D;
	}
	if (!IA_POVHat_ValueChange)
	{
		IA_POVHat_ValueChange = CreateDefaultSubobject<UInputAction>(TEXT("IA_POVHat_Left_Press"));
		IA_POVHat_ValueChange->ValueType = EInputActionValueType::Axis1D;
	}
	if (!IA_Stick_X_ValueChange)
	{
		IA_Stick_X_ValueChange = CreateDefaultSubobject<UInputAction>(TEXT("IA_Stick_X_ValueChange"));
		IA_Stick_X_ValueChange->ValueType = EInputActionValueType::Axis1D;
	}
	if (!IA_Stick_Y_ValueChange)
	{
		IA_Stick_Y_ValueChange = CreateDefaultSubobject<UInputAction>(TEXT("IA_Stick_Y_ValueChange"));
		IA_Stick_Y_ValueChange->ValueType = EInputActionValueType::Axis1D;
	}
	if (!IA_MinMouse_X)
	{
		IA_MinMouse_X = CreateDefaultSubobject<UInputAction>(TEXT("IA_MinMouse_X"));
		IA_MinMouse_X->ValueType = EInputActionValueType::Axis1D;
	}
	if (!IA_MinMouse_Y)
	{
		IA_MinMouse_Y = CreateDefaultSubobject<UInputAction>(TEXT("IA_MinMouse_Y"));
		IA_MinMouse_Y->ValueType = EInputActionValueType::Axis1D;
	}
	if (!IA_ScrollWheel_Forward)
	{
		IA_ScrollWheel_Forward = CreateDefaultSubobject<UInputAction>(TEXT("IA_ScrollWheel_Forward"));
		IA_ScrollWheel_Forward->ValueType = EInputActionValueType::Boolean;
	}
	if (!IA_ScrollWheel_Back)
	{
		IA_ScrollWheel_Back = CreateDefaultSubobject<UInputAction>(TEXT("IA_ScrollWheel_Back"));
		IA_ScrollWheel_Back->ValueType = EInputActionValueType::Boolean;
	}
	
}

void AASaitekX65FInputHandler::MapKeys()
{
	TArray<FKey> ButtonKeys;
	TArray<FKey> AxisKeys;

	for (int i = 1; i <= 96; i++)
	{
	
		FString keyName = FString::Printf(TEXT("GenericUSBController_Button%d"), i);
		ButtonKeys.Add(FKey(*keyName));
	}
	for (int i = 1; i <= 24; i++)
	{
		FString keyName = FString::Printf(TEXT("GenericUSBController_Axis%d"), i);
		AxisKeys.Add(FKey(*keyName));
	}


	if (MappingContext)
	{
		MappingContext->MapKey(IA_Trigger_Press, ButtonKeys[0]);

		MappingContext->MapKey(IA_CastleHat_Down_Press, ButtonKeys[14]);
		MappingContext->MapKey(IA_CastleHat_Right_Press, ButtonKeys[13]);
		MappingContext->MapKey(IA_CastleHat_UP_Press, ButtonKeys[12]);
		MappingContext->MapKey(IA_CastleHat_Left_Press, ButtonKeys[15]);

		MappingContext->MapKey(IA_BowlHat_Left_Press, ButtonKeys[9]);		
		MappingContext->MapKey(IA_BowlHat_Right_Press, ButtonKeys[11]);
		MappingContext->MapKey(IA_BowlHat_UP_Press, ButtonKeys[8]);
		MappingContext->MapKey(IA_BowlHat_Down_Press, ButtonKeys[10]);

		MappingContext->MapKey(IA_POVHat_ValueChange, AxisKeys[7]);	 

		MappingContext->MapKey(IA_HHat_Left_Press, ButtonKeys[19]);			
		MappingContext->MapKey(IA_HHat_Right_Press, ButtonKeys[17]);		
		MappingContext->MapKey(IA_HHat_UP_Press, ButtonKeys[16]);			
		MappingContext->MapKey(IA_HHat_Down_Press, ButtonKeys[18]);			

		MappingContext->MapKey(IA_Hat4_Left_Press, ButtonKeys[21]);
		MappingContext->MapKey(IA_Hat4_Right_Press, ButtonKeys[23]);
		MappingContext->MapKey(IA_Hat4_UP_Press, ButtonKeys[21]);
		MappingContext->MapKey(IA_Hat4_Down_Press, ButtonKeys[22]);

		MappingContext->MapKey(IA_Hat5_Left_Press, ButtonKeys[25]);
		MappingContext->MapKey(IA_Hat5_Right_Press, ButtonKeys[27]);
		MappingContext->MapKey(IA_Hat5_UP_Press, ButtonKeys[24]);
		MappingContext->MapKey(IA_Hat5_Down_Press, ButtonKeys[26]);

		MappingContext->MapKey(IA_Hat6_Left_Press, ButtonKeys[31]);
		MappingContext->MapKey(IA_Hat6_Right_Press, ButtonKeys[29]);
		MappingContext->MapKey(IA_Hat6_UP_Press, ButtonKeys[28]);
		MappingContext->MapKey(IA_Hat6_Down_Press, ButtonKeys[30]);

		MappingContext->MapKey(IA_Hat7_Left_Press, ButtonKeys[35]);
		MappingContext->MapKey(IA_Hat7_Right_Press, ButtonKeys[33]);
		MappingContext->MapKey(IA_Hat7_UP_Press, ButtonKeys[32]);
		MappingContext->MapKey(IA_Hat7_Down_Press, ButtonKeys[34]);

		MappingContext->MapKey(IA_KSwitch_Down_Press, ButtonKeys[40]);
		MappingContext->MapKey(IA_KSwitch_Up_Press, ButtonKeys[39]);
		MappingContext->MapKey(IA_A_Button_Press, ButtonKeys[1]);
		MappingContext->MapKey(IA_B_Button_Press, ButtonKeys[2]);
		MappingContext->MapKey(IA_F_Button_Press, ButtonKeys[7]);
		MappingContext->MapKey(IA_E_Button_Press, ButtonKeys[6]);
		MappingContext->MapKey(IA_D_Button_Press, ButtonKeys[5]);

		MappingContext->MapKey(IA_Pinkie_Button_Press, ButtonKeys[3]);
		MappingContext->MapKey(IA_FlyingPinkieSwitch_Press, ButtonKeys[4]);

		MappingContext->MapKey(IA_Rotary_1_ValueChange, AxisKeys[5]);
		MappingContext->MapKey(IA_Rotary_2_ValueChange, AxisKeys[4]);
		MappingContext->MapKey(IA_Slider_ValueChange, AxisKeys[3]);

		MappingContext->MapKey(IA_Stick_X_ValueChange, AxisKeys[1]);
		MappingContext->MapKey(IA_Stick_Y_ValueChange, AxisKeys[0]);

		MappingContext->MapKey(IA_MinMouse_X, EKeys::MouseX);
		MappingContext->MapKey(IA_MinMouse_Y, EKeys::MouseY);

		MappingContext->MapKey(IA_ScrollWheel_Forward, ButtonKeys[37]);
		MappingContext->MapKey(IA_ScrollWheel_Back, ButtonKeys[38]);
	}
}



