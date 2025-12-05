// Fill out your copyright notice in the Description page of Project Settings.


#include "MouseInputHandler.h"

// Sets default values
AMouseInputHandler::AMouseInputHandler()
{
    CreateInputActions();
}

// Called when the game starts or when spawned
void AMouseInputHandler::BeginPlay()
{
	Super::BeginPlay();
	MapKeys();
	
}

void AMouseInputHandler::CreateInputActions()
{
    if (!IA_MouseX)
    {
        IA_MouseX = CreateDefaultSubobject<UInputAction>(TEXT("IA_MouseX"));
        IA_MouseX->ValueType = EInputActionValueType::Axis1D;
    }

    if (!IA_MouseY)
    {
        IA_MouseY = CreateDefaultSubobject<UInputAction>(TEXT("IA_MouseY"));
        IA_MouseY->ValueType = EInputActionValueType::Axis1D;
    }

    if (!IA_MouseScroll)
    {
        IA_MouseScroll = CreateDefaultSubobject<UInputAction>(TEXT("IA_MouseScroll"));
        IA_MouseScroll->ValueType = EInputActionValueType::Axis1D;
    }

    if (!IA_LeftMouseButton)
    {
        IA_LeftMouseButton = CreateDefaultSubobject<UInputAction>(TEXT("IA_LeftMouseButton"));
        IA_LeftMouseButton->ValueType = EInputActionValueType::Boolean;
    }

    if (!IA_RightMouseButton)
    {
        IA_RightMouseButton = CreateDefaultSubobject<UInputAction>(TEXT("IA_RightMouseButton"));
        IA_RightMouseButton->ValueType = EInputActionValueType::Boolean;
    }
}

void AMouseInputHandler::MapKeys()
{
    if (MappingContext)
    {
        MappingContext->MapKey(IA_MouseX, EKeys::MouseX);
        MappingContext->MapKey(IA_MouseY, EKeys::MouseY);
        MappingContext->MapKey(IA_MouseScroll, EKeys::MouseWheelAxis);
        MappingContext->MapKey(IA_LeftMouseButton, EKeys::LeftMouseButton);
        MappingContext->MapKey(IA_RightMouseButton, EKeys::RightMouseButton);
    }
}

