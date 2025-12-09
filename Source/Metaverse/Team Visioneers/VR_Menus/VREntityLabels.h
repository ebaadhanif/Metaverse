// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VRMenuParent.h"
#include "VREntityLabels.generated.h"

/**
 * 
 */
UCLASS()
class METAVERSE_API UVREntityLabels : public UVRMenuParent
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* LabelOnOffButton;
	UPROPERTY(meta = (BindWidget))
	UButton* LabelSmallButton;
	UPROPERTY(meta = (BindWidget))
	UButton* LabelMediumButton;
	UPROPERTY(meta = (BindWidget))
	UButton* LabelLargeButton;
	UPROPERTY(meta = (BindWidget))
	UButton* LabelOffset1Button;
	UPROPERTY(meta = (BindWidget))
	UButton* LabelOffset2Button;
	UPROPERTY(meta = (BindWidget))
	UButton* LabelOffset3Button;
	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;
	UPROPERTY(meta = (BindWidget))
	UButton* HomeButton;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageLabelSmallToggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageLabelToggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageLabelMediumToggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageLabelLargeToggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageOffset1Toggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageOffset2Toggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageOffset3Toggle;
private:
	UFUNCTION()
	void OnLabelOnOffButtonClick();
	UFUNCTION()
	void OnLabelSmallButtonClick();
	UFUNCTION()
	void OnLabelMediumButtonClick();
	UFUNCTION()
	void OnLabelLargeButtonClick();
	UFUNCTION()
	void OnLabelOffset1ButtonClick();
	UFUNCTION()
	void OnLabelOffset2ButtonClick();
	UFUNCTION()
	void OnLabelOffset3ButtonClick();
	UFUNCTION()
	void OnBackButtonClick();
	UFUNCTION()
	void OnHomeButtonClick();
};
