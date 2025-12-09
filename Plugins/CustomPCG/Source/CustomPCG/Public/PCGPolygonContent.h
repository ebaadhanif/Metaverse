#pragma once
#include "CoreMinimal.h"
#include "PCGContent.h"
#include "Components/SplineComponent.h"
#include "PCGComponent.h"
#include "PCGPolygonActor.h"
#include "PolygonHiGenActor.h"
#include "PCGPolygonContent.generated.h"



USTRUCT()
struct FBakedInstanceBatch
{
    GENERATED_BODY();

    UPROPERTY(SaveGame) FSoftObjectPath MeshPath;
    UPROPERTY(SaveGame) TArray<FSoftObjectPath> Materials;
    UPROPERTY(SaveGame) TArray<FTransform> Transforms;
};


UCLASS()
class CUSTOMPCG_API APCGPolygonContent : public APCGContent
{
    GENERATED_BODY()

private:

    TArray<TObjectPtr<APCGPolygonActor>> PolygonActors;
    TArray<TObjectPtr<APolygonHiGenActor>> PolygonHiGenActors;

public:

    APCGPolygonContent();

    virtual void BeginPlay() override;

    virtual void InitializeContent() override;

    virtual void Tick(float DeltaTime) override;

    void InitializePCGPolygonData(const FShapeRawData& Raw);

    bool InsertPolygonsFeaturesToDB(const FString& ShapefileID);

    bool InsertPolygonFeaturesToDB(const FGrassPolygonData& Data);

    void SpawnPCGPolygonData();

    void SpawnIndividualPCGPolygonData(const FGrassPolygonData& Data);

    void AssignPCGGraph(UPCGComponent* TargetPCG, const FString& GraphName);

    void ExtractPointsDataFromPCGGraph(UPCGComponent* PCG);

    bool InsertPolygonPointsDataToDB(const FString& ShapefileID, FGrassPolygonData Data, const TMap<int32, FTransform>& SeedToTransformMap);

    bool InsertPolygonPointsToDB(const FString& ShapefileID, FGrassPolygonData PolygonID, const TArray<FTransform>& Instances, const FString& MeshID);

    UFUNCTION()
    void OnPcgGraphGenerated(UPCGComponent* PCG);

    void LoadPolygonDataFromDatabase(const FString& ShapefileName);

    void SpawnIndividualHiGenActor(
        const FString& ShapeFileID,
        const TMap<int32, TArray<FVector>>& PolygonPointsMap,
        const TMap<int32, FString>& PolygonGraphMap,
        const TMap<int32, FVector>& PolygonBoxExtentsMap,
        const TMap<int32, FVector>& PolygonCenterMap);

    virtual void ToggleVisibility(bool bVisible) override;

    TArray<FGrassPolygonData> PolygonDataList;
    FTimerHandle handle;
};
