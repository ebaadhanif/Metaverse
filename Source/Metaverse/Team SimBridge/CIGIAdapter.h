// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProtocolAdapter.h"

/**
 * 
 */
class METAVERSE_API CIGIAdapter : public ProtocolAdapter
{
public:
	CIGIAdapter();
	void InitializeAdapter() override;
	void Update(float deltaTime, double appTime) override;
	FEntityState GetEntityUpdate(FEntityID id) override;
	void CloseNetwork() override;
	~CIGIAdapter();
};
