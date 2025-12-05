#pragma once

#include <DISUtils/DISDefinitions.h>
#include <fstream>
#include <DIS7\msLibMacro.h>

namespace DIS
{
	class EXPORT_MACRO CHostnamesFileHandler
	{
	private:
		static CHostnamesFileHandler*		_pInstance;

		std::ifstream						_file;
		std::vector<HostnamesData>			_vecHostnames;

		CHostnamesFileHandler();
		~CHostnamesFileHandler();

	public:
		static CHostnamesFileHandler* GetInstance();

		void LoadDataFromFile();
		bool OpenHostnamesFile();

		std::string GetHostname(std::string ip);
	};
}
