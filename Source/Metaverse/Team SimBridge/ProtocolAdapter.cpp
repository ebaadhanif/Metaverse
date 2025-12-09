// Fill out your copyright notice in the Description page of Project Settings.


#include "ProtocolAdapter.h"

ProtocolAdapter::ProtocolAdapter()
{
	EntityManager::GetEntityManagerInstance()->SetProtocolAdapterPtr(this);
}

ProtocolAdapter::~ProtocolAdapter()
{
}
