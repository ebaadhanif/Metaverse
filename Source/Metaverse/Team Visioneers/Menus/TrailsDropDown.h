// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuParent.h"
#include "MetaverseMode.h"
#include "../../Public/AppConstEnumStruct.h"
#include "TrailsDropDown.generated.h"

class UVRTrails;
class AVRWidgetActor;

/**
 * 
 */
UCLASS()
class METAVERSE_API UTrailsDropDown : public UMenuParent
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta=(BindWidget))
	UCheckBox* Trail30SecChecbox;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* Trail1MinCheckbox;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* TrailLifetimeCheckbox;
	UPROPERTY()
	ETrailChannel TrailChannel = ETrailChannel::Horizontal;
private:
	UFUNCTION()
	void OnTrail30SecCheckBox(bool bIsChecked);
	UFUNCTION()
	void OnTrail1MinCheckBox(bool bIsChecked);
	UFUNCTION()
	void OnTrailLifetimeCheckBox(bool bIsChecked);

public:
	void NativeConstruct();
	void UncheckOtherCheckboxes(UCheckBox* CheckedBox);
	void InitializeChannel(ETrailChannel InChannel) { TrailChannel = InChannel; }
	virtual void ApplyMode(UMetaverseMode* Mode) override;
};
