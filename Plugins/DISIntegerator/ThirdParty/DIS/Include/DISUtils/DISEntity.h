#pragma once
#include <DISUtils/IFFSystem.h>
#include <functional>
#include <DISUtils/DeadReckoningModel.h>
#include <DIS7/ElectromagneticEmissionsPdu.h>
#include <DISEnums/DeadReckoningAlgorithm.h>
#include <DISEnums/DetonationResult.h>
#include <DISUtils/ArticulationParametersManager.h>
#include <DIS7/AttributePdu.h>
#include <DIS7/AttributeRecordSet.h>
#include <DIS7/msLibMacro.h>
#include <DISEnums\IFFSystemPower.h>
#include <DISEnums\IFFChangeOptionsType.h>
#include <DISEnums\DetonationTypeIndicator.h>

namespace DIS
{
	class EXPORT_MACRO CDISEntity
	{
	private:
		CArticulationParametersManager _articulationParametersManager{};

		double _initializationDelay{};
		float _requestTime{};

		bool _isInitialized{ false };

		EntityID _entityID{};
		EntityTypeWithDescription _entityType{};
		CDeadReckoningModel _deadReckoningModel{};
		DEAD_RECKONING_STEP_MODE _deadReckoningStepMode{};
		EntityInitializationData _initializationData{};
		EntityStateMessage _disEntityState{};
		ElectromagneticEmissionsPdu	_eePDU{};
		EntityStatePdu _esPDU{};
		CIFFSystem _iffSystem{};
		AttributeMessage _disAttribute{};
		LocalHealth _health{};

		unsigned char _forceID{};

		std::function<void()> _onUpdateEEPDU{};

		unsigned int _charlieHeight{};

		Vector3Double _predictedLocalPosition{};
		Vector3Double _predictedGeoPosition{};
		Vector3Double _geocentricPosition{};
		Vector3Float _geocentricVelocity{};
		Vector3Float _geocentricAcceleration{};
		Vector3Float _bodyAngularVelocity{};
		GeodeticCoordinates _geodeticCooridnates{};
		GeodeticCoordinates _predictedGeodeticCooridnates{};

		EulerAngles	_geocentricOrientation{};
		EulerAngles	_previousGeocentricOrientation{};

		int _fps{};
		int _deadReckoningAlgorithm{};
		int _afiseEntityType{};
		int _numberOfPDUsSent{};
		int _numberOfESPDUsSentPerSecond{};
		int _numberOfAccelerationPDUs{};
		int _numberOfHeightPDUs{};

		float _appTime{};
		float _firstEDSPDUTime{};
		float _totalTimeElapsed{};
		float _lastEDSPduSentTime{};
		float _previousTotalTimeElapsed{};
		float _lastEDSPDUTime{};
		float _lastESUpdatedTime{};
		float _lastEEPDUSentTime{};
		float _fLastCounterTime{};

		bool _checkThresholds{ true };
		bool _isESPDUSent{ false };
		bool _isEEPDUSent{ false };
		bool _iffSystemState{ false };
		bool _isRadarON{ false };
		bool _isAlive{ true };								// If this entity is alive or not.
		bool _isExploded{ false };							// If this entity is exploded or not.
		bool _isPositionOrOrientationThreshold{ false };
		bool _isUpdateEEPDU{ true };
		bool _removeExplodedEntity{ true };
		bool _isbeamDataUpdated{ false };
		bool _isEntityPaused{ false };
		bool _attributeStateChangeIndicator{ false };
		bool _sendESPDUInBundle{ false };
		bool _firstEDSPDUSent{ false};

		std::vector<TrackerEntity> _trackerEntities{};

		void Initialize(float deltaTime, float appTime, EntityStateMessage disEntityState);

		void SendEntityStatePDU(const EntityStateMessage& entityState);
		bool SendEntityStateUpdatePdu(const std::vector<VariableParameterRecord>& variableParameters);
		void SendAttributePDU(std::vector<AttributeRecordSet> attributeRecordSets);

		void SendIFFPDU(unsigned char changeOption, unsigned int altitude);

		void SendFirstElectromagneticEmissionPDU();
		void SendElectromagneticEmissionPDU(bool stateChangeIndicator = false);
		void SendFinalElectromagneticEmissionPDU();

		void SendFirePDU(GeodeticCoordinates geodeticPosition, EntityID firingEntityID, EntityID targetEntityID, EntityID munitionExpendibleID, int stationNumber, EntityType munitionType, int munitionTypeIndex, unsigned int fireMissionIndex);
		void SendDetonationPDU(GeodeticCoordinates location,EntityID firingEntityID,EntityID targetEntityID,EntityID explodingEntityID,unsigned char detonationResult,DetonationTypeIndicator detonationTypeIndicator,int munitionTypeIndex);
		
		void SendCollisionPDU(EntityID issuingEntityID, EntityID CollidingEntityID, CollisionType collisiontyp, Vector3Float positionInEntityCoordinates, Vector3Double positionInWorldCoordinates, Vector3Float velocityInWorldCoordinates, float mass);

		void SendRemoveEntityPDU();

		void AttachAttributePDUWithEntityStatePDU();
		void SetIFFSystemState(bool state);

	public:
		CDISEntity();
		~CDISEntity();

		EntityID RequestInitialization(EntityInitializationData initializationData, bool sendESPDUInBundle = false);

		//**********************************************************************//
		//							Get Functions							    //
		//**********************************************************************//
		EntityID GetEntityID() const;
		EntityTypeWithDescription GetEntityType() const;

		EntityStatePdu* GetEntityStatePDU();
		ElectromagneticEmissionsPdu* GetElectromagneticEmissionsPDU();
		IFFModesData GetIFFParameters();

		CDeadReckoningModel* GetDeadReckoningModel();
		CArticulationParametersManager* GetArticulationParametersManager() noexcept;
		LocalHealth GetLocalHealth() const;
		float GetFirstEDSPDUTime() { return _firstEDSPDUTime; } const
		float GetLastEDSPDUTime() { return _lastEDSPDUTime; } const
		float GetLastEDSPduSentTime() { return _lastEDSPduSentTime; } const
		bool GetIsAlive() { return _isAlive; } const
		const bool GetIFFSystemState();


		bool IsInitialized() const { return _isInitialized; }

		bool IsESPDUSent() const;
		bool IsEEPDUSent() const;
		bool GetFirstEDSPDUSent() { return _firstEDSPDUSent; } const
		float GetTotalTimeElapsed() { return _totalTimeElapsed; } const
		//***********************************************************************//

		//**********************************************************************//
		//							Set Functions							    //
		//**********************************************************************//
		void SetPower(IFFSystemPower power = IFFSystemPower::PWR_NORMAL);
		void SetRadarState(bool isRadarON, float fAppTime);
		void SetEntityStatePDUPadding(unsigned char padding);
		void SetFireMsg(FireMessage msg);
		void SetCollisionMsg(CollisionMessage msg);

		void SetBeamsState(bool activateBeams);

		void SetEntityAttributes(AttributeMessage msg);

		void SetFirstEDSPDUTime(float firstEDSPDUTime);
		void SetLastEDSPDUTime(float lastEDSPDUTime);
		void SetLastEDSPduSentTime(float lastEDSPduSentTime);
		void SetFirstEDSPDUSent(bool firstEDSPDUSent);
		//***********************************************************************//

		//**********************************************************************//
		//					  Tracker & Beam Functions				            //
		//**********************************************************************//

		std::vector<TrackerEntity>* GetTrackerEntities();
		bool TrackerEntityExists(EntityID entityID);
		void AddTrackerEntity(TrackerEntity trackerEntity);
		void AddPickedTargetToBeamData(EntityID targetEntityID, TargetType targetType, unsigned char beamFunction = 0);
		void AddPickedTargetToBeamData(EntityID targetEntityID, bool isPSR, bool isIFF);

		void SetElectromagneticEmissionSystemData(ElectromagneticEmissionSystemData);

		void RemoveTrackerEntity(TrackerEntity trackerEntity);
		void RemoveOldTrackerEntities(float appTime);
		void RemovePickedTargetFromBeamData(EntityID targetEntityID, bool forceToSendPDUs = false);
		void RemovePickedTargetFromBeamData(EntityID targetEntityID, bool isPSR, bool isIFF);
		void RemoveAllPickedTargetsFromBeamData(unsigned char beamFunction = 0, bool forceToSendPDU = false);
		void RemoveAllJamTracks();
		void RemovePSRAllJamTracks();
		void RemoveIFFAllJamTracks();
		bool IsRadarON() const;
		//***********************************************************************//

		void Update(
			float deltaTime,
			float fAppTime,
			EntityStateMessage disEntityState,
			IFFModesData iffData,
			bool hasEEPDUUpdate = false,
			bool eeStateChangeIndicator = false,
			bool sendESPDUByForce = false,
			bool enableAccelerationTx = true,
			bool enableAngularVelocityTx = true);

		void UpdateWeapon(
			float deltaTime,
			float fAppTime,
			EntityStateMessage disEntityState,
			bool isWeaponTimeout, 		
			bool sendESPDUByForce = false,
			bool enableAccelerationTx = true,
			bool enableAngularVelocityTx = true);

		// No need to pass arguments to default parameters, 
		//if detonationTypeIndicator = DETONATION_TYPE_INDICATOR::NON_MUNITION_EXPENDIBLE
		void Explode(
			DetonationMessage msg,
			unsigned int appearance,
			bool removeExplodedEntity,
			bool isImpactedByOther = false);

		void RemoveEntity();

		static bool CompareEntityIDs(EntityID e1, EntityID e2);

	};
}