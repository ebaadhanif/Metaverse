// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuParent.h"
#include "Blueprint/UserWidget.h"
#include "MetaverseMode.h"
#include "TerrainEditorDropDown.generated.h"


/**
 * 
 */
UCLASS()
class METAVERSE_API UTerrainEditorDropDown : public UMenuParent
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	UCheckBox* ShadedReliefCheckBox;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* SplatMapCheckbox;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* ContoursCheckbox;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* Vegetation_CheckBox;
	UPROPERTY(meta = (BindWidget))
	UButton* MarkerButton;
	bool MarkerButtonClicked = false;
private:
	UFUNCTION()
	void OnMarkerButtonClick();
	UFUNCTION()
	void OnShadedReliefCheckBox(bool bIsChecked);
	UFUNCTION()
	void OnSplatMapCheckBox(bool bIsChecked);
	UFUNCTION()
	void OnContoursCheckBox(bool bIsChecked);
	UFUNCTION()
	void OnVegetationCheckBox(bool bIsChecked);

public:
	UFUNCTION()
	void NativeConstruct();
	virtual void ApplyMode(UMetaverseMode* Mode) override;
};
