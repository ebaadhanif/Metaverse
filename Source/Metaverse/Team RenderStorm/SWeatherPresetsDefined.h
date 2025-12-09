#pragma once

#include "WeatherProperties.h"

// Represents a named weather preset + its values
struct FWeatherPreset
{
    FString Name;
    FWeatherProperties Properties;

    FWeatherPreset(const FString& InName, const FWeatherProperties& InProps)
        : Name(InName), Properties(InProps) {
    }
};

class SWeatherPresetsDefined
{
public:
    static TArray<FWeatherPreset> GetAllPresets();
    static FWeatherPreset GetPresetByName(const FString& Name);
};
