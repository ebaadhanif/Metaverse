// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EntityBase.h"
#include "EntityMunition.generated.h"

UCLASS()
class METAVERSE_API AEntityMunition : public AEntityBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEntityMunition();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
