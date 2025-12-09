// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
#include "EntityBase.h"
#include "EntityPlatform.generated.h"

UCLASS()
class METAVERSE_API AEntityPlatform : public AEntityBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEntityPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
