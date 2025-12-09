#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FreeCameraPawn.h"
#include <Components/TextRenderComponent.h>
#include "RadialCompas.generated.h"
UCLASS()
class METAVERSE_API ARadialCompas : public AActor
{
	GENERATED_BODY()
	
public:	
	ARadialCompas();

	UPROPERTY(VisibleAnywhere)
	TArray<class UTextRenderComponent*> DirectionsText;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	APlayerCameraManager* PlayerCameraManager;
	AFreeCameraPawn* FreeCamPawn = nullptr;
	APawn* PlayerPawn;
	UMaterialInterface* CompasTextMaterial;
	
	TWeakObjectPtr<class APlayerController> PlayerController;

	UPROPERTY(EditAnywhere)
	float CompasRadius = 170.0f;

	UPROPERTY(EditAnywhere)
	float Height = -50.f;

	UPROPERTY(EditAnywhere)
	float NorthYaw = .0f;

	UPROPERTY(EditAnywhere)
	float TextWorldSize = 18.0f;

	UPROPERTY(EditAnywhere)
	float DistanceFromCamera = 150.0f;

	UPROPERTY(EditAnywhere)
	float VerticalOffset = 0.0f;

	FVector PlayerCamLoc;
	FRotator PlayerCamRot;
	FVector JtacPawnLocation;
	FRotator JtacPawnRotation;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
