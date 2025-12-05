#pragma once
#include <DISUtils/DISDefinitions.h>
#include <DISUtils/IPacketProcessor.h>  // for base class
#include <DISUtils/IFFSystem.h>

//using namespace DIS::ENUMS;
namespace DIS {

	/*********************************************PDU CALLBACKS*******************************************/

	using AcknowledgeCallback = std::function<void(const AcknowledgeMessage&)>;
	using ActionRequestCallback = std::function<void(const ActionRequestMessage&)>;
	using ActionResponseCallback = std::function<void(const ActionResponseMessage&)>;
	using AttributeCallback = std::function<void(const AttributeMessage&)>;
	using CollisionCallback = std::function<void(const CollisionMessage&)>;
	using DataCallback = std::function<void(const DataMessage&)>;
	using DataQueryCallback = std::function<void(const DataQueryMessage&)>;
	using DetonationCallback = std::function<void(const DetonationMessage&)>;
	using ElectromagneticEmissionsCallback = std::function<void(const ElectromagneticEmissionsMessage&)>;
	using EntityStateCallback = std::function<void(const EntityStateMessage&)>;
	using EntityStateUpdateCallback = std::function<void(const EntityStateUpdateMessage&)>;
	using EventReportCallback = std::function<void(const EventReportMessage&)>;
	using FireCallback = std::function<void(const FireMessage&)>;
	using IFFCallback = std::function<void(const CIFFSystem&)>;
	using RemoveEntityCallback = std::function<void(const RemoveEntityMessage&)>;
	using SetDataCallback = std::function<void(const SetDataMessage&)>;
	using StartResumeCallback = std::function<void(const StartResumeMessage&)>;
	using StopFreezeCallback = std::function<void(const StopFreezeMessage&)>;
	using SignalCallback = std::function<void(const SignalMessage&)>;

	/*static AttributeCallback _cbAttribute = nullptr;
	static AcknowledgeCallback _cbACK = nullptr;
	static ActionRequestCallback _cbActionRqst = nullptr;
	static ActionResponseCallback _cbActionRspnse = nullptr;
	static CollisionCallback _cbCollision = nullptr;
	static DataCallback _cbData = nullptr;
	static DataQueryCallback _cbDataQuery = nullptr;
	static DetonationCallback _cbDetonation = nullptr;
	static ElectromagneticEmissionsCallback _cbEE = nullptr;
	static EntityStateCallback _cbFunction = nullptr;
	static EntityStateUpdateCallback _cbES = nullptr;
	static EventReportCallback _cbEventRprt = nullptr;
	static FireCallback _cbFire = nullptr;
	static IFFCallback _cbIFF = nullptr;
	static RemoveEntityCallback _cbRmveEntity = nullptr;
	static SetDataCallback _cbSetData = nullptr;
	static SignalCallback _cbSgnl = nullptr;
	static StartResumeCallback _cbstrtResume = nullptr;
	static StopFreezeCallback _cbstpFreeze = nullptr;*/

}
/*********************************************REMOTE ENTITY CALLBACKS*******************************************/
