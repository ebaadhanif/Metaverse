// Fill out your copyright notice in the Description page of Project Settings.


#include "VRTrails.h"
#include "../Menus/UIManager.h"
#include "../VR_Menus/VRWidgetActor.h"
#include "../VR_Menus/VRBattlespaceGraphics.h"

void UVRTrails::NativeConstruct()
{
	if (TrailsOnOffButton)
	{
		TrailsOnOffButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		TrailsOnOffButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		TrailsOnOffButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsTrailLifetime, ImageITrailToggle);
		TrailsOnOffButton->OnClicked.Clear();
		TrailsOnOffButton->OnClicked.AddUniqueDynamic(this, &UVRTrails::OnTrailsOnOffButtonClick);
	}
	if (Trail1MinButton)
	{
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsTrail1Min, Image1MinToggle);
		Trail1MinButton->OnClicked.Clear();
		Trail1MinButton->OnClicked.AddUniqueDynamic(this, &UVRTrails::OnTrail1MinButtonClick);
	}
	if (Trail30SecButton)
	{
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsTrail30Sec, Image30SecToggle);
		Trail30SecButton->OnClicked.Clear();
		Trail30SecButton->OnClicked.AddUniqueDynamic(this, &UVRTrails::OnTrail30SecButtonClick);
	}
	if (TrailLifetimeButton)
	{
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsTrailLifetime, ImageLifetimeToggle);
		TrailLifetimeButton->OnClicked.Clear();
		TrailLifetimeButton->OnClicked.AddUniqueDynamic(this, &UVRTrails::OnTrailLifetimeButtonClick);
	}
	if (BackButton)
	{
		BackButton->OnClicked.Clear();
		BackButton->OnClicked.AddUniqueDynamic(this, &UVRTrails::OnBackButtonClick);
	}
	if (HomeButton)
	{
		HomeButton->OnClicked.Clear();
		HomeButton->OnClicked.AddUniqueDynamic(this, &UVRTrails::OnHomeButtonClick);
	}

}

void UVRTrails::OnTrailsOnOffButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::VerticalTrail);
	UIManager::GetInstance()->SetState(EButtonsName::HorizontalTrail);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsTrail, ImageITrailToggle);
	
}

void UVRTrails::OnTrail1MinButtonClick()
{
	if (UIManager::GetInstance()->ButtonSates.bIsTrail == false)
	{
		UpdateVisual(false, Image1MinToggle);
		UpdateVisual(false, Image30SecToggle);
		UpdateVisual(false, ImageLifetimeToggle);
		return;
	}
	UIManager::GetInstance()->SetState(EButtonsName::Trail1Min);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsTrail1Min, Image1MinToggle);
	UpdateVisual(false, Image30SecToggle);
	UpdateVisual(false, ImageLifetimeToggle);
}

void UVRTrails::OnTrail30SecButtonClick()
{
	if (UIManager::GetInstance()->ButtonSates.bIsTrail == false)
	{
		UpdateVisual(false, Image1MinToggle);
		UpdateVisual(false, Image30SecToggle);
		UpdateVisual(false, ImageLifetimeToggle);
		return;
	}
	UIManager::GetInstance()->SetState(EButtonsName::Trail30Sec);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsTrail30Sec, Image30SecToggle);
	UpdateVisual(false, Image1MinToggle);
	UpdateVisual(false, ImageLifetimeToggle);

}

void UVRTrails::OnTrailLifetimeButtonClick()
{
	if (UIManager::GetInstance()->ButtonSates.bIsTrail == false)
	{
		UpdateVisual(false, Image1MinToggle);
		UpdateVisual(false, Image30SecToggle);
		UpdateVisual(false, ImageLifetimeToggle);
		return;
	}
	UIManager::GetInstance()->SetState(EButtonsName::TrailLifetime);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsTrailLifetime, ImageLifetimeToggle);
	UpdateVisual(false, Image1MinToggle);
	UpdateVisual(false, Image30SecToggle);
}
void UVRTrails::OnBackButtonClick()
{
	BackButtonClick();
}

void UVRTrails::OnHomeButtonClick()
{
	HomeButtonClick();
}