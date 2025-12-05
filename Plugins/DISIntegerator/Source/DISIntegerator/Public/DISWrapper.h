#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"
#include <DIS7/EntityID.h>
#include <DIS7/EntityType.h>
#include<DISUtils/DISDefinitions.h>
//#include "DISDelegate.h"


struct FEntityInfo
{
	DIS::EntityType EntityType;
	int RemoteEntityType;
	FString CallSign;
	FRotator Orientation;
	FVector Position;
	int forceType;
	TArray<DIS::EntityID> TrackedEntitiesList;
	DIS::LocalHealth health;
	bool isSensorOn;
	short speedInKnots;
	TArray<DIS::EntityID> LockedEntitiesList;
	int WeightOnWheels;
	bool isLandingGearExtended;
	bool isNavLightsOn;
	FEntityInfo()
	{
		Position = FVector::ZeroVector;
		Orientation = FRotator::ZeroRotator;
		isSensorOn = false;
		WeightOnWheels = 0;
		isLandingGearExtended = false;
		isNavLightsOn = false;
	}
};

//delegates
DECLARE_MULTICAST_DELEGATE_TwoParams(FEntityAddDelegate, DIS::EntityID,FEntityInfo);
DECLARE_MULTICAST_DELEGATE_TwoParams(FEntityRemoveDelegate, DIS::EntityID, bool);
DECLARE_MULTICAST_DELEGATE(FAppExitDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FEntityDetonationDelegate, DIS::DetonationMessage);
DECLARE_MULTICAST_DELEGATE_OneParam(FEntityFireDelegate, DIS::FireMessage);
DECLARE_MULTICAST_DELEGATE_OneParam(FStartResumeDelegate, bool);
DECLARE_MULTICAST_DELEGATE_OneParam(FStopFreezeDelegate, bool);


class DISINTEGERATOR_API DISWrapper
{
public:
	
	static FEntityAddDelegate entityAddDelegate;
	static FEntityRemoveDelegate entityRemoveDelegate; 
	static FAppExitDelegate appExitDelegate;
	static FEntityDetonationDelegate entityDetonationDelegate;
	static FEntityFireDelegate entityFireDelegate;
	static FStartResumeDelegate startResumeDelegate;
	static FStopFreezeDelegate stopFreezeDelegate;

	void* Handle;

public:
	DISWrapper();
	void Initialize();
	static void CallbackFunc(bool success);
	void Update(float deltaTime, double appTime);
	FEntityInfo GetEntityUpdate(DIS::EntityID Id);
	void EntityStateCallbackFunc();
	static void AddEntityCallback(DIS::EntityID ID, FEntityInfo entityInfo);
	static void RemoveEntityCallback(DIS::EntityID& ID, bool bvar);
	static void DetonationCallback(DIS::DetonationMessage& detonationMsg);
	static void FireCallback(DIS::FireMessage& fireMsg);
	static void StartResumeCallback(DIS::StartResumeMessage& startResumeMessage);
	static void StopFreezeCallback(DIS::StopFreezeMessage& stopFreezeMessage);
	void ReleaseDIS();
	~DISWrapper();
};
