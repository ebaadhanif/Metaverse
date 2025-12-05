#pragma once
#include <DISUtils/RemoteEntity.h>
#include <DISUtils/IFFSystem.h>
#include <DISEnums/es_appear_platform_surface.h>

using namespace DIS;

class EXPORT_MACRO CRemoteSurfaceEntity : public CRemoteEntity
{
private:
	es_appear_platform_surface::bitmask _entityAppearence;

public:
	CRemoteSurfaceEntity(void);
	~CRemoteSurfaceEntity(void);

	void Initialize(const EntityStatePdu& esPdu, float appTime) override;

	void FillEntityParameters(const EntityStatePdu& esPdu);
	void FillEntityParameters(const AttributePdu& attrPdu);

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
	CIFFSystem* GetIFFSystemObj() { return &_iffSystem; }
	int	 GetRemoteEntityType();

	bool IsFlamming();
	bool IsEntityEmittingSmoke();
	LocalHealth GetDamageState();
	es_appear_platform_surface::bitmask GetEntityAppearence();

};
