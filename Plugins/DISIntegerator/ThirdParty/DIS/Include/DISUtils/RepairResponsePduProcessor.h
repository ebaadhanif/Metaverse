#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base class
#include <DIS7/RepairResponsePdu.h>  // for typedef
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{
	using RepairResponseCallback = std::function<void(const RepairResponseMessage&)>;

	class EXPORT_MACRO CRepairResponsePduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static RepairResponseCallback _cbFunction;

		void TriggerCallback(const RepairResponsePdu& RepairResponsePdu);

	public:
		CRepairResponsePduProcessor();
		~CRepairResponsePduProcessor();

		void AddCallback(RepairResponseCallback cb);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetRepairResponseMessage(RepairResponseMessage msg);

		static unsigned char PreparePduStatus(LVCIndicator LVCData = LVCIndicator::VIRTUAL, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED);
	};
}