// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuParent.h"
#include "StatusBar.generated.h"

/**
 * 
 */
UCLASS()
class METAVERSE_API UStatusBar : public UMenuParent
{
	GENERATED_BODY()

protected:
	//status bar
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ObserverLatText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ObserverLonText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ObserverAltText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScreenTimeText;
	//UPROPERTY(meta = (BindWidget))
	//UTextBlock* ClockTimeText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ExerciseTimeText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* FPSText;
	int FPS = 0;
	float OneSecondTime = 0;
	float ElapsedTime = 0.0f;
	FTimerHandle ScreenTimeTimerHandler;
public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void NativeConstruct();

	void UpdateScreenTime();
	void SetFPS(int fps);
	void UpdateTime();

};
