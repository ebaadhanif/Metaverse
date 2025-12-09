// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuParent.h"
#include "../DisplayManager.h"
#include "EntityVisualsDropDown.generated.h"

/**
 * 
 */
UCLASS()
class METAVERSE_API UEntityVisualsDropDown : public UMenuParent
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	UCheckBox* ModelsCheckbox;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* ColorizedCheckbox;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* Mil2525Chechbox;

private:
	UFUNCTION()
	void On3DModelsCheckBox(bool bIsChecked);
	UFUNCTION()
	void On3DModelsColorizedCheckBox(bool bIsChecked);
	UFUNCTION()
	void OnMil2525CheckBox(bool bIsChecked);
	void UncheckOtherCheckboxes(UCheckBox* CheckedBox);
public:
	void NativeConstruct();

};
