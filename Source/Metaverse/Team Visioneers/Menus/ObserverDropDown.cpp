// Fill out your copyright notice in the Description page of Project Settings.


#include "ObserverDropDown.h"
#include "UIManager.h"

void UObserverDropDown::NativeConstruct()
{
	MenuDepth = 1;

	if (ObserverModeButton)
	{
		ObserverModeButton->OnClicked.Clear();
		ObserverModeButton->OnClicked.AddUniqueDynamic(this, &UObserverDropDown::OnObserverModeButtonClick);
	}
	if (CompassButton)
	{
		CompassButton->OnClicked.Clear();
		CompassButton->OnClicked.AddUniqueDynamic(this, &UObserverDropDown::OnCompassButtonClick);
	}
}

void UObserverDropDown::OnObserverModeButtonClick()
{
}

void UObserverDropDown::OnCompassButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::Compass);
}


