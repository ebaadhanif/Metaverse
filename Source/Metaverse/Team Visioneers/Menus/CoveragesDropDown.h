// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Public/AppConstEnumStruct.h"
#include "MenuParent.h"
#include "CoveragesDropDown.generated.h"

/**
 * 
 */
UCLASS()
class METAVERSE_API UCoveragesDropDown : public UMenuParent
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	UCheckBox* CoveragesOnCheckbox;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* CoveragesFootprintCheckbox;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* DomeRingsCheckbox;

private:
	UFUNCTION()
	void OnCoveragesOnCheckBox(bool bIsChecked);
	UFUNCTION()
	void OnCoveragesFootprintsCheckBox(bool bIsChecked);
	UFUNCTION()
	void OnDomeRingsCheckBox(bool bIsChecked);

public:
	UFUNCTION()
	void NativeConstruct();

};
