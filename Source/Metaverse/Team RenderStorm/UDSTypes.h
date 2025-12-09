// UDSTypes.h
#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EUDSColorMode : uint8
{
    SkyAtmosphere   UMETA(DisplayName = "Sky Atmosphere"),
    SimplifiedColor UMETA(DisplayName = "Simplified Color"),
    // Add more color modes here if needed
};
