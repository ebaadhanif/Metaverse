#pragma once
#include "Logging/LogMacros.h"
#include "ProceduralMeshComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Math/UnrealMathUtility.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/WorldSettings.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#define NOMINMAX
#include "CesiumGeoreference.h"
#undef OPAQUE
#include "Cesium3DTileset.h"
#include "KismetProceduralMeshLibrary.h"
#include "CoreMinimal.h"


class AFISEDRAWINGSLOADER_API IShape: public TSharedFromThis<IShape>
{
public:
	virtual ~IShape() {}

	virtual FString GetShapeType() const = 0;
	virtual FVector GetWorldPosition() const = 0;
	virtual FVector GetLatLongHeightPosition() const = 0;
	//virtual FVector GetLatLongHeightPositions() const = 0;


	virtual void LogInfo() const = 0;
	virtual void SetLineColor(const FLinearColor& InColor) = 0;
	virtual void SetLineWidth(int32 InWidth) {};
	virtual void SetLineHeight(int32 InHeight) {};
	virtual void SetFillColor(const FLinearColor& InColor) = 0;
	virtual void Draw(UWorld* World) = 0;
	virtual void SetProjectionVisibility(bool bVisible) = 0;
	virtual void Clear() = 0;
	virtual void SetVisibility(bool bVisible) = 0;
	virtual void CreateMeshes(UWorld* World) = 0;
	virtual void UpdateScale(UWorld* World) = 0;


	static void SetGeoreference(ACesiumGeoreference* InGeoref);
	static ACesiumGeoreference* GetGeoreference();
	static void SetTileset(ACesium3DTileset* InTileset);
	static ACesium3DTileset* GetTileset();
	static void SetWorld(UWorld* InWorld);
	static UWorld* GetWorld();


	void SampleHeightAboveTerrain(
		const TArray<FVector>& LatLongPoints,
		TFunction<void(TArray<FVector>&, TArray<FVector>&)> OnComplete);


protected:
	static ACesiumGeoreference* Georeference;
	static ACesium3DTileset* Tileset;
	static UWorld* ParentWorld;




	FString MaterialPath;
	FString ProjectionMaterialPath = "/Game/Materials/Drawings/M_Plane";

	UMaterialInterface* Material = nullptr;
	UMaterialInstanceDynamic* DynamicMaterial = nullptr;

	UMaterialInterface* ProjectionMaterial = nullptr;
	UMaterialInstanceDynamic* DynamicProjectionMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Components")
	UProceduralMeshComponent* WallMeshComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Components")
	UProceduralMeshComponent* LineMeshComponent = nullptr;


	int32 BaseLineWidth = 1.0f;
	int32 BaseLineHeight = 1.0f;




};





