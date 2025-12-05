#pragma once

#include <DISUtils/DISDefinitions.h>
#include <fstream>

namespace DIS
{
	class EXPORT_MACRO CSiteNameFileHandler
	{
	private:
		static CSiteNameFileHandler*	_pInstance;

		std::ifstream					_file;
		std::vector<SiteNameData>		_vecSiteNames;

		CSiteNameFileHandler();
		~CSiteNameFileHandler();

	public:
		static CSiteNameFileHandler* GetInstance();

		void LoadDataFromFile();
		bool OpenSiteNameFile();

		std::string GetSiteShortName(unsigned short AppType);
	};
}
