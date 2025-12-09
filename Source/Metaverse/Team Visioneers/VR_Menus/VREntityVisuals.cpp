// Fill out your copyright notice in the Description page of Project Settings.


#include "VREntityVisuals.h"
#include "../DisplayManager.h"

void UVREntityVisuals::NativeConstruct()
{
	if (TextureModelButton)
	{
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsTextureModel, ImageTexturedToggle);
		TextureModelButton->OnClicked.Clear();
		TextureModelButton->OnClicked.AddUniqueDynamic(this, &UVREntityVisuals::OnTextureModelButtonClick);
	}
	if (ColoredModelButton)
	{
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsForceBasedModel, ImageColoredToggle);
		ColoredModelButton->OnClicked.Clear();
		ColoredModelButton->OnClicked.AddUniqueDynamic(this, &UVREntityVisuals::OnColoredModelButtonClick);
	}
	if (Mil2525Button)
	{
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsMil2525Model, ImageMil25Toggle);
		Mil2525Button->OnClicked.Clear();
		Mil2525Button->OnClicked.AddUniqueDynamic(this, &UVREntityVisuals::OnMil2525ButtonClick);
	}
	if (SmallModelButton)
	{
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsEntitySmall, ImageEntitySmallToggle);
		SmallModelButton->OnClicked.Clear();
		SmallModelButton->OnClicked.AddUniqueDynamic(this, &UVREntityVisuals::OnSmallModelButtonClick);
	}
	if (MediumModelButton)
	{
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsEntityMedium, ImageEntityMediumToggle);
		MediumModelButton->OnClicked.Clear();
		MediumModelButton->OnClicked.AddUniqueDynamic(this, &UVREntityVisuals::OnMediumModelButtonClick);
	}
	if (LargeModelButton)
	{
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsEntityLarge, ImageEntityLargeToggle);
		LargeModelButton->OnClicked.Clear();
		LargeModelButton->OnClicked.AddUniqueDynamic(this, &UVREntityVisuals::OnLargeModelButtonClick);
	}
	if (BackButton)
	{
		BackButton->OnClicked.Clear();
		BackButton->OnClicked.AddUniqueDynamic(this, &UVREntityVisuals::OnBackButtonClick);
	}
	if (HomeButton)
	{
		HomeButton->OnClicked.Clear();
		HomeButton->OnClicked.AddUniqueDynamic(this, &UVREntityVisuals::OnHomeButtonClick);
	}
}

void UVREntityVisuals::OnTextureModelButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::TextureModel);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsTextureModel, ImageTexturedToggle);
	UpdateVisual(false, ImageMil25Toggle);
	UpdateVisual(false, ImageColoredToggle);
}

void UVREntityVisuals::OnColoredModelButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::ForceBasedModel);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsForceBasedModel, ImageColoredToggle);
	UpdateVisual(false, ImageMil25Toggle);
	UpdateVisual(false, ImageTexturedToggle);
}

void UVREntityVisuals::OnMil2525ButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::Mil2525Model);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsMil2525Model, ImageMil25Toggle);
	UpdateVisual(false, ImageTexturedToggle);
	UpdateVisual(false, ImageColoredToggle);
}

void UVREntityVisuals::OnSmallModelButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::EntitySmall);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsEntitySmall, ImageEntitySmallToggle);
	UpdateVisual(false, ImageEntityMediumToggle);
	UpdateVisual(false, ImageEntityLargeToggle);
}

void UVREntityVisuals::OnMediumModelButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::EntityMedium);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsEntityMedium, ImageEntityMediumToggle);
	UpdateVisual(false, ImageEntitySmallToggle);
	UpdateVisual(false, ImageEntityLargeToggle);

}

void UVREntityVisuals::OnLargeModelButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::EntityLarge);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsEntityLarge, ImageEntityLargeToggle);
	UpdateVisual(false, ImageEntitySmallToggle);
	UpdateVisual(false, ImageEntityMediumToggle);

}

void UVREntityVisuals::OnBackButtonClick()
{
	BackButtonClick();
}

void UVREntityVisuals::OnHomeButtonClick()
{
	HomeButtonClick();
}