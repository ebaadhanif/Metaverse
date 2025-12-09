// Fill out your copyright notice in the Description page of Project Settings.


#include "PinLabelWidget.h"
#include "Components/TextBlock.h"

void UPinLabelWidget::SetLabelText_Implementation(const FText& NewText) {
	if (LabelTextBlock) {
		LabelTextBlock->SetText(NewText);
	}
}


