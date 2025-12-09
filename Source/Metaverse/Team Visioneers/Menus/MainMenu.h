// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "TimerManager.h"
#include "Components/Border.h"
#include "MenuParent.h"
#include "MainMenu.generated.h"

/**
 *
 */
UCLASS()
class METAVERSE_API UMainMenu : public UMenuParent
{
	GENERATED_BODY()
protected:
	//main menu
	UPROPERTY(meta = (BindWidget))
	UBorder* Border;
	UPROPERTY(meta = (BindWidget))
	UButton* FileButton;
	UPROPERTY(meta = (BindWidget))
	UButton* ViewButton;
	UPROPERTY(meta = (BindWidget))
	UButton* SettingsButton;
	UPROPERTY(meta = (BindWidget))
	UButton* ObserverButton;
	UPROPERTY(meta = (BindWidget))
	UButton* HelpButton;
	//status bar
	/*UPROPERTY(meta = (BindWidget))
	UTextBlock* ObserverLatText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ObserverLonText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ObserverAltText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScreenTimeText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ClockTimeText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ExerciseTimeText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* FPSText;*/
	int FPS = 0;
	float OneSecondTime = 0;
	float ElapsedTime = 0.0f;
	FTimerHandle ScreenTimeTimerHandler;
public:
	UFUNCTION()
	void NativeConstruct();
	UFUNCTION()

	void NativeDestruct();
	//status bar
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void UpdateScreenTime();
	void SetFPS(int fps);
private:
	UFUNCTION()
	void OnViewButtonClick();
	UFUNCTION()
	void OnFileButtonClick();
	UFUNCTION()
	void OnSettingsButtonClick();
	UFUNCTION()
	void OnHelpButtonClick();
	UFUNCTION()
	void OnObserverButtonClick();
	void UpdateTime();
};
