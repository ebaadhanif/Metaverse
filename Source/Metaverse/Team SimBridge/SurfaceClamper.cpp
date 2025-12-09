// Fill out your copyright notice in the Description page of Project Settings.


#include "SurfaceClamper.h"
#include "EntityBase.h"

SurfaceClamper::SurfaceClamper()
{
}

SurfaceClamper* SurfaceClamper::m_SurfaceClamperInstance = NULL;
SurfaceClamper* SurfaceClamper::GetSurfaceClamperInstance()
{
	if (m_SurfaceClamperInstance == nullptr)
	{
		m_SurfaceClamperInstance = new SurfaceClamper();
	}
	return m_SurfaceClamperInstance;
}

FVector SurfaceClamper::GroundClampEntity(FVector Actorlocation, AEntityBase* entityPtr, UWorld* world)
{
	float TraceDistance = 100000.0f;  //Default Trace Distance
	float GroundOffset = 1000.0f;    //Default offset above ground

	FVector Start = Actorlocation + FVector(0, 0, GroundOffset);
	FVector End = Start + FVector(0.0f, 0.0f, -TraceDistance);

	//setting up line trace parameters
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(entityPtr);
	TArray<AActor*, FDefaultAllocator> children;
	entityPtr->FindAllChildActors(entityPtr, children);
	QueryParams.AddIgnoredActors(children);
	//TSet<UActorComponent*> childComponents;
	//childComponents = entityPtr->SetActorEnableCollision(false);
	entityPtr->SetActorEnableCollision(false);
	//QueryParams.AddIgnoredComponents()

	bool bHit = world->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility,
		QueryParams
	);

	if (bHit)
	{
		FVector NewLocation = HitResult.Location;// +FVector(0.0f, 0.0f, GroundOffset);
		return NewLocation;
	}

	return Start;
}



SurfaceClamper::~SurfaceClamper()
{
}
