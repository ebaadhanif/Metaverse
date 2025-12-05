
#pragma once
#include <DIS7\EntityID.h>
#include <DIS7/FirePdu.h>
#include <DISUtils/Vector2D.h>
#include <DISUtils/RemoteEntity.h>
#include <DISUtils/Vector3D.h>
#include<DISUtils/ThresholdCalculator.h>
#include <DISEnums/es_appear_munition.h>
#include <DISUtils/DISDefinitions.h>
#include <DISUtils/DeadReckoningModel.h>

using namespace DIS;

	class EXPORT_MACRO CRemoteWeapon : public CRemoteEntity
	{
	private:
		FirePdu _fireParams;
		unsigned int _RequestId;
		int	 _ReleaseWeaponId;
		bool _bIsDetonated;

		EventIdentifier _eventID;
		es_appear_munition::bitmask _entityAppearence;

	public:
		CRemoteWeapon(void);
		~CRemoteWeapon(void);

		void FillEntityParameters(const EntityStatePdu& esPdu);
		void FillEntityParameters(const FirePdu& firePdu);

		void Initialize(const FirePdu& firePdu, float appTime);
		void Initialize(const EntityStatePdu& esPdu, float appTime) override;

		void HandleEntityStatePDU(const EntityStatePdu& esPdu);
		void HandleEntityStateUpdatePDU(const EntityStateUpdatePdu& esUpdatePdu);
		void HandleElectromagneticEmissionPDU(const ElectromagneticEmissionsPdu& eePdu);
		void HandleIffPDU(const IFFPdu& iffPdu);
		void HandleDetonationPDU(const DetonationPdu& detonationPdu);
		void HandleFirePDU(const FirePdu& firePdu);
		void HandleAttributePdu(const AttributePdu& attrPdu);

		void Update(float deltaTime, float totalAppTime);
		void Render();

		int  GetType();
		FirePdu GetFirePdu() { return _fireParams; }
		int GetRemoteEntityType();
		LocalHealth GetDamageState();
		es_appear_munition::bitmask GetEntityAppearence();

		bool IsFlamming();
		bool IsEntityEmittingSmoke();
	};

