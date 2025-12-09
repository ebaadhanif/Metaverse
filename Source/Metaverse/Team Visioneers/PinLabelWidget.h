// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PinLabelWidget.generated.h"

//forword declare UTextBlock
class UTextBlock;

UCLASS()
class METAVERSE_API UPinLabelWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Label")
	void SetLabelText(const FText& NewText);

	virtual void SetLabelText_Implementation(const FText& NewText);
protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* LabelTextBlock;
};
