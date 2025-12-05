#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base class
#include <DIS7/SeesPdu.h>  // for typedef
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{
	using SeesCallback = std::function<void(const SeesMessage&)>;

	class EXPORT_MACRO CSeesPduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static SeesCallback _cbFunction;

		void TriggerCallback(const SeesPdu& SeesPdu);

	public:
		CSeesPduProcessor();
		~CSeesPduProcessor();

		void AddCallback(SeesCallback cb);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetSeesMessage(SeesMessage msg);

		static unsigned char PreparePduStatus(LVCIndicator LVCData = LVCIndicator::VIRTUAL, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED);
	};
}