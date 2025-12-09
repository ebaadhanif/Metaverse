// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EntityEnvironmental.h"
#include "GameFramework/Actor.h"
#include "RemoteVegetation.generated.h"

UCLASS()
class METAVERSE_API ARemoteVegetation : public AEntityEnvironmental
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARemoteVegetation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
