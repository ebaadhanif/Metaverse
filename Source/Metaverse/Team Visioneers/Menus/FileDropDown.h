// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuParent.h"
#include "MetaverseMode.h"
#include "FileDropDown.generated.h"

class UDWGXDrawingManager;
class UVRDrawings;
/**
 *
 */
UCLASS()
class METAVERSE_API UFileDropDown : public UMenuParent
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* LoadDrawingButton;
	//UPROPERTY(meta = (BindWidget))
	//UCheckBox* TerrainBorder;
	UPROPERTY(meta = (BindWidget))
	UButton* RestartIGButton;
	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

private:
	UFUNCTION()
	void OnLoadDrawingButtonClick();
	UFUNCTION()
	void OnRestartButtonClick();
	UFUNCTION()
	void OnExitButtonClick();
	/*UFUNCTION()
	void OnTerrainBorderClicked(bool isVisible);
	bool isBorderVisibile = false;*/
public:
	void NativeConstruct();
	virtual void ApplyMode(UMetaverseMode* Mode) override;
};

