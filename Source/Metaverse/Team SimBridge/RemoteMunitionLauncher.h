// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EntityPlatform.h"
#include "RemoteMunitionLauncher.generated.h"

UCLASS()
class METAVERSE_API ARemoteMunitionLauncher : public AEntityPlatform
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARemoteMunitionLauncher();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
