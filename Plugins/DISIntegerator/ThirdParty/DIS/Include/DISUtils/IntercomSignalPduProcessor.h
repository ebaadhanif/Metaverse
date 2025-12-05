#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base 
#include <DIS7/IntercomSignalPdu.h>        // for typedef
#include <DISUtils/DISDefinitions.h>
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISEnums/TransferredEntityIndicator.h>
#include <DISEnums/RadioAttachedIndicator.h>
#include <DISEnums/IntercomAttachedIndicator.h>
#include <DISUtils/IntercomSignalMessage.h>

namespace DIS
{
	using IntercomSignalCallback = std::function<void(const IntercomSignalMessage&)>;

	class EXPORT_MACRO CIntercomSignalPduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;
		static IntercomSignalCallback _cbFunction;

		void TriggerCallback(const IntercomSignalPdu & pdu);

	public:
		CIntercomSignalPduProcessor();
		~CIntercomSignalPduProcessor();

		static void AddCallback(IntercomSignalCallback cb);
		static void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const DIS::Pdu& packet);

		static unsigned char PreparePduStatus(TransferredEntityIndicator TEI = TransferredEntityIndicator::NO_DIFFERENCE, LVCIndicator LVC = LVCIndicator::NO_STATEMENT, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED, IntercomAttachedIndicator IAI = IntercomAttachedIndicator::ATTACHED);

		void SetIntercomSignalMessage(IntercomSignalMessage msg);
	};
}

