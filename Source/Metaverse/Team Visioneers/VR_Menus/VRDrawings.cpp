// Fill out your copyright notice in the Description page of Project Settings.


#include "VRDrawings.h"
#include "../DisplayManager.h"
#include "DWGXDrawingManager.h"

void UVRDrawings::NativeConstruct()
{
	if (DrawingsOnOffButton)
	{
		DrawingsOnOffButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		DrawingsOnOffButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		DrawingsOnOffButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsDrawings, ImageDrawingsToggle);
		DrawingsOnOffButton->OnClicked.Clear();
		DrawingsOnOffButton->OnClicked.AddUniqueDynamic(this, &UVRDrawings::OnDrawingsOnOffButtonClick);
	}
	if (selectFileButton)
	{
		selectFileButton->OnClicked.Clear();
		selectFileButton->OnClicked.AddUniqueDynamic(this, &UVRDrawings::OnselectFileButtonClick);
	}
	if (ClearFileButton)
	{
		ClearFileButton->OnClicked.Clear();
		ClearFileButton->OnClicked.AddUniqueDynamic(this, &UVRDrawings::OnClearFileButtonClick);
	}
	if (BackButton)
	{
		BackButton->OnClicked.Clear();
		BackButton->OnClicked.AddUniqueDynamic(this, &UVRDrawings::OnBackButtonClick);
	}
	if (HomeButton)
	{
		HomeButton->OnClicked.Clear();
		HomeButton->OnClicked.AddUniqueDynamic(this, &UVRDrawings::OnHomeButtonClick);
	}
}

void UVRDrawings::OnDrawingsOnOffButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::Drawings);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsDrawings, ImageDrawingsToggle);
}


void UVRDrawings::OnselectFileButtonClick()
{
	ACesiumGeoreference* Goereference = ACesiumGeoreference::GetDefaultGeoreference(GetWorld());
	ACesium3DTileset* Tileset = Cast< ACesium3DTileset>(UGameplayStatics::GetActorOfClass(GetWorld(), ACesium3DTileset::StaticClass()));
	IShape::SetTileset(Tileset);
	IShape::SetGeoreference(Goereference);

	UDWGXDrawingManager::Get(GetWorld())->LoadDrawingConfig();
	UDWGXDrawingManager::Get(GetWorld())->LoadDrawingFromFileExplorer();
}

void UVRDrawings::OnClearFileButtonClick()
{
	UDWGXDrawingManager::Get(GetWorld())->ClearAllShapes();
}

void UVRDrawings::OnBackButtonClick()
{
	BackButtonClick();
}

void UVRDrawings::OnHomeButtonClick()
{
	HomeButtonClick();
}