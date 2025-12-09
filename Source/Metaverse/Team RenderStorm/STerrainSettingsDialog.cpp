// Class Added by Ebaad, This class is Template for future use for feeding terrain configs to Cesium
#include "STerrainSettingsDialog.h"
#include "SlateOptMacros.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Layout/SUniformGridPanel.h"
#include "TerrainConfigStruct.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void STerrainSettingsDialog::Construct(const FArguments& InArgs)
{
    LoadTerrains();

    ChildSlot
        [
            SNew(SBorder)
                .Padding(FMargin(10))
                [
                    SNew(SVerticalBox)

                        // Dropdown for Active Configuration
                        + SVerticalBox::Slot().AutoHeight().Padding(FMargin(5))
                        [
                            SNew(SHorizontalBox)

                                + SHorizontalBox::Slot().AutoWidth().Padding(FMargin(5)).VAlign(VAlign_Center)
                                [
                                    SNew(STextBlock).Text(FText::FromString("Active Configuration:"))
                                ]

                                + SHorizontalBox::Slot().FillWidth(1.0f).Padding(FMargin(5)).VAlign(VAlign_Center)
                                [
                                    SNew(SComboBox<TSharedPtr<FString>>)
                                        .OptionsSource(&TerrainNames)
                                        .OnSelectionChanged_Lambda([this](TSharedPtr<FString> NewValue, ESelectInfo::Type)
                                            {
                                                SelectedTerrain = *NewValue;
                                            })
                                        .OnGenerateWidget_Lambda([](TSharedPtr<FString> Item)
                                            {
                                                return SNew(STextBlock).Text(FText::FromString(*Item));
                                            })
                                        .Content()
                                        [
                                            SNew(STextBlock)
                                                .Text_Lambda([this]()
                                                    {
                                                        return FText::FromString(SelectedTerrain.IsEmpty() ? "Select Configuration" : SelectedTerrain);
                                                    })
                                        ]
                                ]
                        ]

                        // Button to Add Terrain
                        + SVerticalBox::Slot().AutoHeight().Padding(FMargin(5))
                        [
                            SNew(SButton)
                                .Text(FText::FromString("Add Terrain"))
                                .HAlign(HAlign_Center)
                                .OnClicked_Lambda([this]()
                                    {
                                        AddNewTerrain();
                                        return FReply::Handled();
                                    })
                        ]

                        // Static Container for Scrollbox
                        + SVerticalBox::Slot()
                        // .FillHeight(1.0f)
                         // .Padding(FMargin(5))
                        [
                            SNew(SScrollBox)
                                + SScrollBox::Slot()
                                [
                                    SAssignNew(AssetBox, SVerticalBox)
                                ]
                        ]

                        // Save Changes Button
                        + SVerticalBox::Slot().AutoHeight().Padding(FMargin(5))
                        [
                            SNew(SButton)
                                .Text(FText::FromString("Save Changes"))
                                .HAlign(HAlign_Center)
                                .OnClicked_Lambda([this]()
                                    {
                                        SaveChanges();
                                        return FReply::Handled();
                                    })
                        ]
                ]
        ];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void STerrainSettingsDialog::LoadTerrains()
{
    // Placeholder for loading terrain configurations (e.g., from XML)
    TerrainNames.Empty();

    TerrainNames.Add(MakeShared<FString>("Terrain 1"));
    TerrainNames.Add(MakeShared<FString>("Terrain 2"));

    AssetTypes.Add(MakeShared<FString>("CesiumION_3D_Tileset"));
    AssetTypes.Add(MakeShared<FString>("Blank_3D_Tileset"));


    TerrainTypes.Add(MakeShared<FString>("CESIUM"));
    TerrainTypes.Add(MakeShared<FString>("ARC-GIS"));



}

void STerrainSettingsDialog::AddNewTerrain()
{

    int32 NewTerrainIndex = TerrainConfiguration.Terrains.Num();
    TerrainConfiguration.Terrains.Add(FTerrainConfig());



    AssetBox->AddSlot().Padding(FMargin(5, 2))
        [
            SNew(SVerticalBox)

                + SVerticalBox::Slot().AutoHeight().Padding(FMargin(5))
                [
                    SNew(SUniformGridPanel)
                        .SlotPadding(FMargin(5, 2))

                        + SUniformGridPanel::Slot(0, 0)
                        [
                            SNew(STextBlock)
                                .Text(FText::FromString("Terrain ID:"))
                                .MinDesiredWidth(120)
                        ]

                        + SUniformGridPanel::Slot(1, 0)
                        [
                            SNew(SEditableTextBox)
                                .MinDesiredWidth(200).OnTextCommitted_Lambda([this, NewTerrainIndex](const FText& NewText, ETextCommit::Type CommitType) {
                                TerrainConfiguration.Terrains[NewTerrainIndex].ID = FCString::Atof(*NewText.ToString());
                                    })
                        ]
                        + SUniformGridPanel::Slot(0, 1)[

                            SNew(STextBlock)
                                .Text(FText::FromString("Select Terrain Type:"))
                                .MinDesiredWidth(120)

                        ]

                        + SUniformGridPanel::Slot(1, 1)[

                            SNew(SComboBox<TSharedPtr<FString>>)
                                .OptionsSource(&TerrainTypes)
                                .OnSelectionChanged_Lambda([this, NewTerrainIndex](TSharedPtr<FString> NewValue, ESelectInfo::Type CommitType)
                                    {
                                        if (NewValue.IsValid())
                                        {
                                            SelectedTerrainType = *NewValue;
                                            TerrainConfiguration.Terrains[NewTerrainIndex].Type = *NewValue;
                                            UpdateTerrainUI(*NewValue, NewTerrainIndex);

                                            if (*NewValue == "CESIUM")
                                            {
                                                AddAssetToTerrain();
                                            }
                                            else
                                            {
                                                // Clear the Asset UI if switching to a non-CESIUM terrain type
                                                if (UpdateAssetTypeUIContainer.IsValid())
                                                {
                                                    UpdateAssetTypeUIContainer->ClearChildren();

                                                }
                                                if (UpdateUIContainer.IsValid()) {
                                                    UpdateUIContainer->ClearChildren();
                                                }

                                                if (UpdateOverlayUIContainer.IsValid()) {
                                                    UpdateOverlayUIContainer->ClearChildren();
                                                }


                                            }
                                        }
                                    })
                                .OnGenerateWidget_Lambda([](TSharedPtr<FString> Item)
                                    {
                                        return SNew(STextBlock).Text(FText::FromString(*Item)).MinDesiredWidth(150);
                                    })
                                .Content()
                                [
                                    SNew(STextBlock)
                                        .Text_Lambda([this]()
                                            {
                                                return FText::FromString(SelectedTerrainType.IsEmpty() ? "Choose Terrain Type" : SelectedTerrainType);
                                            })
                                ]

                        ]


                        + SUniformGridPanel::Slot(0, 2)
                        [
                            SNew(STextBlock)
                                .Text(FText::FromString("Terrain Name:"))
                                .MinDesiredWidth(120)
                        ]

                        + SUniformGridPanel::Slot(1, 2)
                        [
                            SNew(SEditableTextBox)
                                .MinDesiredWidth(200).OnTextCommitted_Lambda([this, NewTerrainIndex](const FText& NewText, ETextCommit::Type CommitType) {
                                TerrainConfiguration.Terrains[NewTerrainIndex].Name = NewText.ToString();
                                    })
                        ]


                ]
                + SVerticalBox::Slot().AutoHeight().Padding(FMargin(5))
                [

                    SAssignNew(TerrainBox, SVerticalBox)

                ]
            + SVerticalBox::Slot().AutoHeight().Padding(FMargin(5))
                [

                    SAssignNew(AssetTypeBox, SVerticalBox)

                ]
            /*          + SVerticalBox::Slot().AutoHeight().Padding(FMargin(5))
                      [
                          SAssignNew(OverlayBox, SVerticalBox)
                      ]*/



        ];



}
void STerrainSettingsDialog::UpdateTerrainUI(const FString& TerrainType, int32 terrainIndex)
{
    if (!UpdateTerrainUIContainer.IsValid())
    {
        TerrainBox->AddSlot()
            [
                SAssignNew(UpdateTerrainUIContainer, SVerticalBox)
            ];
    }


    UpdateTerrainUIContainer->ClearChildren();

    if (TerrainType == "CESIUM") {


        UpdateTerrainUIContainer->AddSlot()[

            SNew(SBorder).
                BorderBackgroundColor(FLinearColor::Green).Padding(FMargin(5, 2, 5, 2))[

                    SNew(SVerticalBox)

                        + SVerticalBox::Slot().AutoHeight().Padding(5, 2)[

                            SNew(SUniformGridPanel)
                                .SlotPadding(FMargin(5, 2))
                                + SUniformGridPanel::Slot(0, 0)
                                [
                                    SNew(STextBlock)
                                        .Text(FText::FromString("Longitude:"))
                                        .MinDesiredWidth(120)
                                ]

                                + SUniformGridPanel::Slot(1, 0)
                                [
                                    SNew(SEditableTextBox)
                                        .MinDesiredWidth(200).OnTextCommitted_Lambda([this, terrainIndex](const FText& NewText, ETextCommit::Type CommitType) {
                                        TerrainConfiguration.Terrains[terrainIndex].Georeference.Longitude = FCString::Atof(*NewText.ToString());
                                            })
                                ]

                                + SUniformGridPanel::Slot(0, 1)
                                [
                                    SNew(STextBlock)
                                        .Text(FText::FromString("Latitude:"))
                                        .MinDesiredWidth(120)
                                ]

                                + SUniformGridPanel::Slot(1, 1)
                                [
                                    SNew(SEditableTextBox)
                                        .MinDesiredWidth(200).OnTextCommitted_Lambda([this, terrainIndex](const FText& NewText, ETextCommit::Type CommitType) {
                                        TerrainConfiguration.Terrains[terrainIndex].Georeference.Latitude = FCString::Atof(*NewText.ToString());
                                            })
                                ]

                                + SUniformGridPanel::Slot(0, 2)
                                [
                                    SNew(STextBlock)
                                        .Text(FText::FromString("Height:"))
                                        .MinDesiredWidth(120)
                                ]

                                + SUniformGridPanel::Slot(1, 2)
                                [
                                    SNew(SEditableTextBox)
                                        .MinDesiredWidth(200).OnTextCommitted_Lambda([this, terrainIndex](const FText& NewText, ETextCommit::Type CommitType) {
                                        TerrainConfiguration.Terrains[terrainIndex].Georeference.Height = FCString::Atof(*NewText.ToString());
                                            })
                                ]
                        ]

                ]


        ];

    }


    else if (TerrainType == "ARC-GIS") {

        UpdateTerrainUIContainer->AddSlot()[

            SNew(SBorder).
                BorderBackgroundColor(FLinearColor::Green).Padding(FMargin(5, 2, 5, 2))[

                    SNew(SVerticalBox)

                        + SVerticalBox::Slot().AutoHeight().Padding(FMargin(5, 2))[

                            SNew(SUniformGridPanel)
                                .SlotPadding(FMargin(5, 2))
                                + SUniformGridPanel::Slot(0, 0)
                                [
                                    SNew(STextBlock)
                                        .Text(FText::FromString("Arc Gis Parameter:"))
                                        .MinDesiredWidth(120)
                                ]

                                + SUniformGridPanel::Slot(1, 0)
                                [
                                    SNew(SEditableTextBox)
                                        .MinDesiredWidth(200)
                                ]

                        ]

                ]


        ];


    }



}

void STerrainSettingsDialog::AddAssetToTerrain()
{
    if (!UpdateAssetTypeUIContainer.IsValid())
    {
        AssetTypeBox->AddSlot()
            [
                SAssignNew(UpdateAssetTypeUIContainer, SVerticalBox)
            ];
    }

    UpdateAssetTypeUIContainer->ClearChildren();


    if (TerrainConfiguration.Terrains.Num() == 0)
    {
        return;
    }


    int32 SelectedTerrainIndex = TerrainConfiguration.Terrains.Num() - 1; // Add asset to the last added terrain
    int32 NewAssetIndex = TerrainConfiguration.Terrains[SelectedTerrainIndex].Assets.Num();
    TerrainConfiguration.Terrains[SelectedTerrainIndex].Assets.Add(FAssetConfig());




    UpdateAssetTypeUIContainer->AddSlot()
        [
            SNew(SVerticalBox)


                // Asset Type
                +SVerticalBox::Slot().AutoHeight().Padding(FMargin(5, 5, 5, 70))
                [
                    SNew(SHorizontalBox)
                        + SHorizontalBox::Slot().AutoWidth().Padding(FMargin(5)).VAlign(VAlign_Center)
                        [
                            SNew(STextBlock)
                                .Text(FText::FromString("Select Asset Type:"))
                                .MinDesiredWidth(150)
                        ]
                        + SHorizontalBox::Slot().FillWidth(1.0f).Padding(FMargin(5, 20)).VAlign(VAlign_Center)
                        [
                            SNew(SComboBox<TSharedPtr<FString>>)
                                .OptionsSource(&AssetTypes)
                                .OnSelectionChanged_Lambda([this, SelectedTerrainIndex, NewAssetIndex](TSharedPtr<FString> NewValue, ESelectInfo::Type CommitType)
                                    {
                                        if (NewValue.IsValid())
                                        {
                                            SelectedAssetType = *NewValue;
                                            TerrainConfiguration.Terrains[SelectedTerrainIndex].Assets[NewAssetIndex].Type = *NewValue;
                                            UpdateAssetUI(*NewValue);
                                        }
                                    })
                                .OnGenerateWidget_Lambda([](TSharedPtr<FString> Item)
                                    {
                                        return SNew(STextBlock).Text(FText::FromString(*Item));
                                    })
                                .Content()
                                [
                                    SNew(STextBlock)
                                        .Text_Lambda([this]()
                                            {
                                                return FText::FromString(SelectedAssetType.IsEmpty() ? "Choose Asset Type" : SelectedAssetType);
                                            })
                                ]

                        ]
                ]
        ];


}
void STerrainSettingsDialog::UpdateAssetUI(const FString& AssetType)
{

    if (!UpdateUIContainer.IsValid())
    {
        AssetBox->AddSlot()
            //.Padding(FMargin(5, 2))
            [
                SAssignNew(UpdateUIContainer, SVerticalBox)
            ];
    }

    UpdateUIContainer->ClearChildren();

    int32 SelectedTerrainIndex = TerrainConfiguration.Terrains.Num() - 1; // Add asset to the last added terrain
    int32 NewAssetIndex = TerrainConfiguration.Terrains[SelectedTerrainIndex].Assets.Num() - 1;
    FAssetConfig& CurrentAsset = TerrainConfiguration.Terrains[SelectedTerrainIndex].Assets[NewAssetIndex];


    // Example of clearing before adding new terrain
    //FTerrainConfig& RecentTerrain = TerrainConfiguration.Terrains.Last();
    //RecentTerrain.Assets.Empty(); // Ensure no leftover assets




    if (AssetType == "Blank_3D_Tileset")
    {

        CurrentAsset.Type = AssetType;


        UpdateUIContainer->AddSlot()
            [
                SNew(SVerticalBox)

                    + SVerticalBox::Slot().AutoHeight().Padding(FMargin(5, 2))
                    [
                        SNew(SHorizontalBox)


                            + SHorizontalBox::Slot().AutoWidth().Padding(FMargin(5)).VAlign(VAlign_Center)
                            [
                                SNew(STextBlock)
                                    .Text(FText::FromString("Enter Id:"))
                                    .MinDesiredWidth(150)
                            ]

                            + SHorizontalBox::Slot().FillWidth(1.0f).Padding(FMargin(5)).VAlign(VAlign_Center)
                            [
                                SNew(SEditableTextBox)
                                    .MinDesiredWidth(300)
                                    .OnTextCommitted_Lambda([this, SelectedTerrainIndex, NewAssetIndex, &CurrentAsset](const FText& NewText, ETextCommit::Type CommitType)
                                        {

                                            CurrentAsset.ID = FCString::Atoi(*NewText.ToString());
                                        })
                            ]
                    ]


                    // Horizontal layout for "Enter Tileset URL" label and input field
                    +SVerticalBox::Slot().AutoHeight().Padding(FMargin(5, 2))
                    [
                        SNew(SHorizontalBox)

                            + SHorizontalBox::Slot().AutoWidth().Padding(FMargin(5)).VAlign(VAlign_Center)
                            [
                                SNew(STextBlock)
                                    .Text(FText::FromString("Enter Tileset URL:"))
                                    .MinDesiredWidth(150)
                            ]

                            + SHorizontalBox::Slot().FillWidth(1.0f).Padding(FMargin(5)).VAlign(VAlign_Center)
                            [
                                SNew(SEditableTextBox)
                                    .MinDesiredWidth(300).OnTextCommitted_Lambda([this, SelectedTerrainIndex, NewAssetIndex, &CurrentAsset](const FText& NewText, ETextCommit::Type CommitType)
                                        {
                                            CurrentAsset.TilesetConfig.Url = NewText.ToString();

                                            // TerrainConfiguration.Terrains[SelectedTerrainIndex].Assets[NewAssetIndex].TilesetConfig.Url = NewText.ToString();
                                        })
                            ]
                    ]


                    + SVerticalBox::Slot().AutoHeight().Padding(FMargin(5, 2))
                    [
                        SNew(SHorizontalBox)


                            + SHorizontalBox::Slot().AutoWidth().Padding(FMargin(5)).VAlign(VAlign_Center)
                            [
                                SNew(STextBlock)
                                    .Text(FText::FromString("Enter Name:"))
                                    .MinDesiredWidth(150)
                            ]


                            + SHorizontalBox::Slot().FillWidth(1.0f).Padding(FMargin(5)).VAlign(VAlign_Center)
                            [
                                SNew(SEditableTextBox)
                                    .MinDesiredWidth(300)
                                    .OnTextCommitted_Lambda([this, SelectedTerrainIndex, NewAssetIndex, &CurrentAsset](const FText& NewText, ETextCommit::Type CommitType)
                                        {
                                            CurrentAsset.Name = NewText.ToString();
                                        })
                            ]
                    ]
                    // Add Overlay button
                    + SVerticalBox::Slot().AutoHeight().Padding(FMargin(5, 10))
                    [
                        SNew(SButton)
                            .Text(FText::FromString("Add Overlay"))
                            .HAlign(HAlign_Center)
                            .OnClicked_Lambda([this]()
                                {
                                    AddOverlayUI();
                                    return FReply::Handled();
                                })
                    ]
            ];
    }
    else if (AssetType == "CesiumION_3D_Tileset")
    {

        if (UpdateOverlayUIContainer) {
            UpdateOverlayUIContainer->ClearChildren();
        }
        CurrentAsset.Type = AssetType;


        UpdateUIContainer->AddSlot()//.Padding(FMargin(5, 2))
            [
                SNew(SVerticalBox)

                    + SVerticalBox::Slot().AutoHeight().Padding(FMargin(5, 2))
                    [
                        SNew(SHorizontalBox)

                            + SHorizontalBox::Slot().AutoWidth().Padding(FMargin(5)).VAlign(VAlign_Center)
                            [
                                SNew(STextBlock)
                                    .Text(FText::FromString("Enter ID:"))
                                    .MinDesiredWidth(150)
                            ]

                            + SHorizontalBox::Slot().FillWidth(1.0f).Padding(FMargin(5)).VAlign(VAlign_Center)
                            [
                                SNew(SEditableTextBox)
                                    .MinDesiredWidth(300).OnTextCommitted_Lambda([this, SelectedTerrainIndex, NewAssetIndex, &CurrentAsset](const FText& NewText, ETextCommit::Type CommitType) {

                                    CurrentAsset.ID = FCString::Atoi(*NewText.ToString());
                                        })
                            ]
                    ]

                    + SVerticalBox::Slot().AutoHeight().Padding(FMargin(5, 2))
                    [
                        SNew(SHorizontalBox)

                            + SHorizontalBox::Slot().AutoWidth().Padding(FMargin(5)).VAlign(VAlign_Center)
                            [
                                SNew(STextBlock)
                                    .Text(FText::FromString("Enter Name:"))
                                    .MinDesiredWidth(150)
                            ]

                            + SHorizontalBox::Slot().FillWidth(1.0f).Padding(FMargin(5)).VAlign(VAlign_Center)
                            [
                                SNew(SEditableTextBox)
                                    .MinDesiredWidth(300).OnTextCommitted_Lambda([this, SelectedTerrainIndex, NewAssetIndex, &CurrentAsset](const FText& NewText, ETextCommit::Type CommitType) {
                                    CurrentAsset.Name = NewText.ToString();
                                        })
                            ]
                    ]


                    + SVerticalBox::Slot().AutoHeight().Padding(FMargin(5, 2))
                    [
                        SNew(SHorizontalBox)


                            + SHorizontalBox::Slot().AutoWidth().Padding(FMargin(5)).VAlign(VAlign_Center)
                            [
                                SNew(STextBlock)
                                    .Text(FText::FromString("Enter Asset ID:"))
                                    .MinDesiredWidth(150)
                            ]


                            + SHorizontalBox::Slot().FillWidth(1.0f).Padding(FMargin(5)).VAlign(VAlign_Center)
                            [
                                SNew(SEditableTextBox)
                                    .MinDesiredWidth(300).OnTextCommitted_Lambda([this, SelectedTerrainIndex, NewAssetIndex, &CurrentAsset](const FText& NewText, ETextCommit::Type CommitType) {
                                    CurrentAsset.CesiumIONConfig.CesiumIONAssetID = FCString::Atoi(*NewText.ToString());


                                    //TerrainConfiguration.Terrains[SelectedTerrainIndex].Assets[NewAssetIndex].CesiumIONConfig.CesiumIONAssetID = FCString::Atoi(*NewText.ToString());
                                        })
                            ]
                    ]
                    + SVerticalBox::Slot().AutoHeight().Padding(FMargin(5, 2))
                    [
                        SNew(SHorizontalBox)

                            + SHorizontalBox::Slot().AutoWidth().Padding(FMargin(5)).VAlign(VAlign_Center)
                            [
                                SNew(STextBlock)
                                    .Text(FText::FromString("Enter Access Token:"))
                                    .MinDesiredWidth(150)
                            ]

                            + SHorizontalBox::Slot().FillWidth(1.0f).Padding(FMargin(5)).VAlign(VAlign_Center)
                            [
                                SNew(SEditableTextBox)
                                    .MinDesiredWidth(300).OnTextCommitted_Lambda([this, SelectedTerrainIndex, NewAssetIndex, &CurrentAsset](const FText& NewText, ETextCommit::Type CommitType) {

                                    CurrentAsset.CesiumIONConfig.CesiumIONAccessToken = NewText.ToString();

                                    //TerrainConfiguration.Terrains[SelectedTerrainIndex].Assets[NewAssetIndex].CesiumIONConfig.CesiumIONAccessToken = NewText.ToString();
                                        })
                            ]
                    ]
            ];
    }
}


void STerrainSettingsDialog::AddOverlayUI()
{
    OverlayCounter++;

    if (!UpdateOverlayUIContainer.IsValid())
    {
        //OverlayBox->AddSlot()//.Padding(FMargin(5, 2))
        //    [
        //        SAssignNew(UpdateOverlayUIContainer, SVerticalBox)
        //    ];

        UpdateUIContainer->AddSlot()
            [
                SAssignNew(UpdateOverlayUIContainer, SVerticalBox)
            ];
    }


    //UpdateOverlayUIContainer->ClearChildren();


    if (TerrainConfiguration.Terrains.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No terrains available for overlays."));
        return;
    }

    int32 SelectedTerrainIndex = TerrainConfiguration.Terrains.Num() - 1; // Last added terrain
    int32 SelectedAssetIndex = TerrainConfiguration.Terrains[SelectedTerrainIndex].Assets.Num() - 1; // Last added asset

    if (SelectedAssetIndex < 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No assets available for overlays."));
        return;
    }

    // Add a new overlay to the selected asset
    FOverlayConfig NewOverlay;
    TerrainConfiguration.Terrains[SelectedTerrainIndex].Assets[SelectedAssetIndex].TilesetConfig.Overlays.Add(NewOverlay);

    int32 OverlayIndex = TerrainConfiguration.Terrains[SelectedTerrainIndex].Assets[SelectedAssetIndex].TilesetConfig.Overlays.Num() - 1;
    FOverlayConfig& CurrentOverlay = TerrainConfiguration.Terrains[SelectedTerrainIndex].Assets[SelectedAssetIndex].TilesetConfig.Overlays[OverlayIndex];





    UpdateOverlayUIContainer->AddSlot()
        [

            SNew(SVerticalBox)


                // Label for the overlay
                +SVerticalBox::Slot().AutoHeight().Padding(FMargin(5, 2))
                [
                    SNew(STextBlock)
                        .Text(FText::Format(FText::FromString("Overlay {0}"), FText::AsNumber(OverlayCounter)))
                        .Font(FCoreStyle::GetDefaultFontStyle("Bold", 12))
                        .ColorAndOpacity(FLinearColor::White)
                ]



                +SVerticalBox::Slot().AutoHeight().Padding(FMargin(5, 2))
                [

                    SNew(SUniformGridPanel)
                        .SlotPadding(FMargin(5, 2))

                        + SUniformGridPanel::Slot(0, 0)
                        [
                            SNew(STextBlock).Text(FText::FromString("Overlay URL:")).MinDesiredWidth(150)
                        ]

                        + SUniformGridPanel::Slot(1, 0)
                        [
                            SNew(SEditableTextBox).MinDesiredWidth(300).OnTextCommitted_Lambda([this, &CurrentOverlay](const FText& NewText, ETextCommit::Type CommitType)
                                {
                                    CurrentOverlay.Url = NewText.ToString();
                                })
                        ]

                        + SUniformGridPanel::Slot(0, 1)
                        [
                            SNew(STextBlock).Text(FText::FromString("Min Zoom:")).MinDesiredWidth(150)
                        ]

                        + SUniformGridPanel::Slot(1, 1)
                        [
                            SNew(SEditableTextBox).MinDesiredWidth(300).OnTextCommitted_Lambda([this, &CurrentOverlay](const FText& NewText, ETextCommit::Type CommitType)
                                {
                                    CurrentOverlay.MinZoom = FCString::Atoi(*NewText.ToString());
                                })
                        ]

                        + SUniformGridPanel::Slot(0, 2)
                        [
                            SNew(STextBlock).Text(FText::FromString("Max Zoom:")).MinDesiredWidth(150)
                        ]

                        + SUniformGridPanel::Slot(1, 2)
                        [
                            SNew(SEditableTextBox).MinDesiredWidth(300).OnTextCommitted_Lambda([this, &CurrentOverlay](const FText& NewText, ETextCommit::Type CommitType)
                                {
                                    CurrentOverlay.MaxZoom = FCString::Atoi(*NewText.ToString());
                                })
                        ]

                        + SUniformGridPanel::Slot(0, 3)
                        [
                            SNew(STextBlock).Text(FText::FromString("Material Layer Key:")).MinDesiredWidth(150)
                        ]

                        + SUniformGridPanel::Slot(1, 3)
                        [
                            SNew(SEditableTextBox).MinDesiredWidth(300).OnTextCommitted_Lambda([this, &CurrentOverlay](const FText& NewText, ETextCommit::Type CommitType)
                                {
                                    CurrentOverlay.MaterialLayerKey = NewText.ToString();
                                })
                        ]
                ]

        ];
}

void STerrainSettingsDialog::SaveChanges()
{
    if (TerrainConfiguration.Terrains.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No terrains available to save."));
        return;
    }

    const FTerrainConfig& RecentTerrain = TerrainConfiguration.Terrains.Last();

    UE_LOG(LogTemp, Log, TEXT("Logging the most recently added terrain:"));
    UE_LOG(LogTemp, Log, TEXT("  ID: %d"), RecentTerrain.ID);
    UE_LOG(LogTemp, Log, TEXT("  Name: %s"), *RecentTerrain.Name);
    UE_LOG(LogTemp, Log, TEXT("  Type: %s"), *RecentTerrain.Type);
    UE_LOG(LogTemp, Log, TEXT("  Georeference: Longitude = %f, Latitude = %f, Height = %f"),
        RecentTerrain.Georeference.Longitude,
        RecentTerrain.Georeference.Latitude,
        RecentTerrain.Georeference.Height);

    for (int32 AssetIndex = 0; AssetIndex < RecentTerrain.Assets.Num(); ++AssetIndex)
    {
        const FAssetConfig& Asset = RecentTerrain.Assets[AssetIndex];
        UE_LOG(LogTemp, Log, TEXT("  Asset %d:"), AssetIndex + 1);
        UE_LOG(LogTemp, Log, TEXT("    ID: %d"), Asset.ID);
        UE_LOG(LogTemp, Log, TEXT("    Name: %s"), *Asset.Name);
        UE_LOG(LogTemp, Log, TEXT("    Type: %s"), *Asset.Type);

        for (int32 OverlayIndex = 0; OverlayIndex < Asset.TilesetConfig.Overlays.Num(); ++OverlayIndex)
        {
            const FOverlayConfig& Overlay = Asset.TilesetConfig.Overlays[OverlayIndex];
            UE_LOG(LogTemp, Log, TEXT("    Overlay %d:"), OverlayIndex + 1);
            UE_LOG(LogTemp, Log, TEXT("      URL: %s"), *Overlay.Url);
            UE_LOG(LogTemp, Log, TEXT("      Min Zoom: %d"), Overlay.MinZoom);
            UE_LOG(LogTemp, Log, TEXT("      Max Zoom: %d"), Overlay.MaxZoom);
        }
    }

    UE_LOG(LogTemp, Log, TEXT("Terrain data saved successfully."));
}
