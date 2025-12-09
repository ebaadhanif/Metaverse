// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProtocolAdapter.h"
#include "DISAdapter.h"
#include "CIGIAdapter.h"
#include "HLAAdapter.h"
#include "AppConstEnumStruct.h"

/**
 * 
 */

//Singleton class
class METAVERSE_API ProtocolFactory
{
private:
	static ProtocolFactory* m_pProtocolFactoryInstance;
	ProtocolFactory();

public:
	static ProtocolFactory* GetProtocolFactoryInstance();
	ProtocolAdapter* GetProtocolAdapterObj(EProtocolAdapterType protocolType);
	~ProtocolFactory();
};
