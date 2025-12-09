// Fill out your copyright notice in the Description page of Project Settings.


#include "MarkersDropDown.h"
#include "UIManager.h"
#include "../VR_Menus/VRWidgetActor.h"
#include "../VR_Menus/VRMapLayers.h"
#include "../../Team RenderStorm/RibbonMeshActor.h"
#include "../../Team RenderStorm/VerticalRibbonMeshActor.h"
#include "../AirBaseManager.h"
#include "MarkersDropDown.h"
#include <Metaverse/Team RenderStorm/ModeManager.h>

void UMarkersDropDown::NativeConstruct()
{
	MenuDepth = 2;
	if (PakistanBasesCheckBox)
	{
		setState(UIManager::GetInstance()->ButtonSates.bIsPakBases, PakistanBasesCheckBox);
		PakistanBasesCheckBox->OnCheckStateChanged.Clear();
		PakistanBasesCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UMarkersDropDown::OnPakistanBasesCheckBox);
	}
	if (PakCitiesCheckBox)
	{
		setState(UIManager::GetInstance()->ButtonSates.bIsPakCities, PakCitiesCheckBox);
		PakCitiesCheckBox->OnCheckStateChanged.Clear();
		PakCitiesCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UMarkersDropDown::OnPakistanCitiesCheckBox);
	}
	if (AModeManager::getInstance()->getActiveMode())
	{
		ApplyMode(AModeManager::getInstance()->getActiveMode());
	}
}

void UMarkersDropDown::ApplyMode(UMetaverseMode* Mode)
{
	if (!Mode)
	{
		return;
	}
	if (PakistanBasesCheckBox)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::PakBases))
		{
			PakistanBasesCheckBox->SetVisibility(State->Visibility);
			PakistanBasesCheckBox->SetIsChecked(State->FeatureActive);
		}
		else
		{
			PakistanBasesCheckBox->SetVisibility(ESlateVisibility::Collapsed);
			PakistanBasesCheckBox->SetIsChecked(false);
		}
	}
	if (PakCitiesCheckBox)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::PakCities))
		{
			PakCitiesCheckBox->SetVisibility(State->Visibility);
			PakCitiesCheckBox->SetIsChecked(State->FeatureActive);
		}
		else
		{
			PakCitiesCheckBox->SetVisibility(ESlateVisibility::Collapsed);
			PakCitiesCheckBox->SetIsChecked(false);
		}
	}
}

void UMarkersDropDown::OnPakistanBasesCheckBox(bool bIsChecked)
{
	
	UIManager::GetInstance()->SetStateofScreen(EButtonsName::PakBases, bIsChecked);
}

void UMarkersDropDown::OnOtherBasesCheckBox(bool bIsChecked)
{
	UIManager::GetInstance()->SetStateofScreen(EButtonsName::IndBases, bIsChecked);
}

void UMarkersDropDown::OnOtherCitiesCheckBox(bool bIsChecked)
{
	UIManager::GetInstance()->SetStateofScreen(EButtonsName::IndCities, bIsChecked);
}

void UMarkersDropDown::OnPakistanCitiesCheckBox(bool bIsChecked)
{
	UIManager::GetInstance()->SetStateofScreen(EButtonsName::PakCities, bIsChecked);
}


