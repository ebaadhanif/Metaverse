// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Math/Vector2D.h"
#include "UIManager.h"

void UMainMenu::NativeConstruct()
{
	MenuDepth = 0;
	ElapsedTime = 0.0f;
	if (FileButton)
	{
		FileButton->OnClicked.Clear();
		FileButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::OnFileButtonClick);
	}
	if (ViewButton)
	{
		ViewButton->OnClicked.Clear();
		ViewButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::OnViewButtonClick);
	}
	if (SettingsButton)
	{
		SettingsButton->OnClicked.Clear();
		SettingsButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::OnSettingsButtonClick);
	}
	if (HelpButton)
	{
		HelpButton->OnClicked.Clear();
		HelpButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::OnHelpButtonClick);
	}
	if (ObserverButton)
	{
		ObserverButton->OnClicked.Clear();
		ObserverButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::OnObserverButtonClick);
	}
	//UpdateTime();
	//if (GetWorld())
	//{
	//	FTimerHandle TimerHansler;
	//	GetWorld()->GetTimerManager().SetTimer(TimerHansler, this, &UMainMenu::UpdateTime, 1.0f, true);
	//}
	//UpdateScreenTime();
	//if (GetWorld())
	//{
	//	GetWorld()->GetTimerManager().SetTimer(ScreenTimeTimerHandler, this, &UMainMenu::UpdateScreenTime, 1.0f, true);
	//}
}

void UMainMenu::NativeDestruct()
{
	if (UWorld* World =GetWorld())
	{
		World->GetTimerManager().ClearTimer(ScreenTimeTimerHandler);
	}
	Super::NativeDestruct();
}

void UMainMenu::OnViewButtonClick()
{
	UIManager::GetInstance()->HideMenu(UIManager::GetInstance()->OpenedMenu);
	UIManager::GetInstance()->CloseAllOpenMenu();
	UIManager::GetInstance()->close();
	UIManager::GetInstance()->ShowMenu(EMenus::ViewDropDown);
	TObjectPtr<UUserWidget>* Found = UIManager::GetInstance()->MenuWidgetMap.Find(EMenus::ViewDropDown);
	UUserWidget* FoundPtr = Found->Get();
	UIManager::GetInstance()->Toggle(this, ViewButton, FoundPtr, 0.f, 0.3f); 
	
}

void UMainMenu::OnFileButtonClick()
{
	UIManager::GetInstance()->HideMenu(UIManager::GetInstance()->OpenedMenu);
	UIManager::GetInstance()->CloseAllOpenMenu();
	UIManager::GetInstance()->ShowMenu(EMenus::FileDropDown);
	TObjectPtr<UUserWidget>* Found = UIManager::GetInstance()->MenuWidgetMap.Find(EMenus::FileDropDown);
	UUserWidget* FoundPtr = Found->Get();
	UIManager::GetInstance()->Toggle(this, FileButton, FoundPtr, 0.f, 0.3f);
}

void UMainMenu::OnSettingsButtonClick()
{
	UIManager::GetInstance()->HideMenu(UIManager::GetInstance()->OpenedMenu);
	UIManager::GetInstance()->CloseAllOpenMenu();
	UIManager::GetInstance()->ShowMenu(EMenus::SettingsDropDown);
	TObjectPtr<UUserWidget>* Found = UIManager::GetInstance()->MenuWidgetMap.Find(EMenus::SettingsDropDown);
	UUserWidget* FoundPtr = Found->Get();
	UIManager::GetInstance()->Toggle(this, SettingsButton, FoundPtr, 0.f, 0.3f);	
}

void UMainMenu::OnHelpButtonClick()
{
	UIManager::GetInstance()->HideMenu(UIManager::GetInstance()->OpenedMenu);
	UIManager::GetInstance()->CloseAllOpenMenu();
	UIManager::GetInstance()->ShowMenu(EMenus::HelpDropDown);
	TObjectPtr<UUserWidget>* Found = UIManager::GetInstance()->MenuWidgetMap.Find(EMenus::HelpDropDown);
	UUserWidget* FoundPtr = Found->Get();
	UIManager::GetInstance()->Toggle(this, HelpButton, FoundPtr, 0.f, 0.3f);
}

void UMainMenu::OnObserverButtonClick()
{
	UIManager::GetInstance()->HideMenu(UIManager::GetInstance()->OpenedMenu);
	UIManager::GetInstance()->CloseAllOpenMenu();
	UIManager::GetInstance()->ShowMenu(EMenus::ObserverDropDown);
	TObjectPtr<UUserWidget>* Found = UIManager::GetInstance()->MenuWidgetMap.Find(EMenus::ObserverDropDown);
	UUserWidget* FoundPtr = Found->Get();
	UIManager::GetInstance()->Toggle(this, ObserverButton, FoundPtr, 0.f, 0.3f);
}

void UMainMenu::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	OneSecondTime += InDeltaTime;
	
}
//void UMainMenu::UpdateScreenTime()
//{
//	ElapsedTime += 1.0f;
//	int32 Hours = FMath::FloorToInt(ElapsedTime / 3600);
//	int32 Mins = FMath::FloorToInt(FMath::Fmod(ElapsedTime / 60, 60));
//	int32 Secs = FMath::FloorToInt(FMath::Fmod(ElapsedTime, 60));
//	FString TimeString = FString::Printf(TEXT("%02d:%02d:%02d"), Hours, Mins, Secs);
//	if (ScreenTimeText)
//		ScreenTimeText->SetText(FText::FromString(TimeString));
//}
//
//void UMainMenu::UpdateTime()
//{
//	FDateTime Now = FDateTime::Now();
//	FString TimeString = FString::Printf(TEXT("%02d:%02d:%02d"), Now.GetHour(), Now.GetMinute(), Now.GetSecond());
//	if (ClockTimeText)
//	{
//		ClockTimeText->SetText(FText::FromString(TimeString));
//	}
//}
//
//void UMainMenu::SetFPS(int fps) {
//	FPSText->SetText(FText::AsNumber(fps));
//}