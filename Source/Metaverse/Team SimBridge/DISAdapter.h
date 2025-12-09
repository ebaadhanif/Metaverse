// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "ProtocolAdapter.h"
#include "EntityManager.h"
#include "DISWrapper.h"

/**
 * 
 */
class METAVERSE_API DISAdapter : public ProtocolAdapter
{
private:
	double TotalElapsedTime;
	DISWrapper m_disWrapperObj;
public:
	DISAdapter();
	static void CallbackFunc(bool success);
	void InitializeAdapter() override;
	void Update(float deltaTime, double appTime) override;
	void AddEntity(DIS::EntityID id, FEntityInfo entityInfo);
	void RemoveEntity(DIS::EntityID id, bool flag);
	void DetonateEntity(DIS::DetonationMessage detonationMsg);
	void EntityFire(DIS::FireMessage fireMsg);
	void StartResumeApp(bool startResumeMsg);
	void StopFreezeApp(bool stopFreezeMsg);
	void CloseApp();
	FEntityState GetEntityUpdate(FEntityID id) override;
	void CloseNetwork() override;
	~DISAdapter();
};
