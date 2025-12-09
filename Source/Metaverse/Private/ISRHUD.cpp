// Fill out your copyright notice in the Description page of Project Settings.


#include "ISRHUD.h"

AISRHUD::AISRHUD()
{
    static ConstructorHelpers::FClassFinder<UBRITEStarWidget> WidgetBPClass(TEXT("/Game/Gadgets/BRITEStar/WBP_BRITESTAR"));

    if (WidgetBPClass.Succeeded())
    {
        BriteStarClass = WidgetBPClass.Class;
    }
}

void AISRHUD::BeginPlay()
{
    Super::BeginPlay();

    if (BriteStarClass)
    {
        BriteStarWidget = Cast<UBRITEStarWidget>(CreateWidget<UUserWidget>(GetWorld(), BriteStarClass));
        if (BriteStarWidget)
        {
            BriteStarWidget->AddToViewport();
            //BriteStarWidget->SetVisibility(ESlateVisibility::Visible); // Initially hidden
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to create TopBarMenuWidget!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("TopBarMenuClass is not set in CustomHUD!"));
    }
}

UBRITEStarWidget* AISRHUD::GetISRHUDWidget()
{
    return BriteStarWidget;
}

TSubclassOf<UUserWidget> AISRHUD::GetBriteStarClass()
{
    return BriteStarClass;
}


