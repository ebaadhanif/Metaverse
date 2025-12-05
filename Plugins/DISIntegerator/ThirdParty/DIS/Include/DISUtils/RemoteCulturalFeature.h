#pragma once
#include <DIS7\EntityID.h>
#include <DIS7/EntityStatePdu.h>
#include <DISUtils/Vector2D.h>
#include <DISUtils/Vector3D.h>
#include <DISUtils/RemoteEntity.h>
#include<DISUtils/ThresholdCalculator.h>
#include <DISEnums/es_appear_cultural.h>

using namespace DIS;

	class EXPORT_MACRO CRemoteCulturalFeature : public CRemoteEntity
	{
	private:
		EventIdentifier _eventID; //for EE PDU

		es_appear_cultural::bitmask _entityAppearence;
	public:
		CRemoteCulturalFeature(void);
		~CRemoteCulturalFeature(void);

		void Initialize(const EntityStatePdu& esPdu, float appTime) override;
		void FillEntityParameters(const EntityStatePdu& esPdu);

		void HandleEntityStatePDU(const EntityStatePdu& esPdu);
		void HandleEntityStateUpdatePDU(const EntityStateUpdatePdu& esUpdatePdu);
		void HandleElectromagneticEmissionPDU(const ElectromagneticEmissionsPdu& eePdu);
		void HandleIffPDU(const IFFPdu& iffPdu);
		void HandleFirePDU(const FirePdu& firePdu);
		void HandleDetonationPDU(const DetonationPdu& detonationPdu);
		void HandleAttributePdu(const AttributePdu& attrPdu);

		void Update(float deltaTime, float fAppTime);
		void Render();

		int  GetType();
		int	 GetRemoteEntityType();
		LocalHealth GetDamageState();
		es_appear_cultural::bitmask GetEntityAppearence();

		bool IsFlamming();
		bool IsEntityEmittingSmoke();
	};

