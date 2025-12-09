// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EntitySensorEmitter.h"
#include "RemoteRadar.generated.h"

UCLASS()
class METAVERSE_API ARemoteRadar : public AEntitySensorEmitter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARemoteRadar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
