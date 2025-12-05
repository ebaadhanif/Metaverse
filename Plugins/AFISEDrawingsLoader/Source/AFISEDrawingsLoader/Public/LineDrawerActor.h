// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "ProceduralMeshComponent.h"
#include "LineDrawerActor.generated.h"

UCLASS()
class AFISEDRAWINGSLOADER_API ALineDrawerActor : public AActor
{
	GENERATED_BODY()

public:
	ALineDrawerActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// Spline component to define the line path
	UPROPERTY(VisibleAnywhere, Category = "Spline")
	USplineComponent* SplineComponent;

	// Array to hold spline mesh components
	UPROPERTY(VisibleAnywhere, Category = "Spline")
	TArray<USplineMeshComponent*> SplineMeshComponents;

	// Function to update the spline mesh along the spline points
	void UpdateLine(const TArray<FVector>& Points, UMaterialInterface* Material);


private:
	// Function to create spline meshes along the spline
	void CreateSplineMeshes(UMaterialInterface* Material);

	void SpawnSphereAtLocation(UWorld* World, const FVector& Location);

	UPROPERTY()
	UProceduralMeshComponent* ProceduralMesh = nullptr;


};
