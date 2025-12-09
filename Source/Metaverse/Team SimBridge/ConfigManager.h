#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Model3DAsset.h"
#include "ConfigManager.generated.h"

UCLASS()
class METAVERSE_API UConfigManager : public UObject
{
	GENERATED_BODY()
public:
	static FModelConfiguration LoadModelConfigFromXml(const FString& FilePath);
};

