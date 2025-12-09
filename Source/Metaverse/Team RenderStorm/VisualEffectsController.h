// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "VisualEffectsController.generated.h"

UCLASS()
class METAVERSE_API AVisualEffectsController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVisualEffectsController();
	static AVisualEffectsController* instance;
	static AVisualEffectsController* getInstance();
	void spawnBlastEffect(FVector Location);

	void toggleEffectsVisibility(bool isVisible);
	void ToggleNiagaraComponentVisibility(AActor* Actor, bool IsEnabled);
	void toggleSounds(bool IsEnable);
	void ToggleSound(AActor* Actor, bool IsVisible);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Beam")
	UNiagaraSystem* DetonationNiagaraSystem = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Beam")
	UNiagaraComponent* DetonationNiagaraComponent = nullptr;

	UWorld* World = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
