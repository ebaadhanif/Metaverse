// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#undef OPAQUE
#include "Cesium3DTileset.h"
#include "CesiumGeoreference.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Kismet/GameplayStatics.h"
#include "CesiumGlobeAnchorComponent.h"
#include "CesiumGeospatial/CartographicPolygon.h"
#include "CesiumPolygonRasterOverlay.h"
#include "Blank_3D_Tileset.h"
#include "SplatMapping.generated.h"


UCLASS()
class METAVERSE_API ASplatMapping : public AActor
{
	GENERATED_BODY()
	
public:	
	ASplatMapping();
	static ASplatMapping* GetInstance();
	ACesiumCartographicPolygon* GetOrCreatePolygon(const FString& PolygonKey, const TArray<FVector>& AdjustedVertices);
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void SetPolygonOverlaysVisible(bool isVisible);

protected:
	static ASplatMapping* Instance;

	virtual void BeginPlay() override;

	void ApplyMaterialToTilesets(UMaterialInterface* InMaterialToApply);

	void LoadShapeFilesAndApplySplatMaps(Blank_3D_Tileset* TerrainAsset);

	void CreateParentSplatActor();

	TArray<TWeakObjectPtr<ACesium3DTileset>> TargetTilesets;

	UCesiumPolygonRasterOverlay* GetOrCreatePolygonRasterOverlay(ACesium3DTileset* Tileset, const FString &MaterialLayerKey);

	//UPROPERTY(EditAnywhere)
	//UMaterialInterface* PolygonMaterial;

	UPROPERTY(EditAnywhere)
	ACesiumGeoreference* CesiumGeoreference;

	UPROPERTY(EditAnywhere)
	UCesiumPolygonRasterOverlay* PolygonRasterOverlay;

	UMaterialInterface* MaterialToApply;
	UMaterialInstanceDynamic* test;

	AActor* ParentActor;

	bool bCesiumOverlayInUse = false;
	bool bIsShuttingDown = false;

	TMap<FString, UCesiumPolygonRasterOverlay*> MaterialToOverlayMap;
	TMap<TWeakObjectPtr<ACesium3DTileset>, TMap<FString, UCesiumPolygonRasterOverlay*>> OverlaysByTileset;
	TArray<TerrainAssets> TargetedAssets;
	TMap<FString, ACesiumCartographicPolygon*> PolygonCache;
	TArray<FName> LayerKeys;


};
