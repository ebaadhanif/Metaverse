// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AppConstEnumStruct.h"
#include "../Team Visioneers/EntityListUI.h"
#include "../Team Visioneers/LabelManager.h"
//#include "../Team Visioneers/ConfigMenuWidget.h"
#include "../Team RenderStorm/CoveragesManager.h"



class UIManager;
class AEntityBase;
class UCoveragesManager;
class ProtocolAdapter;
//Singleton Class
class METAVERSE_API EntityManager
{
private:

	static EntityManager* m_pEntityManagerInstance;
	TArray<AEntityBase*> m_RemoteEntitiesList;
	TMap <FEntityID, AEntityBase*>m_RemoteEntitiesMap;
	ProtocolAdapter* m_pProtocolAdapter;
	EntityManager();
	bool bisBattlespaceModeEnabled = false;
	ModelVisualMode VisualMode = ModelVisualMode::TexturedMode;

public:

	bool showLocklines = true;
	bool blinkOnSpawnAndDestroy = true;
	bool bRingsVisible = true;
	ELockLineType GLockLineType = ELockLineType::All;

public:
	void ShowTexturedModel();
	void ShowColoredModel();
	void ShowMil2525Model();

	void ToggleBattleSpaceMode();
	ModelVisualMode GetModeVisualMode();
	bool IsInBattlespaceMode();
	UCoveragesManager* CoveragesManager;
	int duplicate = 0;
	AEntityBase* pEntityBase;
	static EntityManager* GetEntityManagerInstance();
	void AddEntity(FEntityState addedEntityState);
	void RemoveEntity(FEntityID entityid, bool flag);
	AEntityBase* getEntityById(FEntityID ID);
	FEntityState UpdateEntity(FEntityID entityId);
	void SetProtocolAdapterPtr(ProtocolAdapter* protcolAdapter);
	TArray<AEntityBase*> getRemoteEntitiesList();
	const TArray<AEntityBase*>& GetEntityList() const;
	UEntityListUI* EntityListWidget;
	~EntityManager();

	AEntityBase* GetEntity();
	void SetAllMil2525Height();

};
