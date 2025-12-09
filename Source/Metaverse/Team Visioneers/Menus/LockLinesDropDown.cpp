// Fill out your copyright notice in the Description page of Project Settings.


#include "LockLinesDropDown.h"
#include "UIManager.h"
#include "../VR_Menus/VRWidgetActor.h"
#include "../VR_Menus/VRBattlespaceGraphics.h"


void ULockLinesDropDown::NativeConstruct()
{
	if (AllLockinesChcekbox)
	{
		setState(UIManager::GetInstance()->ButtonSates.bIsAllLocklines, AllLockinesChcekbox);
		AllLockinesChcekbox->OnCheckStateChanged.Clear();
		AllLockinesChcekbox->OnCheckStateChanged.AddUniqueDynamic(this, &ULockLinesDropDown::OnAllLocklinesChcekboxClick);
	}
	if (SameLocklinesCheckBox)
	{
		setState(UIManager::GetInstance()->ButtonSates.bIsSameLockline, SameLocklinesCheckBox);
		SameLocklinesCheckBox->OnCheckStateChanged.Clear();
		SameLocklinesCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &ULockLinesDropDown::OnSameLocklinesChcekboxClick);
	}
	if (OpposingLocklinesChcekbox)
	{
		setState(UIManager::GetInstance()->ButtonSates.bIsOpposingLockline, OpposingLocklinesChcekbox);
		OpposingLocklinesChcekbox->OnCheckStateChanged.Clear();
		OpposingLocklinesChcekbox->OnCheckStateChanged.AddUniqueDynamic(this, &ULockLinesDropDown::OnOpposingLocklinesChcekboxClick);
	}

}

void ULockLinesDropDown::OnAllLocklinesChcekboxClick(bool bIsChecked)
{
	if (bUpdatingLocklineUI) return;
	bUpdatingLocklineUI = true;
	if (bIsChecked) {
		if (OpposingLocklinesChcekbox) OpposingLocklinesChcekbox->SetIsEnabled(false);
		if (SameLocklinesCheckBox)     SameLocklinesCheckBox->SetIsEnabled(false);
	}
	else {
		if (OpposingLocklinesChcekbox) OpposingLocklinesChcekbox->SetIsEnabled(true);
		if (SameLocklinesCheckBox)     SameLocklinesCheckBox->SetIsEnabled(true);

	}
	UIManager::GetInstance()->SetStateofScreen(EButtonsName::AllLocklines, bIsChecked);

	bUpdatingLocklineUI = false;
}

void ULockLinesDropDown::OnSameLocklinesChcekboxClick(bool bIsChecked)
{
	if (bUpdatingLocklineUI) return;
	bUpdatingLocklineUI = true;
	if (SameLocklinesCheckBox)     SameLocklinesCheckBox->SetIsChecked(bIsChecked);

	if (bIsChecked)
	{
		if (OpposingLocklinesChcekbox) OpposingLocklinesChcekbox->SetIsEnabled(false);
		if (AllLockinesChcekbox)      AllLockinesChcekbox->SetIsEnabled(false);
	}
	else {
		if (OpposingLocklinesChcekbox) OpposingLocklinesChcekbox->SetIsEnabled(true);
		if (AllLockinesChcekbox)      AllLockinesChcekbox->SetIsEnabled(true);
	}


	UIManager::GetInstance()->SetStateofScreen(EButtonsName::SameLockline, bIsChecked);

	bUpdatingLocklineUI = false;
}

void ULockLinesDropDown::OnOpposingLocklinesChcekboxClick(bool bIsChecked)
{
	if (bUpdatingLocklineUI) return;
	bUpdatingLocklineUI = true;
	if (OpposingLocklinesChcekbox) OpposingLocklinesChcekbox->SetIsChecked(bIsChecked);
	if (bIsChecked) {
		if (SameLocklinesCheckBox)     SameLocklinesCheckBox->SetIsEnabled(false);
		if (AllLockinesChcekbox)      AllLockinesChcekbox->SetIsEnabled(false);
	}
	else {
		if (SameLocklinesCheckBox)     SameLocklinesCheckBox->SetIsEnabled(true);
		if (AllLockinesChcekbox)      AllLockinesChcekbox->SetIsEnabled(true);
	}
	UIManager::GetInstance()->SetStateofScreen(EButtonsName::OpposingLockline, bIsChecked);

	bUpdatingLocklineUI = false;

}
