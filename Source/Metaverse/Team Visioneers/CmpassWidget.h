// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "CmpassWidget.generated.h"

/**
 * 
 */
class UImage;
class UTextBlock;
class UScaleBox;

UCLASS()
class METAVERSE_API UCmpassWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	void ApplyCustomDPIScalling();

public:
	UFUNCTION(BlueprintCallable)
	void UpdateCompassNeedle(float Yaw);
	float GetNormalizedYaw(float Yaw);
	FString GetDisplayValue(float Yaw);
	virtual void NativeConstruct() override;

protected:

	UPROPERTY(meta = (BindWidget))
	UImage* CompassNeedleImage;


	UPROPERTY(meta = (BindWidget))
	UTextBlock* CompassYawText;


	UPROPERTY(meta = (BindWidget))
	UScaleBox* RootScaleBox;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="DPI")
	UCurveFloat* DPI_Curve;
	

	
};
