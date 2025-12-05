#include <DIS6/PDUBank.h>
#include <DIS7/EntityStatePdu.h>
#include <DIS7/FirePdu.h>
#include <DIS7/DetonationPdu.h>
#include <DIS7/CollisionPdu.h>
//PDU_SERVICE_REQUEST
//#include <DIS7/ResupplyOfferPdu.h>
//#include <DIS7/ResupplyReceivedPdu.h>
//#include <DIS7/ResupplyCancelPdu.h>
//#include <DIS7/RepairCompletePdu.h>
//#include <DIS7/RepairResponsePdu.h>
//#include <DIS7/CreateEntityPdu.h>
#include <DIS7/RemoveEntityPdu.h>
#include <DIS7/StartResumePdu.h>
#include <DIS7/StopFreezePdu.h>
#include <DIS7/AcknowledgePdu.h>
#include <DIS7/ActionRequestPdu.h>
#include <DIS7/ActionResponsePdu.h>
#include <DIS7/DataQueryPdu.h>
#include <DIS7/SetDataPdu.h>
#include <DIS7/DataPdu.h>
#include <DIS7/EventReportPdu.h>
//#include <DIS7/CommentPdu.h>
#include <DIS7/ElectromagneticEmissionsPdu.h>
//#include <DIS7/DesignatorPdu.h>
#include <DIS7/TransmitterPdu.h>
#include <DIS7/SignalPdu.h>
#include <DIS7/ReceiverPdu.h>
#include <DIS7/IFFPdu.h>
//PDU_UNDERWATER_ACOUSTIC
//PDU_SUPPLEMENTAL_EMISSION_ENTITY_STATE
//#include <DIS7/IntercomSignalPdu.h>
//#include <DIS7/IntercomControlPdu.h>
//#include <DIS7/AggregateStatePdu.h>
//#include <DIS7/IsGroupOfPdu.h>
//PDU_TRANSFER_OWNERSHIP #include <DIS/TransferControlRequestPdu.h>
//#include <DIS7/IsPartOfPdu.h>
//#include <DIS7/MinefieldStatePdu.h>
//#include <DIS7/MinefieldQueryPdu.h>
//#include <DIS7/MinefieldDataPdu.h>
//#include <DIS7/MinefieldResponseNackPdu.h>
//#include <DIS7/EnvironmentalProcessPdu.h>
//#include <DIS7/GriddedDataPdu.h>
//#include <DIS7/PointObjectStatePdu.h>
//#include <DIS7/LinearObjectStatePdu.h>
//#include <DIS7/ArealObjectStatePdu.h>
//PDU_TSPI
//PDU_APPEARANCE
//PDU_ARTICULATED_PARTS
//PDU_LE_FIRE
//PDU_LE_DETONATION
//#include <DIS7/CreateEntityReliablePdu.h>
//#include <DIS7/RemoveEntityReliablePdu.h>
//#include <DIS7/StartResumeReliablePdu.h>
//#include <DIS7/StopFreezeReliablePdu.h>
//#include <DIS7/AcknowledgeReliablePdu.h>
//#include <DIS7/ActionRequestReliablePdu.h>
//#include <DIS7/ActionResponseReliablePdu.h>
//#include <DIS7/DataQueryReliablePdu.h>
#include <DIS7/SetDataReliablePdu.h>
//#include <DIS7/DataReliablePdu.h>
//#include <DIS7/EventReportReliablePdu.h>
//#include <DIS7/CommentReliablePdu.h>
//PDU_RECORD_R
//#include <DIS7/SetRecordReliablePdu.h>
//#include <DIS7/RecordQueryReliablePdu.h>
//#include <DIS7/CollisionElasticPdu.h>
#include <DIS7/EntityStateUpdatePdu.h>
//#include <DIS7/DirectedEnergyFirePdu.h>
#include <DIS7/EntityDamageStatusPdu.h>
//PDU_INFORMATION_OPERATIONS_ACTION
//PDU_INFORMATION_OPERATIONS_REPORT
#include <DIS7/AttributePdu.h>


using namespace DIS;

Pdu* PduBank::GetStaticPDU( DIS::PDUType pdu_type )
{
	static Pdu								defaultPdu;
	static EntityStatePdu					entityStatePdu;
	static FirePdu							firePdu;
	static DetonationPdu					detonationPdu;
	static CollisionPdu						collisionPdu;
	//PDU_SERVICE_REQUEST
	//static ResupplyOfferPdu					resupplyOfferPdu;
	//static ResupplyReceivedPdu				resupplyReceivedPdu;
	//static ResupplyCancelPdu				resupplyCancelPdu;
	//static RepairCompletePdu				repairCompletePdu;
	//static RepairResponsePdu				repairResponsePdu;
	//static CreateEntityPdu					createEntityPdu;
	static RemoveEntityPdu					removeEntityPdu;
	static StartResumePdu					startResumePdu;
	static StopFreezePdu					stopFreezePdu;
	static AcknowledgePdu					acknowledgePdu;
	static ActionRequestPdu					actionRequestPdu;
	static ActionResponsePdu				actionResponsePdu;
	static DataQueryPdu						dataQueryPdu;
	static SetDataPdu						setDataPdu;
	static DataPdu							dataPdu;
	static EventReportPdu					eventReportPdu;
	//static CommentPdu						commentPdu;
	static ElectromagneticEmissionsPdu		electronicEmissionPdu;
	//static DesignatorPdu					designatorPdu;
	static TransmitterPdu					transmitterPdu;
	static SignalPdu						signalPdu;
	static ReceiverPdu						receiverPdu;
	static IFFPdu							iffAtcNavAidsLayer1Pdu;
	//PDU_UNDERWATER_ACOUSTIC
	//PDU_SUPPLEMENTAL_EMISSION_ENTITY_STATE
	//static IntercomSignalPdu				intercomSignalPdu;
	//static IntercomControlPdu				intercomControlPdu;
	//static AggregateStatePdu				aggregateStatePdu;
	//static IsGroupOfPdu						isGroupOfPdu;
	//PDU_TRANSFER_OWNERSHIP #include <DIS/TransferControlRequestPdu.h>
	//static IsPartOfPdu						isPartOfPdu;
	//static MinefieldStatePdu				minefieldStatePdu;
	//static MinefieldQueryPdu				minefieldQueryPdu;
	//static MinefieldDataPdu					minefieldDataPdu;
	//static MinefieldResponseNackPdu			minefieldResponseNackPdu;
	//static EnvironmentalProcessPdu			environmentalProcessPdu;
	//static GriddedDataPdu					griddedDataPdu;
	//static PointObjectStatePdu				pointObjectStatePdu;
	//static LinearObjectStatePdu				linearObjectStatePdu;
	//static ArealObjectStatePdu				arealObjectStatePdu;
	//PDU_TSPI
	//PDU_APPEARANCE
	//PDU_ARTICULATED_PARTS
	//PDU_LE_FIRE
	//PDU_LE_DETONATION
	//static CreateEntityReliablePdu			createEntityReliablePdu;
	//static RemoveEntityReliablePdu			removeEntityReliablePdu;
	//static StartResumeReliablePdu			startResumeReliablePdu;
	//static StopFreezeReliablePdu			stopFreezeReliablePdu;
	//static AcknowledgeReliablePdu			acknowledgeReliablePdu;
	//static ActionRequestReliablePdu			actionRequestReliablePdu;
	//static ActionResponseReliablePdu		actionResponseReliablePdu;
	//static DataQueryReliablePdu				dataQueryReliablePdu;
	static SetDataReliablePdu				setDataReliablePdu;
	//static DataReliablePdu					dataReliablePdu;
	//static EventReportReliablePdu			eventReportReliablePdu;
	//static CommentReliablePdu				commentReliablePdu;
	//PDU_RECORD_R
	//static SetRecordReliablePdu				setRecordReliablePdu;
	//static RecordQueryReliablePdu			recordQueryReliablePdu;
	//static CollisionElasticPdu				collisionElasticPdu;
	static EntityStateUpdatePdu				entityStateUpdatePdu;
	//static DirectedEnergyFirePdu			directedEnergyFirePdu;
	static EntityDamageStatusPdu			entityDamageStatusPdu;
	//PDU_INFORMATION_OPERATIONS_ACTION
	//PDU_INFORMATION_OPERATIONS_REPORT
	static AttributePdu						attributePdu;
  
	switch(pdu_type)
	{
		case PDU_OTHER:								return &defaultPdu;					break;
		case PDU_ENTITY_STATE:						return &entityStatePdu;				break;
		case PDU_FIRE:								return &firePdu;					break; 
		case PDU_DETONATION:						return &detonationPdu;				break; 
		case PDU_COLLISION:							return &collisionPdu;				break; 
		//PDU_SERVICE_REQUEST
		//case PDU_RESUPPLY_OFFER:					return &resupplyOfferPdu;			break; 
		//case PDU_RESUPPLY_RECEIVED:					return &resupplyReceivedPdu;		break; 
		//case PDU_RESUPPLY_CANCEL:					return &resupplyCancelPdu;			break; 
		//case PDU_REPAIR_COMPLETE:					return &repairCompletePdu;			break;
		//case PDU_REPAIR_RESPONSE:					return &repairResponsePdu;			break;
		//case PDU_CREATE_ENTITY:						return &createEntityPdu;			break; 
		case PDU_REMOVE_ENTITY:						return &removeEntityPdu;			break; 
		case PDU_START_RESUME:						return &startResumePdu;				break; 
		case PDU_STOP_FREEZE:						return &stopFreezePdu;				break;
		//case PDU_ACKNOWLEDGE:						return &acknowledgePdu;				break;
		case PDU_ACTION_REQUEST:					return &actionRequestPdu;			break; 
		case PDU_ACTION_RESPONSE:					return &actionResponsePdu;			break; 
		case PDU_DATA_QUERY:						return &dataQueryPdu;				break; 
		case PDU_SET_DATA:							return &setDataPdu;					break; 
		case PDU_DATA:								return &dataPdu;					break; 
		case PDU_EVENT_REPORT:						return &eventReportPdu;				break; 
		//case PDU_COMMENT:							return &commentPdu;					break; 
		case PDU_ELECTROMAGNETIC_EMISSION:			return &electronicEmissionPdu;		break;
		//case PDU_TRANSMITTER:						return &transmitterPdu;				break;
		case PDU_SIGNAL:							return &signalPdu;					break;
		//case PDU_RECEIVER:							return &receiverPdu;				break;
		case PDU_IFF:								return &iffAtcNavAidsLayer1Pdu;     break;
		//PDU_UNDERWATER_ACOUSTIC
		//PDU_SUPPLEMENTAL_EMISSION_ENTITY_STATE
		//case PDU_INTERCOM_SIGNAL:					return &intercomSignalPdu;			break;
		//case PDU_INTERCOM_CONTROL:					return &intercomControlPdu;			break;
		//case PDU_AGGREGATE_STATE:					return &aggregateStatePdu;			break;
		//case PDU_ISGROUPOF:							return &isGroupOfPdu;				break;
		//PDU_TRANSFER_OWNERSHIP #include <DIS/TransferControlRequestPdu.h>
		//case PDU_ISPARTOF:							return &isPartOfPdu;				break;
		//case PDU_MINEFIELD_STATE:					return &minefieldStatePdu;			break;
		//case PDU_MINEFIELD_QUERY:					return &minefieldQueryPdu;			break;
		//case PDU_MINEFIELD_DATA:					return &minefieldDataPdu;			break;
		//case PDU_MINEFIELD_RESPONSE_NACK:			return &minefieldResponseNackPdu;	break;
		//case PDU_ENVIRONMENTAL_PROCESS:				return &environmentalProcessPdu;	break;
		//case PDU_GRIDDED_DATA:						return &griddedDataPdu;				break;
		//case PDU_POINT_OBJECT_STATE:				return &pointObjectStatePdu;		break;
		//case PDU_LINEAR_OBJECT_STATE:				return &linearObjectStatePdu;		break;
		//case PDU_AREAL_OBJECT_STATE:				return &arealObjectStatePdu;		break;
		//PDU_TSPI
		//PDU_APPEARANCE
		//PDU_ARTICULATED_PARTS
		//PDU_LE_FIRE
		//PDU_LE_DETONATION
		//case PDU_CREATE_ENTITY_R:					return &createEntityReliablePdu;	break;
		//case PDU_REMOVE_ENTITY_R:					return &removeEntityReliablePdu;	break;
		//case PDU_START_RESUME_R:					return &startResumeReliablePdu;		break;
		//case PDU_STOP_FREEZE_R:						return &stopFreezeReliablePdu;		break;
		//case PDU_ACKNOWLEDGE_R:						return &acknowledgeReliablePdu;		break;
		//case PDU_ACTION_REQUEST_R:					return &actionRequestReliablePdu;	break;
		//case PDU_ACTION_RESPONSE_R:					return &actionResponseReliablePdu;	break;
		//case PDU_DATA_QUERY_R:						return &dataQueryReliablePdu;		break;
		//case PDU_SET_DATA_R:						return &setDataReliablePdu;			break;
		//case PDU_DATA_R:							return &dataReliablePdu;			break;
		//case PDU_EVENT_REPORT_R:					return &eventReportReliablePdu;		break;
		//case PDU_COMMENT_R:							return &commentReliablePdu;			break;
		//PDU_RECORD_R
		//case PDU_SET_RECORD_R:						return &setRecordReliablePdu;		break;
		//case PDU_RECORD_QUERY_R:					return &recordQueryReliablePdu;		break;
		//case PDU_COLLISION_ELASTIC:					return &collisionElasticPdu;		break;
		case PDU_ENTITY_STATE_UPDATE:				return &entityStateUpdatePdu;		break;
		//case PDU_DIRECTED_ENERGY_FIRE:				return &directedEnergyFirePdu;		break;
		case PDU_ENTITY_DAMAGE_STATUS:				return &entityDamageStatusPdu;		break;
		//PDU_INFORMATION_OPERATIONS_ACTION
		//PDU_INFORMATION_OPERATIONS_REPORT
		case PDU_ATTRIBUTE:							return &attributePdu;				break;
	}	

	return NULL;
}
