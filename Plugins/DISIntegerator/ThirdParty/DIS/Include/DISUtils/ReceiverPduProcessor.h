#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base 
#include <DIS7/ReceiverPdu.h>        // for typedef
#include <DISUtils/DISDefinitions.h>
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISEnums/TransferredEntityIndicator.h>
#include <DISEnums/RadioAttachedIndicator.h>

namespace DIS
{
	using ReceiverCallback = std::function<void(const ReceiverMessage&)>;

	class EXPORT_MACRO CReceiverPduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;
		static ReceiverCallback _cbFunction;

		void TriggerCallback(const ReceiverPdu & pdu);

	public:
		CReceiverPduProcessor();
		~CReceiverPduProcessor();

		static void AddCallback(ReceiverCallback cb);
		static void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const DIS::Pdu& packet);

		static unsigned char PreparePduStatus(TransferredEntityIndicator TEI = TransferredEntityIndicator::NO_DIFFERENCE, LVCIndicator LVC = LVCIndicator::NO_STATEMENT, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED, RadioAttachedIndicator RAI = RadioAttachedIndicator::ATTACHED);

		void SetReceiverMessage(ReceiverMessage msg);
	};
}

