#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "HookedStatePawn.generated.h"

UCLASS()
class METAVERSE_API AHookedStatePawn : public APawn
{
	GENERATED_BODY()

public:
	AHookedStatePawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};
