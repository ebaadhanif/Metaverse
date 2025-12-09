 //Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InsetView.h"
#include "InsetViewManager.generated.h"

UCLASS()
class METAVERSE_API AInsetViewManager : public AActor
{
	GENERATED_BODY()
	
protected:	
	// Sets default values for this actor's properties
	AInsetViewManager();
	APlayerCameraManager* CameraManager;
	AActor* InsetViewParentActor = nullptr;
	bool FirstTime = false;
	bool FirstTime1 = false;
	int CameraDistance;
	FVector loc;
	FRotator rot;
	float RightSideAngle = 30;
	float LeftSideAngle = -30;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TArray<AInsetView*> InsetViewList;
	int GetNextViewIndex();
	void SetInsetViewPivot(AInsetView* insetVIew);
	void SetInsetViewPosition(AInsetView* insetVIew);
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnInsetView();
	void DeleteInsetView(int Index);
	void InsetViewFaceCamera();
	void PositionInsetView(AInsetView* InsetViewActor);
	void PositionCircularInsetView(AInsetView* InsetViewActor, FVector SpawnLoc);
	void PositionCircularRefToCam(AInsetView* InsetViewActor);
	
};
