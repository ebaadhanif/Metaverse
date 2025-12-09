// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VRMenuParent.h"
#include "TerrainManager.h"
#include "../DisplayManager.h"
#include "VRMainMenu.generated.h"
/**
 *
 */
UCLASS()
class METAVERSE_API UVRMainMenu : public UVRMenuParent
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* TerrainVisualsButton;
	UPROPERTY(meta = (BindWidget))
	UButton* MapLayersButton;
	UPROPERTY(meta = (BindWidget))
	UButton* BattlespaceGraphicsButton;
	UPROPERTY(meta = (BindWidget))
	UButton* ShortcutToolbarButton;
	UPROPERTY(meta = (BindWidget))
	UButton* AnalyticsButton;
	UPROPERTY(meta = (BindWidget))
	UButton* StatusBarButton;
	UPROPERTY(meta = (BindWidget))
	UButton* CompassButton;
	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;
	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageTerrainToggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageToolbarToggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageAnalyticsToggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageStatusBarToggle;
	UPROPERTY(meta = (BindWidget))
	UImage* ImageCompassToggle;
public:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnTerrainVisualsButtonClick();
	UFUNCTION()
	void OnMapLayersButtonClick();
	UFUNCTION()
	void OnBattlespaceGraphicsButtonClick();
	UFUNCTION()
	void OnShortcutToolbarButtonClick();
	UFUNCTION()
	void OnAnalyticsButtonClick();
	UFUNCTION()
	void OnStatusBarButtonClick();
	UFUNCTION()
	void OnCompassButtonClick();
	UFUNCTION()
	void OnRestartButtonClick();
	UFUNCTION()
	void OnExitButtonClick();

	AActor* Found;
	ATerrainManager* TM;
};
