#include "LoadingScreenWidget.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadingScreenWidget.h"

void ULoadingScreenWidget::SetLoadingMessage(const FText& NewMessage)
{
	if (LoadingMessageText)
	{
		
		//NewMessage= FText::FromString(TEXT("Loading ")) + FText::FromString(NewMessage.ToString().LeftChop(2));
		LoadingMessageText->SetText(FText::FromString(FString::Printf(TEXT("Loading %s..."), *GetUpdatedText(NewMessage.ToString().LeftChop(2)))));
	}
}

FString ULoadingScreenWidget::GetUpdatedText(const FString& InputString)
{

	if (InputString.Contains("HanTracking", ESearchCase::IgnoreCase))
	{
		return "Gestures";
	}
	else if (InputString.Contains("ScalingManager", ESearchCase::IgnoreCase))
	{
		return "Entity Modules";
	}
	else if (InputString.Contains("FPSDisplay", ESearchCase::IgnoreCase))
	{
		return "System Modules";
	}
	else if (InputString.Contains("WeatherController", ESearchCase::IgnoreCase))
	{
		return "Weather";
	}
	else if (InputString.Contains("AirBaseManager", ESearchCase::IgnoreCase))
	{
		return "Point Data";
	}
	else if (InputString.Contains("ExerciseStatsManager", ESearchCase::IgnoreCase))
	{
		return "Stats Data";
	}
	else if (InputString.Contains("NetworkManager", ESearchCase::IgnoreCase))
	{
		return "Network Manager";
	}
	else if (InputString.Contains("PCGManager", ESearchCase::IgnoreCase))
	{
		return "PCG Data";
	}
	else
	{
		return "Additional Assets";
	}


}

void ULoadingScreenWidget::SetProgressBar(float ProgressValue)
{
	if (LoadingProgressBar)
	{
		LoadingProgressBar->SetPercent(FMath::Clamp(ProgressValue, 0.0f, 1.0f));
	}
}
