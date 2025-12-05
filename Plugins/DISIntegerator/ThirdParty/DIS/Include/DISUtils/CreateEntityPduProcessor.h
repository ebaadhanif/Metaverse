#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base 
#include <DIS7/CreateEntityPdu.h>        // for typedef
#include <DISUtils/DISDefinitions.h>
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISEnums/PDUStatus.h>
namespace DIS
{
	using CreateEntityCallback = std::function<void(const CreateEntityMessage&)>;

	class EXPORT_MACRO CCreateEntityPduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;
		static CreateEntityCallback _cbFunction;

		void TriggerCallback(const CreateEntityPdu & pdu);

	public:
		CCreateEntityPduProcessor();
		~CCreateEntityPduProcessor();

		static void AddCallback(CreateEntityCallback cb);
		static void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const DIS::Pdu& packet);

		static unsigned char PreparePduStatus(
			LVCIndicator LVC = LVCIndicator::NO_STATEMENT, 
			CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED);

		void SetCreateEntityMessage(CreateEntityMessage msg);
	};
}

