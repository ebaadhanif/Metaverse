#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base class
#include <DIS7/EventReportPdu.h>  // for typedef
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISEnums/TransferredEntityIndicator.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{
	using EventReportCallback = std::function<void(const EventReportMessage&)>;

	class EXPORT_MACRO CEventReportPduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static EventReportCallback _cbFunction;

		void TriggerCallback(const EventReportPdu& pdu);

	public:
		CEventReportPduProcessor();
		~CEventReportPduProcessor();

		void AddCallback(EventReportCallback cb);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetEventReportMessage(EventReportMessage msg);

		static unsigned char PreparePduStatus(LVCIndicator LVCData = LVCIndicator::VIRTUAL, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED, TransferredEntityIndicator TEI = TransferredEntityIndicator::NO_DIFFERENCE);
	};
}