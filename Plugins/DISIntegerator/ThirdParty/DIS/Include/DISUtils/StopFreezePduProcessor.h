#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base class
#include <DIS7/StopFreezePdu.h>  // for typedef
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISEnums/TransferredEntityIndicator.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{
	using StopFreezeCallback = std::function<void(const StopFreezeMessage&)>;

	class EXPORT_MACRO CStopFreezePduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static StopFreezeCallback _cbFunction;

		void TriggerCallback(const StopFreezePdu& stopFreezePdu);

	public:
		CStopFreezePduProcessor();
		~CStopFreezePduProcessor();

		void AddCallback(StopFreezeCallback cb);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetStopFreezeMessage(StopFreezeMessage msg);

		static unsigned char PreparePduStatus(LVCIndicator LVCData = LVCIndicator::VIRTUAL, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED);
	};
}