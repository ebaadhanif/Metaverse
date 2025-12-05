
#pragma once
#include <DIS7\EntityID.h>
#include <DIS7/FirePdu.h>
#include <DIS7/DetonationPdu.h>
#include <DISUtils/ThresholdCalculator.h>
#include <DISEnums/es_appear_expendables.h>
#include <DISUtils/RemoteEntity.h>

	class EXPORT_MACRO CRemoteExpandable : public CRemoteEntity
	{
	private:
		FirePdu	_fireParams;
		unsigned int _RequestId;
		int _ReleaseWeaponId;
		bool _bIsDetonated;
		float _lastUpdateTimeInP3D;
		float _fEightFpsUpdateTime;

		EventIdentifier _eventID;
		es_appear_expendables::bitmask _entityAppearence;

		//GBADS code for Depictions
		/*bool _bIsTracking;
		std::vector<int> vecGbadsIds;
		std::string trackName;*/
		//--GBADS

	public:
		CRemoteExpandable(void);
		~CRemoteExpandable(void);

		void FillEntityParameters(const  FirePdu& firePdu);
		void FillEntityParameters(const EntityStatePdu& esPdu);
		void Initialize(const FirePdu& firePdu, float appTime);
		void Initialize(const EntityStatePdu& esPdu, float appTime) override;

		void HandleEntityStatePDU(const EntityStatePdu& esPdu);//
		void HandleEntityStateUpdatePDU(const EntityStateUpdatePdu& esUpdatePdu);
		void HandleElectromagneticEmissionPDU(const ElectromagneticEmissionsPdu& eePdu);//
		void HandleIffAtcNavaidsPDU(const IFFPdu& iffPdu);//
		void HandleFirePDU(const FirePdu& firePdu);
		void HandleIffPDU(const IFFPdu& iffPdu);
		void HandleDetonationPDU(const DetonationPdu& detonationPdu) override;
		void HandleAttributePdu(const AttributePdu& attrPdu);

		void Update(float deltaTime, float fAppTime);//
		void Render();//

		int  GetType();
		int GetRemoteEntityType();
		FirePdu GetFirePdu() { return _fireParams; };
		LocalHealth GetDamageState();
		es_appear_expendables::bitmask GetEntityAppearence();

		bool IsFlamming();
		bool IsEntityEmittingSmoke();

		//GBADS code for Depictions
		//inline void SetTracking(bool state) { _bIsTracking = state; }
		//inline bool GetTrackingStatus() { return _bIsTracking; }
		//void SetGbadsId(int gbadsId);
		//int GetNoOfGbads();
		//void DropGbadsId(int gbadsId);
		//void SetTrackName(std::string trackName);
		//std::string GetTrackName();
		//--GBADS
	};
//}

