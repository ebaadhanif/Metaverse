#include "ObjAsset.h"
#include "EntityBase.h"

void UObjAsset::Import3DAsset()
{
    Model = NewObject<UAssimpRuntime3DModelsImporter>();
    if (Model)
    {
        Model->LoadAssimpDLLIfNeeded();
        Model->ImportModel(FolderPath);
        Model->SetModelName(ExtractModelNameFromPath(FolderPath));
    }
}

void UObjAsset::Spawn3DAsset(UWorld* World, const FTransform& modelTransform)
{
	TArray<FString> LodNames = { "-1" };

    if (Model)
    {
		if (_modelConfig.LODs.IsEmpty())
			_spawnedActor = Model->SpawnModel(World, modelTransform);
		else
		{
			for (int i = 0; i < _modelConfig.LODs.Num(); i++)
			{
				LodNames.Add(_modelConfig.LODs[i].Name);
			}

			_spawnedActor = Model->SpawnModel(World, modelTransform);

		}
    }
}

void UObjAsset::GetConfigRawDataFromFile(const FString& XmlFilePath)
{

}

void UObjAsset::AttachComponentsToRawDataInModel(UWorld* World, AEntityBase* base)
{


}
