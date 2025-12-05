#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base class
#include <DIS7/SetDataPdu.h>  // for typedef
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{
	#ifndef SET_DATA_PDU_REQUEST_IDS_DEFINITION
	#define SET_DATA_PDU_REQUEST_IDS_DEFINITION

		enum SET_DATA_PDU_REQUEST_IDS
		{
			OTHER_SET_DATA = 0,
			COLLISION_CONTROLL_SET_DATA = 1
		};
	#endif

		using SetDataCallback = std::function<void(const SetDataMessage&)>;

	class EXPORT_MACRO CSetDataPduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static SetDataCallback _cbFunction;

		void TriggerCallback(const SetDataPdu& pdu);

	public:
		CSetDataPduProcessor();
		~CSetDataPduProcessor();

		void AddCallback(SetDataCallback cb);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetSetDataMessage(SetDataMessage setDataMsg);

		static unsigned char PreparePduStatus(LVCIndicator LVC = LVCIndicator::NO_STATEMENT, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED);
	};
}

