// Class Added by Ebaad, This class is wrapper on Assimp Plugin and each instance of this class is a model/3dasset
#include "FbxAsset.h"
#include "NiagaraComponent.h"           
#include "NiagaraFunctionLibrary.h"     
#include "NiagaraSystem.h"           
#include <NiagaraDataInterfaceAudioPlayer.h>


void UFbxAsset::Import3DAsset()
{
	Model = NewObject<UAssimpRuntime3DModelsImporter>();
	if (Model)
	{
		Model->LoadAssimpDLLIfNeeded();
		Model->ImportModel(FolderPath);
		Model->SetModelName(ExtractModelNameFromPath(FolderPath));


	}
}

void UFbxAsset::Spawn3DAsset(UWorld* World, const FTransform& modelTransform)
{

	if (Model)
	{
		int actorNum = 0;
		for (int i = 0; i < _modelConfig.LODs.Num(); i++)
		{
			Model->ListOfSpecificActorNames.Add(_modelConfig.LODs[i].Name);
		}
		Model->ListOfSpecificActorNames.Add(_modelConfig.ModelInfo.DamageModel);
		Model->ListOfSpecificActorNames.Add(_modelConfig.ModelInfo.DestroyModel);
		Model->ListOfSpecificActorNames.Add(_modelConfig.ModelInfo.BattlespaceModel);

		AActor* nullactor = nullptr;
		for (int i = 0; i < Model->ListOfSpecificActorNames.Num(); i++)
		{
			Model->ListOfSpecificActors.Add(nullactor);
		}

		_spawnedActor = Model->SpawnModel(World, modelTransform);

		for (int i = 0; i < _modelConfig.LODs.Num(); i++)
		{
			LODs.Add(Model->ListOfSpecificActors[i]);
			actorNum++;
		}

		DamagedActors_Parent = Model->ListOfSpecificActors[actorNum];
		actorNum++;
		DestroyedActors_Parent = Model->ListOfSpecificActors[actorNum];
		actorNum++;
		Battlespace_Actor = Model->ListOfSpecificActors[actorNum];

		if (_spawnedActor)
		{
			RootModelActor = Model->RootFBXActor;
		}
		Model->ListOfSpecificActorNames.Empty();
		Model->ListOfSpecificActors.Empty();
	}


}

void UFbxAsset::GetConfigRawDataFromFile(const FString& XmlFilePath)
{
	_modelConfig = UConfigManager::LoadModelConfigFromXml(XmlFilePath);
}

void UFbxAsset::AttachComponentsToRawDataInModel(UWorld* World, AEntityBase* base)
{
	if (!Model) return;

	const FModelInfo& modelInfo = _modelConfig.ModelInfo;
	const FString entitySoundPath = FString::Printf(TEXT("/Game/SFX/Sound/%s.%s"), *modelInfo.Sound, *modelInfo.Sound);

	USoundBase* EntitySoundAsset = LoadObject<USoundBase>(nullptr, *entitySoundPath);
	if (!EntitySoundAsset)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not load Sound System: %s"), *entitySoundPath);
	}


	UAudioComponent* EntityAudioComp = UGameplayStatics::SpawnSoundAttached(EntitySoundAsset, base->GetRootComponent(), NAME_None, FVector::ZeroVector, EAttachLocation::KeepRelativeOffset, false, 1, 1, 0);
	if (EntityAudioComp)
	{
		EntityAudioComp->bIsUISound = false;
		EntityAudioComp->bAllowSpatialization = true;
		EntityAudioComp->bAutoActivate = true;
		EntityAudioComp->bAutoDestroy = false;
		EntityAudioComp->bCanPlayMultipleInstances = true;
		EntityAudioComp->Play();
	}

	base->SoundRegistry.Add(FName(TEXT("Entity_Sound")), EntityAudioComp);
	auto MakeEffectPath = [](const FString& Name)
		{
			static const FString Base = TEXT("/Game/VFX/Blueprints/Effects/");
			return FString::Printf(TEXT("%s%s.%s"), *Base, *Name, *Name);
		};

	auto MakeSoundPath = [](const FString& Name)
		{
			static const FString Base = TEXT("/Game/SFX/Sound/");
			return FString::Printf(TEXT("%s%s.%s"), *Base, *Name, *Name);
		};
	// Lights: 
	for (const FModelLightConfig& Light : _modelConfig.Lights)
	{
		AActor* NodeActor = Model->GetNodeActorByName(Light.RefNode);
		if (!NodeActor)
		{
			UE_LOG(LogTemp, Warning, TEXT(" No node actor found for RefNode: %s"), *Light.RefNode);
			continue;
		}
		// Construct path to the Blueprint Pawn class
		const FString BPPath = FString::Printf(TEXT("/Game/VFX/Blueprints/Lights/%s.%s_C"), *Light.VFX, *Light.VFX);
		UClass* LightBPClass = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), nullptr, *BPPath));
		if (!LightBPClass)
		{
			UE_LOG(LogTemp, Warning, TEXT(" Could not load light VFX Pawn class: %s"), *BPPath);
			continue;
		}
		UWorld* World = NodeActor->GetWorld();
		if (!World)
		{
			UE_LOG(LogTemp, Error, TEXT(" World is null for RefNode: %s"), *Light.RefNode);
			continue;
		}
		// Spawn  using deferred spawning and attach before finishing
		AActor* LightActor = World->SpawnActorDeferred<AActor>(LightBPClass, FTransform::Identity, NodeActor);
		if (!LightActor)
		{
			UE_LOG(LogTemp, Error, TEXT(" Failed to spawn light pawn for: %s"), *Light.VFX);
			continue;
		}

#if WITH_EDITOR
		LightActor->SetActorLabel(Light.VFX);
#endif
		FTransform SpawnTransform = NodeActor->GetActorTransform(); // or any valid world transform
		LightActor->FinishSpawning(
			SpawnTransform,
			true,
			nullptr,
			ESpawnActorScaleMethod::MultiplyWithRoot
		);
		LightActor->AttachToActor(NodeActor, FAttachmentTransformRules::KeepRelativeTransform);
		LightActor->SetActorRelativeLocation(FVector::ZeroVector);
		LightActor->SetActorRelativeRotation(SpawnTransform.Rotator());
		LightActor->SetActorRelativeScale3D(NodeActor->GetTransform().GetScale3D() / (SpawnTransform.GetScale3D() * 100));
	}


	//   Effects:
	for (const FModelEffectConfig& Effect : _modelConfig.Effects)
	{
		AActor* NodeActor = Model->GetNodeActorByName(Effect.RefNode);
		FString RefNode = *Effect.RefNode;
		FString VFX = *Effect.VFX;
		FName name = FName(*Effect.VFX);
		if (!NodeActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("No node actor found for RefNode: %s"), *Effect.RefNode);
			continue;
		}
		FString CleanRefNode = Effect.RefNode.Replace(TEXT(" "), TEXT(""), ESearchCase::IgnoreCase);

		USceneComponent* AttachComponent = NodeActor->GetRootComponent();
		if (!AttachComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("Node actor has no root component: %s"), *Effect.RefNode);
			continue;
		}

		UNiagaraSystem* NiagaraSystem = nullptr;
		if (!Effect.VFX.IsEmpty())
		{
			const FString NSpath = MakeEffectPath(Effect.VFX);
			NiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, *NSpath);
			if (!NiagaraSystem)
			{
				UE_LOG(LogTemp, Warning, TEXT("Could not load Niagara System: %s"), *NSpath);
			}
		}

		USoundBase* SoundAsset = nullptr;
		//UNiagaraDataInterfaceAudioPlayer* AudioDI = nullptr;
		if (!Effect.Sound.IsEmpty())
		{
			const FString SoundPath = MakeSoundPath(Effect.Sound);
			SoundAsset = LoadObject<USoundBase>(nullptr, *SoundPath);
			if (!SoundAsset)
			{
				UE_LOG(LogTemp, Warning, TEXT("Could not load Sound System: %s"), *SoundPath);
			}
		}
		if (NiagaraSystem)
		{
			UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
				NiagaraSystem,
				AttachComponent,
				NAME_None,
				FVector::ZeroVector,
				FRotator::ZeroRotator,
				EAttachLocation::KeepRelativeOffset,
				false,
				true,
				ENCPoolMethod::None
			);

			if (NiagaraComponent)
			{
				UAudioComponent* AudioComp = UGameplayStatics::SpawnSoundAttached(SoundAsset, NiagaraComponent, NAME_None, FVector::ZeroVector, EAttachLocation::KeepRelativeOffset, false, 1, 1, 0);
				if (AudioComp)
				{
					AudioComp->bIsUISound = false;
					AudioComp->bAllowSpatialization = true;
					AudioComp->bAutoActivate = true;
					AudioComp->bAutoDestroy = false;

					base->SoundRegistry.Add(name, AudioComp);
					//AudioComp->Play();
				}
				//AudioDI = NewObject<UNiagaraDataInterfaceAudioPlayer>(NiagaraComponent);
				//if (AudioDI)
				//{
				//	AudioDI->SoundToPlay = SoundAsset;
				//}
			}

			//NiagaraComponent->SetVariableObject(FName(TEXT("Audio_Player")), AudioDI);
			NiagaraComponent->RegisterComponent();
			UE_LOG(LogTemp, Warning, TEXT("Attached with success"));

			base->EffectsRegistry.Add(name, NiagaraComponent);
		}

		//		const FString BPPath = FString::Printf(TEXT("/Game/VFX/Blueprints/Effects/%s.%s_C"), *Effect.VFX, *Effect.VFX);
		//
		//		UClass* EffectBPClass = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), nullptr, *BPPath));
		//		if (!EffectBPClass)
		//		{
		//			UE_LOG(LogTemp, Warning, TEXT("Could not load Niagara Blueprint: %s"), *BPPath);
		//			continue;
		//		}
		//		UWorld* World = NodeActor->GetWorld();
		//		if (!World)
		//		{
		//			UE_LOG(LogTemp, Error, TEXT("World is null for RefNode: %s"), *Effect.RefNode);
		//			continue;
		//		}
		//		AActor* EffectActor = World->SpawnActorDeferred<AActor>(EffectBPClass, FTransform::Identity, NodeActor);
		//		if (!EffectActor)
		//			continue;
		//#if WITH_EDITOR
		//		EffectActor->SetActorLabel(Effect.RefNode);
		//#endif
		//		FTransform SpawnTransform = NodeActor->GetActorTransform(); // or any valid world transform
		//		EffectActor->FinishSpawning(
		//			SpawnTransform,
		//			true,
		//			nullptr,
		//			ESpawnActorScaleMethod::MultiplyWithRoot
		//		);
		//		// Attach to node actor
		//		EffectActor->AttachToActor(NodeActor, FAttachmentTransformRules::KeepRelativeTransform);
		//		EffectActor->SetActorRelativeLocation(FVector::ZeroVector);
		//		EffectActor->SetActorRelativeRotation(SpawnTransform.Rotator());
		//		EffectActor->SetActorRelativeScale3D(NodeActor->GetTransform().GetScale3D() / (SpawnTransform.GetScale3D() * 100));
	}
	// Attachments:
	for (const FAttachment& Attachment : _modelConfig.Attachments)
	{
		FString CleanRefNode = Attachment.RefNode.Replace(TEXT(" "), TEXT(""), ESearchCase::IgnoreCase);
		AActor* NodeActor = Model->GetNodeActorByName(Attachment.RefNode);
		if (!NodeActor)
		{
			UE_LOG(LogTemp, Warning, TEXT(" No node actor found for RefNode: %s"), *Attachment.RefNode);
			continue;
		}
		const FString BPPath = FString::Printf(TEXT("/Game/VFX/Blueprints/Attachments/%s.%s_C"), *CleanRefNode, *CleanRefNode);
		UClass* AttachmentBPClass = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), nullptr, *BPPath));
		if (!AttachmentBPClass)
		{
			UE_LOG(LogTemp, Warning, TEXT(" Could not load light VFX class: %s"), *BPPath);
			continue;
		}
		UWorld* World = NodeActor->GetWorld();
		if (!World)
		{
			UE_LOG(LogTemp, Error, TEXT(" World is null for RefNode: %s"), *Attachment.RefNode);
			continue;
		}
		FTransform SpawnTransform = NodeActor->GetActorTransform();
		AActor* AttachmentActor = World->SpawnActorDeferred<AActor>(
			AttachmentBPClass,
			FTransform::Identity,
			NodeActor
		);
		if (!AttachmentActor)
			continue;
#if WITH_EDITOR
		AttachmentActor->SetActorLabel(Attachment.RefNode);
#endif
		AttachmentActor->FinishSpawning(
			SpawnTransform,
			true,
			nullptr,
			ESpawnActorScaleMethod::MultiplyWithRoot
		);
		AttachmentActor->AttachToActor(NodeActor, FAttachmentTransformRules::KeepRelativeTransform);
		AttachmentActor->SetActorRelativeLocation(FVector::ZeroVector);
		AttachmentActor->SetActorRelativeScale3D(NodeActor->GetTransform().GetScale3D() / (SpawnTransform.GetScale3D() * 100));
	}
}


