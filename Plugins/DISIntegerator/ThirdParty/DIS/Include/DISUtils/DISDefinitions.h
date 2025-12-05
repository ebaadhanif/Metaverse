#pragma once
#include <DIS7\msLibMacro.h>
#include <tuple>
#include <string>
#include <functional>
#include <DIS7/MunitionDescriptor.h>
#include <DIS7/ElectromagneticEmissionSystemData.h>
#include <DIS7/FixedDatum.h>
#include <DIS7/VariableDatum.h>
#include <DIS7/AttributeRecordSet.h>
#include <DIS7/EntityID.h>
#include <DIS7/Vector3Double.h>
#include <DIS7/Vector3Float.h>
#include <DIS7/EulerAngles.h>
#include <DIS7/Marking.h>
#include <DIS7/VariableParameterRecord.h>
#include <DIS7/EventIdentifier.h>
#include <DIS7/EntityType.h>
#include <DIS7/RadioType.h>
#include <DIS7/OneByteChunk.h>
#include <DIS7/IntercomCommunicationsParameters.h>
#include <DISUtils/DISTime.h>
#include <DISEnums/ForceID.h>
#include <DISEnums/ActionID.h>
#include <DISEnums/StateChangeUpdateIndicator.h>
#include <DISEnums/DetonationResult.h>
#include <DISEnums/DetonationTypeIndicator.h>
#include <DISEnums/DeadReckoningAlgorithm.h>
#include <DISEnums/EventType.h>
#include <DISEnums/CollisionType.h>
#include <DISEnums/Reason.h>
#include <DISEnums/simman_stop_frozenbehavior.h>
#include <DISEnums/radio_tx_encoding.h>
#include <DISEnums/communications_channel_type.h>
#include <DISEnums/TransmitLineState.h>
#include <DISEnums/ControlType.h>
#include <DISEnums/Command.h>
#include <DISEnums/AcknowledgeFlag.h>
#include <DISEnums/ProtocolVersion.h>
#include <DISEnums/TDLType.h>
#include <DISEnums\ServiceRequest.h>
#include <DIS7\SupplyQuantity.h>
#include <DISEnums\GeneralRepairCode.h>
#include <DISEnums\RepairResponse.h>
#include <DIS7\PropulsionSystemData.h>
#include <DIS7\VectoringNozzleSystem.h>
#include <DISEnums/TransmitState.h>
#include <DISEnums/InputSource.h>
#include <DISEnums/AntennaPatternType.h>
//#include <DISEnums/MajorModulation.h>
//#include <DISEnums/RadioSystem.h>
#include <DISEnums/CryptoSystem.h>
#include <DISEnums/Crypto_Key_Id_Record.h>
#include <DIS7/RadioEntityType.h>
#include <DIS7/ModulationType.h>
#include <DISEnums/ReceiverState.h>
#include <DISEnums/SystemType.h>
#include <DISEnums/SystemName.h>
#include <DISEnums/SystemMode.h>
#include <DISEnums/IFFChangeOptionsType.h>
#include <DISEnums/IFFMilitaryEmergency.h>
#include <DISEnums/IFFModeStatus.h>
#include <DISEnums/IFFSystemPower.h>
#include <DISEnums/IFFSystemStatus.h>

#include <DISEnums/ComponentVisualDamageStatus.h>
#include <DISEnums/ComponentDamageStatus.h>
#include <DISEnums/ComponentIdentification.h>
#include <DISEnums/ComponentVisualSmokeColor.h>
#include<DIS7/DirectedEnergyDamage.h>

using namespace DIS::ENUMS;

namespace DIS
{
#pragma region MathConstantsAndConversions

	constexpr double DIS_PI = 3.141592654;

	constexpr double MIN_YAW = -DIS_PI;
	constexpr double MAX_YAW = DIS_PI;
	constexpr double DIS_MIN_PITCH = -DIS_PI / 2.0;
	constexpr double DIS_MAX_PITCH = DIS_PI / 2.0;
	constexpr double MIN_ROLL = -DIS_PI;
	constexpr double MAX_ROLL = DIS_PI;
	constexpr double MIN_LATITUDE = -90;
	constexpr double MAX_LATITUDE = 90;
	constexpr double MIN_LONGITUDE = -180;
	constexpr double MAX_LONGITUDE = 180;

	constexpr double FEET_TO_METER = 0.3048;
	constexpr int METERS_PER_NMI = 1852;
	constexpr double METERS_IN_ONE_DEG = 111120.0;
	constexpr double METERS_PER_FEET = 3.280839895013123;
	constexpr double FEET_PER_NAUTICAL_MILE = 6076.12;
	constexpr double METER_PER_SEC_TO_KNOTS = 1.944012;

	constexpr double LAT_SAHIWAL = 30.66075;
	constexpr double LONG_SAHIWAL = 73.10133;
	constexpr double ELIP_ALT_SAHIWAL = 151.0;

	constexpr double DIS_DEG_2_RAD(double degree) { return ((degree) * (DIS_PI / 180.0)); }
	constexpr double DIS_RAD_2_DEG(double radian) { return ((radian) * (180.0 / DIS_PI)); }

	constexpr double SEMI_MAJOR = 6378137.0;
	constexpr double SEMI_MINOR = 6356752.314200000000;
	constexpr double FLATENING = 0.00335281066474748;

#pragma endregion MathConstantsAndConversions

#pragma region DISConstants

	constexpr float THRESHOLD_OOS_ES_POSITION = 10.0f;//10.0f
	constexpr float THRESHOLD_NORMAL_ES_POSITION = 6.0f;//1.0f		// This value is for adaptive thresholds for position in Meters.
	constexpr float THRESHOLD_AOI_ES_POSITION = 3.0f;//0.25f
	constexpr float THRESHOLD_SR_ES_POSITION = 1.0f;//0.05f

	constexpr float THRESHOLD_OOS_ES_ORIENTATION = 15.0f;
	constexpr float THRESHOLD_NORMAL_ES_ORIENTATION = 8.0f;		// This value is for adaptive thresholds for orientation in Degrees.
	constexpr float THRESHOLD_AOI_ES_ORIENTATION = 5.0f;
	constexpr float THRESHOLD_SR_ES_ORIENTATION = 3.0f;/*1.0f*/

	constexpr float REGION_OOS_ES_POSITION = 0.0f;
	constexpr float REGION_NORMAL_ES_POSITION = 37040.0f;//20.0f NM	
	constexpr float REGION_AOI_ES_POSITION = 18520.0f;//10.0f NM   // This value is for Adaptive Regions in Meters.
	constexpr float REGION_SR_ES_POSITION = 9260.0f;//5.0f NM

													// DIS Time Thresholds
	constexpr float TIMESTAMP_AHEAD = 5.0;
	constexpr float TIMESTAMP_BEHIND = 5.0;

	constexpr int ENTITY_MAX_HEALTH = 100;

	constexpr float	MISSILE_SENSITIVE_REGION_REQUEST_TIME = 0.14f;
	constexpr float	MISSILE_NORMAL_REQUEST_TIME = 1.0f;

	//for fire pdu
	constexpr int NO_FIRE_MISSION = 0;

	//Appearance bits
	constexpr int APPEARANCE_FROZEN_BIT = 21;
	constexpr int APPEARANCE_STATE_BIT = 23;

	//Maximum Socket recieving buffer size
	constexpr int MAX_RECEIVE_BUFFER_SIZE = 8192;

	constexpr short NO_SITE = 0;
	constexpr short NO_APPLICATION = 0;
	constexpr short NO_ENTITY = 0;

	constexpr int ALL_SITES = 65535;
	constexpr int ALL_APPLIC = 65535;
	constexpr int ALL_ENTITITIES = 65535;

	const EntityID TARGET_ID_UNKNOWN = EntityID();
	const EntityID NO_SPECIFIC_ENTITY = EntityID();

	const unsigned char PROTOCOL_VERSION = (unsigned char)ProtocolVersion::IEEE_12781_2012.getValue();

	//Resupply Timers (in seconds)
	constexpr int RESUP_REC_T1 = 5;
	constexpr int RESUP_REC_T2 = 55;
	constexpr int RESUP_SUP_T1 = 60;

	//Repair Timers (in seconds)
	constexpr int REPAR_REC_T1 = 5;
	constexpr int REPAR_SUP_T1 = 12;
	constexpr int REPAR_SUP_T2 = 12;

#pragma endregion DISConstants

	enum DR_CURRENT_OWNERSHIP_MODE
	{
		DR_CURRENT_OWNERSHIP_MODE_OWNER,
		DR_CURRENT_OWNERSHIP_MODE_REMOTE
	};

	enum DR_ENTITY_MOVEMENT_PHASE
	{
		DR_ENTITY_MOVEMENT_PHASE_INTERPOLATION,
		DR_ENTITY_MOVEMENT_PHASE_EXTRAPOLATION,
	};

	enum RequestStatus
	{
		OTHER = 0,
		PENDING = 1,
		EXECUTINGS = 2,
		PARTIALLY_COMPLETE = 3,
		COMPLETE = 4,
		REQUEST_REJECTED = 5,
		RETRANSMIT_REQUEST_NOW = 6,
		RETRANSMIT_REQUEST_LATER = 7,
		INVALID_TIME_PARAMETERS = 8,
		SIMULATION_TIME_EXCEEDED = 9,
		REQUEST_DONE = 10,
		TACCSF_LOS_REPLY_TYPE_1 = 100,
		TACCSF_LOS_REPLY_TYPE_2 = 101,
		JOIN_EXERCISE_REQUEST_REJECTED = 201,
	};

	enum RadarSubscriptionState
	{
		UNSUBSCRIBED = 0,
		SUBSCRIBED = 1,
		SUBSCRIBED_BY_OTHERS = 2
	};

	enum RadarDataEventType
	{
		RADAR_DATA_EVENT_ADD,
		RADAR_DATA_EVENT_UPDATE,
		RADAR_DATA_EVENT_REMOVE,
		RADAR_DATA_EVENT_REMOVE_ALL
	};

	enum EventActionType
	{
		RADAR_DEPLOYMENT_REQUEST,
		RADAR_DEPLOYMENT_RESPONSE_VSM,
		RADAR_RECEIVAL_ON_SSA,
		RADAR_SUB_REQUEST,
		RADAR_SUB_RESPONSE_VSM,
		RADAR_SUB_ON_SSA,
		RADAR_UNSUB_REQUEST,
		RADAR_UNSUB_RESPONSE_VSM,
		RADAR_UNSUB_ON_SSA,
		RADAR_ADGE__IO_REQUEST,
		RADAR_ADGE_IO_RESPONSE_VSM,
		RADAR_ADGE_IO_ACK_SSA,
		RADAR_UPDATION_REQUEST,
		RADAR_UPDATION_RESPONSE_VSM,
		RADAR_UPDATION_ACK_SSA,
		RADAR_DELETION_REQUEST,
		RADAR_DELETION_RESPONSE,
		RADAR_DELETION_ACK_SSA
	};

	enum ActionPduRequestIDs
	{
		OTHER_RADAR_REQUEST_ID = 0,
		GMCC_RADAR_SUBSCRIPTION_REQUEST = 1,
		GMCC_ADGE_IO_ACTION_REQUEST = 2,
		GMCC_RADAR_DEPLOYMENT_REQUEST_DATA = 3,
	};

	enum AdgeIORequestActionType
	{
		ADGE_NONE = 0,
		ADGE_SAVE = 1,
		ADGE_LOAD = 2,
		ADGE_DELETE = 3,
	};

	enum class EXPORT_MACRO DEAD_RECKONING_STEP_MODE
	{
		AUTOMATIC,
		MANUAL,
	};

#pragma pack( push, 1 )

	enum class EXPORT_MACRO DIRECTION
	{
		NORTH,
		EAST,
		UP,
		DOWN,
	};

	enum class EXPORT_MACRO LocalFrame
	{
		ENU,
		EUN,
		NEU,
		NUE,
		UEN,
		UNE,
		NED,
		NDE,
		END,
		EDN,
		DEN,
		DNE,
	};

	enum class EXPORT_MACRO SignalPduTypes
	{
		LINK16_SIGNAL_PDU = 0,
		RADIO_VOICE_SIGNAL_PDU = 1,
		INTERCOM_VOICE_SIGNAL_PDU = 2,
		TACAN_AA_TR_SIGNAL_PDU = 3
	};

	//LINK16 ENUMRATIONS STARTS

	enum class EXPORT_MACRO Link16Power
	{
		POWER_ON,
		POWER_OFF,
	};

	enum class EXPORT_MACRO FlightLeadStatus
	{
		FL_YES,
		FL_NO,
	};

	enum class EXPORT_MACRO TransmitterPowerRange
	{
		HI = 300,		//In Knots
		MED = 130,
		LOW = 20,
		OFF = 0,
	};
	enum class EXPORT_MACRO TransmitterPowerOutput
	{
		OUTPUT_HI = 200,		//In WATTS
		OUTPUT_MED = 42,
		OUTPUT_LOW = 1,
		OUTPUT_NONE = 0,
	};

	enum class EXPORT_MACRO NetStatusSync
	{
		INPROG,
		COARSE,
		FINE,
	};
	enum class EXPORT_MACRO FrequencyMode
	{
		MODE1,
		MODE2,
		MODE3,
		MODE4,
	};
	enum class EXPORT_MACRO SynchronizationState
	{
		COARSE_SYNCHRONIZATION = 1,
		FINE_SYNCHRONIZATION = 2,
	};

	enum class EXPORT_MACRO TargetSortingStatus
	{
		ENGAGING,
		INVESTIGATING,
		MISSILE_IN_FLIGHT,
		WEAPON_RELEASED,
		NEW_SENSOR_TARGET_REPORT,
		TARGET_DESTROYED,
		DISENGAGING,
		TARGET_PARTIALLY_DESTROYED,
		HEADS_UP,
		LOCK_ON,
	};

	enum class EXPORT_MACRO TargetType
	{
		NO_TARGET = 0,
		NORMAL_TARGET = 1,
		TRACK_TARGET = 2,
		BUGGED_TARGET = 6,
		HARD_LOCKED_TARGET = 14 // a hard lock target is also a locked target
	};

	enum class EXPORT_MACRO TrackLockedType
	{
		PRIMARY = 1,		// if LOCKED || BUGDED TARGET
		SECONDARY = 2,		// if TRACKED TARGET
	};

	enum class EXPORT_MACRO MissileStateOnRemoteAircraft
	{
		NO_MISSILE,
		LAUNCHED,
		ACTIVE,
		IMPACT,
		DETONATE,
		MISSING,
	};

	enum class EXPORT_MACRO CountermeasureType
	{
		CHAFF = 0,
		FLARE = 1,
		OTHER1 = 2,
		OTHER2 = 3,
	};

	enum class EXPORT_MACRO CounterMeasureProgram
	{
		NONE_PROGRAM = 0,
		PROGRAM1 = 1,
		PROGRAM2 = 2,
		PROGRAM3 = 3,
		PROGRAM4 = 4,
		PROGRAM5 = 5,
	};

	enum class EXPORT_MACRO TrackerEntityEquality
	{
		ENTITY_NOT_EQUAL,
		ENTITY_EQUAL,
		ENTITY_TYPE_DIFFERENT,
	};

	enum class EXPORT_MACRO GearPositionType
	{
		GEAR_POSITION_UNKNOWN = 1,
		GEAR_POSITION_UP = 2,
		GEAR_POSITION_DOWN = 3,
	};

	enum class EXPORT_MACRO EntityOwnershipType
	{
		_LOCAL,
		_REMOTE
	};

	struct EntityTypeDescription
	{
		/** Kind of entity */
		std::string	entityKindDesc;

		/** Domain of entity (air, surface, subsurface, space, etc) */
		std::string	domainDesc;

		/** country to which the design of the entity is attributed */
		std::string	countryDesc;

		/** category of entity */
		std::string	categoryDesc;

		/** subcategory of entity */
		std::string	subcategoryDesc;

		/** specific info based on subcategory field */
		std::string	specificDesc;

		std::string	extraDesc;
	};

	struct NEDVelocityFloat
	{
		float x{ 0.0f };
		float y{ 0.0f };
		float z{ 0.0f };

		void SetNedVelocity(float X, float Y, float Z)
		{
			x = X;
			y = Y;
			z = Z;
		}

		std::tuple<float, float, float> GetNedVelocity() const
		{
			return std::make_tuple(x, y, z);
		}
	};

	struct	EntityTypeWithDescription
	{
		EntityType entityType;
		EntityTypeDescription entityTypeDesc;
	};

	struct SimulationApplicationState
	{
		char callSign[50];
		bool status;
		uint8_t	capacity;
		unsigned short radarCount;
	};

	struct RadarSubscriptionResponseData
	{
		EntityID sensorGatewayAppID;
		EntityID radarEntityID;
		RadarSubscriptionState subscriptionState; // sub/unsub or subscribed by other
	};

	struct RadarRequestActionsResponseData
	{
		EntityID				actionRequestAppID;
		RequestStatus			requestStatus;
		unsigned short			localRequestID;
		RadarDataEventType		action;
		EntityID				radarEntityID;
	};

	struct AdgeRequestActionsResponseData
	{
		EntityID				actionRequestAppID;
		bool					requestStatus;
		char					action;
	};

	struct RadarSubscriptionRequestData
	{
		EntityID	radarEntityID;
		bool		subscriptionState;	//sub or unsub
		EntityID	sensorGatewayAppID;
		char		sensorGatewayStationName[50];
	};

	struct RadarRequestGenericData
	{
		INT16  GenericMsgType;
		INT16 ExactMsgType;
	};

	struct RadarRequestDeleteData : public RadarRequestGenericData
	{
		RadarDataEventType action;

		unsigned short srcSiteID{};
		unsigned short srcApplicationID{};
		unsigned short srcEntityID{};
		unsigned short destSiteID{};
		unsigned short destApplicationID{};
		unsigned short destEntityID{};

		RadarRequestDeleteData() {}
	};

	struct Location
	{
		float x;
		float y;
		float z;

		Location()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}
	};

	struct AdgeIORequestData
	{
		char action;
		char path[MAX_PATH];
		EntityID receivingVSMAppID;

		AdgeIORequestData()
		{
			action = (char)AdgeIORequestActionType::ADGE_NONE;
			sprintf(path, "");
		}

		AdgeIORequestData(AdgeIORequestActionType requestAction, std::string strPath)
		{
			action = (char)requestAction;
			sprintf(path, strPath.c_str());
		}
	};

	struct RadarClutterRegionData
	{
		INT16 AzStart;
		INT16 AzEnd;
		INT16 RgStart;
		INT16 RgEnd;
		INT16 Intensity;
		INT16 RegionNo;

		RadarClutterRegionData()
		{
			AzStart = -1;
			AzEnd = -1;
			RgStart = -1;
			RgEnd = -1;
			Intensity = 0;
			RegionNo = 0;
		}
	};

	struct RadarClutterData
	{
		INT16  ClutterType;
		INT16 RegionCount;

		RadarClutterRegionData  Regions[10];

		RadarClutterData()
		{
			ClutterType = 0;
			RegionCount = 0;
		}
	};

	struct RadarAttributesParams
	{
		bool stateChangeIndicator{ false };
		EntityID entityId;
		int radarState;
		int status;
		float antennaHeight;
		int clutterLevel;
		int mode;
		float degreeOut;
		float xOut;
		float yOut;
		std::string locationName;
		int RPM;
		int sic;
		int frequency;
		float tilt;
		float PRF;
		bool isSubscribed{ false };
		EntityID subscribedSensorAppID{};    //sensorGateway ID for sub or unsub
											 //Clutter Data
		RadarClutterData clutterData;
		unsigned short Sector;

		RadarAttributesParams()
		{
		}

		RadarAttributesParams(bool stateChange, EntityID id, int radSt, int st, float anHt, int clt, int md, float dOut, float xot,
			float yot, std::string locName, int rp, int sc, int freq, float tlt, float pr, bool subcribd, EntityID sensorAppID, RadarClutterData clutter, short sector)
		{
			stateChangeIndicator = stateChange;
			radarState = radSt;
			entityId = id;
			status = st;
			antennaHeight = anHt;
			clutterLevel = clt;
			mode = md;
			degreeOut = dOut;
			xOut = xot;
			yOut = yot;
			locationName = locName;
			RPM = rp;
			sic = sc;
			frequency = freq;
			tilt = tlt;
			PRF = pr;
			isSubscribed = subcribd;
			subscribedSensorAppID = sensorAppID;
			clutterData = clutter;
			Sector = sector;
		}
	};

	struct RadarRequestDeploymentData : public RadarRequestGenericData
	{
		unsigned short requestID;
		RadarDataEventType action;
		int type;
		int SelRPM;
		int ForceID;
		int GroupID;
		int SiteID;
		int RadarStatus;
		int Status;
		int ClutterLevel;
		int Mode;
		unsigned short Sector;

		float AntenaHeight;
		float RadarRange;
		float SelFreq;
		float ERP;	//Effective Radiated Power
		float SelPRF;
		float SelTilt;
		float DegreeOut;
		float Xout;
		float Yout;
		Location RadarPos;
		COLORREF Color;
		char Designation[MAX_PATH];
		char LocName[100];

		// for Clutter   ...
		RadarClutterData  ClutterInfo;
		int destAppID{};
		int destSiteID{};
		int destEntityID{};
		int srcSiteID{};
		int srcAppID{};
		int srcEntityID{};
		int sicID{};
		int previousSicID{};
		char vsmCallSign[50];

		RadarRequestDeploymentData()
		{
			RadarStatus = 1;
		}
	};

	struct EntityTimeoutSettingsData
	{
		std::string	entityKind;
		int	entityKindID;
		std::string	entityDomain;
		int	entityDomainID;
		int	entityDomaintimeout;
	};

	struct EntityDeadReckoningSettingsData
	{
		std::string	entityKind;
		int	entityKindID;
		std::string	entityDomain;
		int	entityDomainID;
		int	drFPS;
		bool isDeadReckoning;
	};

	struct ApplicationNameData
	{
		std::string name;
		int	ID;
		std::string	shortName;
	};

	struct SiteNameData
	{
		std::string	name;
		int	ID;
		std::string	shortName;
	};

	struct HostnamesData
	{
		std::string IPAddress;
		std::string hostname;
	};

	struct AttachedPartData
	{
		int afiseEntityType{ 0 };
		int stationNo{ 0 };
		int weaponQuantity{ 0 };

		AttachedPartData(int afiseEntity, int station, int quantity)
		{
			afiseEntityType = afiseEntity;
			stationNo = station;
			weaponQuantity = quantity;
		}
	};

	struct StandardAttachedPart {
		int standardStationNo{ 0 };
		int attachedPart{ 0 }; // ENUMS::AttachedParts::NOTHING_EMPTY.getValue() = 0
	};

	struct FighterStationAircraftData
	{
		EntityID entityID;
		unsigned int aircraftType;
		float height;
		float heading;
		Vector3Double position;
	};

	struct FighterStationAircraftLaunchData
	{
		char callSign[50]; // Max 50 character long Call Sign
		unsigned int noOfAircraft;
		FighterStationAircraftData aircraftData[4]; // As Fighter Station can generate 4 aircraft at maximum
	};

	struct FighterStationAircraftDropData
	{
		char callSign[50]; // Max 50 character long Call Sign
	};

	struct EntityDetails
	{
	public:
		float Hdg;
		float Spd;
		Vector3Double Pos;

		EntityDetails()
		{
			Hdg = 0.0f;
			Spd = 0.0f;
			Pos = Vector3Double();
		}
	};

#pragma region EntityDamageStatusData

	enum class EXPORT_MACRO LocalHealth
	{
		NO_DAMAGE = 100,
		MINOR_DAMAGE = 75,
		MEDIUM_DAMAGE = 50,
		MAJOR_DAMAGE = 25,
		DESTROYED = 0,
	};
#pragma endregion EntityDamageStatusData

#pragma region ElectromegnaticEmissionData

	const short NO_KIND = 0;
	const short NO_CATEGORY = 0;
	const short NO_SUBCAT = 0;
	const short NO_SPECIFIC = 0;

	const short NO_EMITTER = 0;
	const short NO_BEAM = 0;

	const short EE_HIGH_DENSITY_THRESH = 255;

	const short FALSE_TARGETS_ATTRIBUTE_RECORD = 3502; // [UID 66]

	const short NO_STATEMENT = 0; // [UID 295]

	const short FALSE_TARGET_ATTRIBUTE_RECORD_SIZE = 320;

	enum class EXPORT_MACRO JamType
	{
		SPOT,
		BARRAGE,
		FALSE_TARGET,
		PREEMPTIVE,
		NONE
	};

	enum class EXPORT_MACRO EEAttributeStateIndicator // [UID 300]
	{
		HEARTBEAT_UPDATE = 0,
		CHANGED_DATA = 1,
		HAS_CEASED = 2,
	};
#pragma endregion ElectromegnaticEmissionData

	struct RadarParams
	{
		int TypeIndex;
		std::string TypeName;

		float* Tilt;
		int nTilt;
		float SelTilt;

		int* Mode;
		int nMode;
		int SelMode;

		int* RPM;
		int nRPM;
		int SelRPM;
		int* MaxRange;
		int SelMaxRange;
		int MaxIFFRange;
		float RngRes;
		float AzRes;

		float* PRF;
		int nPRF;
		float SelPRF;

		float* Frequencies;
		int nFreq;
		float SelFreq;

		float AntGain;
		float PeakPwr;
		float RxSen;
		int MinHt;
		int MaxHt;
		float ERP;	//Effective Radiated Power
	};

	struct TrackerEntity
	{
		EntityID entityID;
		TargetType targetType;
		int	entityType;				//For sending RWR data with entityType, this could be radar, aircraft, missile etc.
		float fTime;

		TrackerEntityEquality operator==(const TrackerEntity& te) const
		{
			if ((entityID.getApplication() == te.entityID.getApplication())
				&& (entityID.getSite() == te.entityID.getSite())
				&& (entityID.getEntity() == te.entityID.getEntity()))
			{
				if (targetType == te.targetType)
				{
					return TrackerEntityEquality::ENTITY_EQUAL;
				}
				else
				{
					return TrackerEntityEquality::ENTITY_TYPE_DIFFERENT;
				}
			}

			return TrackerEntityEquality::ENTITY_NOT_EQUAL;
		}
	};

	struct GeodeticCoordinates {
		double latitude;//in decimalDegree
		double longitude;//in decimalDegree
		double altitude;//in meters

		void SetGeodeticCoordinates(double lat, double longi, double alt)
		{
			latitude = lat;
			longitude = longi;
			altitude = alt;
		}

		std::tuple<double, double, double> GetGeodeticCoordinates() const
		{
			return std::make_tuple(latitude, longitude, altitude);
		}
	};

	struct BodyAngles {
		double rollRad;
		double pitchRad;
		double yawRad;

		void SetBodyAnglesFloat(float yaw, float pitch, float roll)
		{
			rollRad = roll;
			pitchRad = pitch;
			yawRad = yaw > MAX_YAW ? yaw - (2.0 * MAX_YAW) : yaw;
		}
	};

	struct IFFModesData
	{
		int		Mode1;
		int		Mode2;
		int		Mode3;
		bool	ModeC;
		bool	Mode6A;
		bool	Mode6B;
	};

	struct RWRSignal {
		EntityID trackerID{};
		GeodeticCoordinates position{};
		TargetType targetType{};
		int trackerEntityType{};
	};

	struct RWRData {
		std::vector<RWRSignal> rwrSignals{};

		RWRData() {}
		~RWRData() {}

		void AddSignal(RWRSignal newRWRSignal) noexcept
		{
			for (auto& signal : rwrSignals)
			{
				if (signal.trackerID == newRWRSignal.trackerID)
				{
					signal.position = newRWRSignal.position;
					signal.targetType = newRWRSignal.targetType;

					return;
				}
			}

			rwrSignals.push_back(newRWRSignal);
		}

		void RemoveSignal(EntityID trackerID) noexcept
		{
			for (int i = 0; i < rwrSignals.size(); i++)
			{
				if (trackerID == rwrSignals[i].trackerID)
				{
					rwrSignals.erase(rwrSignals.begin() + i);
					return;
				}
			}
		}
	};

	struct LocalFrameInformation {
		DIRECTION x;
		DIRECTION y;
		DIRECTION z;
		LocalFrame frame;
		LocalFrameInformation() = default;
		LocalFrameInformation(DIRECTION xD, DIRECTION yD, DIRECTION zD, LocalFrame localFrame)
		{
			x = xD;
			y = yD;
			z = zD;
			frame = localFrame;
		}
	};

	class CMulticastSocket;
	class CRemoteEntitiesManager;

	struct EntityDamageDescription
	{
		Vector3Float damageLocation{ Vector3Float() };
		float damageDiameter{ 0.0f };
		float temperature{ 0.0f };
		DIS::ENUMS::ComponentIdentification componentIdentification{ DIS::ENUMS::ComponentIdentification::ENTITY_CENTER };
		LocalHealth health{ LocalHealth::NO_DAMAGE };
		DIS::ENUMS::COMPONENT_VISUAL_DAMAGE_STATUS::IsFirePresent isFirePresent{ DIS::ENUMS::COMPONENT_VISUAL_DAMAGE_STATUS::IsFirePresent::NOT_PRESENT };
		DIS::ENUMS::COMPONENT_VISUAL_DAMAGE_STATUS::SmokeComponentVisualDamageStatus smokeComponentVisualDamageStatus{ DIS::ENUMS::COMPONENT_VISUAL_DAMAGE_STATUS::SmokeComponentVisualDamageStatus::NO_SMOKE };
		DIS::ENUMS::COMPONENT_VISUAL_DAMAGE_STATUS::SurfaceDamageComponentVisualDamageStatus surfaceDamageComponentVisualDamageStatus{ DIS::ENUMS::COMPONENT_VISUAL_DAMAGE_STATUS::SurfaceDamageComponentVisualDamageStatus::NORMAL_APPEARANCE };
		DIS::ENUMS::ComponentVisualSmokeColor componentVisualSmokeColor{ DIS::ENUMS::ComponentVisualSmokeColor::NO_SMOKE };
		EventIdentifier fireEventID{ EventIdentifier() };
	};

#pragma region FireAndDetonationPdusData

	struct MunitionDescriptorRecord {
		unsigned short warhead{};
		unsigned short fuse{};
	};

#pragma endregion FireAndDetonationPdusData

#pragma region SimulationManagementPdusData

	struct AcknowledgeMessage
	{
		EntityID receivingID;
		AcknowledgeFlag	acknowledgeFlag{ AcknowledgeFlag::START_RESUME };

		unsigned int requestID;
	};

	enum ApplicationPlayPauseState
	{
		PLAYED,
		LOCALLY_PAUSED,
		GLOBALLY_PAUSED
	};

#pragma endregion SimulationManagementPdusData

#pragma region ActionRequestPduData

	struct ActionRequestMessage
	{
		EntityID receivingEntityID;

		ActionID actionID{ ActionID::OTHER };

		std::vector<FixedDatum> vecFixedDatum;
		std::vector<VariableDatum> vecVariableDatum;
	};
#pragma endregion ActionRequestPduData

#pragma region ActionResponsePduData

	struct ActionResponseMessage
	{
		EntityID receivingEntityID;

		ActionID requestStatus{ ActionID::OTHER };

		std::vector<FixedDatum> vecFixedDatum;
		std::vector<VariableDatum> vecVariableDatum;
	};
#pragma endregion ActionResponsePduData

#pragma region AttributePduData

	struct AttributeMessage
	{
		std::vector<AttributeRecordSet> attributeRecordSets;
	};
#pragma endregion AttributePduMessage

#pragma region CollisionPduData

	typedef Vector3Float PositionInEntityCoordinates; //meters
	struct CollisionMessage
	{
		EntityID issuingEntityID; // Local entity that is collided
		EntityID collidingEntityID; // Remote entity with which local entity is collided

		ENUMS::CollisionType collisionType;

		Vector3Float positionInEntityCoordinates{}; // in meters, in NED frame (x North, y East, z Down)
		Vector3Double positionInWorldCoordinates; // in meters, in NED frame (x North, y East, z Down)

		Vector3Float velocityInWorldCoordinates; // Local velocity (x, y, z in m/s and in NED) 

		float mass; // mass of issuing entity

		short	speedInMeterPerSecond; //for reception of collision, DIS is providing Speed in meter per second

		CollisionMessage() : collisionType(ENUMS::CollisionType::INELASTIC), mass(0.0f), speedInMeterPerSecond(0)
		{
			positionInEntityCoordinates.setX(0.0f);
			positionInEntityCoordinates.setY(0.0f);
			positionInEntityCoordinates.setZ(0.0f);

			positionInWorldCoordinates.setX(0.0);
			positionInWorldCoordinates.setY(0.0);
			positionInWorldCoordinates.setZ(0.0);

			velocityInWorldCoordinates.setX(0.0f);
			velocityInWorldCoordinates.setY(0.0f);
			velocityInWorldCoordinates.setZ(0.0f);
		}
	};
#pragma endregion CollisionPduData

#pragma region CreateEntityPdu

	struct CreateEntityMessage
	{
		EntityID receivingID; //Site,App,ReferenceNo
		unsigned int requestID; //specific and unique entity removal request
	};
#pragma endregion CreateEntityPdu

#pragma region DataPdu

	struct DataMessage
	{
		EntityID receivingEntityID;

		std::vector<FixedDatum> vecFixedDatum;
		std::vector<VariableDatum> vecVariableDatum;
	};
#pragma endregion DataPdu

#pragma region DataQueryPdu

	struct DataQueryMessage
	{
		EntityID receivingEntityID;

		std::vector<FixedDatum> vecFixedDatum;
		std::vector<VariableDatum> vecVariableDatum;
	};
#pragma endregion DataQueryPdu

#pragma region SetDataPdu

	struct SetDataMessage
	{
		EntityID receivingEntityID;

		std::vector<FixedDatum> vecFixedDatum;
		std::vector<VariableDatum> vecVariableDatum;
	};
#pragma endregion SetDataPdu

#pragma region CollisionControlSetDataPdu

	struct CollisionControlSetDataMessage
	{
		EntityID originationEntityID;
		EntityID receivingEntityID;

		bool bIsCollisionOn{ true };
	};
#pragma endregion CollisionControlSetDataPdu

#pragma region DetonationPduData

	struct DetonationMessage
	{
		EntityID sourceEntityID;
		EntityID targetEntityID;
		EntityID explodingEntityID;
		Vector3Float velocity;
		GeodeticCoordinates locationInWorldCoordinates;

		/*For munition descriptor*/
		int munitionTypeIndex;
		DetonationTypeIndicator detonationTypeIndicator{ DetonationTypeIndicator::MUNITION };

		PositionInEntityCoordinates locationOfEntityCoordinates;
		DetonationResult detonationResult{ DetonationResult::OTHER };
	};
#pragma endregion DetonationPduData

#pragma region ElectromagneticEmissionPduData
	struct ElectromagneticEmissionsMessage
	{
		EntityID emittingEntityID;
		StateChangeUpdateIndicator stateChangeUpdateIndicator{ StateChangeUpdateIndicator::STATE_UPDATE };
		std::vector<ElectromagneticEmissionSystemData> systems;

	};
#pragma endregion ElectromagneticEmissionPduData

#pragma region EntityStateUpdatePduData

	struct EntityStateUpdateMessage
	{

	};
#pragma endregion EntityStateUpdatePduData

#pragma region EventReportPduData

	struct EventReportMessage
	{
		EntityID receivingEntityID;

		EventType eventType{ EventType::OTHER };

		std::vector<FixedDatum> vecFixedDatum;
		std::vector<VariableDatum> vecVariableDatum;
	};
#pragma endregion EventReportPduData

#pragma region FirePduData

	struct FireMessage
	{
		EntityID firingEntityID;
		EntityID targetEntityID;
		EntityID munitionExpendableID;
		unsigned int fireMissionIndex{ NO_FIRE_MISSION };
		GeodeticCoordinates geodeticLocation;
		Vector3Float velocity;
		float range;

		//For Munition Descriptor Record
		int munitionTypeIndex;
		EntityType munitionType;

		//For Padding
		int	stationNo;
	};
#pragma endregion FirePduData

#pragma region EntityDamageStatusPduData
	//................................................................................................................
	//................................................................................................................
	//................................................................................................................
	//................................................................................................................
	//................................................................................................................
	//................................................................................................................
	//................................................................................................................
	//................................................................................................................
	struct EntityDamageStatusMessage
	{
		EntityID damagedEntityID;
		//unsigned short	padding1;
		//unsigned short padding2;
		unsigned short numberOfDamageDescription;
		std::vector<DirectedEnergyDamage> damageDescriptionRecords;
	};
#pragma endregion EntityDamageStatusPduData

#pragma region IFFMessage

	struct IFFMessage
	{
		//********Layer 1**********//
		EntityID emittingEntityID;
		Vector3Float relativeAnennaLocation;
		unsigned int systemDesignator;
		unsigned int charlieHeight;
		IFFModesData paramIFF;

		//** SystemIdentifier info **//
		DIS::ENUMS::SystemType systemType{ DIS::ENUMS::SystemType::MARK_X_XII_ATCRBS_MODE_S_TRANSPONDER };
		DIS::ENUMS::SystemName  systemName{ DIS::ENUMS::SystemName::MARK_X_XII_ATCRBS_MODE_S };
		DIS::ENUMS::SystemMode systemMode{ DIS::ENUMS::SystemMode::OTHER };
		DIS::ENUMS::IFFChangeOptionsType changeOptions{ DIS::ENUMS::IFFChangeOptionsType::CHANGE };
		//*****************************//

		//** FundamentalOperationalData info **//
		IFFSystemStatus systemStatus;
		unsigned char dataField1; //Alternate Mode4 Challenge/Reply.
		unsigned char informationLayers;
		unsigned char dataField2; //Modifier record.
		unsigned short parameter1; //Mode 1 Code Record.
		unsigned short parameter2; //Mode 2 Code Record.
		unsigned short parameter3; //Mode 3/A Code Record.
		unsigned short parameter4; //Mode 4 Code Record.
		unsigned short parameter5; //Mode C Altitude Record.
		unsigned short parameter6; //TCAS/ACAS status Record.

								   //For further use //
		IFFMilitaryEmergency militaryEmergency;
		IFFSystemPower systemPower;
		IFFModeStatus modeStatus;

		unsigned int platformAltitudeMSL;
	};
#pragma endregion IFFMessage
	struct TimeRecord
	{
		unsigned int hoursSinceJan1970;
		unsigned int microSecondPastHour;

	};

#pragma region RemoveEntityPduData

	struct RemoveEntityMessage
	{
		EntityID receivingID; //Site,App,ReferenceNo
		unsigned int requestID; //specific and unique entity removal request
	};
#pragma endregion RemoveEntityPduData

#pragma region SignalPduData
	struct SignalMessage
	{
		EntityID entityRadiaID;	//ID of the entity that is the source of the communication
		unsigned int radioID{ 0 };	//particular radio within an entity
		DIS::ENUMS::radio_tx_encoding::EncodingType encodingType{ DIS::ENUMS::radio_tx_encoding::EncodingType::X_16_BIT_LINEAR_PCM };
		DIS::ENUMS::radio_tx_encoding::EncodingClass encodingClass{ DIS::ENUMS::radio_tx_encoding::EncodingClass::APPLICATION_SPECIFIC_DATA };
		DIS::ENUMS::TDLType tdlType{ DIS::ENUMS::TDLType::LINK_16_ENHANCED_DATA_RATE_EDR_JTIDS_MIDS_TADIL_J };
		unsigned int sampleRate; //Depends on encoding scheme record, if Encoded Audio(0) then samples/sec if database(3) then set as 0, for data transmission set as bits/sec
		unsigned int samples; //If encoding class is not Encoded audio(0) then set 0
		std::vector<DIS::OneByteChunk> vecSignalData;

	};
#pragma endregion SignalPduData

#pragma region TransmitterMessage
	struct TransmitterMessage
	{
		EntityID entityRadioID;								 /* radio refernce id*/
		unsigned short radioID{ 0 };						 /* radio number */
		RadioEntityType radioEntityType;					 /* radio Type Record */
		DIS::ENUMS::TransmitState transmitState
		{ DIS::ENUMS::TransmitState::OFF };					 /* transmitter state */

		DIS::ENUMS::InputSource inputSource
		{ DIS::ENUMS::InputSource::OTHER };					 /* input source */

		GeodeticCoordinates antennaLocation;				 /* Location of antenna */
		Vector3Float relativeAntennaLocation;				 /* relative location of antenna */

		DIS::ENUMS::AntennaPatternType antennaPatternType
		{ DIS::ENUMS::AntennaPatternType::OMNI_DIRECTIONAL }; /* antenna pattern type */

		unsigned short antennaPatternCount;					 /* antenna pattern length */
		unsigned long long frequency;						 /* frequency */
		float transmitFrequencyBandwidth;					 /* transmit frequency Bandwidth */
		float power;										 /* transmission power */

		ModulationType modulationType;						 /* modulation type record */

		DIS::ENUMS::CryptoSystem cryptoSystem
		{ DIS::ENUMS::CryptoSystem::OTHER };				 /* Depict crptosystem used */

		unsigned int cryptoKey;							     /* crypto system key identifer */

		DIS::ENUMS::Crypto_Key_Id_Record::CryptoMode cryptoMode{ DIS::ENUMS::Crypto_Key_Id_Record::CryptoMode::BASEBAND };

		std::vector<Vector3Float> modulationParametersList;  /* variable length list of modulation parameters */
		std::vector<Vector3Float> antennaPatternList;		 /* variable length list of antenna pattern records */
	};
#pragma endregion TransmitterMessage

#pragma region ReceiverMessage
	struct ReceiverMessage
	{
		EntityID radioReferenceID;					/* radio refernce id*/
		unsigned short radioNo{ 0 };		    /* radio number */
		DIS::ENUMS::ReceiverState receiverState{ DIS::ENUMS::ReceiverState::ON_AND_RECEIVING };
		float receivedPower{ 0.0f };					/* received power */
		EntityID transmitterEntityId;			/* ID of transmitter */
		unsigned short transmitterRadioNo{ 0 };		/* ID of transmitting radio */
	};
#pragma endregion ReceiverMessage

//#pragma region IntercomSignalPduData
//	struct IntercomSignalMessage
//	{
//		EntityID entityIntercomID;	//ID of the entity that is the source of the communication
//		unsigned short intercomID{ 0 };	//particular radio within an entity
//		DIS::ENUMS::radio_tx_encoding::EncodingType encodingType{ DIS::ENUMS::radio_tx_encoding::EncodingType::X_16_BIT_LINEAR_PCM };
//		DIS::ENUMS::radio_tx_encoding::EncodingClass encodingClass{ DIS::ENUMS::radio_tx_encoding::EncodingClass::APPLICATION_SPECIFIC_DATA };
//		DIS::ENUMS::TDLType tdlType{ DIS::ENUMS::TDLType::LINK_16_ENHANCED_DATA_RATE_EDR_JTIDS_MIDS_TADIL_J };
//		unsigned int sampleRate; //Depends on encoding scheme record, if Encoded Audio(0) then samples/sec if database(3) then set as 0, for data transmission set as bits/sec
//								 /*
//								 ........................changed unsigned int to unsigned short..........................
//								 */
//		unsigned short samples; //If encoding class is not Encoded audio(0) then set 0
//		std::vector<DIS::OneByteChunk> vecIntercomSignalData;
//
//	};
//#pragma endregion IntercomSignalPduData

#pragma region IntercomControlPduData
	struct IntercomControlMessage
	{
		DIS::ENUMS::ControlType controlType{ DIS::ENUMS::ControlType::ACK_REQUEST_GRANTED };
		DIS::ENUMS::communications_channel_type::bitmask communications_channel;
		EntityID sourceEntityID;/** Source entity ID */
		unsigned short sourceCommunicationsDeviceID;/** The specific intercom device being simulated within an entity. */
		unsigned int sourceLineID;/** Line number to which the intercom control refers */
		unsigned int transmitPriority;/** priority of this message relative to transmissons from other intercom devices */
		DIS::ENUMS::TransmitLineState transmitLineState{ DIS::ENUMS::TransmitLineState::TRANSMITTING };/** current transmit state of the line */
		DIS::ENUMS::Command command{ DIS::ENUMS::Command::CONNECT };/** detailed type requested. */
		EntityID masterEntityID;/** eid of the entity that has created this intercom channel. */
		unsigned short masterCommunicationsDeviceID;/** specific intercom device that has created this intercom channel */
		unsigned short masterCommunicationsChannelNumber;/** unique intercom channel created by this Master	Intercom Reference ID and Master Intercom Number pair */
		unsigned int intercomParametersLength;/** number of intercom parameters */
		std::vector<IntercomCommunicationsParameters> intercomParameters;/** ^^^This is wrong--the length of the data field is variable. Using a long for now. */

	};
#pragma endregion IntercomControlPduData

#pragma region EntityInformationInteraction

	//Entity state
	class EXPORT_MACRO EntityInitializationData
	{
	private:
		int afiseEntityType;
		float appTime;
		int fps;
		DEAD_RECKONING_STEP_MODE stepMode;
		ElectromagneticEmissionSystemData systemData;
		std::function<void()> onUpdateEEPDU;
		bool checkThreshold{ true };
		int deadReckoningAlgorithm{ DeadReckoningAlgorithm::DRMR_V_W.getValue() };
		bool eeStateChangeIndicator;
		float entityStateHeartbeat;
		float electromagneticEmissionHeartbeat;

	public:
		EntityInitializationData() {}

		EntityInitializationData(int AFISEEntityType, float AppTime, int FPS, DEAD_RECKONING_STEP_MODE StepMode,
			ElectromagneticEmissionSystemData SystemData, std::function<void()> OnUpdateEEPDU, bool CheckThreshold,
			int DeadReckoningAlgorithm, bool EEStateChangeIndicator, float EntityStateHeartbeat, float ElectromagneticEmissionHeartbeat)
		{
			afiseEntityType = AFISEEntityType;
			appTime = AppTime;
			fps = FPS;
			stepMode = StepMode;
			systemData = SystemData;
			onUpdateEEPDU = OnUpdateEEPDU;
			checkThreshold = CheckThreshold;
			deadReckoningAlgorithm = DeadReckoningAlgorithm;
			eeStateChangeIndicator = EEStateChangeIndicator;
			entityStateHeartbeat = EntityStateHeartbeat;
			electromagneticEmissionHeartbeat = ElectromagneticEmissionHeartbeat;
		}

		void SetAFISEEntityType(int type) { afiseEntityType = type; }
		void SetAppTime(float applicationTime) { appTime = applicationTime; }
		void SetFPS(int framepersec) { fps = framepersec; }
		void SetStepMode(DEAD_RECKONING_STEP_MODE sMode) { stepMode = sMode; }
		void SetEESystemData(ElectromagneticEmissionSystemData SystemData) { systemData = SystemData; }
		void SetOnUpdateEEPDU(std::function<void()> addEEUpdate) { onUpdateEEPDU = addEEUpdate; }
		void SetCheckThreshold(bool threshold) { checkThreshold = threshold; }
		void SetDeadReckoningAlgorithm(int DRA) { deadReckoningAlgorithm = DRA; }
		void SetEEStateChangeIndicator(bool stateChangeIndicator) { eeStateChangeIndicator = eeStateChangeIndicator; }
		void SetEntityStateHeartbeat(float esHeartbeat) { entityStateHeartbeat = esHeartbeat; }
		void SetElectromagneticEmissionHeartbeat(float eeHeartbeat) { electromagneticEmissionHeartbeat = eeHeartbeat; }

		int GetAFISEEntityType() { return afiseEntityType; }
		float GetAppTime() { return appTime; }
		int GetFPS() { return fps; }
		DEAD_RECKONING_STEP_MODE GetStepMode() { return stepMode; }
		ElectromagneticEmissionSystemData GetEESystemData() { return systemData; }
		std::function<void()> GetOnUpdateEEPDU() { return onUpdateEEPDU; }
		bool GetCheckThreshold() { return checkThreshold; }
		int GetDeadReckoningAlgorithm() { return deadReckoningAlgorithm; }
		bool GetEEStateChangeIndicator() { return eeStateChangeIndicator; }
		float GetEntityStateHeartbeat() { return entityStateHeartbeat; }
		float GetElectromagneticEmissionHeartbeat() { return electromagneticEmissionHeartbeat; }
	};

	class EXPORT_MACRO EntityStateMessage
	{
	private:
		ForceID forceID{ ForceID::OTHER };

		NEDVelocityFloat velocity; // Local velocity (x, y, heightVelocity)
		GeodeticCoordinates position{}; // Local Position (x, y, height)
		BodyAngles bodyAngles;

		unsigned int appearance{ 0 };

		float gs{ 0.0f };
		short speed{ 0 }; // knots.

		Marking marking;
		unsigned int capabilities{ 0 };

		bool articulationParametersChanged{ false };
		std::vector<VariableParameterRecord> variableParameters;

	public:

		EntityStateMessage() {}

		EntityStateMessage(ForceID forceId, NEDVelocityFloat Nedvelocity, GeodeticCoordinates GeoPosition,
			BodyAngles BodyAngles, unsigned int Appearance, float Gs, short Speed, Marking Marking,
			unsigned int Capabilities, bool ArticulationParamsChanged,
			std::vector<VariableParameterRecord> VariableParam)
		{
			forceID = forceId;
			velocity = Nedvelocity;
			position = GeoPosition;
			bodyAngles = BodyAngles;
			appearance = Appearance;
			gs = Gs;
			speed = Speed;
			marking = Marking;
			capabilities = Capabilities;
			articulationParametersChanged = ArticulationParamsChanged;
			variableParameters = VariableParam;
		}

		void SetForceID(ForceID forceId) { forceID = forceId; }
		void SetNEDVelocity(Vector3Float nedVelocity)
		{
			velocity.SetNedVelocity(nedVelocity.getX(), nedVelocity.getY(), nedVelocity.getZ());
		}
		void SetGeoPosition(double lat, double longi, float height)
		{
			position.SetGeodeticCoordinates(lat, longi, height);
		}
		void SetBodyAngles(float yaw, float pitch, float roll) { bodyAngles.SetBodyAnglesFloat(yaw, pitch, roll); }
		void SetAppearance(unsigned int Appearance) { appearance = Appearance; }
		void SetGs(float Gs) { gs = Gs; }
		void SetSpeed(short Speed) { speed = Speed; }
		void SetMarking(Marking Markng) { marking = Markng; }
		void SetCapabilities(unsigned int Capabilities) { capabilities = Capabilities; }
		void SetArticulationParametersChanged(bool ArticulationParamsChanged) { articulationParametersChanged = ArticulationParamsChanged; }
		void SetVariableParameters(std::vector<VariableParameterRecord> VariableParam) { variableParameters = VariableParam; }

		ForceID GetForceID() const { return forceID; }
		NEDVelocityFloat GetNEDVelocity() const { return velocity; }
		GeodeticCoordinates GetGeoPosition() const { return position; }
		BodyAngles GetBodyAngles() const { return bodyAngles; }
		unsigned int GetAppearance() const { return appearance; }
		float GetGs() const { return gs; }
		short GetSpeed() const { return speed; }
		Marking GetMarking() const { return marking; }
		unsigned int GetCapabilities() const { return capabilities; }
		bool GetArticulationParametersChanged() const { return articulationParametersChanged; }
		std::vector<VariableParameterRecord> GetVariableParameters() const { return variableParameters; }
	};

#pragma endregion EntityInformationInteraction

	struct TrackData
	{
		unsigned short trackNo; //In case tracking numbering logic changed
		EntityID trackEntityID;
		int	fusedRadarType; //Assign type from AFISE Entities Definitions list
		EntityID radarEntityID;
		char quality;
		char ident[4];	//Add truncation at the end of the string
		char callSign[10]; //Add truncation at the end of the string
	};

#define SMCC_GMCC_TRACKS_DATA_SIZE 25
	struct SMCCGMCCTracksData
	{
		int	noOfTracks;
		TrackData tracks[SMCC_GMCC_TRACKS_DATA_SIZE];
	};

#define GMCC_RADARS_ASSIGNMENT_LIMIT 64
	struct GMCCRadarAssignmentData
	{
		int	noOfRadars;
		EntityID entityIDs[GMCC_RADARS_ASSIGNMENT_LIMIT];
	};

	//------------------------------------------------------------------------------------------
#pragma region SimulationManagement

#pragma region StartResumePduData

	struct StartResumeMessage
	{
		EntityID receivingId; //Site,App,ReferenceNo

		TimeRecord realWorldTime;
		TimeRecord simulationTime;

		unsigned int requestID; //isStart
	};
#pragma endregion StartResumePduData

#pragma region StopFreezePduData

	struct StopFreezeMessage
	{
		EntityID receivingID; //Site,App,ReferenceNo

		TimeRecord realWorldTime;

		//ClockTime realWorldTime; //Real-world time at which the entity is to start/resume in the exercise
		DIS::ENUMS::Reason reason{ DIS::ENUMS::Reason::RECESS };
		unsigned char frozenBehaviour;
		unsigned int requestID;  //isStop
	};
#pragma endregion StopFreezePduData

#pragma region CommentPduData

	struct CommentMessage
	{
		EntityID receivingID;							/* Site,App,ReferenceNo	*/
		std::vector<VariableDatum> variableDatums;      /* variable length list of variable length datums */
	};
#pragma endregion CommentPduData

#pragma endregion SimulationManagement

	//
	//------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------
#pragma region Logistics

#pragma region ServiceRequestPduData

	struct ServiceRequestMessage
	{
		EntityID servicingEntityID;
		DIS::ENUMS::ServiceRequest serviceTypeRequested{ DIS::ENUMS::ServiceRequest::OTHER };
		unsigned int numberOfSupplyTypes;
		std::vector<SupplyQuantity> supplies;
	};
#pragma endregion ServiceRequestPduData

#pragma region ResupplyOfferPduData

	struct ResupplyOfferMessage
	{
		EntityID receivingEntityID;
		unsigned int numberOfSupplyTypes;
		std::vector<SupplyQuantity> supplies;

	};
#pragma endregion ResupplyOfferPduData

#pragma region ResupplyReceivedPduData

	struct ResupplyReceivedMessage
	{
		EntityID supplyingEntityID;
		unsigned int numberOfSupplyTypes;
		std::vector<SupplyQuantity> supplies;
	};
#pragma endregion ResupplyReceivedPduData

#pragma region ResupplyCancelPduData

	struct ResupplyCancelMessage
	{
		EntityID supplyingEntityID;
	};
#pragma endregion ResupplyCancelPduData

#pragma region RepairCompletePduData

	struct RepairCompleteMessage
	{
		EntityID receivingEntityID;
		DIS::ENUMS::GeneralRepairCode repair{ DIS::ENUMS::GeneralRepairCode::ALL_REQUESTED_REPAIRS_PERFORMED };
	};
#pragma endregion RepairCompletePduData

#pragma region RepairResponsePduData

	struct RepairResponseMessage
	{
		EntityID repairingEntityID;
		DIS::ENUMS::RepairResponse repairResult{ DIS::ENUMS::RepairResponse::REPAIR_ENDED };
	};
#pragma endregion RepairResponsePduData

#pragma endregion Logistics

#pragma region Distributed Emission Regeneration
	struct SeesMessage
	{
		unsigned int infraredSignatureRepresentationIndex;
		unsigned int acousticSignatureRepresentationIndex;
		unsigned int radarCrossSectionSignatureRepresentationIndex;
		unsigned int numberOfPropulsionSystems;
		unsigned int numberOfVectoringNozzleSystems;
		std::vector<PropulsionSystemData> propulsionSystemData;
		std::vector<VectoringNozzleSystem> vectoringSystemData;
	};

#pragma endregion  Distributed Emission Regeneration
#pragma pack( pop )
}