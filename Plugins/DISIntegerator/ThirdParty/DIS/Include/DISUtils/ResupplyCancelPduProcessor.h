#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base class
#include <DIS7/ResupplyCancelPdu.h>  // for typedef
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{
	using ResupplyCancelCallback = std::function<void(const ResupplyCancelMessage&)>;

	class EXPORT_MACRO CResupplyCancelPduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static ResupplyCancelCallback _cbFunction;

		void TriggerCallback(const ResupplyCancelPdu& ResupplyCancelPdu);

	public:
		CResupplyCancelPduProcessor();
		~CResupplyCancelPduProcessor();

		void AddCallback(ResupplyCancelCallback cb);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetResupplyCancelMessage(ResupplyCancelMessage msg);

		static unsigned char PreparePduStatus(LVCIndicator LVCData = LVCIndicator::VIRTUAL, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED);
	};
}