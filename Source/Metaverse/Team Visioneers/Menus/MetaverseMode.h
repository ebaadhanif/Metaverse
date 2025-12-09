// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XmlFile.h"
#include "../../Public/AppConstEnumStruct.h"
#include "MetaverseMode.generated.h"

/**
 * 
 */
UCLASS()
class METAVERSE_API UMetaverseMode : public UObject
{
	GENERATED_BODY()
public:
    UPROPERTY()
    int32 ModeID = -1;
    UPROPERTY()
    FString ModeName;
    UPROPERTY()
    bool bMenuVisible = true;
    UPROPERTY()
    bool bStatusBarVisible = true;
    UPROPERTY()
    float PlayerLongitude = 0.f;
    UPROPERTY()
    float PlayerLatitude = 0.f;
    UPROPERTY()
    float PlayerHeight = 0.f;
    //UPROPERTY()
    TMap<EButtonsName, FButtonStateStruct> ButtonStates;
    void InitDefaultButtons();
    //UFUNCTION()
    bool InitFromXmlModeNode(const FXmlNode* ModeNode);

private:
    static bool StringToFeatureEnum(const FString& InName, EButtonsName& OutEnum);

};
