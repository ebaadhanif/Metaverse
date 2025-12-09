// Fill out your copyright notice in the Description page of Project Settings.


#include "VRMenuParent.h"
#include "UIManagerVR.h"
#include "../Team Visioneers/DisplayManager.h"


void UVRMenuParent::NativeConstruct()
{

}

void UVRMenuParent::UpdateVisual(bool bIsOn, UImage* image)
{
	if (bIsOn==true && image)
	{
		image->SetVisibility(ESlateVisibility::HitTestInvisible); 
	}
	else
	{
		image->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UVRMenuParent::WidgetHandling(EMenusVR MenuType)
{
	if (MenuType == UIManager::GetInstance()->CurrentMenu) return;
	UIManager::GetInstance()->HideMenuVR(UIManager::GetInstance()->CurrentMenu);
	UIManager::GetInstance()->CurrentMenu = MenuType;
	UIManager::GetInstance()->ShowMenuVR(UIManager::GetInstance()->CurrentMenu);
}

void UVRMenuParent::HomeButtonClick()
{
	if (UIManager::GetInstance()->CurrentMenu == EMenusVR::MainMenu) return;
	UIManager::GetInstance()->HideMenuVR(UIManager::GetInstance()->CurrentMenu);
	UIManager::GetInstance()->ShowMenuVR(EMenusVR::MainMenu);
	UIManager::GetInstance()->CurrentMenu = EMenusVR::MainMenu;
	UIManager::GetInstance()->MenuHistory.Empty();
}

void UVRMenuParent::BackButtonClick()
{
	UIManager* Manager = UIManager::GetInstance();
	if (Manager->CurrentMenu == EMenusVR::MainMenu)
		return;
	if (Manager->MenuHistory.Num() == 0)
	{
		return;
	}

	MenuToHide = Manager->MenuHistory[Manager->MenuHistory.Num()-1];
	Manager->HideMenuVR(MenuToHide);
	Manager->MenuHistory.RemoveAt(Manager->MenuHistory.Num() - 1);
	MenuToDisplay = Manager->MenuHistory[Manager->MenuHistory.Num() - 1];
	Manager->CurrentMenu = MenuToDisplay;
}

//void UVRMenuParent::RefreshVisuals(bool bIsOn, UButton* button)
//{
//	if (button)
//	{
//		button->SetBackgroundColor(bIsOn ? OnColor : OffColor);
//	}
//}
//
//void UVRMenuParent::ApplyColor(bool bIsOn, UButton* button)
//{
//	if (bIsOn)
//	{
//		button->SetBackgroundColor(OnColor);
//	}
//	else
//	{
//		button->SetBackgroundColor(OffColor);
//	}
//}
