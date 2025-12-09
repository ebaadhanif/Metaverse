// Fill out your copyright notice in the Description page of Project Settings.


#include "ListDropDown.h"
#include "../DisplayManager.h"
#include "UIManager.h"

void UListDropDown::NativeConstruct()
{
	MenuDepth = 1;

	if (HookButton)
	{
		HookButton->OnClicked.Clear();
		HookButton->OnClicked.AddUniqueDynamic(this, &UListDropDown::OnHookButtonClick);
	}
	if (UnHookButton)
	{
		UnHookButton->OnClicked.Clear();
		UnHookButton->OnClicked.AddUniqueDynamic(this, &UListDropDown::OnUnHookButtonClick);
		UnHookButton->SetIsEnabled(false);
	}
}

void UListDropDown::OnHookButtonClick()
{
	UMetaverseMode* Mode = UIManager::GetInstance()->GetActiveMode();
	if (!Mode)
		return;
	if (UnHookButton)
	{
		UnHookButton->SetIsEnabled(true);
	}
	if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::Hook))
	{
		const bool bNewState = State->FeatureActive;
		UIManager::GetInstance()->SetStateofScreen(EButtonsName::Hook, bNewState);
	}

}

void UListDropDown::OnUnHookButtonClick()
{
	UMetaverseMode* Mode = UIManager::GetInstance()->GetActiveMode();
	if (!Mode)
		return;
	if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::Unhook))
	{
		const bool bNewState = State->FeatureActive;
		UIManager::GetInstance()->SetStateofScreen(EButtonsName::Unhook, bNewState);
	}

}
