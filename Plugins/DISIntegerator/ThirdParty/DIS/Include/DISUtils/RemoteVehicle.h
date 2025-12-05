#pragma once
#include <DISEnums/es_appear_platform_land.h>
#include <DISUtils/RemoteEntity.h>
#include <DISUtils/DISDefinitions.h>
#include <DIS7/EntityStatePdu.h>

using namespace DIS;

	class EXPORT_MACRO CRemoteVehicle : public CRemoteEntity
	{
		es_appear_platform_land::bitmask _entityAppearence;
	public:
		CRemoteVehicle(void);
		~CRemoteVehicle(void);

		void Initialize(const EntityStatePdu& esPdu, float appTime) override;
		void FillEntityParameters(const EntityStatePdu& esPdu);

		void HandleEntityStatePDU(const EntityStatePdu& esPdu);
		void HandleElectromagneticEmissionPDU(const ElectromagneticEmissionsPdu& eePdu);
		void HandleEntityStateUpdatePDU(const EntityStateUpdatePdu& esUpdatePdu);
		void HandleIffPDU(const IFFPdu& iffPdu);
		void HandleFirePDU(const FirePdu& firePdu);
		void HandleDetonationPDU(const DetonationPdu& detonationPdu);
		void HandleAttributePdu(const AttributePdu& attrPdu);

		void Update(float deltaTime, float fAppTime);
		void Render();

		int  GetType();
		int	 GetRemoteEntityType();
		LocalHealth GetDamageState();
		es_appear_platform_land::bitmask GetEntityAppearence();

		bool IsFlamming();
		bool IsEntityEmittingSmoke();
	};

