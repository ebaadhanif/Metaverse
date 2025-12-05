#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base 
#include <DIS7/ActionRequestPdu.h>  // for typedef
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{
	using ActionRequestCallback = std::function<void(const ActionRequestMessage&)>;

	class EXPORT_MACRO CActionRequestPduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static ActionRequestCallback _cbFunction;

		void TriggerCallback(const ActionRequestPdu& pdu);

	public:
		CActionRequestPduProcessor();
		~CActionRequestPduProcessor();

		void AddCallback(ActionRequestCallback cb);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetActionRequestMessage(ActionRequestMessage msg);

		static unsigned char PreparePduStatus(LVCIndicator LVCData = LVCIndicator::VIRTUAL, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED);
	};
}
