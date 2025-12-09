// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EntityCulturalFeature.h"
#include "RemoteStructure.generated.h"

UCLASS()
class METAVERSE_API ARemoteStructure : public AEntityCulturalFeature
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARemoteStructure();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
