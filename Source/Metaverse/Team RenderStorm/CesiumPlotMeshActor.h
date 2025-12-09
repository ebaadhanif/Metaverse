//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "DynamicMesh/DynamicMesh3.h"
//#include "Components/DynamicMeshComponent.h"
//#include "ProceduralMeshComponent.h"
//#include "CesiumCartographicPolygon.h"
//#include "CesiumPolygonRasterOverlay.h"
//#include "CesiumPlotMeshActor.generated.h"
//
//
//class UDynamicMeshComponent;
//class ACesiumCartographicPolygon;
//class ACesium3DTileset;
//class UMaterialInterface;
//class USplineComponent;
//
//
//UCLASS()
//class METAVERSE_API ACesiumPlotMeshActor : public AActor
//{
//    GENERATED_BODY()
//
//public:
//    ACesiumPlotMeshActor();
//
//    virtual void BeginPlay() override;
//
//
//    void UpdatePlotMeshForPolygon();
//    TArray<FVector> GetPolygonMeshVertices();
//    void SmoothMesh(FDynamicMesh3& Mesh);
//    void CommitMesh(FDynamicMesh3& Mesh);
//    void SnapMeshToTerrain(FDynamicMesh3& Mesh);
//    void RemoveCraterPolygonAndMesh();
//
//    ACesiumCartographicPolygon* CreateCraterPolygonOnOverlay(UCesiumPolygonRasterOverlay* SharedOverlay);
//
//
//protected:
//    void BuildMeshFromPolygon(FDynamicMesh3& Mesh, const TArray<FVector>& Poly);
//    void ApplyCraterEffect(FDynamicMesh3& Mesh);
//
//    FVector ComputePolygonCenter(const TArray<FVector>& Points);
//
//public:
//    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
//    TObjectPtr<UDynamicMeshComponent> PlotMesh;
//
//    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
//    TObjectPtr<USceneComponent> DefaultSceneRoot;
//
//    UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
//    TObjectPtr<ACesiumCartographicPolygon> CartographicPolygon;
//
//    UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
//    TObjectPtr<ACesium3DTileset> CesiumTileset;
//
//    UPROPERTY(EditAnywhere)
//    ACesiumGeoreference* CesiumGeoreference;
//
//    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
//    TObjectPtr<UMaterialInterface> PlotMeshMaterial;
//
//    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
//    bool bFlatPlotMeshOnly = false;
//
//    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
//    bool bUsePlotMesh = true;
//
//    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
//    double DitchRadius = 5000;
//
//    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
//    FVector DitchCenter;
//
//    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
//    double BlendRadius = 1000;
//
//    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
//    double MaxDepth = -3000;
//
//    bool bSmooth = true;
//    bool bFlat = true;
//
//    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crater")
//    double RimWidth = 4000.0;
//
//    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crater")
//    double MaxRimHeight = 1000.0;
//
//    TArray<int32> BoundaryVertexIndices;
//
//
//
//};
