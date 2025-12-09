#include "DetonationController.h"
#include "Cesium3DTileset.h"
#include "CesiumGeoreference.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "../Team RenderStorm/VisualEffectsController.h"
//#include "CesiumPlotMeshActor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

UDetonationController* UDetonationController::Instance = nullptr;
ACesiumGeoreference* UDetonationController::Georeference = nullptr;
ACesium3DTileset* UDetonationController::Tileset = nullptr;

UDetonationController* UDetonationController::Get()
{
    if (!Instance)
    {
        Instance = NewObject<UDetonationController>();
        Instance->AddToRoot();
    }
    return Instance;
}

void UDetonationController::SpawnDetonationEffectsOnTerrain(const TArray<FVector>& LatLonHeightPoints)
{
    if (LatLonHeightPoints.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No points provided for detonation."));
        return;
    }

    for (const FVector& Point : LatLonHeightPoints)
    {
        SpawnDetonationEffectOnTerrain(Point.X, Point.Y);
    }

    UE_LOG(LogTemp, Log, TEXT("Spawned %d detonation effects."), LatLonHeightPoints.Num());
}

void UDetonationController::InitializeOverlay()
{
    if (!m_World || SharedRasterOverlay) return;

    if (!Tileset)
    {
        UE_LOG(LogTemp, Error, TEXT("No Cesium3DTileset found. Cannot create RasterOverlay."));
        return;
    }

    SharedRasterOverlay = NewObject<UCesiumPolygonRasterOverlay>(Tileset);
    SharedRasterOverlay->RegisterComponent();
    SharedRasterOverlay->MaterialLayerKey = TEXT("Clipping");

    UE_LOG(LogTemp, Log, TEXT("Created SharedRasterOverlay and attached to Cesium3DTileset."));
}
void UDetonationController::SetWorldVariable(UWorld* InWorld)
{
    m_World = InWorld;
}


void UDetonationController::SpawnDetonationEffectOnTerrain(double Lat, double Lon)
{
    FVector Location = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(FVector(Lon, Lat, 150.0));
    AVisualEffectsController::getInstance()->spawnBlastEffect(Location);
//
//    if (!m_World) return;
//
//    if (!SharedRasterOverlay)
//    {
//        InitializeOverlay();
//        if (!SharedRasterOverlay) return;
//    }
//
//
//    // Convert (Lat, Lon) -> Unreal World space
//    const FVector WorldPos =
//        Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(FVector(Lon, Lat, 0.0));
//
//    // Enforce spacing
//    for (ACesiumPlotMeshActor* Existing : SpawnedPlotActors)
//    {
//        if (!IsValid(Existing)) continue;
//
//        const float DistanceSq = FVector::DistSquared(WorldPos, Existing->GetActorLocation());
//        if (DistanceSq <= MinDistanceBetweenDetonations * MinDistanceBetweenDetonations)
//        {
//            UE_LOG(LogTemp, Warning, TEXT("Detonation too close to existing plot. Skipping."));
//            return;
//        }
//    }
//
//    // Ensure we have a parent container called "Detonations"
//    AActor* Root = EnsureDetonationsRoot();
//    if (!Root)
//    {
//        UE_LOG(LogTemp, Error, TEXT("Failed to ensure Detonations root actor."));
//        return;
//    }
//
//    // Spawn the detonation plot actor
//    FActorSpawnParameters SpawnParams;
//    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//
//    ACesiumPlotMeshActor* PlotMeshActor = m_World->SpawnActor<ACesiumPlotMeshActor>(
//        ACesiumPlotMeshActor::StaticClass(),
//        WorldPos,
//        FRotator::ZeroRotator,
//        SpawnParams
//    );
//
//    if (USceneComponent* ParentRoot = DetonationsRoot->GetRootComponent())
//    {
//        if (USceneComponent* ChildRoot = PlotMeshActor->GetRootComponent())
//        {
//            ChildRoot->AttachToComponent(ParentRoot, FAttachmentTransformRules::KeepWorldTransform);
//        }
//        else
//        {
//            // Fallback: if for some reason there’s no child root yet
//            PlotMeshActor->AttachToActor(DetonationsRoot, FAttachmentTransformRules::KeepWorldTransform);
//        }
//    }
//
//    // Parent it under "Detonations"
//    PlotMeshActor->AttachToComponent(Root->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
//
//    // Configure Cesium references
//    PlotMeshActor->CesiumGeoreference = Georeference;
//    PlotMeshActor->CesiumTileset = SharedRasterOverlay->GetTypedOuter<ACesium3DTileset>();
//
//    // Create the crater polygon on the shared overlay
//    ACesiumCartographicPolygon* Polygon = PlotMeshActor->CreateCraterPolygonOnOverlay(SharedRasterOverlay);
//
//    // Track it
//    SpawnedPlotActors.Add(PlotMeshActor);
//
//    // Give the child a helpful editor label like "detonation24.78,79.89"
//#if WITH_EDITOR
//    PlotMeshActor->SetActorLabel(MakeDetonationLabel(Lat, Lon), /*bMarkDirty*/ false);
//#endif
//
//    UE_LOG(LogTemp, Log, TEXT("Spawned PlotMeshActor at %s"), *WorldPos.ToString());
}

void UDetonationController::ClearDetonations()
{

    //if (SharedRasterOverlay)
    //{
    //    SharedRasterOverlay->UnregisterComponent();
    //    SharedRasterOverlay->DestroyComponent();
    //    SharedRasterOverlay = nullptr;
    //}

    //// Destroy all children actors
    //for (ACesiumPlotMeshActor* Actor : SpawnedPlotActors)
    //{
    //    if (IsValid(Actor))
    //    {
    //        Actor->RemoveCraterPolygonAndMesh();
    //        Actor->Destroy();
    //    }
    //}
    //SpawnedPlotActors.Empty();

    //// Destroy the parent container
    //if (IsValid(DetonationsRoot))
    //{
    //    DetonationsRoot->Destroy();
    //    DetonationsRoot = nullptr;
    //}

    //UE_LOG(LogTemp, Log, TEXT("All detonations cleared."));
}



AActor* UDetonationController::EnsureDetonationsRoot()
{
    if (IsValid(DetonationsRoot)) return DetonationsRoot;

    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    DetonationsRoot = m_World->SpawnActor<AActor>(AActor::StaticClass(), FTransform::Identity, Params);
    if (!DetonationsRoot) return nullptr;

    // Make sure it has a root scene component so children can attach and show in the hierarchy
    if (!DetonationsRoot->GetRootComponent())
    {
        USceneComponent* RootScene = NewObject<USceneComponent>(DetonationsRoot, TEXT("DetonationsRootComponent"));
        DetonationsRoot->SetRootComponent(RootScene);
        RootScene->RegisterComponent();
        RootScene->SetMobility(EComponentMobility::Static);
    }

#if WITH_EDITOR
    DetonationsRoot->SetActorLabel(TEXT("Detonations"), /*bMarkDirty*/ false);
#endif

    DetonationsRoot->SetActorLocation(FVector::ZeroVector);
    return DetonationsRoot;
}



FString UDetonationController::MakeDetonationLabel(double Lat, double Lon)
{
    return FString::Printf(TEXT("detonation%.2f,%.2f"), Lat, Lon);
}


void UDetonationController::Shutdown()
{
    if (Instance)
    {
        Instance->RemoveFromRoot();
        Instance = nullptr;
    }
}

ACesiumGeoreference* UDetonationController::GetGeoreference()
{
    return UDetonationController::Georeference;
}
void UDetonationController::SetGeoreference(ACesiumGeoreference* inGeoreference)
{
    UDetonationController::Georeference = inGeoreference;
}

void UDetonationController::SetTileset(ACesium3DTileset* InTileset)
{
    UDetonationController::Tileset = InTileset;
}

UWorld* UDetonationController::GetStoredWorld() {
    return m_World;
}

ACesium3DTileset* UDetonationController::GetTileset()
{
    return Tileset;
}



