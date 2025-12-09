// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaserPointerActor.generated.h"

UCLASS()
class METAVERSE_API ALaserPointerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ALaserPointerActor();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Beam")
	void SetBeamTarget(const FVector& InStart, const FVector& InEnd);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beam")
	bool bSmooth = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beam", meta = (ClampMin = "0.1"))
	float BeamRadius = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beam", meta = (ClampMin = "1.0"))
	float PositionInterpSpeed = 30.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Beam")
	UStaticMeshComponent* BeamMesh;

protected:
	FVector TargetStart;
	FVector TargetEnd;
	FVector CurrentStart;
	FVector CurrentEnd;

	float MeshHalfHeight;
	float MeshRadius;

	void UpdateVisual();

};
