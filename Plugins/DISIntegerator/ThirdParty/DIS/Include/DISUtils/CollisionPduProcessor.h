#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base 
#include <DIS7/CollisionPdu.h>   // for typedef      
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{
	using CollisionCallback = std::function<void(const CollisionMessage&)>;

	class EXPORT_MACRO CCollisionPduProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static CollisionCallback _cbFunction;

		void TriggerCallback(const CollisionPdu& pdu);

	public:
		CCollisionPduProcessor();
		~CCollisionPduProcessor();

		void AddCallback(CollisionCallback cb);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetCollisionMessage(CollisionMessage msg);

		static unsigned char PreparePduStatus(LVCIndicator LVC = LVCIndicator::NO_STATEMENT, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED);
	};
}

