#include "StatsTable.h"
#include "StatsTable.h"
#include "DisplayManager.h"


void UStatsTable::NativeConstruct()
{
	Super::NativeConstruct();

	DisabledAllImages();
	Image_1->SetIsEnabled(true);

	if (Button_1)
	{
		Button_1->OnClicked.AddUniqueDynamic(this, &UStatsTable::OnButton1Clicked);
	}
	if (Button_2)
	{
		Button_2->OnClicked.AddUniqueDynamic(this, &UStatsTable::OnButton2Clicked);
	}
	if (Button_3)
	{
		Button_3->OnClicked.AddUniqueDynamic(this, &UStatsTable::OnButton3Clicked);
	}
	if (Button_4)
	{
		Button_4->OnClicked.AddUniqueDynamic(this, &UStatsTable::OnButton4Clicked);
	}
	if (Button_5)
	{
		Button_5->OnClicked.AddUniqueDynamic(this, &UStatsTable::OnButton5Clicked);
	}
}




void UStatsTable::UpdateStatsTableData(int Index,EntityStats StatsData)
{
	DisabledAllImages();

	switch (Index)
	{
	case -1:
	case 0:
		Image_1->SetIsEnabled(true);
		Text1->SetText(FText::FromString(TEXT("Blue")));
		Text1->SetColorAndOpacity(FSlateColor(FLinearColor::Blue));
		Text2->SetText(FText::FromString(TEXT("Red")));
		Text2->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
		Text3->SetText(FText::FromString(TEXT("Neutral")));
		Text3->SetColorAndOpacity(FSlateColor(FLinearColor::Green));
		Text4->SetText(FText::FromString(TEXT("Other")));
		Text4->SetColorAndOpacity(FSlateColor(FLinearColor::Yellow));
		break;
	case 1:
		Image_2->SetIsEnabled(true);
		ChangeTextsForSpecificType();
		break;
	case 2:
		Image_3->SetIsEnabled(true);
		ChangeTextsForSpecificType();
		break;
	case 3:
		Image_4->SetIsEnabled(true);
		ChangeTextsForSpecificType();
		break;
	case 4:
		Image_5->SetIsEnabled(true);
		ChangeTextsForSpecificType();
		break;

	}

	

	if (TotalAll)
	{
		int data;
		switch (Index) 
		{
		case -1:
		case 0:
			data = StatsData.TotatlEntities;
			break;
		case 1:
			data = StatsData.FriendlyEntities;
			break;
		case 2:
			data = StatsData.EnemyEntities;
			break;
		case 3:
			data = StatsData.NeutralEntities;
			break;
		case 4:
			data = StatsData.OtherEntities;
			break;
		default:
			break;
		}
		FString  TotatlEntities = FString::FromInt(data);
		TotalAll->SetText(FText::FromString(TotatlEntities));
	}

	if (AliveAll)
	{
		int data;
		switch (Index)
		{
		case -1:
		case 0:
			data = StatsData.AliveEntities;
			break;
		case 1:
			data = StatsData.FriendlyAliveEntities;
			break;
		case 2:
			data = StatsData.EnemyAliveEntities;
			break;
		case 3:
			data = StatsData.NeutralAliveEntities;
			break;
		case 4:
			data = StatsData.OtherAliveEntities;
			break;
		default:
			break;
		}
		FString  AllAlive = FString::FromInt(data);
		AliveAll->SetText(FText::FromString(AllAlive));
	}

	if (DeadAll)
	{
		int data;
		switch (Index)
		{
		case -1:
		case 0:
			data = StatsData.DeadEntities;
			break;
		case 1:
			data = StatsData.FriendlyDeadEntities;
			break;
		case 2:
			data = StatsData.EnemyDeadEntities;
			break;
		case 3:
			data = StatsData.NeutralDeadEntities;
			break;
		case 4:
			data = StatsData.OtherDeadEntities;
			break;
		default:
			break;
		}

		FString  AllDead = FString::FromInt(data);
		DeadAll->SetText(FText::FromString(AllDead));
	}
	if (TotalBlue)
	{
		int data;
		switch (Index)
		{
		case -1:
		case 0:
			data = StatsData.FriendlyEntities;
			break;
		case 1:
			data = StatsData.FriendlyAirEntities;
			break;
		case 2:
			data = StatsData.EnemyAirEntities;
			break;
		case 3:
			data = StatsData.NeutralAirEntities;
			break;
		case 4:
			data = StatsData.OtherAirEntities;
			break;
		default:
			break;
		}

		FString  BlueTotal = FString::FromInt(data);
		TotalBlue->SetText(FText::FromString(BlueTotal));
	}
	if (AliveBlue)
	{
		int data;
		switch (Index)
		{
		case -1:
		case 0:
			data = StatsData.FriendlyAliveEntities;
			break;
		case 1:
			data = StatsData.FriendlyAirActiveEntities;
			break;
		case 2:
			data = StatsData.EnemyAirActiveEntities;
			break;
		case 3:
			data = StatsData.NeutralAirActiveEntities;
			break;
		case 4:
			data = StatsData.OtherAirActiveEntities;
			break;
		default:
			break;
		}
		FString  BlueAlive = FString::FromInt(data);
		AliveBlue->SetText(FText::FromString(BlueAlive));
	}
	if (DeadBlue)
	{
		int data;
		switch (Index)
		{
		case -1:
		case 0:
			data = StatsData.FriendlyDeadEntities;
			break;
		case 1:
			data = StatsData.FriendlyAirDeadEntities;
			break;
		case 2:
			data = StatsData.EnemyAirDeadEntities;
			break;
		case 3:
			data = StatsData.NeutralAirDeadEntities;
			break;
		case 4:
			data = StatsData.OtherAirDeadEntities;
			break;
		default:
			break;
		}
		FString  BlueDead = FString::FromInt(data);
		DeadBlue->SetText(FText::FromString(BlueDead));

	}
	if (TotalRed)
	{
		int data;
		switch (Index)
		{
		case -1:
		case 0:
			data = StatsData.EnemyEntities;
			break;
		case 1:
			data = StatsData.FriendlyGroundEntities;
			break;
		case 2:
			data = StatsData.EnemyGroundEntities;
			break;
		case 3:
			data = StatsData.NeutralGroundEntities;
			break;
		case 4:
			data = StatsData.OtherGroundEntities;
			break;
		default:
			break;
		}
		FString  RedTotal = FString::FromInt(data);
		TotalRed->SetText(FText::FromString(RedTotal));
	}
	if (AliveRed)
	{
		int data;
		switch (Index)
		{
		case -1:
		case 0:
			data = StatsData.EnemyAliveEntities;
			break;
		case 1:
			data = StatsData.FriendlyGroundActiveEntities;
			break;
		case 2:
			data = StatsData.EnemyGroundActiveEntities;
			break;
		case 3:
			data = StatsData.NeutralGroundActiveEntities;
			break;
		case 4:
			data = StatsData.OtherGroundActiveEntities;
			break;
		default:
			break;
		}

		FString  RedAlive = FString::FromInt(data);
		AliveRed->SetText(FText::FromString(RedAlive));
	}
	if (DeadRed)
	{
		int data;
		switch (Index)
		{
		case -1:
		case 0:
			data = StatsData.EnemyDeadEntities;
			break;
		case 1:
			data = StatsData.FriendlyGroundDeadEntities;
			break;
		case 2:
			data = StatsData.EnemyGroundDeadEntities;
			break;
		case 3:
			data = StatsData.NeutralGroundDeadEntities;
			break;
		case 4:
			data = StatsData.OtherGroundDeadEntities;
			break;
		default:
			break;
		}

		FString  RedDead = FString::FromInt(data);
		DeadRed->SetText(FText::FromString(RedDead));
	}
	if (TotalNeutral)
	{
		int data;
		switch (Index)
		{
		case -1:
		case 0:
			data = StatsData.NeutralEntities;
			break;
		case 1:
			data = StatsData.FriendlySeaEntities;
			break;
		case 2:
			data = StatsData.EnemySeaEntities;
			break;
		case 3:
			data = StatsData.NeutralSeaEntities;
			break;
		case 4:
			data = StatsData.OtherSeaEntities;
			break;
		default:
			break;
		}

		FString  NeutralTotal = FString::FromInt(data);
		TotalNeutral->SetText(FText::FromString(NeutralTotal));

	}

	if (AliveNeutral)
	{
		int data;
		switch (Index)
		{
		case -1:
		case 0:
			data = StatsData.NeutralAliveEntities;
			break;
		case 1:
			data = StatsData.FriendlySeaActiveEntities;
			break;
		case 2:
			data = StatsData.EnemySeaActiveEntities;
			break;
		case 3:
			data = StatsData.NeutralSeaActiveEntities;
			break;
		case 4:
			data = StatsData.OtherSeaActiveEntities;
			break;
		default:
			break;
		}

		FString  NeutralAlive = FString::FromInt(data);
		AliveNeutral->SetText(FText::FromString(NeutralAlive));
	}
	if (DeadNeutral)
	{
		int data;
		switch (Index)
		{
		case -1:
		case 0:
			data = StatsData.NeutralDeadEntities;
			break;
		case 1:
			data = StatsData.FriendlySeaDeadEntities;
			break;
		case 2:
			data = StatsData.EnemySeaDeadEntities;
			break;
		case 3:
			data = StatsData.NeutralSeaDeadEntities;
			break;
		case 4:
			data = StatsData.OtherSeaDeadEntities;
			break;
		default:
			break;
		}

		FString  NeutralDead = FString::FromInt(data);
		DeadNeutral->SetText(FText::FromString(NeutralDead));

	}
	if (TotalOther)
	{
		int data;
		switch (Index)
		{
		case -1:
		case 0:
			data = StatsData.OtherEntities;
			break;
		case 1:
			data = StatsData.FriendlyMisiles;
			break;
		case 2:
			data = StatsData.EnemyMisiles;
			break;
		case 3:
			data = StatsData.NeutralMisiles;
			break;
		case 4:
			data = StatsData.OtherMisiles;
			break;
		default:
			break;
		}

		FString  OtherTotal = FString::FromInt(data);
		TotalOther->SetText(FText::FromString(OtherTotal));

	}

	if (AliveOther)
	{
		int data;
		switch (Index)
		{
		case -1:
		case 0:
			data = StatsData.OtherAliveEntities;
			break;
		case 1:
			data = StatsData.FriendlyActiveMisiles;
			break;
		case 2:
			data = StatsData.EnemyActiveMisiles;
			break;
		case 3:
			data = StatsData.NeutralActiveMisiles;
			break;
		case 4:
			data = StatsData.OtherActiveMisiles;
			break;
		default:
			break;
		}

		FString  OtherAlive = FString::FromInt(data);
		AliveOther->SetText(FText::FromString(OtherAlive));

	}

	if (DeadOther)
	{
		int data=0;
		switch (Index)
		{
		case -1:
		case 0:
			data = StatsData.OtherDeadEntities;
			break;
		case 1:
			data = StatsData.FriendlyDeadMisiles;
			break;
		case 2:
			data = StatsData.EnemyDeadEntities;
			break;
		case 3:
			data = StatsData.NeutralDeadEntities;
			break;
		case 4:
			data = StatsData.OtherDeadMisiles;
			break;
		default:
			break;
		}
		FString  OtherDead = FString::FromInt(data);
		DeadOther->SetText(FText::FromString(OtherDead));

	}

	


}



void UStatsTable::DisabledAllImages()
{
	Image_1->SetIsEnabled(false);
	Image_2->SetIsEnabled(false);
	Image_3->SetIsEnabled(false);
	Image_4->SetIsEnabled(false);
	Image_5->SetIsEnabled(false);
}




void UStatsTable::ChangeTextsForSpecificType()
{
	Text1->SetText(FText::FromString(TEXT("Air")));
	Text1->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	Text2->SetText(FText::FromString(TEXT("Land")));
	Text2->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	Text3->SetText(FText::FromString(TEXT("Surface")));
	Text3->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	Text4->SetText(FText::FromString(TEXT("Missile")));
	Text4->SetColorAndOpacity(FSlateColor(FLinearColor::White));
}

void UStatsTable::OnButton1Clicked()
{
	ADisplayManager::GetInstance()->FreeCamPawn->StatsTableImageIndex = 0;
	UpdateStatsTableData(0, AExerciseStatsManager::GetInstance()->GetEntityStats());
}


void UStatsTable::OnButton2Clicked()
{
	ADisplayManager::GetInstance()->FreeCamPawn->StatsTableImageIndex = 1;
	UpdateStatsTableData(1, AExerciseStatsManager::GetInstance()->GetEntityStats());

}

void UStatsTable::OnButton3Clicked()
{
	ADisplayManager::GetInstance()->FreeCamPawn->StatsTableImageIndex = 2;
	UpdateStatsTableData(2, AExerciseStatsManager::GetInstance()->GetEntityStats());

}

void UStatsTable::OnButton4Clicked()
{
	ADisplayManager::GetInstance()->FreeCamPawn->StatsTableImageIndex = 3;
	UpdateStatsTableData(3, AExerciseStatsManager::GetInstance()->GetEntityStats());

}

void UStatsTable::OnButton5Clicked()
{
	ADisplayManager::GetInstance()->FreeCamPawn->StatsTableImageIndex = 4;
	UpdateStatsTableData(4, AExerciseStatsManager::GetInstance()->GetEntityStats());

}