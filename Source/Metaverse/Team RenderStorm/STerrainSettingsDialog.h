#pragma once
#include "CoreMinimal.h"
#include "TerrainConfigStruct.h"
#include "Widgets/SCompoundWidget.h"

class METAVERSE_API STerrainSettingsDialog : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(STerrainSettingsDialog)
        {
        }
    SLATE_END_ARGS()

    /** Constructs this widget with InArgs */
    void Construct(const FArguments& InArgs);

    void LoadTerrains();

    void AddNewTerrain();

    void AddAssetToTerrain();

    void UpdateTerrainUI(const FString& TerrainType, int32 terrainIndex);

    void UpdateAssetUI(const FString& AssetType);

    void AddOverlayUI();

    void SaveChanges();

private:

    TArray<TSharedPtr<FString>> TerrainNames;
    FString SelectedTerrain;
    TArray<TSharedPtr<FString>> AssetTypes;
    TArray<TSharedPtr<FString>> TerrainTypes;
    FString SelectedAssetType;
    FString SelectedTerrainType;
    TSharedPtr<SVerticalBox> TerrainBox;
    TSharedPtr<SVerticalBox> UpdateTerrainUIContainer; //Container for AddTerrainUi  Widgets
    TSharedPtr<SVerticalBox> AssetBox;
    TSharedPtr<SVerticalBox> UpdateUIContainer; // Container for UpdateAssetUI widgets
    TSharedPtr<SVerticalBox> OverlayBox;
    TSharedPtr<SVerticalBox> UpdateOverlayUIContainer;  //container for AddOverlayUI widgets 
    TSharedPtr<SVerticalBox> AssetTypeBox;
    TSharedPtr<SVerticalBox> UpdateAssetTypeUIContainer;
    int32 OverlayCounter = 0;
    FTerrainConfiguration TerrainConfiguration;
};
