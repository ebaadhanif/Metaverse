#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplineLockLineActor.generated.h"

class USplineComponent;
class USplineMeshComponent;

UCLASS()
class METAVERSE_API ASplineLockLineActor : public AActor
{
	GENERATED_BODY()

public:
	ASplineLockLineActor();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Spline")
	void SetJetEndpoints(AActor* JetA, AActor* JetB);

	UFUNCTION(BlueprintCallable)
	void ShowLockLine();

	UFUNCTION(BlueprintCallable)
	void HideLockLine();


protected:
	virtual void BeginPlay() override;

private:
	void UpdateSpline();

	UPROPERTY()
	AActor* Source;

	UPROPERTY()
	AActor* Destination;

	UPROPERTY()
	USplineComponent* SplineComp;

	UPROPERTY()
	USplineMeshComponent* SplineMeshComp;

	UPROPERTY()
	UStaticMesh* BeamMesh;

	UPROPERTY()
	UMaterialInterface* BeamMaterial;
};
