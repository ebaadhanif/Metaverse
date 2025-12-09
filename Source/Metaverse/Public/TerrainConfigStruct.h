#pragma once
#include "CoreMinimal.h"
#include "TerrainConfigStruct.generated.h"

/** Overlay configuration for 3D Tilesets */
USTRUCT(BlueprintType)
struct FOverlayConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overlay")
    FString Url;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overlay")
    int32 MinZoom;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overlay")
    int32 MaxZoom;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overlay")
    bool SpecifyZoomLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overlay")
    FString MaterialLayerKey;
};

/** 3D Tileset configuration for an asset */
USTRUCT(BlueprintType)
struct F3DTilesetConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "3D Tileset")
    FString Url;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "3D Tileset")
    TArray<FOverlayConfig> Overlays;
};

/** Cesium ION configuration for an asset */
USTRUCT(BlueprintType)
struct FCesiumIONConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cesium ION")
    int32 CesiumIONAssetID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cesium ION")
    FString CesiumIONAccessToken;
};

/** Asset configuration inside a terrain */
USTRUCT(BlueprintType)
struct FAssetConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asset")
    int32 ID; // Asset ID

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asset")
    FString Name; // Asset Name

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asset")
    FString Type; // Asset Type

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asset")
    F3DTilesetConfig TilesetConfig;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asset")
    FCesiumIONConfig CesiumIONConfig;
};


/** Georeference information for a terrain */
USTRUCT(BlueprintType)
struct FGeoreferenceConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Georeference")
    float Longitude;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Georeference")
    float Latitude;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Georeference")
    float Height;
};

/** Terrain configuration */
USTRUCT(BlueprintType)
struct FTerrainConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain")
    int32 ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain")
    FString Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain")
    FGeoreferenceConfig Georeference;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain")
    TArray<FAssetConfig> Assets;
};

/** Main configuration for terrains */
USTRUCT(BlueprintType)
struct FTerrainConfiguration
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
    int32 ActiveTerrainID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
    TArray<FTerrainConfig> Terrains;
};
