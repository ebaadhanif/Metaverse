// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityVisualsDropDown.h"
#include "../Team SimBridge/EntityManager.h"
#include "UIManager.h"


void UEntityVisualsDropDown::NativeConstruct()
{
	MenuDepth = 2;
	if (ModelsCheckbox)
	{
		setState(UIManager::GetInstance()->ButtonSates.bIsTextureModel, ModelsCheckbox);
		ModelsCheckbox->OnCheckStateChanged.Clear();
		ModelsCheckbox->OnCheckStateChanged.AddUniqueDynamic(this, &UEntityVisualsDropDown::On3DModelsCheckBox);
	}
	if (ColorizedCheckbox)
	{
		setState(UIManager::GetInstance()->ButtonSates.bIsForceBasedModel, ColorizedCheckbox);
		ColorizedCheckbox->OnCheckStateChanged.Clear();
		ColorizedCheckbox->OnCheckStateChanged.AddUniqueDynamic(this, &UEntityVisualsDropDown::On3DModelsColorizedCheckBox);
	}
	if (Mil2525Chechbox)
	{
		setState(UIManager::GetInstance()->ButtonSates.bIsMil2525Model, Mil2525Chechbox);
		Mil2525Chechbox->OnCheckStateChanged.Clear();
		Mil2525Chechbox->OnCheckStateChanged.AddUniqueDynamic(this, &UEntityVisualsDropDown::OnMil2525CheckBox);
	}

}

void UEntityVisualsDropDown::On3DModelsCheckBox(bool bIsChecked)
{
	if (bIsChecked)
		UncheckOtherCheckboxes(ModelsCheckbox);
	UIManager::GetInstance()->SetStateofScreen(EButtonsName::TextureModel, bIsChecked);
}


void UEntityVisualsDropDown::On3DModelsColorizedCheckBox(bool bIsChecked)
{
	if (bIsChecked)
		UncheckOtherCheckboxes(ColorizedCheckbox);
	UIManager::GetInstance()->SetStateofScreen(EButtonsName::ForceBasedModel, bIsChecked);
}


void UEntityVisualsDropDown::OnMil2525CheckBox(bool bIsChecked)
{
	if (bIsChecked)
		UncheckOtherCheckboxes(Mil2525Chechbox);
	UIManager::GetInstance()->SetStateofScreen(EButtonsName::Mil2525Model, bIsChecked);
}
void UEntityVisualsDropDown::UncheckOtherCheckboxes(UCheckBox* CheckedBox)
{
	if (CheckedBox != ModelsCheckbox)
	{
		ModelsCheckbox->SetIsChecked(false);
	}
	if (CheckedBox != ColorizedCheckbox)
	{
		ColorizedCheckbox->SetIsChecked(false);
	}
	if (CheckedBox != Mil2525Chechbox)
	{
		Mil2525Chechbox->SetIsChecked(false);
	}
}