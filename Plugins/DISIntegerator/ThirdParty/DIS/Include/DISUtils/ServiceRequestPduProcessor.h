#pragma once
#include <DISUtils/IPacketProcessor.h>  // for base class
#include <DIS7/ServiceRequestPdu.h>  // for typedef
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{
	using ServiceRequestCallback = std::function<void(const ServiceRequestMessage&)>;

	class EXPORT_MACRO CServiceRequestPduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static ServiceRequestCallback _cbFunction;

		void TriggerCallback(const ServiceRequestPdu& ServiceRequestPdu);

	public:
		CServiceRequestPduProcessor();
		~CServiceRequestPduProcessor();

		void AddCallback(ServiceRequestCallback cb);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetServiceRequestMessage(ServiceRequestMessage msg);

		static unsigned char PreparePduStatus(LVCIndicator LVCData = LVCIndicator::VIRTUAL, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED);
	};
}