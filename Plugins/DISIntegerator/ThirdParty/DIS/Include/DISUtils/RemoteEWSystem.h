#pragma once
#include <DIS7/EventIdentifier.h>
#include <DIS7/EntityStatePdu.h>
#include <DISUtils/Vector2D.h>
#include <DISUtils/Vector3D.h>
#include<DISUtils/ThresholdCalculator.h>
#include <DISEnums/es_appear_sensoremitter.h>
#include <DISUtils/RemoteEntity.h>
#include <DISUtils/DISDefinitions.h>

using namespace DIS;

struct CJammedEntity
{
	EntityID entityID;
	bool doRetain{ true };
};

	class EXPORT_MACRO CRemoteEWSystem : public CRemoteEntity
	{
	private:
		bool _bIsRadarActive{ false };
		EventIdentifier	_eventID;			//for EE PDU
		es_appear_sensoremitter::bitmask _entityAppearence;
		AttributePdu _AttrPdu;

		std::vector<CJammedEntity> _vecJammedEntities{};
		RadarAttributesParams _radarAttributeParams;
		RadarParams	_RadarParam;

	public:
		CRemoteEWSystem(void);
		~CRemoteEWSystem(void);
	
		void FillEntityParameters(const EntityStatePdu& esPdu);
		void FillEntityParameters(const AttributePdu& attrPdu);
	
		void Initialize(const EntityStatePdu& esPdu, float appTime) override;
	
		void HandleEntityStatePDU(const EntityStatePdu& esPdu);
		void HandleEntityStateUpdatePDU(const EntityStateUpdatePdu& esUpdatePdu);
		void HandleElectromagneticEmissionPDU(const ElectromagneticEmissionsPdu& eePdu);
		void HandleIffPDU(const IFFPdu& iffPdu);
		void HandleAttributePdu(const AttributePdu& ttrPdu);
		void HandleEntityAttributePdu(const AttributePdu& attrPdu);
		void HandleDetonationPDU(const DetonationPdu& detonationPdu);
		void HandleFirePDU(const FirePdu& firePdu);
	
		void Update(float deltaTime, float fAppTime);
		void Render();

		int  GetType();
		int	 GetRemoteEntityType();
		bool GetIsRadarActive() { return _bIsRadarActive; }
		std::vector<CJammedEntity> GetJammedEntities();
		RadarAttributesParams GetRadarAttributeParams() { return _radarAttributeParams; }
		LocalHealth GetDamageState();
		es_appear_sensoremitter::bitmask GetEntityAppearence();

		bool IsFlamming();
		bool IsEntityEmittingSmoke();
	};
	

