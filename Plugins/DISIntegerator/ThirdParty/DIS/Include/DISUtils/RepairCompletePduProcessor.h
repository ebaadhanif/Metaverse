#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base class
#include <DIS7/RepairCompletePdu.h>  // for typedef
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{
	using RepairCompleteCallback = std::function<void(const RepairCompleteMessage&)>;

	class EXPORT_MACRO CRepairCompletePduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static RepairCompleteCallback _cbFunction;

		void TriggerCallback(const RepairCompletePdu& RepairCompletePdu);

	public:
		CRepairCompletePduProcessor();
		~CRepairCompletePduProcessor();

		void AddCallback(RepairCompleteCallback cb);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetRepairCompleteMessage(RepairCompleteMessage msg);

		static unsigned char PreparePduStatus(LVCIndicator LVCData = LVCIndicator::VIRTUAL, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED);
	};
}