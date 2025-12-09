// Fill out your copyright notice in the Description page of Project Settings.


#include "ProtocolFactory.h"

ProtocolFactory::ProtocolFactory()
{
}

ProtocolFactory* ProtocolFactory::m_pProtocolFactoryInstance = nullptr;
ProtocolFactory* ProtocolFactory::GetProtocolFactoryInstance()
{
    if (m_pProtocolFactoryInstance == nullptr)
    {
        m_pProtocolFactoryInstance = new ProtocolFactory();
    }
    return m_pProtocolFactoryInstance;
}

ProtocolAdapter* ProtocolFactory::GetProtocolAdapterObj(EProtocolAdapterType protocolType)
{
    ProtocolAdapter* pTempProtocolType = nullptr;
    switch (protocolType)
    {
    case EProtocolAdapterType::DIS:
    {
        pTempProtocolType = new DISAdapter();
        break;
    }
    case EProtocolAdapterType::CIGI:
    {
        pTempProtocolType = new CIGIAdapter();
        break;
    }
    case EProtocolAdapterType::HLA:
    {
        pTempProtocolType = new HLAAdapter();
        break;
    }
    default:
        pTempProtocolType = new DISAdapter();
        break;
    }

    return pTempProtocolType;
}

ProtocolFactory::~ProtocolFactory()
{
}
