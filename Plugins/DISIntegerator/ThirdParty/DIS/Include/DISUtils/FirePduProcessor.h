#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base class
#include <DIS7/FirePdu.h> // for typedef
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISEnums/FireTypeIndicator.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{
	using FireCallback = std::function<void(const FireMessage&)>;

	class EXPORT_MACRO CFirePduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static FireCallback _cbFunction;

		void TriggerCallback(const FirePdu& firePdu);

	public:
		CFirePduProcessor();
		~CFirePduProcessor();

		void AddCallback(FireCallback cb);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetFireMessage(FireMessage msg);

		static unsigned char PreparePduStatus(LVCIndicator LVC = LVCIndicator::NO_STATEMENT, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED, FireTypeIndicator FTI = FireTypeIndicator::MUNITION);
	};
}

