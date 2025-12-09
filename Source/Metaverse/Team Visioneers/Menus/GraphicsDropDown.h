// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuParent.h"
#include "MetaverseMode.h"
#include "Blueprint/UserWidget.h"
#include "GraphicsDropDown.generated.h"

class VRBattlespaceGraphics;
/**
 * 
 */
UCLASS()
class METAVERSE_API UGraphicsDropDown : public UMenuParent
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* HorizontalTrailButton;
	UPROPERTY(meta = (BindWidget))
	UButton* VerticalTrailButton;
	UPROPERTY(meta = (BindWidget))
	UButton* LocklinesButton;
	UPROPERTY(meta = (BindWidget))
	UButton* GroundCoveragesButton;
	UPROPERTY(meta = (BindWidget))
	UButton* EntityVisualsButton;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* EntityLabelChcekbox;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* ScalingCheckbox;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* AircraftCoveragesCheckBox;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* HeadingVectorChcekbox;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* HeightCheckbox;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* HeightVectorRings;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* OrientationUpCheckbox;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* StateBlink_CheckBox;

	bool HorizontalTrailState = false;
	bool VerticalStateState = false;
	bool CoveragesState = false;
	bool LocklinesState = false;
	bool EntityVisualsState = false;
	TArray<UUserWidget*> OpenGraphicsMenu;
private:
	UFUNCTION()
	void OnHorizontalTrailButtonClick();
	UFUNCTION()
	void OnVerticalTrailButtonClick();
	UFUNCTION()
	void OnLocklinesButtonClick();
	UFUNCTION()
	void OnGroundCoveragesButtonClick();
	UFUNCTION()
	void OnEntityVisualsButtonClick();
	UFUNCTION()
	void OnEntityLabelCheckBox(bool bIsChecked);
	UFUNCTION()
	void OnAircraftCoveragesCheckBox(bool bIsChecked);
	UFUNCTION()
	void OnHeadingVectorCheckBox(bool bIsChecked);
	UFUNCTION()
	void OnHeightCheckBox(bool bIsChecked);
	UFUNCTION()
	void OnGroundVectorRingsCheckBox(bool bIsChecked);
	UFUNCTION()
	void OnOrientationUpCheckBox(bool bIsChecked);
	UFUNCTION()
	void onBlinkCheckboxClicked(bool bIsChecked);
	UFUNCTION()
	void OnScalingCheckBox(bool bIsChecked);
	void CloseGraphicsOpenMenu();
public:
	UFUNCTION()
	void NativeConstruct();
	virtual void ApplyMode(UMetaverseMode* Mode) override;
};
