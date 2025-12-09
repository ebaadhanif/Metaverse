#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <MotionControllerComponent.h>
#include "ControllerTracking.generated.h"

UCLASS()
class METAVERSEXRSYSTEM_API AControllerTracking : public AActor
{
	GENERATED_BODY()

public:
	AControllerTracking();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:

	UMotionControllerComponent* LeftMotionController;
	UMotionControllerComponent* RightMotionController;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UMotionControllerComponent* LeftController;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UMotionControllerComponent* RightController;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* LeftControllerMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* RightControllerMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMesh* DefaultLeftMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMesh* DefaultRightMesh;

	UPROPERTY(BlueprintReadWrite)
	bool bIsControllerConnected;

	UPROPERTY(BlueprintReadWrite)
	bool bIsCurrentlyConnected;

	UFUNCTION(BlueprintCallable)
	bool AreControllersConnected();

	UFUNCTION(BlueprintCallable)
	void SetControllersActive(bool bActivate);

	IXRTrackingSystem* XRSystem;
	TArray<int32> DevicesIds;
	APlayerController* PC;

private:
	void UpdateConnectionState();
	void InitializeMeshes();
	void PlayHaptic(UHapticFeedbackEffect_Base* Effect, EControllerHand Hand);

};
