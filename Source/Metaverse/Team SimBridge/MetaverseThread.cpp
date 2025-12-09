// Fill out your copyright notice in the Description page of Project Settings.


#include "MetaverseThread.h"
#include "HAL/PlatformProcess.h"

MetaverseThread::MetaverseThread()
	: Thread(nullptr),
	bIsRunning(true)
{
	Thread = FRunnableThread::Create(this, TEXT("MetaverseThread"), 0, TPri_Normal);
	protocolAdapter = nullptr;
}

MetaverseThread::~MetaverseThread()
{
	if (Thread) {

		Stop();
		EnsureCompletion();
		delete Thread;
		Thread = nullptr;

	}
}

bool MetaverseThread::Init()
{
	return true;
}

uint32 MetaverseThread::Run()
{
	while (bIsRunning && StopTaskCounter.GetValue() == 0) {

		MetaverseCallback();
		FPlatformProcess::Sleep(0.016f);
	}
	return 0;

}

void MetaverseThread::Stop()
{
	bIsRunning = false;
	StopTaskCounter.Increment();

}

void MetaverseThread::Exit()
{

}
MetaverseThread* MetaverseThread::StartThread()
{
	return new MetaverseThread();
}

void MetaverseThread::InitializeAdapter(ProtocolAdapter* _protocolAdapter)
{
	protocolAdapter = _protocolAdapter;
	startTime = FPlatformTime::Seconds();
}

void MetaverseThread::EnsureCompletion()
{
	if (Thread)
	{
		Thread->WaitForCompletion();
	}

}

void MetaverseThread::MetaverseCallback()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Black, FString::Printf(TEXT("Time: %f"), apptime));
	if (protocolAdapter)
	{
		if (!bIsInitialized)
		{
			protocolAdapter->InitializeAdapter();
			bIsInitialized = true;
			protocolAdapter->bIsJoined = true;
		}
		else
		{
			apptime = FPlatformTime::Seconds() - startTime;
			protocolAdapter->Update(apptime - deltaTime, apptime);
			deltaTime = apptime;
		}
		
	}

	//fps++;

	//if (currentTime - deltaTime >= 1000) 
	//{
	//	//EntityManager::GetEntityManagerInstance()->Update(currentTime - deltaTime);
	//	deltaTime = currentTime;
	//	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Black, FString::Printf(TEXT("FPS: %d"), fps));
	//	fps = 0;
	//}

}



