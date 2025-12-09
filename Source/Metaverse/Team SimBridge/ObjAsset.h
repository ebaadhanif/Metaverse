#pragma once
#include "CoreMinimal.h"
#include "Model3DAsset.h"
#include "ConfigManager.h"
#include "UObject/NoExportTypes.h"
#include "ObjAsset.generated.h"

UCLASS()
class METAVERSE_API UObjAsset : public UModel3DAsset
{
	GENERATED_BODY()
public:

	virtual void Import3DAsset() override;
	virtual void Spawn3DAsset(UWorld* World, const FTransform& modelTransform) override;
	virtual void GetConfigRawDataFromFile(const FString& XmlFilePath) override;
	virtual void AttachComponentsToRawDataInModel(UWorld* World, AEntityBase* base) override;
};
