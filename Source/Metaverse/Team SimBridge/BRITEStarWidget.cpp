// Fill out your copyright notice in the Description page of Project Settings.


#include "BRITEStarWidget.h"

void UBRITEStarWidget::NativeConstruct()
{
	CurrentFOV = EFieldOfView::MFOV;

}

void UBRITEStarWidget::NextFOV()
{
	if (CurrentFOV != EFieldOfView::SNFOV)
	{
		int tempFOV = static_cast<int>(CurrentFOV);
		tempFOV++;
		CurrentFOV = static_cast<EFieldOfView>(tempFOV);

		UpdateReticle();
	}

}

void UBRITEStarWidget::PrevFOV()
{
	if (CurrentFOV != EFieldOfView::WFOV)
	{
		int tempFOV = static_cast<int>(CurrentFOV);
		tempFOV--;
		CurrentFOV = static_cast<EFieldOfView>(tempFOV);
		UpdateReticle();
	}
}



void UBRITEStarWidget::SetOwnLatLong(double Latitude, double Longitude)
{
	FString LatText = FString::Printf(TEXT("%.0f"), Latitude);
	FString LongText = FString::Printf(TEXT("%.0f"), Longitude);
	OwnLatText->SetText(FText::FromString(LatText));
	OwnLonText->SetText(FText::FromString(LongText));
}

void UBRITEStarWidget::SetTargetLatLong(double Latitude, double Longitude)
{
	FString LatText = FString::Printf(TEXT("%.0f"), Latitude);
	FString LongText = FString::Printf(TEXT("%.0f"), Longitude);
	TgtLatText->SetText(FText::FromString(LatText));
	TgtLatText->SetText(FText::FromString(LongText));
}

void UBRITEStarWidget::SetTargetDistance(double Distance)
{
	FString DistanceText = FString::Printf(TEXT("%.0f"), Distance);

	TgtDistText->SetText(FText::FromString(DistanceText));


}

void UBRITEStarWidget::SetTargetAltitude(double Altitude)
{
	FString AltitudeText = FString::Printf(TEXT("%.0f"), Altitude);

	TgtAltText->SetText(FText::FromString(AltitudeText));

}





void UBRITEStarWidget::SetAzimuthCarret( float PositionX)
{
	//Los = Los - 90;
	//GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Black, FString::Printf(TEXT("Value: %f"), Los));
	FVector2D CarretAnchor = FVector2D(PositionX, -15.42865);
	if (HorizontalCaretCanvasSlot) {
		HorizontalCaretCanvasSlot->SetPosition(CarretAnchor);
	}
	else
	{
		HorizontalCaretCanvasSlot = Cast<UCanvasPanelSlot>(Horizontal_CaretImage->Slot);
	}

	if (!azimuthbarsSlot) {
		azimuthbarsSlot = Cast<UCanvasPanelSlot>(azimuthbars->Slot);
		//ContainSize = azimuthbarsSlot->GetSize();
		
	}

}

void UBRITEStarWidget::Update(double Azimuth, double Elevation, float AzimuthCarretAnchor, float ElevationCarretAnchor)
{
	SetAzimuth(Azimuth);
	SetElevationAngle(Elevation);
	SetAzimuthCarret(AzimuthCarretAnchor);
	SetElevationCarret(ElevationCarretAnchor);
}





void UBRITEStarWidget::SetElevationCarret( float  PositionY)
{
	//Los = Los - 90;
	//GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Black, FString::Printf(TEXT("Value: %f"), Los));
	FVector2D CarretAnchor = FVector2D(104.0, PositionY);
	if (elevationBarsSlot) {
		elevationBarsSlot->SetPosition(CarretAnchor);
	}
	else
	{
		elevationBarsSlot = Cast<UCanvasPanelSlot>(Vertical_CaretImage->Slot);
	}

	if (!azimuthbarsSlot) {
		azimuthbarsSlot = Cast<UCanvasPanelSlot>(elevationBars->Slot);
		//ContainSize = azimuthbarsSlot->GetSize();

	}

}
void UBRITEStarWidget::SetHeadingStripImage(FVector2D LOS)
{

	if (LOSBarStripSlot) {
		LOSBarStripSlot->SetPosition(LOS);
	}
	else
	{
		LOSBarStripSlot = Cast<UCanvasPanelSlot>(HeadingStripImage->Slot);
	}

	//if (!azimuthbarsSlot) {
	//	azimuthbarsSlot = Cast<UCanvasPanelSlot>(elevationBars->Slot);
	//	//ContainSize = azimuthbarsSlot->GetSize();

	//}


}

void UBRITEStarWidget::SetAzimuth(float AzAngle)
{
	FString AngleText = FString::Printf(TEXT("%.0f"), AzAngle);
	OwnAzimuthText->SetText(FText::FromString(AngleText));
}


void UBRITEStarWidget::SetLOSValue(float LOS)
{
	FString LOSText = FString::Printf(TEXT("%.0f"), LOS);
	LOSValue->SetText(FText::FromString(LOSText));
}
void UBRITEStarWidget::SetElevationAngle(float ElvAngle)
{
	FString ElvAngleText = FString::Printf(TEXT("%.0f"), ElvAngle);
	E1Text->SetText(FText::FromString(ElvAngleText));
}
void UBRITEStarWidget::SetDate()
{
	FDateTime Now = FDateTime::Now();
	FString TimeString = FString::Printf(TEXT("%02d-%02d-%02d"), Now.GetDay(), Now.GetMonth(), Now.GetYear());
	if (Datetext)
	{
		Datetext->SetText(FText::FromString(TimeString));
	}

}

void UBRITEStarWidget::SetTime()
{
	FDateTime Now = FDateTime::Now();
	FString TimeString = FString::Printf(TEXT("%02d:%02d:%02d E"), Now.GetHour(), Now.GetMinute(), Now.GetSecond());
	if (TimeText)
	{
		TimeText->SetText(FText::FromString(TimeString));
	}

}



void UBRITEStarWidget::FormateDate()
{

}

//void UBRITEStarWidget::SetTargetLatLong(double Latitude, double Longitude)
//{
//	FString LatText = FString::Printf(TEXT("%.0d"), Latitude);
//	FString LongText = FString::Printf(TEXT("%.0d"), Longitude);
//	TgtLatText->SetText(FText::FromString(LatText));
//	TgtLatText->SetText(FText::FromString(LongText));
//}

void SetAltitude(double Height)
{


}








void UBRITEStarWidget::HideReticle()
{
	crosshairMediumImage->SetVisibility(ESlateVisibility::Hidden);
	crosshairSuperNarrowImage->SetVisibility(ESlateVisibility::Hidden);
	CrosshairNarrowImage->SetVisibility(ESlateVisibility::Hidden);
	CrosshairWideImage->SetVisibility(ESlateVisibility::Hidden);
}

void UBRITEStarWidget::UpdateReticle()
{
	HideReticle();
	switch (CurrentFOV)
	{
	case EFieldOfView::WFOV:
	{
		CrosshairWideImage->SetVisibility(ESlateVisibility::Visible);
		FOVText->SetText(FText::FromString("WFOV"));
		break;
	}
	case EFieldOfView::MFOV:
	{
		crosshairMediumImage->SetVisibility(ESlateVisibility::Visible);
		FOVText->SetText(FText::FromString("MFOV"));
		break;
	}
	case EFieldOfView::NFOV:
	{
		CrosshairNarrowImage->SetVisibility(ESlateVisibility::Visible);
		FOVText->SetText(FText::FromString("NFOV"));
		break;
	}
	case EFieldOfView::SNFOV:
	{
		crosshairSuperNarrowImage->SetVisibility(ESlateVisibility::Visible);
		FOVText->SetText(FText::FromString("SNFOV"));
		break;
	}

	default:
	{
		crosshairMediumImage->SetVisibility(ESlateVisibility::Visible);
		FOVText->SetText(FText::FromString("MFOV"));
	}
	}

}

