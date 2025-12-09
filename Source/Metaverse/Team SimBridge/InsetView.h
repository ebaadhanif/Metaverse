// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "InsetView.generated.h"
UCLASS()
class METAVERSE_API AInsetView : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInsetView();
	UWidgetComponent* WidgetComponent=nullptr;
	APlayerCameraManager* CameraManager=nullptr;
	FVector CameraLocation;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TSubclassOf<UUserWidget> InsetViewClass;
	int Index;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetIndex(int _index) { Index = _index; }
	int GetIndex() { return Index; }

	
};
