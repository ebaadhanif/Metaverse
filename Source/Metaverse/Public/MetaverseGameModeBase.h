#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MetaverseGameModeBase.generated.h"


UCLASS()
class METAVERSE_API AMetaverseGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AMetaverseGameModeBase();

	virtual void BeginPlay() override;
	
};
	