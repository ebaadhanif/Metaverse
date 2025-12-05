#pragma once

#include <DIS7/msLibMacro.h>

#include <DISUtils/MulticastSocket.h>
#include <DISUtils/DISTime.h>
#include <DISUtils/RemoteEntitiesManager.h>
#include <DISUtils/DISDefinitions.h>
#include <DISUtils/DISConfigurationsHandler.h>
#include <DISUtils/PDUProcessorsInclusions.h>
#include <DISUtils/ApplicationNameFileHandler.h>
#include <DISUtils/SiteNameFileHandler.h>
#include <DISUtils/DISApplicationSettingsFileHandler.h>
#include <DISUtils/PDUManager.h>

#include <GeographicLib/geocentric.hpp>

#include <mutex>

namespace DIS
{
	using InitializationCallback = std::function<void(bool)>;

	struct MulticastMessage
	{
		char message[MAX_RECEIVE_BUFFER_SIZE];
		int messageSize;

		MulticastMessage(char* buffer, int length) {
			memcpy(message, buffer, length);
			messageSize = length;
		}
	};
	class EXPORT_MACRO CDISHandler
	{
	private:
		static CDISHandler* _instance;

		GeographicLib::Geocentric _geoLib;

		Endian _appEndian{};
		Endian _machineEndian{};

		float _appTime{};
		CDISTime _disTime{};

		CMulticastSocket _multicastSocket{};

		bool _isInitialized{ false };
		static InitializationCallback _initializationCb;

		static std::mutex _receivedMessagesMutex;
		static std::list<MulticastMessage> _listReceivedMessages;

		ApplicationPlayPauseState _bApplicationPlayPauseState{ PLAYED };

		CDISHandler();
		~CDISHandler();

		void ProcessMulticastMessages();
		static void ProcessIncomingMessages(char* buffer, int length);

	public:

		static CDISHandler* GetInstance();

		void Initialize(DIS::ENUMS::AFISE::ApplicationID appType, Endian appEndian, InitializationCallback  cb, std::string dialogExePath = "");
		void Initialize(DIS::ENUMS::AFISE::ApplicationID appType, Endian appEndian, void(*cb)(bool), char* dialogExePath);

		bool IsInitialized() const;

		GeographicLib::Geocentric GetGeoLib();

		Endian GetAppEndian();
		Endian GetMachineEndian();

		float GetAppTime();
		CDISTime* GetDISTimePtr();

		void InitializeMulticastSocket();

		CMulticastSocket* GetMulticastSocketPtr();

		bool GetIsApplicationPaused();
		ApplicationPlayPauseState GetApplicationPlayPauseState();
		void SetApplicationPlayPauseState(ApplicationPlayPauseState flag);

		void Update(float deltaTime, float totalAppTime);

		bool Release();
	};
}



