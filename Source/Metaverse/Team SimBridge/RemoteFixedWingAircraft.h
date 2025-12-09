
#pragma once

#include "CoreMinimal.h"
#include "EntityPlatform.h"
#include "../Team RenderStorm/RibbonMeshActor.h"
#include "../Team RenderStorm//VerticalRibbonMeshActor.h"
#include "../Team RenderStorm/GroundVectorActor.h"
#include "../Team RenderStorm/ForwardVectorActor.h"
#include "../Team RenderStorm/UpwardVector.h"
#include "AppConstEnumStruct.h"        
#include "Components/ChildActorComponent.h"
#include "RemoteFixedWingAircraft.generated.h"


class ARibbonMeshActor;
class AVerticalRibbonMeshActor;
class AGroundVectorActor;
class AForwardVectorActor;
class ANiagaraLockLineActor;
class ANiagaraLockLineRedActor;

UCLASS()
class METAVERSE_API ARemoteFixedWingAircraft : public AEntityPlatform
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
	float StraightRibbonInterval = 0.25f;   

	float TimeSinceStraightVerticalRibbon = 0.f;   
	int32 FramesSinceTurnVerticalRibbon = 0;       


	// Tuning knobs
	float TurnRateVerticalThresholdDegPerSec = 2.f;
	int32 TurnVerticalRibbonFrameInterval = 2;
	float StraightVerticalRibbonInterval = 0.5f;

	// Vertical trail tracking
	FVector PrevJetLocation;
	FVector PrevGroundHit;
	bool bHasPrevVertical = false;

	//UPROPERTY()
	//USettingsDropDown* SettingDropdown;

	UPROPERTY() int32 horizontalTrailWidth = 1800;
	UPROPERTY() int32 verticalTrailHeight = 100000000.f;

	UPROPERTY(EditAnywhere) UStaticMeshComponent* LeftWingCube = nullptr;
	UPROPERTY(EditAnywhere) UStaticMeshComponent* RightWingCube = nullptr;


	UPROPERTY() AForwardVectorActor* ForwardBeamActor = nullptr;
	UPROPERTY() AUpwardVector* UpwardBeamActor = nullptr;
	UPROPERTY(VisibleAnywhere) USceneComponent* rootComp = nullptr;
	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* forwardVectorComponent = nullptr;
	UPROPERTY() UMaterialInterface* ForwardvectorMaterial = nullptr;

	// ChildActorComponents for the beam actors

	UPROPERTY(VisibleAnywhere, Category = "Beams") UChildActorComponent* ForwardBeamCAC = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Beams") UChildActorComponent* UpwardBeamCAC = nullptr;

	bool bShowLOD0 = false;
	bool bShowLOD1 = false;

public:

	UPROPERTY() 
	ARibbonMeshActor* RibbonActor = nullptr;
	UPROPERTY() 
	AVerticalRibbonMeshActor* VerticalTrailActor = nullptr;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Beam")
	UNiagaraComponent* SmokeNiagaraComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Beam")
	UNiagaraComponent* SmokeLeftNiagaraComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Beam")
	UNiagaraSystem* SmokeNiagaraSystem = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Beam")
	UNiagaraComponent* AfterBurnerNiagaraComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Beam")
	UNiagaraSystem* AfterBurnerNiagaraSystem = nullptr;

public:

	ARemoteFixedWingAircraft();

	void SetRibbonmesh(float DeltaTime);
	void SetVerticalTrail(float DeltaTime);



	void setRibbon() override;
	void setVerticalRibbon() override;
	void setForwardVector() override;
	virtual void ResetTrails() override;
	void UpdateLods();

	UFUNCTION(BlueprintCallable, Category = "Beams|Ground")
	void SetGroundRingSpacingMeters(float SpacingMeters);

	UFUNCTION(BlueprintCallable, Category = "Beams|Ground")
	void ApplyGroundBeamConfigMeters(float SpacingMeters, float RadiusMeters, float ThicknessMeters, int32 MaxRings);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void ApplyMode() override;
	virtual void EndPlay(const EEndPlayReason::Type EEndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



private:

	void UpdateForwardBeam(float DeltaTime, const FVector& JetLocation, float SpeedCmPerSec);
	void SetForwardVector(FEntityState entityState);
};
