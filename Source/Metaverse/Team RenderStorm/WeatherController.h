#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeatherProperties.h"
#include "UDSTypes.h"
#include "Engine/DirectionalLight.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/LightComponentBase.h"
#include "MegaScanPresetParentWrapper.h"
#include "Components/WindDirectionalSourceComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "SWeatherSettingsDialog.h"
#undef UpdateResource
#include "Engine/TextureCube.h"
#include "Engine/WindDirectionalSource.h"
#include "WeatherController.generated.h"




//UENUM(BlueprintType)
//enum class UDS_SkyMode : uint8
//{
//    StaticClouds UMETA(DisplayName = "Static Clouds"),
//    VolumetricClouds UMETA(DisplayName = "Volumetric Clouds"),
//    // Add other modes as needed
//};

//UENUM(BlueprintType)
//enum class EUDSColorMode : uint8
//{
//    SkyAtmosphere UMETA(DisplayName = "Sky Atmosphere"),
//    SimplifiedColor UMETA(DisplayName = "Simplified Color"),
//    // Add other modes as needed
//};

UENUM(BlueprintType)
enum class ESkyProperties : uint8
{
    //Here we are actually mapping the UDS actors
    EUDSColorMode UMETA(DisplayName = "Color Mode"),
    TimeofDay UMETA(DisplayName = "Time Of Day"),
    FogShadows       UMETA(DisplayName = "FogShadows"),
    DustShadows      UMETA(DisplayName = "DustShadows"),
    BaseHeightFogFalloff UMETA(DisplayName = "Base Height Fog Falloff"),
    DustAmount       UMETA(DisplayName = "Dust Amount"),
    DustDensityContribution UMETA(DisplayName = "Dust Density Contribution"),
    DustyHeightFogFalloff  UMETA(DisplayName = "Dusty Height Fog Falloff"),
    DustColor        UMETA(DisplayName = "Dust Color"),

    //For Cirrocumulus clouds
    BottomAltitude    UMETA(DisplayName = "Bottom Altitude"),
    VolumetricCloudScale UMETA(DisplayName = "Volumetric Clouds Scale"),
    LayerHeightScale  UMETA(DisplayName = "Layer Height Scale"),
    NoiseScale3D      UMETA(DisplayName = "3D Noise Scale"),
    ErosionIntensity3D UMETA(DisplayName = "3D Erosion Intensity"),
    ExtinctionScale   UMETA(DisplayName = "Extinction Scale"),
    CloudWispsOpacityCloudy UMETA(DisplayName = "Cloud Wisps Opacity (Cloudy)"),
    CloudWispsOpacityClear UMETA(DisplayName = "Cloud Wisps Opacity (Clear)"),

    //For Cirrostratus clouds
    //SkyMode                     UMETA(DisplayName = "Sky Mode"),
    StaticCloudsTexture         UMETA(DisplayName = "Static Clouds Texture"),
    StaticCloudsRotationSpeed   UMETA(DisplayName = "Static Clouds Rotation Speed"),
    StaticCloudsColorIntensity  UMETA(DisplayName = "Static Clouds Color Intensity"),
    CloudWispsColorIntensity    UMETA(DisplayName = "Cloud Wisps Color Intensity"),

    //For CirroCongestus Clouds
    CloudFormationTextureScale  UMETA(DisplayName = "Cloud Formation Texture Scale"),
    CloudSpeed UMETA(DisplayName = "Cloud Speed"),
    CloudDirection UMETA(DisplayName = "Cloud Direction"),
    TracingMaxStartDistance UMETA(DisplayName = "Tracing Max Start Distance"),
    RayleighColor UMETA(DisplayName = "Rayleigh Scattering Color (Day)"),
    BaseSkyColor UMETA(DisplayName = "Base Sky Color (Night)"),
    NightSkyGlowColor UMETA(DisplayName = "Night Sky Glow Color"),
    BaseFogDensity  UMETA(DisplayName = "Base Fog Density"),

    //Dealing With Shadows
    SunCastsShadows UMETA(DisplayName = "Sun Casts Shadows"),
    MoonCastsShadows UMETA(DisplayName = "Moon Casts Shadows"),
    StaticSkyLightCastsShadows UMETA(DisplayName = "Static/Stationary Sky Light Casts Shadows"),
    MovableSkyLightCastsShadows UMETA(DisplayName = "Movable Sky Light Casts Shadows (Enable DFAO)"),
    UseCloudShadows UMETA(DisplayName = "Use Cloud Shadows")
};

UENUM(BlueprintType)
enum class EWeatherProperties : uint8
{
    WindDirection UMETA(DisplayName = "Wind Direction"),
    Snow UMETA(DisplayName = "Snow"),
    ThunderLightning UMETA(DisplayName = "Thunder/ Lightning"),
    CloudCoverage UMETA(DisplayName = "Cloud Coverage"),
    Fog UMETA(DisplayName = "Fog"),
    WindIntensity UMETA(DisplayName = "Wind Intensity"),
    Rain UMETA(DisplayName = "Rain"),
    Dust UMETA(DisplayName = "Dust"),
    PostProcessWindFog UMETA(DisplayName = "Enable Post Process Wind Fog"),
    LightningFlashesCastsShadows UMETA(DisplayName = "Lightning Flashes Cast Shadows")


    /*  UberGraphFrame UMETA(DisplayName = "UberGraphFrame"),
      Rainbow UMETA(DisplayName = "Rainbow"),
      PlayerOcclusion UMETA(DisplayName = "Player Occlusion"),
      LightRain_Y_Negative UMETA(DisplayName = "Light Rain Y Negative"),
      LightRain_Y_Positive UMETA(DisplayName = "Light Rain Y Positive"),
      LightRain_X_Negative UMETA(DisplayName = "Light Rain X Negative"),
      LightRain_X_Positive UMETA(DisplayName = "Light Rain X Positive"),
      Dust_Particles UMETA(DisplayName = "Dust Particles"),
      Wind_Debris_Particles UMETA(DisplayName = "Wind Debris Particles"),
      Snow_Particles UMETA(DisplayName = "Snow Particles"),
      ScreenDroplets UMETA(DisplayName = "Screen Droplets"),
      Wind_X_Positive UMETA(DisplayName = "Wind X Positive"),
      Rain_Y_Negative UMETA(DisplayName = "Rain Y Negative"),
      Rain_Y_Positive UMETA(DisplayName = "Rain Y Positive"),
      Rain_X_Negative UMETA(DisplayName = "Rain X Negative"),
      Rain_X_Positive UMETA(DisplayName = "Rain X Positive"),
      Wind_Y_Negative UMETA(DisplayName = "Wind Y Negative"),
      Wind_Y_Positive UMETA(DisplayName = "Wind Y Positive"),
      Wind_X_Negative UMETA(DisplayName = "Wind X Negative"),
      SpatializedAudioRoot UMETA(DisplayName = "Spatialized Audio Root"),
      PostProcessWindFog UMETA(DisplayName = "Post Process Wind Fog"),
      RandomWeatherVariation UMETA(DisplayName = "Random Weather Variation"),
      WindWhistling UMETA(DisplayName = "Wind Whistling"),
      DistantThunderCue UMETA(DisplayName = "Distant Thunder Cue"),
      ObscuredLightning UMETA(DisplayName = "Obscured Lightning"),
      LightningLight UMETA(DisplayName = "Lightning Light"),
      Root UMETA(DisplayName = "Root"),
      Rain_Particles UMETA(DisplayName = "Rain Particles"),
      UltraDynamicSky UMETA(DisplayName = "Ultra Dynamic Sky"),
      Weather UMETA(DisplayName = "Weather"),
      MaterialWetness UMETA(DisplayName = "Material Wetness"),
      MaterialSnowCoverage UMETA(DisplayName = "Material Snow Coverage"),
      LerpToNewSettings UMETA(DisplayName = "Lerp To New Settings"),
      LerpToStaticSettings UMETA(DisplayName = "Lerp To Static Settings"),
      TransitionInTime UMETA(DisplayName = "Transition In Time"),
      TransitionState UMETA(DisplayName = "Transition State"),
      Timer UMETA(DisplayName = "Timer"),
      ParticleCollisionEnabled UMETA(DisplayName = "Particle Collision Enabled"),
      CameraForwardSpawnOffset UMETA(DisplayName = "Camera Forward Spawn Offset"),
      CeilingCheckHeight UMETA(DisplayName = "Ceiling Check Height"),
      SpawnBoxHeight UMETA(DisplayName = "Spawn Box Height"),
      MaxSpawnDistance UMETA(DisplayName = "Max Spawn Distance"),
      SpawnDistanceDistribution UMETA(DisplayName = "Spawn Distance Distribution"),
      MinimumParticleDistance UMETA(DisplayName = "Minimum Particle Distance"),
      UseWaterLevel UMETA(DisplayName = "Use Water Level"),
      WaterLevel UMETA(DisplayName = "Water Level"),
      WeatherParticleCollisionChannel UMETA(DisplayName = "Weather Particle Collision Channel"),
      ScaleDistantParticles UMETA(DisplayName = "Scale Distant Particles"),
      EnableRainParticles UMETA(DisplayName = "Enable Rain Particles"),
      MaxRainParticleSpawnRate UMETA(DisplayName = "Max Rain Particle Spawn Rate"),
      RainDropsScale UMETA(DisplayName = "Rain Drops Scale"),
      RainParticleColorMultiplier UMETA(DisplayName = "Rain Particle Color Multiplier"),
      RainDropsAlpha UMETA(DisplayName = "Rain Drops Alpha"),
      RenderRaindropDecals UMETA(DisplayName = "Render Raindrop Decals"),
      SplashFrequency UMETA(DisplayName = "Splash Frequency"),
      SplashParticlesScale UMETA(DisplayName = "Splash Particles Scale"),
      MaxDuplicateSplashParticles UMETA(DisplayName = "Max Duplicate Splash Particles"),
      MaxDuplicateSplashRange UMETA(DisplayName = "Max Duplicate Splash Range"),
      EnableSnowParticles UMETA(DisplayName = "Enable Snow Particles"),
      MaxSnowParticleSpawnRate UMETA(DisplayName = "Max Snow Particle Spawn Rate"),
      SnowFlakesScale UMETA(DisplayName = "Snow Flakes Scale"),
      SnowFlakesAlpha UMETA(DisplayName = "Snow Flakes Alpha"),
      SnowParticleColorMultiplier UMETA(DisplayName = "Snow Particle Color Multiplier"),
      SnowFlakesStickToSurfaces UMETA(DisplayName = "Snow Flakes Stick To Surfaces"),
      SnowFlakesStickTime UMETA(DisplayName = "Snow Flakes Stick Time"),
      SpawnLightningFlashes UMETA(DisplayName = "Spawn Lightning Flashes"),
      LightningFlashIntervalMin UMETA(DisplayName = "Lightning Flash Interval Min"),
      LightningFlashIntervalMax UMETA(DisplayName = "Lightning Flash Interval Max"),
      LightningFlashTimingRandomization UMETA(DisplayName = "Lightning Flash Timing Randomization"),
      LightningFlashLightSource UMETA(DisplayName = "Lightning Flash Light Source")*/

};

UCLASS()
class METAVERSE_API AWeatherController : public AActor
{
    GENERATED_BODY()
public:
    AWeatherController();
    // void ChangeSkyModeAtRuntime(UDS_SkyMode NewSkyMode);
protected:
    virtual void BeginPlay() override;
public:
    void updateWeather(FWeatherProperties weatherProperties);
    void ApplyWindEffectOnMegaScanAssetsandWindsourceDirectionAssets(float windSpeed, float windDir);
    void ApplyWindEffectUsingWindDirectionalSource(float windSpeed, float windDir);


    //Here, we are changing the default weather options
    UFUNCTION(BlueprintCallable, Category = "Weather")
    void ApplyUDSWeatherAsset(const FString& AssetPath);

    UFUNCTION(BlueprintCallable, Category = "Weather")
    void ResetToManualWeather();
    void ResetSkySettingsToDefault();

private:
    UPROPERTY() UStaticMesh* SkySphereMesh = nullptr;
    UPROPERTY() UMaterialInterface* NewMaterial = nullptr;
    UPROPERTY() UMaterialInterface* NewMaterial2 = nullptr;
    UPROPERTY() AStaticMeshActor* SkySphere1 = nullptr;
    UPROPERTY() AStaticMeshActor* SkySphere2 = nullptr;
    UPROPERTY() AActor* UltraDynamicSkyActor = nullptr;
    UPROPERTY() AActor* UltraDynamicWeatherActor = nullptr;
    UPROPERTY() ADirectionalLight* MyDirectionalLight = nullptr;



    UPROPERTY() UTextureCube* Cube = nullptr;

    void ChangeColorModeToSimplified();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weather")
    AMegaScanPresetParentWrapper* GlobalFoliageActor;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weather")
    AWindDirectionalSource* WindDirectionalSourceActor;
    template<typename TEnum, typename TValue>
    void SetEnvironmentProperty(TEnum EnumKey, const TValue& NewValue);
    void AfterUDSVarsChanged();
    void ToggleSkyBoxColorMode(FWeatherProperties& WeatherProperties);

    void CallCompleteClearSkiesondefault();
    //// Function for updating the UDS!
    //UFUNCTION(BlueprintCallable)
    //void NudgeUDSTick();

    UPROPERTY() APostProcessVolume* PostProcessVolume = nullptr;

    // WeatherController.h
    UFUNCTION(BlueprintCallable, Category = "UDS")
    void RefreshUltraDynamicSky(bool bRerunConstruction = false);


    //Dealing With Shadows
    UDirectionalLightComponent* GetUDSSunComponent() const;
    void ApplySunCastShadows(bool bEnable);

    UDirectionalLightComponent* GetUDSMoonComponent() const;
    void ApplyMoonCastShadows(bool bEnable);

    UDirectionalLightComponent* GetUDSSkyLightComponent() const;
    void ApplySkyLightCastShadows(bool bEnable);


    UDirectionalLightComponent* GetUDSLightningComponent() const;
    void ApplyLightningLightCastShadows(bool bEnable);

    void SetDirectionalLightCastShadows(bool bEnable);

    void HardCacheReset();

    void SetAmbientCubemapIntensityFromPercent(float Percent0to100);

    bool ChangeMaterialOnRunTime(bool value);

    UFUNCTION(BlueprintCallable) void SetSkySphere1Visible(bool bVisible);
    //UFUNCTION(BlueprintCallable) void SetSkySphere2Visible(bool bVisible);
    UFUNCTION(BlueprintCallable) void SetUDSVisible(bool bVisible);
    UFUNCTION(BlueprintCallable) void DirectionalLightVisible(bool bVisible);
    UFUNCTION(BlueprintCallable) void SetPPVVisible(bool bVisible);

};

