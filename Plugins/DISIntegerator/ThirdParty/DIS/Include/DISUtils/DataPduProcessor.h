#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base class
#include <DIS7/DataPdu.h>  // for typedef
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{
	using DataCallback = std::function<void(const DataMessage&)>;
	struct logisticServices
	{
	};
	class EXPORT_MACRO CDataPduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static DataCallback _cbFunction;

		void TriggerCallback(const DataPdu& pdu);

	public:
		CDataPduProcessor();
		~CDataPduProcessor();

		void AddCallback(DataCallback cb);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetDataMessage(DataMessage msg);

		static unsigned char PreparePduStatus(LVCIndicator LVCData = LVCIndicator::VIRTUAL, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED);
	};
}
