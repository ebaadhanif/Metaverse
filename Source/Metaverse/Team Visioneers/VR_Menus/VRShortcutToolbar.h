// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VRMenuParent.h"
#include "../../Public/AppConstEnumStruct.h"
#include "VRShortcutToolbar.generated.h"

class UIManagerVR;
class UDWGXDrawingManager;
class ATrailController;
class EntityManager;
class AEntityBase;
/**
 *
 */
UCLASS()
class METAVERSE_API UVRShortcutToolbar : public UVRMenuParent
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void SetFPS(int fps);
protected:
	bool bUpdatingLocklineUI = false;
	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;
	UPROPERTY(meta = (BindWidget))
	UButton* EntityVisualsButton;
	UPROPERTY(meta = (BindWidget))
	UButton* EntityLabelsButton;
	UPROPERTY(meta = (BindWidget))
	UButton* LockLinesButton;
	UPROPERTY(meta = (BindWidget))
	UButton* CoveragesButton;
	UPROPERTY(meta = (BindWidget))
	UButton* TrailsButton;
	UPROPERTY(meta = (BindWidget))
	UButton* HeadingVectorButton;
	UPROPERTY(meta = (BindWidget))
	UButton* HeightVectorButton;
	UPROPERTY(meta = (BindWidget))
	UButton* RotationUpVectorButton;
	UPROPERTY(meta = (BindWidget))
	UButton* DrawingsButton;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* FPS_Text;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageVisualsToggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageLabelsToggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageLocklinesToggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageCoveragesToggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageTrailsToggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageHeadingToggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageHeightToggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageRotationToggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageDrawingsToggle;
	int FPS = 0;
	float OneSecondTime = 0;
	int32 ChangeVisual = 0;
public:
	UFUNCTION()
	void OnCloseButtonClick();
	UFUNCTION()
	void OnEntityVisualsButtonClick();
	UFUNCTION()
	void OnEntityLabelButtonClick();
	UFUNCTION()
	void OnLockLinesButtonClick();
	UFUNCTION()
	void OnCoveragesButtonClick();
	UFUNCTION()
	void OnTrailButtonClick();
	UFUNCTION()
	void OnHeadingVectorButtonClick();
	UFUNCTION()
	void OnHeightVectorButtonClick();
	UFUNCTION()
	void OnRotationUpButtonClick();
	UFUNCTION()
	void OnDrawingsButtonClick();

	UPROPERTY()
	ATrailController* trailController;
};
