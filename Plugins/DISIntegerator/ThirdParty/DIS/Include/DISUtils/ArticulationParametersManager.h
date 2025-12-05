#pragma once
#include <DISEnums/ArticulatedPartsIndexNumber.h>
#include <DISEnums/ArticulatedPartsOffsetNumber.h>
#include <DISEnums/AttachedParts.h>
#include <DISEnums/ParameterTypeDesignator.h>
#include <DISEnums/StateChangeUpdateIndicator.h>
#include <DISUtils/ArticulatedPart.h>
#include <DISUtils/AttachedPartUtil.h>
#include <DISUtils/DISEnumerationsManager.h>
#include <DISUtils/DISDefinitions.h>
#include <vector>
#include <DIS7\msLibMacro.h>

namespace DIS
{
	class EXPORT_MACRO CArticulationParametersManager
	{
	private:
		std::vector<CArticulatedPart>					_vecArticulationParameters;
		std::vector<CAttachedPart>                      _vecAttachedParameters;
		bool											_bIsArticulationParametersUpdated;
		bool											_bIsReceived;

		EntityOwnershipType								_eEntityOwnership;
		int												_afiseEntityType{};			//AFISE Entity type owning this manager

	public:
		CArticulationParametersManager();
		~CArticulationParametersManager();

		void SetEntityOwnership(EntityOwnershipType ownership, int afiseEntityType);
		EntityOwnershipType GetEntityOwnership() { return _eEntityOwnership; }
		std::vector<AttachedPartData>							_vecAttachedParts;

		/////////////////////////////////////////////Sending & Receiving/////////////////////////////////
	private:
		//ParameterType consists of Type Class + Metric Type = ArticulatedPartsIndexNumber + ArticulatedPartsOffsetNumber
		void AddArticulationParameter(ENUMS::ArticulatedPartsIndexNumber typeClass, ENUMS::ArticulatedPartsOffsetNumber metricType, double value, unsigned char changeIndicator/*Default if no change indicator available*/);
		void AddAttachedParameter(ENUMS::AttachedParts part, EntityType eType, bool detachIndicator, int stationNo, int quantity);

	public:
		//This function is used to attach/detach an attach part with the entity, stationNo must start from 0 on the part
		void UpdateAttachedParameter(ENUMS::AttachedParts part, int afiseEntityType, int stationNo, bool detachedIndicator, int quantity = 1);
		void UpdateArticualtionParameter(ENUMS::ArticulatedPartsIndexNumber typeClass, ENUMS::ArticulatedPartsOffsetNumber metricType, double value, unsigned char changeIndicator = 0/*Default if no change indicator available*/);

		/////////////////////////////////////////////Sending////////////////////////////////////////////

	public:
		bool UpdateArticulationParametersInPdu(EntityStatePdu& esPdu);
		//ParameterType consists of Type Class + Metric Type = ArticulatedPartsIndexNumber + ArticulatedPartsOffsetNumber
		void RemoveArticulationParameter(ENUMS::ArticulatedPartsIndexNumber typeClass, ENUMS::ArticulatedPartsOffsetNumber metricType);		//Changed Later...
		void RemoveAttachedParamters(ENUMS::AttachedParts parts, int stationNo);
		void RemoveDetachedParts();
		bool GetIsArticulationParametersUpdated() { return _bIsArticulationParametersUpdated; }
		void SetISArticulationParametersUpdated(bool isUpdated) { _bIsArticulationParametersUpdated = isUpdated; }
		void SetIsReceived(bool isRec) { _bIsReceived = isRec; }
		bool GetIsReceived() { return _bIsReceived; }
		void ClearAttachedParts();
		void ClearArticulatedParts();
		void ClearAllArticulationParameters();

		/////////////////////////////////////////////Receiving////////////////////////////////////////////

	private:
		void ExtractArticulatedPart(VariableParameterRecord articulationParameter);
		void ExtractAttachedParameter(VariableParameterRecord articulationParameter);
		void UpdateAttachedPartQuantity(VariableParameterRecord articulationParameter);
	public:
		void ExtractDatafromPdu(const EntityStatePdu& esPdu);
		bool GetArticulationParameterValue(ENUMS::ArticulatedPartsIndexNumber typeClass, ENUMS::ArticulatedPartsOffsetNumber metricType, double& paramterValue);
	};
}

