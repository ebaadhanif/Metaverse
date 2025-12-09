#include "SplatMapping.h"
#include "FShapeFileReader.h"
#include "CesiumCartographicPolygon.h"
#undef OPAQUE
#include "Cesium3DTileset.h"
#include "CesiumPolygonRasterOverlay.h"
#include "CesiumGeoreference.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInterface.h"
#include "UObject/NameTypes.h"
#include "Async/Async.h"
#include "TerrainManager.h"
#include "UObject/ConstructorHelpers.h"


ASplatMapping* ASplatMapping::Instance = nullptr;

ASplatMapping::ASplatMapping()
{
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//SetRootComponent(Root);
}

void ASplatMapping::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (Instance == this) {
        Instance = nullptr;
    }
    Super::EndPlay(EndPlayReason);
}

void ASplatMapping::BeginPlay()
{
	Super::BeginPlay();
    if (Instance == nullptr)
    {
        Instance = this;
    }

	CesiumGeoreference = ACesiumGeoreference::GetDefaultGeoreference(GetWorld());

    if (ATerrainManager::GetInstance()->ActiveTerrainSystem->TerrainID != 1) return;

    for (TerrainAssets* Asset : ATerrainManager::GetInstance()->ActiveTerrainSystem->TerrainAssetsList) {
        if (Blank_3D_Tileset* Blank3d_Asset = static_cast<Blank_3D_Tileset*>(Asset)) {
            if (!Blank3d_Asset->splatmapdata.Name.IsEmpty()) {
                if(!ParentActor) CreateParentSplatActor();
                if (Blank3d_Asset->TilesetAssetName == "World Terrain" || Blank3d_Asset->TilesetAssetName == "Shaded Releif") {
                    TargetTilesets.Add(Blank3d_Asset->Tileset);
                    LoadShapeFilesAndApplySplatMaps(Blank3d_Asset);
                }
            }
        }
    }

	MaterialToApply = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/SplatMapping/MI_SplatMapping.MI_SplatMapping"));

	if (!IsValid(MaterialToApply))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load material MI_SplatMapping."));
	}
    else
    
    {
        ApplyMaterialToTilesets(MaterialToApply);
    }
}


void ASplatMapping::ApplyMaterialToTilesets(UMaterialInterface* InMaterialToApply) {
    for (TWeakObjectPtr<ACesium3DTileset> WeakTs : TargetTilesets) {
        if (ACesium3DTileset* Tileset = WeakTs.Get()) {
            if (InMaterialToApply) {
                Tileset->SetMaterial(MaterialToApply);
                Tileset->SetGenerateSmoothNormals(true);
            }
        }
    }
}

void ASplatMapping::LoadShapeFilesAndApplySplatMaps(Blank_3D_Tileset* TerrainAsset)
{

    for (FString& FilePath : TerrainAsset->splatmapdata.ShpFilePaths)
    {
      
        FPaths::NormalizeFilename(FilePath);
        UE_LOG(LogTemp, Warning, TEXT("Path: %s"), *FilePath);
        if (!IFileManager::Get().FileExists(*FilePath)) continue;
        FShapeRawData Raw = FShapeFileReader::ReadShapefileRawData(FilePath);

        const int32 NumPolygons = Raw.Geometries.Num();
        for (int32 PolyIndex = 0; PolyIndex < NumPolygons; ++PolyIndex)
        {
            const TArray<FVector>& RawPoly = Raw.Geometries[PolyIndex];
            if (RawPoly.Num() < 3) {
                const FString* KeyPtr = Raw.Attributes[PolyIndex].Find(TEXT("id"));
                UE_LOG(LogTemp, Error, TEXT("Polygon: %s contains less than 3 points"), *KeyPtr->ToLower());
                continue;
            }

            // Extract material layer key from attributes
            FString MaterialLayerKey = TEXT("splat_sand");

            FString PolygonName = TEXT("POLYGON");
            FString PolygonID = TEXT("ID");


            if (Raw.Attributes.IsValidIndex(PolyIndex))
            {
                const TMap<FString, FString>& Attrs = Raw.Attributes[PolyIndex];

                if (const FString* KeyPtr = Attrs.Find(TEXT("Model")) ? Attrs.Find(TEXT("Model")) : Attrs.Find(TEXT("model"))) {
                    if (KeyPtr && !KeyPtr->IsEmpty())
                    {
                        MaterialLayerKey = *KeyPtr->ToLower();
                    }
                }
                if (const FString* KeyPtr = Attrs.Find(TEXT("Name"))) {
                    if (KeyPtr && !KeyPtr->IsEmpty())
                    {
                        PolygonName = *KeyPtr->ToLower();
                    }
                }

                if (const FString* KeyPtr = Attrs.Find(TEXT("id"))) {
                    if (KeyPtr && !KeyPtr->IsEmpty())
                    {
                        PolygonID = *KeyPtr->ToLower();
                    }
                }
            }



            // Convert geographic coordinates to Unreal
            TArray<FVector> Adjusted;
            for (const FVector& Point : RawPoly)
            {
                FVector UnrealLoc = CesiumGeoreference->TransformLongitudeLatitudeHeightPositionToUnreal(Point);
                Adjusted.Add(UnrealLoc);
            }
            if (Adjusted.Num() < 3) continue;

            // Calculating PolygonCenter
            FVector PolygonCenter = FVector(0, 0, 0);
            for (FVector Point : Adjusted) {
                PolygonCenter += Point;
            }

            PolygonCenter /= Adjusted.Num();

            // Calculating Max Radius from edge 
            float MaxRadius = 0;

            for (FVector Point : Adjusted) {
                float calculated = FVector::Dist(PolygonCenter, Point);
                if (MaxRadius < calculated) MaxRadius = calculated;

            }

            if (test) {
                test->SetVectorParameterValue(FName("PolygonCenter"), FLinearColor(PolygonCenter));
                test->SetScalarParameterValue(FName("MaxRadius"), MaxRadius);
            }


            //FActorSpawnParameters SpawnParamsCarto;
            //SpawnParamsCarto.Owner = this;
            //FString FormatString = FString::Printf(TEXT("Splat Polygon Actor (%s) %s"), *PolygonName, *PolygonID);
            //FName NameFromString(*FormatString);
            //SpawnParamsCarto.Name = NameFromString;
            //FVector Origin = Adjusted[0];
            //ACesiumCartographicPolygon* PolyActor = GetWorld()->SpawnActor<ACesiumCartographicPolygon>();


            ACesiumCartographicPolygon* PolyActor = GetOrCreatePolygon(PolygonID,Adjusted);

           
            //if (!PolyActor)
            //{
            //    UE_LOG(LogTemp, Warning, TEXT("Failed to spawn polygon actor."));
            //    continue;
            //}

            //PolyActor->Polygon->ClearSplinePoints();
            //PolyActor->SetActorLocation(Origin);

            //for (int32 j = 0; j < Adjusted.Num(); ++j)
            //{
            //    FVector Local = Adjusted[j] - Origin;
            //    PolyActor->Polygon->AddSplinePoint(Local, ESplineCoordinateSpace::Local, true);
            //    PolyActor->Polygon->SetSplinePointType(j, ESplinePointType::Linear, false);
            //}

            //PolyActor->Polygon->SetClosedLoop(true);
            //PolyActor->Polygon->UpdateSpline();
            //if (IsValid(ParentActor))
            //{
            //    PolyActor->AttachToComponent(ParentActor->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
            //}

   
           
            const FString MLBPath = FString::Printf(TEXT("/Game/Materials/SplatMapping/BlendAssets/MLB_%s.MLB_%s"), *MaterialLayerKey, *MaterialLayerKey);
            FAssetRegistryModule& AssetRegistryModule = FModuleManager::GetModuleChecked<FAssetRegistryModule>("AssetRegistry");
            FAssetData data = AssetRegistryModule.Get().GetAssetByObjectPath(*MLBPath);

            if (!data.IsValid())
                 MaterialLayerKey = "default";

            UCesiumPolygonRasterOverlay* Overlay = GetOrCreatePolygonRasterOverlay(TerrainAsset->Tileset, MaterialLayerKey);


            if (IsValid(Overlay))
            {
                Overlay->Polygons.Add(PolyActor);
                Overlay->Refresh();
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("Invalid Overlay"));
            }
        }
    }
}

void ASplatMapping::CreateParentSplatActor()
{
    FShapeFileReader::LoadDllForGDAL();
    FActorSpawnParameters SpawnParams;
    SpawnParams.Name = TEXT("SplatMappingParent");
    ParentActor = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
    if (ParentActor)
    {
        USceneComponent* RootComp = NewObject<USceneComponent>(ParentActor);
        RootComp->SetupAttachment(nullptr);
        RootComp->RegisterComponent();
        ParentActor->SetRootComponent(RootComp);

#if WITH_EDITOR
        ParentActor->SetActorLabel(TEXT("Splat Mapping Parent"));
#endif
    }
}

UCesiumPolygonRasterOverlay* ASplatMapping::GetOrCreatePolygonRasterOverlay(ACesium3DTileset* Tileset, const FString &MaterialLayerKey)
{
    if (!Tileset) return nullptr;
    TMap<FString, UCesiumPolygonRasterOverlay*>& MapForTileset = OverlaysByTileset.FindOrAdd(Tileset);
    if (UCesiumPolygonRasterOverlay** Existing = MapForTileset.Find(MaterialLayerKey)) {
        return *Existing;
    }
    FString name = "SplatMap(CesiumPolygonRasterOverlay)";
    FString Concat = name + MaterialLayerKey;
    FName OverlayName(*Concat);
   // FName OverlayName = "SplatMap(CesiumPolygonRasterOverlay)";
    UCesiumPolygonRasterOverlay* Overlay = NewObject<UCesiumPolygonRasterOverlay>(Tileset, UCesiumPolygonRasterOverlay::StaticClass(),
        OverlayName,
        RF_Transactional // so undo/redo works in editor
    );
    Tileset->AddInstanceComponent(Overlay);
    Tileset->Modify();
    Overlay->ComponentTags.Add("SplatMap");
    Overlay->RegisterComponent();
    Overlay->MaterialLayerKey = MaterialLayerKey;
    Overlay->ExcludeSelectedTiles = false;

    MapForTileset.Add(MaterialLayerKey, Overlay);
    
    return Overlay;
}

void ASplatMapping::SetPolygonOverlaysVisible(bool isVisible) {
    for (auto& OverlayTileset : OverlaysByTileset) {
        for (auto& Pair : OverlayTileset.Value) {
            if (UCesiumPolygonRasterOverlay* Overlay = Pair.Value) {
                if (isVisible) {
                    Overlay->Activate(true);
                    Overlay->SetComponentTickEnabled(true);
                }
                else {
                    Overlay->Deactivate();
                    Overlay->SetComponentTickEnabled(false);
                }
                Overlay->Refresh();
            }
        }
    }

}

ASplatMapping* ASplatMapping::GetInstance()
{
    return Instance;
}


ACesiumCartographicPolygon* ASplatMapping::GetOrCreatePolygon(
        const FString& PolygonKey,
        const TArray<FVector>& AdjustedVertices)
{
    // 1️⃣ If we already made it, return it
    if (ACesiumCartographicPolygon** Found = PolygonCache.Find(PolygonKey))
    {
        return *Found;
    }

    // 2️⃣ Not found – spawn a brand‑new actor
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner      = this;
    SpawnParams.Name       = FName(*FString::Printf(TEXT("SplatPoly_%s"), *PolygonKey));
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    ACesiumCartographicPolygon* PolyActor =
        GetWorld()->SpawnActor<ACesiumCartographicPolygon>(SpawnParams);

    if (!PolyActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to spawn polygon actor for key %s"), *PolygonKey);
        return nullptr;
    }

    // Build the spline (same code you already have)
    PolyActor->Polygon->ClearSplinePoints();
    PolyActor->SetActorLocation(AdjustedVertices[0]);

    for (int32 i = 0; i < AdjustedVertices.Num(); ++i)
    {
        FVector Local = AdjustedVertices[i] - AdjustedVertices[0];
        PolyActor->Polygon->AddSplinePoint(Local, ESplineCoordinateSpace::Local, true);
        PolyActor->Polygon->SetSplinePointType(i, ESplinePointType::Linear, false);
    }

    PolyActor->Polygon->SetClosedLoop(true);
    PolyActor->Polygon->UpdateSpline();

    // Attach to the parent if you use one
    if (IsValid(ParentActor))
    {
        PolyActor->AttachToComponent(ParentActor->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
    }

    // Cache it for future reuse
    PolygonCache.Add(PolygonKey, PolyActor);

    return PolyActor;
}
