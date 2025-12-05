#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base 
#include <DIS7/SignalPdu.h>        // for typedef
#include <DISUtils/DISDefinitions.h>
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISEnums/TransferredEntityIndicator.h>
#include <DISEnums/RadioAttachedIndicator.h>

namespace DIS
{
	using SignalCallback = std::function<void(const SignalMessage&)>;

	class EXPORT_MACRO CSignalPduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;
		static SignalCallback _cbFunction;

		void TriggerCallback(const SignalPdu & pdu);

	public:
		CSignalPduProcessor();
		~CSignalPduProcessor();

		static void AddCallback(SignalCallback cb);
		static void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const DIS::Pdu& packet);

		static unsigned char PreparePduStatus(TransferredEntityIndicator TEI = TransferredEntityIndicator::NO_DIFFERENCE, LVCIndicator LVC = LVCIndicator::NO_STATEMENT, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED, RadioAttachedIndicator RAI = RadioAttachedIndicator::ATTACHED);

		void SetSignalMessage(SignalMessage msg);
	};
}

