// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphicsDropDown.h"
#include "UIManager.h"
#include "../ScalingManager.h"
#include "../Team RenderStorm/ModeManager.h"
#include "../VR_Menus/VRTrails.h"

void UGraphicsDropDown::NativeConstruct()
{
	if (EntityLabelChcekbox)
	{
		setState(UIManager::GetInstance()->ButtonSates.bIsEntityLabels, EntityLabelChcekbox);
		EntityLabelChcekbox->OnCheckStateChanged.Clear();
		EntityLabelChcekbox->OnCheckStateChanged.AddUniqueDynamic(this, &UGraphicsDropDown::OnEntityLabelCheckBox);
	}
	if (ScalingCheckbox)
	{
		//setState(UIManager::GetInstance()->ButtonSates.bIsEntityLabels, EntityLabelChcekbox);
		//calingCheckbox->OnCheckStateChanged.Clear();
		ScalingCheckbox->OnCheckStateChanged.AddUniqueDynamic(this, &UGraphicsDropDown::OnScalingCheckBox);
	}
	if (AircraftCoveragesCheckBox)
	{
		setState(UIManager::GetInstance()->ButtonSates.bIsAircraftCoverage, AircraftCoveragesCheckBox);
		AircraftCoveragesCheckBox->OnCheckStateChanged.Clear();
		AircraftCoveragesCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UGraphicsDropDown::OnAircraftCoveragesCheckBox);
	}
	if (HeadingVectorChcekbox)
	{
		setState(UIManager::GetInstance()->ButtonSates.bIsHeadingVector, HeadingVectorChcekbox);
		HeadingVectorChcekbox->OnCheckStateChanged.Clear();
		HeadingVectorChcekbox->OnCheckStateChanged.AddUniqueDynamic(this, &UGraphicsDropDown::OnHeadingVectorCheckBox);
	}
	if (HeightCheckbox)
	{
		setState(UIManager::GetInstance()->ButtonSates.bIsDownVector, HeightCheckbox);
		HeightCheckbox->OnCheckStateChanged.Clear();
		HeightCheckbox->OnCheckStateChanged.AddUniqueDynamic(this, &UGraphicsDropDown::OnHeightCheckBox);
	}
	if (HeightVectorRings)
	{
		setState(UIManager::GetInstance()->ButtonSates.bIsHeightVectorRings, HeightVectorRings);
		HeightVectorRings->OnCheckStateChanged.Clear();
		HeightVectorRings->OnCheckStateChanged.AddUniqueDynamic(this, &UGraphicsDropDown::OnGroundVectorRingsCheckBox);
	}
	if (OrientationUpCheckbox)
	{
		setState(UIManager::GetInstance()->ButtonSates.bIsUpVector, OrientationUpCheckbox);
		OrientationUpCheckbox->OnCheckStateChanged.Clear();
		OrientationUpCheckbox->OnCheckStateChanged.AddUniqueDynamic(this, &UGraphicsDropDown::OnOrientationUpCheckBox);
	}
	if (HorizontalTrailButton)
	{
		HorizontalTrailButton->OnClicked.Clear();
		HorizontalTrailButton->OnClicked.AddUniqueDynamic(this, &UGraphicsDropDown::OnHorizontalTrailButtonClick);
	}
	if (EntityVisualsButton)
	{
		EntityVisualsButton->OnClicked.Clear();
		EntityVisualsButton->OnClicked.AddUniqueDynamic(this, &UGraphicsDropDown::OnEntityVisualsButtonClick);
	}
	if (VerticalTrailButton)
	{
		VerticalTrailButton->OnClicked.Clear();
		VerticalTrailButton->OnClicked.AddUniqueDynamic(this, &UGraphicsDropDown::OnVerticalTrailButtonClick);
	}
	if (LocklinesButton)
	{
		LocklinesButton->OnClicked.Clear();
		LocklinesButton->OnClicked.AddUniqueDynamic(this, &UGraphicsDropDown::OnLocklinesButtonClick);
	}
	if (GroundCoveragesButton)
	{
		GroundCoveragesButton->OnClicked.Clear();
		GroundCoveragesButton->OnClicked.AddUniqueDynamic(this, &UGraphicsDropDown::OnGroundCoveragesButtonClick);
	}
	if (StateBlink_CheckBox)
	{
		//setState(UIManager::GetInstance()->ButtonSates.bIsUpVector, OrientationUpCheckbox);
		StateBlink_CheckBox->OnCheckStateChanged.Clear();
		StateBlink_CheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UGraphicsDropDown::onBlinkCheckboxClicked);
	}
	if (AModeManager::getInstance()->getActiveMode())
	{
		ApplyMode(AModeManager::getInstance()->getActiveMode());
	}
}

void UGraphicsDropDown::ApplyMode(UMetaverseMode* Mode)
{
	if (!Mode)
	{
		return;
	}
	if (EntityLabelChcekbox)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::EntityLabels))
		{
			EntityLabelChcekbox->SetVisibility(State->Visibility);
 			EntityLabelChcekbox->SetIsChecked(State->FeatureActive);
		}
		else
		{
			EntityLabelChcekbox->SetVisibility(ESlateVisibility::Collapsed);
			EntityLabelChcekbox->SetIsChecked(false);
		}
	}
	if (AircraftCoveragesCheckBox)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::AircraftCoverage))
		{
			AircraftCoveragesCheckBox->SetVisibility(State->Visibility);
			AircraftCoveragesCheckBox->SetIsChecked(State->FeatureActive);
		}
		else
		{
			AircraftCoveragesCheckBox->SetVisibility(ESlateVisibility::Collapsed);
			AircraftCoveragesCheckBox->SetIsChecked(false);
		}
	}
	if (HeadingVectorChcekbox)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::HeadingVector))
		{
			HeadingVectorChcekbox->SetVisibility(State->Visibility);
			HeadingVectorChcekbox->SetIsChecked(State->FeatureActive);
		}
		else
		{
			HeadingVectorChcekbox->SetVisibility(ESlateVisibility::Collapsed);
			HeadingVectorChcekbox->SetIsChecked(false);
		}
	}
	if (HeightCheckbox)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::DownVector))
		{
			HeightCheckbox->SetVisibility(State->Visibility);
			HeightCheckbox->SetIsChecked(State->FeatureActive);
		}
		else
		{
			HeightCheckbox->SetVisibility(ESlateVisibility::Collapsed);
			HeightCheckbox->SetIsChecked(false);
		}
	}
	if (HeightVectorRings)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::HeightVectorRings))
		{
			HeightVectorRings->SetVisibility(State->Visibility);
			HeightVectorRings->SetIsChecked(State->FeatureActive);
		}
		else
		{
			HeightVectorRings->SetVisibility(ESlateVisibility::Collapsed);
			HeightVectorRings->SetIsChecked(false);
		}
	}
	if (OrientationUpCheckbox)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::UpVector))
		{
			OrientationUpCheckbox->SetVisibility(State->Visibility);
			OrientationUpCheckbox->SetIsChecked(State->FeatureActive);
		}
		else
		{
			OrientationUpCheckbox->SetVisibility(ESlateVisibility::Collapsed);
			OrientationUpCheckbox->SetIsChecked(false);
		}
	}
	if (HorizontalTrailButton)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::HorizontalTrail))
		{
			HorizontalTrailButton->SetVisibility(State->Visibility);
		}
		else
		{
			HorizontalTrailButton->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	if (VerticalTrailButton)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::VerticalTrail))
		{
			VerticalTrailButton->SetVisibility(State->Visibility);
		}
		else
		{
			VerticalTrailButton->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	if (LocklinesButton)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::AllLocklines))
		{
			LocklinesButton->SetVisibility(State->Visibility);
		}
		else
		{
			LocklinesButton->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	if (EntityVisualsButton)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::EntityVisuals))
		{
			EntityVisualsButton->SetVisibility(State->Visibility);
		}
		else
		{
			EntityVisualsButton->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	if (GroundCoveragesButton)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::GroundCoverages))
		{
			GroundCoveragesButton->SetVisibility(State->Visibility);
		}
		else
		{
			GroundCoveragesButton->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	if (ScalingCheckbox)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::Scaling))
		{
			ScalingCheckbox->SetVisibility(State->Visibility);
			ScalingCheckbox->SetIsChecked(State->FeatureActive);
		}
		else
		{
			ScalingCheckbox->SetVisibility(ESlateVisibility::Collapsed);
			ScalingCheckbox->SetIsChecked(false);
		}
	}
}

void UGraphicsDropDown::CloseGraphicsOpenMenu()
{
	for (UUserWidget* OpenedMenu1 : OpenGraphicsMenu)
	{
		if (OpenedMenu1)
			OpenedMenu1->RemoveFromViewport();
			//OpenedMenu1->SetVisibility(ESlateVisibility::Hidden);
	}
	OpenGraphicsMenu.Empty();
}

void UGraphicsDropDown::OnHorizontalTrailButtonClick()
{
	auto* TrailsWidget = Cast<UTrailsDropDown>(UIManager::GetInstance()->MenuWidgetMap[EMenus::TrailDropDown].Get());
	UMetaverseMode* Mode = UIManager::GetInstance()->GetActiveMode();
	if (!Mode)
		return;
	//if (!HorizontalTrailState)
	//{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::HorizontalTrail))
		{
			const bool bNewState = State->FeatureActive;  

			UIManager::GetInstance()->SetStateofScreen(EButtonsName::HorizontalTrail, bNewState);
			HorizontalTrailState = true;
			CloseGraphicsOpenMenu();

			TObjectPtr<UUserWidget>* Found2 = UIManager::GetInstance()->MenuWidgetMap.Find(EMenus::TrailDropDown);
			UUserWidget* FoundPtr2 = Found2->Get();

			if (!FoundPtr2->IsInViewport())
			{
				UIManager::GetInstance()->ShowMenu(EMenus::TrailDropDown);
				if (TrailsWidget) {
					TrailsWidget->InitializeChannel(ETrailChannel::Horizontal); TrailsWidget->ApplyMode(AModeManager::getInstance()->getActiveMode());
				}

				FVector2D SubMenuPosition1 = UIManager::GetInstance()->CalculateForwardMenuPosition(this, HorizontalTrailButton, FoundPtr2);
				FoundPtr2->SetRenderTranslation(SubMenuPosition1);
				//FoundPtr2->SetVisibility(ESlateVisibility::Visible);
				UIManager::GetInstance()->OpenMenu.Add(FoundPtr2);
				OpenGraphicsMenu.Add(FoundPtr2);
			}
			else {
				UIManager::GetInstance()->HideMenu(EMenus::TrailDropDown);
			}

		}
	//}
	//else
	//{
	//	HorizontalTrailState = false;
	//	UIManager::GetInstance()->HideMenu(EMenus::TrailDropDown);
	//}
}


void UGraphicsDropDown::OnVerticalTrailButtonClick()
{
	auto* TrailsWidget = Cast<UTrailsDropDown>(UIManager::GetInstance()->MenuWidgetMap[EMenus::TrailDropDown].Get());
	UMetaverseMode* Mode = UIManager::GetInstance()->GetActiveMode();
	if (!Mode)
		return;
	//if (!VerticalStateState)
	//{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::VerticalTrail))
		{
			const bool bNewState = State->FeatureActive;  

			UIManager::GetInstance()->SetStateofScreen(EButtonsName::VerticalTrail, bNewState);
			VerticalStateState = true;
			CloseGraphicsOpenMenu();
			TObjectPtr<UUserWidget>* Found3 = UIManager::GetInstance()->MenuWidgetMap.Find(EMenus::TrailDropDown);
			UUserWidget* FoundPtr3 = Found3->Get();

			if (!FoundPtr3->IsInViewport())
			{
				UIManager::GetInstance()->ShowMenu(EMenus::TrailDropDown);
				if (TrailsWidget) { TrailsWidget->InitializeChannel(ETrailChannel::Vertical); TrailsWidget->ApplyMode(UIManager::GetInstance()->GetActiveMode()); }
				FVector2D SubMenuPosition3 = UIManager::GetInstance()->CalculateForwardMenuPosition(this, VerticalTrailButton, FoundPtr3);
				FoundPtr3->SetRenderTranslation(SubMenuPosition3);
				//FoundPtr3->SetVisibility(ESlateVisibility::Visible);
				UIManager::GetInstance()->OpenMenu.Add(FoundPtr3);
				OpenGraphicsMenu.Add(FoundPtr3);
			}
			else {
				UIManager::GetInstance()->HideMenu(EMenus::TrailDropDown);
			}

		}

	//}
	//else
	//{
	//	//UIManager::GetInstance()->SetState(EButtonsName::VerticalTrail);
	//	VerticalStateState = false;
	//	UIManager::GetInstance()->HideMenu(EMenus::TrailDropDown);
	//}
}

void UGraphicsDropDown::OnLocklinesButtonClick()
{
	//if (!LocklinesState)
	//{
		LocklinesState = true;
		CloseGraphicsOpenMenu();
		TObjectPtr<UUserWidget>* Found4 = UIManager::GetInstance()->MenuWidgetMap.Find(EMenus::LocklinesDropDown);
		UUserWidget* FoundPtr4 = Found4->Get();

		if (!FoundPtr4->IsInViewport())
		{
			UIManager::GetInstance()->ShowMenu(EMenus::LocklinesDropDown);

			FVector2D SubMenuPosition4 = UIManager::GetInstance()->CalculateForwardMenuPosition(this, LocklinesButton, FoundPtr4);
			FoundPtr4->SetRenderTranslation(SubMenuPosition4);
			//FoundPtr4->SetVisibility(ESlateVisibility::Visible);
			UIManager::GetInstance()->OpenMenu.Add(FoundPtr4);
			OpenGraphicsMenu.Add(FoundPtr4);
		}
		else {
			UIManager::GetInstance()->HideMenu(EMenus::LocklinesDropDown);
		}

	//}
	//else
	//{
	//	LocklinesState = false;
	//	UIManager::GetInstance()->HideMenu(EMenus::LocklinesDropDown);
	//}
}

void UGraphicsDropDown::OnGroundCoveragesButtonClick()
{
	//if (!CoveragesState)
	//{
		CoveragesState = true;
		CloseGraphicsOpenMenu();
		TObjectPtr<UUserWidget>* Found5 = UIManager::GetInstance()->MenuWidgetMap.Find(EMenus::CoveragesDropDown);
		UUserWidget* FoundPtr5 = Found5->Get();
		if (!FoundPtr5->IsInViewport())
		{
			UIManager::GetInstance()->ShowMenu(EMenus::CoveragesDropDown);
			FVector2D SubMenuPosition5 = UIManager::GetInstance()->CalculateForwardMenuPosition(this, GroundCoveragesButton, FoundPtr5);
			FoundPtr5->SetRenderTranslation(SubMenuPosition5);
			//FoundPtr5->SetVisibility(ESlateVisibility::Visible);
			UIManager::GetInstance()->OpenMenu.Add(FoundPtr5);
			OpenGraphicsMenu.Add(FoundPtr5);
		}
		else{
			UIManager::GetInstance()->HideMenu(EMenus::CoveragesDropDown);
		}



	//}
	//else
	//{
	//	CoveragesState = false;
	//	UIManager::GetInstance()->HideMenu(EMenus::CoveragesDropDown);
	//}
}

void UGraphicsDropDown::OnEntityVisualsButtonClick()
{
	//if (!EntityVisualsState)
	//{
		EntityVisualsState = true;
		CloseGraphicsOpenMenu();

		TObjectPtr<UUserWidget>* Found6 = UIManager::GetInstance()->MenuWidgetMap.Find(EMenus::EntityVisualsDropDown);
		UUserWidget* FoundPtr6 = Found6->Get();
		if (!FoundPtr6->IsInViewport())
		{
			UIManager::GetInstance()->ShowMenu(EMenus::EntityVisualsDropDown);
			FVector2D SubMenuPosition6 = UIManager::GetInstance()->CalculateForwardMenuPosition(this, EntityVisualsButton, FoundPtr6);
			FoundPtr6->SetRenderTranslation(SubMenuPosition6);
			//FoundPtr6->SetVisibility(ESlateVisibility::Visible);
			UIManager::GetInstance()->OpenMenu.Add(FoundPtr6);
			OpenGraphicsMenu.Add(FoundPtr6);
		}
		else {
			UIManager::GetInstance()->HideMenu(EMenus::EntityVisualsDropDown);
		}


	//}
	//else
	//{
	//	EntityVisualsState = false;
	//	UIManager::GetInstance()->HideMenu(EMenus::CoveragesDropDown);
	//}
}


void UGraphicsDropDown::OnEntityLabelCheckBox(bool bIsChecked)
{
	UIManager::GetInstance()->SetStateofScreen(EButtonsName::EntityLabels , bIsChecked);
}

void UGraphicsDropDown::OnScalingCheckBox(bool bIsChecked)
{
	AScalingManager::GetInstance()->scale = bIsChecked;
	UIManager::GetInstance()->SetStateofScreen(EButtonsName::Scaling , bIsChecked);
}

void UGraphicsDropDown::OnAircraftCoveragesCheckBox(bool bIsChecked)
{
	UIManager::GetInstance()->SetStateofScreen(EButtonsName::AircraftCoverage, bIsChecked);
}

void UGraphicsDropDown::OnHeadingVectorCheckBox(bool bIsChecked)
{
	UIManager::GetInstance()->SetStateofScreen(EButtonsName::HeadingVector, bIsChecked);
}

void UGraphicsDropDown::OnHeightCheckBox(bool bIsChecked)
{
	UIManager::GetInstance()->SetStateofScreen(EButtonsName::DownVector , bIsChecked);
	UMetaverseMode* Mode = UIManager::GetInstance()->GetActiveMode();
	if (!Mode)
		return;
	if (bIsChecked == false && !HeightCheckbox->IsChecked())
	{
		HeightVectorRings->SetIsChecked(false);
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::HeightVectorRings))
		{
			State->FeatureActive = false;
		}
	}
}

void UGraphicsDropDown::OnGroundVectorRingsCheckBox(bool bIsChecked)
{
	//UIManager::GetInstance()->SetStateofScreen(EButtonsName::HeightVectorRings, bIsChecked);
	UMetaverseMode* Mode = UIManager::GetInstance()->GetActiveMode();
	if (!Mode)
		return;
	if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::DownVector))
	{
		const bool NewState = State->FeatureActive;
		if (bIsChecked == true && NewState == true)
		{
			HeightVectorRings->SetIsChecked(true);
			if (FButtonStateStruct* StateRings = Mode->ButtonStates.Find(EButtonsName::HeightVectorRings))
			{
				StateRings->FeatureActive = true;
				const bool bNewState = State->FeatureActive;
				UIManager::GetInstance()->SetStateofScreen(EButtonsName::HeightVectorRings, bNewState);

			}
			else
			{
				StateRings->FeatureActive = false;
				const bool bNewState = State->FeatureActive;
				UIManager::GetInstance()->SetStateofScreen(EButtonsName::HeightVectorRings, bNewState);

			}	
		}
		else
		{
			if (FButtonStateStruct* StateRings = Mode->ButtonStates.Find(EButtonsName::HeightVectorRings))
			{
				StateRings->FeatureActive = false;
			}
			HeightVectorRings->SetIsChecked(false);
			UIManager::GetInstance()->SetStateofScreen(EButtonsName::HeightVectorRings, false);

		}
	}
	
}

void UGraphicsDropDown::OnOrientationUpCheckBox(bool bIsChecked)
{
	UIManager::GetInstance()->SetStateofScreen(EButtonsName::UpVector, bIsChecked);
}

void UGraphicsDropDown::onBlinkCheckboxClicked(bool bIsChecked)
{
	UIManager::GetInstance()->SetStateofScreen(EButtonsName::Blink, bIsChecked);
}
