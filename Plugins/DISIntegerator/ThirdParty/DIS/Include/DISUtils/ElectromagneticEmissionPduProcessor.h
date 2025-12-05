#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base class
#include <DIS7/ElectromagneticEmissionsPdu.h> // for typedef
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISEnums/TransferredEntityIndicator.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{
	using ElectromagneticEmissionsCallback = std::function<void(const ElectromagneticEmissionsMessage&)>;

	class EXPORT_MACRO CElectromagneticEmissionPduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static ElectromagneticEmissionsCallback _cbFunction;

		void TriggerCallback(const ElectromagneticEmissionsPdu& pdu);

	public:
		CElectromagneticEmissionPduProcessor();
		~CElectromagneticEmissionPduProcessor();

		void AddCallback(ElectromagneticEmissionsCallback cb);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetElectromagneticEmissionMessage(ElectromagneticEmissionsMessage msg);

		static unsigned char PreparePduStatus(LVCIndicator LVCData = LVCIndicator::VIRTUAL, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED, TransferredEntityIndicator TEI = TransferredEntityIndicator::NO_DIFFERENCE);

		static unsigned char PrepareBeamStatus(short beamState);
		static short ExtractBeamState(unsigned char beamStatus);
	};
}
