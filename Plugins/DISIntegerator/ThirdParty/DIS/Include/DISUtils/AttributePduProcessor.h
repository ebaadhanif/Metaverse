#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base class
#include <DIS7/AttributePdu.h>  // for typedef  
#include <DISEnums/LVCIndicator.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{
	using AttributeCallback = std::function<void(const AttributeMessage&)>;

	class EXPORT_MACRO CAttributePduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static AttributeCallback _cbFunction;

		void TriggerCallback(const AttributePdu& pdu);

	public:
		CAttributePduProcessor();
		~CAttributePduProcessor();

		void AddCallback(AttributeCallback cb);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetAttributeMessage(AttributeMessage msg);

		static unsigned char PreparePduStatus(LVCIndicator LVCData = LVCIndicator::VIRTUAL);
	};
}

