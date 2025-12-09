// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RemoteArmoredVehicle.h"
#include "RemoteGeneralVehicle.h"
#include "RemoteRotorcraft.h"
#include "RemoteShips.h"
#include "RemoteFixedWingAircraft.h"
#include "RemoteRadar.h"
#include "RemoteRadio.h"
#include "RemoteAnimal.h"
#include "RemoteChaff.h"
#include "RemoteFlare.h"
#include "RemoteHuman.h"
#include "RemoteStructure.h"
#include "RemoteOtherCultureFeature.h"
#include "RemoteVegetation.h"
#include "RemoteMissile.h"
#include "RemoteBomb.h"
#include "RemoteShell.h"
#include"RemoteMunitionLauncher.h"
#include "AppConstEnumStruct.h"


/**
 * 
 */
//Singleton Class
class METAVERSE_API RemoteEntityFactory
{
private:
	static RemoteEntityFactory* m_pRemoteEntityFactoryInstance;
	UWorld* worldPtr = nullptr;
	RemoteEntityFactory();
	TMap<FEntityType, int> ObjectTypeMap;
	TMap<FEntityType, int> EntityRangeMap;
public:
	static RemoteEntityFactory* GetRemoteEntityFactoryInstance();
	AEntityBase* GetRemoteEntityObj(FEntityType entityType);
	void SetWorld(UWorld* world);
	void LoadObjectTypesEnumFile();
	int GetRadarRange(FEntityType entityType);
	//ERemoteEntityType GetMissingRemoteEntityType(FEntityType entityType);
	ERemoteEntityType GetUnknownEntity(FEntityType entityType);
	~RemoteEntityFactory();
	
};
