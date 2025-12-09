#include "SWeatherPresetsDefined.h"
#include<../Team RenderStorm/WeatherController.h>

TArray<FWeatherPreset> SWeatherPresetsDefined::GetAllPresets()
{
    //FWeatherProperties ClearSkies;
    //ClearSkies.CloudCoverage = 0.0f;
    //ClearSkies.Rain = 0.0f;
    //ClearSkies.Snow= 0.0f;
    //ClearSkies.ThunderLightning= 0.0f;
    //ClearSkies.WindIntensity = 2.0f;
    //ClearSkies.Fog = 0.0f;
    //ClearSkies.Dust = 0.0f;
    //ClearSkies.RayleighColor = FLinearColor(0.073413f, 0.172646f, 0.317708f, 1.0f); //sky color
    //
    //FWeatherProperties Cloudy;
    //Cloudy.CloudCoverage = 5.0f;
    //Cloudy.Rain = 0.0f;
    //Cloudy.Snow = 0.0f;
    //Cloudy.ThunderLightning = 0.0f;
    //Cloudy.WindIntensity = 2.5f;
    //Cloudy.Fog = 1.0f;
    //Cloudy.Dust = 0.0f;
    //Cloudy.RayleighColor = FLinearColor(0.073413f, 0.172646f, 0.317708f, 1.0f); //sky color

    //FWeatherProperties Foggy;
    //Foggy.CloudCoverage = 0.0f;
    //Foggy.Rain = 0.0f;
    //Foggy.Snow = 0.0f;
    //Foggy.ThunderLightning = 0.0f;
    //Foggy.WindIntensity = 1.0f;
    //Foggy.Fog = 7.0f;
    //Foggy.Dust = 0.0f;
    //Foggy.RayleighColor = FLinearColor(0.073413f, 0.172646f, 0.317708f, 1.0f); //sky color

    //FWeatherProperties Overcast;
    //Overcast.CloudCoverage = 7.5f;
    //Overcast.Rain = 0.0f;
    //Overcast.Snow = 0.0f;
    //Overcast.ThunderLightning = 0.0f;
    //Overcast.WindIntensity = 3.0f;
    //Overcast.Fog = 1.5f;
    //Overcast.Dust = 0.0f;
    //Overcast.RayleighColor = FLinearColor(0.168627f, 0.407843f, 1.0f, 1.0f); //sky color

    //FWeatherProperties PartlyCloudy;
    //PartlyCloudy.CloudCoverage = 3.8f;
    //PartlyCloudy.Rain = 0.0f;
    //PartlyCloudy.Snow = 0.0f;
    //PartlyCloudy.ThunderLightning = 0.0f;
    //PartlyCloudy.WindIntensity = 2.0f;
    //PartlyCloudy.Fog = 1.0f;
    //PartlyCloudy.Dust = 0.0f;
    //PartlyCloudy.RayleighColor = FLinearColor(0.073413f, 0.172646f, 0.317708f, 1.0f); //sky color


    //FWeatherProperties Rain;
    //Rain.CloudCoverage = 0.0f;
    //Rain.Rain = 4.0f;
    //Rain.Snow = 0.0f;
    //Rain.ThunderLightning = 4.0f;
    //Rain.WindIntensity = 0.0f;
    //Rain.Fog = 0.0f;
    //Rain.Dust = 0.0f;
    //Rain.RayleighColor = FLinearColor(0.073413f, 0.172646f, 0.317708f, 1.0f); //sky color

    //FWeatherProperties Rain_Light;
    //Rain_Light.CloudCoverage = 6.0f;
    //Rain_Light.Rain = 3.0f;
    //Rain_Light.Snow = 0.0f;
    //Rain_Light.ThunderLightning = 1.0f;
    //Rain_Light.WindIntensity = 2.0f;
    //Rain_Light.Fog = 1.5f;
    //Rain_Light.Dust = 0.0f;
    //Rain_Light.RayleighColor = FLinearColor(0.073413f, 0.172646f, 0.317708f, 1.0f); //sky color

    //FWeatherProperties Rain_Thunderstorm;
    //Rain_Thunderstorm.CloudCoverage = 8.0f;
    //Rain_Thunderstorm.Rain = 10.0f;
    //Rain_Thunderstorm.Snow = 0.0f;
    //Rain_Thunderstorm.ThunderLightning = 10.0f;
    //Rain_Thunderstorm.WindIntensity = 10.0f;
    //Rain_Thunderstorm.Fog = 6.5f;
    //Rain_Thunderstorm.Dust = 0.0f;
    //Rain_Thunderstorm.RayleighColor = FLinearColor(0.073413f, 0.172646f, 0.317708f, 1.0f); //sky color

    //FWeatherProperties Sand_Dust_Calm;
    //Sand_Dust_Calm.CloudCoverage = 0.0f;
    //Sand_Dust_Calm.Rain = 0.0f;
    //Sand_Dust_Calm.Snow = 0.0f;
    //Sand_Dust_Calm.ThunderLightning = 0.0f;
    //Sand_Dust_Calm.WindIntensity = 1.0f;
    //Sand_Dust_Calm.Fog = 1.0f;
    //Sand_Dust_Calm.Dust = 0.0f;
    //Sand_Dust_Calm.RayleighColor = FLinearColor(0.073413f, 0.172646f, 0.317708f, 1.0f); //sky color

    //FWeatherProperties Sand_Dust_Storm;
    //Sand_Dust_Calm.CloudCoverage = 0.0f;
    //Sand_Dust_Calm.Rain = 0.0f;
    //Sand_Dust_Calm.Snow = 0.0f;
    //Sand_Dust_Calm.ThunderLightning = 0.0f;
    //Sand_Dust_Calm.WindIntensity = 10.0f;
    //Sand_Dust_Calm.Fog = 0.0f;
    //Sand_Dust_Calm.Dust = 10.0f;
    //Sand_Dust_Calm.RayleighColor = FLinearColor(0.073413f, 0.172646f, 0.317708f, 1.0f); //sky color


    //FWeatherProperties Snow;
    //Snow.CloudCoverage = 8.5f;
    //Snow.Rain = 0.0f;
    //Snow.Snow = 6.0f;
    //Snow.ThunderLightning = 0.0f;
    //Snow.WindIntensity = 4.0f;
    //Snow.Fog = 5.0f;
    //Snow.Dust = 0.0f;
    //Snow.RayleighColor = FLinearColor(0.073413f, 0.172646f, 0.317708f, 1.0f); //sky color

    //FWeatherProperties Snow_Blizzard;
    //Snow_Blizzard.CloudCoverage = 10.0f;
    //Snow_Blizzard.Rain = 0.0f;
    //Snow_Blizzard.Snow = 10.0f;
    //Snow_Blizzard.ThunderLightning = 0.0f;
    //Snow_Blizzard.WindIntensity = 10.0f;
    //Snow_Blizzard.Fog = 10.0f;
    //Snow_Blizzard.Dust = 0.0f;
    //Snow_Blizzard.RayleighColor = FLinearColor(0.073413f, 0.172646f, 0.317708f, 1.0f); //sky color

    //FWeatherProperties Snow_Light;
    //Snow_Light.CloudCoverage = 6.0f;
    //Snow_Light.Rain = 0.0f;
    //Snow_Light.Snow = 3.0f;
    //Snow_Light.ThunderLightning = 0.0f;
    //Snow_Light.WindIntensity = 1.0f;
    //Snow_Light.Fog = 3.0f;
    //Snow_Light.Dust = 0.0f;
    //Snow_Light.RayleighColor = FLinearColor(0.073413f, 0.172646f, 0.317708f, 1.0f); //sky color

    FWeatherProperties HazeProps;
    HazeProps.TimeOfDay = 900.0f;
    HazeProps.FogShadows = 0.8f;
    HazeProps.DustShadows = 0.42f;
    HazeProps.BaseHeightFogFalloff = 0.5f;
    HazeProps.DustAmount = 0.5888f;
    HazeProps.DustDensityContribution = 0.57f;
    HazeProps.DustyHeightFogFalloff = 0.1f;
    HazeProps.DustColor = FLinearColor(1.0f, 0.8f, 0.6f, 1.0f);
    HazeProps.Fog = 5.9f;
    HazeProps.CloudCoverage = 0.5f;
    HazeProps.WindIntensity = 0.0f;
    HazeProps.WindDirection = 0.0f;
    HazeProps.Dust = 0.0f;
    HazeProps.Rain = 0.0f;
    HazeProps.Snow = 0.0f;
    HazeProps.ThunderLightning = 0.0f;

    //FWeatherProperties RainProps;
    //RainProps.TimeOfDay = 980.0f;
    //RainProps.Fog = 5.0f;
    //RainProps.CloudCoverage = 6.0f;
    //RainProps.WindIntensity = 0.5f;
    //RainProps.WindDirection = 90.0f;
    ////RainProps.DustAmount = 0.3f;
    //RainProps.Dust = 3.0f;
    //RainProps.DustColor = FLinearColor(0.02416f, 0.007506f, 0.036458f, 1.0f);
    //RainProps.Rain = 8.0f;
    //RainProps.Snow = 0.0f;
    //RainProps.BottomAltitude = 10.0f;
    //RainProps.VolumetricCloudScale = 5.0f;
    //RainProps.LayerHeightScale = 0.1f;
    //RainProps.CloudFormationTextureScale = 1.8f;
    //RainProps.NoiseScale3D = 4.0f;
    //RainProps.ErosionIntensity3D = 1.0f;
    //RainProps.ExtinctionScale = 5.0f;
    //RainProps.RayleighColor = FLinearColor(0.652327, 0.682292f, 0.650507f, 1.0f); //sky color
    //RainProps.PostProcessWindFog = false;

   /* FWeatherProperties CloudyProps;
    CloudyProps.TimeOfDay = 1100.0f;
    CloudyProps.Fog = 0.3f;
    CloudyProps.CloudCoverage = 0.9f;
    CloudyProps.WindIntensity = 0.2f;
    CloudyProps.WindDirection = 180.0f;*/

    /*FWeatherProperties SnowProps;
    SnowProps.TimeOfDay = 700.0f;
    SnowProps.Fog = 0.5f;
    SnowProps.CloudCoverage = 0.7f;
    SnowProps.WindIntensity = 0.2f;
    SnowProps.WindDirection = 270.0f;
    SnowProps.Snow = 1.0f;
    SnowProps.ThunderLightning = 0.1f;*/

    FWeatherProperties FogProps;
    FogProps.TimeOfDay = 880.0f;
    FogProps.Fog = 7.0f;
    FogProps.CloudCoverage = 0.2f;
    FogProps.WindIntensity = 1.0f;
    FogProps.WindDirection = 60.0f;
    FogProps.Dust = 0.0f;

    FWeatherProperties CirrocumulusProps;
    CirrocumulusProps.TimeOfDay = 1594.0f;
    CirrocumulusProps.CloudCoverage = 5.76f;
    CirrocumulusProps.BottomAltitude = 1.589f;
    CirrocumulusProps.VolumetricCloudScale = 2.21f;
    CirrocumulusProps.LayerHeightScale = 0.521f;
    CirrocumulusProps.NoiseScale3D = 1.43f;
    CirrocumulusProps.ErosionIntensity3D = 0.94f;
    CirrocumulusProps.ExtinctionScale = 13.2472f;
    CirrocumulusProps.CloudWispsOpacity = 0.704f;
    CirrocumulusProps.Fog = 0.0f;
    CirrocumulusProps.RayleighColor = FLinearColor(0.073413f, 0.172646f, 0.317708f, 1.0f); //sky color


    FWeatherProperties CirrostratusProps;
    CirrostratusProps.TimeOfDay = 960.0f;
    //CirrostratusProps.SkyMode = "Static Clouds"; // Sky Mode
    //CirrocumulusProps.SkyMode = UDS_SkyMode::StaticClouds;
    CirrostratusProps.CloudCoverage = 1.0f;
    CirrostratusProps.StaticCloudsTexture = "Wind Turbulence Vector And Gust Magnitude";
    CirrostratusProps.StaticCloudsRotationSpeed = 0.128f;
    CirrostratusProps.StaticCloudsColorIntensity = 1.0f;
    CirrostratusProps.CloudWispsOpacity = 1.0f;
    CirrostratusProps.CloudWispsOpacityClear = 1.0f;
    CirrostratusProps.CloudWispsColorIntensity = 2.04f;
    CirrostratusProps.BottomAltitude = -0.6f;
    CirrostratusProps.VolumetricCloudScale = 2.21f;
    CirrostratusProps.LayerHeightScale = 0.2f;
    CirrostratusProps.NoiseScale3D = 0.4f;
    CirrostratusProps.ErosionIntensity3D = 0.3f;
    CirrostratusProps.ExtinctionScale = 13.2472f;
    CirrostratusProps.RayleighColor = FLinearColor(0.073413f, 0.172646f, 0.317708f, 1.0f); //sky color


    FWeatherProperties CumulusCongestusProps;
    CumulusCongestusProps.TimeOfDay = 887.0f;
    //CirrostratusProps.SkyMode = "Static Clouds"; // Sky Mode
    //CirrocumulusProps.SkyMode = UDS_SkyMode::StaticClouds;
    CumulusCongestusProps.CloudCoverage = 2.5f;
    CumulusCongestusProps.CloudWispsOpacity = 1.0f;
    CumulusCongestusProps.CloudWispsColorIntensity = 2.04f;
    CumulusCongestusProps.BottomAltitude = 30.0f;
    CumulusCongestusProps.VolumetricCloudScale = 5.0f;
    CumulusCongestusProps.LayerHeightScale = 2.0f;
    CumulusCongestusProps.CloudFormationTextureScale = 1.8f;
    CumulusCongestusProps.NoiseScale3D = 4.0f;
    CumulusCongestusProps.ErosionIntensity3D = 1.0f;
    CumulusCongestusProps.ExtinctionScale = 5.0f;
    CumulusCongestusProps.CloudWispsOpacity = 0.0f;
    CumulusCongestusProps.CloudWispsOpacityClear = 0.0f;
    CumulusCongestusProps.CloudSpeed = 0.35f;
    CumulusCongestusProps.CloudDirection = 180.0f;
    CumulusCongestusProps.TracingMaxStartDistance = 17.0f;
    CumulusCongestusProps.RayleighColor = FLinearColor(0.073413f, 0.172646f, 0.317708f, 1.0f); //sky color


    FWeatherProperties CompleteClearSkies;
    CompleteClearSkies.CloudCoverage = 0.0f;
    CompleteClearSkies.Rain = 0.0f;
    CompleteClearSkies.Snow = 0.0f;
    CompleteClearSkies.ThunderLightning = 0.0f;
    CompleteClearSkies.WindIntensity = 2.0f;
    CompleteClearSkies.Fog = 0.0f;
    CompleteClearSkies.Dust = 0.0f;
    CompleteClearSkies.BaseHeightFogFalloff = 0.08f;
    CompleteClearSkies.CloudWispsOpacityClear = 0.0f;
    CompleteClearSkies.BaseFogDensity = 0.0f;
    CompleteClearSkies.RayleighColor = FLinearColor(0.168627f, 0.407843f, 1.0f, 1.0f);
    //CompleteClearSkies.ColorMode = EUDSColorMode::SimplifiedColor;

    FWeatherProperties NightSky;
    NightSky.BaseFogDensity = 0.0f;
    NightSky.BaseHeightFogFalloff = 0.0f;
    NightSky.Fog = 0.0f;
    NightSky.CloudWispsOpacityClear = 0.0f;
    NightSky.CloudCoverage = 0.0f;
    //NightSky.NightSkyGlowColor = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f); //black 
    //NightSky.BaseSkyColor = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //NightSky.RayleighColor = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f);
    NightSky.TimeOfDay = 2200.0f;

    static bool bIsSimplifiedColor = false;  // Persistent state (toggle flag)

    FWeatherProperties ChangeSkyBox;
    ChangeSkyBox.ColorMode = EUDSColorMode::SkyAtmosphere;  // Set to SkyAtmosphere
    /*ChangeSkyBox.BaseFogDensity = 0.0f;
    ChangeSkyBox.BaseHeightFogFalloff = 0.0f;
    ChangeSkyBox.Fog = 0.0f;
    ChangeSkyBox.CloudWispsOpacityClear = 0.0f;*/




    FWeatherProperties Default;

    FWeatherProperties ShadowsOn;
    ShadowsOn.SunCastsShadows = true;
    ShadowsOn.MoonCastsShadows = true;
    ShadowsOn.MovableSkyLightCastsShadows = true;
    ShadowsOn.StaticSkyLightCastsShadows = true;
    ShadowsOn.UseCloudShadows = true;


    FWeatherProperties ShadowsOff;
    ShadowsOff.SunCastsShadows = false;
    ShadowsOff.MoonCastsShadows = false;
    ShadowsOff.MovableSkyLightCastsShadows = false;
    ShadowsOff.StaticSkyLightCastsShadows = false;
    ShadowsOff.UseCloudShadows = false;

   
    //10AM, 9hours, 60 min= 10AM if 960
    
    //12PM
    FWeatherProperties Day;
    Day.TimeOfDay = 1200.0f;
    Day.CloudCoverage = 0.0f;

    //0 or 2400 corresponds to 12AM [MidNight]
    FWeatherProperties Night;
    Night.TimeOfDay = 2400.0f;
    Night.CloudCoverage = 0.0f;
    
    //6AM
    FWeatherProperties Dawn;
    Dawn.TimeOfDay = 630.0f;
    Dawn.CloudCoverage = 0.0f;

    //6PM
    FWeatherProperties Dusk;
    Dusk.TimeOfDay = 1800.0f;
    Dusk.CloudCoverage = 0.0f;



    // Toggle ColorMode between SkyAtmosphere and SimplifiedColor
    //if (bIsSimplifiedColor)
    //{
    //    ChangeSkyBox.ColorMode = EUDSColorMode::SkyAtmosphere;  // Set to SkyAtmosphere
    //    bIsSimplifiedColor = false;  // Flip the toggle state
    //    // Inside GetAllPresets()
    //    UE_LOG(LogTemp, Log, TEXT("Toggled ColorMode to: %s"), *UEnum::GetValueAsString(ChangeSkyBox.ColorMode));

    //}
    //else
    //{
    //    ChangeSkyBox.ColorMode = EUDSColorMode::SimplifiedColor;  // Set to SimplifiedColor
    //    bIsSimplifiedColor = true;  // Flip the toggle state
    //    // Inside GetAllPresets()
    //    UE_LOG(LogTemp, Log, TEXT("Toggled ColorMode to: %s"), *UEnum::GetValueAsString(ChangeSkyBox.ColorMode));

    //}



    return {
        //FWeatherPreset("Clear", ClearSkies),
        //FWeatherPreset("Cloudy", Cloudy),
        //FWeatherPreset("Foggy", Foggy),
        //FWeatherPreset("Overcast", Overcast),
       // FWeatherPreset("PartlyCloudy", PartlyCloudy),
        //FWeatherPreset("Rain", Rain),
       // FWeatherPreset("Rain_Light", Rain_Light),
        //FWeatherPreset("Rain_Thunderstorm", Rain_Thunderstorm),
       // FWeatherPreset("Sand_Dust_Calm", Sand_Dust_Calm),
       // FWeatherPreset("Sand_Dust_Storm", Sand_Dust_Storm),
       // FWeatherPreset("Snow", Snow),
       // FWeatherPreset("Snow_Blizzard", Snow_Blizzard),
       // FWeatherPreset("Snow_Light", Snow_Light),

        //FWeatherPreset("Haze", HazeProps),
        //FWeatherPreset("Fog", FogProps),
        FWeatherPreset("Default", Default),
        FWeatherPreset("CompleteClearSkies", CompleteClearSkies),
        FWeatherPreset("Cirrocumulus Clouds",CirrocumulusProps),
        FWeatherPreset("Cirrostratus Clouds", CirrostratusProps),
        FWeatherPreset("CumulusCongestus Clouds", CumulusCongestusProps),
        FWeatherPreset("ChangeSkyBox", ChangeSkyBox),
        FWeatherPreset("NightSky", NightSky),
        FWeatherPreset("ShadowsOn", ShadowsOn),
        FWeatherPreset("ShadowsOff", ShadowsOff),
        FWeatherPreset("Day", Day),
        FWeatherPreset("Night", Night),
        FWeatherPreset("Dawn", Dawn),
        FWeatherPreset("Dusk", Dusk)


        //Trying direct access
       // FWeatherPreset("Overcast", WeatherController->ApplyUDSWeatherAsset(TEXT("/Game/UltraDynamicSky/Blueprints/Weather_Effects/System/UDS_Weather_Settings.UDS_Weather_Settings_C'/Game/UltraDynamicSky/Blueprints/Weather_Effects/Weather_Presets/Overcast.Overcast'"));

    };
}


FWeatherPreset SWeatherPresetsDefined::GetPresetByName(const FString& Name)
{
    for (const FWeatherPreset& Preset : GetAllPresets())
    {
        if (Preset.Name.Equals(Name, ESearchCase::IgnoreCase))
        {
            return Preset;
        }
    }
    return FWeatherPreset("Default", {});
}
