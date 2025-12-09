#pragma once
#include "UDSTypes.h"

// forward-declare the enum so we can use it as a field type
enum class EUDSColorMode : uint8;
struct FWeatherProperties
{

    //Sky Related Entities
    float TimeOfDay = 960.0f; // sky
    float FogShadows = 0.0f; //sky
    float DustShadows = 0.0f; //sky
    float BaseHeightFogFalloff = 0.0f; //sky
    float DustAmount = 0.0f; //sky
    float DustDensityContribution = 0.0f; //sky
    float DustyHeightFogFalloff = 0.0f; //sky
    float BaseFogDensity = 0.0f; //sky
    FLinearColor DustColor = FLinearColor::White; // ✅ RGBA color //sky

    //Weather Related Entities
    float Fog = 1.0f; // weather
    float CloudCoverage = 1.14f; // weather 
    float WindIntensity = 0.09f; // weather
    float WindDirection = 1.0f; // weather
    float Dust = 0.0f;// weather
    float Rain = 0.0f; //weather
    float Snow = 0.0f; // weather
    float ThunderLightning = 0.0f; //weather


    // Cloud-related-- Cirrocumulus
    float BottomAltitude = 0.0f;
    float VolumetricCloudScale = 0.0f;
    float LayerHeightScale = 0.0f;
    float NoiseScale3D = 0.0f;
    float ErosionIntensity3D = 0.0f;
    float ExtinctionScale = 0.0f;
    float CloudWispsOpacity = 0.0f;
    float CloudWispsOpacityClear = 0.0f;

    //CirroStratus Clouds
    // Assuming SkyMode is of type UDS_SkyMode
    //UDS_SkyMode SkyMode = UDS_SkyMode::StaticClouds;
    FString StaticCloudsTexture;               // Texture name or ID
    float StaticCloudsRotationSpeed = 0.0f;
    float StaticCloudsColorIntensity = 1.0f;
    float CloudWispsColorIntensity = 1.0f;


    float CloudFormationTextureScale = 0.0f;
    float CloudSpeed = 0.0f;
    float CloudDirection = 0.0f;
    float TracingMaxStartDistance = 0.0f;

    FLinearColor RayleighColor = FLinearColor::White;
    bool PostProcessWindFog = true;

    EUDSColorMode ColorMode = EUDSColorMode::SkyAtmosphere;

    FLinearColor BaseSkyColor = FLinearColor::White;
    FLinearColor NightSkyGlowColor = FLinearColor::White;


    bool SunCastsShadows = true;
    bool MoonCastsShadows = true;
    bool MovableSkyLightCastsShadows = true;
    bool StaticSkyLightCastsShadows = true;
    bool UseCloudShadows = true;
    bool LightningFlashesCastsShadows = true;

};

