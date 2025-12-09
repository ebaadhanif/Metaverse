// Fill out your copyright notice in the Description page of Project Settings.


#include "TrailsDropDown.h"
#include "UIManager.h"
#include "../VR_Menus/VRTrails.h"
#include "../VR_Menus/VRWidgetActor.h"
#include "../../Team RenderStorm/RibbonMeshActor.h"
#include "../../Team RenderStorm/VerticalRibbonMeshActor.h"
#include <Metaverse/Team RenderStorm/ModeManager.h>

void UTrailsDropDown::NativeConstruct()
{
	MenuDepth = 2;
	if (Trail30SecChecbox)
	{
		//setState(UIManager::GetInstance()->ButtonSates.bIsTrail30Sec, Trail30SecChecbox);
		Trail30SecChecbox->OnCheckStateChanged.Clear();
		Trail30SecChecbox->OnCheckStateChanged.AddUniqueDynamic(this, &UTrailsDropDown::OnTrail30SecCheckBox);
	}
	if (Trail1MinCheckbox)
	{
		//setState(UIManager::GetInstance()->ButtonSates.bIsTrail1Min, Trail1MinCheckbox);
		Trail1MinCheckbox->OnCheckStateChanged.Clear();
		Trail1MinCheckbox->OnCheckStateChanged.AddUniqueDynamic(this, &UTrailsDropDown::OnTrail1MinCheckBox);
	}
	if (TrailLifetimeCheckbox)
	{
		//setState(UIManager::GetInstance()->ButtonSates.bIsTrailLifetime, TrailLifetimeCheckbox);
		TrailLifetimeCheckbox->OnCheckStateChanged.Clear();
		TrailLifetimeCheckbox->OnCheckStateChanged.AddUniqueDynamic(this, &UTrailsDropDown::OnTrailLifetimeCheckBox);
	}
	if (AModeManager::getInstance()->getActiveMode())
	{
		ApplyMode(AModeManager::getInstance()->getActiveMode());
	}
}

void UTrailsDropDown::ApplyMode(UMetaverseMode* Mode)
{
	if (!Mode) return;
	const TMap<EButtonsName, FButtonStateStruct>& Map = Mode->ButtonStates;
	auto IsOn = [&Map](EButtonsName Name)->bool
		{
			if (const FButtonStateStruct* State = Map.Find(Name))
			{
				return State->FeatureActive;
			}
			return false;
		};
	bool b30 = false;
	bool b60 = false;
	bool bLife = false;

	if (TrailChannel == ETrailChannel::Horizontal)
	{
		b30 = IsOn(EButtonsName::HorizontalTrail30Sec);
		b60 = IsOn(EButtonsName::HorizontalTrail1Min);
		bLife = IsOn(EButtonsName::HorizontalTrailLifetime);
	}
	else
	{
		b30 = IsOn(EButtonsName::VerticalTrail30Sec);
		b60 = IsOn(EButtonsName::VerticalTrail1Min);
		bLife = IsOn(EButtonsName::VerticalTrailLifetime);
	}

	if (Trail30SecChecbox) Trail30SecChecbox->SetIsChecked(b30);
	if (Trail1MinCheckbox) Trail30SecChecbox->SetIsChecked(b60);
	if (TrailLifetimeCheckbox) Trail30SecChecbox->SetIsChecked(bLife);
}

void UTrailsDropDown::OnTrail30SecCheckBox(bool bIsChecked)
{
	if (bIsChecked)
		UncheckOtherCheckboxes(Trail30SecChecbox);
	EButtonsName ButtonEnum = (TrailChannel == ETrailChannel::Horizontal) ? EButtonsName::HorizontalTrail30Sec : EButtonsName::VerticalTrail30Sec;
	UIManager::GetInstance()->SetStateofScreen(ButtonEnum, bIsChecked);
}


void UTrailsDropDown::OnTrail1MinCheckBox(bool bIsChecked)
{

	if (bIsChecked)
		UncheckOtherCheckboxes(Trail1MinCheckbox);
	EButtonsName ButtonEnum = (TrailChannel == ETrailChannel::Horizontal) ? EButtonsName::HorizontalTrail1Min : EButtonsName::VerticalTrail1Min;
	UIManager::GetInstance()->SetStateofScreen(ButtonEnum, bIsChecked);
}


void UTrailsDropDown::OnTrailLifetimeCheckBox(bool bIsChecked)
{
	if (bIsChecked)
		UncheckOtherCheckboxes(TrailLifetimeCheckbox);
	EButtonsName ButtonEnum = (TrailChannel == ETrailChannel::Horizontal) ? EButtonsName::HorizontalTrailLifetime : EButtonsName::VerticalTrailLifetime;
	UIManager::GetInstance()->SetStateofScreen(ButtonEnum, bIsChecked);
}

void UTrailsDropDown::UncheckOtherCheckboxes(UCheckBox* CheckedBox)
{
	if (CheckedBox != Trail30SecChecbox)
	{
		Trail30SecChecbox->SetIsChecked(false);
	}
	if (CheckedBox != Trail1MinCheckbox)
	{
		Trail1MinCheckbox->SetIsChecked(false);
	}
	if (CheckedBox != TrailLifetimeCheckbox)
	{
		TrailLifetimeCheckbox->SetIsChecked(false);
	}
}
