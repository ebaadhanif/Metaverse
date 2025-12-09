#pragma once
#include "CoreMinimal.h"
#include "FbxAsset.h"
#include "ObjAsset.h"
#undef OPAQUE
#include "Cesium3DTileset.h"
#include "CesiumGeoreference.h"
#include "UObject/NoExportTypes.h"
#include <AppConstEnumStruct.h>
#include "EntityBase.h"
#include "../Team RenderStorm/BeamVectorActorBase.h"

#include "Model3DAssetManager.generated.h"






UCLASS()
class METAVERSE_API UModel3DAssetManager : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TArray<UModel3DAsset*> ModelAssetList;
	FString ModelsFolderpath;
	void Import3DAsset();
	void Spawn3DAsset(UWorld* World, UModel3DAsset* Obj);
	FTransform modelTransform;
	float X = 202200.000000, Y = 822931.000000, Z = -13542.000000;
	ACesiumGeoreference* CesiumGeoreference;
	ACesium3DTileset* Tileset;
	void AttachSpawnedActorsToParent();
	UModel3DAsset* GetDefaultModelAsset(ERemoteEntityType RemoteEntityType);
	UModel3DAsset* GetDefaultModelByName(FString modelName);
	void ImportBaseModel(AEntityBase* base);
	UModel3DAsset* Get3DAssetByEntityType(FEntityType entityType);
	//void CreateDefaultActorMesh(AEntityBase* base);
	void FindAllChildActors(AActor* Parent, TArray<AActor*>& OutMeshes);
	bool ValidateDefaultModelAsset(UModel3DAsset* asset, AEntityBase*  base);

	void HandleStandardTextures(TArray<AActor*> actors, UTexture2D* texture);
	void HandleIRStandardTextures(AEntityBase* base, UTexture* texture);
	void GetAllMaterialsofAllActors(AEntityBase* base);
	void RevertToOrignalTextures(AEntityBase* base);

	UPROPERTY()
	UTexture2D* IRTexture = nullptr;

	private:
		bool bIsUsingDefaultModel;
		bool bisOnLOD1 = true;
		bool bisOnLOD0;
		bool bisDestroyed;
		bool bisDamaged;
		bool bisActorHidden;
		bool bisUsingPaperMesh;

		UPROPERTY()
		UMaterialInterface* StandardaMaterial = nullptr;
		UPROPERTY()
		UMaterialInterface* IRMat = nullptr;
		UPROPERTY()
		UTexture2D* DamagedTexture = nullptr;
		

		UPROPERTY()
		UTexture2D* DestroyedTexture = nullptr;
		


};


