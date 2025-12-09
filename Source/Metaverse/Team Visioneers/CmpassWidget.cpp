// Fill out your copyright notice in the Description page of Project Settings.


#include "CmpassWidget.h"
#include "Components/Image.h"
#include "Components/ScaleBox.h"




void UCmpassWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ApplyCustomDPIScalling();


}


void UCmpassWidget::UpdateCompassNeedle(float Yaw)
{
	if (!CompassNeedleImage) return;
	//UE_LOG(LogTemp, Log, TEXT("VR Mode Enabled"), Yaw);

	float CompassYaw = FMath::Fmod(Yaw - 90.f + 360.f, 360.f);
	CompassYaw = FMath::Fmod(CompassYaw+180.f,360.f);
	float RotationAngle = -CompassYaw;
	CompassNeedleImage->SetRenderTransformAngle(RotationAngle);

	if (CompassYawText)
	{
		//FString ab = FString::Printf(TEXT("Yaw: %.2f"), GetDisplayValue(GetNormalizedYaw(Yaw + 90)));
		
		FString YawString = GetDisplayValue(GetNormalizedYaw(Yaw + 90));
		//GEngine->AddOnScreenDebugMessage(-1, 0.5, FColor::Green, "Yaw "+YawString);

		CompassYawText->SetText(FText::FromString(YawString));
	}
}

float UCmpassWidget::GetNormalizedYaw(float Yaw)
{
	return fmod(fmod(Yaw , 360) + 360,360);
}

FString UCmpassWidget::GetDisplayValue(float Yaw)
{
	if (Yaw > 355 || Yaw < 5)
		return FString("N");
	if (Yaw > 175 && Yaw < 185)
		return FString("S");
	if (Yaw > 85 && Yaw < 95)
		return FString("E");
	if (Yaw > 265 && Yaw < 275)
		return FString("W");



	if (Yaw > 40 && Yaw < 50)
		return FString("NE");
	if (Yaw > 310 && Yaw < 320)
		return FString("NW");
	if (Yaw > 130 && Yaw < 140)
		return FString("SE");
	if (Yaw > 220 && Yaw < 230)
		return FString("SW");

	return FString::Printf(TEXT("%.0f"), Yaw);
}






void UCmpassWidget::ApplyCustomDPIScalling()
{ 
	if (!DPI_Curve || !RootScaleBox) return;

	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);
	float ScreenHeight = ViewportSize.Y;
	float Scale = DPI_Curve->GetFloatValue(ScreenHeight);
	RootScaleBox->SetRenderTransform(FWidgetTransform(FVector2D::ZeroVector,FVector2D(Scale,Scale),FVector2D::ZeroVector,0.0f));
}
