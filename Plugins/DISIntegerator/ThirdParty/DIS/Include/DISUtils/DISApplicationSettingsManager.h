#pragma once
#include <DIS7\msLibMacro.h>

namespace DIS
{
	class EXPORT_MACRO CDISApplicationSettingsManager
	{
	private:
		static  CDISApplicationSettingsManager* _instance;

		CDISApplicationSettingsManager();
		~CDISApplicationSettingsManager();

	public:
		static CDISApplicationSettingsManager* GetInstance();

		void DISApplicationSettingsDialogStartUp();
	};
}

