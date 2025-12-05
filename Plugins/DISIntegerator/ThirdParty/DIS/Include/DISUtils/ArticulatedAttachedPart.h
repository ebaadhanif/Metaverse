#pragma once

#include <DISUtils/ArticulationParameterRecord.h>
#include <DIS7/VariableParameterRecord.h>
#include <DISEnums/ParameterTypeDesignator.h>
#include <DIS7/VariableParameterRecord.h>
#include <DIS7/EntityType.h>
#include <DIS7/EntityStatePdu.h>
#include <DIS7\msLibMacro.h>

namespace DIS
{
	class EXPORT_MACRO CArticulatedAttachedPart
	{
		//For Attached Part
		//ParameterType consists of Entity Type converted to int
		VariableParameterRecord	_parameter;
		std::vector<CArticulationParameterRecord> _vecRecords;

	public:
		CArticulatedAttachedPart();
		~CArticulatedAttachedPart();

		VariableParameterRecord* GetParameter();

		void UpdateAttachedParameterRecord(ENUMS::ArticulatedPartsOffsetNumber recordType, double value);

		void UpdateDataInPdu(EntityStatePdu& esPdu);

		static double ConvertEntityTypeToParameterValue(EntityType eType);
		static EntityType ConvertParameterValueToEntityType(double parameterValue);

	private:
		struct EntityType
		{
			unsigned char _entityKind;
			unsigned char _domain;
			unsigned char _country[2];
			unsigned char _category;
			unsigned char _subcategory;
			unsigned char _specific;
			unsigned char _extra;
		};
	};
}
