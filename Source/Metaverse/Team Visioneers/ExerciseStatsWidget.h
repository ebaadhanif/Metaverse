// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "../Team Visioneers/ExerciseStatsManager.h"
#include "ExerciseStatsWidget.generated.h"

/**
 * 
 */

class UTextBlock;
class UImage;


UCLASS()
class METAVERSE_API UExerciseStatsWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* T_Entities;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* A_Entities;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* G_Entities;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* S_Entities;




	UPROPERTY(meta = (BindWidget))
	UTextBlock* f_Entities;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* O_Entities;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* N_Entities;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Other_Entities;



	UPROPERTY(meta = (BindWidget))
	UTextBlock* F_Air_Active_Entities;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* F_Air_Dead_Entities;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* O_Air_Active_Entities;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* O_Air_Dead_Entities;


	UPROPERTY(meta = (BindWidget))
	UTextBlock* Misile_Entities;








	void UpdateStatsData(EntityStats StatsData);





	
};
