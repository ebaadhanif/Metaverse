#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base class
#include <DIS7/IFFPdu.h>        // for typedef
#include <DISEnums/IFFAltitudeIndicator.h>
#include <DISEnums/IFFChangeIndicator.h>
#include <DISEnums/IFFHeartbeatIndicator.h>
#include <DISEnums/IFFSystemSpecificField1.h>
#include <DISEnums/IFFSystemSpecificField2.h>
#include <DISEnums/IFFTransponderInterogatorIndicator.h>
#include <DISEnums/IFFSimulationMode.h>
#include <DISEnums/IFFInteractiveCapable.h>
#include <DISEnums/IFFTestMode.h>
#include <DISEnums/IFFSystemStatus.h>
#include <DISEnums/IFFParameterCapable.h>
#include <DISEnums/IFFOperationalStatus.h>
#include <DISEnums/IFFMilitaryEmergency.h>
#include <DISEnums/IFFPositionIdentification.h>
#include <DISEnums/IFFUnmannedAircraft.h>
#include <DISEnums/IFFDamageStatus.h>
#include <DISEnums/IFFMalfunctionStatus.h>
#include <DISEnums/IFFModeStatus.h>
#include <DISEnums/IFFLayerIndicator.h>
#include <DISEnums/ActiveInterogationIndicator.h>
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/DetonationTypeIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISEnums/TransferredEntityIndicator.h>
#include <DISUtils/DISDefinitions.h>
#include <DISUtils/IFFSystem.h>

namespace DIS
{
	using IFFCallback = std::function<void(const CIFFSystem&)>;

	class EXPORT_MACRO CIFFPduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static IFFCallback _cbFunction;

		void TriggerCallback(const CIFFSystem& iffSystemData);

	public:
		CIFFPduProcessor();
		~CIFFPduProcessor();

		void AddCallback(IFFCallback cb);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetIFFMessage(CIFFSystem iffSystemData);

		static unsigned char PreparePduStatus(TransferredEntityIndicator TEI = TransferredEntityIndicator::NO_DIFFERENCE, LVCIndicator LVC = LVCIndicator::NO_STATEMENT,
			CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED, IFFSimulationMode ISM = IFFSimulationMode::REGENERATION, 
			ACTIVEInterogationIndicator AII = ACTIVEInterogationIndicator::NOT_ACTIVE);

		//******* Preparation of PDU Record Fields for PDU header of IFF PDU Start ********//

		//For Sending Side
		static unsigned char PrepareChangeRecord(IFFChangeIndicator CI, IFFHeartbeatIndicator HI, 
			IFFSystemSpecificField1 SSF1 = IFFSystemSpecificField1::NOT_PRESENT,
			IFFSystemSpecificField2 SSF2 = IFFSystemSpecificField2::PRESENT /* Mode C Capability Present */,
			IFFTransponderInterogatorIndicator TII = IFFTransponderInterogatorIndicator::TRANSPONDER,
			IFFSimulationMode ISM = IFFSimulationMode::REGENERATION, 
			IFFInteractiveCapable IIC = IFFInteractiveCapable::NOT_CAPABLE, 
			IFFTestMode TM = IFFTestMode::OFF);

		static unsigned char PrepareSystemStatusRecord(IFFSystemStatus ISS, 
			IFFParameterCapable PARAM1 = IFFParameterCapable::CAPABLE,
			IFFParameterCapable PARAM2 = IFFParameterCapable::CAPABLE, 
			IFFParameterCapable PARAM3 = IFFParameterCapable::CAPABLE,
			IFFParameterCapable PARAM4 = IFFParameterCapable::NOT_CAPABLE,
			IFFParameterCapable PARAM5 = IFFParameterCapable::CAPABLE /* For ModeC */,
			IFFParameterCapable PARAM6 = IFFParameterCapable::NOT_CAPABLE,
			IFFOperationalStatus IOS = IFFOperationalStatus::OPERATIONAL);

		static unsigned char PrepareModifierRecord(IFFMilitaryEmergency IME,
			IFFPositionIdentification IPI = IFFPositionIdentification::OFF,
			IFFUnmannedAircraft IUA = IFFUnmannedAircraft::OFF);

		static unsigned short PrepareModeCAltitudeRecord(unsigned int modecAltitude,
			IFFModeStatus mode,
			IFFAltitudeIndicator AI = IFFAltitudeIndicator::POSITIVE_ABOVE_MSL,
			IFFDamageStatus IDS = IFFDamageStatus::NO_DAMAGE,
			IFFMalfunctionStatus IMS = IFFMalfunctionStatus::NO_MALFUNCTION);

		static unsigned short PrepareModeCodeRecord(int code, int split,
			IFFModeStatus mode, 
			IFFDamageStatus IDS = IFFDamageStatus::NO_DAMAGE,
			IFFMalfunctionStatus IMS = IFFMalfunctionStatus::NO_MALFUNCTION);

		static unsigned char PrepareInformationLayers(IFFLayerIndicator layer1 = IFFLayerIndicator::PRESENT,
			IFFLayerIndicator layer2 = IFFLayerIndicator::NOT_PRESENT,
			IFFLayerIndicator layer3 = IFFLayerIndicator::NOT_PRESENT,
			IFFLayerIndicator layer4 = IFFLayerIndicator::NOT_PRESENT,
			IFFLayerIndicator layer5 = IFFLayerIndicator::NOT_PRESENT,
			IFFLayerIndicator layer6 = IFFLayerIndicator::NOT_PRESENT,
			IFFLayerIndicator layer7 = IFFLayerIndicator::NOT_PRESENT);

		static unsigned char PreparePadding(short mode6A, short mode6B);

		// For Recieving Side
		static void GetCharlieHeight(unsigned short parameter, unsigned int& height);
		static int DecimalToOctal(long int decimal);
		static bool  GetModeStateAndValue(int parameterCode, int& octal);

		//******* Preparation of PDU Record Fields for PDU header of IFF PDU End ********//
	};
}
