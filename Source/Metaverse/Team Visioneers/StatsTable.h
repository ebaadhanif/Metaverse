// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "../Team Visioneers/ExerciseStatsManager.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "StatsTable.generated.h"

/**
 * 
 */

class UTextBlock;
class UImage;
class UButton;

UCLASS()
class METAVERSE_API UStatsTable : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:


	UPROPERTY(meta = (BindWidget))
	UButton* Button_1;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_2;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_3;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_4;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_5;



	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text1;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text2;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text3;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text4;


	UPROPERTY(meta = (BindWidget))
	UTextBlock* TotalAll;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AliveAll;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DeadAll;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TotalBlue;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AliveBlue;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DeadBlue;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TotalRed;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AliveRed;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DeadRed;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TotalNeutral;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AliveNeutral;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DeadNeutral;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TotalOther;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AliveOther;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DeadOther;





	UPROPERTY(meta = (BindWidget))
	UImage* Image_1;

	UPROPERTY(meta = (BindWidget))
	UImage* Image_2;

	UPROPERTY(meta = (BindWidget))
	UImage* Image_3;

	UPROPERTY(meta = (BindWidget))
	UImage* Image_4;

	UPROPERTY(meta = (BindWidget))
	UImage* Image_5;


	void UpdateStatsTableData(int Index, EntityStats StatsData);

	void DisabledAllImages();
	void ChangeTextsForSpecificType();



	UFUNCTION()
	void OnButton1Clicked();

	UFUNCTION()
	void OnButton2Clicked();

	UFUNCTION()
	void OnButton3Clicked();

	UFUNCTION()
	void OnButton4Clicked();

	UFUNCTION()
	void OnButton5Clicked();
	
};
