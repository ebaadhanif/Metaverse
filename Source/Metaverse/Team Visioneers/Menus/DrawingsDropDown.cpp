// Fill out your copyright notice in the Description page of Project Settings.


#include "DrawingsDropDown.h"
#include "UIManager.h"
#include "DWGXDrawingManager.h"



void UDrawingsDropDown::NativeConstruct()
{
	if (DrawingsOnChcekbox)
	{
		setState(UIManager::GetInstance()->ButtonSates.bIsAllLocklines, DrawingsOnChcekbox);
		DrawingsOnChcekbox->OnCheckStateChanged.Clear();
		DrawingsOnChcekbox->OnCheckStateChanged.AddUniqueDynamic(this, &UDrawingsDropDown::OnDrawingsOnChcekbox);
	}
	if (DrawingsProjwctionCheckBox)
	{
		setState(UIManager::GetInstance()->ButtonSates.bIsAllLocklines, DrawingsProjwctionCheckBox);
		DrawingsProjwctionCheckBox->OnCheckStateChanged.Clear();
		DrawingsProjwctionCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UDrawingsDropDown::OnDrawingsProjwctionCheckBox);
	}
	if (ClearDrawingsButton)
	{
		ClearDrawingsButton->OnClicked.Clear();
		ClearDrawingsButton->OnClicked.AddUniqueDynamic(this, &UDrawingsDropDown::OnClearDrawingsButton);
	}
}

void UDrawingsDropDown::ApplyMode(UMetaverseMode* Mode)
{
	if (DrawingsOnChcekbox)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::DrawingsOn))
		{
			DrawingsOnChcekbox->SetVisibility(State->Visibility);
			DrawingsOnChcekbox->SetIsChecked(State->FeatureActive);
		}
		else
		{
			DrawingsOnChcekbox->SetVisibility(ESlateVisibility::Collapsed);
			DrawingsOnChcekbox->SetIsChecked(false);
		}
	}
	if (DrawingsProjwctionCheckBox)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::DrawingsProjection))
		{
			DrawingsProjwctionCheckBox->SetVisibility(State->Visibility);
			DrawingsProjwctionCheckBox->SetIsChecked(State->FeatureActive);
		}
		else
		{
			DrawingsProjwctionCheckBox->SetVisibility(ESlateVisibility::Collapsed);
			DrawingsProjwctionCheckBox->SetIsChecked(false);
		}
	}
	if (ClearDrawingsButton)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::ClearDrawings))
		{
			ClearDrawingsButton->SetVisibility(State->Visibility);
		}
		else
		{
			ClearDrawingsButton->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UDrawingsDropDown::OnDrawingsOnChcekbox(bool bIsChecked)
{
	UIManager::GetInstance()->SetStateofScreen(EButtonsName::Drawings, bIsChecked);
}

void UDrawingsDropDown::OnDrawingsProjwctionCheckBox(bool bIsChecked)
{
	UIManager::GetInstance()->SetStateofScreen(EButtonsName::DrawingsProjection, bIsChecked);
}

void UDrawingsDropDown::OnClearDrawingsButton()
{
	UDWGXDrawingManager::Get(GetWorld())->ClearAllShapes();
}
