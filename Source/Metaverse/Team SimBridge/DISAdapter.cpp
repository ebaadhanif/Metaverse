// Fill out your copyright notice in the Description page of Project Settings.


#include "DISAdapter.h"
#include "../Team SimBridge/EntityBase.h"
#include "../Team RenderStorm/DetonationController.h"
DISAdapter::DISAdapter()
{

	m_disWrapperObj.entityAddDelegate.AddRaw(this, &DISAdapter::AddEntity);
	m_disWrapperObj.entityRemoveDelegate.AddRaw(this, &DISAdapter::RemoveEntity);
	m_disWrapperObj.appExitDelegate.AddRaw(this, &DISAdapter::CloseApp);
	m_disWrapperObj.entityDetonationDelegate.AddRaw(this, &DISAdapter::DetonateEntity);
	m_disWrapperObj.entityFireDelegate.AddRaw(this, &DISAdapter::EntityFire);
	m_disWrapperObj.startResumeDelegate.AddRaw(this, &DISAdapter::StartResumeApp);
	m_disWrapperObj.stopFreezeDelegate.AddRaw(this, &DISAdapter::StopFreezeApp);

}

void DISAdapter::CallbackFunc(bool success)
{

}

void DISAdapter::InitializeAdapter()
{
	m_disWrapperObj.Initialize();
}

void DISAdapter::Update(float deltaTime, double appTime)
{
	m_disWrapperObj.Update(deltaTime, appTime);
}

void DISAdapter::AddEntity(DIS::EntityID id, FEntityInfo entityInfo)
{
	//return;
	FEntityState addedEntityState;

	addedEntityState.Id.AppID = id.getApplication();
	addedEntityState.Id.SiteID = id.getSite();
	addedEntityState.Id.EntityID = id.getEntity();

	addedEntityState.entityType.category = entityInfo.EntityType.getCategory();
	addedEntityState.entityType.subcategory = entityInfo.EntityType.getSubcategory();
	addedEntityState.entityType.domain = entityInfo.EntityType.getDomain();
	addedEntityState.entityType.country = entityInfo.EntityType.getCountry();
	addedEntityState.entityType.extra = entityInfo.EntityType.getExtra();
	addedEntityState.entityType.entiyKind = entityInfo.EntityType.getEntityKind();
	addedEntityState.entityType.specific = entityInfo.EntityType.getSpecific();

	addedEntityState.RemoteEntityType = static_cast<ERemoteEntityType>(entityInfo.RemoteEntityType);
	addedEntityState.GeodeticLocation = entityInfo.Position;
	addedEntityState.Orientation = entityInfo.Orientation;
	addedEntityState.CallSign = entityInfo.CallSign;
	addedEntityState.forceType = static_cast<EForceType>(entityInfo.forceType);
	addedEntityState.speedInKnots = entityInfo.speedInKnots;

	AsyncTask(ENamedThreads::GameThread, [this, addedEntityState]() {
		EntityManager::GetEntityManagerInstance()->AddEntity(addedEntityState);
		});

}

void DISAdapter::RemoveEntity(DIS::EntityID id, bool flag)
{
	FEntityID entityID;
	entityID.AppID = id.getApplication();
	entityID.SiteID = id.getSite();
	entityID.EntityID = id.getEntity();

	AsyncTask(ENamedThreads::GameThread, [this, entityID]() {
		EntityManager::GetEntityManagerInstance()->RemoveEntity(entityID, false);
		});

}

void DISAdapter::DetonateEntity(DIS::DetonationMessage detonationMsg)
{
	FDetonationMessage msg;
	FEntityID TargetEntityID;
	TargetEntityID.AppID = detonationMsg.targetEntityID.getApplication();
	TargetEntityID.SiteID = detonationMsg.targetEntityID.getSite();
	TargetEntityID.EntityID = detonationMsg.targetEntityID.getEntity();
	msg.targetEntityID = TargetEntityID;

	FEntityID SourceEntityID;
	SourceEntityID.AppID = detonationMsg.sourceEntityID.getApplication();
	SourceEntityID.SiteID = detonationMsg.sourceEntityID.getSite();
	SourceEntityID.EntityID = detonationMsg.sourceEntityID.getEntity();
	msg.sourceEntityID = SourceEntityID;

	FEntityID ExplodingEntityID;
	ExplodingEntityID.AppID = detonationMsg.explodingEntityID.getApplication();
	ExplodingEntityID.SiteID = detonationMsg.explodingEntityID.getSite();
	ExplodingEntityID.EntityID = detonationMsg.explodingEntityID.getEntity();
	msg.explodingEntityID = ExplodingEntityID;

	msg.WorldLocation.X = detonationMsg.locationInWorldCoordinates.latitude;
	msg.WorldLocation.Y = detonationMsg.locationInWorldCoordinates.longitude;
	msg.WorldLocation.Z = detonationMsg.locationInWorldCoordinates.altitude;

	AsyncTask(ENamedThreads::GameThread, [this, detonationMsg]()
		{
			UDetonationController::Get()->SpawnDetonationEffectOnTerrain(detonationMsg.locationInWorldCoordinates.latitude, detonationMsg.locationInWorldCoordinates.longitude);
		});

}

void DISAdapter::CloseApp()
{
	FPlatformMisc::RequestExit(false);
}


void DISAdapter::EntityFire(DIS::FireMessage fireMsg)
{
	FFireMessage msg;

	msg.targetEntityID.AppID = fireMsg.targetEntityID.getApplication();
	msg.targetEntityID.SiteID = fireMsg.targetEntityID.getSite();
	msg.targetEntityID.EntityID = fireMsg.targetEntityID.getEntity();

	msg.firingEntityID.AppID = fireMsg.firingEntityID.getApplication();
	msg.firingEntityID.SiteID = fireMsg.firingEntityID.getSite();
	msg.firingEntityID.EntityID = fireMsg.firingEntityID.getEntity();

	msg.munitionExpendibleID.AppID = fireMsg.munitionExpendableID.getApplication();
	msg.munitionExpendibleID.SiteID = fireMsg.munitionExpendableID.getSite();
	msg.munitionExpendibleID.EntityID = fireMsg.munitionExpendableID.getEntity();

	msg.geodeticLocation.X = fireMsg.geodeticLocation.latitude;
	msg.geodeticLocation.Y = fireMsg.geodeticLocation.longitude;
	msg.geodeticLocation.Z = fireMsg.geodeticLocation.altitude;

	AEntityBase* firingEntity = EntityManager::GetEntityManagerInstance()->getEntityById(msg.firingEntityID);

	AsyncTask(ENamedThreads::GameThread, [this, fireMsg, firingEntity]()
		{
			if (firingEntity)
			{
				firingEntity->Fire();
			}

		});
}

void DISAdapter::StartResumeApp(bool startResumeMsg)
{
	bool msg = startResumeMsg;
}

void DISAdapter::StopFreezeApp(bool stopFreezeMsg)
{
	bool msg = stopFreezeMsg;
}



FEntityState DISAdapter::GetEntityUpdate(FEntityID id)
{
	DIS::EntityID entityIdObj;
	entityIdObj.setEntity(id.EntityID);
	entityIdObj.setSite(id.SiteID);
	entityIdObj.setApplication(id.AppID);

	FEntityInfo entitiyUpdatedinfo;
	entitiyUpdatedinfo = m_disWrapperObj.GetEntityUpdate(entityIdObj);
	FEntityState  entityState;
	entityState.Id = id;
	entityState.Orientation = entitiyUpdatedinfo.Orientation;
	entityState.GeodeticLocation = entitiyUpdatedinfo.Position;
	entityState.health = static_cast<ELocalHealth>(entitiyUpdatedinfo.health);
	entityState.isSensorOn = entitiyUpdatedinfo.isSensorOn;
	entityState.speedInKnots = entitiyUpdatedinfo.speedInKnots;
	entityState.WeightOnWheels = entitiyUpdatedinfo.WeightOnWheels;
	entityState.isLandingGearExtended = entitiyUpdatedinfo.isLandingGearExtended;
	entityState.isNavLightsOn = entitiyUpdatedinfo.isNavLightsOn;
	if (!entitiyUpdatedinfo.TrackedEntitiesList.IsEmpty())
	{
		FEntityID tempTrackedEntityId;
		for (auto trackedEntity : entitiyUpdatedinfo.TrackedEntitiesList)
		{
			tempTrackedEntityId.AppID = trackedEntity.getApplication();
			tempTrackedEntityId.SiteID = trackedEntity.getSite();
			tempTrackedEntityId.EntityID = trackedEntity.getEntity();
			entityState.TrackedEntitiesList.Add(tempTrackedEntityId);
		}
		FEntityID tempLockedEntityId;
		if (!entitiyUpdatedinfo.LockedEntitiesList.IsEmpty())
		{
			for (auto lockedEntity : entitiyUpdatedinfo.LockedEntitiesList)
			{
				tempLockedEntityId.AppID = lockedEntity.getApplication();
				tempLockedEntityId.SiteID = lockedEntity.getSite();
				tempLockedEntityId.EntityID = lockedEntity.getEntity();
				entityState.LockedEntitiesList.Add(tempLockedEntityId);
			}
		}

	}
	return entityState;
}

void DISAdapter::CloseNetwork()
{
	m_disWrapperObj.ReleaseDIS();
}

DISAdapter::~DISAdapter()
{
}

