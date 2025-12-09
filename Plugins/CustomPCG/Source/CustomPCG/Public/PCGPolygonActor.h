#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/BoxComponent.h"
#include "PCGComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "PCGPolygonActor.generated.h"


USTRUCT(BlueprintType)
struct FGrassPolygonData
{
    GENERATED_BODY();

    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") int32 Id;
    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") FString Name;
    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") float Density;
    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") float Area;
    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") float Pnts;
    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") FString Type;
    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") FString Model;
    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") int32 KindID;
    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") FString KindDesc;
    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") int32 DomainID;
    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") FString DomainDesc;
    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") int32 CountryID;
    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") FString CountryDes;
    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") int32 CategoryID;
    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") FString CategoryDe;
    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") int32 SubCategID;
    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") FString SubCategDe;
    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") int32 SpecificID;
    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") FString SpecificDe;
    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") FString EntityEnum;
    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") int32 Scale;
    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") FString Foliage;
    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") FString State;
    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") TArray<FVector> PolygonPoints;
    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") FString FileName;
    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") FVector BoxExtents;

    UPROPERTY(BlueprintReadWrite, Category = "CustomPCG|PolygonData") FVector Center = FVector::ZeroVector;
};

UCLASS()
class CUSTOMPCG_API APCGPolygonActor : public AActor
{
    GENERATED_BODY()

private:
    TArray<UInstancedStaticMeshComponent*> CachedHISM;

public:
    APCGPolygonActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CustomPCG|Components")
    USplineComponent* SplineComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CustomPCG|Components")
    UPCGComponent* PCGComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomPCG|Sampling", meta = (ClampMin = "0.0", UIMin = "0.0"))
    float InteriorSampleSpacing = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomPCG|Sampling", meta = (ClampMin = "0.0", UIMin = "0.0"))
    float InteriorBorderSpacing = 100.f;


    bool isActive = false;

    // UFUNCTION(BlueprintCallable, Category="CustomPCG")
    void ActivatePCG();
    // UFUNCTION(BlueprintCallable, Category="CustomPCG")
    void DeActivatePCG();

    void CachePCGGeneratedComponents();
    void ToggleVisibility(bool bVisible);

    FGrassPolygonData Data;

};
