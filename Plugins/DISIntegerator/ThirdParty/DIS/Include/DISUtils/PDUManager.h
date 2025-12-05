#pragma once

#include <DISUtils/IncomingMessage.h>
#include <DISUtils/ActionRequestPduProcessor.h>
#include <DISUtils/ActionResponsePduProcessor.h>
#include <DISUtils/AttributePduProcessor.h>
#include <DISUtils/CreateEntityPduProcessor.h>
#include <DISUtils/StartResumePduProcessor.h>
#include <DISUtils/StopFreezePduProcessor.h>
#include <DISUtils/CommentPduProcessor.h>
#include <DISUtils/AcknowledgePduProcessor.h>
#include <DISUtils/CollisionPduProcessor.h>
#include <DISUtils/EntityStatePduProcessor.h>
#include <DISUtils/ElectromagneticEmissionPduProcessor.h>
#include <DISUtils/IFFPduProcessor.h>
#include <DISUtils/EntityStateUpdatePduProcessor.h>
#include <DISUtils/RemoveEntityPduProcessor.h>
#include <DISUtils/FirePduProcessor.h>
#include <DISUtils/EntityDamageStatusPduProcessor.h>
#include <DISUtils/DetonationPduProcessor.h>
#include <DISUtils/DataPduProcessor.h>
#include <DISUtils/DataQueryPduProcessor.h>
#include <DISUtils/EventReportPduProcessor.h>
#include <DISUtils/SignalPduProcessor.h>
#include <DISUtils/IntercomSignalPduProcessor.h>
#include <DISUtils/IntercomControlPduProcessor.h>
#include <DISUtils/SetDataPduProcessor.h>
#include <DISUtils\ServiceRequestPduProcessor.h>
#include <DISUtils\ResupplyOfferPduProcessor.h>
#include <DISUtils\ResupplyReceivedPduProcessor.h>
#include <DISUtils\ResupplyCancelPduProcessor.h>
#include <DISUtils\RepairCompletePduProcessor.h>
#include <DISUtils\RepairResponsePduProcessor.h>
#include <DISUtils\SeesPduProcessor.h>

#include <DISUtils/TransmitterPduProcessor.h>
#include <DISUtils/ReceiverPduProcessor.h>

namespace DIS 
{
	class EXPORT_MACRO PDUManager
	{
	private:
		static PDUManager* _instance;

		IncomingMessage _incomingMessageProcessor;

		CEntityStatePduProcessor _esPduProcessor;
		CCollisionPduProcessor _collisionPduProcessor;
		CEntityStateUpdatePduProcessor _esUpdatePduProcessor;
		CAttributePduProcessor _attributePduProcessor;

		CFirePduProcessor _firePduProcessor;
		CEntityDamageStatusPduProcessor _entityDamageStatusPduProcessor;
		CDetonationPduProcessor _detonationPduProcessor;

		CCreateEntityPduProcessor _createEntityPduProcessor;
		CRemoveEntityProcessor _removeEntityPduProcessor;
		CStartResumePduProcessor _startResumePduProcessor;
		CStopFreezePduProcessor _stopFreezePduProcessor;
		CCommentProcessor _commentPduProcessor;

		CAcknowledgePduProcessor _acknowledgePduProcessor;
		CActionRequestPduProcessor _actionRequestPduProcessor;
		CActionResponsePduProcessor _actionResponsePduProcessor;
		CDataQueryPduProcessor _dataQueryPduProcessor;
		CSetDataPduProcessor _setDataPduProcessor;
		CDataPduProcessor _dataPduProcessor;
		CEventReportPduProcessor _eventReportPduProcessor;

		CElectromagneticEmissionPduProcessor _eePduProcessor;
		CSeesPduProcessor _seesPduProcessor;
		CIFFPduProcessor _iffPduProcessor;

		CSignalPduProcessor _signalPduProcessor;
		CTransmitterPduProcessor _transmitterPduProcessor;
		CReceiverPduProcessor _receiverPduProcessor;
		CIntercomSignalPduProcessor _intercomSignalPduProcessor;
		CIntercomControlPduProcessor _intercomControlPduProcessor;
	
		CServiceRequestPduProcessor _serviceRequestPduProcessor;
		CResupplyOfferPduProcessor _resupplyOfferPduProcessor;
		CResupplyReceivedPduProcessor _resupplyReceivedPduProcessor;
		CResupplyCancelPduProcessor _resupplyCancelPduProcessor;
		CRepairCompletePduProcessor _repairCompletePduProcessor;
		CRepairResponsePduProcessor _repairResponsePduProcessor;

		

		
	
		PDUManager();
		~PDUManager();

		void AddMessageProcessors();
		void RemoveMessageProcessors();

		friend class CDISHandler;

	public:
		static PDUManager* GetInstance();

		//................................................................CreateEntity..........
		void AddCreateEntityCallback(CreateEntityCallback cb);
		void AddCreateEntityCallback(void(*cb)(const CreateEntityMessage&));
		//.................................................................added............
		void AddAcknowledgeCallback(AcknowledgeCallback cb);
		void AddAcknowledgeCallback(void(*cb)(const AcknowledgeMessage&));
		void AddActionRequestCallback(ActionRequestCallback cb);
		void AddActionRequestCallback(void(*cb)(const ActionRequestMessage&));
		void AddActionResponseCallback(ActionResponseCallback cb);
		void AddActionResponseCallback(void(*cb)(const ActionResponseMessage&));
		void AddAttributeCallback(AttributeCallback cb);
		void AddAttributeCallback(void(*cb)(const AttributeMessage&));
		void AddCollisionCallback(CollisionCallback cb);
		void AddCollisionCallback(void(*cb)(const CollisionMessage&));
		void AddDataCallback(DataCallback cb);
		void AddDataCallback(void(*cb)(const DataMessage&));
		void AddDataQueryCallback(DataQueryCallback cb);
		void AddDataQueryCallback(void(*cb)(const DataQueryMessage&));
		void AddDetonationCallback(DetonationCallback cb);
		void AddDetonationCallback(void(*cb)(const DetonationMessage&));
		void AddEECallback(ElectromagneticEmissionsCallback cb);
		void AddEECallback(void(*cb)(const ElectromagneticEmissionsMessage&));
		void AddSeesCallback(SeesCallback cb);
		void AddSeesCallback(void(*cb)(const SeesMessage&));
		void AddEntityStateCallback(EntityStateCallback cb);
		void AddEntityStateCallback(void(*cb)(const EntityStateMessage&));
		void AddEntityStateUpdateCallback(EntityStateUpdateCallback cb);
		void AddEntityStateUpdateCallback(void(*cb)(const EntityStateUpdateMessage&));
		void AddEventReportCallback(EventReportCallback cb);
		void AddEventReportCallback(void(*cb)(const EventReportMessage&));
		void AddFireCallback(FireCallback cb);
		void AddFireCallback(void(*cb)(const FireMessage&));
		//................................................................EntityDamageStatus..........
		void AddEntityDamageStatusCallback(EntityDamageStatusCallback cb);
		void AddEntityDamageStatusCallback(void(*cb)(const EntityDamageStatusMessage&));
		//.................................................................added............
		void AddIFFCallback(IFFCallback cb);
		void AddIFFCallback(void(*cb)(const CIFFSystem&));
		void AddRemoveEntityCallback(RemoveEntityCallback cb);
		void AddRemoveEntityCallback(void(*cb)(const RemoveEntityMessage&));
		void AddSetDataCallback(SetDataCallback cb);
		void AddSetDataCallback(void(*cb)(const SetDataMessage&));
		void AddSignalCallback(SignalCallback cb);
		void AddSignalCallback(void(*cb)(const SignalMessage&));
		void AddTransmitterCallback(TransmitterCallback cb);
		void AddTransmitterCallback(void(*cb)(const TransmitterMessage &));
		void AddReceiverCallback(ReceiverCallback cb);
		void AddReceiverCallback(void(*cb)(const ReceiverMessage &));
		//................................................................IntercomSignal..........
		void AddIntercomSignalCallback(IntercomSignalCallback cb);
		void AddIntercomSignalCallback(void(*cb)(const IntercomSignalMessage&));
		//.................................................................added............

		//................................................................IntercomControl..........
		void AddIntercomControlCallback(IntercomControlCallback cb);
		void AddIntercomControlCallback(void(*cb)(const IntercomControlMessage&));
		//.................................................................added............
		void AddStartResumeCallback(StartResumeCallback cb);
		void AddStartResumeCallback(void(*cb)(const StartResumeMessage&));
		void AddStopFreezeCallback(StopFreezeCallback cb);
		void AddStopFreezeCallback(void(*cb)(const StopFreezeMessage&));
		void AddServiceRequestCallback(ServiceRequestCallback cb);
		void AddServiceRequestCallback(void(*cb)(const ServiceRequestMessage&));
		void AddResupplyOfferCallback(ResupplyOfferCallback cb);
		void AddResupplyOfferCallback(void(*cb)(const ResupplyOfferMessage&));
		void AddResupplyReceivedCallback(ResupplyReceivedCallback cb);
		void AddResupplyReceivedCallback(void(*cb)(const ResupplyReceivedMessage&));
		void AddResupplyCancelCallback(ResupplyCancelCallback cb);
		void AddResupplyCancelCallback(void(*cb)(const ResupplyCancelMessage&));
		void AddRepairCompleteCallback(RepairCompleteCallback cb);
		void AddRepairCompleteCallback(void(*cb)(const RepairCompleteMessage&));
		void AddRepairResponseCallback(RepairResponseCallback cb);
		void AddRepairResponseCallback(void(*cb)(const RepairResponseMessage&));
		void AddCommentCallback(CommentCallback cb);
		void AddCommentCallback(void(*cb)(const CommentMessage&));

		//......................................RemovalcreateEntity.........
		void RemoveCreateEntityCallback();
		//.......................................added...........
		void RemoveAcknowledgeCallback();
		void RemoveActionRequestCallback();
		void RemoveActionResponseCallback();
		void RemoveAttributeCallback();
		void RemoveCollisionCallback();
		void RemoveDataCallback();
		void RemoveDataQueryCallback();
		void RemoveDetonationCallback();
		void RemoveEECallback();
		void RemoveSeesCallback();
		void RemoveEntityStateCallback();
		void RemoveEntityStateUpdateCallback();
		void RemoveEventReportCallback();
		void RemoveFireCallback();
		//......................................EntityDamageStatus.........
		void RemoveEntityDamageStatusCallback();
		//.......................................added...........
		void RemoveRemoveEntityCallback();
		void RemoveSetDataCallback();
		void RemoveSignalCallback();
		void RemoveTransmitterCallback();
		void RemoveReceiverCallback();
		//......................................intercomSignal.........
		void RemoveIntercomSignalCallback();
		//.......................................added...........

		//......................................intercomControl.........
		void RemoveIntercomControlCallback();
		//.......................................added...........
		void RemoveStartResumeCallback();
		void RemoveStopFreezeCallback();
		void RemoveServiceRequestCallback();
		void RemoveResupplyOfferCallback();
		void RemoveResupplyReceivedCallback();
		void RemoveResupplyCancelCallback();
		void RemoveRepairCompleteCallback();
		void RemoveRepairResponseCallback();
		void RemoveCommentCallback();

		//..........................................CreateEntity...........
		void SetCreateEntityMsg(CreateEntityMessage msg);
		//..........................................added..............
		void SetAcknowledgeMsg(AcknowledgeMessage msg);
		void SetActionRequestMsg(ActionRequestMessage msg);
		void SetActionResponseMsg(ActionResponseMessage msg);
		void SetAttributeMsg(AttributeMessage msg);
		void SetCollisionMsg(CollisionMessage msg);
		void SetDataMsg(DataMessage msg);
		void SetDataQueryMsg(DataQueryMessage msg);
		void SetDetonationMsg(DetonationMessage msg);
		void SetEEMsg(ElectromagneticEmissionsMessage msg);
		void SetSeesMsg(SeesMessage msg);
		void SetEntityStateMsg(EntityStateMessage msg);
		void SetEntityStateUpdateMessage(EntityStateUpdateMessage msg);
		void SetEventReportMsg(EventReportMessage msg);
		void SetFireMsg(FireMessage msg);
		//..........................................EntityDamageStatus...........
		void SetEntityDamageStatusMsg(EntityDamageStatusMessage msg);
		//..........................................added..............
		void SetIFFMsg(CIFFSystem msg);
		void SetRemoveEntityMsg(RemoveEntityMessage msg);
		void SetSetDataMsg(SetDataMessage msg);
		void SetSignalMsg(SignalMessage msg);
		void SetTransmitterMsg(TransmitterMessage msg);
		void SetReceiverMsg(ReceiverMessage msg);
		//..........................................intercomSignal...........
		void SetIntercomSignalMsg(IntercomSignalMessage msg);
		//..........................................added..............

		//..........................................intercomControl...........
		void SetIntercomControlMsg(IntercomControlMessage msg);
		//..........................................added..............
		void SetStartResumeMsg(StartResumeMessage msg);
		void SetStopFreezeMsg(StopFreezeMessage msg);
		void SetServiceRequestMsg(ServiceRequestMessage msg);
		void SetResupplyOfferMsg(ResupplyOfferMessage msg);
		void SetResupplyReceivedMsg(ResupplyReceivedMessage msg);
		void SetResupplyCancelMsg(ResupplyCancelMessage msg);
		void SetRepairCompleteMsg(RepairCompleteMessage msg);
		void SetRepairResponseMsg(RepairResponseMessage msg);
		void SetCommentMsg(CommentMessage msg);
	};
}

