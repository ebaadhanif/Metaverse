// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityManager.h"
#include "ProtocolAdapter.h"
#include "../Team Visioneers/Menus/UIManager.h"
#include "RemoteEntityFactory.h"


EntityManager::EntityManager()
{
	m_RemoteEntitiesList.Empty();
}

void EntityManager::ShowTexturedModel()
{
	VisualMode = ModelVisualMode::TexturedMode;

}

void EntityManager::ShowColoredModel()
{
	VisualMode = ModelVisualMode::BattleSpaceMode;


}

void EntityManager::ShowMil2525Model()
{
	VisualMode = ModelVisualMode::Mil2525Mode;
}

void EntityManager::ToggleBattleSpaceMode()
{

}

ModelVisualMode EntityManager::GetModeVisualMode()
{
	return VisualMode;
}



bool EntityManager::IsInBattlespaceMode()
{
	return bisBattlespaceModeEnabled;
}

EntityManager* EntityManager::m_pEntityManagerInstance = NULL;
EntityManager* EntityManager::GetEntityManagerInstance()
{
	if (m_pEntityManagerInstance == nullptr)
	{
		m_pEntityManagerInstance = new EntityManager();
	}
	return m_pEntityManagerInstance;
}

void EntityManager::AddEntity(FEntityState addedEntityState)
{
	for (auto* entity : m_RemoteEntitiesList)
	{
		if (entity->GetEntityId() == addedEntityState.Id)
		{
			duplicate++;
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, FString::Printf(TEXT("Duplicate: %d"), duplicate));
			return;
		}
	}

	pEntityBase = RemoteEntityFactory::GetRemoteEntityFactoryInstance()->GetRemoteEntityObj(addedEntityState.entityType);
	if (pEntityBase != nullptr)
	{
		int radarRange = RemoteEntityFactory::GetRemoteEntityFactoryInstance()->GetRadarRange(addedEntityState.entityType);
		pEntityBase->Initialize(addedEntityState, radarRange);
		m_RemoteEntitiesList.Add(pEntityBase);
		LabelManager::AttachLabelToEntity(pEntityBase);
		//pEntityBase->EntityStateEffect(3.0f);


		// dummy check

		//pEntityBase->SetActorEnableCollision(true);

		if (pEntityBase->GetRadarRange() > 0) {
			UCoveragesManager::GetInstance()->AddEntityToCoveragesList(pEntityBase);
		}

		if (pEntityBase->GetRemoteEntityType() == ERemoteEntityType::FIXEDWING_AIRCRAFT || pEntityBase->GetRemoteEntityType() == ERemoteEntityType::MISSILE)
		{
			pEntityBase->setRibbon();
			pEntityBase->setVerticalRibbon();
			pEntityBase->setForwardVector();
		}
		pEntityBase->ImportEntityModel();
		UIManager::GetInstance()->GetEntityListPtr()->AddEntityCallsignTolist(pEntityBase);
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, FString::Printf(TEXT("Total Entities: %d"), m_RemoteEntitiesList.Num()));

		/*ToggleBattleSpaceMode();*/
	}
}

void EntityManager::RemoveEntity(FEntityID id, bool flag)
{
	if (!m_RemoteEntitiesList.IsEmpty())
	{
		for (int32 index = m_RemoteEntitiesList.Num() - 1; index >= 0; --index)
		{
			if (m_RemoteEntitiesList[index]->GetEntityId() == id)
			{
				UIManager::GetInstance()->GetEntityListPtr()->RemoveEntityCallsignFromList(m_RemoteEntitiesList[index]);
				LabelManager::RemoveLabelFromEntity(m_RemoteEntitiesList[index]);
				if (m_RemoteEntitiesList[index]->GetRadarRange() > 0) {
					UCoveragesManager::GetInstance()->RemoveEntity(m_RemoteEntitiesList[index]);
				}
				//m_RemoteEntitiesList[index]->EntityStateEffect(3.0f);
				m_RemoteEntitiesList[index]->Destroy();
				m_RemoteEntitiesList.RemoveAt(index);

			}
		}
	}
}

AEntityBase* EntityManager::getEntityById(FEntityID id)
{
	for (auto* entity : m_RemoteEntitiesList)
	{
		if (entity->GetEntityId() == id)
		{
			return entity;
		}
	}
	return nullptr;
}

FEntityState EntityManager::UpdateEntity(FEntityID entityId)
{
	return m_pProtocolAdapter->GetEntityUpdate(entityId);
}

void EntityManager::SetProtocolAdapterPtr(ProtocolAdapter* protcolAdapter)
{
	m_pProtocolAdapter = protcolAdapter;
}

TArray<AEntityBase*> EntityManager::getRemoteEntitiesList()
{
	return m_RemoteEntitiesList;
}

EntityManager::~EntityManager()
{
	if (!m_RemoteEntitiesList.IsEmpty())
	{
		for (int32 index = m_RemoteEntitiesList.Num() - 1; index >= 0; --index)
		{
			m_RemoteEntitiesList[index]->Destroy();
			m_RemoteEntitiesList.RemoveAt(index);
		}
		m_RemoteEntitiesList.Empty();

	}
}

const TArray<AEntityBase*>& EntityManager::GetEntityList() const
{
	return m_RemoteEntitiesList;
}



AEntityBase* EntityManager::GetEntity()
{
	return m_RemoteEntitiesList[0];
}
void EntityManager::SetAllMil2525Height()
{

	for (auto* entity : m_RemoteEntitiesList)
	{

		entity->Mil2525Height = Mil2525Manager::GetMil2525ManagerInstance()->SetMil2525Height(entity->Mil2525Height);
	}

}