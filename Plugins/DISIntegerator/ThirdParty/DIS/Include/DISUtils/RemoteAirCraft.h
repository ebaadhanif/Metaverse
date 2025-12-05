#pragma once
#include <DISUtils/Vector2D.h>
#include <DISUtils/Vector3D.h>
#include <DISUtils/ThresholdCalculator.h>
#include <DISUtils/DISDefinitions.h>
#include <DISUtils/RemoteEntity.h>
#include <DISUtils/DeadReckoningModel.h>
#include <DIS7/EventIdentifier.h>
#include <DIS7/EntityStatePdu.h>
#include <DISEnums/es_appear_platform_air.h>
#include <string>

using namespace DIS;

	class EXPORT_MACRO CRemoteAircraft : public CRemoteEntity
	{
	private:
		AttributePdu _attrPdu;
		EventIdentifier	_eventID;			//for EE PDU
		es_appear_platform_air::bitmask 	_entityAppearence;
		float _Gs;
		RWRData	_rwr{};
		Vector3Double _eLocation{};
		EulerAngles	_eOrientation{};
		std::vector<TrackerEntity>	_trackerEntities{};
		float _lastChaffFiredTime{};
		float _lastFlareFiredTime{};
		bool _bIsNavigtionsLightOn{};

	public:
		CRemoteAircraft(void);
		~CRemoteAircraft(void);

		void FillEntityParameters(const EntityStatePdu& esPdu);
		void FillEntityParameters(const AttributePdu& attrPdu);
		void Initialize(const EntityStatePdu& esPdu, float appTime) override;

		void HandleEntityStatePDU(const EntityStatePdu& esPdu);
		void HandleEntityStateUpdatePDU(const EntityStateUpdatePdu& esUpdatePdu);
		void HandleElectromagneticEmissionPDU(const ElectromagneticEmissionsPdu& eePdu);
		void HandleIffPDU(const IFFPdu& iffPdu);
		void HandleFirePDU(const FirePdu& firePdu);
		void HandleDetonationPDU(const DetonationPdu& detonationPdu);
		void HandleAttributePdu(const AttributePdu& attrPdu);

		void SetLastChaffFiredTime(float chaff) { _lastChaffFiredTime = chaff; };
		void SetLastFlareFiredTime(float flare) { _lastFlareFiredTime = flare; };

		void Update(float deltaTime, float fAppTime);
		void Render();

		int  GetType();
		int	 GetRemoteEntityType();
		RWRData* GetRWR();
		float GetLastChaffFiredTime() { return _lastChaffFiredTime; };
		float GetLastFlareFiredTime() { return _lastFlareFiredTime; };
		CDeadReckoningModel* GetDeadReckoningModel() { return &_deadReckoningModel; }
		LocalHealth GetDamageState();
		es_appear_platform_air::bitmask GetEntityAppearence();

		bool IsLandingGearExtended();
		bool IsFlamming();
		bool IsEntityEmittingSmoke();
		bool IsNavigationLightsOn();
	
	//public:
	//	std::string GetIFFStr();
	//	std::string GetApplicationNameStr(int appId);
	//	std::string GetForceIdStr();
	//	//void SetInfoDisplayFlag(bool flag) { this->_infoDisplayFlag = flag; }
	//	//void ToggleInfoDisplayFlag() {
	//	//	this->_infoDisplayFlag = ! this->_infoDisplayFlag;
	//	//}
	//	bool GetRaidApplicationDisplayCheck();

	//	std::string GetSciteNameAbbreviation();
	};


