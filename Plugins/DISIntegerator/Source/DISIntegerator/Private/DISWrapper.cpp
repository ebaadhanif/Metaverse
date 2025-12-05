// Fill out your copyright notice in the Description page of Project Settings.


#include "DISWrapper.h"

THIRD_PARTY_INCLUDES_START

#pragma warning(push)
#pragma warning(disable: 4996)  // 'sprintf': deprecated
#pragma warning(disable: 5040)  // exception specs deprecated
#pragma warning(disable: 4141)  // dllimport used more than once
#pragma warning(disable: 4005)  // macro redefinition
#pragma warning(disable: 4265)  // non-virtual destructors

#pragma push_macro("check")
#undef check
#include <DISUtils/RemoteAirCraft.h>
#include <DISUtils/DISHandler.h>
#include <DISUtils/PDUManager.h>
#include <DISUtils/RemoteEntitiesManager.h>
#include <DISUtils/DISNetworkConfigApplicationManager.h>
#include <DISEnums/AFISE/ApplicationID.h>
#pragma pop_macro("check")

#pragma warning(pop)

THIRD_PARTY_INCLUDES_END
#include<unordered_map>

#include <DISIntegerator.h>
#include "HAL/PlatformProcess.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "Misc/MessageDialog.h"

FEntityAddDelegate DISWrapper::entityAddDelegate;
FEntityRemoveDelegate DISWrapper::entityRemoveDelegate;
FAppExitDelegate DISWrapper::appExitDelegate;
FEntityDetonationDelegate DISWrapper::entityDetonationDelegate;
FEntityFireDelegate DISWrapper::entityFireDelegate;
FStartResumeDelegate DISWrapper::startResumeDelegate;
FStopFreezeDelegate DISWrapper::stopFreezeDelegate;

DISWrapper::DISWrapper()
{

}

void DISWrapper::AddEntityCallback(DIS::EntityID ID, FEntityInfo entityInfo)
{
	entityAddDelegate.Broadcast(ID, entityInfo);
}

void DISWrapper::RemoveEntityCallback(DIS::EntityID& ID, bool bvar)
{
	entityRemoveDelegate.Broadcast(ID, bvar);
}

void DISWrapper::DetonationCallback(DIS::DetonationMessage& detonationMsg)
{
	entityDetonationDelegate.Broadcast(detonationMsg);
}

void DISWrapper::FireCallback(DIS::FireMessage& fireMsg)
{
	entityFireDelegate.Broadcast(fireMsg);
}

void DISWrapper::StartResumeCallback(DIS::StartResumeMessage& startResumeMessage)
{
	startResumeDelegate.Broadcast(true);
}

void DISWrapper::StopFreezeCallback(DIS::StopFreezeMessage& stopFreezeMessage)
{
	stopFreezeDelegate.Broadcast(true);
}

void DISWrapper::ReleaseDIS()
{
	bool release = CDISHandler::GetInstance()->Release();
	CRemoteEntitiesManager::GetInstance()->ClearList();

	if (Handle) {
		FPlatformProcess::FreeDllHandle(Handle);
		Handle = nullptr;
	}
}

void DISWrapper::CallbackFunc(bool success)
{
	if (!success)
	{
		CDISHandler::GetInstance()->Release();
		return;
	}

	bool isInitialized = CDISHandler::GetInstance()->IsInitialized();
	if (isInitialized)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, "Initialization True");
	}
	else GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, "Initialization False");

	CRemoteEntitiesManager::GetInstance()->EnableRemoteEntities({ RemoteEntityType::ALL_ENTITIES });
	DISWrapper* instance;
	CRemoteEntitiesManager::GetInstance()->AddEntityAddtionCallback([instance](const CRemoteEntity& entity)
		{
			CRemoteEntity& obj = const_cast<CRemoteEntity&>(entity);

			FVector location;
			location.X = obj.GetEntityGeodeticPosition().latitude;
			location.Y = obj.GetEntityGeodeticPosition().longitude;
			location.Z = obj.GetEntityGeodeticPosition().altitude * METERS_PER_FEET;

			FRotator orientation;
			orientation.Pitch = obj.GetPitch();
			orientation.Yaw = obj.GetYaw();
			orientation.Roll = obj.GetRoll();

			FEntityInfo entityInfoObj;
			entityInfoObj.EntityType = obj.GetEntityType();
			entityInfoObj.RemoteEntityType = obj.GetRemoteEntityType();
			entityInfoObj.Orientation = orientation;
			entityInfoObj.Position = location;
			entityInfoObj.CallSign = UTF8_TO_TCHAR(obj.GetCallSign().c_str());
			entityInfoObj.forceType = obj.GetForceID();
			entityInfoObj.speedInKnots = obj.GetSpeedInKnots();
			AddEntityCallback(obj.GetEntityID(), entityInfoObj);
		});

	PDUManager::GetInstance()->AddEntityStateCallback([](const DIS::EntityStateMessage es) {
		int a = 0;
		});

	CRemoteEntitiesManager::GetInstance()->AddEntityRemovalCallback([instance](const DIS::EntityID& entityID, bool booleanVal)
		{
			DIS::EntityID& Id = const_cast<DIS::EntityID&>(entityID);
			RemoveEntityCallback(Id, booleanVal);

		});

	PDUManager::GetInstance()->AddDetonationCallback([instance](const DIS::DetonationMessage& detonationMsg)
		{
			DIS::DetonationMessage& msg = const_cast<DIS::DetonationMessage&>(detonationMsg);
			DetonationCallback(msg);
		});

	PDUManager::GetInstance()->AddFireCallback([instance](const DIS::FireMessage& fireMsg)
		{
			DIS::FireMessage& msg = const_cast<DIS::FireMessage&>(fireMsg);
			FireCallback(msg);
		});

	PDUManager::GetInstance()->AddStartResumeCallback([instance](const DIS::StartResumeMessage& startResumeMsg)
		{
			DIS::StartResumeMessage& msg = const_cast<DIS::StartResumeMessage&>(startResumeMsg);
			StartResumeCallback(msg);
		});
	
	PDUManager::GetInstance()->AddStopFreezeCallback([instance](const DIS::StopFreezeMessage& stopFreezeMsg)
		{
			DIS::StopFreezeMessage& msg = const_cast<DIS::StopFreezeMessage&>(stopFreezeMsg);
			StopFreezeCallback(msg);
		});
	
}

void DISWrapper::Update(float deltaTime, double appTime)
{
	CDISHandler::GetInstance()->Update(deltaTime, appTime);
}

FEntityInfo DISWrapper::GetEntityUpdate(DIS::EntityID Id)
{
	auto entity = CRemoteEntitiesManager::GetInstance()->GetRemoteEntityByEntityID(Id);
	FEntityInfo entityUpdateInfoStruct;
	if (entity)
	{
		if (entity->GetEntityType().getEntityKind() == 1 && entity->GetEntityType().getDomain() == 2) //air entities
		{
			CRemoteAircraft* aircraft = dynamic_cast<CRemoteAircraft*>(entity);
			if (aircraft)
			{
				entityUpdateInfoStruct.isLandingGearExtended = aircraft->IsLandingGearExtended();
				entityUpdateInfoStruct.WeightOnWheels = aircraft->GetEntityAppearence().WeightOnWheels;
				entityUpdateInfoStruct.isNavLightsOn= aircraft->IsNavigationLightsOn();
			}

		}
		
		entityUpdateInfoStruct.Orientation.Pitch = entity->GetPitch();
		entityUpdateInfoStruct.Orientation.Yaw = entity->GetYaw();
		entityUpdateInfoStruct.Orientation.Roll = entity->GetRoll();

		entityUpdateInfoStruct.Position.X = entity->GetEntityGeodeticPosition().latitude;
		entityUpdateInfoStruct.Position.Y = entity->GetEntityGeodeticPosition().longitude;
		entityUpdateInfoStruct.Position.Z = entity->GetEntityGeodeticPosition().altitude;

		entityUpdateInfoStruct.EntityType = entity->GetEntityType();
		entityUpdateInfoStruct.RemoteEntityType = entity->GetRemoteEntityType();
		entityUpdateInfoStruct.health = entity->GetDamageState();
		entityUpdateInfoStruct.speedInKnots = entity->GetSpeedInKnots();
		auto systems = entity->GetElectronicmagneticEmissionsData().getSystems();
		if (systems.empty())
		{
			entityUpdateInfoStruct.isSensorOn = false;
		}
		else
		{
			entityUpdateInfoStruct.isSensorOn = true;
			TArray<DIS::EntityID>TempTrackedEntitiesList;
			TArray<DIS::EntityID>TempLockedEntitiesList;

			for (auto system : systems)
			{
				for (auto beamRecord : system.getBeamDataRecords())
				{
					for (auto trackJamTargets : beamRecord.getTrackJamTargets())
					{
						TempTrackedEntitiesList.Add(trackJamTargets.getEntityID());
						if (beamRecord.getBeamFunction() == 3 || beamRecord.getBeamFunction() == 5 || beamRecord.getBeamFunction() == 4)
						{
							TempLockedEntitiesList.Add(trackJamTargets.getEntityID());
						}
						
					}
				}
			}

			entityUpdateInfoStruct.TrackedEntitiesList = TempTrackedEntitiesList;
			entityUpdateInfoStruct.LockedEntitiesList = TempLockedEntitiesList;

		}
		
	}
	return entityUpdateInfoStruct;
}

void DISWrapper::EntityStateCallbackFunc()
{

}

void DISWrapper::Initialize()
{
	FString PluginBaseDir = IPluginManager::Get().FindPlugin(TEXT("DISIntegerator"))->GetBaseDir();
	FString DllName = TEXT("DISV7.dll");
	FString DllPath = FPaths::Combine(PluginBaseDir, TEXT("Binaries/Win64"), DllName);
	Handle = FPlatformProcess::GetDllHandle(*DllPath);

	if (!Handle)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to manually load DIS DLL: %s"), *DllPath);
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("Loaded DIS DLL: %s"), *DllPath);

	FString ArchiveFolderPath = FPaths::ProjectPluginsDir() / TEXT("DISIntegerator/Content/DIS/");

	//if (FPaths::DirectoryExists(ArchiveFolderPath))
	{
		char* DISArchiveFolderPath = TCHAR_TO_UTF8(*ArchiveFolderPath);
		CDISHandler::GetInstance()->Initialize(DIS::ENUMS::AFISE::ApplicationID::ATC_INSTRUCTOR, DIS::Endian::BIG, CallbackFunc, DISArchiveFolderPath);/**/
	}
	/*else
	{
		UE_LOG(LogTemp, Error, TEXT("DIS configuration folder not found: %s"), *ArchiveFolderPath);
	}*/
}



DISWrapper::~DISWrapper()
{
}
