// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include"EntityMunition.h"
#include "../Team RenderStorm/RibbonMeshActor.h"
#include "../Team RenderStorm//VerticalRibbonMeshActor.h"
#include "../Team RenderStorm/GroundVectorActor.h"
#include "../Team RenderStorm/ForwardVectorActor.h"
#include "../Team RenderStorm/UpwardVector.h"
#include "AppConstEnumStruct.h"        
#include "Components/ChildActorComponent.h"
#include "../Team Visioneers/Menus/SettingsDropDown.h"
#include "RemoteMissile.generated.h"



class ARibbonMeshActor;
class AVerticalRibbonMeshActor;
class AGroundVectorActor;
class AForwardVectorActor;


UCLASS()
class METAVERSE_API ARemoteMissile : public AEntityMunition
{
	GENERATED_BODY()

private:
	FRotator currentRotation;
	FVector LastJetDir = FVector::ForwardVector;
	FVector PrevLeft, PrevRight;
	bool bHasPreviousPoints = false;
	FRotator PrevActorRot;
	bool bHavePrevRot = false;
	float TimeSinceStraightRibbon = 0.f;
	int32 FramesSinceTurnRibbon = 0;


	// Tuning knobs
	float TurnRateThresholdDegPerSec = 2.f;
	float MinWingPointDelta = 1.0f;
	int32 TurnRibbonFrameInterval = 2;
	float StraightRibbonInterval = 1.0f;

	float TimeSinceStraightVerticalRibbon = 0.f;
	int32 FramesSinceTurnVerticalRibbon = 0;


	// Tuning knobs
	float TurnRateVerticalThresholdDegPerSec = 2.f;
	int32 TurnVerticalRibbonFrameInterval = 2;
	float StraightVerticalRibbonInterval = 1.0f;

	// Vertical trail tracking
	FVector PrevJetLocation;
	FVector PrevGroundHit;
	bool bHasPrevVertical = false;

	//UPROPERTY()
	//USettingsDropDown* SettingDropdown;

	UPROPERTY() ARibbonMeshActor* RibbonActor = nullptr;
	UPROPERTY() AVerticalRibbonMeshActor* VerticalTrailActor = nullptr;

	UPROPERTY() int32 horizontalTrailWidth = 1800;
	UPROPERTY() int32 verticalTrailHeight = 100000000.f;

	UPROPERTY(EditAnywhere) UStaticMeshComponent* LeftWingCube = nullptr;
	UPROPERTY(EditAnywhere) UStaticMeshComponent* RightWingCube = nullptr;
	UPROPERTY() AForwardVectorActor* ForwardBeamActor = nullptr;
	UPROPERTY() AUpwardVector* UpwardBeamActor = nullptr;
	UPROPERTY(VisibleAnywhere) USceneComponent* rootComp = nullptr;
	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* forwardVectorComponent = nullptr;
	UPROPERTY() UMaterialInterface* ForwardvectorMaterial = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Beams") UChildActorComponent* ForwardBeamCAC = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Beams") UChildActorComponent* UpwardBeamCAC = nullptr;


public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beams|Forward")
	float ForwardLookAheadSeconds = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beams|Forward")
	float ForwardDistanceMin = 10000.f;     // cm

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beams|Forward")
	float ForwardDistanceMax = 2000000.f;   // cm

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beams|Forward")
	bool bUseForwardDistanceOverride = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beams|Forward", meta = (ClampMin = "0.0"))
	float ForwardDistanceOverrideCm = 0.f;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	ARemoteMissile();
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EEndPlayReason) override;
	UFUNCTION(BlueprintCallable, Category = "Beams|Ground")
	void SetGroundRingSpacingMeters(float SpacingMeters);

	UFUNCTION(BlueprintCallable, Category = "Beams|Ground")
	void ApplyGroundBeamConfigMeters(float SpacingMeters, float RadiusMeters, float ThicknessMeters, int32 MaxRings);

	void SetRibbonmesh(float DeltaTime);
	void SetVerticalTrail(float DeltaTime);

	void setRibbon() override;
	void setVerticalRibbon() override;
	void setForwardVector() override;
	virtual void ResetTrails() override;
	virtual void ApplyMode() override;

	void UpdateForwardBeam(float DeltaTime, const FVector& JetLocation, float SpeedCmPerSec);
	void SetForwardVector(FEntityState entityState);


};
