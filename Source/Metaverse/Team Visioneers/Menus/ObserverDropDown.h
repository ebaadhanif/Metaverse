// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuParent.h"
#include "ObserverDropDown.generated.h"

/**
 * 
 */
UCLASS()
class METAVERSE_API UObserverDropDown : public UMenuParent
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* ObserverModeButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CompassButton;
private:
	UFUNCTION()
	void OnObserverModeButtonClick();

	UFUNCTION()
	void OnCompassButtonClick();
public:
	void NativeConstruct();

};
