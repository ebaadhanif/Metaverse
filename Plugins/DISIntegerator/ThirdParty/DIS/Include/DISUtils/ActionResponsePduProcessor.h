#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base 
#include <DIS7/ActionResponsePdu.h>  // for typedef
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{
	using ActionResponseCallback = std::function<void(const ActionResponseMessage&)>;

	class EXPORT_MACRO CActionResponsePduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static ActionResponseCallback _cbFunction;

		void TriggerCallback(const ActionResponsePdu& pdu);

	public:
		CActionResponsePduProcessor();
		~CActionResponsePduProcessor();

		void AddCallback(ActionResponseCallback cb);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetActionResponseMessage(ActionResponseMessage msg);

		static unsigned char PreparePduStatus(LVCIndicator LVCData = LVCIndicator::VIRTUAL, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED);
	};
}
