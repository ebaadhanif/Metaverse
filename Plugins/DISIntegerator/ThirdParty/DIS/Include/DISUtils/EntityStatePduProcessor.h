#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base class
#include <DIS7/EntityStatePdu.h>        // for typedef
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISEnums/TransferredEntityIndicator.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{
	using EntityStateCallback = std::function<void(const EntityStateMessage&)>;

	class EXPORT_MACRO CEntityStatePduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static EntityStateCallback _cbFunction;

		void TriggerCallback(const EntityStatePdu& pdu);

	public:
		CEntityStatePduProcessor();
		~CEntityStatePduProcessor();

		void AddCallback(EntityStateCallback cb);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetEntityStateMessage(EntityStateMessage msg);

		static unsigned char PreparePduStatus(LVCIndicator LVCData = LVCIndicator::VIRTUAL, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED, TransferredEntityIndicator TEI = TransferredEntityIndicator::NO_DIFFERENCE);
	};
}
