#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MetaverseXRInputManager.generated.h"

class AHanTracking;
class AControllerTracking;

UENUM(BlueprintType)
enum class EXRInputMode : uint8 {
	HandTracking UMETA(DisplayName = "Hand Tracking"),
	ControllerTracking UMETA(DisplayName = "Controller Tracking")
};

UCLASS()
class METAVERSEXRSYSTEM_API AMetaverseXRInputManager : public AActor
{
	GENERATED_BODY()

public:
	AMetaverseXRInputManager();

	virtual void Tick(float DeltaTime) override;

	AHanTracking* GetHandTrackingActor() {
		return HandTrackingActor;
	}

protected:
	virtual void BeginPlay() override;

public:

	void CheckXRMode();
	void SetXRMode(EXRInputMode InputMode);
	bool AreControllersConnected();

	EXRInputMode CurrentMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AHanTracking* HandTrackingActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AControllerTracking* ControllerTrackingActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AHanTracking> HandTrackerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AControllerTracking> ControllerTrackerClass;

	bool bControllersConnected = false;

	IXRTrackingSystem* XRSystem;
	TArray<int32> DevicesIds;
};
