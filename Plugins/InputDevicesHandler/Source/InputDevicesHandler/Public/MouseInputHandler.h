// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ADevicesHandler.h"
#include "MouseInputHandler.generated.h"

UCLASS()
class INPUTDEVICESHANDLER_API AMouseInputHandler : public AADevicesHandler
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMouseInputHandler();

    // Axis Input
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* IA_MouseX;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* IA_MouseY;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* IA_MouseScroll;

    // Ctrl Toggle Input
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* IA_LeftMouseButton;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* IA_RightMouseButton;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void CreateInputActions() override;
	virtual void MapKeys() override;



};
