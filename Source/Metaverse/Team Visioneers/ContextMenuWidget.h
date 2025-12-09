// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Team SimBridge/EntityBase.h"
#include "Components/Button.h"
#include "ContextMenuWidget.generated.h"

/**
 * 
 */

class AEntityBase;
class UButton;
class AFreeCameraPawn;

UCLASS()
class METAVERSE_API UContextMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void Init(AEntityBase* InEntity);

	UFUNCTION(BlueprintCallable)
	void SetScreenPosition(const FVector2D& ScreenPosition);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnShowInfoClicked();


	UFUNCTION()
	void OnCloseClicked();
	


	UPROPERTY(meta=(BindWidget))
	UButton* ShowInfoButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;

	UPROPERTY()
	AEntityBase* TargetEntity;


	
};
