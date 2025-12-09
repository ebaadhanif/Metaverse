// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VRMenuParent.h"
#include "../Menus/EntityVisualsDropDown.h"
#include "VREntityVisuals.generated.h"


/**
 * 
 */
UCLASS()
class METAVERSE_API UVREntityVisuals :public UVRMenuParent
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* TextureModelButton;
	UPROPERTY(meta = (BindWidget))
	UButton* ColoredModelButton;
	UPROPERTY(meta = (BindWidget))
	UButton* Mil2525Button;
	UPROPERTY(meta = (BindWidget))
	UButton* SmallModelButton;
	UPROPERTY(meta = (BindWidget))
	UButton* MediumModelButton;
	UPROPERTY(meta = (BindWidget))
	UButton* LargeModelButton;
	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;
	UPROPERTY(meta = (BindWidget))
	UButton* HomeButton;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageTexturedToggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageColoredToggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageMil25Toggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageEntitySmallToggle; 
	UPROPERTY(meta = (BindWidget))
	UImage* ImageEntityMediumToggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageEntityLargeToggle;

private:
	UFUNCTION()
	void OnTextureModelButtonClick();
	UFUNCTION()
	void OnColoredModelButtonClick();
	UFUNCTION()
	void OnMil2525ButtonClick();
	UFUNCTION()
	void OnSmallModelButtonClick();
	UFUNCTION()
	void OnMediumModelButtonClick();
	UFUNCTION()
	void OnLargeModelButtonClick();
	UFUNCTION()
	void OnBackButtonClick();
	UFUNCTION()
	void OnHomeButtonClick();
};
