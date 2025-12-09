// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/CheckBox.h"
#include "MetaverseMode.h"
#include "Components/Button.h"
#include "MenuParent.generated.h"

/**
 * 
 */
UCLASS()
class METAVERSE_API UMenuParent : public UUserWidget
{
	GENERATED_BODY()
public:
	int MenuDepth = -1;
	void setState(bool state, UCheckBox* checkbox);
	virtual void ApplyMode(UMetaverseMode* Mode);
};
