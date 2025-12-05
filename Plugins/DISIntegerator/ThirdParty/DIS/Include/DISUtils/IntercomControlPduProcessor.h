#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base 
#include <DIS7/IntercomControlPdu.h>        // for typedef
#include <DISUtils/DISDefinitions.h>
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISEnums/TransferredEntityIndicator.h>
#include <DISEnums/PDUStatus.h>
#include <DISEnums/IntercomAttachedIndicator.h>
namespace DIS
{
	using IntercomControlCallback = std::function<void(const IntercomControlMessage&)>;

	class EXPORT_MACRO CIntercomControlPduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;
		static IntercomControlCallback _cbFunction;

		void TriggerCallback(const IntercomControlPdu & pdu);

	public:
		CIntercomControlPduProcessor();
		~CIntercomControlPduProcessor();

		static void AddCallback(IntercomControlCallback cb);
		static void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const DIS::Pdu& packet);

		static unsigned char PreparePduStatus(
			TransferredEntityIndicator TEI = TransferredEntityIndicator::NO_DIFFERENCE, 
			LVCIndicator LVC = LVCIndicator::NO_STATEMENT, 
			CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED,
			IntercomAttachedIndicator IAI = IntercomAttachedIndicator::ATTACHED);

		void SetIntercomControlMessage(IntercomControlMessage msg);
	};
}

