// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AppConstEnumStruct.h"
#include "EntityManager.h"


/**
 * 
 */
class METAVERSE_API ProtocolAdapter
{
public:
	ProtocolAdapter();
	virtual void InitializeAdapter() = 0;
	virtual void Update(float deltaTime,double appTime) = 0;
	virtual FEntityState GetEntityUpdate(FEntityID id) = 0;
	virtual void CloseNetwork() = 0;
	bool bIsJoined = false;
	~ProtocolAdapter();
};
