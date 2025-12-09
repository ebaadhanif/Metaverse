// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VRMenuParent.h"
#include "VRDrawings.generated.h"

class UDWGXDrawingManager;
/**
 * 
 */
UCLASS()
class METAVERSE_API UVRDrawings : public UVRMenuParent
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* DrawingsOnOffButton;
	UPROPERTY(meta = (BindWidget))
	UButton* selectFileButton;
	UPROPERTY(meta = (BindWidget))
	UButton* ClearFileButton;
	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;
	UPROPERTY(meta = (BindWidget))
	UButton* HomeButton;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageDrawingsToggle;

private:
	UFUNCTION()
	void OnDrawingsOnOffButtonClick();
	UFUNCTION()
	void OnselectFileButtonClick();
	UFUNCTION()
	void OnClearFileButtonClick();
	UFUNCTION()
	void OnBackButtonClick();
	UFUNCTION()
	void OnHomeButtonClick();
};
