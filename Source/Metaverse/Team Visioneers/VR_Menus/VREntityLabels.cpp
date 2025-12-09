// Fill out your copyright notice in the Description page of Project Settings.


#include "VREntityLabels.h"
#include "../DisplayManager.h"

void UVREntityLabels::NativeConstruct()
{
	if (LabelOnOffButton)
	{
		LabelOnOffButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		LabelOnOffButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		LabelOnOffButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsEntityLabels, ImageLabelToggle);
		LabelOnOffButton->OnClicked.Clear();
		LabelOnOffButton->OnClicked.AddUniqueDynamic(this, &UVREntityLabels::OnLabelOnOffButtonClick);
	}
	if (LabelSmallButton)
	{
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsLabelSmall, ImageLabelSmallToggle);
		LabelSmallButton->OnClicked.Clear();
		LabelSmallButton->OnClicked.AddUniqueDynamic(this, &UVREntityLabels::OnLabelSmallButtonClick);
	}
	if (LabelMediumButton)
	{
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsLabelMedium, ImageLabelMediumToggle);
		LabelMediumButton->OnClicked.Clear();
		LabelMediumButton->OnClicked.AddUniqueDynamic(this, &UVREntityLabels::OnLabelMediumButtonClick);
	}
	if (LabelLargeButton)
	{
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsLabelLarge, ImageLabelLargeToggle);
		LabelLargeButton->OnClicked.Clear();
		LabelLargeButton->OnClicked.AddUniqueDynamic(this, &UVREntityLabels::OnLabelLargeButtonClick);
	}
	if (LabelOffset1Button)
	{
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsLabelOffset1, ImageOffset1Toggle);
		LabelOffset1Button->OnClicked.Clear();
		LabelOffset1Button->OnClicked.AddUniqueDynamic(this, &UVREntityLabels::OnLabelOffset1ButtonClick);
	}
	if (LabelOffset2Button)
	{
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsLabelOffset2, ImageOffset2Toggle);
		LabelOffset2Button->OnClicked.Clear();
		LabelOffset2Button->OnClicked.AddUniqueDynamic(this, &UVREntityLabels::OnLabelOffset2ButtonClick);
	}
	if (LabelOffset3Button)
	{
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsLabelOffset3, ImageOffset3Toggle);
		LabelOffset3Button->OnClicked.Clear();
		LabelOffset3Button->OnClicked.AddUniqueDynamic(this, &UVREntityLabels::OnLabelOffset3ButtonClick);
	}
	if (BackButton)
	{
		BackButton->OnClicked.Clear();
		BackButton->OnClicked.AddUniqueDynamic(this, &UVREntityLabels::OnBackButtonClick);
	}
	if (HomeButton)
	{
		HomeButton->OnClicked.Clear();
		HomeButton->OnClicked.AddUniqueDynamic(this, &UVREntityLabels::OnHomeButtonClick);
	}
}

void UVREntityLabels::OnLabelOnOffButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::EntityLabels);
	UpdateVisual(AScalingManager::GetInstance()->isShowLabel, ImageLabelToggle);
}

void UVREntityLabels::OnLabelSmallButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::LabelSmall);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsLabelSmall, ImageLabelSmallToggle);
	UpdateVisual(false, ImageLabelMediumToggle);
	UpdateVisual(false, ImageLabelLargeToggle);
}

void UVREntityLabels::OnLabelMediumButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::LabelMedium);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsLabelMedium, ImageLabelMediumToggle);
	UpdateVisual(false, ImageLabelSmallToggle);
	UpdateVisual(false, ImageLabelLargeToggle);
}

void UVREntityLabels::OnLabelLargeButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::LabelLarge);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsLabelLarge, ImageLabelLargeToggle);
	UpdateVisual(false, ImageLabelSmallToggle);
	UpdateVisual(false, ImageLabelMediumToggle);
}

void UVREntityLabels::OnLabelOffset1ButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::LabelOffset1);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsLabelOffset1, ImageOffset1Toggle);
	UpdateVisual(false, ImageOffset2Toggle);
	UpdateVisual(false, ImageOffset3Toggle);
}

void UVREntityLabels::OnLabelOffset2ButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::LabelOffset2);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsLabelOffset2, ImageOffset2Toggle);
	UpdateVisual(false, ImageOffset3Toggle);
	UpdateVisual(false, ImageOffset1Toggle);
}

void UVREntityLabels::OnLabelOffset3ButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::LabelOffset3);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsLabelOffset3, ImageOffset3Toggle);
	UpdateVisual(false, ImageOffset2Toggle);
	UpdateVisual(false, ImageOffset1Toggle);
}

void UVREntityLabels::OnBackButtonClick()
{
	BackButtonClick();
}

void UVREntityLabels::OnHomeButtonClick()
{
	HomeButtonClick();
}