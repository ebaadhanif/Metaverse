#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base class
#include <DIS7/ResupplyReceivedPdu.h>  // for typedef
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{
	using ResupplyReceivedCallback = std::function<void(const ResupplyReceivedMessage&)>;

	class EXPORT_MACRO CResupplyReceivedPduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static ResupplyReceivedCallback _cbFunction;

		void TriggerCallback(const ResupplyReceivedPdu& ResupplyReceivedPdu);

	public:
		CResupplyReceivedPduProcessor();
		~CResupplyReceivedPduProcessor();

		void AddCallback(ResupplyReceivedCallback cb);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetResupplyReceivedMessage(ResupplyReceivedMessage msg);

		static unsigned char PreparePduStatus(LVCIndicator LVCData = LVCIndicator::VIRTUAL, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED);
	};
}