// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuParent.h"
#include "MetaverseMode.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "ListDropDown.generated.h"

class AEntityBase;
/**
 * 
 */
UCLASS()
class METAVERSE_API UListDropDown : public UMenuParent
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* HookButton;
	UPROPERTY(meta = (BindWidget))
	UButton* UnHookButton;
	UPROPERTY()
	AEntityBase* SelectedEntity;

private:

	UFUNCTION()
	void OnHookButtonClick();
	UFUNCTION()
	void OnUnHookButtonClick();

public:
	void NativeConstruct();
	UFUNCTION()
	void SetSelectedEntity(AEntityBase* entity) { SelectedEntity = entity; }

};
