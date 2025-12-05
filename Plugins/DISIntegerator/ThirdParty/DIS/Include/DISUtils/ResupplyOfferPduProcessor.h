#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base class
#include <DIS7/ResupplyOfferPdu.h>  // for typedef
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{
	using ResupplyOfferCallback = std::function<void(const ResupplyOfferMessage&)>;

	class EXPORT_MACRO CResupplyOfferPduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static ResupplyOfferCallback _cbFunction;

		void TriggerCallback(const ResupplyOfferPdu& ResupplyOfferPdu);

	public:
		CResupplyOfferPduProcessor();
		~CResupplyOfferPduProcessor();

		void AddCallback(ResupplyOfferCallback cb);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetResupplyOfferMessage(ResupplyOfferMessage msg);

		static unsigned char PreparePduStatus(LVCIndicator LVCData = LVCIndicator::VIRTUAL, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED);
	};
}