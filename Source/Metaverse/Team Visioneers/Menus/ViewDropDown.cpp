// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewDropDown.h"
#include "UIManager.h"
#include "../EntityListUI.h"
#include "MetaverseMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameUserSettings.h"
#include "Engine/GameEngine.h"
#include <Metaverse/Team RenderStorm/ModeManager.h>

void UViewDropDown::SetEntityListInstance(UEntityListUI* instance)
{
	EntityListInstance = instance;
}
void UViewDropDown::NativeConstruct()
{
	MenuDepth = 1;

	if (AnalyticsCheckbox)
	{
		AnalyticsCheckbox->OnCheckStateChanged.Clear();
		AnalyticsCheckbox->OnCheckStateChanged.AddUniqueDynamic(this, &UViewDropDown::OnAnalyticsCheckBox);
	}
	if (StatusBarCheckbox)
	{
		StatusBarCheckbox->OnCheckStateChanged.Clear();
		StatusBarCheckbox->OnCheckStateChanged.AddUniqueDynamic(this, &UViewDropDown::OnStatusBarCheckBox);
	}
	if (TerrainEditorButton)
	{
		TerrainEditorButton->OnClicked.Clear();
		TerrainEditorButton->OnClicked.AddUniqueDynamic(this, &UViewDropDown::OnTerrainEditorButtonClick);
	}
	if (ObjectListButton)
	{
		ObjectListButton->OnClicked.Clear();
		ObjectListButton->OnClicked.AddUniqueDynamic(this, &UViewDropDown::OnObjectListButtonClick);
	}
	if (PreviewModelButton)
	{
		PreviewModelButton->OnClicked.Clear();
		PreviewModelButton->OnClicked.AddUniqueDynamic(this, &UViewDropDown::OnPreviewModelButtonClick);
	}
	if (GoToLocationButton)
	{
		GoToLocationButton->OnClicked.Clear();
		GoToLocationButton->OnClicked.AddUniqueDynamic(this, &UViewDropDown::OnGoToLocationButtonClick);
	}
	if (FullScreenButton)
	{
		FullScreenButton->OnClicked.Clear();
		FullScreenButton->OnClicked.AddUniqueDynamic(this, &UViewDropDown::OnFullScreenButtonClick);
	}
	if (AModeManager::getInstance()->getActiveMode())
	{
		ApplyMode(AModeManager::getInstance()->getActiveMode());
	}
}

void UViewDropDown::ApplyMode(UMetaverseMode* Mode)
{
	if (!Mode)
	{
		return;
	}
	if (AnalyticsCheckbox)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::Analytics))
		{
			AnalyticsCheckbox->SetVisibility(State->Visibility);
			AnalyticsCheckbox->SetIsChecked(State->FeatureActive);
		}
		else
		{
			AnalyticsCheckbox->SetVisibility(ESlateVisibility::Collapsed);
			AnalyticsCheckbox->SetIsChecked(false);
		}
	}
	if (StatusBarCheckbox)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::StatusBar))
		{
			StatusBarCheckbox->SetVisibility(State->Visibility);
			StatusBarCheckbox->SetIsChecked(State->FeatureActive);
		}
		else
		{
			StatusBarCheckbox->SetVisibility(ESlateVisibility::Collapsed);
			StatusBarCheckbox->SetIsChecked(false);
		}
	}
	if (ObjectListButton)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::ObjectList))
		{
			ObjectListButton->SetVisibility(State->Visibility);
		}
		else
		{
			ObjectListButton->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	if (PreviewModelButton)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::PreviewModels))
		{
			PreviewModelButton->SetVisibility(State->Visibility);
		}
		else
		{
			PreviewModelButton->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	if (GoToLocationButton)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::GoToLocation))
		{
			GoToLocationButton->SetVisibility(State->Visibility);
		}
		else
		{
			GoToLocationButton->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	if (FullScreenButton)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::FullScreen))
		{
			FullScreenButton->SetVisibility(State->Visibility);
		}
		else
		{
			FullScreenButton->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	if (TerrainEditorButton)
	{
		bool bAnyChildVisible = false;
		if (FButtonStateStruct* TerrainVisualsState = Mode->ButtonStates.Find(EButtonsName::ShadedRelief))
		{
			bAnyChildVisible |= (TerrainVisualsState->Visibility == ESlateVisibility::Visible);
		}
		if (FButtonStateStruct* SplatMapState = Mode->ButtonStates.Find(EButtonsName::SplatMap))
		{
			bAnyChildVisible |= (SplatMapState->Visibility == ESlateVisibility::Visible);
		}
		if (FButtonStateStruct* ContoursState = Mode->ButtonStates.Find(EButtonsName::Contours))
		{
			bAnyChildVisible |= (ContoursState->Visibility == ESlateVisibility::Visible);
		}
		if (FButtonStateStruct* MarkersState = Mode->ButtonStates.Find(EButtonsName::Markers))
		{
			bAnyChildVisible |= (MarkersState->Visibility == ESlateVisibility::Visible);
		}
		if (FButtonStateStruct* MarkersState = Mode->ButtonStates.Find(EButtonsName::Vegetation))
		{
			bAnyChildVisible |= (MarkersState->Visibility == ESlateVisibility::Visible);
		}
		TerrainEditorButton->SetVisibility(bAnyChildVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
}

void UViewDropDown::OnAnalyticsCheckBox(bool bIsChecked)
{
}

void UViewDropDown::OnStatusBarCheckBox(bool bIsChecked)
{
	/*if (bIsChecked) {
		UIManager::GetInstance()->ShowMenu(EMenus::StatusBar);
	}
	else
	{
		UIManager::GetInstance()->HideMenu(EMenus::StatusBar);
	}

	RemoveFromParent();*/
}

void UViewDropDown::OnTerrainEditorButtonClick()
{
	//if (!TerrainEditorMenu)
	//{
		TerrainEditorMenu = true;


		TObjectPtr<UUserWidget>* Found1 = UIManager::GetInstance()->MenuWidgetMap.Find(EMenus::TerrainEditorDropDown);
		UUserWidget* FoundPtr1 = Found1->Get();

		if (!FoundPtr1->IsInViewport())
		{
			//UIManager::GetInstance()->CloseAllOpenMenu();
			UIManager::GetInstance()->ShowMenu(EMenus::TerrainEditorDropDown);
			FVector2D SubMenuPosition = UIManager::GetInstance()->CalculateForwardMenuPosition(this, TerrainEditorButton, FoundPtr1);
			FoundPtr1->SetRenderTranslation(SubMenuPosition);
			FoundPtr1->SetVisibility(ESlateVisibility::Visible);
			UIManager::GetInstance()->OpenMenu.Add(FoundPtr1);
		}
		else {
			UIManager::GetInstance()->HideMenu(EMenus::TerrainEditorDropDown);
			UIManager::GetInstance()->HideMenu(EMenus::MarkersDropDown);
		}


	//}
	//else
	//{
	//	TerrainEditorMenu = false;
	//	UIManager::GetInstance()->HideMenu(EMenus::TerrainEditorDropDown);
	//}

}

void UViewDropDown::OnPreviewModelButtonClick()
{
}

void UViewDropDown::OnObjectListButtonClick()
{
	UMetaverseMode* Mode = UIManager::GetInstance()->GetActiveMode();
	if (!Mode)
		return;

	//if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::ObjectList))
	//{
		//const bool bNewState = !State->FeatureActive;  // toggle
	UIManager::GetInstance()->CloseAllOpenMenu();
	UIManager::GetInstance()->HideMenu(EMenus::ViewDropDown);
	TObjectPtr<UUserWidget>* Found5 = UIManager::GetInstance()->MenuWidgetMap.Find(EMenus::EntityList);
	UUserWidget* FoundPtr5 = Found5->Get();
	if (!FoundPtr5->IsInViewport()) {
		FoundPtr5->AddToViewport(-1);
		//UIManager::GetInstance()->ShowMenu(EMenus::EntityList);
		UIManager::GetInstance()->SetStateofScreen(EButtonsName::ObjectList, true);
		UIManager::GetInstance()->OpenMenu.Add(FoundPtr5);
	}
	else {
		UIManager::GetInstance()->HideMenu(EMenus::EntityList);
		UIManager::GetInstance()->SetStateofScreen(EButtonsName::ObjectList, false);
		UIManager::GetInstance()->OpenMenu.Remove(FoundPtr5);
	}
	//}
}

void UViewDropDown::OnGoToLocationButtonClick()
{
	UIManager::GetInstance()->CloseAllOpenMenu();
}

void UViewDropDown::OnFullScreenButtonClick()
{
	UIManager::GetInstance()->CloseAllOpenMenu();
	if (UGameEngine* GameEngine = Cast<UGameEngine>(GEngine))
	{
		UGameUserSettings* Settings = GEngine->GetGameUserSettings();
		if (!Settings) return;
		Settings->SetFullscreenMode(EWindowMode::Fullscreen);
		Settings->ApplySettings(false);

	}
}

