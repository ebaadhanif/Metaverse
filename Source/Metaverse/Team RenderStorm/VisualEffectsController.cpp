// Fill out your copyright notice in the Description page of Project Settings.


#include "VisualEffectsController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "ModeManager.h"



AVisualEffectsController* AVisualEffectsController::instance = nullptr;
// Sets default values
AVisualEffectsController::AVisualEffectsController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> BeamSysAsset(TEXT("/Game/VFX/Blueprints/Effects/Blast.Blast")); 
	if (BeamSysAsset.Succeeded())
	{
		DetonationNiagaraSystem = BeamSysAsset.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load Beam Niagara System"));
	}


	World = GetWorld();

}

// Called when the game starts or when spawned
void AVisualEffectsController::BeginPlay()
{
	Super::BeginPlay();

	instance = this;

}

// Called every frame
void AVisualEffectsController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


AVisualEffectsController* AVisualEffectsController::getInstance()
{
	return instance;
}


void AVisualEffectsController::spawnBlastEffect(FVector Location)
{
	if (!DetonationNiagaraSystem || !AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::VisualGraphics).FeatureActive)
	{
		UE_LOG(LogTemp, Error, TEXT("Niagara System not assigned"));
		return;
	}

	DetonationNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DetonationNiagaraSystem, Location, FRotator(0, 0, 0), FVector(1), true, true);

	if (DetonationNiagaraComponent)
	{
		DetonationNiagaraComponent->SetAutoActivate(true);
		UE_LOG(LogTemp, Error, TEXT("Niagara System assigned"));
	}
}


void AVisualEffectsController::toggleEffectsVisibility(bool IsVisible)
{

	if (!World)
		return;

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), Actors);

	for (AActor* Actor : Actors)
	{
		ToggleNiagaraComponentVisibility(Actor, IsVisible);
	}

	for (TObjectIterator<UAudioComponent> It; It; ++It) {
		UAudioComponent* AudioComp = *It;

		if (AudioComp->GetWorld() == World)
		{
			AudioComp->SetPaused(!IsVisible);
		}
	}

}

void AVisualEffectsController::ToggleNiagaraComponentVisibility(AActor* Actor, bool IsVisible)
{
	if (!Actor)
	{
		return;
	}
	TArray<UNiagaraComponent*> NiagaraComponents;
	Actor->GetComponents<UNiagaraComponent>(NiagaraComponents);

	for (UNiagaraComponent* NiagaraComp : NiagaraComponents)
	{
		if (NiagaraComp)
		{
			NiagaraComp->SetVisibility(IsVisible);
			NiagaraComp->SetHiddenInGame(!IsVisible, true);

			if (IsVisible)
			{
				NiagaraComp->Activate(true);
			}
			else {
				NiagaraComp->Deactivate();
			}
		}
	}
}


void AVisualEffectsController::toggleSounds(bool IsEnable)
{

	if (!World)
		return;

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), Actors);

	for (AActor* Actor : Actors)
	{
		ToggleSound(Actor, IsEnable);
	}

	for (TObjectIterator<UAudioComponent> It; It; ++It) {
		UAudioComponent* AudioComp = *It;

		if (AudioComp->GetWorld() == World)
		{
			AudioComp->SetPaused(!IsEnable);
		}
	}

}

void AVisualEffectsController::ToggleSound(AActor* Actor, bool IsEnabled)
{
	if (!Actor)
	{
		return;
	}
	TArray<UAudioComponent*> NiagaraComponents;
	Actor->GetComponents<UAudioComponent>(NiagaraComponents);

	for (UAudioComponent* AudioComp : NiagaraComponents)
	{
		if (AudioComp)
		{
			AudioComp->SetHiddenInGame(!IsEnabled, true);

			if (IsEnabled)
			{
				AudioComp->Activate(true);
				AudioComp->SetPaused(false);
				
			}
			else {
				AudioComp->Deactivate();
				AudioComp->SetPaused(true);
			}
		}
	}
}

//void AVisualEffectsController::ActivateFire(E entity) {
//
//}

