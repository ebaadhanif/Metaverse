// Fill out your copyright notice in the Description page of Project Settings.


#include "PCGPolygonActor.h"

// Sets default values
APCGPolygonActor::APCGPolygonActor()
{

	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SplineComponent->SetupAttachment(RootComponent);
	// SplineComponent->SetMobility(EComponentMobility::Static);
	SplineComponent->PrimaryComponentTick.bCanEverTick = false;
	PCGComponent = CreateDefaultSubobject<UPCGComponent>(TEXT("PCGComponent"));
	InteriorSampleSpacing = 100.0f;
}

void APCGPolygonActor::ActivatePCG()
{
	if (isActive) return;
	PCGComponent->Generate();
	isActive = true;
}

void APCGPolygonActor::DeActivatePCG()
{
	if (!isActive) return;
	PCGComponent->CleanupLocal(true, true);
	isActive = false;
}

void APCGPolygonActor::CachePCGGeneratedComponents() {
	
	for (UActorComponent* Comp : GetComponents())
	{
		if (auto* HISMC = Cast<UHierarchicalInstancedStaticMeshComponent>(Comp)) {
			CachedHISM.Add(HISMC);
		}
		else if (auto* ISMC = Cast<UInstancedStaticMeshComponent>(Comp)) {
			CachedHISM.Add(ISMC);
		}
	}
}

void APCGPolygonActor::ToggleVisibility(bool bVisible) {
	for (auto& Component : CachedHISM)
	{
		Component->SetVisibility(bVisible, true);
		Component->SetHiddenInGame(!bVisible);
	}
}



