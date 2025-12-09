// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuParent.h"
#include "HelpDropDown.generated.h"

/**
 * 
 */
UCLASS()
class METAVERSE_API UHelpDropDown : public UMenuParent
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* UsersGuideButton;

	UPROPERTY(meta = (BindWidget))
	UButton* AboutUsButton;

private:

	UFUNCTION()
	void OnGuideButtonClick();
	UFUNCTION()
	void OnAboutUsButtonClick();

public:
	void NativeConstruct();

};
