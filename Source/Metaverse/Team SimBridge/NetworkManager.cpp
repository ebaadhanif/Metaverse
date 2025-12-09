// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkManager.h"
#include "RemoteEntityFactory.h"
#include "EntityManager.h"

// Sets default values
ANetworkManager::ANetworkManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_pProtocolAdapter = nullptr;
	m_pWorld = nullptr;
	networkThread = nullptr;
	m_adapterType = EProtocolAdapterType::DIS;
}

// Called when the game starts or when spawned
void ANetworkManager::BeginPlay()
{
	Super::BeginPlay();
	m_pProtocolAdapter = ProtocolFactory::GetProtocolFactoryInstance()->GetProtocolAdapterObj(m_adapterType);
	//m_pProtocolAdapter->InitializeAdapter();
	networkThread = MetaverseThread::StartThread();
	networkThread->InitializeAdapter(m_pProtocolAdapter);
}

void ANetworkManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (networkThread) {
		networkThread->Stop();
		delete networkThread;
		networkThread = nullptr;
	}
	m_pProtocolAdapter->CloseNetwork();
	delete m_pProtocolAdapter;
	m_pProtocolAdapter = nullptr;
	EntityManager::GetEntityManagerInstance()->~EntityManager();
}


// Called every frame
void ANetworkManager::Tick(float DeltaTime)
{
	if (!m_pWorld)
	{
		if (GetWorld()) {
			m_pWorld = GetWorld();
			RemoteEntityFactory::GetRemoteEntityFactoryInstance()->SetWorld(m_pWorld);
			PrimaryActorTick.bCanEverTick = false;

		}
	}
	Super::Tick(DeltaTime);
}

ProtocolAdapter* ANetworkManager::GetProtocolAdapterPtr()
{
	return m_pProtocolAdapter;
}

