#pragma once

#include <DISUtils/DISDefinitions.h>
#include <fstream>
#include <DIS7\msLibMacro.h>

namespace DIS
{
	class EXPORT_MACRO CApplicationNameFileHandler
	{
	private:
		static CApplicationNameFileHandler* _pInstance;

		std::ifstream					_file;
		std::vector<ApplicationNameData> _vecApplicationNames;

		CApplicationNameFileHandler();
		~CApplicationNameFileHandler();

	public:
		static CApplicationNameFileHandler* GetInstance();

		void LoadDataFromFile();
		bool OpenApplicationNameFile();

		std::string GetApplicationShortName(unsigned short AppType);
	};
}
