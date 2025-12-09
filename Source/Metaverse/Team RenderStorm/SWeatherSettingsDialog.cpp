#include "SWeatherSettingsDialog.h"
#include "SlateOptMacros.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SComboBox.h"
#include "EngineUtils.h"
#include "WeatherController.h"
#if WITH_EDITOR
#include "Editor.h"
#include "ScopedTransaction.h"
#include "EngineUtils.h"
#include "Runtime/Engine/Classes/Engine/World.h"


//namespace
//{
//    // Switch this off if you want editor-only eye icon without affecting PIE/packaged.
//    static constexpr bool GApplyRuntimeVisibilityToo = true;
//
//    static UWorld* GetActiveEditorOrPIEWorld()
//    {
//        if (!GEditor) return nullptr;
//        if (GEditor->PlayWorld) return GEditor->PlayWorld; // PIE running
//        return GEditor->GetEditorWorldContext().World();
//    }
//
//    static void ApplyVisibilityToActor(AActor* Actor, bool bHidden)
//    {
//        if (!Actor) return;
//
//        // Editor Outliner eye
//        Actor->Modify();
//        Actor->SetIsTemporarilyHiddenInEditor(bHidden);
//        Actor->MarkComponentsRenderStateDirty();
//
//        // Optional runtime parity
//        if (GApplyRuntimeVisibilityToo)
//        {
//            Actor->SetActorHiddenInGame(bHidden);
//            Actor->SetActorEnableCollision(!bHidden);
//            Actor->SetActorTickEnabled(!bHidden);
//        }
//    }
//
//    // Core: hide everything that has any tag in HideTags; show everything with any tag in ShowTags
//    static void SetHiddenByTags(const TArray<FName>& HideTags, const TArray<FName>& ShowTags)
//    {
//        UWorld* World = GetActiveEditorOrPIEWorld();
//        if (!World) { UE_LOG(LogTemp, Warning, TEXT("No valid world.")); return; }
//
//        const FScopedTransaction Tx(FText::FromString(TEXT("Toggle Sky Systems (Tags)")));
//
//        int32 Hidden = 0, Shown = 0;
//
//        // Hide pass
//        for (TActorIterator<AActor> It(World); It; ++It)
//        {
//            AActor* A = *It;
//            if (!A) continue;
//            for (const FName& Tag : HideTags)
//            {
//                if (A->ActorHasTag(Tag))
//                {
//                    ApplyVisibilityToActor(A, /*bHidden=*/true);
//                    ++Hidden;
//                    break; // one match is enough
//                }
//            }
//        }
//
//        // Show pass
//        for (TActorIterator<AActor> It(World); It; ++It)
//        {
//            AActor* A = *It;
//            if (!A) continue;
//            for (const FName& Tag : ShowTags)
//            {
//                if (A->ActorHasTag(Tag))
//                {
//                    ApplyVisibilityToActor(A, /*bHidden=*/false);
//                    ++Shown;
//                    break;
//                }
//            }
//        }
//
//        // Optional repaint if you’ve linked UnrealEd; otherwise comment it out.
//        // if (GEditor) { GEditor->RedrawAllViewports(true); }
//
//        UE_LOG(LogTemp, Log, TEXT("Tag toggle: Hidden=%d, Shown=%d"), Hidden, Shown);
//    }
//}
#endif // WITH_EDITOR


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SWeatherSettingsDialog::Construct(const FArguments& InArgs)
{
    WeatherController = InArgs._WeatherController;

    //#if WITH_EDITOR
    //SetHiddenByTags(
    //    /*Hide*/{ FName("SkySphere1"), FName("SkySphere2") ,FName("DirectionalLight") },
    //    /*Show*/{ FName("Ultra_Dynamic_Sky"), FName("Ultra_Dynamic_Weather") }
    //);
    //#endif


    for (const FWeatherPreset& Preset : SWeatherPresetsDefined::GetAllPresets())
    {
        if (Preset.Name != "ChangeSkyBox" && Preset.Name != "ShadowsOff" && Preset.Name != "ShadowsOn") // hide from dropdown
        {
            WeatherOptions.Add(MakeShared<FString>(Preset.Name));
        }
    }
    SelectedWeatherOption = WeatherOptions.Num() > 0 ? WeatherOptions[0] : nullptr;

    // ✅ Manually add Overcast (DataAsset-based)
    WeatherOptions.Add(MakeShared<FString>(TEXT("Overcast")));
    WeatherOptions.Add(MakeShared<FString>(TEXT("Clear_Skies")));
    WeatherOptions.Add(MakeShared<FString>(TEXT("Cloudy")));
    WeatherOptions.Add(MakeShared<FString>(TEXT("Foggy")));
    WeatherOptions.Add(MakeShared<FString>(TEXT("Partly_Cloudy")));
    WeatherOptions.Add(MakeShared<FString>(TEXT("Rain")));
    WeatherOptions.Add(MakeShared<FString>(TEXT("Rain_Light")));
    WeatherOptions.Add(MakeShared<FString>(TEXT("Rain_Thunderstorm")));
    WeatherOptions.Add(MakeShared<FString>(TEXT("Sand_Dust_Calm")));
    WeatherOptions.Add(MakeShared<FString>(TEXT("Sand_Dust_Storm")));
    WeatherOptions.Add(MakeShared<FString>(TEXT("Snow")));
    WeatherOptions.Add(MakeShared<FString>(TEXT("Snow_Blizzard")));
    WeatherOptions.Add(MakeShared<FString>(TEXT("Snow_Light")));


    //    ChildSlot
    //        [
    //            SNew(SBorder)
    //                .Padding(10)
    //                [
    //                    SNew(SScrollBox) // <-- added
    //                        + SScrollBox::Slot()
    //                        [
    //                            SNew(SVerticalBox)
    //
    //                                + SVerticalBox::Slot().AutoHeight().Padding(5)
    //                                [
    //                                    SNew(STextBlock).Text(FText::FromString("Weather Preset:"))
    //                                ]
    //
    //                                + SVerticalBox::Slot().AutoHeight().Padding(5)
    //                                [
    //                                    SNew(SComboBox<TSharedPtr<FString>>)
    //                                        .OptionsSource(&WeatherOptions)
    //                                        .OnGenerateWidget_Lambda([](TSharedPtr<FString> InItem)
    //                                            {
    //                                                return SNew(STextBlock).Text(FText::FromString(*InItem));
    //                                            })
    //                                        .OnSelectionChanged_Lambda([this](TSharedPtr<FString> NewSelection, ESelectInfo::Type)
    //                                            {
    //                                                SelectedWeatherOption = NewSelection;
    //                                                const FWeatherPreset Preset = SWeatherPresetsDefined::GetPresetByName(*SelectedWeatherOption);
    //                                                EditableProperties = Preset.Properties;
    //                                            })
    //                                        .InitiallySelectedItem(SelectedWeatherOption)
    //                                        [
    //                                            SNew(STextBlock)
    //                                                .Text_Lambda([this]() -> FText
    //                                                    {
    //                                                        return FText::FromString(*SelectedWeatherOption);
    //                                                    })
    //                                        ]
    //                                ]
    //
    //                            + SVerticalBox::Slot().AutoHeight().Padding(5)
    //                                [AddEditableField("Time of Day:", EditableProperties.TimeOfDay)]
    //
    //                                + SVerticalBox::Slot().AutoHeight().Padding(5)
    //                                [AddEditableField("Fog Density:", EditableProperties.Fog)]
    //
    //                                + SVerticalBox::Slot().AutoHeight().Padding(5)
    //                                [AddEditableField("Cloud Coverage:", EditableProperties.CloudCoverage)]
    //
    //                                + SVerticalBox::Slot().AutoHeight().Padding(5)
    //                                [AddEditableField("Wind Intensity:", EditableProperties.WindIntensity)]
    //
    //                                + SVerticalBox::Slot().AutoHeight().Padding(5)
    //                                [AddEditableField("Wind Direction:", EditableProperties.WindDirection)]
    //
    //                                + SVerticalBox::Slot().AutoHeight().Padding(5)
    //                                [AddEditableField("Dust Density:", EditableProperties.Dust)]
    //
    //                                + SVerticalBox::Slot().AutoHeight().Padding(5)
    //                                [AddEditableField("Rain Density:", EditableProperties.Rain)]
    //
    //                                + SVerticalBox::Slot().AutoHeight().Padding(5)
    //                                [AddEditableField("Snow Density:", EditableProperties.Snow)]
    //
    //                                + SVerticalBox::Slot().AutoHeight().Padding(5)
    //                                [AddEditableField("Thunder Lightning:", EditableProperties.ThunderLightning)]
    //
    //                                + SVerticalBox::Slot().AutoHeight().Padding(5)
    //                                [AddEditableField("Fog Shadows", EditableProperties.FogShadows)]
    //
    //                                + SVerticalBox::Slot().AutoHeight().Padding(5)
    //                                [AddEditableField("Dust Shadows", EditableProperties.DustShadows)]
    //
    //                                + SVerticalBox::Slot().AutoHeight().Padding(5)
    //                                [AddEditableField("Base Height Fog FallOff", EditableProperties.BaseHeightFogFalloff)]
    //
    //                                + SVerticalBox::Slot().AutoHeight().Padding(5)
    //                                [AddEditableField("Dust Amount", EditableProperties.DustAmount)]
    //
    //                                + SVerticalBox::Slot().AutoHeight().Padding(5)
    //                                [AddEditableField("Fog", EditableProperties.Fog)]
    //
    //                                + SVerticalBox::Slot().AutoHeight().Padding(5)
    //                                [AddEditableField("Dust Density Contribution", EditableProperties.DustDensityContribution)]
    //
    //                                + SVerticalBox::Slot().AutoHeight().Padding(5)
    //                                [AddEditableField("Dust Height Fog FallOff", EditableProperties.DustyHeightFogFalloff)]
    //
    //                                + SVerticalBox::Slot().AutoHeight().Padding(5)
    //                                [AddColorField("Dust Color", EditableProperties.DustColor)]
    //
    //                                + SVerticalBox::Slot().AutoHeight().Padding(5)
    //                                [AddEditableField("Base Fog Density", EditableProperties.BaseFogDensity)]
    //
    //
    //                                + SVerticalBox::Slot().AutoHeight().Padding(5)
    //                                [
    //                                    SNew(SButton)
    //                                        .Text(FText::FromString("Apply"))
    //                                        .HAlign(HAlign_Center)
    //                                        .ButtonColorAndOpacity(FLinearColor::Blue)
    //                                        .OnClicked_Lambda([this]() {
    //                                        if (WeatherController.IsValid())
    //                                        {
    //                                            WeatherController->updateWeather(EditableProperties);
    //                                        }
    //                                        return FReply::Handled();
    //                                            })
    //                                ]
    //
    //                            + SVerticalBox::Slot().AutoHeight().Padding(5)
    //                                [
    //                                    SNew(SButton)
    //                                        .Text(FText::FromString("Close"))
    //                                        .HAlign(HAlign_Center)
    //                                        .ButtonColorAndOpacity(FLinearColor::Red)
    //                                        .OnClicked_Lambda([this]() {
    //                                        TSharedPtr<SWindow> ParentWindow = FSlateApplication::Get().FindWidgetWindow(AsShared());
    //                                        if (ParentWindow.IsValid())
    //                                        {
    //                                            ParentWindow->RequestDestroyWindow();
    //                                        }
    //                                        return FReply::Handled();
    //                                            })
    //                                ]
    //                        ]
    //]
    //        ];

    ChildSlot
        [
            SNew(SBorder)
                .Padding(10)
                [
                    SNew(SVerticalBox)

                        // Label
                        + SVerticalBox::Slot().AutoHeight().Padding(5)
                        [
                            SNew(STextBlock)
                                .Text(FText::FromString("Select Weather Preset:"))
                        ]

                        // Preset ComboBox
                        + SVerticalBox::Slot().AutoHeight().Padding(5)
                        [
                            SNew(SComboBox<TSharedPtr<FString>>)
                                .OptionsSource(&WeatherOptions)
                                .OnGenerateWidget_Lambda([](TSharedPtr<FString> InItem)
                                    {
                                        return SNew(STextBlock).Text(FText::FromString(*InItem));
                                    })
                                //.OnSelectionChanged_Lambda([this](TSharedPtr<FString> NewSelection, ESelectInfo::Type)
                                //    {
                                //        SelectedWeatherOption = NewSelection;
                                //        /*const FWeatherPreset Preset = SWeatherPresetsDefined::GetPresetByName(*SelectedWeatherOption);
                                //        EditableProperties = Preset.Properties;*/

                                //        if (WeatherController.IsValid())
                                //        {
                                //            FString AssetName = *SelectedWeatherOption;
                                //            FString Path = FString::Printf(TEXT("/Game/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/%s.%s"), *AssetName, *AssetName);

                                //            WeatherController->ApplyUDSWeatherAsset(Path);
                                //        }


                                //    })
                                .OnSelectionChanged_Lambda([this](TSharedPtr<FString> NewSelection, ESelectInfo::Type)
                                    {
                                        SelectedWeatherOption = NewSelection;
                                        FString PresetName = *SelectedWeatherOption;

                                        // Skip ChangeSkyBox, handled by button, filhal it's not part of it 
                                        if (PresetName == TEXT("ChangeSkyBox"))
                                        {
                                            return;
                                        }

                                        if (WeatherController.IsValid())
                                        {
                                            const FWeatherPreset CustomPreset = SWeatherPresetsDefined::GetPresetByName(PresetName);

                                            if (CustomPreset.Name != "Default")
                                            {
                                                WeatherController->ResetToManualWeather();
                                                WeatherController->ResetSkySettingsToDefault();
                                                EditableProperties = CustomPreset.Properties;
                                                WeatherController->updateWeather(EditableProperties);
                                            }
                                            else
                                            {
                                                WeatherController->ResetToManualWeather();
                                                WeatherController->ResetSkySettingsToDefault();
                                                //WeatherController->HardCacheReset();


                                                FString Path = FString::Printf(TEXT("/Game/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/%s.%s"), *PresetName, *PresetName);
                                                WeatherController->ApplyUDSWeatherAsset(Path);
                                            }
                                        }
                                    })



                                .InitiallySelectedItem(SelectedWeatherOption)
                                [
                                    SNew(STextBlock)
                                        .Text_Lambda([this]() { return FText::FromString(*SelectedWeatherOption); })
                                ]
                        ]

                    // Apply Button
                    + SVerticalBox::Slot().AutoHeight().Padding(5)
                        [
                            SNew(SButton)
                                .Text(FText::FromString("Apply"))
                                .HAlign(HAlign_Center)
                                .OnClicked_Lambda([this]() {
                                if (WeatherController.IsValid())
                                {
                                    WeatherController->updateWeather(EditableProperties);
                                }
                                return FReply::Handled();
                                    })
                        ]
                    // ChangeSkyBox Button
                    + SVerticalBox::Slot().AutoHeight().Padding(5)
                        [
                            SNew(SButton)
                                .Text(FText::FromString("Change SkyBox"))
                                .HAlign(HAlign_Center)
                                .ButtonColorAndOpacity(FLinearColor(0.2f, 0.6f, 1.0f, 1.0f)) // light blue
                                .OnClicked_Lambda([this]() {

                                if (WeatherController.IsValid())
                                {
                                    const FWeatherPreset SkyBoxPreset = SWeatherPresetsDefined::GetPresetByName(TEXT("ChangeSkyBox"));

                                    if (SkyBoxPreset.Name != "Default")
                                    {
                                        // Clear current UDS preset
                                        WeatherController->ResetToManualWeather();

                                        FWeatherProperties PropertiesCopy = EditableProperties;
                                        if (PropertiesCopy.ColorMode == EUDSColorMode::SkyAtmosphere)
                                        {
                                            PropertiesCopy.ColorMode = EUDSColorMode::SimplifiedColor;
                                        }
                                        else
                                        {
                                            PropertiesCopy.ColorMode = EUDSColorMode::SkyAtmosphere;
                                        }

                                        EditableProperties = PropertiesCopy;
                                        WeatherController->updateWeather(EditableProperties);
                                    }
                                }

                                return FReply::Handled();
                                    })
                        ]

                    // --- Use PPV only ---
                    + SVerticalBox::Slot().AutoHeight().Padding(5)
                        [
                            SNew(SButton)
                                .Text(FText::FromString("MR Mode"))
                                .HAlign(HAlign_Center)
                                .OnClicked_Lambda([this]()
                                    {
                                        if (WeatherController.IsValid())
                                        {
                                            // Show PPV only, hide others
                                            WeatherController->SetPPVVisible(true);
                                            WeatherController->SetSkySphere1Visible(false);
                                            //WeatherController->DirectionalLightVisible(true);
                                            WeatherController->SetUDSVisible(false);
                                        }

                                        return FReply::Handled();
                                    })
                        ]
                    // --- Use SkySphere 1 ---
                    + SVerticalBox::Slot().AutoHeight().Padding(5)
                        [
                            SNew(SButton)
                                .Text(FText::FromString("Use SkySphere 1"))
                                .HAlign(HAlign_Center)
                                .OnClicked_Lambda([this]()
                                    {
                                        if (WeatherController.IsValid())
                                        {
                                            // Show SkySphere1, hide others
                                            WeatherController->SetSkySphere1Visible(true);
                                            WeatherController->SetPPVVisible(true);
                                            WeatherController->ChangeMaterialOnRunTime(false);
                                            //WeatherController->DirectionalLightVisible(true);
                                            WeatherController->SetUDSVisible(false);

                                        }
                                        return FReply::Handled();
                                    })
                        ]

                    // --- Use SkySphere 2 ---
                    + SVerticalBox::Slot().AutoHeight().Padding(5)
                        [
                            SNew(SButton)
                                .Text(FText::FromString("Use SkySphere 2"))
                                .HAlign(HAlign_Center)
                                .OnClicked_Lambda([this]()
                                    {
                                        if (WeatherController.IsValid())
                                        {
                                            // Show SkySphere2, hide others
                                            WeatherController->SetSkySphere1Visible(true);
                                            WeatherController->ChangeMaterialOnRunTime(true);
                                            WeatherController->SetPPVVisible(true);
                                            //WeatherController->DirectionalLightVisible(true);
                                            WeatherController->SetUDSVisible(false);
                                        }

                                        return FReply::Handled();
                                    })
                        ]

                    // --- Use Ultra Dynamic Sky (UDS) ---
                    + SVerticalBox::Slot().AutoHeight().Padding(5)
                        [
                            SNew(SButton)
                                .Text(FText::FromString("Use Ultra Dynamic Sky"))
                                .HAlign(HAlign_Center)
                                .OnClicked_Lambda([this]()
                                    {
                                        if (WeatherController.IsValid())
                                        {
                                            // Show UDS, hide others
                                            WeatherController->SetSkySphere1Visible(false);
                                            WeatherController->DirectionalLightVisible(false);
                                            WeatherController->SetPPVVisible(false);
                                            WeatherController->SetUDSVisible(true);
                                        }


                                        return FReply::Handled();
                                    })
                        ]


                    + SVerticalBox::Slot().AutoHeight().Padding(5)
                        [
                            SNew(SHorizontalBox)

                                // Label
                                + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(0, 0, 8, 0)
                                [
                                    SNew(STextBlock)
                                        .Text(FText::FromString("Ambient Cubemap Intensity (0 to 100)"))
                                ]

                                // Slider: displays current PPV intensity, sends 0..100 to your function on change
                                + SHorizontalBox::Slot().FillWidth(1).VAlign(VAlign_Center)
                                [
                                    SNew(SSlider)
                                        // Show current value from PPV (0..4 -> 0..1)
                                        .Value_Lambda([this]()
                                            {
                                                if (WeatherController.IsValid() && WeatherController->PostProcessVolume)
                                                {
                                                    const float cur = WeatherController->PostProcessVolume->Settings.AmbientCubemapIntensity; // 0..4
                                                    return FMath::Clamp(cur / 4.f, 0.f, 1.f);
                                                }
                                                return 0.f;
                                            })
                                        // On change: map 0..1 -> 0..100 and call your function
                                        .OnValueChanged_Lambda([this](float Normalized01)
                                            {
                                                if (WeatherController.IsValid())
                                                {
                                                    WeatherController->SetAmbientCubemapIntensityFromPercent(Normalized01 * 100.f);
                                                }
                                            })
                                        .ToolTipText(FText::FromString("Drag: 0–100 (mapped to 0–4 internally)"))
                                ]

                            // Readout (derived from PPV live; no local state)
                            + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(8, 0, 0, 0)
                                [
                                    SNew(STextBlock)
                                        .Text_Lambda([this]()
                                            {
                                                if (WeatherController.IsValid() && WeatherController->PostProcessVolume)
                                                {
                                                    const float cur = WeatherController->PostProcessVolume->Settings.AmbientCubemapIntensity; // 0..4
                                                    const float percent = FMath::Clamp(cur / 4.f * 100.f, 0.f, 100.f);
                                                    return FText::FromString(FString::Printf(TEXT("%.0f"), percent));
                                                }
                                                return FText::FromString(TEXT("-"));
                                            })
                                ]
                        ]

                    // Disable Shadows
                    + SVerticalBox::Slot().AutoHeight().Padding(5)
                        [
                            SNew(SButton)
                                .Text(FText::FromString("Disable Shadows"))
                                .HAlign(HAlign_Center)
                                .OnClicked_Lambda([this]()
                                    {
                                        if (WeatherController.IsValid())
                                        {
                                            const FWeatherPreset Preset = SWeatherPresetsDefined::GetPresetByName("ShadowsOff");
                                            if (WeatherController.IsValid())
                                            {
                                                WeatherController->ApplySunCastShadows(false);
                                                WeatherController->ApplyMoonCastShadows(false);
                                                WeatherController->ApplySkyLightCastShadows(false);
                                                WeatherController->ApplyLightningLightCastShadows(false);
                                                //WeatherController->SetDirectionalLightCastShadows(false);
                                            }
                                                
                                        }
                                        return FReply::Handled();
                                    })
                        ]

                    // Enable Shadows
                    + SVerticalBox::Slot().AutoHeight().Padding(5)
                        [
                            SNew(SButton)
                                .Text(FText::FromString("Enable Shadows"))
                                .HAlign(HAlign_Center)
                                .OnClicked_Lambda([this]()
                                    {
                                        //WeatherController->RefreshUltraDynamicSky();
                                        if (WeatherController.IsValid())
                                        {
                                            const FWeatherPreset Preset = SWeatherPresetsDefined::GetPresetByName("ShadowsOn");
                                            if (WeatherController.IsValid())
                                            {
                                                WeatherController->ApplySunCastShadows(true);
                                                WeatherController->ApplyMoonCastShadows(true);
                                                WeatherController->ApplySkyLightCastShadows(true);
                                                WeatherController->ApplyLightningLightCastShadows(true);
                                                //WeatherController->SetDirectionalLightCastShadows(true);
                                            }

                                        } 
                                        return FReply::Handled();

                                    })
                        ]

                    // Day Button
                    + SVerticalBox::Slot().AutoHeight().Padding(5)
                        [
                            SNew(SButton)
                                .Text(FText::FromString("Day"))
                                .HAlign(HAlign_Center)
                                .OnClicked_Lambda([this]() {

                                const FWeatherPreset CustomPreset = SWeatherPresetsDefined::GetPresetByName("Day");

                                if (CustomPreset.Name == "Day")
                                {

                                    UE_LOG(LogTemp, Log, TEXT("Preset 'Day' found."));
                                }
                                else
                                {

                                    UE_LOG(LogTemp, Log, TEXT("Preset 'Day' not found!"));

                                }


                                if (CustomPreset.Name != "Default")
                                {
                                    WeatherController->ResetToManualWeather();
                                    WeatherController->ResetSkySettingsToDefault();
                                    //EditableProperties = CustomPreset.Properties;
                                    WeatherController->updateWeather(CustomPreset.Properties);
                                }
                                return FReply::Handled();
                                    })
                        ]

                    // Night Button
                    + SVerticalBox::Slot().AutoHeight().Padding(5)
                        [
                            SNew(SButton)
                                .Text(FText::FromString("Night"))
                                .HAlign(HAlign_Center)
                                .OnClicked_Lambda([this]() {

                                const FWeatherPreset CustomPreset = SWeatherPresetsDefined::GetPresetByName("Night");

                                if (CustomPreset.Name == "Night")
                                {

                                    UE_LOG(LogTemp, Log, TEXT("Preset 'Night' found."));
                                }
                                else
                                {

                                    UE_LOG(LogTemp, Log, TEXT("Preset 'Night' not found!"));

                                }


                                if (CustomPreset.Name != "Default")
                                {
                                    WeatherController->ResetToManualWeather();
                                    WeatherController->ResetSkySettingsToDefault();
                                    //EditableProperties = CustomPreset.Properties;
                                    WeatherController->updateWeather(CustomPreset.Properties);
                                }
                                return FReply::Handled();
                                    })
                        ]
                        
                    // Dawn Button
                    + SVerticalBox::Slot().AutoHeight().Padding(5)
                        [
                            SNew(SButton)
                                .Text(FText::FromString("Dawn"))
                                .HAlign(HAlign_Center)
                                .OnClicked_Lambda([this]() {

                                const FWeatherPreset CustomPreset = SWeatherPresetsDefined::GetPresetByName("Dawn");

                                if (CustomPreset.Name == "Dawn")
                                {

                                    UE_LOG(LogTemp, Log, TEXT("Preset 'Dawn' found."));
                                }
                                else
                                {

                                    UE_LOG(LogTemp, Log, TEXT("Preset 'Dawn' not found!"));

                                }


                                if (CustomPreset.Name != "Default")
                                {
                                    WeatherController->ResetToManualWeather();
                                    WeatherController->ResetSkySettingsToDefault();
                                    //EditableProperties = CustomPreset.Properties;
                                    WeatherController->updateWeather(CustomPreset.Properties);
                                }
                                return FReply::Handled();
                                    })
                        ]

                    // Dusk Button
                    + SVerticalBox::Slot().AutoHeight().Padding(5)
                        [
                            SNew(SButton)
                                .Text(FText::FromString("Dusk"))
                                .HAlign(HAlign_Center)
                                .OnClicked_Lambda([this]() {

                                const FWeatherPreset CustomPreset = SWeatherPresetsDefined::GetPresetByName("Dusk");

                                if (CustomPreset.Name == "Dusk")
                                {

                                    UE_LOG(LogTemp, Log, TEXT("Preset 'Dusk' found."));
                                }
                                else
                                {

                                    UE_LOG(LogTemp, Log, TEXT("Preset 'Dusk' not found!"));

                                }


                                if (CustomPreset.Name != "Default")
                                {
                                    WeatherController->ResetToManualWeather();
                                    WeatherController->ResetSkySettingsToDefault();
                                    //EditableProperties = CustomPreset.Properties;
                                    WeatherController->updateWeather(CustomPreset.Properties);
                                }
                                return FReply::Handled();
                                    })
                        ]
                    // Close Button
                    +SVerticalBox::Slot().AutoHeight().Padding(5)
                        [
                            SNew(SButton)
                                .Text(FText::FromString("Close"))
                                .HAlign(HAlign_Center)
                                .OnClicked_Lambda([this]() {
                                TSharedPtr<SWindow> ParentWindow = FSlateApplication::Get().FindWidgetWindow(AsShared());
                                if (ParentWindow.IsValid())
                                {
                                    ParentWindow->RequestDestroyWindow();
                                }
                                return FReply::Handled();
                                    })
                        ]

                ]
        ];

}

//TSharedRef<SWidget> SWeatherSettingsDialog::AddEditableField(const FString& Label, float& Target)
//{
//    return SNew(SVerticalBox)
//        + SVerticalBox::Slot().AutoHeight().Padding(2)
//        [SNew(STextBlock).Text(FText::FromString(Label))]
//
//        + SVerticalBox::Slot().AutoHeight().Padding(2)
//        [
//            SNew(SEditableTextBox)
//                .Text_Lambda([&Target]() { return FText::AsNumber(Target); })
//                .OnTextCommitted_Lambda([&Target](const FText& NewText, ETextCommit::Type CommitType)
//                    {
//                        Target = FCString::Atof(*NewText.ToString());
//                    })
//        ];
//}
//
//TSharedRef<SWidget> SWeatherSettingsDialog::AddColorField(const FString& Label, FLinearColor& Color)
//{
//    return SNew(SVerticalBox)
//        + SVerticalBox::Slot().AutoHeight().Padding(5)
//        [
//            SNew(STextBlock).Text(FText::FromString(Label))
//        ]
//        + SVerticalBox::Slot().AutoHeight().Padding(5)
//        [
//            SNew(SHorizontalBox)
//                + SHorizontalBox::Slot().Padding(2).FillWidth(1.0f)
//                [
//                    SNew(SEditableTextBox)
//                        .Text_Lambda([&]() { return FText::AsNumber(Color.R); })
//                        .OnTextCommitted_Lambda([&](const FText& NewText, ETextCommit::Type) {
//                        Color.R = FCString::Atof(*NewText.ToString());
//                            })
//                ]
//            + SHorizontalBox::Slot().Padding(2).FillWidth(1.0f)
//                [
//                    SNew(SEditableTextBox)
//                        .Text_Lambda([&]() { return FText::AsNumber(Color.G); })
//                        .OnTextCommitted_Lambda([&](const FText& NewText, ETextCommit::Type) {
//                        Color.G = FCString::Atof(*NewText.ToString());
//                            })
//                ]
//            + SHorizontalBox::Slot().Padding(2).FillWidth(1.0f)
//                [
//                    SNew(SEditableTextBox)
//                        .Text_Lambda([&]() { return FText::AsNumber(Color.B); })
//                        .OnTextCommitted_Lambda([&](const FText& NewText, ETextCommit::Type) {
//                        Color.B = FCString::Atof(*NewText.ToString());
//                            })
//                ]
//            + SHorizontalBox::Slot().Padding(2).FillWidth(1.0f)
//                [
//                    SNew(SEditableTextBox)
//                        .Text_Lambda([&]() { return FText::AsNumber(Color.A); })
//                        .OnTextCommitted_Lambda([&](const FText& NewText, ETextCommit::Type) {
//                        Color.A = FCString::Atof(*NewText.ToString());
//                            })
//                ]
//        ];
//}


void SWeatherSettingsDialog::OnCloseClicked()
{
    TSharedPtr<SWindow> ParentWindow = FSlateApplication::Get().FindWidgetWindow(AsShared());
    if (ParentWindow.IsValid())
    {
        ParentWindow->RequestDestroyWindow();
    }
}

void SWeatherSettingsDialog::OnTextCommitted(const FText& NewText, ETextCommit::Type CommitType, float& TargetProperty)
{
    TargetProperty = FCString::Atof(*NewText.ToString());
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
