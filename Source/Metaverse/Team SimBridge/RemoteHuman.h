// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include"EntityLifeForm.h"
#include "RemoteHuman.generated.h"

UCLASS()
class METAVERSE_API ARemoteHuman : public AEntityLifeForm
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARemoteHuman();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
