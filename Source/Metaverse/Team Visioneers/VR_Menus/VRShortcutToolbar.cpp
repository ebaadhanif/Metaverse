// Fill out your copyright notice in the Description page of Project Settings.


#include "VRShortcutToolbar.h"
#include "VRWidgetActor.h"
#include "UIManagerVR.h"
#include "Kismet/GameplayStatics.h"
#include "DWGXDrawingManager.h"
#include "../DisplayManager.h"
#include "../../Team RenderStorm/TrailController.h"
#include "../../Team RenderStorm/RibbonMeshActor.h"
#include "../../Team RenderStorm/VerticalRibbonMeshActor.h"
#include "../../Team RenderStorm/GroundVectorActor.h"
#include "../../Team RenderStorm/ForwardVectorActor.h"
#include "../../Team SimBridge/EntityManager.h"
#include "../../Team SimBridge/EntityBase.h"


void UVRShortcutToolbar::NativeConstruct()
{

	if (CloseButton)
	{
		CloseButton->OnClicked.Clear();
		CloseButton->OnClicked.AddUniqueDynamic(this, &UVRShortcutToolbar::OnCloseButtonClick);
	}

	if (EntityVisualsButton)
	{
		EntityVisualsButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		EntityVisualsButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		EntityVisualsButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsForceBasedModel, ImageVisualsToggle);
		EntityVisualsButton->OnClicked.Clear();
		EntityVisualsButton->OnClicked.AddUniqueDynamic(this, &UVRShortcutToolbar::OnEntityVisualsButtonClick);
	}
	if (EntityLabelsButton)
	{
		EntityLabelsButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		EntityLabelsButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		EntityLabelsButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsEntityLabels, ImageLabelsToggle);
		EntityLabelsButton->OnClicked.Clear();
		EntityLabelsButton->OnClicked.AddUniqueDynamic(this, &UVRShortcutToolbar::OnEntityLabelButtonClick);
	}

	if (LockLinesButton)
	{
		LockLinesButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		LockLinesButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		LockLinesButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsAllLocklines, ImageLocklinesToggle);
		LockLinesButton->OnClicked.Clear();
		LockLinesButton->OnClicked.AddUniqueDynamic(this, &UVRShortcutToolbar::OnLockLinesButtonClick);
	}

	if (CoveragesButton)
	{
		CoveragesButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		CoveragesButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		CoveragesButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsGroundCoverages, ImageCoveragesToggle);
		CoveragesButton->OnClicked.Clear();
		CoveragesButton->OnClicked.AddUniqueDynamic(this, &UVRShortcutToolbar::OnCoveragesButtonClick);
	}

	if (TrailsButton)
	{
		TrailsButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		TrailsButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		TrailsButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsTrailLifetime, ImageTrailsToggle);
		TrailsButton->OnClicked.Clear();
		TrailsButton->OnClicked.AddUniqueDynamic(this, &UVRShortcutToolbar::OnTrailButtonClick);
	}

	if (HeadingVectorButton)
	{
		HeadingVectorButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		HeadingVectorButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		HeadingVectorButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsHeadingVector, ImageHeadingToggle);
		HeadingVectorButton->OnClicked.Clear();
		HeadingVectorButton->OnClicked.AddUniqueDynamic(this, &UVRShortcutToolbar::OnHeadingVectorButtonClick);
	}

	if (HeightVectorButton)
	{
		HeightVectorButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		HeightVectorButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		HeightVectorButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsDownVector, ImageHeightToggle);
		HeightVectorButton->OnClicked.Clear();
		HeightVectorButton->OnClicked.AddUniqueDynamic(this, &UVRShortcutToolbar::OnHeightVectorButtonClick);
	}

	if (RotationUpVectorButton)
	{
		RotationUpVectorButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		RotationUpVectorButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		RotationUpVectorButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsUpVector, ImageRotationToggle);
		RotationUpVectorButton->OnClicked.Clear();
		RotationUpVectorButton->OnClicked.AddUniqueDynamic(this, &UVRShortcutToolbar::OnRotationUpButtonClick);
	}

	if (DrawingsButton)
	{
		DrawingsButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		DrawingsButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		DrawingsButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsDrawings, ImageDrawingsToggle);
		DrawingsButton->OnClicked.Clear();
		DrawingsButton->OnClicked.AddUniqueDynamic(this, &UVRShortcutToolbar::OnDrawingsButtonClick);
	}
}

void UVRShortcutToolbar::SetFPS(int fps) {
	FPS_Text->SetText(FText::AsNumber(fps));
}

void UVRShortcutToolbar::OnCloseButtonClick()
{
	if (this->GetVisibility() == ESlateVisibility::Visible)
	{
		this->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		this->SetVisibility(ESlateVisibility::Visible);
	}
}


void UVRShortcutToolbar::OnEntityVisualsButtonClick()
{
	EVisualsButtonStateVR Current = UIManager::GetInstance()->ButtonSates.EntityVisualStateVR;

	switch (Current)
	{
	case EVisualsButtonStateVR::Off:
	{
		UIManager::GetInstance()->ButtonSates.EntityVisualStateVR = EVisualsButtonStateVR::TextureModel;
		UIManager::GetInstance()->SetState(EButtonsName::TextureModel);
		break;
	}

	case EVisualsButtonStateVR::TextureModel:
	{
		UIManager::GetInstance()->ButtonSates.EntityVisualStateVR = EVisualsButtonStateVR::ForceBasedModel;
		UIManager::GetInstance()->SetState(EButtonsName::ForceBasedModel);
		break;
	}

	case EVisualsButtonStateVR::ForceBasedModel:
	{
		UIManager::GetInstance()->ButtonSates.EntityVisualStateVR = EVisualsButtonStateVR::Mil2525Model;
		UIManager::GetInstance()->SetState(EButtonsName::Mil2525Model);
		break;
	}

	case EVisualsButtonStateVR::Mil2525Model:
	{
		UIManager::GetInstance()->ButtonSates.EntityVisualStateVR = EVisualsButtonStateVR::Off;
		break;
	}
	}

	if (UIManager::GetInstance()->ButtonSates.EntityVisualStateVR == EVisualsButtonStateVR::Off)
	{
		UpdateVisual(false, ImageVisualsToggle);
	}
	else
	{
		UpdateVisual(true, ImageVisualsToggle);
	}
	
}
void UVRShortcutToolbar::OnEntityLabelButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::EntityLabels);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsEntityLabels, ImageLabelsToggle);
}


void UVRShortcutToolbar::OnLockLinesButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::AllLocklines);	
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsAllLocklines, ImageLocklinesToggle);
}

void UVRShortcutToolbar::OnCoveragesButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::GroundCoverages);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsGroundCoverages, ImageCoveragesToggle);
	
}

void UVRShortcutToolbar::OnTrailButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::HorizontalTrail);
	UIManager::GetInstance()->SetState(EButtonsName::VerticalTrail);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsHorizontalTrail, ImageTrailsToggle);
}

void UVRShortcutToolbar::OnHeadingVectorButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::HeadingVector);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsHeadingVector, ImageHeadingToggle);
}

void UVRShortcutToolbar::OnHeightVectorButtonClick()
{
	bool state = UIManager::GetInstance()->ButtonSates.bIsDownVector;
	if (state)
	{

		UpdateVisual(false, ImageHeightToggle);
		UIManager::GetInstance()->ButtonSates.bIsDownVector = false;
	}
	else
	{
		UpdateVisual(true, ImageHeightToggle);
		UIManager::GetInstance()->ButtonSates.bIsDownVector = true;
	}
	UIManager::GetInstance()->SetState(EButtonsName::DownVector);
	UIManager::GetInstance()->SetState(EButtonsName::HeightVectorRings);

}

void UVRShortcutToolbar::OnRotationUpButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::UpVector);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsUpVector, ImageRotationToggle);
}

void UVRShortcutToolbar::OnDrawingsButtonClick()
{
	bool state = UIManager::GetInstance()->ButtonSates.bIsDrawings;
	if (state)
	{
		UpdateVisual(false, ImageDrawingsToggle);
		UIManager::GetInstance()->SetState(EButtonsName::Drawings);
	}
	else
	{
		UpdateVisual(true, ImageDrawingsToggle);
		UDWGXDrawingManager::Get(this)->ClearAllShapes();
	}


}
