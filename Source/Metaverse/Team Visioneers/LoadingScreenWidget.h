// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "LoadingScreenWidget.generated.h"



/**
 * 
 */
UCLASS()
class METAVERSE_API ULoadingScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* LoadingMessageText;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* LoadingProgressBar;

	UFUNCTION(BlueprintCallable)
	void SetLoadingMessage(const FText& NewMessage);

	FString GetUpdatedText(const FString& InputString);


	UFUNCTION(BlueprintCallable)
	void SetProgressBar(float ProgressValue);
	
};
