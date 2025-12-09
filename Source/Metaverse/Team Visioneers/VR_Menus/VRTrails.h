// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VRMenuParent.h"
#include "../Menus/GraphicsDropDown.h"
#include "../Menus/TrailsDropDown.h"
#include "VRTrails.generated.h"

/**
 * 
 */
UCLASS()
class METAVERSE_API UVRTrails : public UVRMenuParent
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* TrailsOnOffButton;
	UPROPERTY(meta = (BindWidget))
	UButton* Trail1MinButton;
	UPROPERTY(meta = (BindWidget))
	UButton* Trail30SecButton;
	UPROPERTY(meta = (BindWidget))
	UButton* TrailLifetimeButton;
	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;
	UPROPERTY(meta = (BindWidget))
	UButton* HomeButton;
	UPROPERTY(meta = (BindWidget))
	UImage* Image30SecToggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageITrailToggle;
	UPROPERTY(meta = (BindWidget))
	UImage* Image1MinToggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageLifetimeToggle;
	
private:
	UFUNCTION()
	void OnTrailsOnOffButtonClick();
	UFUNCTION()
	void OnTrail1MinButtonClick();
	UFUNCTION()
	void OnTrail30SecButtonClick();
	UFUNCTION()
	void OnTrailLifetimeButtonClick();
	UFUNCTION()
	void OnBackButtonClick();
	UFUNCTION()
	void OnHomeButtonClick();

};
