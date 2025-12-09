// Fill out your copyright notice in the Description page of Project Settings.


#include "PCGLoadTracker.h"

void UPCGLoadTracker::RegisterShapeFile(const FString& ShapeFileID)
{
	PendingShapeFiles.Add(ShapeFileID);
	bAllDone = false;
}

void UPCGLoadTracker::MarkShapeFileLoaded(const FString& ShapeFileID)
{
	if (!PendingShapeFiles.Contains(ShapeFileID)) {
		return;
	}

	PendingShapeFiles.Remove(ShapeFileID);
	OnShapeFileLoaded.Broadcast(ShapeFileID);

	if (PendingShapeFiles.Num() == 0 && !bAllDone) {
		bAllDone = true;
		OnAllShapefilesLoaded.Broadcast();
	}
}

bool UPCGLoadTracker::IsAllDataLoaded() const
{
	return bAllDone;
}
