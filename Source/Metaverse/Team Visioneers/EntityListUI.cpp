// Fill out your copyright notice in the Description page of Project Settings.

#include "EntityListUI.h"
#include "Components/ScrollBox.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/SizeBox.h"
#include "DisplayManager.h"
#include "Camera/CameraActor.h"
#include "FreeCameraPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Menus/UIManager.h"
#include "../Team SimBridge/EntityBase.h"
#include "../Team SimBridge/EntityManager.h"

void UEntityListUI::NativeConstruct()
{
	Super::NativeConstruct();
	SearchTextBox->OnTextChanged.AddUniqueDynamic(this, &UEntityListUI::OnSearchTextChanged);
}

void UEntityListUI::AddEntityCallsignTolist(AEntityBase* entity)
{
	/*EntityButton = NewObject<UButton>(this);
	Label = NewObject<UTextBlock>(this);
	Label->SetText(FText::FromString(entity->GetCallSign()));
	FSlateFontInfo FontInfo = Label->Font;
	FontInfo.Size = 12;
	Label->SetFont(FontInfo);
	FButtonStyle ButtonStyle = EntityButton->WidgetStyle;
	FLinearColor CustomNormalColor(0.0f, 0.0f, 10.f / 255.f, 1.0f);
	ButtonStyle.Normal.TintColor = FSlateColor(CustomNormalColor);
	FLinearColor CustomPressedColor(0.53f, 0.81f, 50.f / 255.f, 1.0f);
	ButtonStyle.Pressed.TintColor = FSlateColor(CustomPressedColor);
	FLinearColor CustomHoveredColor(0.0f, 0.0f, 0.50f, 1.0f);
	ButtonStyle.Hovered.TintColor = FSlateColor(CustomHoveredColor);
	EntityButton->SetStyle(ButtonStyle);
	USizeBox* SizeBox = NewObject<USizeBox>(this);
	SizeBox->SetWidthOverride(200.f);
	SizeBox->SetHeightOverride(3.f);
	SizeBox->AddChild(EntityButton);
	EntityButton->AddChild(Label);

	ButtonToEntityMap.Add(EntityButton, entity);
	EntityButton->OnClicked.AddUniqueDynamic(this, &UEntityListUI::OnEntityButtonClick);
	EntityScrollBox->AddChild(EntityButton);*/

}

void UEntityListUI::RemoveEntityCallsignFromList(AEntityBase* entity)
{
	FText TargetText = FText::FromString(entity->GetCallSign());
	for (int i = 0; i < EntityScrollBox->GetChildrenCount(); ++i)
	{
		if (UButton* button = Cast<UButton>(EntityScrollBox->GetChildAt(i)))
		{
			Label = Cast<UTextBlock>(button->GetChildAt(0));
			if (Label && Label->GetText().EqualTo(TargetText))
			{
				EntityScrollBox->RemoveChild(button);
				break;
			}
		}
	}
}

void UEntityListUI::SearchEntityList(const FString& SearchTerm)
{
	/*ButtonToEntityMap.Empty();
	EntityScrollBox->ClearChildren();

	if (!EntityManager::GetEntityManagerInstance()->GetEntityList().IsEmpty())
	{
		for (AEntityBase* entity : EntityManager::GetEntityManagerInstance()->GetEntityList())
		{
			if (entity)
			{
				if (entity->GetCallSign().Contains(SearchTerm, ESearchCase::IgnoreCase))
				{
					EntityButton = NewObject<UButton>(this);
					Label = NewObject<UTextBlock>(this);
					Label->SetText(FText::FromString(entity->GetCallSign()));
					FSlateFontInfo FontInfo = Label->Font;
					FontInfo.Size = 12;
					Label->SetFont(FontInfo);
					FButtonStyle ButtonStyle = EntityButton->WidgetStyle;
					FLinearColor CustomNormalColor(0.0f, 0.0f, 10.f / 255.f, 1.0f);
					ButtonStyle.Normal.TintColor = FSlateColor(CustomNormalColor);
					FLinearColor CustomPressedColor(0.53f, 0.81f, 50.f / 255.f, 1.0f);
					ButtonStyle.Pressed.TintColor = FSlateColor(CustomPressedColor);
					FLinearColor CustomHoveredColor(0.0f, 0.0f, 0.50f, 1.0f);
					ButtonStyle.Hovered.TintColor = FSlateColor(CustomHoveredColor);
					EntityButton->SetStyle(ButtonStyle);
					USizeBox* SizeBox = NewObject<USizeBox>(this);
					SizeBox->SetWidthOverride(200.f);
					SizeBox->SetHeightOverride(3.f);
					SizeBox->AddChild(EntityButton);
					EntityButton->AddChild(Label);

					ButtonToEntityMap.Add(EntityButton, entity);
					EntityButton->OnClicked.AddUniqueDynamic(this, &UEntityListUI::OnEntityButtonClick);
					EntityScrollBox->AddChild(EntityButton);
				}
			}
		}
	}*/
}
void UEntityListUI::OnEntityButtonClick()
{
	UButton* ClickedButton = nullptr;
	for (auto pair : ButtonToEntityMap)
	{
		if (pair.Key->HasKeyboardFocus())
		{
			ClickedButton = pair.Key;
		}
	}
	if (!ClickedButton) return;
	AEntityBase* SelectedEntity = ButtonToEntityMap[ClickedButton];
	if (!SelectedEntity) return;
	UIManager::GetInstance()->SetSelectedEntity(SelectedEntity);
	UIManager::GetInstance()->ShowMenu(EMenus::ListDropDown);
	TObjectPtr<UUserWidget>* Found = UIManager::GetInstance()->MenuWidgetMap.Find(EMenus::ListDropDown);
	UUserWidget* FoundPtr = Found->Get();
	FVector2D SubMenuPosition = UIManager::GetInstance()->CalculateForwardMenuPosition(this, EntityButton, FoundPtr);
	FoundPtr->SetRenderTranslation(SubMenuPosition);
	FoundPtr->SetVisibility(ESlateVisibility::Visible);
}

void UEntityListUI::OnSearchTextChanged(const FText& SearchText)
{
	CurrentSearchQuery = SearchText.ToString();
	EntityScrollBox->ClearChildren();
	SearchEntityList(CurrentSearchQuery);
}

void UEntityListUI::SetListVisibility(bool bVisibile)
{

	if (!EntityScrollBox) return;
	ESlateVisibility CurrentVisibility = EntityScrollBox->GetVisibility();
	if (CurrentVisibility == ESlateVisibility::Visible)
	{
		EntityScrollBox->SetVisibility(ESlateVisibility::Collapsed);
		SearchTextBox->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		EntityScrollBox->SetVisibility(ESlateVisibility::Visible);
		SearchTextBox->SetVisibility(ESlateVisibility::Visible);
	}
}

void UEntityListUI::SelectEntity(AEntityBase* entity)
{
}
