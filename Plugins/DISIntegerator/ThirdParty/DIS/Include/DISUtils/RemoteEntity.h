#pragma once

#include <DISUtils/Vector2D.h>
#include <DISUtils/Vector3D.h>
#include <DISUtils/ThresholdCalculator.h>
#include <DISUtils/DeadReckoningModel.h>
#include <DISUtils/DISConversions.h>
#include <DISUtils/DISDefinitions.h>
#include <DISUtils/ArticulationParametersManager.h>
#include <DISUtils/IFFSystem.h>

#include <DIS7\EntityID.h>
#include <DIS7/EntityStatePdu.h>
#include <DIS7/EntityStateUpdatePdu.h>
#include <DIS7/ElectromagneticEmissionsPdu.h>
#include <DIS7/IFFPdu.h>
#include <DIS7/FirePdu.h>
#include <DIS7/DetonationPdu.h>
#include <DIS7/AttributePdu.h>

#include <DISEnums/AFISE\SiteID.h>
#include <DISEnums/AFISE/ApplicationID.h>
#include <DISEnums/AFISE/SiteID.h>
#include <DISUtils/NetworkAnalyzer.h>
#include <DISUtils/HostnamesFileHandler.h>
#include <string>
#include <unordered_map>
#include <memory>
#include <DIS7\msLibMacro.h>

using namespace DIS;

	#define HBT_DAM_TIMEOUT_MPLIER				2.4f
	#define HBT_TIMEOUT_MPLIER					3.0f

	#define REMOTE_ENTITY_DEFAULT				0
	#define	REMOTE_ENTITY_RADAR					1
	#define	REMOTE_ENTITY_AIRCRAFT				2
	#define	REMOTE_ENTITY_WEAPON				3
	#define	REMOTE_ENTITY_VEHICLE				5
	#define	REMOTE_ENTITY_MISSLE_LAUNCHER		6
	#define REMOTE_ENTITY_LIFE_FORM				7
	#define REMOTE_ENTITY_CULTURAL_FEATURE		8
	#define REMOTE_ENTITY_C3I_SYSTEM			10	
	#define REMOTE_ENTITY_EXPANDABLE			15
	#define	REMOTE_ENTITY_ARMORED_VEHICLE		16
	#define REMOTE_ENTITY_EW_SYSTEM				17
    #define REMOTE_ENTITY_SURFACE				18
	#define OWN_AIRCRAFT						50

//Enums for Entitytype

enum RemoteEntityType
{
	ALL_ENTITIES = -1, DEFAULT_ENTITY = 0, RADAR = 1, AIRCRAFT = 2, WEAPON = 3, VEHICLE = 5, 
	MUNITION_LAUNCHER = 6, LIFE_FORM = 7, CULTRAL_FEATURE = 8, C3I_SYSTEM = 10, EXPANDABLES = 15,
	ARMORED_VEHICLE = 16, EW_SYSTEM = 17, SURFACE_ENTITY = 18
};

	class EXPORT_MACRO CRemoteEntity
	{
	protected:
		EntityStatePdu	_entityParams{};
		CDeadReckoningModel	_deadReckoningModel{};
		CArticulationParametersManager _articulationParameterManager{};
		ElectromagneticEmissionsPdu _eePDU{};
		EntityDamageDescription	_damageDescription{};
		CIFFSystem _iffSystem;
		ElectromagneticEmissionsMessage _eeMsg{};
		Vector3Double _localPosition{};
		Vector3Double _geocentricPosition{};
		GeodeticCoordinates	_geodeticPosition{};

		bool _bIsInitialized{ false };
		bool _bIsRender{ false };
		bool _isFrozen{ false };
		bool _bIsDREnabled{ true };
		bool _bIsAlive{ true };
		bool _bIsDeactived{ false };

		short _speedInKnots{};
		unsigned short _applicationType{};
		unsigned short _forceID{};

		int	 _localEntityType{};
		int	 _id{};
		int	_fps{ 5 };
		unsigned int _fAMSLAltitude{}; // Height in Feet

		double _lastArticulationUpdateTime{};
		float _lastUpdatedTime{};
		float _totalTimeElapsed{};
		float _lastEEUpdatedTime{};
		float _fLastRenderSetTime{};
		float _yaw{};
		float _pitch{};
		float _roll{};
		float _rcs{ 0.0f };

		char _callSign[12]{};

		std::string	_strCountry{};
		std::string	_strForceColor{};
		std::string	_applicationTypeName{};
		std::string	_siteName{};
		std::string	_applicationShortName{};
		std::string	_siteShortName{};
		std::string	_hostName{};
		std::string	_forceName{};

	public:
		CRemoteEntity(void);
		virtual ~CRemoteEntity(void);
		void SetElectromegnaticEmissionsMessage(ElectromagneticEmissionsPdu eePdu);
		void Initialize();

		//**********************************************************************//
		//							Get Functions								//
		//**********************************************************************//

		float GetYaw() { return _yaw; }
		float GetPitch() { return _pitch; }
		float GetRoll() { return _roll; }

		std::string	GetForceName(unsigned short forceId);
		int	GetForceID() { return (int)this->_entityParams.getForceId(); }
		EntityID GetEntityID();
		DIS::EntityType	GetEntityType() { return _entityParams.getEntityType(); };

		int	GetApplicationType() const { return _applicationType; }
		std::string	GetApplicationTypeName() { return _applicationTypeName; };
		std::string	GetSiteName() { return _siteName; };
		std::string	GetApplicationShortName();
		std::string	GetSiteShortName() { return _siteShortName; };
		std::string	GetHostname() { return _hostName; }

		std::string	GetCallSign() { return std::string(_callSign); }

		bool GetIsFrozen() { return _isFrozen; };
		bool GetisAlive() { return _bIsAlive; }
		bool GetIsDeactivated() { return _bIsDeactived; }

		float GetLastUpdatedTime() { return _lastUpdatedTime; }
		unsigned int GetTimeStamp() { return _entityParams.getTimestamp(); }
		float GetTotalTimeElapsed() { return _totalTimeElapsed; }

		CDeadReckoningModel* GetDeadReckoningModel() { return &_deadReckoningModel; }

		DIS::Vector3Double GetEntityLocalPosition() { return _localPosition; }
		GeodeticCoordinates	GetEntityGeodeticPosition() { return _geodeticPosition; }
		DIS::Vector3Double GetEntityGeocentricPosition() { return _geocentricPosition; }

		short GetSpeedInKnots();

		float GetRcsValue() { return _rcs; }
		void SetRcsValue(float rcsVal) { _rcs = rcsVal; }

		virtual	int GetType() = 0;
		virtual int	GetRemoteEntityType() = 0;

		virtual LocalHealth	GetDamageState() = 0;

		CIFFSystem* GetIFFSystemAddress();

		//**********************************************************************//
		//							Set Functions								//
		//**********************************************************************//

		void SetIsAlive(bool flag) { this->_bIsAlive = flag; }

		void SetForceColor(unsigned char forceID);

		void SetIsRender(bool flag, float fAppTime);
		//**********************************************************************//
		virtual	void FillEntityParameters(const DIS::EntityStatePdu& esPdu) = 0;
		virtual	void Initialize(const DIS::EntityStatePdu& esPdu, float appTime) = 0;

		//**********************************************************************//
		//							PDU Handle Functions						//
		//**********************************************************************//
		virtual	void HandleEntityStatePDU(const DIS::EntityStatePdu& esPdu) = 0;
		virtual	void HandleEntityStateUpdatePDU(const DIS::EntityStateUpdatePdu& esUpdatePdu) = 0;
		virtual void HandleDetonationPDU(const DIS::DetonationPdu& detonationPdu) = 0;
		virtual	void HandleElectromagneticEmissionPDU(const DIS::ElectromagneticEmissionsPdu& eePdu) = 0;
		virtual void HandleIffPDU(const DIS::IFFPdu& iffPdu) = 0;
		virtual void HandleFirePDU(const DIS::FirePdu& firePdu) = 0;
		virtual void HandleAttributePdu(const DIS::AttributePdu& attrPdu) = 0;

		//**********************************************************************//
		virtual	void Update(float, float fAppTime);
		virtual	void Render() = 0;

		void ResetDamageDescription();
		virtual bool IsFlamming() = 0;
		virtual bool IsEntityEmittingSmoke() = 0;

		void DeactivateRadar();

		bool CompareEntityIDs(DIS::EntityID e1, DIS::EntityID e2);

		ElectromagneticEmissionsPdu GetElectronicmagneticEmissionsData();
	};

