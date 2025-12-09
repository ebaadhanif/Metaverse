#pragma once
#include "CoreMinimal.h"
#include "AssimpRuntime3DModelsImporter.h"
#include "UObject/NoExportTypes.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EntityBase.h"
#include "Model3DAsset.generated.h"

USTRUCT()
struct FModelInfo
{
    GENERATED_BODY()


    FModelInfo()
        : Title(""), Description(""), Manufacturer(""), Type(""), Variation(""),
        RoleType(""), CreatedBy(""), NormalModel(""), Sound(""), Texture(""),
        VisualDamage(0), HealthPoints(0), DamageModel(""), DestroyModel(""),
        BattlespaceModel(""), InitialOrientation(""), DISEntityType(""), CustomDamagedTexture(true),
        CustomDestroyedTexture(true), ModelHeight(1), ModelLength(1),ModelWidth(1)
    {
    }


    UPROPERTY() FString Title;
    UPROPERTY() FString Description;
    UPROPERTY() FString Manufacturer;
    UPROPERTY() FString Type;
    UPROPERTY() FString Variation;
    UPROPERTY() FString RoleType;
    UPROPERTY() FString CreatedBy;
    UPROPERTY() FString NormalModel;
    UPROPERTY() FString Sound;
    UPROPERTY() FString Texture;
    UPROPERTY() int32 VisualDamage;
    UPROPERTY() int32 HealthPoints;
    UPROPERTY() FString DamageModel;
    UPROPERTY() FString DestroyModel;
    UPROPERTY() FString BattlespaceModel;
    UPROPERTY() FString InitialOrientation;
    UPROPERTY() FString DISEntityType;
    UPROPERTY() FString IRTextureName;
    UPROPERTY() float ModelLength;
    UPROPERTY() float ModelWidth;
    UPROPERTY() float ModelHeight;
    UPROPERTY() bool CustomDamagedTexture;
    UPROPERTY() bool CustomDestroyedTexture;
};

USTRUCT()
struct FTextureEntry
{
    GENERATED_BODY()



    FTextureEntry() : Id(0), CountryId(0), Name("") {}

    UPROPERTY() int32 Id;
    UPROPERTY() int32 CountryId;
    UPROPERTY() FString Name;
};

USTRUCT()
struct FLODEntry
{
    GENERATED_BODY()

    FLODEntry() : Id(0), Name(""), Value(0.0f) {}


    UPROPERTY() int32 Id;
    UPROPERTY() FString Name;
    UPROPERTY() float Value;
};

USTRUCT()
struct FModelLightConfig
{
    GENERATED_BODY()

    FModelLightConfig() : Id(0), RefNode(""), VFX("") {}


    UPROPERTY() int32 Id;
    UPROPERTY() FString RefNode;
    UPROPERTY() FString VFX;
};

USTRUCT()
struct FModelEffectConfig
{
    GENERATED_BODY()

    FModelEffectConfig() : Type(""), RefNode(""), VFX("") {}


    UPROPERTY() FString Type;
    UPROPERTY() FString Event;
    UPROPERTY() FString Sound;
    UPROPERTY() FString RefNode;
    UPROPERTY() FString VFX;
};

USTRUCT()
struct FSupportPoint
{
    GENERATED_BODY()

    FSupportPoint() : Id(0), RefNode("") {}


    UPROPERTY() int32 Id;
    UPROPERTY() FString RefNode;
};

USTRUCT()
struct FArticulatedEffect
{
    GENERATED_BODY()


    FArticulatedEffect() : Event(""), VFX(""), Sound(""), RefNode("") {}
    UPROPERTY() FString Event;
    UPROPERTY() FString VFX;
    UPROPERTY() FString Sound;
    UPROPERTY() FString RefNode;
};

USTRUCT()
struct FArticulatedPart
{
    GENERATED_BODY()

    FArticulatedPart()
        : Id(0), Category(""), State(""), Type(""), RefNodes(""), AnimationSeq(""), Effects()
    {
    }

    UPROPERTY() int32 Id;
    UPROPERTY() FString Category;
    UPROPERTY() FString State; // Optional
    UPROPERTY() FString Type;  // Optional
    UPROPERTY() FString RefNodes;
    UPROPERTY() FString AnimationSeq;
    UPROPERTY() TArray<FArticulatedEffect> Effects;
};

USTRUCT()
struct FAttachment
{
    GENERATED_BODY()

    FAttachment() : Id(0), RefNode(""), PartNo(0), StationNo(0), Orientation("") {}


    UPROPERTY() int32 Id;
    UPROPERTY() FString RefNode;
    UPROPERTY() int32 PartNo;
    UPROPERTY() int32 StationNo;
    UPROPERTY() FString Orientation;
};

USTRUCT()
struct FCameraConfig
{
    GENERATED_BODY()


    FCameraConfig()
        : Id(0), Title(""), Description(""), Origin(""), AllowZoom(false),
        InitialZoom(0.0f), ZoomFactor(0.0f), InitialXyz(""),
        InitialOrientation(""), ShowLensFlare(false), Category(""), CameraType("")
    {
    }


    UPROPERTY() int32 Id;
    UPROPERTY() FString Title;
    UPROPERTY() FString Description;
    UPROPERTY() FString Origin;
    UPROPERTY() bool AllowZoom;
    UPROPERTY() float InitialZoom;
    UPROPERTY() float ZoomFactor;
    UPROPERTY() FString InitialXyz;
    UPROPERTY() FString InitialOrientation;
    UPROPERTY() bool ShowLensFlare;
    UPROPERTY() FString Category;
    UPROPERTY() FString CameraType;
};

USTRUCT()
struct FModelConfiguration
{
    GENERATED_BODY()


    FModelConfiguration()
        : ModelInfo()
        , Textures()
        , LODs()
        , Lights()
        , Effects()
        , SupportPoints()
        , ArticulatedParts()
        , Attachments()
        , Cameras()
    {
    }

    UPROPERTY() FModelInfo ModelInfo;
    UPROPERTY() TArray<FTextureEntry> Textures;
    UPROPERTY() TArray<FLODEntry> LODs;
    UPROPERTY() TArray<FModelLightConfig> Lights;
    UPROPERTY() TArray<FModelEffectConfig> Effects;
    UPROPERTY() TArray<FSupportPoint> SupportPoints;
    UPROPERTY() TArray<FArticulatedPart> ArticulatedParts;
    UPROPERTY() TArray<FAttachment> Attachments;
    UPROPERTY() TArray<FCameraConfig> Cameras;
};

UCLASS()
class METAVERSE_API UModel3DAsset : public UObject
{
    GENERATED_BODY()
public:
    UPROPERTY()
    UAssimpRuntime3DModelsImporter* Model;
    virtual void Import3DAsset() PURE_VIRTUAL(UModel3DAsset::Import3DAsset, );
    virtual void Spawn3DAsset(UWorld* World, const FTransform& modelTransform) PURE_VIRTUAL(UModel3DAsset::Spawn3DAsset, );
    virtual void GetConfigRawDataFromFile(const FString& XmlFilePath) PURE_VIRTUAL(UModel3DAsset::GetConfigRawDataFromFile, );
    virtual void AttachComponentsToRawDataInModel(UWorld* World,AEntityBase* base) PURE_VIRTUAL(UModel3DAsset::AttachComponentsToRawDataInModel, );
    UTexture2D* LoadIRTexture();

    FString ExtractModelNameFromPath(const FString& Path);
    AActor* _spawnedActor;
    FModelConfiguration _modelConfig;
    FString FolderPath;
    TArray<AActor*> LODs;
   // AActor* LOD0_Parent;
   // AActor* LOD1_Parent;
    AActor* DamagedActors_Parent;
    AActor* DestroyedActors_Parent;
    AActor* Battlespace_Actor;
    AActor* RootModelActor;


};
