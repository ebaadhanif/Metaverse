#pragma once
#include "DISDefinitions.h"
#include <DIS7\msLibMacro.h>

namespace DIS
{
	class EXPORT_MACRO CDISApplicationSettingsFileHandler
	{
	private:
		unsigned short									_landDetonationRadius{ 0 };
		int												_expandableFiringEntityDetectionRadiusInMeters{ 0 };
		int												_maxReceivedBuffer{ 0 };
		bool											_autoGroundClamp{ false };
		bool											_lagCompensation{ true };
		bool											_disabledArticulatedParts{ false };

		std::vector<EntityTimeoutSettingsData>			_vecEntityTimeoutSettings;
		std::vector<EntityDeadReckoningSettingsData>	_vecDRSettings;

		static  CDISApplicationSettingsFileHandler* _instance;
		CDISApplicationSettingsFileHandler();

	public:
		~CDISApplicationSettingsFileHandler();
		static CDISApplicationSettingsFileHandler* GetInstance();

		int GetLandDetonationRadius() { return _landDetonationRadius; }
		int GetFiringEntityDetectionRadiusInMeters() { return _expandableFiringEntityDetectionRadiusInMeters; }

		int GetMaxReceivedBuffer() { return _maxReceivedBuffer == 0 || _maxReceivedBuffer > MAX_RECEIVE_BUFFER_SIZE ? MAX_RECEIVE_BUFFER_SIZE : _maxReceivedBuffer; }
		bool GetAutoGroundClamp() { return _autoGroundClamp; }
		bool GetLagCompensation() { return _lagCompensation; }
		bool GetDisabledArticulatedParts() { return _disabledArticulatedParts; }
		bool GetDRFPSByEntityType(EntityType entityType, int& drFPS);
		int GetEntityTimeoutByEntityType(EntityType entityType);

		std::vector<EntityTimeoutSettingsData> GetEntityTimeoutSettingsVector() { return _vecEntityTimeoutSettings; };
		std::vector<EntityDeadReckoningSettingsData> GetDRSettingsVector() { return _vecDRSettings; };

		void ReadDISApplicationSettingsFromXmlFile();
		void WriteDISApplicationSettingsToXmlFile();

		std::vector<EntityTimeoutSettingsData> GetTimeoutSettingsVector();
		std::vector<EntityDeadReckoningSettingsData> GetDeadReckoningSettingsVector();
	};
}
