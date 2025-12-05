#pragma once
#include<stdlib.h>
#include<string>
#include <DIS7/EventIdentifier.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <fstream>
#include <DIS7\msLibMacro.h>
#include <DISEnums\AFISE\ApplicationID.h>
#include <string>

namespace DIS
{
	class EXPORT_MACRO CDISConfigurationsHandler
	{
	private:
		static std::string						_currDir;

		unsigned int                            _requestID{ 0 };
		//SIMNET Group
		std::string								_connectionMode{};
		std::string								_connectionType{};
		std::string								_SIMNETGroupName{};
		std::string								_multicastAddress{};
		int										_multicastPort;
		int										_multicastTtl;

		//Exercise Group
		unsigned char							_exerciseGroupId{ 0 };
		std::string								_exerciseGroupName{};

		//Network Interface Card Info
		std::string								_interfaceAddress{};
		std::string								_subnetMask{};
		std::string								_macAddress{};

		// Site Info
		unsigned short							_siteId{ 0 };
		std::string         					_siteName{};
		std::string								_siteShortName{};

		//Application
		unsigned short							_usApplicationID{ 1 }; // Default - Other
		unsigned short							_applicationType{ 1 }; // Default - Other
		std::string								_appShortName{};
		std::string								_applicationName{};

		//Entity ID
		unsigned short							_usCurrentID{ 1 };

		//Event ID
		unsigned short							_eventNumber{ 0 };

		int										_isAbsoulteTimestamp{ 0 };
		int										_loopBack{ 0 };

		SimulationAddress					    _simulationAddress{};

		static  CDISConfigurationsHandler* _instance;
		/// <summary>
		/// 
		/// </summary>
		CDISConfigurationsHandler();
		~CDISConfigurationsHandler();

	public:
		static CDISConfigurationsHandler* GetInstance();

		void ReadUserNetworkConfigurationsFromFile();

		std::string GetCurrentAppDirectory() { return _currDir; }

		std::string GetConnectionModeName() { return _connectionMode; }
		std::string GetConnectionTypeName() { return _connectionType; }
		std::string GetSIMNETGroupName() { return _SIMNETGroupName; }
		std::string GetMulticastAddress() { return _multicastAddress; }
		int GetMulticastPort() { return _multicastPort; }
		int GetMulticastTtl() { return _multicastTtl; }

		unsigned char GetExerciseGroupId() { return _exerciseGroupId; }
		std::string GetExerciseGroupName() { return _exerciseGroupName; }
		std::string GetInterfaceAddress() { return _interfaceAddress; }
		std::string GetSubnetMask() { return _subnetMask; }
		std::string GetMacAddress() { return _macAddress; }

		unsigned short GetSiteID() { return _siteId; }
		std::string GetSiteName() { return _siteName; }
		std::string GetSiteShortName() { return _siteShortName; }

		unsigned short GetApplicationId() { return _usApplicationID; }
		unsigned short GetApplicationType() { return _applicationType; }
		std::string GetAppShortName() { return _appShortName; }
		std::string GetAppName() { return _applicationName; }

		unsigned short GetCurrentID() { return _usCurrentID; }
		unsigned short GetNewID() { return _usCurrentID++; }

		unsigned short GetCurrentRequestID() { return _requestID; }
		unsigned short GetNewRequestID() { return _requestID++; }

		EventIdentifier GetNewEventID();

		int GetLoopBack() { return _loopBack; }

		void SetApplicationId(unsigned short appId);
		void SetApplicationType(DIS::ENUMS::AFISE::ApplicationID appType);
		static void SetFilePath(std::string dialogExePath);
	}; 
}

