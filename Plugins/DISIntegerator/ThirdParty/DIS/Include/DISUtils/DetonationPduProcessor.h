#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base class
#include <DIS7/DetonationPdu.h> // for typedef
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISEnums/DetonationTypeIndicator.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{
	using DetonationCallback = std::function<void(const DetonationMessage&)>;

	class EXPORT_MACRO CDetonationPduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static DetonationCallback _cbFunction;

		void TriggerCallback(const DetonationPdu& pdu);

	public:
		CDetonationPduProcessor();
		~CDetonationPduProcessor();

		void AddCallback(DetonationCallback cb);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetDetonationMessage(DetonationMessage msg);

		static unsigned char PreparePduStatus(LVCIndicator LVC = LVCIndicator::NO_STATEMENT, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED, DetonationTypeIndicator DTI = DetonationTypeIndicator::MUNITION);

		static void ExtractPDUStatus(unsigned char pduStatus, LVCIndicator& LVC, CoupledExtensionIndicator& CEI, DetonationTypeIndicator& DTI);
	};
}


