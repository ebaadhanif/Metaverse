// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AppConstEnumStruct.h"

/**
 * 
 */
class METAVERSE_API Mil2525Manager
{
private:
	static Mil2525Manager* m_pMil2525ManagerInstance;
public:
	static Mil2525Manager* GetMil2525ManagerInstance();
	UWorld* worldPtr = nullptr;
	TMap<FEntityType, FString> ObjectTypeMap;
	UMaterialInterface* BillbordMaterial = nullptr;
public:
	Mil2525Manager();
	~Mil2525Manager();
	void LoadFileData();

	UTexture2D* LoadMil2525Sprite(FEntityType Entity, EForceType Force);
	void UpdateMil2525Symbol(UMaterialInstanceDynamic* DynamicMaterial, ELocalHealth Health);
	UMaterialInstanceDynamic* SetupMil2525Material(FEntityType Entity, EForceType Force);
	float SetMil2525Height(float Height);
	FString GetUnknownEntity(FEntityType entityType);

};
