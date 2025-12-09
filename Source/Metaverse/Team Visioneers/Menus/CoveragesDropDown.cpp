// Fill out your copyright notice in the Description page of Project Settings.


#include "CoveragesDropDown.h"
#include "UIManager.h"

void UCoveragesDropDown::NativeConstruct()
{
	if (CoveragesOnCheckbox)
	{
		setState(UIManager::GetInstance()->ButtonSates.bIsGroundCoverages, CoveragesOnCheckbox);
		CoveragesOnCheckbox->OnCheckStateChanged.Clear();
		CoveragesOnCheckbox->OnCheckStateChanged.AddUniqueDynamic(this, &UCoveragesDropDown::OnCoveragesOnCheckBox);
	}
	if (CoveragesFootprintCheckbox)
	{
		setState(UIManager::GetInstance()->ButtonSates.bIsGroundCoveragesFootprints, CoveragesFootprintCheckbox);
		CoveragesFootprintCheckbox->OnCheckStateChanged.Clear();
		CoveragesFootprintCheckbox->OnCheckStateChanged.AddUniqueDynamic(this, &UCoveragesDropDown::OnCoveragesFootprintsCheckBox);
	}
	if (DomeRingsCheckbox)
	{
		setState(UIManager::GetInstance()->ButtonSates.bIsDomeRing, DomeRingsCheckbox);
		DomeRingsCheckbox->OnCheckStateChanged.Clear();
		DomeRingsCheckbox->OnCheckStateChanged.AddUniqueDynamic(this, &UCoveragesDropDown::OnDomeRingsCheckBox);
	}
}


void UCoveragesDropDown::OnCoveragesOnCheckBox(bool bIsChecked)
{
	UIManager::GetInstance()->SetStateofScreen(EButtonsName::GroundCoverages, bIsChecked);
	if (const UMetaverseMode* Mode = UIManager::GetInstance()->GetActiveMode())
	{
		if (const FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::DomeRing))
		{
			if (DomeRingsCheckbox)
			{
				DomeRingsCheckbox->SetIsChecked(State->FeatureActive);
			}
		}
	}

}

void UCoveragesDropDown::OnCoveragesFootprintsCheckBox(bool bIsChecked)
{
	UIManager::GetInstance()->SetStateofScreen(EButtonsName::GroundCoveragesFootprints, bIsChecked);
}

void UCoveragesDropDown::OnDomeRingsCheckBox(bool bIsChecked)
{
	UIManager::GetInstance()->SetStateofScreen(EButtonsName::DomeRing, bIsChecked);

	if (const UMetaverseMode* Mode = UIManager::GetInstance()->GetActiveMode())
	{
		if (const FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::DomeRing))
		{
			if (DomeRingsCheckbox)
			{
				DomeRingsCheckbox->SetIsChecked(State->FeatureActive);
			}
		}
	}
}