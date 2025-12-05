#pragma once
#include <DISUtils/DISDefinitions.h>

#include <DIS7/EntityID.h>
#include <DIS7/IFFPdu.h>
#include <DIS7/SystemIdentifier.h>
#include <DIS7\msLibMacro.h>
#include <DISEnums\IFFSystemPower.h>
#include <DISEnums\IFFChangeOptionsType.h>

namespace DIS
{
	class EXPORT_MACRO CIFFSystem
	{
	private:
		DIS::ENUMS::IFFSystemPower _systemPower{DIS::ENUMS::IFFSystemPower::PWR_OFF };
		float _lastPduSentTime;
		DIS::ENUMS::IFFChangeOptionsType _lastUpdate{ DIS::ENUMS::IFFChangeOptionsType::NO };
		SystemIdentifier _systemID;
		unsigned int _lastRecTimeStamp;
		unsigned int _charlieHeight; // For Altitude of Mode C
		bool _isAlternateCharlieHeight;

	public:

		IFFModesData					_paramIFF;				//Sent for Owner and received for Remote

		CIFFSystem(void);
		~CIFFSystem(void);

		IFFModesData	GetIFFParameters();

		void SetIFFSystemPower(DIS::ENUMS::IFFSystemPower power);
		DIS::ENUMS::IFFSystemPower GetPower();

		const bool GetIFFState();
		bool GetIFFSystemStatus();
		unsigned int GetCharlieHeight();

		void SetLastPduUpdateTime(float fTime);
		DIS::ENUMS::IFFChangeOptionsType IsUpdateRequired(float time, IFFModesData* pIFF);
		void PrepareIFFPdu(EntityID emittingEntityID, unsigned int timeStamp, DataStream& dStream, unsigned char changeOption, unsigned int altitude);
		void HandleIFFPdu(const IFFPdu& iffPdu, unsigned int platformAltitudeMSL);
	};
}

