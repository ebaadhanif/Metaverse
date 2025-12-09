#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MegaScanPresetParentWrapper.generated.h"

UCLASS()
class METAVERSE_API AMegaScanPresetParentWrapper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMegaScanPresetParentWrapper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
