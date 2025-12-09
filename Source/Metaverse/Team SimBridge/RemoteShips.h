// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EntityPlatform.h"
#include "RemoteShips.generated.h"

UCLASS()
class METAVERSE_API ARemoteShips : public AEntityPlatform
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARemoteShips();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
