#pragma once
#include <DISUtils/RemoteEntity.h>
#include <DISEnums/es_appear_platform_air.h>

using namespace DIS;

	class EXPORT_MACRO CRemoteDefaultEntity :public CRemoteEntity
	{
	private:
		es_appear_platform_air::bitmask _entityAppearence;

	public:
		CRemoteDefaultEntity();
		virtual ~CRemoteDefaultEntity();

		void Initialize(const EntityStatePdu& esPdu, float appTime) override;
		void FillEntityParameters(const EntityStatePdu& esPdu);

		void HandleEntityStatePDU(const EntityStatePdu& esPdu);
		void HandleEntityStateUpdatePDU(const EntityStateUpdatePdu& esUpdatePdu);
		void HandleElectromagneticEmissionPDU(const ElectromagneticEmissionsPdu& eePdu);
		void HandleIffPDU(const IFFPdu& iffPdu);
		void HandleFirePDU(const FirePdu& firePdu);
		void HandleDetonationPDU(const DetonationPdu& detonationPdu);
		void HandleAttributePdu(const AttributePdu& attrPdu);

		void Update(float deltaTime, float fApptime);
		void Render();

		int  GetType();
		int	 GetRemoteEntityType();
		LocalHealth GetDamageState();
		es_appear_platform_air::bitmask GetEntityAppearence();

		bool IsFlamming();
		bool IsEntityEmittingSmoke();
	};


