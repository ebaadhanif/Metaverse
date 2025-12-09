// Fill out your copyright notice in the Description page of Project Settings.


#include "ContextMenuWidget.h"


void UContextMenuWidget::Init(AEntityBase* InEntity)
{
	TargetEntity = InEntity;
}

void UContextMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (ShowInfoButton)
	{
		ShowInfoButton->OnClicked.AddUniqueDynamic(this, &UContextMenuWidget::OnShowInfoClicked);
	}
	if (CloseButton)
	{
		CloseButton->OnClicked.AddUniqueDynamic(this,&UContextMenuWidget::OnCloseClicked);
	}
}

void UContextMenuWidget::OnShowInfoClicked()
{
	if (TargetEntity)
	{
		UE_LOG(LogTemp, Warning, TEXT("Entityyy %s"), *TargetEntity->GetCallSign());
		//RemoveFromParent();
		SetVisibility(ESlateVisibility::Hidden);
	}
}


void UContextMenuWidget::OnCloseClicked()
{
	if (TargetEntity)
	{
		UE_LOG(LogTemp, Warning, TEXT("Entityyy %s"), *TargetEntity->GetCallSign());
		//RemoveFromParent();
		SetVisibility(ESlateVisibility::Hidden);
	}
}

void UContextMenuWidget::SetScreenPosition(const FVector2D& ScreenPosition)
{
	SetPositionInViewport(ScreenPosition, false);
}
