#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "FreeCameraPawn.h"
#include "VRWidgetActor.generated.h"

UCLASS()
class METAVERSE_API AVRWidgetActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AVRWidgetActor();
	void SetVRWidget(TSubclassOf<UUserWidget> WidgetClass);
	void ShowWidget();
	void HideWidget();
		

	UPROPERTY(EditAnywhere)
	UWidgetComponent* WidgetComponent;
	APlayerController* PC;
	FVector CameraLocation;
	FVector WidgetLocation;
	FRotator LookAtRotation;

protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
};
