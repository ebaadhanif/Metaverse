// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PCGPointContent.h"
#include "PCGPolygonContent.h"
#include "PolygonCacheSave.h"
#include "SQLiteDatabase.h"
#include "TimerManager.h"
#include "PCGLoadTracker.h"
#include "PCGManager.generated.h"


UCLASS()
class CUSTOMPCG_API APCGManager : public AActor
{
	GENERATED_BODY()


public:
    APCGManager();
    UGameInstance* GI;
    UPCGLoadTracker* LoadTracker;

    TQueue<UPCGComponent*> pendingPCGActors;
    TArray<UPCGComponent*> activePCGActors;

    virtual void BeginPlay() override;

    void LoadDataforPCGPoint();

    void Testing();

    void InitializeDatabase();

    void LoadDataforPCGPolygon();

    void SetPCGPolygonDataVisibility(bool bVisible);

    FString GetPCGShapeFilesPath();
    
    UFUNCTION()
    void HandleAllPolygonDataLoaded();

    void SetPCGDataVisibility(bool bVisible);

    void SetPCGPointDataVisibility(bool bVisible);
    
    void SetCullDistance(float distanceInMeters);

    static APCGManager* GetInstance();

private:
    static APCGManager* Instance;
    FSQLiteDatabase DB;
    FString ShapeFilesFolderPath;

    TArray<TObjectPtr<APCGPointContent>> PointContents;
    TArray<TObjectPtr<APCGPolygonContent>> PolygonContents;
    UPROPERTY() AActor* PCGPointParent = nullptr;
    FTimerHandle DelayTimeHandle;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};

