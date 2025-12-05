#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base class
#include <DIS7/EntityStateUpdatePdu.h>  // for typedef
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISEnums/TransferredEntityIndicator.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{
	using EntityStateUpdateCallback = std::function<void(const EntityStateUpdateMessage&)>;

	class EXPORT_MACRO CEntityStateUpdatePduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static EntityStateUpdateCallback _cbFunction;

		void TriggerCallback(const EntityStateUpdatePdu& pdu);

	public:
		CEntityStateUpdatePduProcessor();
		~CEntityStateUpdatePduProcessor();

		void AddCallback(EntityStateUpdateCallback cb);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetEntityStateUpdateMessage(EntityStateUpdateMessage acknowledgeMsg);

		static unsigned char PreparePduStatus(LVCIndicator LVCData = LVCIndicator::VIRTUAL, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED, TransferredEntityIndicator TEI = TransferredEntityIndicator::NO_DIFFERENCE);
	};
}

