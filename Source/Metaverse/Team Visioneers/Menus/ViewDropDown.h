// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuParent.h"
#include "../EntityListUI.h"
#include "ViewDropDown.generated.h"

class UMetaverseMode;
/**
 * 
 */
UCLASS()
class METAVERSE_API UViewDropDown : public UMenuParent
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	UEntityListUI* EntityListInstance;

	UPROPERTY(meta = (BindWidget))
	UCheckBox* AnalyticsCheckbox;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* StatusBarCheckbox;
	UPROPERTY(meta = (BindWidget))
	UButton* TerrainEditorButton;
	UPROPERTY(meta = (BindWidget))
	UButton* PreviewModelButton;
	UPROPERTY(meta = (BindWidget))
	UButton* GoToLocationButton;
	UPROPERTY(meta = (BindWidget))
	UButton* FullScreenButton;

	bool TerrainEditorMenu = false;
private:
	UFUNCTION()
	void OnTerrainEditorButtonClick();
	UFUNCTION()
	void OnPreviewModelButtonClick();
	UFUNCTION()
	void OnGoToLocationButtonClick();
	UFUNCTION()
	void OnFullScreenButtonClick();
	UFUNCTION()
	void OnObjectListButtonClick();
	UFUNCTION()
	void OnAnalyticsCheckBox(bool bIsChecked);
	UFUNCTION()
	void OnStatusBarCheckBox(bool bIsChecked);
public:	
	UPROPERTY(meta = (BindWidget))
	UButton* ObjectListButton;
	bool ObjListBtn = false;
	UFUNCTION()
	void SetEntityListInstance(UEntityListUI* instance);
	UFUNCTION()
	void NativeConstruct();
	virtual void ApplyMode(UMetaverseMode* Mode) override;
};
