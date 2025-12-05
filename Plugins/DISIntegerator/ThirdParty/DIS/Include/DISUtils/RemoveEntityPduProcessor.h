#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base 
#include <DIS7/RemoveEntityPdu.h>        // for typedef
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{
	using RemoveEntityCallback = std::function<void(const RemoveEntityMessage&)>;

	class EXPORT_MACRO CRemoveEntityProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static RemoveEntityCallback _cbFunction;

		void TriggerCallback(const RemoveEntityPdu& pdu);

	public:
		CRemoveEntityProcessor();
		~CRemoveEntityProcessor();

		void AddCallback(RemoveEntityCallback cb);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetRemoveEnityMessage(RemoveEntityMessage msg);

		static unsigned char PreparePduStatus(LVCIndicator LVC = LVCIndicator::NO_STATEMENT, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED);
	};
}
