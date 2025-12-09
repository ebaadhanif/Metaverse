// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Metaverse/Team Visioneers/Menus/MetaverseMode.h>
#include "ModeManager.generated.h"


UCLASS()
class METAVERSE_API AModeManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AModeManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	static AModeManager* instance;
	static AModeManager* getInstance();
	UPROPERTY()
	TMap<FName, UMetaverseMode*> MetaverseModes;

	UPROPERTY()
	UMetaverseMode* ActiveMode = nullptr;

	//Functions
	bool LoadModesFromConfig(const FString& ConfigFileFolder, const FString& AppConfigFile);
	UMetaverseMode* getActiveMode();

	void setActiveMode(UMetaverseMode* activeMode);

	//Tick
	virtual void Tick(float DeltaTime) override;

};
