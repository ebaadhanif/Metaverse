#pragma once

#include <DISUtils/IPacketProcessor.h>  // for base 
#include <DIS7/CommentPdu.h>        // for typedef
#include <DISEnums/CoupledExtensionIndicator.h>
#include <DISEnums/LVCIndicator.h>
#include <DISUtils/DISDefinitions.h>

namespace DIS
{
	using CommentCallback = std::function<void(const CommentMessage&)>;

	class EXPORT_MACRO CCommentProcessor : public IPacketProcessor
	{
	private:
		PDUType _pduType;

		static CommentCallback _cbFunction;

		void TriggerCallback(const CommentPdu& pdu);

	public:
		CCommentProcessor();
		~CCommentProcessor();

		void AddCallback(CommentCallback cb);
		void RemoveCallback();

		PDUType GetRegisteredType() const;

		void Process(const Pdu& packet);

		void SetCommentMessage(CommentMessage msg);

		static unsigned char PreparePduStatus(LVCIndicator LVC = LVCIndicator::NO_STATEMENT, CoupledExtensionIndicator CEI = CoupledExtensionIndicator::NOT_COUPLED);
	};
}
