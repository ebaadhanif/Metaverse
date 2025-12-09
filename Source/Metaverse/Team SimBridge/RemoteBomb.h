// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EntityMunition.h"
#include "RemoteBomb.generated.h"

UCLASS()
class METAVERSE_API ARemoteBomb : public AEntityMunition
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARemoteBomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
