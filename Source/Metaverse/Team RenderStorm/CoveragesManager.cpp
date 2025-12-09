// Fill out your copyright...

#include "CoveragesManager.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "../Team Visioneers/Menus/UIManager.h"

DEFINE_LOG_CATEGORY(LogCoveragesManager);

const FName UCoveragesManager::NAME_Color = FName("Color");
const FName UCoveragesManager::NAME_Opacity = FName("Opacity");

UCoveragesManager* UCoveragesManager::Instance = nullptr;

UCoveragesManager* UCoveragesManager::GetInstance()
{
    if (!Instance)
    {
        Instance = NewObject<UCoveragesManager>();
        Instance->AddToRoot();

        Instance->SSS.entiyKind = 1;
        Instance->SSS.domain = 2;
        Instance->SSS.country = static_cast<uint16>(165);
        Instance->SSS.category = 8;
        Instance->SSS.subcategory = 1;
        Instance->SSS.specific = 0;
        Instance->SSS.extra = 0;

    }
    return Instance;
}
int32 UCoveragesManager::CalcDomeSortPriority(AEntityBase* Entity) {
    const int32 range = FMath::Clamp(static_cast<int32>(Entity->GetRadarRange()), 0, 5000);
    UE_LOG(LogCoveragesManager, Error, TEXT("CalcDomeSortPriority: %d "), range);
    return 5000 - range;
}


void UCoveragesManager::SetWorld(UWorld* InWorld)
{
    World = InWorld;
    ACesiumGeoreference* Goereference = ACesiumGeoreference::GetDefaultGeoreference(Instance->World);
    ACesium3DTileset* Tileset = Cast< ACesium3DTileset>(UGameplayStatics::GetActorOfClass(Instance->World, ACesium3DTileset::StaticClass()));
    IShape::SetTileset(Tileset);
    IShape::SetGeoreference(Goereference);
    IShape::SetWorld(Instance->World);
}

void UCoveragesManager::Shutdown()
{
    if (Instance)
    {
        //Instance->ClearAll();
        Instance->RemoveFromRoot();
        Instance = nullptr;
    }
}

void UCoveragesManager::AddEntityToCoveragesList(AEntityBase* Entity)
{
    if (!IsValid(Entity))
    {
        UE_LOG(LogCoveragesManager, Warning, TEXT("AddActorToList: Attempted to add a null entity."));
        return;
    }
    ActorList.AddUnique(Entity);
    AttachCoverageMesh(Entity);
   // if (Entity->GetRemoteEntityType() == ERemoteEntityType::GENERAL_VEHICLE) Entity->CoverageMesh->SetCullDistance(5000000.0f);
    if (Entity->GetRemoteEntityType() == ERemoteEntityType::RADAR || Entity->GetRemoteEntityType() == ERemoteEntityType::ARMORED_VEHICLE || Entity->GetRemoteEntityType() == ERemoteEntityType::SHIPS || Entity->GetRemoteEntityType() == ERemoteEntityType::GENERAL_VEHICLE) {
        AttachCoverageFootPrint(Entity);
        for (AEntityBase* pEntityBase : EntityManager::GetEntityManagerInstance()->getRemoteEntitiesList()) pEntityBase->SetActorEnableCollision(false);
      
        SpawnProceduralRingsOnDome(Entity, Entity->CoverageMesh, 20000.0F, 328, 1000.0F, 1000.0F, 2.f,
        	"CoverageRingProc",
        	false, true);
        for (AEntityBase* pEntityBase : EntityManager::GetEntityManagerInstance()->getRemoteEntitiesList()) pEntityBase->SetActorEnableCollision(true);
        if (Entity->CoverageMesh) {
            Entity->CoverageMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        }
    }
}

void UCoveragesManager::AttachCoverageMesh(AEntityBase* Entity)
{
    if (!IsValid(Entity))
    {
        UE_LOG(LogCoveragesManager, Warning, TEXT("AttachCoverageMesh: Invalid entity."));
        return;
    }

    const ECoverage Kind = GetCoverageKindForEntity(Entity);
    EnsureAssetsCached(Kind);

    UStaticMesh* Mesh = CachedMeshes.FindRef(Kind);
    if (!Mesh)
    {
        UE_LOG(LogCoveragesManager, Warning, TEXT("AttachCoverageMesh: Mesh not found for coverage kind."));
        return;
    }

    // Create the coverage component if needed
    if (!Entity->CoverageMesh)
    {
        Entity->CoverageMesh = NewObject<UStaticMeshComponent>(Entity);
        if (!Entity->CoverageMesh)
        {
            UE_LOG(LogCoveragesManager, Warning, TEXT("AttachCoverageMesh: Failed to create UStaticMeshComponent."));
            return;
        }
       // Entity->CoverageMesh->SetupAttachment(Entity->GetRootComponent());
    }

    Entity->CoverageMesh->SetStaticMesh(Mesh);
    Entity->CoverageMesh->SetMobility(EComponentMobility::Movable);
    Entity->CoverageMesh->RegisterComponent();
    Entity->CoverageMesh->ComponentTags.Add("CoverageDome");
    Entity->CoverageMesh->SetTranslucentSortPriority(CalcDomeSortPriority(Entity));

    if (Entity->GetRemoteEntityType() == ERemoteEntityType::FIXEDWING_AIRCRAFT) 
        Entity->CoverageMesh->SetVisibility(UIManager::GetInstance()->ButtonSates.bIsAircraftCoverage);
    else if (Entity->GetRemoteEntityType() == ERemoteEntityType::RADAR || Entity->GetRemoteEntityType() == ERemoteEntityType::ARMORED_VEHICLE || Entity->GetRemoteEntityType() == ERemoteEntityType::SHIPS || Entity->GetRemoteEntityType() == ERemoteEntityType::GENERAL_VEHICLE)
        Entity->CoverageMesh->SetVisibility(UIManager::GetInstance()->ButtonSates.bIsGroundCoverages);



    // Apply material instances (color/opacity set by force type)
    ApplyCustomMaterial(Entity);

    const float CoverageNM = Entity->GetRadarRange();
    UE_LOG(LogCoveragesManager, Verbose, TEXT("Coverage for Entity id:%d is: %f NM"),
        Entity->GetEntityId().EntityID, CoverageNM);

    //const float ScaleCm = CoverageNM * CM_PER_NM;
    //const FVector Scale(ScaleCm, ScaleCm, ScaleCm);

    FVector Scale;
    if (Entity->GetRemoteEntityType() == ERemoteEntityType::FIXEDWING_AIRCRAFT) {
        Scale = GetDefaultScale(Entity);
    }
    else {
         Scale = GetCoverageScale(Entity);
    }
    FVector RelativeScale = Scale / Entity->GetActorScale3D();
    Entity->CoverageMesh->SetRelativeScale3D(RelativeScale);
    Entity->CoverageMesh->SetRelativeLocation(FVector::Zero());

    // slight offset above ground
    //const FVector Offset(0.f, 0.f, -500.f);
   // FRotator rotation = Entity->GetWorldOrientation()+ FRotator(0.0f, 90.0f, 0.0f);
   // FRotator rotation = Entity->GetWorldOrientation() ;
   // Entity->CoverageMesh->SetWorldRotation(rotation);
  //  Entity->CoverageMesh->SetRelativeLocation(Entity->CoverageMesh->GetRelativeLocation() + Offset);
   // Entity->CoverageMesh->SetWorldLocation(Entity->GetWorldLocation());
    Entity->CoverageMesh->AttachToComponent(Entity->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true));
}

FVector UCoveragesManager::GetDefaultScale(AEntityBase* Entity) {
    FVector OriginalScale;
    float defaultRange;
    float SCALEFACTOR_X, SCALEFACTOR_Y, SCALEFACTOR_Z;
    if (Entity->GetEntityType() == SSS) {
        OriginalScale = FVector(889, 958, 121);
        defaultRange = OriginalScale.Y;
        SCALEFACTOR_Y = (5* CM_PER_NM) / defaultRange;
        SCALEFACTOR_X = SCALEFACTOR_Y * (OriginalScale.X / OriginalScale.Y);
        SCALEFACTOR_Z = SCALEFACTOR_Y * (OriginalScale.Z / OriginalScale.Y);
        return FVector(SCALEFACTOR_X, SCALEFACTOR_Y, SCALEFACTOR_Z);
    }
    OriginalScale = FVector(544, 987, 548);
    defaultRange = OriginalScale.X;
    SCALEFACTOR_X = (5 * CM_PER_NM) / defaultRange;
    SCALEFACTOR_Y = SCALEFACTOR_X * (OriginalScale.Y / OriginalScale.X);
    SCALEFACTOR_Z = SCALEFACTOR_X * (OriginalScale.Z / OriginalScale.X);
    return FVector(SCALEFACTOR_X, SCALEFACTOR_X, SCALEFACTOR_X);
}

void UCoveragesManager::ToggleAircraftsDefaultAndOriginal(bool isTrueScale) {
    for (AEntityBase* Entity : ActorList) {
        FVector Scale;
        if (Entity->GetRemoteEntityType() == ERemoteEntityType::FIXEDWING_AIRCRAFT) {
            Scale = isTrueScale? GetCoverageScale(Entity):GetDefaultScale(Entity) ;
            FVector RelativeScale = Scale / Entity->GetActorScale3D();
            Entity->CoverageMesh->SetRelativeScale3D(RelativeScale);
        }
    }
}

FVector UCoveragesManager::GetCoverageScale(AEntityBase* Entity) {

    if (Entity->GetRemoteEntityType() == ERemoteEntityType::RADAR || Entity->GetRemoteEntityType() == ERemoteEntityType::GENERAL_VEHICLE || Entity->GetRemoteEntityType() == ERemoteEntityType::ARMORED_VEHICLE || Entity->GetRemoteEntityType() == ERemoteEntityType::SHIPS) {
        const float Scale = Entity->GetRadarRange() * CM_PER_NM;
        return FVector(Scale, Scale, Scale);
    }
    else if (Entity->GetRemoteEntityType() == ERemoteEntityType::FIXEDWING_AIRCRAFT) {
        FVector OriginalScale;
        float defaultRange;
        float SCALEFACTOR_X, SCALEFACTOR_Y, SCALEFACTOR_Z;
        if (Entity->GetEntityType() == SSS) {
            OriginalScale = FVector(889, 958, 121);
            defaultRange = OriginalScale.Y;
            SCALEFACTOR_Y = (Entity->GetRadarRange() * CM_PER_NM) / defaultRange;
            SCALEFACTOR_X = SCALEFACTOR_Y * (OriginalScale.X / OriginalScale.Y);
            SCALEFACTOR_Z = SCALEFACTOR_Y * (OriginalScale.Z / OriginalScale.Y);
            return FVector(SCALEFACTOR_X, SCALEFACTOR_Y, SCALEFACTOR_Z);
        }
        OriginalScale = FVector(545, 987, 548);
        defaultRange = OriginalScale.X;
        SCALEFACTOR_X = (Entity->GetRadarRange() * CM_PER_NM) / defaultRange;
        SCALEFACTOR_Y = SCALEFACTOR_X * (OriginalScale.Y / OriginalScale.X);
        SCALEFACTOR_Z = SCALEFACTOR_X * (OriginalScale.Z / OriginalScale.X);
        return FVector(SCALEFACTOR_X, SCALEFACTOR_Y, SCALEFACTOR_Z);
    }
    else {
        return FVector(0, 0, 0);
    }
}

void UCoveragesManager::AttachCoverageFootPrint(AEntityBase* Entity)
{
    if (!IsValid(Entity))
    {
        UE_LOG(LogCoveragesManager, Warning, TEXT("AttachCoverageFootPrint: Invalid entity."));
        return;
    }
    const float Radius = static_cast<float>(Entity->GetRadarRange()) / 2.0f;

    const FVector GeodaticPosition = Entity->GetGeodeticLocation();
    const FVector WorldPosition = Entity->GetWorldLocation();
    //const FVector LatLong(WorldLoc.Y, WorldLoc.X, WorldLoc.Z+DEFAULT_FOOTPRINT_ALT_M);
   // const FVector LatLong(GeodaticPosition.Y, GeodaticPosition.X, M_PER_NM * (Radius/2.0f));
    //const FVector LatLong(GeodaticPosition.Y, GeodaticPosition.X, GeodaticPosition.Z + DEFAULT_FOOTPRINT_ALT_M);
    const FVector LatLong(GeodaticPosition.Y, GeodaticPosition.X, ((Radius/5.0f) * M_PER_NM)+ GeodaticPosition.Z);
    const FVector WorldLoc(WorldPosition.X, WorldPosition.Y, WorldPosition.Z);

    Entity->FootPrintConverage = MakeShared<FCircle>(WorldLoc, LatLong, Radius);
   // Entity->FootPrintConverage = new FCircle(WorldLoc, LatLong, Radius);
    if (Entity->FootPrintConverage)
    {
        const FCoverageColors Colors = GetEntityTypeColor(Entity->GetForceType());
        Entity->FootPrintConverage->SetLineColor(Colors.ThickRing);
        Entity->FootPrintConverage->SetLineWidth(FOOTPRINT_LINE_WIDTH);
        Entity->FootPrintConverage->SetLineHeight(FOOTPRINT_LINE_HEIGHT);
        bool check = UIManager::GetInstance()->ButtonSates.bIsGroundCoveragesFootprints;
        Entity->FootPrintConverage->DrawCoverageFootPrint(World, LatLong.Z);
        ToggleFootPrintsVisibilityForEntity(Entity, UIManager::GetInstance()->ButtonSates.bIsGroundCoveragesFootprints);
      //  Entity->FootPrintConverage->Draw(World);
    }
}

void UCoveragesManager::ToggleVisibility(bool bVisible)
{
    PruneNullActors();

    for (AEntityBase* Entity : ActorList)
    {
        if (IsValid(Entity) && Entity->CoverageMesh)
        {
            Entity->CoverageMesh->SetVisibility(bVisible, true);
            Entity->CoverageMesh->SetHiddenInGame(!bVisible);
        }
    }
}

void UCoveragesManager::ToggleFootPrintsVisibility(bool bVisible)
{
    PruneNullActors();

    for (AEntityBase* Entity : ActorList)
    {
        if (IsValid(Entity) && Entity->FootPrintConverage.IsValid())
        {
            Entity->FootPrintConverage->SetVisibility(bVisible);
            Entity->FootPrintConverage->SetProjectionVisibility(bVisible);

        }
    }
}

void UCoveragesManager::ToggleVisibilityOfCoveragesByRemoteEntityType(bool bVisible, ERemoteEntityType RemoteEntityType) {
    for (AEntityBase* Entity : ActorList)
    {
        if (IsValid(Entity) && Entity->CoverageMesh && Entity->GetRemoteEntityType() == RemoteEntityType)
        {
            Entity->CoverageMesh->SetVisibility(bVisible, true);
            Entity->CoverageMesh->SetHiddenInGame(!bVisible);
        }
    }
}

void UCoveragesManager::ToggleFootPrintsVisibilityForEntity(AEntityBase* Entity, bool bVisible)
{
    if (IsValid(Entity) && Entity->FootPrintConverage.IsValid())
    {
        Entity->FootPrintConverage->SetVisibility(bVisible);
    }
}

void UCoveragesManager::ToggleHorizontalRings(bool bVisible) {
   
    for (AEntityBase* Entity : ActorList) {
        if (Entity->DomeRings) {
            Entity->DomeRings->SetVisibility(bVisible);
            Entity->DomeRings->SetHiddenInGame(!bVisible);
        }
    }
}

TArray<AEntityBase*> UCoveragesManager::GetEntitiesCoveragesList()
{
    PruneNullActors();
    return ActorList;
}

int32 UCoveragesManager::GetNumberofCoverageEntities()
{
    PruneNullActors();
    return ActorList.Num();
}

void UCoveragesManager::ApplyCustomMaterial(AEntityBase* Entity)
{
    if (!IsValid(Entity) || !Entity->CoverageMesh)
    {
        UE_LOG(LogCoveragesManager, Warning, TEXT("ApplyCustomMaterial: CoverageMesh is null."));
        return;
    }

    const ECoverage Kind = GetCoverageKindForEntity(Entity);
    EnsureAssetsCached(Kind);
    const FCoverageMaterialPaths& Paths = GetMaterialPaths(Kind);

    const FCoverageColors Colors = GetEntityTypeColor(Entity->GetForceType());

    auto ApplySlot = [&](int32 SlotIdx, const FString& Path, FVector4f ColorVec)
        {
            if (Path.IsEmpty())
                return;

            if (UMaterialInterface* Mat = LoadMaterial(Path))
            {
                UMaterialInstanceDynamic* MID = UMaterialInstanceDynamic::Create(Mat, Entity);
                if (MID)
                {
                    Entity->CoverageMesh->SetMaterial(SlotIdx, MID);
                    MID->SetVectorParameterValue(NAME_Color, ColorVec);
                    MID->SetScalarParameterValue(NAME_Opacity, ColorVec.W);
                }

                // Cache handles back to the entity if you still use them elsewhere
                switch (SlotIdx)
                {
                case 0:
                    Entity->CoverageRingThinMaterial = Mat;
                    Entity->DynamicCoverageRingThinMaterial = MID;
                    break;
                case 1:
                    Entity->CoverageDomeMaterial = Mat;
                    Entity->DynamicCoverageDomeMaterial = MID;
                    break;
                case 2:
                    Entity->CoverageRingThickMaterial = Mat;
                    Entity->DynamicCoverageRingThickMaterial = MID;
                    break;
                default:
                    break;
                }
            }
        };

    ApplySlot(0, Paths.ThinPath, Colors.ThinRing);
    ApplySlot(1, Paths.DomePath, Colors.Dome);
    if (Paths.HasThick())
    {
        ApplySlot(2, Paths.ThickPath, Colors.ThickRing);
    }
}

FCoverageColors UCoveragesManager::GetEntityTypeColor(EForceType Type) const
{
    FCoverageColors Color;

    switch (Type)
    {
    case EForceType::NEUTRAL:
        Color.ThinRing = FVector4f(84, 209, 124, 81) / 255.0f;
        Color.ThickRing = FVector4f(84, 209, 124, 81) / 255.0f;
        Color.Dome = FVector4f(84, 209, 124, 150) / 255.0f;
        break;

    case EForceType::OTHERS:
        Color.ThinRing = FVector4f(232, 190, 60, 81) / 255.0f;
        Color.ThickRing = FVector4f(232, 190, 60, 81) / 255.0f;
        Color.Dome = FVector4f(232, 190, 60, 255) / 255.0f;
        break;

    case EForceType::OPPOSING:
        Color.ThinRing = FVector4f(255, 0, 0, 80) / 255.0f;
        Color.ThickRing = FVector4f(255, 0, 0, 80) / 255.0f;
        Color.Dome = FVector4f(245, 158, 158, 90) / 255.0f;
        break;

    case EForceType::FRIENDLY:
    default:
        Color.ThinRing = FVector4f(7, 9, 212, 90) / 255.0f;
        Color.ThickRing = FVector4f(125, 129, 174, 255) / 255.0f;
        Color.Dome = FVector4f(183, 188, 255, 70) / 255.0f;
        break;
    }

    return Color;
}

ECoverage UCoveragesManager::GetCoverageKindForEntity(AEntityBase* Entity)
{
    if (!IsValid(Entity))
        return ECoverage::Radar; // safe default

    // These calls require a non-const entity because the getters are non-const
    if (Entity->GetEntityType() == SSS)
    {
        return ECoverage::SSS;
    }

    if (Entity->GetRemoteEntityType() == ERemoteEntityType::FIXEDWING_AIRCRAFT)
    {
        return ECoverage::FighterAircraft;
    }

    return ECoverage::Radar;
}

// Material & Mesh path tables (centralized)
static const TMap<ECoverage, FCoverageMaterialPaths> GMaterialPaths = {
    {
        ECoverage::Radar,
        { TEXT("Material'/Game/MyModels/CoverageModels/Radar/80percent.80percent'"),
          TEXT("Material'/Game/MyModels/CoverageModels/Radar/50Percent.50Percent'"),
          TEXT("Material'/Game/MyModels/CoverageModels/Radar/Gradiant80to50.Gradiant80to50'") }
    },
    {
        ECoverage::FighterAircraft,
        { TEXT("Material'/Game/MyModels/CoverageModels/Aircraft/Material_51.Material_51'"),
          TEXT("Material'/Game/MyModels/CoverageModels/Aircraft/50Percent.50Percent'"),
          TEXT("") }
    },
    {
        ECoverage::SSS,
        { TEXT("Material'/Game/MyModels/CoverageModels/SSS/80percent.80percent'"),
          TEXT("Material'/Game/MyModels/CoverageModels/SSS/50Percent.50Percent'"),
          TEXT("") }
    }
};

static const TMap<ECoverage, FString> GMeshPaths = {
    { ECoverage::Radar,    TEXT("StaticMesh'/Game/MyModels/CoverageModels/Radar/RadarCoverage10.RadarCoverage10'") },
    { ECoverage::FighterAircraft, TEXT("StaticMesh'/Game/MyModels/CoverageModels/Aircraft/AircraftRadarCoverage.AircraftRadarCoverage'") },
    { ECoverage::SSS,      TEXT("StaticMesh'/Game/MyModels/CoverageModels/SSS/SSS_RadarCoverageV1.SSS_RadarCoverageV1'") }
};


const FCoverageMaterialPaths& UCoveragesManager::GetMaterialPaths(ECoverage Kind) const
{
    const FCoverageMaterialPaths* Paths = GMaterialPaths.Find(Kind);
    check(Paths); // data table must be valid
    return *Paths;
}

const FString& UCoveragesManager::GetMeshPath(ECoverage Kind) const
{
    const FString* Path = GMeshPaths.Find(Kind);
    check(Path);
    return *Path;
}

UMaterialInterface* UCoveragesManager::LoadMaterial(const FString& Path)
{
    if (Path.IsEmpty())
    {
        return nullptr;
    }

    if (UMaterialInterface** Found = CachedMaterials.Find(Path))
    {
        return *Found;
    }

    if (UMaterialInterface* Mat = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, *Path)))
    {
        CachedMaterials.Add(Path, Mat);
        return Mat;
    }

    UE_LOG(LogCoveragesManager, Warning, TEXT("LoadMaterial: Failed to load material at %s"), *Path);
    return nullptr;
}

UStaticMesh* UCoveragesManager::LoadCoverageMesh(ECoverage Kind)
{
    if (UStaticMesh** Cached = CachedMeshes.Find(Kind))
    {
        return *Cached;
    }

    const FString& Path = GetMeshPath(Kind);
    UStaticMesh* Mesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *Path));
    if (!Mesh)
    {
        UE_LOG(LogCoveragesManager, Warning, TEXT("LoadCoverageMesh: Failed to load mesh at %s"), *Path);
        return nullptr;
    }

    CachedMeshes.Add(Kind, Mesh);
    return Mesh;
}

void UCoveragesManager::EnsureAssetsCached(ECoverage Kind)
{
    // Mesh
    LoadCoverageMesh(Kind);

    // Materials
    const FCoverageMaterialPaths& Paths = GetMaterialPaths(Kind);
    LoadMaterial(Paths.ThinPath);
    LoadMaterial(Paths.DomePath);
    if (Paths.HasThick())
    {
        LoadMaterial(Paths.ThickPath);
    }
}

void UCoveragesManager::PruneNullActors()
{
    ActorList.RemoveAll([](AEntityBase* Ptr) { return !IsValid(Ptr); });
}

void UCoveragesManager::CleanupCoverageForEntity(AEntityBase* Entity)
{
    if (!IsValid(Entity))
        return;

    // Footprint
    if (Entity->FootPrintConverage.IsValid())
    {
        Entity->FootPrintConverage->Clear();
        // delete &Entity->FootPrintConverage;
        Entity->FootPrintConverage.Reset();
    }

    // Horizontal Rings
    if (Entity->DomeRings) {
        Entity->DomeRings->DestroyComponent();
        Entity->DomeRings = nullptr;
    }

    // Coverage mesh component
    if (Entity->CoverageMesh)
    {
        Entity->CoverageMesh->DestroyComponent();
        Entity->CoverageMesh = nullptr;
    }

    // Clear dynamic material refs (avoid dangling pointers on the entity)
    //Entity->CoverageRingThinMaterial = nullptr;
    //Entity->CoverageRingThickMaterial = nullptr;
    //Entity->CoverageDomeMaterial = nullptr;

    //Entity->DynamicCoverageRingThinMaterial = nullptr;
    //Entity->DynamicCoverageRingThickMaterial = nullptr;
    //Entity->DynamicCoverageDomeMaterial = nullptr;

    Entity->Destroy();


}

bool UCoveragesManager::RemoveEntity(AEntityBase* Entity)
{
    if (!IsValid(Entity))
    {
        UE_LOG(LogCoveragesManager, Warning, TEXT("RemoveEntity: Invalid entity"));
        return false;
    }
    // Destroy visual artifacts (safe to call even if not in our list)
    CleanupCoverageForEntity(Entity);

    // Remove from our list first to avoid re-entrancy surprises
    if (!ActorList.IsEmpty()) {
        const int32 Removed = ActorList.RemoveSingleSwap(Entity, /*bAllowShrinking=*/false);
        if (Removed > 0)
        {
            UE_LOG(LogCoveragesManager, Verbose, TEXT("RemoveEntity: Entity %d removed from ActorList"),
                Entity->GetEntityId().EntityID);
            return true;
        }
    }



    // Not found (may have been pruned earlier); still okay
    UE_LOG(LogCoveragesManager, Verbose, TEXT("RemoveEntity: Entity %d not present in ActorList"),
        Entity->GetEntityId().EntityID);
    return false;
}

void UCoveragesManager::ClearAll() {
    for (AEntityBase* entity : ActorList) {
        if (entity) {
            RemoveEntity(entity);
        }
    }
}

bool UCoveragesManager::RemoveEntityById(const FEntityID& Id)
{
    // Find the pointer by ID
    for (int32 i = ActorList.Num() - 1; i >= 0; --i)
    {
        AEntityBase* Entity = ActorList[i];
        if (IsValid(Entity) && Entity->GetEntityId() == Id)
        {
            // Remove + cleanup
            ActorList.RemoveAtSwap(i, 1, /*bAllowShrinking=*/false);
            CleanupCoverageForEntity(Entity);
            UE_LOG(LogCoveragesManager, Verbose, TEXT("RemoveEntityById: Removed entity %d"), Id.EntityID);
            return true;
        }
    }

    UE_LOG(LogCoveragesManager, Verbose, TEXT("RemoveEntityById: No entity found for id %d"), Id.EntityID);
    return false;
}


void UCoveragesManager::CleanupExistingRings(AActor* DomeActor, FName TagForCleanup)
{
    if (!DomeActor) return;

    TArray<UActorComponent*> Components = DomeActor->GetComponentsByTag(UStaticMeshComponent::StaticClass(), TagForCleanup);
    for (UActorComponent* C : Components)
    {
        if (UStaticMeshComponent* SMC = Cast<UStaticMeshComponent>(C))
        {
            SMC->DestroyComponent();
        }
    }
}

// Trace across the full diameter; choose hit nearest to the slice center.
// Uses the provided collision params so we can ignore other domes.
static bool SampleRimPointAcrossDiameter(
    UWorld* World,
    const UPrimitiveComponent* DomeComp,
    const FVector& SliceCenter,
    const FVector& Dir,
    float MaxLen,
    float PushUU,
    const FCollisionQueryParams& Params,
    FVector& OutPoint)
{
    TArray<FHitResult> Hits;
    if (!World->LineTraceMultiByChannel(Hits, SliceCenter - Dir * MaxLen, SliceCenter + Dir * MaxLen, ECC_Visibility, Params))
        return false;

    double best = TNumericLimits<double>::Max();
    bool found = false;
    FVector bestPoint(ForceInit);

    for (const FHitResult& H : Hits)
    {
        if (H.Component.Get() != DomeComp) continue;          // only our dome
        const double score = FMath::Abs(FVector::DotProduct(H.ImpactPoint - SliceCenter, Dir));
        if (score < best)
        {
            best = score;
            bestPoint = H.ImpactPoint + H.ImpactNormal * PushUU; // slight lift to avoid z-fighting
            found = true;
        }
    }
    if (!found) return false;
    OutPoint = bestPoint;
    return true;
}


// Utility: line-trace from start to end and return hit distance on a specific component
static bool TraceDistanceOnComponent(
    UWorld* World,
    const UPrimitiveComponent* TargetComp,
    const FVector& Start,
    const FVector& End,
    float& OutDistance)
{
    FHitResult Hit;
    FCollisionQueryParams Params(SCENE_QUERY_STAT(CoverageRings), /*bTraceComplex*/ true);
    Params.bReturnPhysicalMaterial = false;

    // We want to hit only the dome comp; ignoring actors is not enough if there are other meshes.
    // Use component query params by checking the hit component after the trace.
    bool bHit = World->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);

    if (bHit && Hit.Component.Get() == TargetComp)
    {
        OutDistance = (Hit.ImpactPoint - Start).Size();
        return true;
    }
    return false;
}

// Measure radii at a given Z by tracing +X and +Y planes from the center
static bool MeasureRadiiAtZ(
    UWorld* World,
    UStaticMeshComponent* DomeComp,
    float Z,
    float& OutRadiusX,
    float& OutRadiusY)
{
    if (!World || !DomeComp) return false;

    const FBoxSphereBounds B = DomeComp->Bounds; // world, scale-aware
    const FVector CenterXY(B.Origin.X, B.Origin.Y, Z);

    // Trace lengths: something safely larger than bounds
    const float MaxX = B.BoxExtent.X * 2.5f + 1000.f;
    const float MaxY = B.BoxExtent.Y * 2.5f + 1000.f;

    float DistX = 0.f, DistY = 0.f;

    // Start slightly *inside* to ensure we exit the surface
    const FVector EpsilonX(10.f, 0.f, 0.f);
    const FVector EpsilonY(0.f, 10.f, 0.f);

    const FVector StartX = CenterXY + EpsilonX;
    const FVector EndX = CenterXY + FVector(MaxX, 0.f, 0.f);

    const FVector StartY = CenterXY + EpsilonY;
    const FVector EndY = CenterXY + FVector(0.f, MaxY, 0.f);

    bool bHitX = TraceDistanceOnComponent(World, DomeComp, StartX, EndX, DistX);
    bool bHitY = TraceDistanceOnComponent(World, DomeComp, StartY, EndY, DistY);

    if (bHitX && bHitY)
    {
        OutRadiusX = DistX;
        OutRadiusY = DistY;
        return true;
    }

    return false;
}


//void UCoveragesManager::SpawnProceduralRingsOnDome(
//    AActor* DomeActor,
//    UStaticMeshComponent* DomeComp,
//    float IntervalMeters,
//    int32 Segments,
//    float RingWidthMeters,      // radial width
//    float RingHeightMeters,     // vertical height
//    float SurfacePushCm,
//    FName TagForCleanup,
//    bool /*bFromTop*/,                  // ignored: we always build from center -> up
//    bool bIgnoreOtherDomes /*= true*/)
//{
//    if (!DomeActor || !DomeComp) return;
//
//    // remove old
//    {
//        TArray<UActorComponent*> Comps = DomeActor->GetComponentsByTag(UProceduralMeshComponent::StaticClass(), TagForCleanup);
//        for (UActorComponent* C : Comps)
//            if (auto* PM = Cast<UProceduralMeshComponent>(C)) PM->DestroyComponent();
//    }
//
//    // params
//    IntervalMeters /= 2.0f;
//
//    const int32 N = FMath::Clamp(Segments, 32, 2048);
//    const float StepUU = FMath::Max(1.f, IntervalMeters * 100.f);
//    const float BandUU = FMath::Max(0.1f, RingWidthMeters * 100.f);
//    const float HalfH = FMath::Max(0.1f, RingHeightMeters * 100.f) ;
//    const float PushUU = FMath::Clamp(SurfacePushCm, 0.f, 100.f);
//
//    const FBoxSphereBounds DB = DomeComp->Bounds;     // world-space, scale-aware
//    const float CenterZ = DB.Origin.Z;                // <-- origin (center of dome)
//    const float TopZ = DB.Origin.Z + DB.BoxExtent.Z;
//    const float RadiusZ = TopZ - CenterZ;             // height of UPPER hemisphere only
//
//    // how many rings fit from center -> apex (exclude apex itself)
//    const int32 NumRings = FMath::Clamp(FMath::FloorToInt(RadiusZ / StepUU), 0, 4096);
//    if (NumRings <= 0) return;
//
//    // overlap-safe trace params
//    FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(CoverageRingsMulti), /*bTraceComplex*/ true);
//    TraceParams.bReturnPhysicalMaterial = false;
//    if (bIgnoreOtherDomes)
//    {
//        for (AActor* A : ActorList)
//            if (A && A != DomeActor) TraceParams.AddIgnoredActor(A);
//    }
//
//    // one PMC holding all sections
//    UProceduralMeshComponent* PMC = NewObject<UProceduralMeshComponent>(DomeActor, UProceduralMeshComponent::StaticClass(), NAME_None, RF_Transient);
//    PMC->AttachToComponent(DomeComp, FAttachmentTransformRules::KeepWorldTransform);
//    PMC->RegisterComponent();
//    PMC->SetMobility(EComponentMobility::Movable);
//    PMC->SetCastShadow(false);
//    PMC->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//    PMC->bUseAsyncCooking = false;
//    PMC->ComponentTags.Add(TagForCleanup);
//    if (RingMat) PMC->SetMaterial(0, RingMat);
//
//    // basis (pure yaw)
//    FRotator YawOnly = DomeComp->GetComponentRotation(); YawOnly.Pitch = YawOnly.Roll = 0.f;
//    const FRotationMatrix RM(YawOnly);
//    FVector Xhat = RM.GetUnitAxis(EAxis::X); Xhat.Z = 0.f; Xhat.Normalize();
//    FVector Yhat = RM.GetUnitAxis(EAxis::Y); Yhat.Z = 0.f; Yhat.Normalize();
//
//    const float dTheta = 2.f * PI / float(N);
//    const float MaxLen = FMath::Max(DB.BoxExtent.X, DB.BoxExtent.Y) * 4.f + 10000.f;
//
//    // working buffers
//    TArray<FVector> V;           V.Reserve(N * 8);
//    TArray<int32>   Idx;         Idx.Reserve(N * 24);
//    TArray<FVector> Norm;        Norm.Reserve(N * 8);
//    TArray<FVector2D> UV;        UV.Reserve(N * 8);
//    TArray<FLinearColor> Col;    Col.Init(FLinearColor::White, 0);
//    TArray<FProcMeshTangent> Tg; Tg.Init(FProcMeshTangent(1, 0, 0), 0);
//
//    for (int32 r = 1; r <= NumRings; ++r)
//    {
//        // **From center (equator) upward only**
//        const float Z = CenterZ + r * StepUU;
//        if (Z >= TopZ - 0.5f) continue;      // skip degenerate near-apex plane
//
//        const FVector SliceCenter(DB.Origin.X, DB.Origin.Y, Z);
//
//        // --- sample rim points across full diameter (this dome only) ---
//        TArray<FVector> Rim; Rim.Reserve(N);
//        for (int32 k = 0; k < N; ++k)
//        {
//            const float a = k * dTheta;
//            const FVector Dir = (Xhat * FMath::Cos(a) + Yhat * FMath::Sin(a)).GetSafeNormal();
//
//            FVector HitPoint;
//            if (!SampleRimPointAcrossDiameter(GetWorld(), DomeComp, SliceCenter, Dir, MaxLen, PushUU, TraceParams, HitPoint))
//            {
//                // fallback to bounds ellipse (still center-based)
//                const float t = (Z - CenterZ) / FMath::Max(RadiusZ, 1.f);   // 0..1
//                const float f = FMath::Sqrt(FMath::Max(0.f, 1.f - t * t));
//                HitPoint = SliceCenter
//                    + Xhat * (DB.BoxExtent.X * f * FMath::Cos(a))
//                    + Yhat * (DB.BoxExtent.Y * f * FMath::Sin(a));
//            }
//            Rim.Add(HitPoint);
//        }
//        if (Rim.Num() != N) continue;
//
//        // in-plane perpendiculars
//        TArray<FVector> Perp; Perp.Reserve(N);
//        for (int32 k = 0; k < N; ++k)
//        {
//            const int32 kn = (k + 1) % N;
//            FVector T = Rim[kn] - Rim[k]; T.Z = 0.f;
//            if (!T.Normalize()) T = (Xhat * FMath::Cos(k * dTheta) + Yhat * FMath::Sin(k * dTheta));
//            Perp.Add(FVector(-T.Y, T.X, 0.f).GetSafeNormal());
//        }
//
//        // 4 rails (top/bottom × outer/inner)
//        TArray<FVector> TopOuter, TopInner, BotOuter, BotInner;
//        TopOuter.Reserve(N); TopInner.Reserve(N); BotOuter.Reserve(N); BotInner.Reserve(N);
//
//        for (int32 k = 0; k < N; ++k)
//        {
//            const FVector OC = Rim[k] + Perp[k] * (BandUU * 0.5f);
//            const FVector IC = Rim[k] - Perp[k] * (BandUU * 0.5f);
//            TopOuter.Add(OC + FVector(0, 0, HalfH));
//            TopInner.Add(IC + FVector(0, 0, HalfH));
//            BotOuter.Add(OC - FVector(0, 0, HalfH));
//            BotInner.Add(IC - FVector(0, 0, HalfH));
//        }
//
//        // assemble vertices
//        const int32 baseTop = V.Num(); V.AddUninitialized(2 * N);
//        const int32 baseBottom = V.Num(); V.AddUninitialized(2 * N);
//        const int32 baseOuter = V.Num(); V.AddUninitialized(2 * N);
//        const int32 baseInner = V.Num(); V.AddUninitialized(2 * N);
//
//        Norm.AddUninitialized(8 * N); UV.AddUninitialized(8 * N);
//        Col.AddUninitialized(8 * N); Tg.AddUninitialized(8 * N);
//
//        // TOP face
//        for (int32 k = 0; k < N; ++k)
//        {
//            const int32 v0 = baseTop + 2 * k, v1 = v0 + 1;
//            V[v0] = TopOuter[k]; V[v1] = TopInner[k];
//            Norm[v0] = FVector::UpVector; Norm[v1] = FVector::UpVector;
//            UV[v0] = FVector2D(float(k) / N, 1); UV[v1] = FVector2D(float(k) / N, 0);
//            Col[v0] = Col[v1] = FLinearColor::White; Tg[v0] = Tg[v1] = FProcMeshTangent(1, 0, 0);
//        }
//        for (int32 k = 0; k < N; ++k)
//        {
//            const int32 i0 = baseTop + 2 * k, i1 = i0 + 1, i2 = baseTop + 2 * ((k + 1) % N), i3 = i2 + 1; Idx.Add(i0); Idx.Add(i1); Idx.Add(i3); Idx.Add(i0); Idx.Add(i3); Idx.Add(i2);
//        }
//
//        // BOTTOM face (reverse)
//        for (int32 k = 0; k < N; ++k)
//        {
//            const int32 v0 = baseBottom + 2 * k, v1 = v0 + 1;
//            V[v0] = BotOuter[k]; V[v1] = BotInner[k];
//            Norm[v0] = FVector(0, 0, -1); Norm[v1] = FVector(0, 0, -1);
//            UV[v0] = FVector2D(float(k) / N, 1); UV[v1] = FVector2D(float(k) / N, 0);
//            Col[v0] = Col[v1] = FLinearColor::White; Tg[v0] = Tg[v1] = FProcMeshTangent(1, 0, 0);
//        }
//        for (int32 k = 0; k < N; ++k)
//        {
//            const int32 i0 = baseBottom + 2 * k, i1 = i0 + 1, i2 = baseBottom + 2 * ((k + 1) % N), i3 = i2 + 1; Idx.Add(i2); Idx.Add(i3); Idx.Add(i1); Idx.Add(i2); Idx.Add(i1); Idx.Add(i0);
//        }
//
//        // OUTER wall
//        for (int32 k = 0; k < N; ++k)
//        {
//            const int32 v0 = baseOuter + 2 * k, v1 = v0 + 1;
//            V[v0] = TopOuter[k]; V[v1] = BotOuter[k];
//            Norm[v0] = Perp[k];  Norm[v1] = Perp[k];
//            UV[v0] = FVector2D(float(k) / N, 1); UV[v1] = FVector2D(float(k) / N, 0);
//            Col[v0] = Col[v1] = FLinearColor::White; Tg[v0] = Tg[v1] = FProcMeshTangent(1, 0, 0);
//        }
//        for (int32 k = 0; k < N; ++k)
//        {
//            const int32 i0 = baseOuter + 2 * k, i1 = i0 + 1, i2 = baseOuter + 2 * ((k + 1) % N), i3 = i2 + 1; Idx.Add(i0); Idx.Add(i1); Idx.Add(i3); Idx.Add(i0); Idx.Add(i3); Idx.Add(i2);
//        }
//
//        // INNER wall (reverse)
//        for (int32 k = 0; k < N; ++k)
//        {
//            const int32 v0 = baseInner + 2 * k, v1 = v0 + 1;
//            V[v0] = TopInner[k]; V[v1] = BotInner[k];
//            Norm[v0] = -Perp[k]; Norm[v1] = -Perp[k];
//            UV[v0] = FVector2D(float(k) / N, 1); UV[v1] = FVector2D(float(k) / N, 0);
//            Col[v0] = Col[v1] = FLinearColor::White; Tg[v0] = Tg[v1] = FProcMeshTangent(1, 0, 0);
//        }
//        for (int32 k = 0; k < N; ++k)
//        {
//            const int32 i0 = baseInner + 2 * k, i1 = i0 + 1, i2 = baseInner + 2 * ((k + 1) % N), i3 = i2 + 1; Idx.Add(i2); Idx.Add(i3); Idx.Add(i1); Idx.Add(i2); Idx.Add(i1); Idx.Add(i0);
//        }
//
//        const int32 SectionIndex = r - 1;
//        PMC->CreateMeshSection_LinearColor(SectionIndex, V, Idx, Norm, UV, Col, Tg, false);
//        if (RingMat) PMC->SetMaterial(SectionIndex, RingMat);
//
//        // next ring
//        V.Reset(); Idx.Reset(); Norm.Reset(); UV.Reset(); Col.Reset(); Tg.Reset();
//    }
//}

void UCoveragesManager::SpawnProceduralRingsOnDome(
    AEntityBase* pEntity,
    UStaticMeshComponent* DomeComp,
    float IntervalMeters,
    int32 Segments,
    float RingWidthMeters,      // radial width (meters)
    float RingHeightMeters,     // vertical height (meters)
    float SurfacePushCm,
    FName TagForCleanup,
    bool /*bFromTop*/,                  // ignored: center -> up only
    bool bIgnoreOtherDomes /*= true*/)
{
    if (!pEntity || !DomeComp) return;
  
    // Remove previous
    {
        TArray<UActorComponent*> Comps = pEntity->GetComponentsByTag(UProceduralMeshComponent::StaticClass(), TagForCleanup);
        for (UActorComponent* C : Comps)
            if (auto* PM = Cast<UProceduralMeshComponent>(C)) PM->DestroyComponent();
    }

    // --- parameters (cm) ---
    const int32 N = FMath::Clamp(Segments, 96, 2048);
    const float StepUU = FMath::Max(1.f, IntervalMeters * 100.f);
    const float BandUU = FMath::Max(0.1f, RingWidthMeters * 100.f);
    const float HalfH = FMath::Max(0.1f, RingHeightMeters * 100.f) * 0.5f;
    const float PushUU = FMath::Clamp(SurfacePushCm, 0.f, 100.f);

    const FBoxSphereBounds DB = DomeComp->Bounds;        // world
    const float CenterZ = DB.Origin.Z;                   // origin (equator)
    const float TopZ = DB.Origin.Z + DB.BoxExtent.Z;
    const float RadiusZ = TopZ - CenterZ;                // upper hemi height
    const float RadiusAtZ = FMath::Sqrt(FMath::Max(0.0f, (RadiusZ*RadiusZ) - (TopZ- CenterZ)*(TopZ- CenterZ)));              


    const int32 NumRings = FMath::Clamp(FMath::FloorToInt(RadiusZ / StepUU), 0, 4096);
    if (NumRings <= 0) return;

    // Trace params (ignore other domes)
    FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(CoverageRingsMulti), /*bTraceComplex*/ true);
    TraceParams.bReturnPhysicalMaterial = false;
    if (bIgnoreOtherDomes)
        for (AActor* A : ActorList) if (A && A != pEntity) TraceParams.AddIgnoredActor(A);

    for (AActor* A : EntityManager::GetEntityManagerInstance()->getRemoteEntitiesList()) if (A && A != pEntity) TraceParams.AddIgnoredActor(A);



    // One PMC for all sections

    UProceduralMeshComponent* PMC = NewObject<UProceduralMeshComponent>(pEntity, UProceduralMeshComponent::StaticClass(), NAME_None, RF_Transient);
    pEntity->DomeRings = PMC;

    pEntity->DomeRings->SetVisibility(UIManager::GetInstance()->ButtonSates.bIsDomeRing);
    pEntity->DomeRings->SetHiddenInGame(!UIManager::GetInstance()->ButtonSates.bIsDomeRing);
    PMC->AttachToComponent(DomeComp, FAttachmentTransformRules::KeepWorldTransform);
    PMC->RegisterComponent();
    PMC->SetMobility(EComponentMobility::Movable);
    PMC->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    PMC->SetCastShadow(false);
    PMC->bUseAsyncCooking = false;
    PMC->bUseAttachParentBound = true;
    PMC->SetBoundsScale(2.0f);
    PMC->ComponentTags.Add(TagForCleanup);
    if (RingMat) PMC->SetMaterial(0, RingMat);

    // Horizontal basis (pure yaw)
    FRotator YawOnly = DomeComp->GetComponentRotation(); YawOnly.Pitch = YawOnly.Roll = 0.f;
    const FRotationMatrix RM(YawOnly);
    FVector Xhat = RM.GetUnitAxis(EAxis::X); Xhat.Z = 0.f; Xhat.Normalize();
    FVector Yhat = RM.GetUnitAxis(EAxis::Y); Yhat.Z = 0.f; Yhat.Normalize();

    const float dTheta = 2.f * PI / float(N);
    const float MaxLen = FMath::Max(DB.BoxExtent.X, DB.BoxExtent.Y) * 4.f + 10000.f;

    // Small optional smoothing to suppress triangle jitter
    auto SmoothRing = [](TArray<FVector>& Pts)
        {
            if (Pts.Num() < 3) return;
            TArray<FVector> Tmp; Tmp.SetNumUninitialized(Pts.Num());
            const float Alpha = 0.35f;
            for (int pass = 0; pass < 1; ++pass)   // <= keep gentle (1 pass)
            {
                for (int32 k = 0; k < Pts.Num(); ++k)
                {
                    const int32 kp = (k - 1 + Pts.Num()) % Pts.Num();
                    const int32 kn = (k + 1) % Pts.Num();
                    const FVector Avg = (Pts[kp] + Pts[k] + Pts[kn]) / 3.f;
                    Tmp[k] = FMath::Lerp(Pts[k], Avg, Alpha);
                    Tmp[k].Z = Pts[k].Z; // keep plane height exact
                }
                Pts = Tmp;
            }
        };

    // Working buffers
    TArray<FVector> V;           V.Reserve(N * 8);
    TArray<int32>   Idx;         Idx.Reserve(N * 24);
    TArray<FVector> Norm;        Norm.Reserve(N * 8);
    TArray<FVector2D> UV;        UV.Reserve(N * 8);
    TArray<FLinearColor> Col;    Col.Init(FLinearColor::White, 0);
    TArray<FProcMeshTangent> Tg; Tg.Init(FProcMeshTangent(1, 0, 0), 0);

    for (int32 r = 1; r <= NumRings; ++r)
    {
        const float Z = CenterZ + r * StepUU;          // center -> up
        if (Z >= TopZ - 0.5f) continue;

        const FVector SliceCenter(DB.Origin.X, DB.Origin.Y, Z);

        // ---- 1) sample rim points across diameter ----
        TArray<FVector> Rim; Rim.Reserve(N);
        for (int32 k = 0; k < N; ++k)
        {
            const float a = k * dTheta;
            const FVector Dir = (Xhat * FMath::Cos(a) + Yhat * FMath::Sin(a)).GetSafeNormal();

            FVector P; bool bGot = false;
            TArray<FHitResult> Hits;
            if (World->LineTraceMultiByChannel(Hits, SliceCenter - Dir * MaxLen, SliceCenter + Dir * MaxLen, ECC_Visibility, TraceParams))
            {
                double best = TNumericLimits<double>::Max();
                for (const FHitResult& H : Hits)
                {
                    if (H.Component.Get() != DomeComp) continue;
                    const double score = FMath::Abs(FVector::DotProduct(H.ImpactPoint - SliceCenter, Dir));
                    if (score < best)
                    {
                        best = score;
                        P = H.ImpactPoint + H.ImpactNormal * PushUU;  // lift slightly off surface
                        bGot = true;
                    }
                }
            }
            if (!bGot)
            {
                // Fallback: center-based ellipse
                const float t = (Z - CenterZ) / FMath::Max(RadiusZ, 1.f);
                const float f = FMath::Sqrt(FMath::Max(0.f, 1.f - t * t));
                P = SliceCenter
                    + Xhat * (DB.BoxExtent.X * f * FMath::Cos(a))
                    + Yhat * (DB.BoxExtent.Y * f * FMath::Sin(a));
            }
            Rim.Add(P);
        }

        // ---- 2) gentle smoothing (does not change Z) ----
        SmoothRing(Rim);

        // ---- 3) outward-oriented 2D perpendiculars (prevents sign flips) ----
        TArray<FVector> Perp; Perp.Reserve(N);
        for (int32 k = 0; k < N; ++k)
        {
            const int32 kp = (k - 1 + N) % N;
            const int32 kn = (k + 1) % N;

            // central-difference tangent in XY plane
            FVector Tang = Rim[kn] - Rim[kp];
            Tang.Z = 0.f;
            if (!Tang.Normalize())
                Tang = (Xhat * FMath::Cos(k * dTheta) + Yhat * FMath::Sin(k * dTheta));

            FVector N2D(-Tang.Y, Tang.X, 0.f);  // 2D perp

            // ensure it points OUTWARD by checking against radial from center
            FVector Rad = Rim[k] - SliceCenter; Rad.Z = 0.f;
            if (Rad.IsNearlyZero()) Rad = N2D;  // edge case
            Rad.Normalize();

            if (FVector::DotProduct(N2D, Rad) < 0.f) N2D *= -1.f;

            Perp.Add(N2D.GetSafeNormal());
        }

        // ---- 4) build 4 rails (top/bottom × outer/inner) ----
        TArray<FVector> TopOuter, TopInner, BotOuter, BotInner;
        TopOuter.Reserve(N); TopInner.Reserve(N); BotOuter.Reserve(N); BotInner.Reserve(N);

        for (int32 k = 0; k < N; ++k)
        {
            const FVector OC = Rim[k] + Perp[k] * (BandUU * 0.5f);
            const FVector IC = Rim[k] - Perp[k] * (BandUU * 0.5f);

            TopOuter.Add(OC + FVector(0, 0, HalfH));
            TopInner.Add(IC + FVector(0, 0, HalfH));
            BotOuter.Add(OC - FVector(0, 0, HalfH));
            BotInner.Add(IC - FVector(0, 0, HalfH));
        }

        // ---- 5) assemble faces ----
        const int32 baseTop = V.Num(); V.AddUninitialized(2 * N);
        const int32 baseBottom = V.Num(); V.AddUninitialized(2 * N);
        const int32 baseOuter = V.Num(); V.AddUninitialized(2 * N);
        const int32 baseInner = V.Num(); V.AddUninitialized(2 * N);

        Norm.AddUninitialized(8 * N); UV.AddUninitialized(8 * N);
        Col.AddUninitialized(8 * N); Tg.AddUninitialized(8 * N);

        // TOP
        for (int32 k = 0; k < N; ++k)
        {
            const int32 v0 = baseTop + 2 * k, v1 = v0 + 1;
            V[v0] = TopOuter[k]; V[v1] = TopInner[k];
            Norm[v0] = Norm[v1] = FVector::UpVector;
            UV[v0] = FVector2D(float(k) / N, 1); UV[v1] = FVector2D(float(k) / N, 0);
            Col[v0] = Col[v1] = FLinearColor::White; Tg[v0] = Tg[v1] = FProcMeshTangent(1, 0, 0);
        }
        for (int32 k = 0; k < N; ++k)
        {
            const int32 i0 = baseTop + 2 * k, i1 = i0 + 1, i2 = baseTop + 2 * ((k + 1) % N), i3 = i2 + 1; Idx.Add(i0); Idx.Add(i1); Idx.Add(i3); Idx.Add(i0); Idx.Add(i3); Idx.Add(i2);
        }

        // BOTTOM (reverse)
        for (int32 k = 0; k < N; ++k)
        {
            const int32 v0 = baseBottom + 2 * k, v1 = v0 + 1;
            V[v0] = BotOuter[k]; V[v1] = BotInner[k];
            Norm[v0] = Norm[v1] = FVector(0, 0, -1);
            UV[v0] = FVector2D(float(k) / N, 1); UV[v1] = FVector2D(float(k) / N, 0);
            Col[v0] = Col[v1] = FLinearColor::White; Tg[v0] = Tg[v1] = FProcMeshTangent(1, 0, 0);
        }
        for (int32 k = 0; k < N; ++k)
        {
            const int32 i0 = baseBottom + 2 * k, i1 = i0 + 1, i2 = baseBottom + 2 * ((k + 1) % N), i3 = i2 + 1; Idx.Add(i2); Idx.Add(i3); Idx.Add(i1); Idx.Add(i2); Idx.Add(i1); Idx.Add(i0);
        }

        // OUTER wall
        for (int32 k = 0; k < N; ++k)
        {
            const int32 v0 = baseOuter + 2 * k, v1 = v0 + 1;
            V[v0] = TopOuter[k]; V[v1] = BotOuter[k];
            Norm[v0] = Norm[v1] = Perp[k];
            UV[v0] = FVector2D(float(k) / N, 1); UV[v1] = FVector2D(float(k) / N, 0);
            Col[v0] = Col[v1] = FLinearColor::White; Tg[v0] = Tg[v1] = FProcMeshTangent(1, 0, 0);
        }
        for (int32 k = 0; k < N; ++k)
        {
            const int32 i0 = baseOuter + 2 * k, i1 = i0 + 1, i2 = baseOuter + 2 * ((k + 1) % N), i3 = i2 + 1; Idx.Add(i0); Idx.Add(i1); Idx.Add(i3); Idx.Add(i0); Idx.Add(i3); Idx.Add(i2);
        }

        // INNER wall (reverse)
        for (int32 k = 0; k < N; ++k)
        {
            const int32 v0 = baseInner + 2 * k, v1 = v0 + 1;
            V[v0] = TopInner[k]; V[v1] = BotInner[k];
            Norm[v0] = Norm[v1] = -Perp[k];
            UV[v0] = FVector2D(float(k) / N, 1); UV[v1] = FVector2D(float(k) / N, 0);
            Col[v0] = Col[v1] = FLinearColor::White; Tg[v0] = Tg[v1] = FProcMeshTangent(1, 0, 0);
        }
        for (int32 k = 0; k < N; ++k)
        {
            const int32 i0 = baseInner + 2 * k, i1 = i0 + 1, i2 = baseInner + 2 * ((k + 1) % N), i3 = i2 + 1; Idx.Add(i2); Idx.Add(i3); Idx.Add(i1); Idx.Add(i2); Idx.Add(i1); Idx.Add(i0);
        }

        // --- world -> local for the PMC ---
        const FTransform WorldToLocal = PMC->GetComponentTransform().Inverse();
        for (FVector& P : V) { P = WorldToLocal.TransformPosition(P); }
        for (FVector& Nrm : Norm) { Nrm = WorldToLocal.TransformVector(Nrm).GetSafeNormal(); }

        const int32 SectionIndex = r - 1;
        PMC->CreateMeshSection_LinearColor(SectionIndex, V, Idx, Norm, UV, Col, Tg, false);
        if (RingMat) PMC->SetMaterial(SectionIndex, RingMat);

        V.Reset(); Idx.Reset(); Norm.Reset(); UV.Reset(); Col.Reset(); Tg.Reset();
    }
}

UStaticMeshComponent* UCoveragesManager::FindDomeComp(AActor* DomeActor) const
{
    if (!DomeActor) return nullptr;

    // Prefer the tagged one
    TArray<UActorComponent*> Tagged = DomeActor->GetComponentsByTag(UStaticMeshComponent::StaticClass(), "CoverageDome");
    if (Tagged.Num() > 0)
        return Cast<UStaticMeshComponent>(Tagged[0]);

    // Fallback: pick the largest static mesh comp that is NOT a ring
    TArray<UStaticMeshComponent*> SMs;
    DomeActor->GetComponents<UStaticMeshComponent>(SMs);
    UStaticMeshComponent* Best = nullptr;
    float BestSize = -1.f;
    for (UStaticMeshComponent* C : SMs)
    {
        if (C->ComponentTags.Contains("CoverageRing")) continue; // ignore rings
        const float Size = C->Bounds.SphereRadius;
        if (Size > BestSize) { BestSize = Size; Best = C; }
    }
    return Best;
}


void UCoveragesManager::UpdateProceduralRingIntervalForActor(
    AActor* DomeActor,
    float NewIntervalMetersFromTop,
    int32 Segments,
    float RingWidthMeters,
    float RingHeightMeters,
    float SurfacePushCm,
    FName TagForCleanup)
{
    if (!DomeActor) return;

    // Find the dome component we tagged earlier (or pick the largest non-ring mesh)
    UStaticMeshComponent* DomeComp = FindDomeComp(DomeActor);
    AEntityBase* Entity = Cast<AEntityBase>(DomeActor);
    if (!DomeComp) { UE_LOG(LogTemp, Warning, TEXT("UpdateProceduralRingIntervalFromTopForActor: no dome comp")); return; }

    // Rebuild rings with the new interval measured from the TOP
    SpawnProceduralRingsOnDome(
        Entity,
        DomeComp,
        NewIntervalMetersFromTop,
        Segments,
        RingWidthMeters,
        RingHeightMeters,
        SurfacePushCm,
        TagForCleanup,
        true,
        true);
}


void UCoveragesManager::UpdateProceduralRingIntervalForAll(
    float NewIntervalMeters,
    int32 Segments,
    float RingWidthMeters,
    float RingHeightMeters,
    float SurfacePushCm,
    FName TagForCleanup)
{
    for (AActor* A : ActorList)
    {
        if (!A) continue;
        UStaticMeshComponent* DomeComp = FindDomeComp(A);
        if (!DomeComp) continue;
        AEntityBase* Entity = Cast<AEntityBase>(A);

        SpawnProceduralRingsOnDome(
            Entity, DomeComp,
            NewIntervalMeters,
            Segments,
            RingWidthMeters,
            RingHeightMeters,
            SurfacePushCm,
            TagForCleanup,
            /*bFromTop=*/true,
            /*bIgnoreOtherDomes=*/true);
    }
}
