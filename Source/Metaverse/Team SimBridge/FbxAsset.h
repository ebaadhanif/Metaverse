
#pragma once
#include "CoreMinimal.h"
#include "Model3DAsset.h"
#include "UObject/NoExportTypes.h"
#include "Kismet/GamePlayStatics.h"
#include "Components/AudioComponent.h"
#include "ConfigManager.h"

#include "FbxAsset.generated.h"

UCLASS()
class METAVERSE_API UFbxAsset : public UModel3DAsset
{
public:

	GENERATED_BODY()
	virtual void Import3DAsset() override;
	virtual void Spawn3DAsset(UWorld* World, const FTransform& modelTransform) override;

	virtual void GetConfigRawDataFromFile(const FString& XmlFilePath) override;

	virtual void AttachComponentsToRawDataInModel(UWorld* World, AEntityBase* base) override;

};
