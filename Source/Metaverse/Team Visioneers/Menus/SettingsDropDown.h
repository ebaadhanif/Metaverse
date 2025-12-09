// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuParent.h"
#include "../../Team RenderStorm/WeatherController.h"
#include "../EntityListUI.h"
#include "MetaverseMode.h"
#include "Blueprint/UserWidget.h"
#include "TerrainManager.h"
#include "SettingsDropDown.generated.h"

class UVRBattlespaceGraphics;
class UVRDrawings;
class AVRWidgetActor;
class EntityManager;
class AEntityBase;
/**
 * 
 */
UCLASS()
class METAVERSE_API USettingsDropDown : public UMenuParent
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	UButton* ConnectionButton;
	UPROPERTY(meta = (BindWidget))
	UButton* GraphicsButton;
	UPROPERTY(meta = (BindWidget))
	UButton* AudioSettingsButton;
	UPROPERTY(meta = (BindWidget))
	UButton* WeatherButton;
	UPROPERTY(meta = (BindWidget))
	UButton* DrawingButton;

	UPROPERTY(meta = (BindWidget))
	UCheckBox* VisualGraphics_CheckBox;
	

private:
	void NativeConstruct();
	virtual void ApplyMode(UMetaverseMode* Mode) override;
	UFUNCTION()
	void OnConnectionButtonClick();
	UFUNCTION()
	void OnGraphicsButtonClick();
	UFUNCTION()
	void OnAudioSettingsButtonClick();
	UFUNCTION()
	void OnWeatherButtonClick();
	UFUNCTION()
	void OnDrawingButtonClick();

	UFUNCTION()
	void OnVisualGraphicsCheckBox(bool isVisible);

	TWeakObjectPtr<AWeatherController> WeatherController;
	void InitializeWeatherController();
	TWeakPtr<SWindow> WeatherSettingsWindow;
	bool GraphicsState = false;
	bool DrawingsState = false;

};
