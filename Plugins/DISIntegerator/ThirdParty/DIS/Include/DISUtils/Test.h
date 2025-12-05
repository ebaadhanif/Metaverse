#pragma once
#include <DISUtils/IPacketProcessor.h>  // for base class
#include <DIS7/EntityStatePdu.h>        // for typedef
#include <DISUtils/PDUType.h>
#include <DISUtils/RemoteEntitiesManager.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{
	class EXPORT_MACRO CTest
	{
	private:
		static CTest* m_instance;
		DIS::EntityStatePdu					m_entityParams{};

		CTest();
		~CTest();

	public:

		static CTest* GetInstance();
		EntityID	GetEntityID();

		int Sum(int& a, int& b) { return a + b; }
	};
}

