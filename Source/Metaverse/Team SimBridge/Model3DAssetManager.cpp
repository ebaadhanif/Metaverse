// Class Added by Ebaad, This class deals with importing models using Assimp Plugin
#include "Model3DAssetManager.h"
#include "TimerManager.h"
#include <Metaverse/Team RenderStorm/BeamVectorActorBase.h>

void UModel3DAssetManager::Import3DAsset()
{

	//ModelsFolderpath = "//wsserver/StorageSpace/28- Metaverse/2- PAF Metraverse/GITHUB PROJECT MODELS";

	//ModelsFolderpath = "D:/Assets/AssetToImport/JTAC 2.0 Entites/al khalid";

	//ModelsFolderpath = "D:/Assets/AssetToImport/JTAC 2.0 Entites";
	//
	//ModelsFolderpath = "D:/Assets/AssetToImport/AssimpTest";

	//ModelsFolderpath = "D:/Assets/AssetToImport/memTest";

	StandardaMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/RuntimeModelImporter/M_Standard.M_Standard"));
	IRMat = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/RuntimeModelImporter/M_BaseMaterial.M_BaseMaterial"));

	DamagedTexture = LoadObject<UTexture2D>(
		nullptr,
		TEXT("/Game/Materials/StandardTextures/damage_texture.damage_texture")
	);
	IRTexture = LoadObject<UTexture2D>(
		nullptr,
		TEXT("/Game/Materials/StandardTextures/al_khalid_ir.al_khalid_ir")
	);

	DestroyedTexture = LoadObject<UTexture2D>(
		nullptr,
		TEXT("/Game/Materials/StandardTextures/Destroyed.Destroyed")
	);


	TArray<FString> FoundModelFiles;
	TArray<FString> FoundModelFilesFolders;
	FString BasePath = ModelsFolderpath;
	FPaths::NormalizeDirectoryName(BasePath); // Normalize path (slashes)

	if (!FPaths::DirectoryExists(BasePath))
	{
		UE_LOG(LogTemp, Error, TEXT("❌ Models folder does not exist: %s"), *BasePath);
		return;
	}

	TArray<FString> Extensions = { TEXT("*.fbx"), TEXT("*.glb"), TEXT("*.obj"), TEXT("*.dae"), TEXT("*.3ds"), TEXT("*.stl") };

	for (const FString& Ext : Extensions)
	{
		TArray<FString> TempFiles;
		IFileManager::Get().FindFilesRecursive(TempFiles, *BasePath, *Ext, true, false);
		FoundModelFiles.Append(TempFiles);
		
	}

	// Final list of valid model paths
	for (const FString& FilePath : FoundModelFiles)
	{
	/*	const FString FileName = FPaths::GetCleanFilename(FilePath);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FPaths::GetPath(FilePath));*/
		FoundModelFilesFolders.Add(*FPaths::GetPath(FilePath));


		UE_LOG(LogTemp, Display, TEXT("✅ Found model: %s"), *FilePath);
		UModel3DAsset* ModelAsset = NewObject<UFbxAsset>();
		if (ModelAsset)
		{
			UAssimpRuntime3DModelsImporter* Model = NewObject<UAssimpRuntime3DModelsImporter>();

			//ModelAsset->Import3DAsset(FilePath);
			ModelAsset->FolderPath = FilePath;
			FString ModelDir = FPaths::GetPath(FilePath);
			TArray<FString> ConfigXmlPathFiles;
			IFileManager::Get().FindFilesRecursive(ConfigXmlPathFiles, *ModelDir, TEXT("*.xml"), true, false);
			FString ConfigXmlPath = FPaths::Combine(ModelDir, FPaths::GetBaseFilename(FilePath) + TEXT(".xml"));
			ModelAsset->GetConfigRawDataFromFile(ConfigXmlPathFiles[0]);
			ModelAssetList.Add(ModelAsset);
		}
	}

}

void UModel3DAssetManager::Spawn3DAsset(UWorld* World, UModel3DAsset* Obj)
{


	CesiumGeoreference = ACesiumGeoreference::GetDefaultGeoreference(World);
	Tileset = Cast<ACesium3DTileset>(UGameplayStatics::GetActorOfClass(World, ACesium3DTileset::StaticClass()));
	Tileset->ResolveGeoreference();
	Tileset->ResolveCameraManager();
	Tileset->ResolveCreditSystem();
	FVector location = FVector(X, Y, Z);
	FRotator rotation = FRotator(0, 0, 0);
	FVector scale = FVector(1, 1, 1);
	modelTransform = FTransform(rotation, location, scale);

	for (UModel3DAsset* Obj : ModelAssetList)
	{
		if (Obj)
		{
			/*FString ModelPath = Obj->Model->GetFilePath();
			FString ModelDir = FPaths::GetPath(ModelPath);
			FString ConfigXmlPath = FPaths::Combine(ModelDir, Obj->Model->GetModelName() + TEXT(".xml"));*/
			modelTransform.SetLocation(modelTransform.GetLocation() + FVector(2000, 0, 0));
			FVector ModelLocation = modelTransform.GetLocation();
			FVector LongitudeLatitude = CesiumGeoreference->TransformUnrealPositionToLongitudeLatitudeHeight(ModelLocation);
			TArray<FVector> SamplePositions = { FVector(LongitudeLatitude.X, LongitudeLatitude.Y, 0) };
			FCesiumSampleHeightMostDetailedCallback Callback;
			Callback.BindLambda
			(
				[this, Obj, LongitudeLatitude, World, ModelLocation]
				(ACesium3DTileset* Tileset, const TArray<FCesiumSampleHeightResult>& Results, const TArray<FString>& Warnings)
				{
					FVector WorldLocation;
					if (Results.Num() == 0 || !Results[0].SampleSuccess)
					{
						UE_LOG(LogTemp, Warning, TEXT("Failed to sample terrain height. Using fallback height."));
						// Fallback height in meters (adjust as needed)
						double fallbackHeight = 100.0;
						WorldLocation = ModelLocation;
					}
					else
					{
						const FCesiumSampleHeightResult& Result = Results[0];
						WorldLocation = CesiumGeoreference->TransformLongitudeLatitudeHeightPositionToUnreal(Result.LongitudeLatitudeHeight);
					}
					FTransform CesiumTransform = modelTransform;
					CesiumTransform.SetLocation(WorldLocation);
					/*if (FPaths::FileExists(ConfigXmlPath))
					{
						Obj->GetConfigRawDataFromFile(ConfigXmlPath);
					}*/
					// Obj->Spawn3DAsset(World, CesiumTransform);

					//Obj->AttachComponentsToRawDataInModel(World);

					UE_LOG(LogTemp, Log, TEXT("Spawned model at location: %s"), *WorldLocation.ToString());

					for (const FString& Warn : Warnings)
					{
						UE_LOG(LogTemp, Warning, TEXT("Cesium Warning: %s"), *Warn);
					}
				}
			);

			Tileset->SampleHeightMostDetailed(SamplePositions, Callback);
		}
	}
}

void UModel3DAssetManager::AttachSpawnedActorsToParent()
{
#if WITH_EDITOR
	for (UModel3DAsset* model : ModelAssetList) {
		if (model->_spawnedActor)
			model->_spawnedActor->SetFolderPath("ModelsList");
	}
#endif
}


UModel3DAsset* UModel3DAssetManager::GetDefaultModelByName(FString modelName)
{
	for (UModel3DAsset* model : ModelAssetList)
	{
		if (model->_modelConfig.ModelInfo.Title == modelName)
		{
			return model;
		}
	}

	return nullptr;
}

void UModel3DAssetManager::ImportBaseModel(AEntityBase* base)
{
	if (ModelAssetList.IsEmpty()) {
		//CreateDefaultActorMesh(base);
		base->CreateDefaultMesh();

		return;
	}

	UModel3DAsset* actorAsset;
	UModel3DAsset* battleSpaceAsset = nullptr;
	AActor* targetActor = nullptr;
	FModelConfiguration config;
	actorAsset = Get3DAssetByEntityType(base->GetEntityType());
	battleSpaceAsset = GetDefaultModelAsset(base->GetRemoteEntityType());

	if (actorAsset == nullptr)
	{
		if (battleSpaceAsset)
			actorAsset = battleSpaceAsset;

		if (actorAsset == nullptr)
		{

			//creata new actor and add its componrtnt then add battlepspave veriable to this
			base->CreateDefaultMesh();
			return;
		}
		bIsUsingDefaultModel = true;
	}
	else
		bIsUsingDefaultModel = false;

	if (actorAsset->_spawnedActor == nullptr)
	{
		actorAsset->Import3DAsset();

	}
	UModel3DAsset* newAsset = actorAsset;
	newAsset->Spawn3DAsset(base->GetWorld(), modelTransform);
	newAsset->AttachComponentsToRawDataInModel(base->GetWorld(), base);
	newAsset->_spawnedActor->AttachToActor(base, FAttachmentTransformRules::KeepRelativeTransform);
	targetActor = newAsset->_spawnedActor;
	config = newAsset->_modelConfig;
	
	base->LODParentActors = newAsset->LODs;
	/*base->LOD0_Parent = newAsset->LOD0_Parent;
	base->LOD1_Parent = newAsset->LOD1_Parent;*/
	base->DestroyedActors_Parent = newAsset->DestroyedActors_Parent;
	base->DamagedActors_Parent = newAsset->DamagedActors_Parent;
	//FString aa = FString::Printf(TEXT("Battlespace_Actor : %s"), newAsset->Battlespace_Actor->GetActorLabel());
	//GEngine->AddOnScreenDebugMessage(-1, 0.1, FColor::Green, newAsset->Battlespace_Actor->GetActorLabel());
	base->Battlespace_Actor = newAsset->Battlespace_Actor;
	base->ModelParent = newAsset->RootModelActor;

	TArray<AActor*> _childrens;
	FindAllChildActors(newAsset->_spawnedActor, _childrens);

	for (AActor* actor : _childrens)
	{
		UProceduralMeshComponent* meshComp = Cast<UProceduralMeshComponent>(actor->GetComponentByClass(UProceduralMeshComponent::StaticClass()));
		if (meshComp)
		{
			meshComp->SetRenderInDepthPass(true);
			meshComp->bRenderCustomDepth = true;
			meshComp->SetCustomDepthStencilValue(1);
			
		}
	}

	if (!bIsUsingDefaultModel)
	{
		/*for (auto* actor : _childrens)
		{

			if (!config.LODs.IsEmpty())
			{
				if (actor->GetActorLabel().Contains(config.LODs[0].Name) && !base->LOD0_Parent) base->LOD0_Parent = actor;
				if (actor->GetActorLabel().Contains(config.LODs[1].Name) && !base->LOD1_Parent) base->LOD1_Parent = actor;
			}
			if (actor->GetActorLabel().Contains(config.Mo delInfo.DestroyModel) && !base->DestroyedActors_Parent) base->DestroyedActors_Parent = actor;
			if (actor->GetActorLabel().Contains(config.ModelInfo.DamageModel) && !base->DamagedActors_Parent) base->DamagedActors_Parent = actor;
			if (actor->GetActorLabel().Contains(config.ModelInfo.BattlespaceModel) && !base->Battlespace_Actor)
				base->Battlespace_Actor = actor;
		}*/
	}
	else
	{
		FindAllChildActors(base, base->DefaultChildActors);
	}

	TArray<AActor*> tempArr;

	for (size_t i = 0; i < base->LODParentActors.Num(); i++)
	{
		base->LODsChilds.Add(tempArr);
	}

	for (int i = 0; i < base->LODParentActors.Num(); i++)
	{
		FindAllChildActors(base->LODParentActors[i], base->LODsChilds[i]);

	}
	//if (base->LOD0_Parent)
	//	FindAllChildActors(base->LOD0_Parent, base->LOD0_actors);
	//if (base->LOD1_Parent)
	//	FindAllChildActors(base->LOD1_Parent, base->LOD1_actors);
	if (base->DestroyedActors_Parent)
		FindAllChildActors(base->DestroyedActors_Parent, base->DestroyedActors);
	if (base->DamagedActors_Parent)
		FindAllChildActors(base->DamagedActors_Parent, base->DamagedActors);

	if (!bIsUsingDefaultModel)
	{
		if (base->Battlespace_Actor)
			FindAllChildActors(base->Battlespace_Actor, base->BattlespceChildActors);
		else if (battleSpaceAsset)
		{
			FTransform childTransfrom = base->GetActorTransform();
			FActorSpawnParameters spawnParams;
			AActor* duplicatedActor = base->GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), childTransfrom, spawnParams);
			if (battleSpaceAsset->_spawnedActor == nullptr)
			{
				battleSpaceAsset->Import3DAsset();
			}
			battleSpaceAsset->Spawn3DAsset(base->GetWorld(), modelTransform);
			base->Battlespace_Actor = duplicatedActor;
			FindAllChildActors(base->Battlespace_Actor, base->BattlespceChildActors);
			duplicatedActor->AttachToActor(base, FAttachmentTransformRules::KeepWorldTransform);
		}
	}


	base->GetAttachedActors(base->AttachedRootActors);
	if (newAsset->_modelConfig.ModelInfo.CustomDamagedTexture)
		HandleStandardTextures(base->DamagedActors, DamagedTexture);
	if (newAsset->_modelConfig.ModelInfo.CustomDestroyedTexture)
		HandleStandardTextures(base->DestroyedActors, DestroyedTexture);

	auto ParseToUint8 = [](const FString& Str)->float
		{
			float Value = FCString::Atoi(*Str);
			return static_cast<uint8>(Value);
		};

	base->entityHeight = (newAsset->_modelConfig.ModelInfo.ModelHeight);
	base->entityLength = (newAsset->_modelConfig.ModelInfo.ModelLength);
	base->entityWidth = (newAsset->_modelConfig.ModelInfo.ModelWidth);
	base->IRTexture = newAsset->LoadIRTexture();

	GetAllMaterialsofAllActors(base);

	 newAsset->LODs.Empty();
	 newAsset->DestroyedActors_Parent = nullptr;
	newAsset->DamagedActors_Parent = nullptr;
	newAsset->Battlespace_Actor = nullptr;
	 newAsset->RootModelActor = nullptr;

}

void UModel3DAssetManager::FindAllChildActors(AActor* Parent, TArray<AActor*>& OutMeshes)
{
	if (!Parent) return;

	TArray<AActor*> DirectChildren;
	if (!Parent->IsA(AEntityBase::StaticClass()))
	   OutMeshes.Add(Parent);

	Parent->GetAttachedActors(DirectChildren);
	for (AActor* Child : DirectChildren)
	{
		if (Child->IsA(ABeamVectorActorBase::StaticClass()))
			continue;
		if (Child)
		{
			OutMeshes.Add(Child);

			// Recursively go deeper
			FindAllChildActors(Child, OutMeshes);
		}
	}
}

bool UModel3DAssetManager::ValidateDefaultModelAsset(UModel3DAsset* asset, AEntityBase* base)
{
	asset = GetDefaultModelAsset(base->GetRemoteEntityType());

	if (asset == nullptr)
	{
		base->CreateDefaultMesh();
		//SetForceBasedMaterial();
		return false;
	}
	return true;
}


void UModel3DAssetManager::HandleStandardTextures(TArray<AActor*> actors, UTexture2D* texture)
{
	UTexture* base = nullptr;
	UMaterialInterface* mat = nullptr;

	for (AActor* actor : actors)
	{
		UProceduralMeshComponent* meshComp = Cast<UProceduralMeshComponent>(actor->GetComponentByClass(UProceduralMeshComponent::StaticClass()));
		if (meshComp)
		{
			mat = meshComp->GetMaterial(0);
			mat->GetTextureParameterValue(FMaterialParameterInfo("BaseColor"), base);
			
			UMaterialInstanceDynamic* matIns = UMaterialInstanceDynamic::Create(StandardaMaterial, nullptr);

			matIns->SetTextureParameterValue("BaseColor", base);
			matIns->SetTextureParameterValue("StandardTexture", texture);
			meshComp->SetMaterial(0, matIns);
		}


	}
}
void UModel3DAssetManager::HandleIRStandardTextures(AEntityBase* base, UTexture* texture)
{
	TArray<AActor*> lod0actors;
	TArray<AActor*> lod1actors;
	FindAllChildActors(base,lod0actors);
	if(!base->LODParentActors.IsEmpty())
	FindAllChildActors(base->LODParentActors[1],lod1actors);

	UMaterialInstanceDynamic* matIns = UMaterialInstanceDynamic::Create(IRMat, nullptr);

	UMaterialInterface* mat = nullptr;
	for (AActor* actor: lod0actors)
	{

		UProceduralMeshComponent* meshComp = Cast<UProceduralMeshComponent>(actor->GetComponentByClass(UProceduralMeshComponent::StaticClass()));
		if (meshComp)
		{
			//orignalMats.Add( meshComp->GetMaterial(0));
			matIns->SetTextureParameterValue("BaseColor", IRTexture);
			meshComp->SetMaterial(0, matIns);

		}

	}
	for (AActor* actor: lod1actors)
	{

		UProceduralMeshComponent* meshComp = Cast<UProceduralMeshComponent>(actor->GetComponentByClass(UProceduralMeshComponent::StaticClass()));
		if (meshComp)
		{
			//orignalMats.Add(meshComp->GetMaterial(0));
			matIns->SetTextureParameterValue("StandardTexture", IRTexture);
			matIns->SetTextureParameterValue("BaseColor", IRTexture);
			meshComp->SetMaterial(0, matIns);

		}

	}

	/*}*/
}

void UModel3DAssetManager::GetAllMaterialsofAllActors(AEntityBase* base)
{
	TArray<AActor*> actors;
	FindAllChildActors(base, actors);

	for (AActor* actor : actors)
	{
		UProceduralMeshComponent* meshComp = Cast<UProceduralMeshComponent>(actor->GetComponentByClass(UProceduralMeshComponent::StaticClass()));
		if (meshComp)
		{
			base->ActorsMaterialsList.Add( meshComp->GetMaterial(0));
		
		}
	}

}

void UModel3DAssetManager::RevertToOrignalTextures(AEntityBase* base)
{
	TArray<AActor*> actors;
	FindAllChildActors(base, actors);

	for (int i=0;i< actors.Num() ;i++)
	{
		UProceduralMeshComponent* meshComp = Cast<UProceduralMeshComponent>(actors[i]->GetComponentByClass(UProceduralMeshComponent::StaticClass()));
		if (meshComp)
		{
			UMaterialInstanceDynamic* matIns = UMaterialInstanceDynamic::Create(base->ActorsMaterialsList[i], nullptr);
;
			meshComp->SetMaterial(0, matIns);

		}
	}
}

UModel3DAsset* UModel3DAssetManager::Get3DAssetByEntityType(FEntityType entityType)
{
	UModel3DAsset* tempModel = nullptr;

	TArray<FString> Groups;



	for (UModel3DAsset* model : ModelAssetList)
	{
		/*TArray<TArray<FString>> splitvalues = { { TEXT("-1") }, { TEXT("-1") }, { TEXT("-1") }, { TEXT("-1") }, { TEXT("-1") }, { TEXT("-1") }, { TEXT("-1") } };*/
		TArray<TArray<FString>> splitvalues;
		//splitvalues.SetNum(7, false);

		model->_modelConfig.ModelInfo.DISEntityType.ParseIntoArray(Groups, TEXT(","), true);


		for (FString id : Groups)
		{
			TArray<FString> Values;
			id.ParseIntoArray(Values, TEXT(":"), true);
			splitvalues.Add(Values);
			/*for (int i = 0; i < Values.Num(); i++)
			{
			splitvalues[i]=Values;

			}*/
		}

		auto ParseToUint8 = [](const FString& Str)->uint8
			{
				int32 Value = FCString::Atoi(*Str);
				return static_cast<uint8>(Value);
			};

		for (int i = 0; i < splitvalues.Num(); i++)
		{

			/*if (splitvalues[i].IsEmpty() || splitvalues[i][0] == "-1")
			{
				continue;
			}*/
			for (int j = splitvalues[i].Num(); j < 7; j++)
			{
				splitvalues[i].Add(TEXT("0"));
			}

			FEntityType tempType;
			tempType.entiyKind = ParseToUint8(*splitvalues[i][0]);
			tempType.domain = ParseToUint8(*splitvalues[i][1]);
			int32 tempValue = FCString::Atoi(*splitvalues[i][2]);
			tempType.country = static_cast<uint16>(tempValue);
			tempType.category = ParseToUint8(*splitvalues[i][3]);
			tempType.subcategory = ParseToUint8(*splitvalues[i][4]);
			tempType.specific = ParseToUint8(*splitvalues[i][5]);
			tempType.extra = ParseToUint8(*splitvalues[i][6]);

			if (tempType == entityType)
			{
				splitvalues.Empty();
				return model;
			}
		}
	}
	return tempModel;
}


UModel3DAsset* UModel3DAssetManager::GetDefaultModelAsset(ERemoteEntityType RemoteEntityType)
{
	switch (RemoteEntityType)
	{
	case ERemoteEntityType::FIXEDWING_AIRCRAFT:
	case ERemoteEntityType::ROTORCRAFT:
	{
		return GetDefaultModelByName("Default Air");
	}
	case ERemoteEntityType::ARMORED_VEHICLE:
	case ERemoteEntityType::GENERAL_VEHICLE:
	case ERemoteEntityType::MUNITION_LAUNCHER:
	{
		return GetDefaultModelByName("Default Land");

	}
	case ERemoteEntityType::SHIPS:
	{
		return GetDefaultModelByName("Default Surface");

	}

	case ERemoteEntityType::RADAR:
	{
		return GetDefaultModelByName("Default Sensor");

	}
	case ERemoteEntityType::CHAFF:
	case ERemoteEntityType::FLARE:
	{
		return GetDefaultModelByName("Default Expandable");

	}
	case ERemoteEntityType::HUMAN:
	case ERemoteEntityType::ANIMAL:
	{
		return GetDefaultModelByName("Default LifeForm");

	}
	case ERemoteEntityType::STRUCTURE:
	case ERemoteEntityType::OTHER_CULTURE_FEATURE:
	{
		return GetDefaultModelByName("Default Cultural Feature");

	}
	case ERemoteEntityType::VEGETATION:
	{
		return GetDefaultModelByName("Default Other");

	}
	case ERemoteEntityType::MISSILE:
	case ERemoteEntityType::SHELL:
	case ERemoteEntityType::BOMB:
	{
		return GetDefaultModelByName("Default Munition");

	}
	default:
	{
		return GetDefaultModelByName("Default Other");
	}

	}
}