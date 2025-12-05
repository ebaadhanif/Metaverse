#pragma once

#include <DISUtils/RemoteEntity.h>
#include <DISEnums/es_appear_platform_land.h>

using namespace DIS;

	class EXPORT_MACRO CRemoteArmoredVehilce : public CRemoteEntity
	{
	private:
		es_appear_platform_land::bitmask _entityAppearence;

		float _lastUpdateTimeInP3D;
		float _FAppTime;
		float _fLastCreationInP3DAttemptTime;
		double _turretHeading;
		double _turretElevation;
		double _secondaryGunHeading;
		double _secondaryGunElevation;

	public:
		CRemoteArmoredVehilce(void);
		~CRemoteArmoredVehilce(void);

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
		es_appear_platform_land::bitmask GetEntityAppearence();

		bool IsFlamming();
		bool IsEntityEmittingSmoke();
	};

