// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuParent.h"
#include "MetaverseMode.h"
#include "Blueprint/UserWidget.h"
#include "DrawingsDropDown.generated.h"

class UDWGXDrawingManager;

/**
 * 
 */
UCLASS()
class METAVERSE_API UDrawingsDropDown : public UMenuParent
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	UCheckBox* DrawingsOnChcekbox;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* DrawingsProjwctionCheckBox;
	UPROPERTY(meta = (BindWidget))
	UButton* ClearDrawingsButton;
	
private:
	UFUNCTION()
	void OnDrawingsOnChcekbox(bool bIsChecked);
	UFUNCTION()
	void OnDrawingsProjwctionCheckBox(bool bIsChecked);
	UFUNCTION()
	void OnClearDrawingsButton();

public:
	UFUNCTION()
	void NativeConstruct();
	virtual void ApplyMode(UMetaverseMode* Mode) override;

};
