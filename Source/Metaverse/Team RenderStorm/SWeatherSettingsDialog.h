
#pragma once
#include "CoreMinimal.h"
#include "WeatherProperties.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/SSlider.h"
#include "SWeatherPresetsDefined.h"             
#include "Widgets/Input/SComboBox.h"            

class AWeatherController;

class METAVERSE_API SWeatherSettingsDialog : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWeatherSettingsDialog) {}
		SLATE_ARGUMENT(TWeakObjectPtr<AWeatherController>, WeatherController)
		SLATE_ATTRIBUTE(FText, Title) // The text to display on the border
			SLATE_DEFAULT_SLOT(FArguments, Content)
	SLATE_END_ARGS()
	void Construct(const FArguments& InArgs);

	TSharedRef<SWidget> AddEditableField(const FString& Label, float& Property);
	TSharedRef<SWidget> AddColorField(const FString& Label, FLinearColor& Color);

private:

	TWeakObjectPtr<AWeatherController> WeatherController;
	FWeatherProperties EditableProperties;

	// ⬇ Added for preset support
	TArray<TSharedPtr<FString>> PresetNames;
	TSharedPtr<FString> SelectedPreset;

	TArray<TSharedPtr<FString>> WeatherOptions;
	TSharedPtr<FString> SelectedWeatherOption;

	void OnApplyClicked();
	void OnCloseClicked();
	void OnTextCommitted(const FText& NewText, ETextCommit::Type CommitType, float& TargetProperty);
};
