#pragma once
#include <DIS7/EntityID.h>
#include <DIS7/EntityStatePdu.h>
#include <DIS7/DataPdu.h>
#include <DISUtils/Vector2D.h>
#include <DISUtils/Vector3D.h>
#include <DISUtils/ThresholdCalculator.h>
#include <DISEnums/es_appear_platform_land.h>
#include <DIS7/DetonationPdu.h>  
#include <DIS7/ElectromagneticEmissionsPdu.h>
#include <DIS7/AttributePdu.h>
#include <DIS7/IFFPdu.h>
#include <DIS7/FirePdu.h>
#include <DISUtils/DISDefinitions.h>
#include <DIS7/Pdu.h>
#include <DISUtils/RemoteEntity.h>

using namespace DIS;

class EXPORT_MACRO CRemoteSMCC : public CRemoteEntity
{
	es_appear_platform_land::bitmask _entityAppearence;
public:
	CRemoteSMCC(void);
	~CRemoteSMCC(void);

	void FillEntityParameters(const EntityStatePdu& esPdu);

	void Initialize(const EntityStatePdu& esPdu, float appTime) override;

	void HandleEntityStatePDU(const EntityStatePdu& esPdu);
	void HandleDataPDU(const DataPdu& dataPdu);
	void HandleDetonationPDU(const DetonationPdu& detonationPdu) override;
	void HandleFirePDU(const FirePdu& firePdu);
	void HandleSMCCTracksIdentificationData(const DataPdu& dataPdu);
	void HandleElectromagneticEmissionPDU(const ElectromagneticEmissionsPdu& eePdu) {};
	void HandleElectromagneticEmissionJammingPDU(const ElectromagneticEmissionsPdu& eePdu) {};
	void HandleIffPDU(const IFFPdu& iffPdu) {};
	void HandleAttributePdu(const AttributePdu& ttrPdu) {};

	void Update(float deltaTime, float fAppTime);
	void Render();

	int  GetType();
	int	 GetRemoteEntityType();
	LocalHealth GetDamageState();
	es_appear_platform_land::bitmask GetEntityAppearence();

	bool IsFlamming();
	bool IsEntityEmittingSmoke();	
};
