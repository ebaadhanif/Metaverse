//#include "CesiumPlotMeshActor.h"
//#undef OPAQUE
//#include "Cesium3DTileset.h"
//#include "GameFramework/Actor.h"
//#include "Kismet/GameplayStatics.h"
//#include "Engine/World.h"
//#include "GeometryScript/MeshBasicEditFunctions.h"
//#include "GeometryScript/MeshPrimitiveFunctions.h"
//#include "GeometryScript/PolyPathFunctions.h"
//#include "GeometryScript/MeshRemeshFunctions.h"
//#include "CesiumGeoreference.h"
//
//
//ACesiumPlotMeshActor::ACesiumPlotMeshActor()
//{
//    DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
//    RootComponent = DefaultSceneRoot;
//
//    PlotMesh = CreateDefaultSubobject<UDynamicMeshComponent>(TEXT("PlotMesh"));
//    PlotMesh->SetupAttachment(DefaultSceneRoot);
//
//    static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialFinder(TEXT("/Game/Materials/Detonation/CraterMaterial.CraterMaterial"));
//    if (MaterialFinder.Succeeded()) {
//        PlotMeshMaterial = MaterialFinder.Object;
//    }
//}
//
//void ACesiumPlotMeshActor::BeginPlay()
//{
//    Super::BeginPlay();
//
//    CesiumGeoreference = ACesiumGeoreference::GetDefaultGeoreference(GetWorld());
//    CesiumTileset = Cast<ACesium3DTileset>(UGameplayStatics::GetActorOfClass(GetWorld(), ACesium3DTileset::StaticClass()));
//
//    if (!PlotMeshMaterial) {
//        PlotMeshMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/Test.Test"));
//    }
//
//   // RefreshTilesetCulling();
//}
//
//
//ACesiumCartographicPolygon* ACesiumPlotMeshActor::CreateCraterPolygonOnOverlay(UCesiumPolygonRasterOverlay* SharedOverlay)
//{
//    if (!CesiumTileset || !SharedOverlay || !CesiumGeoreference) {
//        UE_LOG(LogTemp, Warning, TEXT("Missing CesiumTileset, Georeference, or SharedOverlay."));
//        return nullptr;
//    }
//
//    FActorSpawnParameters SpawnParams;
//    SpawnParams.Owner = this;
//    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//
//
//    FVector Origin(0);
//
//    CartographicPolygon = GetWorld()->SpawnActor<ACesiumCartographicPolygon>(
//        ACesiumCartographicPolygon::StaticClass(),
//        Origin,
//        FRotator::ZeroRotator,
//        SpawnParams);
//
//    if (!CartographicPolygon) return nullptr;
//
//    CartographicPolygon->AttachToComponent(DefaultSceneRoot, FAttachmentTransformRules::KeepRelativeTransform);
//
//    USplineComponent* Spline = CartographicPolygon->Polygon;
//    Spline->ClearSplinePoints();
//
//    float Radius = 400.0f;
//    int NumPoints = 20;
//
//    DitchRadius = 0.5 * Radius;
//    BlendRadius = 0.2 * DitchRadius;
//    RimWidth = 0.8 * DitchRadius;
//    MaxRimHeight = 0.04 * DitchRadius;
//    MaxDepth =-0.6 * DitchRadius;
//
//
//
//    TArray<FVector3d> CartoPoints;
//
//    for (int i = 0; i < NumPoints; ++i)
//    {
//        float Angle = FMath::DegreesToRadians(360.0f * i / NumPoints);
//        float X = Radius * FMath::Cos(Angle);
//        float Y = Radius * FMath::Sin(Angle);
//        FVector Point(X, Y, 0);
//        Spline->AddSplinePoint(Point, ESplineCoordinateSpace::Local, false);
//    }
//
//    Spline->SetClosedLoop(true);
//    Spline->UpdateSpline();
//
//    SharedOverlay->Polygons.Add(CartographicPolygon);
//    SharedOverlay->Refresh();
//    UpdatePlotMeshForPolygon();
//
//    return CartographicPolygon;
//}
//
//void ACesiumPlotMeshActor::UpdatePlotMeshForPolygon()
//{
//    if (!CartographicPolygon || !CartographicPolygon->Polygon) return;
//
//    PlotMesh->SetVisibility(true);
//    PlotMesh->SetMaterial(0, PlotMeshMaterial);
//
//
//    FDynamicMesh3 Mesh;
//
//    TArray<FVector> Poly = GetPolygonMeshVertices();
//
//    for (FVector& P : Poly) {
//        P -= GetActorLocation();
//    }
//
//    DitchCenter = ComputePolygonCenter(Poly);
//
//
//    if (Poly.Num() == 0) return;
//
//    Mesh.Clear();
//
//    BuildMeshFromPolygon(Mesh, Poly);
//    SnapMeshToTerrain(Mesh);
//
//}
//
//TArray<FVector> ACesiumPlotMeshActor::GetPolygonMeshVertices()
//{
//    TArray<FVector> OutPoints;
//
//    if (!CartographicPolygon || !CartographicPolygon->Polygon) return OutPoints;
//
//    USplineComponent* Spline = CartographicPolygon->Polygon;
//
//    FGeometryScriptPolyPath PolyPath;
//    FGeometryScriptSplineSamplingOptions SamplingOptions;
//
//    SamplingOptions.RangeMethod = EGeometryScriptEvaluateSplineRange::FullSpline;
//    SamplingOptions.SampleSpacing = EGeometryScriptSampleSpacing::ErrorTolerance;
//    SamplingOptions.CoordinateSpace = ESplineCoordinateSpace::World;
//    SamplingOptions.ErrorTolerance = 0.1f;
//    SamplingOptions.NumSamples = 10;
//    SamplingOptions.RangeStart = 0;
//    SamplingOptions.RangeEnd = 1;
//
//    UGeometryScriptLibrary_PolyPathFunctions::ConvertSplineToPolyPath(Spline, PolyPath, SamplingOptions);
//
//    if (PolyPath.Path.IsValid()) {
//        OutPoints = *PolyPath.Path;
//    }
//
//    return OutPoints;
//}
//
//FVector ACesiumPlotMeshActor::ComputePolygonCenter(const TArray<FVector>& Points)
//{
//    FVector Sum = FVector::ZeroVector;
//    for (const auto& P : Points) Sum += P;
//    return Points.Num() > 0 ? Sum / Points.Num() : FVector::ZeroVector;
//}
//
//void ACesiumPlotMeshActor::BuildMeshFromPolygon(FDynamicMesh3& Mesh, const TArray<FVector>& Poly)
//{
//    UDynamicMesh* TargetUDM = NewObject<UDynamicMesh>();
//    TargetUDM->EditMesh([&](FDynamicMesh3& EditMesh) {
//        EditMesh = Mesh;
//        });
//
//    TArray<FVector2D> Poly2D;
//    Poly2D.Reserve(Poly.Num());
//
//
//    for (const FVector& P : Poly)
//    {
//        Poly2D.Add(FVector2D(P.X, P.Y));
//    }
//
//    UGeometryScriptLibrary_MeshPrimitiveFunctions::AppendTriangulatedPolygon(
//        TargetUDM,
//        FGeometryScriptPrimitiveOptions(),
//        FTransform::Identity,
//        Poly2D,
//        false,
//        nullptr);
//
//    TargetUDM->EditMesh([&](FDynamicMesh3& EditMesh) {
//        Mesh = EditMesh;
//        });
//}
//
//void ACesiumPlotMeshActor::ApplyCraterEffect(FDynamicMesh3& Mesh)
//{
//    double RimStartRadius = DitchRadius + BlendRadius;            // where rim starts
//    double RimEndRadius = RimStartRadius + RimWidth;             // where rim ends
//    double OverlapBlendWidth = 0.2 * BlendRadius;                // extra smooth band
//
//    for (int32 vid : Mesh.VertexIndicesItr())
//    {
//        FVector3d Pos = Mesh.GetVertex(vid);
//
//        FVector2D V2(Pos.X, Pos.Y);
//        FVector2D Center2D(DitchCenter.X, DitchCenter.Y);
//
//        double Dist = FVector2D::Distance(V2, Center2D);
//
//        double Offset = 0.0;
//
//        // Inner crater (constant depth)
//        if (Dist <= DitchRadius)
//        {
//            Offset = MaxDepth;
//        }
//        // Smooth blend from depth back to surface
//        else if (Dist <= DitchRadius + BlendRadius + OverlapBlendWidth)
//        {
//            double Alpha = (Dist - DitchRadius) / (BlendRadius + OverlapBlendWidth); // [0..1]
//            double SmoothAlpha = FMath::InterpEaseInOut(0.0, 1.0, Alpha, 2.0);
//            Offset = FMath::Lerp(MaxDepth, 0.0, SmoothAlpha);
//        }
//
//        // Smooth rim bump
//        if (Dist > RimStartRadius - OverlapBlendWidth && Dist <= RimEndRadius)
//        {
//            double Alpha = (Dist - (RimStartRadius - OverlapBlendWidth)) / ((RimEndRadius + OverlapBlendWidth) - (RimStartRadius - OverlapBlendWidth)); // [0..1]
//            Alpha = FMath::Clamp(Alpha, 0.0, 1.0);
//            double SmoothAlpha = 1.0 - FMath::InterpEaseInOut(0.0, 1.0, Alpha, 2.0);
//            double Bump = FMath::Lerp(0.0, MaxRimHeight, SmoothAlpha);
//            Offset += Bump;
//        }
//
//        Mesh.SetVertex(vid, FVector3d(Pos.X, Pos.Y, Pos.Z + Offset));
//    }
//}
//
//void ACesiumPlotMeshActor::SmoothMesh(FDynamicMesh3& Mesh)
//{
//    UDynamicMesh* TargetUDM = NewObject<UDynamicMesh>();
//    TargetUDM->EditMesh([&](FDynamicMesh3& EditMesh) {
//        EditMesh = Mesh;
//        });
//
//    FGeometryScriptRemeshOptions RemeshOptions;
//    RemeshOptions.RemeshIterations = 3;
//
//    FGeometryScriptUniformRemeshOptions UniformOptions;
//    UniformOptions.TargetEdgeLength = 100.0f;
//
//    UGeometryScriptLibrary_RemeshingFunctions::ApplyUniformRemesh(
//        TargetUDM,
//        RemeshOptions,
//        UniformOptions,
//        nullptr
//    );
//
//    TargetUDM->EditMesh([&](FDynamicMesh3& EditMesh) {
//        Mesh = EditMesh;
//        });
//}
//
//void ACesiumPlotMeshActor::CommitMesh(FDynamicMesh3& Mesh)
//{
//    PlotMesh->GetDynamicMesh()->Reset();
//    PlotMesh->GetDynamicMesh()->EditMesh([&](FDynamicMesh3& EditMesh) {
//        EditMesh = Mesh;
//        });
//    PlotMesh->NotifyMeshUpdated();
//}
//
//void ACesiumPlotMeshActor::SnapMeshToTerrain(FDynamicMesh3& Mesh)
//{
//    if (!CesiumTileset || !CesiumGeoreference) {
//        UE_LOG(LogTemp, Warning, TEXT("Missing CesiumTileset or CesiumGeoreference."));
//        return;
//    }
//
//    BoundaryVertexIndices.Empty();
//    for (int32 vid : Mesh.VertexIndicesItr()) {
//        BoundaryVertexIndices.Add(vid);
//    }
//
//    // Build list of boundary positions in cartographic
//    TArray<FVector3d> PositionsToSample;
//
//    for (int32 vid : BoundaryVertexIndices) {
//        FVector3d V = Mesh.GetVertex(vid) +GetActorLocation() ;
//        FVector CesiumCarto = CesiumGeoreference->TransformUnrealPositionToLongitudeLatitudeHeight(FVector(V.X, V.Y, V.Z));
//        PositionsToSample.Add(FVector3d(CesiumCarto.X, CesiumCarto.Y, 0.0));
//    }
//
//    UE_LOG(LogTemp, Log, TEXT("Starting SampleHeightMostDetailed for %d points on tileset: %s"),
//        PositionsToSample.Num(), *CesiumTileset->GetName());
//
//    FCesiumSampleHeightMostDetailedCallback CesiumCallback;
//
//    CesiumCallback.BindLambda(
//        [this, MeshCopy = MoveTemp(Mesh)](ACesium3DTileset* TileSet, const TArray<FCesiumSampleHeightResult>& Results, const TArray<FString>& Warnings) mutable
//        {
//            if (BoundaryVertexIndices.Num() != Results.Num()) {
//                UE_LOG(LogTemp, Error, TEXT("Sampled points count (%d) does not match boundary vertices (%d)!"),
//                    Results.Num(), BoundaryVertexIndices.Num());
//                return;
//            }
//
//            int32 SuccessCount = 0;
//            double LastValidZ = 0.0;
//
//            FVector LastValidWorldLoc = FVector::ZeroVector;
//
//            for (int32 i = 0; i < Results.Num(); ++i) {
//                const FCesiumSampleHeightResult& Result = Results[i];
//                int32 vid = BoundaryVertexIndices[i];
//
//                FVector3d NewPos;
//
//                FVector WorldLoc = CesiumGeoreference->TransformLongitudeLatitudeHeightPositionToUnreal(Result.LongitudeLatitudeHeight);
//
//                if (Result.SampleSuccess) {
//                    LastValidWorldLoc = WorldLoc;
//                    NewPos = FVector3d(WorldLoc.X, WorldLoc.Y, WorldLoc.Z) - GetActorLocation();
//                    SuccessCount++;
//                }
//                else {
//                    UE_LOG(LogTemp, Warning, TEXT("Sample at [%d] lon=%.6f lat=%.6f failed, using last valid point."),
//                        i, Result.LongitudeLatitudeHeight.X, Result.LongitudeLatitudeHeight.Y);
//
//
//                    NewPos = FVector3d(LastValidWorldLoc.X, LastValidWorldLoc.Y, LastValidWorldLoc.Z) - GetActorLocation();
//                }
//
//                MeshCopy.SetVertex(vid, NewPos);
//            }
//
//
//            for (const FString& Warn : Warnings) {
//                UE_LOG(LogTemp, Warning, TEXT("Cesium Warning: %s"), *Warn);
//            }
//
//            if (SuccessCount == 0) {
//                UE_LOG(LogTemp, Error, TEXT("All samples failed. Check if tileset has data at these coordinates or delay sampling."));
//                return;
//            }
//
//            UE_LOG(LogTemp, Log, TEXT("Successfully clamped %d/%d vertices to terrain."), SuccessCount, Results.Num());
//
//            if (bSmooth) {
//                SmoothMesh(MeshCopy);
//            }
//
//            ApplyCraterEffect(MeshCopy);
//
//            CommitMesh(MeshCopy);
//        });
//
//    FTimerHandle TimerHandle;
//    GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, PositionsToSample, CesiumCallback]()
//        {
//            UE_LOG(LogTemp, Log, TEXT("Executing deferred SampleHeightMostDetailed..."));
//            CesiumTileset->SampleHeightMostDetailed(PositionsToSample, CesiumCallback);
//
//        }, 1.0f, false); // 1 second delay
//}
//
//void ACesiumPlotMeshActor::RemoveCraterPolygonAndMesh() {
//
//
//    if (CartographicPolygon) {
//        CartographicPolygon->Destroy();
//
//    }
//
//}
//
//
//
