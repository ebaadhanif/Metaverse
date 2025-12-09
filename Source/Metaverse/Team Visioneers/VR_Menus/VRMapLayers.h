// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VRMenuParent.h"
#include "Blueprint/UserWidget.h"
#include "../DisplayManager.h"
#include "../Menus/MarkersDropDown.h"
#include "../../Public/AppConstEnumStruct.h"
#include "VRMapLayers.generated.h"
/**
 * 
 */
UCLASS()
class METAVERSE_API UVRMapLayers : public UVRMenuParent
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* BorderButton;
	UPROPERTY(meta = (BindWidget))
	UButton* CitiesButton;
	UPROPERTY(meta = (BindWidget))
	UButton* BasesButton;
	UPROPERTY(meta = (BindWidget))
	UButton* TownsButton;
	UPROPERTY(meta = (BindWidget))
	UButton* InternationalBorderButton;
	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;
	UPROPERTY(meta = (BindWidget))
	UButton* HomeButton;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageBorderToggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageCitiesToggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageBasesToggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageTownsToggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageIntBorderToggle;
	
public:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnBorderButtonClick();
	UFUNCTION()
	void OnCitiesButtonClick();
	UFUNCTION()
	void OnBasesButtonClick();
	UFUNCTION()
	void OnTownsButtonClick();
	UFUNCTION()
	void OnInternationalBorderButtonClick();
	UFUNCTION()
	void OnBackButtonClick();
	UFUNCTION()
	void OnHomeButtonClick();
};
