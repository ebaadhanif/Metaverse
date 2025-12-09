// Fill out your copyright notice in the Description page of Project Settings.


#include "MetaverseMode.h"
#include "Components/SlateWrapperTypes.h"   
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UMetaverseMode::InitDefaultButtons()
{
    ButtonStates.Empty();

    UEnum* Enum = StaticEnum<EButtonsName>();
    if (!Enum)
    {
        return;
    }
    const int32 NumEnums = Enum->NumEnums();
    for (int32 Index = 0; Index < NumEnums; ++Index)
    {
        const FString NameString = Enum->GetNameStringByIndex(Index);
        if (NameString.StartsWith(TEXT("MAX_")))
        {
            continue;
        }
        const int64 Value = Enum->GetValueByIndex(Index);
        EButtonsName Feature = static_cast<EButtonsName>(Value);
        FButtonStateStruct State;
        State.Visibility = ESlateVisibility::Collapsed;
        State.FeatureActive = false;
        ButtonStates.Add(Feature, State);
    }
}

bool UMetaverseMode::StringToFeatureEnum(const FString& InName, EButtonsName& OutEnum)
{
    UEnum* Enum = StaticEnum<EButtonsName>();
    if (!Enum)
    {
        return false;
    }

    int64 Value = Enum->GetValueByNameString(InName);
    if (Value != INDEX_NONE)
    {
        OutEnum = static_cast<EButtonsName>(Value);
        return true;
    }
    return false;
}

bool UMetaverseMode::InitFromXmlModeNode(const FXmlNode* ModeNode)
{
    if (!ModeNode || ModeNode->GetTag() != TEXT("Mode"))
    {
        return false;
    }
    // --- ID ---
    if (const FXmlNode* IdNode = ModeNode->FindChildNode(TEXT("ID")))
    {
        ModeID = FCString::Atoi(*IdNode->GetContent());
    }
    // --- ModeName ---
    const FXmlNode* NameNode = ModeNode->FindChildNode(TEXT("ModeName"));
    if (!NameNode)
    {
        NameNode = ModeNode->FindChildNode(TEXT("Modename"));
    }
    if (NameNode)
    {
        ModeName = NameNode->GetContent().TrimStartAndEnd();
    }
    // --- PlayerStart ---
    if (const FXmlNode* PlayerStartNode = ModeNode->FindChildNode(TEXT("PlayerStart")))
    {
        if (const FXmlNode* LonNode = PlayerStartNode->FindChildNode(TEXT("Longitude")))
        {
            PlayerLongitude = FCString::Atof(*LonNode->GetContent());
        }
        if (const FXmlNode* LatNode = PlayerStartNode->FindChildNode(TEXT("Latitude")))
        {
            PlayerLatitude = FCString::Atof(*LatNode->GetContent());
        }
        if (const FXmlNode* HeightNode = PlayerStartNode->FindChildNode(TEXT("Height")))
        {
            PlayerHeight = FCString::Atof(*HeightNode->GetContent());
        }
    }
    // --- MenuVisibility ---
    if (const FXmlNode* MenuVisNode = ModeNode->FindChildNode(TEXT("MenuVisibility")))
    {
        const FString Value = MenuVisNode->GetContent().TrimStartAndEnd();
        bMenuVisible = Value.Equals(TEXT("true"), ESearchCase::IgnoreCase) ||
            Value.Equals(TEXT("1"), ESearchCase::IgnoreCase) ||
            Value.Equals(TEXT("yes"), ESearchCase::IgnoreCase);
    }
    // --- MenuVisibility ---
    if (const FXmlNode* StatusBarVisNode = ModeNode->FindChildNode(TEXT("StatusBarVisibility")))
    {
        const FString Value = StatusBarVisNode->GetContent().TrimStartAndEnd();
        bStatusBarVisible = Value.Equals(TEXT("true"), ESearchCase::IgnoreCase) ||
            Value.Equals(TEXT("1"), ESearchCase::IgnoreCase) ||
            Value.Equals(TEXT("yes"), ESearchCase::IgnoreCase);
    }
    InitDefaultButtons();
    // --- Features from XML ---
    const FXmlNode* FeaturesNode = ModeNode->FindChildNode(TEXT("Features"));
    if (!FeaturesNode)
    {
        return true;
    }
    const TArray<FXmlNode*>& FeatureNodes = FeaturesNode->GetChildrenNodes();
    for (const FXmlNode* FeatureNode : FeatureNodes)
    {
        if (!FeatureNode || FeatureNode->GetTag() != TEXT("Feature"))
        {
            continue;
        }
        const FXmlNode* FeatureNameNode = FeatureNode->FindChildNode(TEXT("FeatureName"));
        const FXmlNode* FeatureStateNode = FeatureNode->FindChildNode(TEXT("FeatureState"));
        const FXmlNode* FeatureButtonVisibilityNode = FeatureNode->FindChildNode(TEXT("FeatureButtonVisibility"));
        if (!FeatureNameNode)
        {
            continue;
        }
        const FString FeatureNameStr = FeatureNameNode->GetContent().TrimStartAndEnd();
        EButtonsName FeatureEnum;
        if (!StringToFeatureEnum(FeatureNameStr, FeatureEnum))
        {
            continue;
        }
        FButtonStateStruct& State = ButtonStates.FindOrAdd(FeatureEnum);

        auto ToBool = [](const FString& Str)->bool
            {
                return Str.Equals(TEXT("True"), ESearchCase::IgnoreCase) ||
                    Str.Equals(TEXT("Yes"), ESearchCase::IgnoreCase) ||
                    Str.Equals(TEXT("1"), ESearchCase::IgnoreCase) ||
                    Str.Equals(TEXT("true"), ESearchCase::IgnoreCase);
            };
        if (FeatureStateNode)
        {
            const FString Value = FeatureStateNode->GetContent().TrimStartAndEnd();
            State.FeatureActive = ToBool(Value);
        }
        if (FeatureButtonVisibilityNode)
        {
            const FString Value = FeatureButtonVisibilityNode->GetContent().TrimStartAndEnd();
            const bool bVisible = ToBool(Value);
            State.Visibility = bVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed;
            State.buttonVisibility = bVisible;
        }
    }
    return true;
}

