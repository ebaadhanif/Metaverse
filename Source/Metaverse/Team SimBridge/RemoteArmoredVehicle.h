// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EntityPlatform.h"
#include "RemoteArmoredVehicle.generated.h"

UCLASS()
class METAVERSE_API ARemoteArmoredVehicle : public AEntityPlatform
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARemoteArmoredVehicle();


	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Niagara")
	//UNiagaraComponent* DustCompLeft = nullptr;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Niagara")
	//UNiagaraComponent* DustCompRight = nullptr;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Niagara")
	//UNiagaraComponent* DestroNiagaraComponent = nullptr;
	////UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Beam")
	////UNiagaraComponent* FireNiagaraComponent = nullptr;

	//// Optional: for convenience if you set the asset in BP instead of C++
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Niagara")
	//UNiagaraSystem* DustSystemLeft = nullptr;
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Niagara")
	//UNiagaraSystem* DustSystemRight = nullptr;
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Niagara")
	//UNiagaraSystem* DestroyNiagaraSystem = nullptr;
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Niagara")
	//UNiagaraSystem* FireNiagaraSystem = nullptr;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Niagara")
	//UNiagaraSystem* FireNiagaraSystem = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	UAudioComponent* EntitySound = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void spawnAndAttachDust();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
