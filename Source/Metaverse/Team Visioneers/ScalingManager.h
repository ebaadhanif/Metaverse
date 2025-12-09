// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AirBaseManager.h"
#include "../Team Visioneers/Menus/MetaverseMode.h"
#include "Kismet/GameplayStatics.h"
#include "ScalingManager.generated.h"

UENUM(BlueprintType)
enum class EActorType : uint8
{
	EntityModel UMETA(DisplayName = "EntityModel"),
	BaseMarker UMETA(DisplayName = "BaseMarker"),
	EntityLabel UMETA(DisplayName = "EntityLabel"),
};

UENUM(BlueprintType)
enum class ScalingType : uint8
{
	ActualScale UMETA(DisplayName = "ActualScale"),
	ExegeratedScale UMETA(DisplayName = "ExegeratedScale"),
};

UCLASS()
class METAVERSE_API AScalingManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	TObjectPtr<UMetaverseMode> ActiveMode;
	static AScalingManager* GetInstance();
	virtual void Tick(float DeltaTime) override;
	float ScaleActorBasedOnDistance(AActor* Actor, EActorType ActorType, FVector& CameraPosition);
	bool scale = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Markers_Min_Scale = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Markers_Max_Scale = 100000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float entityScaleMultiplier = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float entityLabelScaleMultiplier = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float entityLabelOffsetMultiplier = 1;

	float GetEntityScalingFactor();
	float GetEntityLabelScalingFactor();
	float GetEntityLabelOffsetFactor();
	void SetEntityScalingFactor(Multiplier value);
	void SetEntityLabelScalingFactor(Multiplier value);
	void SetEntityLabelOffsetFactor(Multiplier value);
	void SetEntityScalingType(ScalingType value);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isShowLabel = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ScalingType scalingType;
private:
	AScalingManager();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	static AScalingManager* Instance;
	//FVector CameraPosition1;
	//APlayerController* PC;
	
};
