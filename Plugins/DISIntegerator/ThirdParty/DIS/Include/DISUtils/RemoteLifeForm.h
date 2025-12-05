#pragma once
#include <DISUtils/RemoteEntity.h>
#include <DISEnums/es_appear_lifeform.h>
#include <DISUtils/DISDefinitions.h>
#include <DISUtils/DeadReckoningModel.h>

using namespace DIS;

	class EXPORT_MACRO CRemoteLifeForm : public CRemoteEntity
	{
		es_appear_lifeform::bitmask _entityAppearence;
	public:
		CRemoteLifeForm(void);
		virtual ~CRemoteLifeForm(void);

		void Initialize(const EntityStatePdu& esPdu, float appTime) override;
		void FillEntityParameters(const EntityStatePdu& esPdu);

		void HandleEntityStatePDU(const EntityStatePdu& esPdu);
		void HandleElectromagneticEmissionPDU(const ElectromagneticEmissionsPdu& eePdu);
		void HandleIffPDU(const IFFPdu& iffPdu);
		void HandleFirePDU(const FirePdu& firePdu);
		void HandleEntityStateUpdatePDU(const EntityStateUpdatePdu& esUpdatePdu);
		void HandleDetonationPDU(const DetonationPdu& detonationPdu);
		void HandleAttributePdu(const AttributePdu& attrPdu);

		void Update(float deltaTime, float fApptime);
		void Render();

		int  GetType();
		int	 GetRemoteEntityType();
		LocalHealth GetDamageState();
		es_appear_lifeform::bitmask GetEntityAppearence();

		bool IsFlamming();
		bool IsEntityEmittingSmoke();
	};


