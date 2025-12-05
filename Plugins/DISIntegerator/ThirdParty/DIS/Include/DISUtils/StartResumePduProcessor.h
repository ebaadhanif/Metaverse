#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base class
#include <DIS7/StartResumePdu.h>  // for typedef
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISEnums/TransferredEntityIndicator.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{
	using StartResumeCallback = std::function<void(const StartResumeMessage&)>;

	class EXPORT_MACRO CStartResumePduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static StartResumeCallback _cbFunction;

		void TriggerCallback(const StartResumePdu& pdu);

	public:
		CStartResumePduProcessor();
		~CStartResumePduProcessor();

		void AddCallback(StartResumeCallback cb);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetStartResumeMessage(StartResumeMessage msg);

		static unsigned char PreparePduStatus(LVCIndicator LVCData = LVCIndicator::VIRTUAL, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED);
	};
}