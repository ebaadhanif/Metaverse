// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EntityExpandables.h"
#include "RemoteFlare.generated.h"

UCLASS()
class METAVERSE_API ARemoteFlare : public AEntityExpandables
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARemoteFlare();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
