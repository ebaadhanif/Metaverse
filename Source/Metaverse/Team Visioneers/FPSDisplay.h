#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSDisplay.generated.h"

class ALoadingManager;

UCLASS()
class AFPSDisplay : public AActor
{
	GENERATED_BODY()

public:
	AFPSDisplay();

protected:
	virtual void BeginPlay() override;
	FString FPS;
	float ElapsedTime = 0;
	int32 value = 0;

public:
	virtual void Tick(float DeltaTime) override;
	FString GetFPS() const;

};
