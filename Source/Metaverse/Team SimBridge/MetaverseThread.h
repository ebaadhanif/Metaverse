// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"
#include "ProtocolAdapter.h"
#include "../Team SimBridge/EntityManager.h"

/**
 * 
 */
class METAVERSE_API MetaverseThread: public FRunnable
{
public:
	MetaverseThread();
	virtual ~MetaverseThread();

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;
	static MetaverseThread* StartThread();
	void InitializeAdapter(ProtocolAdapter* _protocolAdapter);
	void EnsureCompletion();
	void MetaverseCallback();
	double startTime = 0, deltaTime = 0, apptime = 0;

private:
	int fps = 0;
	FRunnableThread* Thread;
	FThreadSafeCounter StopTaskCounter;
	ProtocolAdapter* protocolAdapter = nullptr;
	bool bIsRunning;
	bool bIsInitialized = false;
};
