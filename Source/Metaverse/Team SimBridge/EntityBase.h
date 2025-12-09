// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AppConstEnumStruct.h"
#include "CesiumGeoreference.h"
//#include "CesiumRayIntersection.h"
#include "CesiumGlobeAnchorComponent.h"
#include "EntityManager.h"
#include "Components/WidgetComponent.h"
#include "SurfaceClamper.h"
#include "Components/MaterialBillboardComponent.h"
#include "Mil2525Manager.h"
#include "../Team RenderStorm/NiagaraLockLineActor.h"
#include "../Team RenderStorm/NiagaraLockLineRedActor.h"
#include <Kismet/GameplayStatics.h>
#include "Components/StaticMeshComponent.h"
#include "../Team Visioneers/EntityListUI.h"
#include "../Team Visioneers/ScalingManager.h"
#include "Components/TextBlock.h"
#include "FCircle.h"
#include "Templates/Function.h"
#include <Metaverse/Team RenderStorm/GroundVectorActor.h>
#include "EntityBase.generated.h"


class ALoadingManager;
class UModel3DAssetManager;
class UModel3DAsset;

UCLASS()
class METAVERSE_API AEntityBase : public AActor
{
	GENERATED_BODY()

protected:
	ALoadingManager* _loadingManager;
	UModel3DAssetManager* _uModel3DAssetManager;
	FEntityID EntityId;
	FEntityType entityType;
	ERemoteEntityType RemoteEntityType;
	FRotator WorldOrientation;
	FVector GeodeticLocation;
	FVector WorldLocation;
	FString CallSign;
	EForceType ForceType;
	TArray<FEntityID> TrackedEntitiesList;
	TArray<FEntityID> LockedEntitiesList;
	ELocalHealth Health= ELocalHealth::NO_DAMAGE;
	ELocalHealth PreHealth = ELocalHealth::NO_DAMAGE;
	int RadarRange;
	int WeightOnWheels;
	bool isLandingGearExtended;
	bool isNavLightsOn;
	/// <ground clamp>
	bool GroundClamp;
	bool isGroundEntity = false;
	ACesium3DTileset* CesiumTileset;
	double lastClampTime = 0;
	void GroundClampEntity(FEntityState entityState);
	/// </ground clamp>

	int showHideTracker = 202;
	float FramesTime = 0.f;
	int showHideTrackerOnDestroy = 102;
	ACesiumGeoreference* Georeference;
	UCesiumGlobeAnchorComponent* GlobeAnchor;


	double GroundEntityHeightValueFromGround=0.0f;

	bool showLockLines = true;
	bool showTrail = true;
	bool showVerticalTrail = true;
	bool isSensorOn = false;
	ELockLineType LockLineType = ELockLineType::All;
	float FrameTime;
	bool bisBattlespaceModeEnabled;
	UMaterialInterface* BattlespaceMaterial = nullptr;
	UMaterialInstanceDynamic* BattlespaceDynamicInstanceMaterial = nullptr;
	UMaterialBillboardComponent* Billboard;
	UMaterialInterface* BillbordMaterial = nullptr;
	UPROPERTY()
	UMaterialInstanceDynamic* BillboardDynamicMaterial = nullptr;
	FMaterialSpriteElement SpriteElement;
	
	float DesiredScreenSize = 8.0f;

	bool BillboardVisibilityState = true;
	short speedInKnots;

	APlayerCameraManager* CameraManager;
	FVector2D ViewportSize;

	UPROPERTY() AGroundVectorActor* GroundBeamActor = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Beams") UChildActorComponent* GroundBeamCAC = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beams|Ground")
	float GroundRingSpacing = 100000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beams|Ground")
	float GroundRingRadius = 3000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beams|Ground")
	float GroundRingThicknessCm = 5000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beams|Ground")
	int32 GroundMaxRings = 2048;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beams|Ground")
	bool bApplyGroundBeamConfigEveryTick = true;


	// -- Blink States -- //
	FTimerHandle BlinkToggleHandle;
	FTimerHandle BlinkEndHandle;
	bool bBlinkHiddenState = false;
	bool bIsBlinking = false;
	bool bIsPositioned = false;

	void StartBlink(float durationSeconds, float intervalSeconds);
	void StopBlink(bool bEnsureVisible = true);
	void toggleBlink();
	void OnBlinkEnd();

	//Sound
	void PlayEntitySound();
	void StopEntitySound();

	//Locklines
	void setLockLines();
	void setRedLockLines();
	void destroyLockLines();


	void ShowOpposingLocklines() { LockLineType = ELockLineType::OpposingOnly; }
	void ShowSameLocklines() { LockLineType = ELockLineType::SameOnly; }

	void ShowAllLocklines() { LockLineType = ELockLineType::All; }
	void SetLockLinesEnabled(bool bEnable);

	void UpdateLockLinesInternal(bool bUseRed);



	void onEntitySpawn();
	void onEntityDestroy();
	void DestroyeModel();

public:
	
	AActor* DamagedActors_Parent;
	AActor* DestroyedActors_Parent;
	AActor* ModelParent;
	AActor* DefaultPaperMesh;
	TArray<TArray<AActor*>> LODsChilds;
	TArray<UMaterialInterface*> ActorsMaterialsList;
	UTexture2D* IRTexture;

	//Effects Map
	UPROPERTY()
	TMap<FName, UNiagaraComponent*> EffectsRegistry;
	//Effects Map
	UPROPERTY()
	TMap<FName, UAudioComponent*> SoundRegistry;

	//Sound asset
	UAudioComponent* FireSound = nullptr;
	UAudioComponent* EntitySoundd = nullptr;

	//model dimensions
	float entityHeight=1;
	float entityWidth=1;
	float entityLength=1;


	//

	UPROPERTY()
	AActor* Battlespace_Actor;

	TArray<AActor*> LODParentActors;
	
	TArray<AActor*> DamagedActors;
	TArray<AActor*> DestroyedActors;
	TArray<AActor*> BattlespceChildActors;
	TArray<AActor*> DefaultChildActors;
	TArray<AActor*> AttachedRootActors;
	UPROPERTY()
	UStaticMeshComponent* DestroyedActors_ParentCoffinStaticMeshComponent;
	UPROPERTY()
	AActor* CoffinMeshActor;


	AEntityBase();
	void Initialize(FEntityState entitystate, int radarRange);
	void SetEntityState(FEntityState entitystate);
	void SetEntityPosition(FVector entityPosition);
	FEntityType GetEntityType();
	virtual void setRibbon();
	virtual void setVerticalRibbon();
	virtual void setForwardVector();
	virtual void ApplyMode();
	virtual void ResetTrails();
	void SetLockLineType(ELockLineType NewType);

	void SetLockLineVisibility(bool bVisible);
	void toggleTrail(bool IsVisible);
	void toggleVerticalTrail(bool IsVisible);
	void UpdateGroundBeam(float DeltaTime, const FVector& JetLocation);
	void HandleLODs(int id);
	void HandleLODsandHealthStates();

	//UConfigMenuWidget* ListWidget;
	UPROPERTY(VisibleAnywhere, Category = "Label")
	UWidgetComponent* WidgetComponent;
	UTextBlock* TextBlock;
	
	float Mil2525Height = 300.0f;

	void FindAllChildActors(AActor* Parent, TArray<AActor*>& OutMeshes);
	void ImportEntityModel();

	void SetEntityScale(float scaleValue);
	void ResetEntityScale();
	
	void SetForceBasedMaterial();
	

	//------------------------Coverages Work-------------------------
	UPROPERTY(EditAnywhere, Category = "Coverage")
	UStaticMeshComponent* CoverageMesh = nullptr;
	UPROPERTY(EditAnywhere, Category = "Coverage")
	UProceduralMeshComponent* DomeRings = nullptr;

	UMaterialInterface* CoverageDomeMaterial = nullptr;
	UMaterialInstanceDynamic* DynamicCoverageDomeMaterial = nullptr;

	UMaterialInterface* CoverageRingThinMaterial = nullptr;
	UMaterialInstanceDynamic* DynamicCoverageRingThinMaterial = nullptr;

	UMaterialInterface* CoverageRingThickMaterial = nullptr;
	UMaterialInstanceDynamic* DynamicCoverageRingThickMaterial = nullptr;

	TSharedPtr<FCircle> FootPrintConverage = nullptr;
	//------------------------Coverages Work-------------------------


	//Locklines
	bool isLockLineDestroyed = false;
	UPROPERTY() TMap<AEntityBase*, class ANiagaraLockLineActor*>     LockBeams;
	UPROPERTY() TMap<AEntityBase*, class ANiagaraLockLineRedActor*> RedLockBeams;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Beam")
	UNiagaraComponent* FireNiagaraComponent = nullptr;

	UFUNCTION()
	void Fire();
	

public:
	FEntityID GetEntityId();
	ERemoteEntityType GetRemoteEntityType() { return RemoteEntityType; }
	FRotator GetWorldOrientation() { return WorldOrientation; }
	FVector GetGeodeticLocation() { return GeodeticLocation; }
	FVector GetWorldLocation() { return WorldLocation; }
	FString GetCallSign() { return CallSign; }
	EForceType GetForceType() { return ForceType; }
	int GetRadarRange() { return RadarRange; }
	TArray<FEntityID> GetTrackedEntitiesList() { return TrackedEntitiesList; }
	TArray<FEntityID> GetLockedEntitiesList() { return LockedEntitiesList; }
	ELocalHealth GetHealth() { return Health; }
	bool IsSensorOn() { return isSensorOn; }
	short GetSpeedInKnots() { return speedInKnots; }
	bool GetIsNavLightsOn() { return isNavLightsOn; }
	bool GetIsLandingGearExtended() { return isLandingGearExtended; }
	void UpdateBillboardSize();
	void SetMil2525Visibility(bool isVisible);
	void SetMil2525Opacity(float OpacityValue);
	void SetMil2525Scale(float BillboardSize);
	void HideActor();
	void CreateCoffinMesh();
	void SetVisibleModel(const TArray<AActor*> actors, bool isVisible);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	float LodShiftDistance = 10000;

	int activeLODIndex = 0;
	int previousActiveLODIndex = 0;

	bool bisUsingPaperMesh;
	bool bisFirstTimeHealthCheck=false;
	bool bisFirstTimeModeCheck=false;
	ELocalHealth PreviousHealthState = ELocalHealth::NO_DAMAGE;
	ModelVisualMode PreviousVisualMode = ModelVisualMode::BattleSpaceMode;
	APlayerController* playerController;
		void AlignmentToGround();
	FTimerHandle DelayHandle;

public:
	bool bisActorHooked;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void CreateDefaultMesh();


};
