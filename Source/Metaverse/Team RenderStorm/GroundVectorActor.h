// GroundVectorActor.h
#pragma once
#include "CoreMinimal.h"
#include "BeamVectorActorBase.h"
#include "GroundVectorActor.generated.h"

class UInstancedStaticMeshComponent;
class UStaticMesh;

UCLASS()
class METAVERSE_API AGroundVectorActor : public ABeamVectorActorBase
{
	GENERATED_BODY()

public:
	AGroundVectorActor();

	// Ring parameters (cm)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rings")
	float RingSpacing = 100000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rings")
	float RingRadius = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rings")
	float RingThicknessCm = 3000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rings")
	int32 MaxRings = 2048;

	// Visuals
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rings")
	UStaticMesh* RingMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rings")
	UMaterialInterface* RingMaterial = nullptr;

	void ToggleHeightRingVisibility(bool bIsVisible);

protected:
	UPROPERTY(Transient)
	UInstancedStaticMeshComponent* RingISM = nullptr;
	UStaticMeshComponent* HeightRing = nullptr;

	virtual void BeginPlay() override;
	virtual void OnAfterBeamUpdated(float DeltaTime, const FVector& Start, const FVector& End, float radius, float thickness) override;
	virtual void clearRings() override;
	virtual void UpdateHeightRing(const FVector& Start, const FVector& End, float radius, float thickness) override;
private:
	void EnsureRingISM();
	void UpdateRings(const FVector& Start, const FVector& End, float radius, float thickness);



	
};
