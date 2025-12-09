// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuParent.h"
#include "../AirBaseManager.h"
#include "MetaverseMode.h"
#include "MarkersDropDown.generated.h"

class UVRMapLayers;
class AVRWidgetActor;
/**
 * 
 */
UCLASS()
class METAVERSE_API UMarkersDropDown : public UMenuParent
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta=(BindWidget))
	UCheckBox* PakistanBasesCheckBox;
	UPROPERTY(meta=(BindWidget))
	UCheckBox* PakCitiesCheckBox;

private:
	UFUNCTION()
	void OnPakistanBasesCheckBox(bool bIsChecked);
	UFUNCTION()
	void OnOtherCitiesCheckBox(bool bIsChecked);
	UFUNCTION()
	void OnPakistanCitiesCheckBox(bool bIsChecked);
	UFUNCTION()
	void OnOtherBasesCheckBox(bool bIsChecked);


public:
	void NativeConstruct();
	virtual void ApplyMode(UMetaverseMode* Mode) override;
};
