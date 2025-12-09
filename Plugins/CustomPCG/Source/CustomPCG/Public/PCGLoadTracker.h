// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PCGLoadTracker.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShapeFileLoaded, const FString&, ShapefileID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllShapefilesLoaded);


UCLASS()
class CUSTOMPCG_API UPCGLoadTracker : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	FOnShapeFileLoaded OnShapeFileLoaded;
	FOnAllShapefilesLoaded OnAllShapefilesLoaded;
	 

	void RegisterShapeFile(const FString& ShapeFileID);
	void MarkShapeFileLoaded(const FString& ShapeFileID);

	UFUNCTION(BlueprintCallable)
	bool IsAllDataLoaded() const;

private:
	TSet<FString> PendingShapeFiles;
	bool bAllDone = false;

};
