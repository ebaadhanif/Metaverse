#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base class
#include <DIS7/EntityDamageStatusPdu.h> // for typedef
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{
	using EntityDamageStatusCallback = std::function<void(const EntityDamageStatusMessage&)>;

	class EXPORT_MACRO CEntityDamageStatusPduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static EntityDamageStatusCallback _cbFunction;

		void TriggerCallback(const EntityDamageStatusPdu& entityDamageStatusPdu);

	public:
		CEntityDamageStatusPduProcessor();
		~CEntityDamageStatusPduProcessor();

		void AddCallback(EntityDamageStatusCallback cb);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetEntityDamageStatusMessage(EntityDamageStatusMessage msg);

		static unsigned char PreparePduStatus(LVCIndicator LVC = LVCIndicator::NO_STATEMENT, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED);
	};
}

