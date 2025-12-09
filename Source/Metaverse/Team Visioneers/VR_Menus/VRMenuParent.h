// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "../../Public/AppConstEnumStruct.h"
#include "Components/TextBlock.h"
#include "VRMenuParent.generated.h"

class UIManagerVR;

UCLASS()
class METAVERSE_API UVRMenuParent : public UUserWidget
{
	GENERATED_BODY()
protected:
	FLinearColor OffColor = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f);
	FLinearColor OnColor = FLinearColor(0.0f, 0.0f, 1.0f, 1.0f);
	UPROPERTY()
	EMenusVR MenuToHide;
	UPROPERTY()
	EMenusVR MenuToDisplay;
	
	void UpdateVisual(bool bIsOn , UImage* image);
public:
	void WidgetHandling(EMenusVR MenuType);
	void HomeButtonClick();
	void BackButtonClick();
	void RefreshVisuals(bool bIsOn, UButton* button);
	void ApplyColor(bool bIsOn, UButton* button);
	UFUNCTION()
	virtual void NativeConstruct() override;
};
