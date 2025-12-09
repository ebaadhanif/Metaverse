// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuParent.h"
#include "Blueprint/UserWidget.h"
#include "LockLinesDropDown.generated.h"

class VRBattlespaceGraphics;
/**
 * 
 */
UCLASS()
class METAVERSE_API ULockLinesDropDown : public UMenuParent
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	UCheckBox* AllLockinesChcekbox;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* SameLocklinesCheckBox;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* OpposingLocklinesChcekbox;
	bool LocklinesState = false;

private:
	UFUNCTION()
	void OnAllLocklinesChcekboxClick(bool bIsChecked);
	UFUNCTION()
	void OnSameLocklinesChcekboxClick(bool bIsChecked);
	UFUNCTION()
	void OnOpposingLocklinesChcekboxClick(bool bIsChecked);
	bool bUpdatingLocklineUI = false;

public:
	UFUNCTION()
	void NativeConstruct();

};
