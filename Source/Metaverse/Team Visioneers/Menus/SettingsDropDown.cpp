// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsDropDown.h"
#include "UIManager.h"
#include "DWGXDrawingManager.h"
#include "Kismet/GameplayStatics.h"
#include "../VR_Menus/VRWidgetActor.h"
#include "../VR_Menus/VRBattlespaceGraphics.h"
#include "../VR_Menus/VRTrails.h"
#include "../VR_Menus/VRDrawings.h"
#include "../../Team RenderStorm/SWeatherSettingsDialog.h"
#include "../../Team RenderStorm/STerrainSettingsDialog.h"
#include "../../Team RenderStorm/TrailController.h"
#include "../../Team RenderStorm/RibbonMeshActor.h"
#include "../../Team RenderStorm/VerticalRibbonMeshActor.h"
#include "../../Team RenderStorm/GroundVectorActor.h"
#include "../../Team RenderStorm/ForwardVectorActor.h"
#include "../../Team RenderStorm/CoveragesManager.h"
#include "../../Team SimBridge/EntityManager.h"
#include "../../Team SimBridge/EntityBase.h"
#include "GraphicsDropDown.h"
#include "CoveragesDropDown.h"
#include <Metaverse/Team RenderStorm/ModeManager.h>



void USettingsDropDown::NativeConstruct()
{
	MenuDepth = 1;
	InitializeWeatherController();

	if (ConnectionButton)
	{
		ConnectionButton->OnClicked.Clear();
		ConnectionButton->OnClicked.AddUniqueDynamic(this, &USettingsDropDown::OnConnectionButtonClick);
	}
	if (GraphicsButton)
	{
		GraphicsButton->OnClicked.Clear();
		GraphicsButton->OnClicked.RemoveAll(this);

		if (!GraphicsButton->OnClicked.IsAlreadyBound(this, &USettingsDropDown::OnGraphicsButtonClick))
		{
			GraphicsButton->OnClicked.AddUniqueDynamic(this, &USettingsDropDown::OnGraphicsButtonClick);
			//GraphicsButton->OnHovered.AddUniqueDynamic(this, &USettingsDropDown::OnGraphicsButtonClick);
		}
	}
	if (AudioSettingsButton)
	{
		AudioSettingsButton->OnClicked.Clear();
		AudioSettingsButton->OnClicked.AddUniqueDynamic(this, &USettingsDropDown::OnAudioSettingsButtonClick);
	}
	if (WeatherButton)
	{
		WeatherButton->OnClicked.Clear();
		WeatherButton->OnClicked.AddUniqueDynamic(this, &USettingsDropDown::OnWeatherButtonClick);
	}
	if (DrawingButton)
	{
		DrawingButton->OnClicked.Clear();
		DrawingButton->OnClicked.AddUniqueDynamic(this, &USettingsDropDown::OnDrawingButtonClick);
	}

	if (VisualGraphics_CheckBox)
	{
		setState(UIManager::GetInstance()->ButtonSates.bIsEntityLabels, VisualGraphics_CheckBox);
		VisualGraphics_CheckBox->OnCheckStateChanged.Clear();
		VisualGraphics_CheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &USettingsDropDown::OnVisualGraphicsCheckBox);
	}
	if (AModeManager::getInstance()->getActiveMode())
	{
		ApplyMode(AModeManager::getInstance()->getActiveMode());
	}
}

void USettingsDropDown::ApplyMode(UMetaverseMode* Mode)
{
	if (!Mode)
	{
		return;
	}
	if (WeatherButton)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::Weather))
		{
			WeatherButton->SetVisibility(State->Visibility);
		}
		else
		{
			WeatherButton->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	if (AudioSettingsButton)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::AudioSettings))
		{
			AudioSettingsButton->SetVisibility(State->Visibility);
		}
		else
		{
			AudioSettingsButton->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	if (ConnectionButton)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::Connection))
		{
			ConnectionButton->SetVisibility(State->Visibility);
		}
		else
		{
			ConnectionButton->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	if (GraphicsButton)
	{
		bool bAnyChildVisible = false;
		if (FButtonStateStruct* LocklinesState = Mode->ButtonStates.Find(EButtonsName::AllLocklines))
		{
			bAnyChildVisible |= (LocklinesState->Visibility == ESlateVisibility::Visible);
		}
		if (FButtonStateStruct* CoveragesState = Mode->ButtonStates.Find(EButtonsName::GroundCoverages))
		{
			bAnyChildVisible |= (CoveragesState->Visibility == ESlateVisibility::Visible);
		}
		if (FButtonStateStruct* EntityVisualsState = Mode->ButtonStates.Find(EButtonsName::EntityVisuals))
		{
			bAnyChildVisible |= (EntityVisualsState->Visibility == ESlateVisibility::Visible);
		}
		if (FButtonStateStruct* HorizontalTrailState = Mode->ButtonStates.Find(EButtonsName::HorizontalTrail))
		{
			bAnyChildVisible |= (HorizontalTrailState->Visibility == ESlateVisibility::Visible);
		}
		if (FButtonStateStruct* VerticalTrailState = Mode->ButtonStates.Find(EButtonsName::VerticalTrail))
		{
			bAnyChildVisible |= (VerticalTrailState->Visibility == ESlateVisibility::Visible);
		}
		if (FButtonStateStruct* EntityLabelsState = Mode->ButtonStates.Find(EButtonsName::EntityLabels))
		{
			bAnyChildVisible |= (EntityLabelsState->Visibility == ESlateVisibility::Visible);
		}
		if (FButtonStateStruct* AircraftCoverageState = Mode->ButtonStates.Find(EButtonsName::AircraftCoverage))
		{
			bAnyChildVisible |= (AircraftCoverageState->Visibility == ESlateVisibility::Visible);
		}
		if (FButtonStateStruct* HeightVectorState = Mode->ButtonStates.Find(EButtonsName::DownVector))
		{
			bAnyChildVisible |= (HeightVectorState->Visibility == ESlateVisibility::Visible);
		}
		if (FButtonStateStruct* HeadingVectorState = Mode->ButtonStates.Find(EButtonsName::HeadingVector))
		{
			bAnyChildVisible |= (HeadingVectorState->Visibility == ESlateVisibility::Visible);
		}
		if (FButtonStateStruct* UpVectorState = Mode->ButtonStates.Find(EButtonsName::UpVector))
		{
			bAnyChildVisible |= (UpVectorState->Visibility == ESlateVisibility::Visible);
		}
		if (FButtonStateStruct* HeightVectorRingsState = Mode->ButtonStates.Find(EButtonsName::HeightVectorRings))
		{
			bAnyChildVisible |= (HeightVectorRingsState->Visibility == ESlateVisibility::Visible);
		}
		if (FButtonStateStruct* HeightVectorRingsState = Mode->ButtonStates.Find(EButtonsName::Scaling))
		{
			bAnyChildVisible |= (HeightVectorRingsState->Visibility == ESlateVisibility::Visible);
		}
		GraphicsButton->SetVisibility(bAnyChildVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
	if (DrawingButton)
	{
		bool bAnyChildVisible = false;
		if (FButtonStateStruct* DrawingsState1 = Mode->ButtonStates.Find(EButtonsName::DrawingsOn))
		{
			bAnyChildVisible |= (DrawingsState1->Visibility == ESlateVisibility::Visible);
		}
		if (FButtonStateStruct* DrawingsProjectionState = Mode->ButtonStates.Find(EButtonsName::DrawingsProjection))
		{
			bAnyChildVisible |= (DrawingsProjectionState->Visibility == ESlateVisibility::Visible);
		}
		if (FButtonStateStruct* ClearDrawingsState = Mode->ButtonStates.Find(EButtonsName::ClearDrawings))
		{
			bAnyChildVisible |= (ClearDrawingsState->Visibility == ESlateVisibility::Visible);
		}
		DrawingButton->SetVisibility(bAnyChildVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}

	if (VisualGraphics_CheckBox)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::VisualGraphics))
		{
			VisualGraphics_CheckBox->SetVisibility(State->Visibility);
			VisualGraphics_CheckBox->SetIsChecked(State->FeatureActive);
		}
		else
		{
			VisualGraphics_CheckBox->SetVisibility(ESlateVisibility::Collapsed);
			VisualGraphics_CheckBox->SetIsChecked(false);
		}
	}
}


void USettingsDropDown::OnConnectionButtonClick()
{
	UIManager::GetInstance()->HideMenu(EMenus::GraphicsDropDown);
	UIManager::GetInstance()->HideMenu(EMenus::DrawingsDropDown);
	GraphicsState = false;
	DrawingsState = true;
}

void USettingsDropDown::OnGraphicsButtonClick()
{
	TObjectPtr<UUserWidget>* Found4 = UIManager::GetInstance()->MenuWidgetMap.Find(EMenus::DrawingsDropDown);
	UUserWidget* FoundPtr4 = Found4->Get();
	if (FoundPtr4->IsInViewport())
	{
		FoundPtr4->RemoveFromViewport();
	}

	TObjectPtr<UUserWidget>* Found5 = UIManager::GetInstance()->MenuWidgetMap.Find(EMenus::GraphicsDropDown);
	UUserWidget* FoundPtr5 = Found5->Get();
	if (!FoundPtr5->IsInViewport())
	{
		FoundPtr5->AddToViewport(0);
		FVector2D SubMenuPosition3 = UIManager::GetInstance()->CalculateForwardMenuPosition(this, GraphicsButton, FoundPtr5);
		FoundPtr5->SetRenderTranslation(SubMenuPosition3);
		FoundPtr5->SetVisibility(ESlateVisibility::Visible);
		UIManager::GetInstance()->OpenMenu.Add(FoundPtr5);
	}
	else {
		FoundPtr5->RemoveFromViewport();
	}


	//if (!GraphicsState || DrawingsState==true)
	//{
	//	GraphicsState = true;
	//	UIManager::GetInstance()->HideMenu(EMenus::DrawingsDropDown);
	//	DrawingsState = false;
	//	UIManager::GetInstance()->CloseAllOpenMenu();
	//	UIManager::GetInstance()->ShowMenu(EMenus::GraphicsDropDown);
	//	TObjectPtr<UUserWidget>* Found4 = UIManager::GetInstance()->MenuWidgetMap.Find(EMenus::GraphicsDropDown);
	//	UUserWidget* FoundPtr4 = Found4->Get();
	//	FVector2D SubMenuPosition3 = UIManager::GetInstance()->CalculateForwardMenuPosition(this, GraphicsButton, FoundPtr4);
	//	FoundPtr4->SetRenderTranslation(SubMenuPosition3);
	//	FoundPtr4->SetVisibility(ESlateVisibility::Visible);
	//	UIManager::GetInstance()->OpenMenu.Add(FoundPtr4);
	//}
	//else
	//{
	//	GraphicsState = false;
	//	UIManager::GetInstance()->HideMenu(EMenus::GraphicsDropDown);
	//}
}                                                                                      

void USettingsDropDown::OnAudioSettingsButtonClick()
{
	UIManager::GetInstance()->HideMenu(EMenus::GraphicsDropDown);
	UIManager::GetInstance()->HideMenu(EMenus::DrawingsDropDown);
	GraphicsState = false;
	DrawingsState = true;
}

void USettingsDropDown::OnWeatherButtonClick()
{
	//UIManager::GetInstance()->HideMenu(EMenus::GraphicsDropDown);
	//UIManager::GetInstance()->HideMenu(EMenus::DrawingsDropDown);
	//TSharedRef<SWindow> DialogWindow = SNew(SWindow)
	//	.Title(FText::FromString("Weather Settings"))
	//	.ClientSize(FVector2D(400, 600))
	//	.SupportsMinimize(false)
	//	.SupportsMaximize(false)
	//	[
	//		SNew(SWeatherSettingsDialog).WeatherController(WeatherController)
	//	];

	//WeatherSettingsWindow = DialogWindow;

	//FSlateApplication::Get().AddWindow(DialogWindow);
}

void USettingsDropDown::InitializeWeatherController()
{
	for (TActorIterator<AWeatherController> It(GetWorld()); It; ++It)
	{
		WeatherController = *It;
		break;
	}

	if (WeatherController.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("WeatherController initialized in CustomWidget."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WeatherController not found in the level."));
	}
}

void USettingsDropDown::OnDrawingButtonClick()
{

	TObjectPtr<UUserWidget>* Found4 = UIManager::GetInstance()->MenuWidgetMap.Find(EMenus::GraphicsDropDown);
	UUserWidget* FoundPtr4 = Found4->Get();
	if (FoundPtr4->IsInViewport())
	{
		FoundPtr4->RemoveFromViewport();
	}

	TObjectPtr<UUserWidget>* Found5 = UIManager::GetInstance()->MenuWidgetMap.Find(EMenus::DrawingsDropDown);
	UUserWidget* FoundPtr5 = Found5->Get();
	if (!FoundPtr5->IsInViewport())
	{
		FoundPtr5->AddToViewport(0);
		FVector2D SubMenuPosition3 = UIManager::GetInstance()->CalculateForwardMenuPosition(this, DrawingButton, FoundPtr5);
		FoundPtr5->SetRenderTranslation(SubMenuPosition3);
		FoundPtr5->SetVisibility(ESlateVisibility::Visible);
		UIManager::GetInstance()->OpenMenu.Add(FoundPtr5);
	}
	else {
		FoundPtr5->RemoveFromViewport();
	}
}

void USettingsDropDown::OnVisualGraphicsCheckBox(bool isVisible)
{
	UIManager::GetInstance()->SetStateofScreen(EButtonsName::VisualGraphics, isVisible);
}




