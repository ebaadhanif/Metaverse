// Fill out your copyright notice in the Description page of Project Settings.


#include "TerrainEditorDropDown.h"
#include "UIManager.h"
#include <Metaverse/Team RenderStorm/ModeManager.h>


void UTerrainEditorDropDown::NativeConstruct()
{
	if (ShadedReliefCheckBox)
	{
		//setState(UIManager::GetInstance()->ButtonSates.bIsTerrainVisuals, ShadedReliefCheckBox);
		ShadedReliefCheckBox->OnCheckStateChanged.Clear();
		ShadedReliefCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UTerrainEditorDropDown::OnShadedReliefCheckBox);
	}
	if (SplatMapCheckbox)
	{
		//setState(UIManager::GetInstance()->ButtonSates.bIsTerrainSplat, SplatMapCheckbox);
		SplatMapCheckbox->OnCheckStateChanged.Clear();
		SplatMapCheckbox->OnCheckStateChanged.AddUniqueDynamic(this, &UTerrainEditorDropDown::OnSplatMapCheckBox);
	}
	if (ContoursCheckbox)
	{
		//setState(UIManager::GetInstance()->ButtonSates.bIsHorizontalTrail, ContoursCheckbox);
		ContoursCheckbox->OnCheckStateChanged.Clear();
		ContoursCheckbox->OnCheckStateChanged.AddUniqueDynamic(this, &UTerrainEditorDropDown::OnContoursCheckBox);
	}
	if (Vegetation_CheckBox)
	{
		//setState(UIManager::GetInstance()->ButtonSates.bIsHorizontalTrail, ContoursCheckbox);
		Vegetation_CheckBox->OnCheckStateChanged.Clear();
		Vegetation_CheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UTerrainEditorDropDown::OnVegetationCheckBox);
	}
	if (MarkerButton)
	{
		MarkerButton->OnClicked.Clear();
		MarkerButton->OnClicked.AddUniqueDynamic(this, &UTerrainEditorDropDown::OnMarkerButtonClick);
	}
	if (AModeManager::getInstance()->getActiveMode())
	{
		ApplyMode(AModeManager::getInstance()->getActiveMode());
	}
}

void UTerrainEditorDropDown::ApplyMode(UMetaverseMode* Mode)
{
	if (!Mode)
	{
		return;
	}
	if (ShadedReliefCheckBox)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::ShadedRelief))
		{
			ShadedReliefCheckBox->SetVisibility(State->Visibility);
			ShadedReliefCheckBox->SetIsChecked(State->FeatureActive);
		}
		else
		{
			ShadedReliefCheckBox->SetVisibility(ESlateVisibility::Collapsed);
			ShadedReliefCheckBox->SetIsChecked(false);
		}
	}
	if (SplatMapCheckbox)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::SplatMap))
		{
			SplatMapCheckbox->SetVisibility(State->Visibility);
			SplatMapCheckbox->SetIsChecked(State->FeatureActive);
		}
		else
		{
			SplatMapCheckbox->SetVisibility(ESlateVisibility::Collapsed);
			SplatMapCheckbox->SetIsChecked(false);
		}
	}
	if (Vegetation_CheckBox)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::Vegetation))
		{
			Vegetation_CheckBox->SetVisibility(State->Visibility);
			Vegetation_CheckBox->SetIsChecked(State->FeatureActive);
		}
		else
		{
			Vegetation_CheckBox->SetVisibility(ESlateVisibility::Collapsed);
			Vegetation_CheckBox->SetIsChecked(false);
		}
	}
	if (ContoursCheckbox)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::Contours))
		{
			ContoursCheckbox->SetVisibility(State->Visibility);
			ContoursCheckbox->SetIsChecked(State->FeatureActive);
		}
		else
		{
			ContoursCheckbox->SetVisibility(ESlateVisibility::Collapsed);
			ContoursCheckbox->SetIsChecked(false);
		}
	}
	if (Vegetation_CheckBox)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::Vegetation))
		{
			Vegetation_CheckBox->SetVisibility(State->Visibility);
			Vegetation_CheckBox->SetIsChecked(State->FeatureActive);
		}
		else
		{
			Vegetation_CheckBox->SetVisibility(ESlateVisibility::Collapsed);
			Vegetation_CheckBox->SetIsChecked(false);
		}
	}
	if (MarkerButton)
	{
		bool bAnyChildVisible = false;
		if (FButtonStateStruct* PakCitiesState = Mode->ButtonStates.Find(EButtonsName::PakCities))
		{
			bAnyChildVisible |= (PakCitiesState->Visibility == ESlateVisibility::Visible);
		}
		if (FButtonStateStruct* PakBasesState = Mode->ButtonStates.Find(EButtonsName::PakBases))
		{
			bAnyChildVisible |= (PakBasesState->Visibility == ESlateVisibility::Visible);
		}
		MarkerButton->SetVisibility(bAnyChildVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
}

void UTerrainEditorDropDown::OnMarkerButtonClick()
{
	if (!MarkerButtonClicked)
	{
		MarkerButtonClicked = true;
		UIManager::GetInstance()->ShowMenu(EMenus::MarkersDropDown);
		TObjectPtr<UUserWidget>* Found1 = UIManager::GetInstance()->MenuWidgetMap.Find(EMenus::MarkersDropDown);
		UUserWidget* FoundPtr1 = Found1->Get();
		FVector2D SubMenuPosition1 = UIManager::GetInstance()->CalculateForwardMenuPosition(this, MarkerButton, FoundPtr1);
		FoundPtr1->SetRenderTranslation(SubMenuPosition1);
		FoundPtr1->SetVisibility(ESlateVisibility::Visible);
		UIManager::GetInstance()->OpenMenu.Add(FoundPtr1);
	}
	else
	{
		MarkerButtonClicked = false;
		UIManager::GetInstance()->HideMenu(EMenus::MarkersDropDown);
	}
	
}

void UTerrainEditorDropDown::OnShadedReliefCheckBox(bool bIsChecked)
{
	UIManager::GetInstance()->SetStateofScreen(EButtonsName::ShadedRelief , bIsChecked);
}

void UTerrainEditorDropDown::OnSplatMapCheckBox(bool bIsChecked)
{
	UIManager::GetInstance()->SetStateofScreen(EButtonsName::SplatMap , bIsChecked);
}

void UTerrainEditorDropDown::OnContoursCheckBox(bool bIsChecked)
{
	UIManager::GetInstance()->SetStateofScreen(EButtonsName::Contours, bIsChecked);
}

void UTerrainEditorDropDown::OnVegetationCheckBox(bool bIsChecked)
{
	UIManager::GetInstance()->SetStateofScreen(EButtonsName::Vegetation, bIsChecked);
}
