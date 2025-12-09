// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PCGContent.h"
#include "BlueprintRegistery.h"
#include "Engine/Blueprint.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "HAL/ThreadSafeCounter.h"
#include "PCGPointContent.generated.h"

USTRUCT(BlueprintType)
struct FVegetationPointData
{
	GENERATED_BODY();

	// Category groups pins on Make/Break struct nodes and satisfies the Engine-module rule.
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") int32 Id;
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") FString Name;
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") double Lat;
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") double Long;
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") float Elev;
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") float Height;
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") float Scale;
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") float Rotation;
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") FString Code;
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") FString Model;
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") FString State;
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") float Altitude;
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") int32 KindID;
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") FString KindDesc;
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") int32 DomainID;
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") FString DomainDesc;
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") int32 CountryID;
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") FString CountryDes;
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") int32 CategoryID;
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") FString CategoryDe;
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") int32 SubCategID;
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") FString SubCategDe;
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") int32 SpecificID;
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") FString SpecificDe;
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") FString EntityEnum;
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") FVector Location;
	UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PointData") FString FileName;
};


USTRUCT()
struct FCullRange {
	GENERATED_BODY();

	UPROPERTY() int32 Start = 0;
	UPROPERTY() int32 End = 20000;
	FCullRange() {}
	FCullRange(int32 inStart, int32 inEnd) : Start(inStart), End(inEnd) {}
};

UENUM(BlueprintType)
enum class EVegetationCategory : uint8 {
	Shrub UMETA(DisplayName = "Shrub"),
	Tree  UMETA(DisplayName = "Tree"),
	RockPile UMETA(DisplayName = "RockPile"),
	Bushes UMETA(DisplayName = "Bushes"),
	Other UMETA(DisplayName = "Other")
};

USTRUCT()
struct FLoadedTileInfo{
	GENERATED_BODY()

	int32 TileX = 0;
	int32 TileY = 0;
	UPROPERTY()
	AActor* ParentActor = nullptr;
	UPROPERTY()
	TMap<FString, UInstancedStaticMeshComponent*> InstancedMeshMap;
	

};
UCLASS()
class CUSTOMPCG_API APCGPointContent : public APCGContent
{
	GENERATED_BODY()

private:
	TMap<EVegetationCategory, FCullRange> CullByCategory;
	virtual void BeginPlay() override;


protected:

	bool bStreamingEnabled = false;
	float QueryRadiusKm = 5.0f;
	float MinRequeryDistanceKm = 1.0f;

	bool bHasLastQueryCenter = false;
	double LastQueryLat = 0.0;
	double LastQueryLon = 0.0;

	FString StreamingShapeFileId;

	void EnsurePointsDataSpatialIndices();
	void RequestPointsInRadiusAsync();

	void OnPointsLoadedFromDB(TArray<FVegetationPointData>&& Results);
	void ClearAllSpanwnedInstances();
	static double Haversinekm(double Lat1Deg, double Lon1Deg, double Lat2Deg, double Lon2Deg);

	TMap<FIntPoint, FLoadedTileInfo> LoadedTiles;
	TSet<FIntPoint> PendingTileLoads;

public:
	APCGPointContent();

	virtual void Tick(float DeltaSeconds) override;
	void ComputerDesiredTiles(TSet<FIntPoint>& OutDesiredTiles) const;
	void UpdateStreamingTiles();
	void RequestTileAsync(const FIntPoint& TileKey);
	void OnTilesPointLoaded_GameThread(const FIntPoint& TileKey, TArray<FVegetationPointData>&& TilePoints);
	void SpawnTilePoints(const FIntPoint& TileKey, TArray<FVegetationPointData>& TilePoints);
	void UnloadTile(const FIntPoint& TileKey);
     void EnableStreaming(bool bInStreaming, float InRadiusKm = 5.0f, float InMinRequery = 1.0f);
	void SetStreamingShapeFileId(FString InStreamingShapeFileID);
	TArray<FVegetationPointData> PointDataList;
	virtual void InitializeContent() override;
	void InitializePCGPointData(const FShapeRawData& Raw);
	void SpawnPCGPointDataOfDatabase();
	void SpawnPCGPointData_CesiumSamplerBatched();
	UStaticMesh* GetOrLoadMeshForType_GameThread(const FString& CleanedName);
	UInstancedStaticMeshComponent* GetOrCreateHISM_GameThread(const FString& CleanedName, UStaticMesh* Mesh);
	bool InsertPointDataFeaturesToDB(const FVegetationPointData& Data);
	void LoadPointDataFromDatabase(const FString& ShapefileID);
	void SetCullDistance(float distanceInMeters);
	UStaticMesh* ExtractMeshFromBlueprint(TSubclassOf<AActor> BPClass);
	virtual void ToggleVisibility(bool bVisible) override;
	UPROPERTY() UBlueprintRegistery* BlueprintRegistry = nullptr;

	UPROPERTY() TMap<FString, UStaticMesh*> StaticMeshesPerType;
	UPROPERTY() TMap<FString, UInstancedStaticMeshComponent*> InstancedMeshMap;


	//static int32     TotalPointDataPoints;
	//static FDateTime StartTime;
	//static int32     ExpectedTotalPoints;
	//static bool      bTimerStarted;

	int32     TotalFailedPoints = 0;
	int32     TotalSuccessPoints = 0;
	EVegetationCategory GetCategoryForModel(const FString& SubCategDes);
	void PreWarmMeshesFromRegistry(UWorld* World, UBlueprintRegistery* Registery);
	TAtomic<int32> PendingCesiumBatches;

private:
	static bool bGlobalMeshesInitialized;
	static TMap<FString, UStaticMesh*> GlobalMeshesPerType;
	TArray<FVegetationPointData> FailedSamplePoints;


public:
	//-----------Extra functions/members----------
	// static TWeakObjectPtr<AActor> GlobalParentActor;
	// static TMap<FString, UInstancedStaticMeshComponent*> GlobalInstancedMeshMap;
	// static AActor* GetOrCreateGlobalParentActor(UWorld* World);
    //void SpawnPCGPointData();
	//void SpawnPointDataOnTerrainUsingElevData_HISM(const FVegetationPointData& Data);
	//void SpawnPointDataOnTerrainUsingCesiumSampler(const FVegetationPointData& Data);
	//void SpawnPointDataOnTerrainUsingElevData(const FVegetationPointData& Data);
	//void ReSampleFailedPointsAndSpawnPCGPointData_CesiumSamplerBatched();
	//void SpawnPointDataOnTerrainUsingCesiumSampler_HISM(FVegetationPointData& Data);

};
