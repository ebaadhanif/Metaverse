#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base 
#include <DIS7/AcknowledgePdu.h>   // for typedef
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{	
	using AcknowledgeCallback = std::function<void(const AcknowledgeMessage&)>;

	class EXPORT_MACRO CAcknowledgePduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static AcknowledgeCallback _cbFunction;

		void TriggerCallback(const AcknowledgePdu& pdu);

	public:
		CAcknowledgePduProcessor();
		~CAcknowledgePduProcessor();

		void AddCallback(AcknowledgeCallback cb);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetAcknowledgeMessage(AcknowledgeMessage msg);

		static unsigned char PreparePduStatus(LVCIndicator LVCData = LVCIndicator::VIRTUAL, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED);
	};
}

