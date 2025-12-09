#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HanTracking.h"
#include "VRMenuInteraction.generated.h"

UCLASS()
class METAVERSE_API AVRMenuInteraction : public AActor
{
	GENERATED_BODY()
	
public:
	AVRMenuInteraction();

	void VRMenuHandler(float DeltaSeconds);
	void VRMenuClick(float DeltaSeconds);

	UFUNCTION()
	void ReactivateInteractor();

	UPROPERTY(EditAnywhere, Category = "Widget Interactor")
	UWidgetInteractionComponent* WidgetInteractor;

	UPROPERTY(EditAnywhere, Category = "Orbit|Input")
	UStaticMeshComponent* SphereMesh;

	FTimerHandle ReEnableTimerHandle;
	UMaterialInterface* SphereMaterial;
	TArray<FVector> LP, RP;  TArray<FQuat> LR, RR;  TArray<float> LRd, RRd;

	float InteractioinDistance = 7.0f;
	float ClickDistance = 1.5;
	float Distance = 0;

	int32 IndexTip = 0;

	bool bIsClicking = false;
	bool bIsPointing = false;
	bool bIsGrabbing = false;

	bool bL = false;
	bool bR = false;

	FVector RawIndexLoc = FVector::ZeroVector;

	FQuat RawIndexQuat = FQuat::Identity;

	FHitResult HitResult;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
