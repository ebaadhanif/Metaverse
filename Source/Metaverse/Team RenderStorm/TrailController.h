// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrailController.generated.h"

UCLASS()
class METAVERSE_API ATrailController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrailController();
	void toggleTrailVisibility(bool isVisible);
	void toggleVerticalTrailVisisbility(bool isVisible);
	void toggleForwardVectors(bool isVisible);
	void toggleGroundVectors(bool isVisible);
	void toggleUpVectors(bool isVisible);

	void ToggleHeightRing(bool isVisible);


	bool bIsVisible = true;
	bool bIsVerticalVisible = true;

	UWorld* World = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
