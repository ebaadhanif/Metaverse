
#include "WeatherController.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Components/VolumetricCloudComponent.h"
#include "UObject/Class.h"
#include "UObject/UnrealType.h"
//#include "SWeatherPresetsDefined.cpp"

AWeatherController::AWeatherController()
{
    PrimaryActorTick.bCanEverTick = false;
    UltraDynamicSkyActor = nullptr;
    UltraDynamicWeatherActor = nullptr;
}

void AWeatherController::BeginPlay()
{
    Super::BeginPlay();
    CallCompleteClearSkiesondefault();
    // Find Sky Actor
    for (TActorIterator<AActor> It(GetWorld()); It; ++It)
    {
        if (It->ActorHasTag("Ultra_Dynamic_Sky"))
        {
            UltraDynamicSkyActor = *It;
            UE_LOG(LogTemp, Warning, TEXT("Found Ultra Dynamic Sky Actor: %s"), *UltraDynamicSkyActor->GetName());
            break;
        }
    }

    // Find Weather Actor
    for (TActorIterator<AActor> It(GetWorld()); It; ++It)
    {
        if (It->GetName().Contains("Ultra_Dynamic_Weather"))
        {
            UltraDynamicWeatherActor = *It;
            UE_LOG(LogTemp, Warning, TEXT("Found Ultra Dynamic Weather Actor: %s"), *UltraDynamicWeatherActor->GetName());
            break;
        }
    }

    // Check if both actors were found
    if (!UltraDynamicSkyActor)
    {
        UE_LOG(LogTemp, Error, TEXT("Ultra Dynamic Sky Actor not found!"));
    }

    if (!UltraDynamicWeatherActor)
    {
        UE_LOG(LogTemp, Error, TEXT("Ultra Dynamic Weather Actor not found!"));
    }

    UE_LOG(LogTemp, Warning, TEXT("I am printing all the properties of UDS"));

    //For checking the property names(just for UDS) in the output log
    for (TFieldIterator<FProperty> It(UltraDynamicSkyActor->GetClass()); It; ++It)
    {
        UE_LOG(LogTemp, Warning, TEXT("Found property: %s"), *It->GetName());
    }

    //ApplyWindEffectOnMegaScanAssetsandWindsourceDirectionAssets(0, 0);

    //Creating SM_SkySpheres, loading my specific asset [i.e SkySphere] from unreal s
    //lOAD oBJECT always takes the reference path not the file path
    SkySphereMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/MapTemplates/Sky/SM_SkySphere.SM_SkySphere"));
    NewMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/SkyBox/BlueSky_Inst.BlueSky_Inst"));
    NewMaterial2 = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/SkyBox/BlackSky_Inst.BlackSky_Inst"));
    FVector SpawnLocation(0.f, 0.f, 0.f);   // where to place it@
    FRotator SpawnRotation(0.f, 0.f, 0.f); // rotation

    UE_LOG(LogTemp, Warning, TEXT("SkySphereMesh=%p  Blue=%p  Black=%p"),
        SkySphereMesh, NewMaterial, NewMaterial2);


    //Spawing the StaticMeshActor
    SkySphere1 = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), SpawnLocation, SpawnRotation);

    //checking if none of them are null, i.e I got both of these
    if (SkySphere1 && SkySphereMesh)
    {
        //here I'm setting it movable to allow it to assign my mesh on runtime
        UStaticMeshComponent* Comp = SkySphere1->GetStaticMeshComponent();
        Comp->SetMobility(EComponentMobility::Movable);

        // Assign the mesh
        SkySphere1->GetStaticMeshComponent()->SetStaticMesh(SkySphereMesh);

        // Scale them up so you are inside the dome
        FVector SkyScale(500000.f, 500000.f, 500000.f);
        SkySphere1->SetActorScale3D(SkyScale);
    }

    if (SkySphere1)
    {
        SkySphere1->GetStaticMeshComponent()->SetMaterial(0, NewMaterial);  //first is material ki index, next is the material itself
        UE_LOG(LogTemp, Warning, TEXT("Applied new material to %s"), *SkySphere1->GetName());
    }

    // Spawn dir light
   // MyDirectionalLight = GetWorld()->SpawnActor<ADirectionalLight>(ADirectionalLight::StaticClass(), SpawnLocation,SpawnRotation);
    //MyDirectionalLight->setIntensity();

    // Spawn postProcess
    PostProcessVolume = GetWorld()->SpawnActor<APostProcessVolume>(APostProcessVolume::StaticClass(), SpawnLocation, SpawnRotation);
#if WITH_EDITOR
    PostProcessVolume->SetActorLabel("Light POST PROCESS");
#endif
    // settings for it 
    PostProcessVolume->bUnbound = true;
    PostProcessVolume->Priority = 100.f;
    PostProcessVolume->BlendWeight = 1.f;

    //New settigs done for flickering issue
    PostProcessVolume->Settings.bOverride_LumenFinalGatherQuality = true;
    PostProcessVolume->Settings.LumenFinalGatherQuality = true;

    PostProcessVolume->Settings.bOverride_LumenFinalGatherScreenTraces = true;
    PostProcessVolume->Settings.LumenFinalGatherScreenTraces = false;


    // Assigning ambient cube from an asset
    Cube = LoadObject<UTextureCube>(nullptr, TEXT("/Engine/EngineResources/DefaultTextureCube.DefaultTextureCube"));

    if (Cube)
    {
        //thses settings struct is defined in PPV cpp class
        FPostProcessSettings& S = PostProcessVolume->Settings;
        //S.bOverride_AmbientCubemap = true;
        S.bOverride_AmbientCubemapTint = true;
        S.bOverride_AmbientCubemapIntensity = true;

        // --- Exposure: Manual + Compensation +7 EV ---
        S.bOverride_AutoExposureMethod = true;                 // enable override
        S.bOverride_AutoExposureBias = true; //it's display name is "Exposure Compensation"

        S.AmbientCubemap = Cube;
        S.AmbientCubemapTint = FLinearColor::White;
        S.AmbientCubemapIntensity = 1.0f;
        S.AutoExposureMethod = EAutoExposureMethod::AEM_Manual;
        S.AutoExposureBias = 10.0f;

    }

    SetSkySphere1Visible(false);
    DirectionalLightVisible(false);
    SetPPVVisible(false);
    SetUDSVisible(true);
    CallCompleteClearSkiesondefault();
}
// Map 0..100 (UI) -> 0..4 (engine) 
void AWeatherController::SetAmbientCubemapIntensityFromPercent(float Percent0to100)
{
    if (!PostProcessVolume) { UE_LOG(LogTemp, Warning, TEXT("PPV not valid")); return; }

    const float ClampedPct = FMath::Clamp(Percent0to100, 0.f, 100.f);
    const float Mapped = FMath::GetMappedRangeValueClamped(
        FVector2D(0.f, 100.f), FVector2D(0.f, 4.f), ClampedPct);

    FPostProcessSettings& S = PostProcessVolume->Settings;
    S.bOverride_AmbientCubemapIntensity = true;
    S.AmbientCubemapIntensity = Mapped;

    // logging it for debugging
    UE_LOG(LogTemp, Log, TEXT("AmbientCubemapIntensity set: %.2f (from %.0f%%)"), Mapped, ClampedPct);
}
bool AWeatherController::ChangeMaterialOnRunTime(bool value)
{
    if (value == true)
    {
        SkySphere1->GetStaticMeshComponent()->SetMaterial(0, NewMaterial2);
        UE_LOG(LogTemp, Warning, TEXT("Applied black material to %s"), *SkySphere1->GetName());
        return 1;

    }

    else
    {
        SkySphere1->GetStaticMeshComponent()->SetMaterial(0, NewMaterial);
        UE_LOG(LogTemp, Warning, TEXT("Applied blue material to %s"), *SkySphere1->GetName());
        return 0;
    }

}

//Dealing with visibility of all the actors 
static void ApplyVis(AActor* A, bool bVisible)
{
    if (!A) return;
    A->SetActorHiddenInGame(!bVisible);
    A->SetActorEnableCollision(bVisible);
    A->SetActorTickEnabled(bVisible);
    if (UPrimitiveComponent* PC = Cast<UPrimitiveComponent>(A->GetRootComponent()))
    {
        PC->SetVisibility(bVisible, true);
        PC->SetHiddenInGame(!bVisible, true);
        PC->MarkRenderStateDirty();
    }
    //setting visibility in the editor 
#if WITH_EDITOR
    A->SetIsTemporarilyHiddenInEditor(!bVisible);
#endif
}

void AWeatherController::SetSkySphere1Visible(bool bVisible) { ApplyVis(SkySphere1, bVisible); }
void AWeatherController::SetPPVVisible(bool bVisible) { ApplyVis(PostProcessVolume, bVisible); }
void AWeatherController::DirectionalLightVisible(bool bVisible) { ApplyVis(MyDirectionalLight, bVisible); }
void AWeatherController::SetUDSVisible(bool bVisible)
{
    ApplyVis(UltraDynamicSkyActor, bVisible);
    ApplyVis(UltraDynamicWeatherActor, bVisible);
}


void AWeatherController::updateWeather(FWeatherProperties weather)
{
    //set env property is picking up the exact display name here and matching it through reflection
    SetEnvironmentProperty(ESkyProperties::TimeofDay, weather.TimeOfDay);
    SetEnvironmentProperty(EWeatherProperties::CloudCoverage, weather.CloudCoverage);
    SetEnvironmentProperty(EWeatherProperties::Fog, weather.Fog);
    SetEnvironmentProperty(EWeatherProperties::Dust, weather.Dust);
    SetEnvironmentProperty(EWeatherProperties::Rain, weather.Rain);
    SetEnvironmentProperty(EWeatherProperties::WindIntensity, weather.WindIntensity);
    SetEnvironmentProperty(EWeatherProperties::ThunderLightning, weather.ThunderLightning);
    SetEnvironmentProperty(EWeatherProperties::Snow, weather.Snow);
    SetEnvironmentProperty(EWeatherProperties::WindDirection, weather.WindDirection);
    SetEnvironmentProperty(ESkyProperties::FogShadows, weather.FogShadows);
    SetEnvironmentProperty(ESkyProperties::DustShadows, weather.DustShadows);
    SetEnvironmentProperty(ESkyProperties::BaseHeightFogFalloff, weather.BaseHeightFogFalloff);
    SetEnvironmentProperty(ESkyProperties::DustAmount, weather.DustAmount);
    SetEnvironmentProperty(ESkyProperties::DustDensityContribution, weather.DustDensityContribution);
    SetEnvironmentProperty(ESkyProperties::DustyHeightFogFalloff, weather.DustyHeightFogFalloff);
    SetEnvironmentProperty(ESkyProperties::DustColor, weather.DustColor); // This one is FLinearColor

    //FOR CLOUDS
    SetEnvironmentProperty(ESkyProperties::BottomAltitude, weather.BottomAltitude);
    SetEnvironmentProperty(ESkyProperties::VolumetricCloudScale, weather.VolumetricCloudScale);
    SetEnvironmentProperty(ESkyProperties::LayerHeightScale, weather.LayerHeightScale);
    SetEnvironmentProperty(ESkyProperties::NoiseScale3D, weather.NoiseScale3D);
    SetEnvironmentProperty(ESkyProperties::ErosionIntensity3D, weather.ErosionIntensity3D);
    SetEnvironmentProperty(ESkyProperties::ExtinctionScale, weather.ExtinctionScale);
    SetEnvironmentProperty(ESkyProperties::CloudWispsOpacityCloudy, weather.CloudWispsOpacity);
    SetEnvironmentProperty(ESkyProperties::CloudWispsOpacityClear, weather.CloudWispsOpacityClear);

    //For CirroStratus Clouds
    //CirrostratusProps.SkyMode = UDS_SkyMode::StaticClouds;
    SetEnvironmentProperty(ESkyProperties::StaticCloudsTexture, weather.StaticCloudsTexture);
    SetEnvironmentProperty(ESkyProperties::StaticCloudsRotationSpeed, weather.StaticCloudsRotationSpeed);
    SetEnvironmentProperty(ESkyProperties::StaticCloudsColorIntensity, weather.StaticCloudsColorIntensity);
    SetEnvironmentProperty(ESkyProperties::CloudWispsColorIntensity, weather.CloudWispsColorIntensity);

    //For CirroCongestus Clouds
    SetEnvironmentProperty(ESkyProperties::CloudFormationTextureScale, weather.CloudFormationTextureScale);
    SetEnvironmentProperty(ESkyProperties::CloudSpeed, weather.CloudSpeed);
    SetEnvironmentProperty(ESkyProperties::CloudDirection, weather.CloudDirection);
    SetEnvironmentProperty(ESkyProperties::TracingMaxStartDistance, weather.TracingMaxStartDistance);

    //For Fog
    SetEnvironmentProperty(ESkyProperties::RayleighColor, weather.RayleighColor); // This one is FLinearColor
    SetEnvironmentProperty(EWeatherProperties::PostProcessWindFog, weather.PostProcessWindFog);
    SetEnvironmentProperty(ESkyProperties::BaseFogDensity, weather.BaseFogDensity);
    SetEnvironmentProperty(ESkyProperties::EUDSColorMode, weather.ColorMode);


    SetEnvironmentProperty(ESkyProperties::BaseSkyColor, weather.BaseSkyColor); // This one is FLinearColor
    SetEnvironmentProperty(ESkyProperties::NightSkyGlowColor, weather.NightSkyGlowColor);


    //SetEnvironmentProperty
    //ApplyWindEffectOnMegaScanAssetsandWindsourceDirectionAssets(weather.WindIntensity, weather.WindDirection);
    ApplyWindEffectUsingWindDirectionalSource(weather.WindIntensity, weather.WindDirection);


}

// WeatherController.cpp
//These functions arem't available to be accessed directly, sort of hidden type!, thus I'll not be going with this approach!

//void AWeatherController::AfterUDSVarsChanged()
//{
//    if (!UltraDynamicSkyActor) return;
//
//    if (UFunction* Fn = UltraDynamicSkyActor->FindFunction(TEXT("NewFunc1")))
//    {
//        
//        UltraDynamicSkyActor->ProcessEvent(Fn, nullptr);
//        UE_LOG(LogTemp, Log, TEXT("I Got the function"));
//        return;
//    }
//
//    // (Fallback if your UDS version names it differently)
//    if (UFunction* Fn2 = UltraDynamicSkyActor->FindFunction(TEXT("Update Low Priority Properties")))
//    {
//        UltraDynamicSkyActor->ProcessEvent(Fn2, nullptr);
//    }
//}

// UDS UPDATE TRY!
//void AWeatherController::NudgeUDSTick()
//{
//    if (UltraDynamicSkyActor)
//    {
//        UltraDynamicSkyActor->SetActorTickEnabled(true);   // heere it will tick next frame
//        UltraDynamicSkyActor->MarkComponentsRenderStateDirty();
//    }
//}


void AWeatherController::RefreshUltraDynamicSky(bool bRerunConstruction)
{
    //// (Re)locate the actor if the pointer is stale or null — same flow you use in BeginPlay.
    //if (UltraDynamicSkyActor)
    //{
    //    for (TActorIterator<AActor> It(GetWorld()); It; ++It)
    //    {
    //        if (It->ActorHasTag("Ultra_Dynamic_Sky"))
    //        {
    //            UltraDynamicSkyActor = *It;
    //            
    //            break;
    //        }
    //    }
    //}
    //if (!UltraDynamicSkyActor) { UE_LOG(LogTemp, Warning, TEXT("UDS actor not found")); return; }

    //// Optionally re-run the construction script (heavy but thorough).
    //if (bRerunConstruction)
    //    UltraDynamicSkyActor->RerunConstructionScripts();

    //// Make sure it renders/ticks next frame.
    //UltraDynamicSkyActor->MarkComponentsRenderStateDirty();
    //UltraDynamicSkyActor->SetActorTickEnabled(true);

    //// Try to call the UDS public update entry (names vary by UDS version).
    //auto TryCall = [&](const TCHAR* Name)->bool
    //    {
    //        if (UFunction* Fn = UltraDynamicSkyActor->FindFunction(FName(Name)))
    //        {
    //            UltraDynamicSkyActor->ProcessEvent(Fn, nullptr);
    //            UE_LOG(LogTemp, Log, TEXT("Called %s on UDS"), Name);
    //            return true;
    //        }
    //        return false;
    //    };

    //// Common variants (pick the one that exists in your BP)
    //if (TryCall(TEXT("Update Sky"))) return;
    //if (TryCall(TEXT("Update_Sky"))) return;
    //if (TryCall(TEXT("Update Low Priority Properties"))) return;
    //if (TryCall(TEXT("Update_Low_Priority_Properties"))) return;
}

//Dealing with Sun Shadows Functions
//In the Bp of UDS, We could match and see that the Sun_LightComponent is an instance of "DirectionalLightComponent"
UDirectionalLightComponent* AWeatherController::GetUDSSunComponent() const
{
    if (!UltraDynamicSkyActor) return nullptr;

    // A) Read the BP variable directly 
    //This is actually finding the exact matching property with Unreal's reflection system
    //It actually returns the metadata ofor that property, just the type, place in memory etc.
    //It's just that card for a specific library slot!
    if (FObjectProperty* P = FindFProperty<FObjectProperty>(
        UltraDynamicSkyActor->GetClass(), TEXT("Sun_LightComponent")))
    {

        //Here we actually find the instance 
        //Finding that component in UDS
        //here we find the actual refrence to that book that we want
        if (UObject* Obj = P->GetObjectPropertyValue_InContainer(UltraDynamicSkyActor))
            if (auto* Dir = Cast<UDirectionalLightComponent>(Obj))
                return Dir;
    }
    // b) Fallback: scan attached components
    return UltraDynamicSkyActor->FindComponentByClass<UDirectionalLightComponent>();
}

void AWeatherController::ApplySunCastShadows(bool bEnable)
{
    // keep UDS bool in sync (so the checkbox matches)
    SetEnvironmentProperty(ESkyProperties::SunCastsShadows, bEnable);

    // actually flip the light that renders shadows
    if (UDirectionalLightComponent* Sun = GetUDSSunComponent())
    {
        Sun->SetCastShadows(bEnable);

        //This actually ensures that the component needs to be updated!! 
        Sun->MarkRenderStateDirty();
    }
}

// Dealing with Moon Component
UDirectionalLightComponent* AWeatherController::GetUDSMoonComponent() const
{
    if (!UltraDynamicSkyActor) return nullptr;

    // A) Read the BP variable directly (exact name from your screenshot)
    if (FObjectProperty* P = FindFProperty<FObjectProperty>(
        UltraDynamicSkyActor->GetClass(), TEXT("Moon_LightComponent")))
    {
        if (UObject* Obj = P->GetObjectPropertyValue_InContainer(UltraDynamicSkyActor))
            if (auto* Dir = Cast<UDirectionalLightComponent>(Obj))
                return Dir;
        //Casting is being done as [It checks the runtime type of Obj
       // to ensure it’s compatible with UDirectionalLightComponent]
    }
    // b) Fallback: scan attached components and selects the first that it matches
    return UltraDynamicSkyActor->FindComponentByClass<UDirectionalLightComponent>();


}

void AWeatherController::ApplyMoonCastShadows(bool bEnable)
{
    // keep UDS bool in sync (so the checkbox matches)
    SetEnvironmentProperty(ESkyProperties::MoonCastsShadows, bEnable);  // the existing reflection path

    // actually flip the light that renders shadows
    if (UDirectionalLightComponent* Moon = GetUDSMoonComponent())
    {
        Moon->SetCastShadows(bEnable);
        Moon->MarkRenderStateDirty();
    }
}

// Dealing with SkyLight Component
UDirectionalLightComponent* AWeatherController::GetUDSSkyLightComponent() const
{
    if (!UltraDynamicSkyActor) return nullptr;

    // A) Read the BP variable directly (exact name from your screenshot)
    if (FObjectProperty* P = FindFProperty<FObjectProperty>(
        UltraDynamicSkyActor->GetClass(), TEXT("SkyLightComponent")))
    {
        if (UObject* Obj = P->GetObjectPropertyValue_InContainer(UltraDynamicSkyActor))
            if (auto* Dir = Cast<UDirectionalLightComponent>(Obj))
                return Dir;
    }
    // b) Fallback: scan attached components
    return UltraDynamicSkyActor->FindComponentByClass<UDirectionalLightComponent>();
}

void AWeatherController::ApplySkyLightCastShadows(bool bEnable)
{
    // keep UDS bool in sync (so the checkbox matches)
    SetEnvironmentProperty(ESkyProperties::StaticSkyLightCastsShadows, bEnable);
    SetEnvironmentProperty(ESkyProperties::MovableSkyLightCastsShadows, bEnable);

    // actually flip the light that renders shadows
    if (UDirectionalLightComponent* SkyLight = GetUDSSkyLightComponent())
    {
        SkyLight->SetCastShadows(bEnable);
        SkyLight->MarkRenderStateDirty();
    }
}

//Here I am dealing with the shadows that are caused by Rain_ThunderStorm {actually the flashes}
// Dealing with Lightning Light Component [In the Ultra Dynamic Weather]
UDirectionalLightComponent* AWeatherController::GetUDSLightningComponent() const
{
    if (!UltraDynamicWeatherActor) return nullptr;

    // A) Read the BP variable directly (exact name from your screenshot)
    if (FObjectProperty* P = FindFProperty<FObjectProperty>(
        UltraDynamicWeatherActor->GetClass(), TEXT("Lightning Light")))
    {
        if (UObject* Obj = P->GetObjectPropertyValue_InContainer(UltraDynamicWeatherActor))
            if (auto* Dir = Cast<UDirectionalLightComponent>(Obj))
                return Dir;
    }
    // b) Fallback: scan attached components
    return UltraDynamicWeatherActor->FindComponentByClass<UDirectionalLightComponent>();
}

void AWeatherController::ApplyLightningLightCastShadows(bool bEnable)
{
    // keep UDS bool in sync (so the checkbox matches)
    SetEnvironmentProperty(EWeatherProperties::LightningFlashesCastsShadows, bEnable);

    // actually flip the light that renders shadows
    if (UDirectionalLightComponent* LightningLight = GetUDSLightningComponent())
    {
        LightningLight->SetCastShadows(bEnable);
        LightningLight->MarkRenderStateDirty();
    }
}


//unreal's directional light
void AWeatherController::SetDirectionalLightCastShadows(bool bEnable)
{
    if (!MyDirectionalLight) return;

    UDirectionalLightComponent* Comp =
        Cast<UDirectionalLightComponent>(MyDirectionalLight->GetLightComponent());

    if (!Comp) return;

    if (Comp->Mobility == EComponentMobility::Static)
    {
        UE_LOG(LogTemp, Warning,
            TEXT("%s is Static; cannot toggle shadows at runtime."),
            *MyDirectionalLight->GetName());
        return;
    }

    // Toggle
    Comp->SetCastShadows(bEnable);
    Comp->MarkRenderStateDirty();

    UE_LOG(LogTemp, Log,
        TEXT("CastShadows=%s on %s"),
        bEnable ? TEXT("true") : TEXT("false"),
        *MyDirectionalLight->GetName());
}

// Step 1: Manually map enum name to internal property name
FString GetPropertyNameFromEnum(const FString& EnumName)
{
    // Mapping the enum name to the internal property name
    if (EnumName == TEXT("CloudWispsOpacityClear"))
    {
        return TEXT("Cloud Wisps Opacity (Clear)");  // Internal property name
    }
    else if (EnumName == TEXT("CloudWispsOpacityCloudy"))
    {
        return TEXT("Cloud Wisps Opacity (Cloudy)");  // Internal property name
    }
    // Add other mappings as necessary

    // Default case - return the enum name if no special mapping is found
    return EnumName;
}

//try
//"Time Of Day" → "timeofday"
static FString NormalizePropName(const FString& s) {
    FString out; out.Reserve(s.Len());
    for (TCHAR c : s) if (FChar::IsAlnum(c)) out.AppendChar(FChar::ToLower(c));
    return out;
}

//raw names mapping to exact internal names
static FString AliasEnumToBPName(const FString& name) {
    if (name == TEXT("TimeofDay"))   return TEXT("Time Of Day");
    if (name == TEXT("FogShadows"))  return TEXT("Fog Shadows");
    if (name == TEXT("DustShadows")) return TEXT("Dust Shadows");
    return name;
}

template<typename TEnum, typename TValue>
void AWeatherController::SetEnvironmentProperty(TEnum EnumKey, const TValue& NewValue)
{
    // Prefer raw enum token (stable in build), also take pretty label (Editor/localized)
    const FString rawName = StaticEnum<TEnum>()->GetNameStringByValue((int64)EnumKey);            // e.g. "TimeofDay"
    const FString niceLabel = StaticEnum<TEnum>()->GetDisplayNameTextByValue((int64)EnumKey).ToString(); // e.g. "Time Of Day" (or "TimeofDay")

    // Map through aliases; prefer the label mapping, fallback to raw token mapping
    FString wanted = AliasEnumToBPName(niceLabel);
    if (wanted == niceLabel) wanted = AliasEnumToBPName(rawName);

    // Choosing my target
    UObject* Target = nullptr;
    if constexpr (std::is_same_v<TEnum, ESkyProperties>)          Target = UltraDynamicSkyActor;
    else if constexpr (std::is_same_v<TEnum, EWeatherProperties>) Target = UltraDynamicWeatherActor;
    if (!Target) { UE_LOG(LogTemp, Warning, TEXT("Target is null for key %s/%s"), *niceLabel, *rawName); return; }

    // 1) Exact match (fast)
    FProperty* Property = Target->GetClass()->FindPropertyByName(FName(*wanted));

    // 2) Fuzzy fallback (ignores spaces, punctuation, case)
    if (!Property) {
        const FString key = NormalizePropName(wanted);
        for (TFieldIterator<FProperty> It(Target->GetClass()); It; ++It) {
            if (NormalizePropName(It->GetName()) == key) { Property = *It; break; }
        }
    }

    if (!Property) {
        UE_LOG(LogTemp, Warning, TEXT("Property '%s'/'%s' not found on %s"),
            *niceLabel, *rawName, *Target->GetName());
        return;
    }

    const FName PropertyName(*Property->GetName()); // keep your existing type write code below this line
    //FNumericProperty is a subclass of FProperty and only deals with numeric values like int, float, double etc.
    // Handle float
    if constexpr (std::is_same_v<TValue, float>)
    {
        if (FNumericProperty* NumProp = CastField<FNumericProperty>(Property))
        {
            NumProp->SetFloatingPointPropertyValue(NumProp->ContainerPtrToValuePtr<void>(Target), NewValue);
            UE_LOG(LogTemp, Log, TEXT("Set %s to %f on %s"), *PropertyName.ToString(), NewValue, *Target->GetName());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Property '%s' is not a float!"), *PropertyName.ToString());
        }
    }
    // Handle FString
    else if constexpr (std::is_same_v<TValue, FString>)
    {
        if (FStrProperty* StrProp = CastField<FStrProperty>(Property))
        {
            StrProp->SetPropertyValue(StrProp->ContainerPtrToValuePtr<void>(Target), *NewValue);
            UE_LOG(LogTemp, Log, TEXT("Set %s to '%s' on %s"), *PropertyName.ToString(), *NewValue, *Target->GetName());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Property '%s' is not a string!"), *PropertyName.ToString());
        }
    }

    // NEW: Handle FLinearColor
    else if constexpr (std::is_same_v<TValue, FLinearColor>)
    {
        if (FStructProperty* StructProp = CastField<FStructProperty>(Property))
        {
            if (StructProp->Struct == TBaseStructure<FLinearColor>::Get())
            {
                void* ValuePtr = StructProp->ContainerPtrToValuePtr<void>(Target);
                *reinterpret_cast<FLinearColor*>(ValuePtr) = NewValue;
                UE_LOG(LogTemp, Log, TEXT("Set %s to RGBA (%s) on %s"), *PropertyName.ToString(), *NewValue.ToString(), *Target->GetName());
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Property '%s' is a struct but not FLinearColor!"), *PropertyName.ToString());
            }
        }

        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Property '%s' is not a struct (FLinearColor)!"), *PropertyName.ToString());
        }
    }
    // Handle bool
    else if constexpr (std::is_same_v<TValue, bool>)
    {
        if (FBoolProperty* BoolProp = CastField<FBoolProperty>(Property))
        {
            BoolProp->SetPropertyValue(BoolProp->ContainerPtrToValuePtr<void>(Target), NewValue);
            UE_LOG(LogTemp, Log, TEXT("Set %s to %s on %s"), *PropertyName.ToString(), NewValue ? TEXT("true") : TEXT("false"), *Target->GetName());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Property '%s' is not a bool!"), *PropertyName.ToString());
        }
    }
    // Handle Enums (like ColorMode) correctly
    else if constexpr (std::is_enum<TValue>::value)
    {
        if (FEnumProperty* EnumProp = CastField<FEnumProperty>(Property))
        {
            // Convert the enum value to its underlying byte/int value
            void* ValuePtr = EnumProp->ContainerPtrToValuePtr<void>(Target);
            EnumProp->GetUnderlyingProperty()->SetIntPropertyValue(ValuePtr, static_cast<int64>(NewValue));
            UE_LOG(LogTemp, Log, TEXT("Set %s to enum %d on %s"), *PropertyName.ToString(), static_cast<int32>(NewValue), *Target->GetName());
        }
        else if (FByteProperty* ByteProp = CastField<FByteProperty>(Property))
        {
            // Handle byte-backed enums (BP enums like EUDSColorMode)
            ByteProp->SetPropertyValue(ByteProp->ContainerPtrToValuePtr<void>(Target), static_cast<uint8>(NewValue));
            UE_LOG(LogTemp, Log, TEXT("Set %s to enum(byte) %d on %s"), *PropertyName.ToString(), static_cast<uint8>(NewValue), *Target->GetName());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Property '%s' is not an enum/byte!"), *PropertyName.ToString());
        }
    }


    //// Handle FString (like "Simplified Color" to enum)
    //else if constexpr (std::is_same_v<TValue, FString>)
    //{
    //    if (FEnumProperty* EnumProp = CastField<FEnumProperty>(Property))
    //    {
    //        const int64 Index = MapUDSColorModeStringToIndex(NewValue);  // A helper function to map strings to enum values
    //        void* Ptr = EnumProp->ContainerPtrToValuePtr<void>(Target);
    //        EnumProp->GetUnderlyingProperty()->SetIntPropertyValue(Ptr, Index);
    //        UE_LOG(LogTemp, Log, TEXT("Set %s to enum '%s' (idx %lld) on %s"),
    //            *PropertyName.ToString(), *NewValue, (long long)Index, *Target->GetName());
    //    }
    //}

    //// Handling for UDS_SkyMode Enum
    //else if constexpr (std::is_same_v<TValue, UDS_SkyMode>)  
    //{
    //    if (FEnumProperty* EnumProp = CastField<FEnumProperty>(Property))
    //    {
    //        EnumProp->SetPropertyValue(EnumProp->ContainerPtrToValuePtr<void>(Target), static_cast<int32>(NewValue));
    //        UE_LOG(LogTemp, Log, TEXT("Set %s to '%d' on %s"), *PropertyName.ToString(), static_cast<int32>(NewValue), *Target->GetName());
    //    }
    //    else
    //    {
    //        UE_LOG(LogTemp, Warning, TEXT("Property '%s' is not an Enum!"), *PropertyName.ToString());
    //    }
    //}

}

void AWeatherController::ApplyWindEffectOnMegaScanAssetsandWindsourceDirectionAssets(float windSpeed, float windDir)
{
    if (GlobalFoliageActor)
    {
        for (TFieldIterator<FProperty> PropIt(GlobalFoliageActor->GetClass()); PropIt; ++PropIt)
        {
            UE_LOG(LogTemp, Warning, TEXT("Property found: %s, CPPType: %s"),
                *PropIt->GetName(),
                *PropIt->GetCPPType());
        }

        static const FName WindStrengthVar = TEXT("Wind Strength"); // Must match exactly
        FProperty* WindStrengthProperty = GlobalFoliageActor->GetClass()->FindPropertyByName(WindStrengthVar);

        if (FDoubleProperty* DoubleProp = CastField<FDoubleProperty>(WindStrengthProperty))
        {
            DoubleProp->SetPropertyValue_InContainer(GlobalFoliageActor, static_cast<double>(windSpeed * 5));
            UE_LOG(LogTemp, Log, TEXT("WindStrength set successfully as double"));
        }

        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Could not find WindStrength float variable on MS Preset"));
        }

        //    static const FName WindDirectionVar = TEXT("Wind Dir"); // Must match exactly
        //    FProperty* WindDirectionProperty = GlobalFoliageActor->GetClass()->FindPropertyByName(WindDirectionVar);

            //if (FDoubleProperty* DoubleProp = CastField<FDoubleProperty>(WindDirectionProperty))
            //{
            //    DoubleProp->SetPropertyValue_InContainer(GlobalFoliageActor, static_cast<double>(windSpeed * 5));
            //    UE_LOG(LogTemp, Log, TEXT("Wind Direction set successfully as double"));
            //}

            //else
            //{
            //    UE_LOG(LogTemp, Warning, TEXT("Could not find Wind Direction float variable on v"));
            //}

    }
}

// In WeatherController.cpp
//void AWeatherController::ChangeSkyModeAtRuntime(UDS_SkyMode NewSkyMode)
//{
//    // Ensure the UltraDynamicSkyActor is valid before attempting to change its SkyMode
//    if (UltraDynamicSkyActor)
//    {
//        // Change the SkyMode property of the UltraDynamicSkyActor
//        UltraDynamicSkyActor->SkyMode = NewSkyMode;
//
//        // Optionally, you can log this change for debugging purposes
//        UE_LOG(LogTemp, Log, TEXT("Sky Mode changed to: %s"), *UEnum::GetValueAsString(NewSkyMode));
//    }
//    else
//    {
//        UE_LOG(LogTemp, Warning, TEXT("UltraDynamicSkyActor is not valid!"));
//    }
//}



void AWeatherController::ApplyWindEffectUsingWindDirectionalSource(float windSpeed, float windDir)
{
    if (WindDirectionalSourceActor && WindDirectionalSourceActor->GetComponent())
    {
        UWindDirectionalSourceComponent* WindComp = WindDirectionalSourceActor->GetComponent();
        WindComp->Strength = windSpeed;
        WindComp->Speed = windSpeed;


        // Convert degrees to a normalized direction vector (yaw rotation)
        float Radians = FMath::DegreesToRadians(windDir);
        FVector NewDirection = FVector(FMath::Cos(Radians), FMath::Sin(Radians), 0.0f).GetSafeNormal();

        FRotator NewRot = NewDirection.Rotation();
        WindDirectionalSourceActor->SetActorRotation(NewRot);

        UE_LOG(LogTemp, Log, TEXT("Wind updated via AWWindDirectionalSource — Speed: %.2f, Dir: %.2f (Yaw %.2f)"),
            windSpeed, windDir, NewRot.Yaw);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("WindDirectionalSourceActor is not set or missing its component."));
    }
}

void AWeatherController::ApplyUDSWeatherAsset(const FString& AssetPath)
{
    //StaticLoadObject, This function is loading our pre-defined assets from UDS
    UObject* AssetObj = StaticLoadObject(UObject::StaticClass(), nullptr, *AssetPath);
    if (!AssetObj)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load weather asset: %s"), *AssetPath);
        return;
    }

    if (!UltraDynamicWeatherActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("UltraDynamicWeatherActor not set."));
        return;
    }

    // Correct function name based on tooltip
    UFunction* Func = UltraDynamicWeatherActor->FindFunction(TEXT("Change Weather"));
    if (!Func)
    {
        UE_LOG(LogTemp, Warning, TEXT("Function 'ChangeWeather' not found on UltraDynamicWeatherActor."));
        return;
    }

    struct FChangeWeatherParams
    {
        UObject* Preset;
    };

    FChangeWeatherParams Params;
    Params.Preset = AssetObj;

    UltraDynamicWeatherActor->ProcessEvent(Func, &Params);

    UE_LOG(LogTemp, Log, TEXT("Called ChangeWeather with asset: %s"), *AssetPath);

    AVolumetricCloud* CloudActor = Cast<AVolumetricCloud>(
        UGameplayStatics::GetActorOfClass(GetWorld(), AVolumetricCloud::StaticClass())
    );

    if (CloudActor)
    {
        CloudActor->SetActorHiddenInGame(false);

        if (UVolumetricCloudComponent* CloudComp = CloudActor->FindComponentByClass<UVolumetricCloudComponent>())
        {
            CloudComp->SetVisibility(true);
        }

        UE_LOG(LogTemp, Log, TEXT("Re-enabled volumetric clouds after weather asset change."));
    }

}

void AWeatherController::HardCacheReset()
{

    UFunction* Func = UltraDynamicSkyActor->FindFunction(TEXT("Hard Reset Cache"));
    if (!Func)
    {
        UE_LOG(LogTemp, Warning, TEXT("Function 'Hard Reset Cache' not found."));
        return;
    }

}

//It sets the weather to none! No effect on sky properties
void AWeatherController::ResetToManualWeather()
{
    if (!UltraDynamicWeatherActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("UltraDynamicWeatherActor not set."));
        return;
    }

    UFunction* Func = UltraDynamicWeatherActor->FindFunction(TEXT("Change Weather"));
    if (!Func)
    {
        UE_LOG(LogTemp, Warning, TEXT("Function 'Change Weather' not found."));
        return;
    }

    struct FChangeWeatherParams
    {
        UObject* Preset = nullptr;
    };

    FChangeWeatherParams Params;
    Params.Preset = nullptr;  // This is key — tells UDS to go into Manual Mode

    UltraDynamicWeatherActor->ProcessEvent(Func, &Params);

    UE_LOG(LogTemp, Log, TEXT("Reset UDS weather system to manual mode."));
}

void AWeatherController::ResetSkySettingsToDefault()
{
    if (!UltraDynamicSkyActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("UltraDynamicSkyActor not set."));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Resetting UDS&UDW settings"));

    SetEnvironmentProperty(ESkyProperties::TimeofDay, 960.0f);
    // Reset all sky-related properties to their default values
    SetEnvironmentProperty(ESkyProperties::RayleighColor, FLinearColor(0.168627f, 0.407843f, 1.0f, 1.0f));  // Default sky color
    SetEnvironmentProperty(ESkyProperties::CloudWispsOpacityClear, 0.0f);  // No cloud wisps for clear sky
    SetEnvironmentProperty(EWeatherProperties::CloudCoverage, 3.0f);
    SetEnvironmentProperty(ESkyProperties::CloudWispsOpacityCloudy, 0.0f);
    //Reset all sky-related properties to their default values
    SetEnvironmentProperty(ESkyProperties::RayleighColor, FLinearColor(0.168627f, 0.407843f, 1.0f, 1.0f));  // Default sky color
    SetEnvironmentProperty(ESkyProperties::VolumetricCloudScale, 0.0f);  // No volumetric clouds
    SetEnvironmentProperty(ESkyProperties::LayerHeightScale, 0.0f);  // Default cloud layer scale
    SetEnvironmentProperty(ESkyProperties::BottomAltitude, 0.0f);  // Default cloud height

    // Reset Skybox settings
    SetEnvironmentProperty(ESkyProperties::BaseSkyColor, FLinearColor(0.168627f, 0.407843f, 1.0f, 1.0f));  // Default sky color
    SetEnvironmentProperty(ESkyProperties::EUDSColorMode, EUDSColorMode::SkyAtmosphere);  // Default sky mode

    // Reset fog settings
    SetEnvironmentProperty(ESkyProperties::BaseFogDensity, 0.0f);  // No fog
    SetEnvironmentProperty(ESkyProperties::BaseHeightFogFalloff, 0.0f);  // Default fog falloff

    // Reset weather settings
    SetEnvironmentProperty(EWeatherProperties::Rain, 0.0f);  // No rain
    SetEnvironmentProperty(EWeatherProperties::Snow, 0.0f);  // No snow
    SetEnvironmentProperty(EWeatherProperties::ThunderLightning, 0.0f);  // No lightning
    SetEnvironmentProperty(EWeatherProperties::WindIntensity, 0.0f);  // No wind
    SetEnvironmentProperty(EWeatherProperties::Fog, 0.0f);  // No fog
    SetEnvironmentProperty(EWeatherProperties::Dust, 0.0f);  // No dust
}

//void AWeatherController::ChangeColorModeToSimplified()
//{
//    if (UltraDynamicSkyActor)  // Assuming UltraDynamicSkyActor is a valid reference
//    {
//        // Assuming that 'SimplifiedColor' is a valid value in the UDS_ColorMode enum
//        UDS Color Mode NewColorMode = UDS_ColorMode::SimplifiedColor; // Replace with actual enum value
//
//        // Set the Color Mode property directly on UltraDynamicSkyActor
//        UltraDynamicSkyActor->ColorMode = NewColorMode;
//
//        // Log the change for confirmation
//        UE_LOG(LogTemp, Log, TEXT("Color Mode changed to Simplified Color."));
//    }
//    else
//    {
//        UE_LOG(LogTemp, Warning, TEXT("UltraDynamicSkyActor is not valid."));
//    }
//}

//void AWeatherController::ChangeColorModeToSimplified()
//{
//    if (UltraDynamicSkyActor)
//    {
//        // Set the ColorMode to SimplifiedColor (enum value)
//        UltraDynamicSkyActor->ColorMode = EUDSColorMode::SimplifiedColor;
//
//        // Optionally log the change for debugging
//        UE_LOG(LogTemp, Log, TEXT("Color Mode changed to Simplified Color."));
//    }
//}

//static int64 MapUDSColorModeStringToIndex(const FString& S)
//{
//    if (S.Equals(TEXT("Sky Atmosphere"), ESearchCase::IgnoreCase)) return 0;
//    if (S.Equals(TEXT("Simplified Color"), ESearchCase::IgnoreCase)) return 1;
//    // Add any additional mappings here if needed
//    return 0;  // Default to Sky Atmosphere
//}

// Toggle the ColorMode for the SkyBox preset specifically
//void AWeatherController::ToggleSkyBoxColorMode(FWeatherProperties& WeatherProperties)
//{
//    // Toggle between SkyAtmosphere and SimplifiedColor
//    if (WeatherProperties.ColorMode == EUDSColorMode::SkyAtmosphere)
//    {
//        WeatherProperties.ColorMode = EUDSColorMode::SimplifiedColor;
//    }
//    else
//    {
//        WeatherProperties.ColorMode = EUDSColorMode::SkyAtmosphere;
//    }
//
//    // Optionally log the change for debugging
//    UE_LOG(LogTemp, Log, TEXT("Toggled ColorMode to: %s"), *UEnum::GetValueAsString(WeatherProperties.ColorMode));
//}


void AWeatherController::CallCompleteClearSkiesondefault()
{

    const FWeatherPreset CustomPreset = SWeatherPresetsDefined::GetPresetByName("CompleteClearSkies");

    if (CustomPreset.Name == "CompleteClearSkies")
    {

        UE_LOG(LogTemp, Log, TEXT("Preset 'CompleteClearSkies' found."));
    }
    else
    {
    
        UE_LOG(LogTemp, Log, TEXT("Preset 'CompleteClearSkies' not found!"));
    
    }


    if (CustomPreset.Name != "Default")
    {
        ResetToManualWeather();
        ResetSkySettingsToDefault();
        //EditableProperties = CustomPreset.Properties;
        updateWeather(CustomPreset.Properties);
    }


}

