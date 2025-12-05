#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base class
#include <DIS7/DataQueryPdu.h>  // for typedef
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{
	using DataQueryCallback = std::function<void(const DataQueryMessage&)>;

	class EXPORT_MACRO CDataQueryPduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static DataQueryCallback _cbFunction;

		void TriggerCallback(const DataQueryPdu& pdu);

	public:
		CDataQueryPduProcessor();
		~CDataQueryPduProcessor();

		void AddCallback(DataQueryCallback callbackFunction);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetDataQueryMessage(DataQueryMessage msg);

		static unsigned char PreparePduStatus(LVCIndicator LVCData = LVCIndicator::VIRTUAL, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED);
	};
}
