// Fill out your copyright notice in the Description page of Project Settings.


#include "ExerciseStatsWidget.h"

void UExerciseStatsWidget::UpdateStatsData(EntityStats StatsData)
{

	if (T_Entities)
	{
		FString  TotatlEntities = FString::FromInt(StatsData.TotatlEntities);
		T_Entities->SetText(FText::FromString(TotatlEntities));
	}

	if (A_Entities)
	{
		FString  AirEntities = FString::FromInt(StatsData.AirEntities);
		A_Entities->SetText(FText::FromString(AirEntities));
	}

	if (G_Entities)
	{
		FString  GroundEntities = FString::FromInt(StatsData.GroundEntities);
		G_Entities->SetText(FText::FromString(GroundEntities));
	}
	if (S_Entities)
	{
		FString  SeaEntities = FString::FromInt(StatsData.SeaEntities);
		S_Entities->SetText(FText::FromString(SeaEntities));
	}
	if (f_Entities)
	{
		FString  FriendlyAirEntities = FString::FromInt(StatsData.FriendlyAirEntities);
		f_Entities->SetText(FText::FromString(FriendlyAirEntities));
	}
	if (O_Entities)
	{
		FString  EnemyAirEntities = FString::FromInt(StatsData.EnemyAirEntities);
		O_Entities->SetText(FText::FromString(EnemyAirEntities));

	}
	if (N_Entities)
	{
		FString  NeutralAirEntities = FString::FromInt(StatsData.NeutralAirEntities);
		N_Entities->SetText(FText::FromString(NeutralAirEntities));
	}
	if (Other_Entities)
	{
		FString  OtherAirEntities = FString::FromInt(StatsData.OtherAirEntities);
		Other_Entities->SetText(FText::FromString(OtherAirEntities));
	}
	if (F_Air_Active_Entities)
	{
		FString  FriendlyAirActiveEntities = FString::FromInt(StatsData.FriendlyAirActiveEntities);
		F_Air_Active_Entities->SetText(FText::FromString(FriendlyAirActiveEntities));
	}
	if (F_Air_Dead_Entities)
	{
		FString  FriendlyAirDeadEntities = FString::FromInt(StatsData.FriendlyAirDeadEntities);
		F_Air_Dead_Entities->SetText(FText::FromString(FriendlyAirDeadEntities));

	}

	if (O_Air_Active_Entities)
	{
		FString  EnemyAirActiveEntities = FString::FromInt(StatsData.EnemyAirActiveEntities);
		O_Air_Active_Entities->SetText(FText::FromString(EnemyAirActiveEntities));
	}
	if (O_Air_Dead_Entities)
	{
		FString  EnemyAirDeadEntities = FString::FromInt(StatsData.EnemyAirDeadEntities);
		O_Air_Dead_Entities->SetText(FText::FromString(EnemyAirDeadEntities));

	}
	if (Misile_Entities)
	{
		FString  Misiles = FString::FromInt(StatsData.Misiles);
		Misile_Entities->SetText(FText::FromString(Misiles));

	}

	

	


}


