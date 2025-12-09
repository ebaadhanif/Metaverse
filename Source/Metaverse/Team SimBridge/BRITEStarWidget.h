// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "AppConstEnumStruct.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "BRITEStarWidget.generated.h"

/**
 *
 */



UCLASS()
class METAVERSE_API UBRITEStarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	UImage* crosshairMediumImage;

	UPROPERTY(meta = (BindWidget))
	UImage* crosshairSuperNarrowImage;

	UPROPERTY(meta = (BindWidget))
	UImage* CrosshairNarrowImage;

	UPROPERTY(meta = (BindWidget))
	UImage* CrosshairWideImage;

	UPROPERTY(meta = (BindWidget))
	UImage* Horizontal_CaretImage;

	UPROPERTY(meta = (BindWidget))
	UImage* Vertical_CaretImage;

	UPROPERTY(meta = (BindWidget))
	UImage* azimuthbars;

	UPROPERTY(meta = (BindWidget))
	UImage* elevationBars;

	UPROPERTY(meta = (BindWidget))
	UImage* NorthPointerImage;

	UPROPERTY(meta = (BindWidget))
	UImage* HeadingStripImage;
	
	UPROPERTY(meta = (BindWidget))
	UImage* LockBoxImage;


	UPROPERTY(meta = (BindWidget))
	UTextBlock* TgtLatText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TgtLonText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* OwnLatText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* OwnLonText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* OwnAzimuthText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* E1Text;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Datetext;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimeText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TgtDistText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ModeText;


	UPROPERTY(meta = (BindWidget))
	UTextBlock* LockModeText;


	UPROPERTY(meta = (BindWidget))
	UTextBlock* FOVText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CameraModeText;

	/*UPROPERTY(meta = (BindWidget))
	UTextBlock* ;*/

	UPROPERTY(meta = (BindWidget))
	UTextBlock* IRModeText;



	UPROPERTY(meta = (BindWidget))
	UTextBlock* TgtAltText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LOSValue;

	UCanvasPanelSlot* azimuthbarsSlot = nullptr;
	UCanvasPanelSlot* elevationBarsSlot = nullptr;
	UCanvasPanelSlot* LOSBarStripSlot = nullptr;

	FVector2D ContainSize = FVector2D(0, 0);
	FMargin Margin;
	//UPROPERTY(meta = (BindWidget))
	//UTextBlock* TgtLatText;

	//UPROPERTY(meta = (BindWidget))
	//UTextBlock* TgtLatText;

	//UPROPERTY(meta = (BindWidget))
	//UTextBlock* TgtLatText;


	void NextFOV();
	void PrevFOV();
	void HideReticle();
	void UpdateReticle();
	void SetOwnLatLong(double Latitude, double Longitude);
	void SetTargetLatLong(double Latitude, double Longitude);
	void SetAltitude(double Height);
	void SetAzimuthCarret(/*float PlatformHeading, float Los,*/float PositionX);
	void SetElevationCarret(float PositionX);
	void SetHeadingStripImage(FVector2D LOS);
	void SetAzimuth(float AzAngle);
	void SetLOSValue(float LOS);
	

	void SetElevationAngle(float ElvAngle);
	void SetDate();
	void SetTime();
	void FormatTime();
	void FormateDate();
	void SetTargetDistance(double Distance);
	void SetTargetAltitude(double Altitude);
	void Update(double Azimuth, double Elevation, float AzimuthCarretAnchor, float ElevationCarretAnchor);
	
private:
	EFieldOfView CurrentFOV;
	UPROPERTY()
	UCanvasPanelSlot* HorizontalCaretCanvasSlot=nullptr;
	
};
