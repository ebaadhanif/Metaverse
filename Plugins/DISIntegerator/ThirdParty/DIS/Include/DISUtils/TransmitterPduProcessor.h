#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base 
#include <DIS7/TransmitterPdu.h>        // for typedef
#include <DISUtils/DISDefinitions.h>
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISEnums/TransferredEntityIndicator.h>
#include <DISEnums/RadioAttachedIndicator.h>

namespace DIS
{
	using TransmitterCallback = std::function<void(const TransmitterMessage&)>;

	class EXPORT_MACRO CTransmitterPduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;
		static TransmitterCallback _cbFunction;

		void TriggerCallback(const TransmitterPdu & pdu);

	public:
		CTransmitterPduProcessor();
		~CTransmitterPduProcessor();

		static void AddCallback(TransmitterCallback cb);
		static void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		static unsigned char PreparePduStatus(TransferredEntityIndicator TEI = TransferredEntityIndicator::NO_DIFFERENCE, LVCIndicator LVC = LVCIndicator::NO_STATEMENT, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED, RadioAttachedIndicator RAI = RadioAttachedIndicator::ATTACHED);

		void SetTransmitterMessage(TransmitterMessage msg);
	};
}

