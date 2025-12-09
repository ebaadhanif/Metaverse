// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "../Team SimBridge/BRITEStarWidget.h"
#include "ISRHUD.generated.h"

/**
 * 
 */
UCLASS()
class METAVERSE_API AISRHUD : public AHUD
{
	GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> BriteStarClass;
    UBRITEStarWidget* BriteStarWidget;

public:
    AISRHUD();
    virtual void BeginPlay() override;
    UBRITEStarWidget* GetISRHUDWidget();
    TSubclassOf<UUserWidget>GetBriteStarClass();

    
};
