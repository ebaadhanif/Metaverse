#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "AppConstEnumStruct.h"
#include "BeamVectorActorBase.generated.h"

UCLASS(Abstract)
class METAVERSE_API ABeamVectorActorBase : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Beam")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Beam")
	UNiagaraComponent* BeamComp;

	// Optional: for convenience if you set the asset in BP instead of C++
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Beam")
	UNiagaraSystem* BeamSystem = nullptr;


	// Optional: for convenience if you set the asset in BP instead of C++
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Beam")
	UNiagaraSystem* BeamSystemRed = nullptr;

	// Optional: for convenience if you set the asset in BP instead of C++
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Beam")
	UNiagaraSystem* BeamSystemOther = nullptr;

	// Optional: for convenience if you set the asset in BP instead of C++
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Beam")
	UNiagaraSystem* BeamSystemNeutral = nullptr;


	// Source/destination actors OR raw positions
	UPROPERTY() AActor* Source = nullptr;
	UPROPERTY() AActor* Destination = nullptr;

	FVector RawStart = FVector::ZeroVector;
	FVector RawEnd = FVector::ZeroVector;
	bool bUseRawPositions = false;

	float TimeSinceRingsUpdated = 0.f;   
	float RingUpdateInterval = 1.0f; 

	float FrameTime = 0.f;

	bool isHeightRingVisible = false;


	// Optional (you used it previously)
	EForceType ForceType = EForceType::FRIENDLY;

public:
	ABeamVectorActorBase();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EEndPlayReason) override;

	// Common API
	UFUNCTION(BlueprintCallable) void SetJetEndpoints(AActor* InSource, AActor* InDestination);
	UFUNCTION(BlueprintCallable) void SetBeamEndpoints(const FVector& InStart, const FVector& InEnd);
	UFUNCTION(BlueprintCallable) void SetVectorVisibility(bool bVisible);
	void setForceType(EForceType InForce) { ForceType = InForce; }

protected:
	virtual void OnAfterBeamUpdated(float DeltaTime, const FVector& Start, const FVector& End, float radius, float thickness) {}
	virtual void UpdateHeightRing(const FVector& Start, const FVector& End, float radius, float thickness) {}
	virtual void clearRings() {}
};
