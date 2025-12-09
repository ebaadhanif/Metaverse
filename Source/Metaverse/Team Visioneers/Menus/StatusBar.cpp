// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusBar.h"
#include "UIManager.h"

void UStatusBar::NativeConstruct()
{
	MenuDepth = 0;

	UpdateTime();
	if (GetWorld())
	{
		FTimerHandle TimerHansler;
		GetWorld()->GetTimerManager().SetTimer(TimerHansler, this, &UStatusBar::UpdateTime, 1.0f, true);
	}
	UpdateScreenTime();
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(ScreenTimeTimerHandler, this, &UStatusBar::UpdateScreenTime, 1.0f, true);
	}
}
void UStatusBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	OneSecondTime += InDeltaTime;
	FPS++;
	if (OneSecondTime >= 1.0f) {
		FPSText->SetText(FText::AsNumber(FPS));
		FPS = 0;
		OneSecondTime = 0;
	}


}

//void UStatusBar::SetUIManagerInstance(UIManager* instance)
//{
//	UIManagerInstance = instance;
//}

void UStatusBar::UpdateScreenTime()
{
	ElapsedTime += 1.0f;
	int32 Hours = FMath::FloorToInt(ElapsedTime / 3600);
	int32 Mins = FMath::FloorToInt(FMath::Fmod(ElapsedTime / 60, 60));
	int32 Secs = FMath::FloorToInt(FMath::Fmod(ElapsedTime, 60));
	FString TimeString = FString::Printf(TEXT("%02d:%02d:%02d"), Hours, Mins, Secs);
	if (ScreenTimeText)
		ScreenTimeText->SetText(FText::FromString(TimeString));
}

void UStatusBar::UpdateTime()
{
	FDateTime Now = FDateTime::Now();
	FString TimeString = FString::Printf(TEXT("%02d:%02d:%02d"), Now.GetHour(), Now.GetMinute(), Now.GetSecond());
	if (ExerciseTimeText)
	{
		ExerciseTimeText->SetText(FText::FromString(TimeString));
	}
}

void UStatusBar::SetFPS(int fps) {
	FPSText->SetText(FText::AsNumber(fps));
}