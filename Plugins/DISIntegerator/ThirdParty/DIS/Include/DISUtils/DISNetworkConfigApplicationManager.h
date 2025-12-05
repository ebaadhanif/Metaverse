#pragma once
#include <stdlib.h>
#include <functional>
#include <DIS7\msLibMacro.h>

namespace DIS
{
	class EXPORT_MACRO CDISNetworkConfigApplicationManager
	{
	private:
		static  CDISNetworkConfigApplicationManager* _instance;

		CDISNetworkConfigApplicationManager();
		~CDISNetworkConfigApplicationManager();

	public:
		static CDISNetworkConfigApplicationManager* GetInstance();

		static void DISNetworkConfigAppStartUp();
	};
}

