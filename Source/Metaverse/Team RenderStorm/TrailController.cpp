// Fill out your copyright notice in the Description page of Project Settings.


#include "TrailController.h"
#include  "Engine/World.h"
#include "EngineUtils.h"
#include "../Team RenderStorm//RibbonMeshActor.h"
#include "../Team RenderStorm/VerticalRibbonMeshActor.h"
#include "../Team RenderStorm/ForwardVectorActor.h"
#include "../Team RenderStorm/GroundVectorActor.h"
#include "UpwardVector.h"

// Sets default values
ATrailController::ATrailController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	World = GetWorld();
}


void ATrailController::toggleTrailVisibility(bool IsVisible)
{
	
		for (TActorIterator<ARibbonMeshActor> It(World); It; ++It) {
			ARibbonMeshActor* Trail = *It;
			if (Trail)
			{
				Trail->SetActorHiddenInGame(!IsVisible);
				Trail->SetTrailVisibility(IsVisible);
				//Trail->Destroy();

			}
			
		}


		//for (TActorIterator<AVerticalRibbonMeshActor> It(GetWorld()); It; ++It) {
		//	AVerticalRibbonMeshActor* Trail = *It;
		//	if (Trail)
		//	{
		//		Trail->SetActorHiddenInGame(!IsVisible);
		//		Trail->SetTrailVisibility(!IsVisible);
		//		//Trail->Destroy();
		//	}

		//}

		/*bIsVisible = !bIsVisible;*/
}

void ATrailController::toggleVerticalTrailVisisbility(bool IsVisible)
{
	//for (TActorIterator<ARibbonMeshActor> It(GetWorld()); It; ++It) {
	//	ARibbonMeshActor* Trail = *It;
	//	if (Trail)
	//	{
	//		Trail->SetActorHiddenInGame(!IsVisible);
	//		Trail->SetTrailVisibility(!IsVisible);
	//		//Trail->Destroy();

	//	}

	//}


	for (TActorIterator<AVerticalRibbonMeshActor> It(World); It; ++It) {
		AVerticalRibbonMeshActor* Trail = *It;
		if (Trail)
		{
			Trail->SetActorHiddenInGame(!IsVisible);
			Trail->SetTrailVisibility(IsVisible);
			//Trail->Destroy();
		}

	}

	//bIsVerticalVisible = !bIsVerticalVisible;
}

void ATrailController::toggleForwardVectors(bool isVisible)
{
	for (TActorIterator<AForwardVectorActor> It(World); It; ++It) {
		AForwardVectorActor* Forwardvector = *It;
		if (Forwardvector)
		{
			Forwardvector->SetActorHiddenInGame(!isVisible);
			Forwardvector->SetVectorVisibility(isVisible);
			//Trail->Destroy();
		}

	}
}

void ATrailController::toggleGroundVectors(bool isVisible)
{
	for (TActorIterator<AGroundVectorActor> It(World); It; ++It) {
		AGroundVectorActor* Groundvector = *It;
		if (Groundvector)
		{
			Groundvector->SetActorHiddenInGame(!isVisible);
			Groundvector->SetVectorVisibility(isVisible);
			//Trail->Destroy();
		}

	}
}

void ATrailController::toggleUpVectors(bool isVisible)
{
	for (TActorIterator<AUpwardVector> It(World); It; ++It) {
		AUpwardVector* Upwardvector = *It;
		if (Upwardvector)
		{
			Upwardvector->SetActorHiddenInGame(!isVisible);
			Upwardvector->SetVectorVisibility(isVisible);
			//Trail->Destroy();
		}

	}
}

void ATrailController::ToggleHeightRing(bool isVisible) {
	for (TActorIterator<AGroundVectorActor> It(World); It; ++It) {
		AGroundVectorActor* Groundvector = *It;
		if (Groundvector)
		{
			Groundvector->ToggleHeightRingVisibility(isVisible);
			//Trail->Destroy();
		}

	}
}

// Called when the game starts or when spawned
void ATrailController::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();
	
}

// Called every frame
void ATrailController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

