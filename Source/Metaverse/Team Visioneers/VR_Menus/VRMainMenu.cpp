// Fill out your copyright notice in the Description page of Project Settings.


#include "VRMainMenu.h"
#include "VRWidgetActor.h"
#include "UIManagerVR.h"
#include "../../Team RenderStorm/STerrainSettingsDialog.h"
#include "../../Team SimBridge/EntityManager.h"
#include "../../Team SimBridge/EntityBase.h"


void UVRMainMenu::NativeConstruct()
{
	if (TerrainVisualsButton)
	{
		TerrainVisualsButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		TerrainVisualsButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		TerrainVisualsButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsTerrainVisuals, ImageTerrainToggle);
		TerrainVisualsButton->OnClicked.Clear();
		TerrainVisualsButton->OnClicked.AddUniqueDynamic(this, &UVRMainMenu::OnTerrainVisualsButtonClick);
	}

	if (MapLayersButton)
	{
		MapLayersButton->OnClicked.Clear();
		MapLayersButton->OnClicked.AddUniqueDynamic(this, &UVRMainMenu::OnMapLayersButtonClick);
	}

	if (BattlespaceGraphicsButton)
	{
		BattlespaceGraphicsButton->OnClicked.Clear();
		BattlespaceGraphicsButton->OnClicked.AddUniqueDynamic(this, &UVRMainMenu::OnBattlespaceGraphicsButtonClick);
	}

	if (ShortcutToolbarButton)
	{
		ShortcutToolbarButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		ShortcutToolbarButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		ShortcutToolbarButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsShortcutToolBar, ImageToolbarToggle);
		ShortcutToolbarButton->OnClicked.Clear();
		ShortcutToolbarButton->OnClicked.AddUniqueDynamic(this, &UVRMainMenu::OnShortcutToolbarButtonClick);
	}

	if (AnalyticsButton)
	{
		AnalyticsButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		AnalyticsButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		AnalyticsButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsAnalytics, ImageAnalyticsToggle);
		AnalyticsButton->OnClicked.Clear();
		AnalyticsButton->OnClicked.AddUniqueDynamic(this, &UVRMainMenu::OnAnalyticsButtonClick);
	}

	if (StatusBarButton)
	{
		StatusBarButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		StatusBarButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		StatusBarButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsStatusBar, ImageStatusBarToggle);
		StatusBarButton->OnClicked.Clear();
		StatusBarButton->OnClicked.AddUniqueDynamic(this, &UVRMainMenu::OnStatusBarButtonClick);
	}

	if (CompassButton)
	{
		CompassButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		CompassButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		CompassButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsCompass, ImageCompassToggle);
		CompassButton->OnClicked.Clear();
		CompassButton->OnClicked.AddUniqueDynamic(this, &UVRMainMenu::OnCompassButtonClick);
	}
	if (RestartButton)
	{
		RestartButton->OnClicked.Clear();
		RestartButton->OnClicked.AddUniqueDynamic(this, &UVRMainMenu::OnRestartButtonClick);
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.Clear();
		ExitButton->OnClicked.AddUniqueDynamic(this, &UVRMainMenu::OnExitButtonClick);
	}
}

void UVRMainMenu::OnTerrainVisualsButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::ShadedRelief);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsTerrainVisuals , ImageTerrainToggle);
}

void UVRMainMenu::OnMapLayersButtonClick()
{
	WidgetHandling(EMenusVR::MapLayers);
}

void UVRMainMenu::OnBattlespaceGraphicsButtonClick()
{
	WidgetHandling(EMenusVR::BattlespaceGraphics);
}

void UVRMainMenu::OnShortcutToolbarButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::ShortcutToolBar);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsShortcutToolBar, ImageToolbarToggle);
}

void UVRMainMenu::OnAnalyticsButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::Analytics);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsAnalytics, ImageAnalyticsToggle);	

}

void UVRMainMenu::OnStatusBarButtonClick()
{
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsStatusBar, ImageStatusBarToggle);

}

void UVRMainMenu::OnCompassButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::Compass);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsCompass, ImageCompassToggle);
}

void UVRMainMenu::OnRestartButtonClick()
{
	APlayerController* playerController = GetOwningPlayer();
	FString CurrentLevel = GetWorld()->GetMapName();
	CurrentLevel.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
	UGameplayStatics::OpenLevel(GetWorld(), FName(*CurrentLevel));
}

void UVRMainMenu::OnExitButtonClick()
{
	APlayerController* playerController = GetOwningPlayer();
	UKismetSystemLibrary::QuitGame(GetWorld(), playerController, EQuitPreference::Quit, true);
}

