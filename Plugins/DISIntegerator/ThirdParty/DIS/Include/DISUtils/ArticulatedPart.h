#pragma once

#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS 1

#include <DISUtils/ArticulationParameterRecord.h>
#include <DISEnums/ArticulatedPartsOffsetNumber.h>
#include <DISEnums/ParameterTypeDesignator.h>
#include <DIS7/VariableParameterRecord.h>
#include <DIS7/EntityStatePdu.h>
#include <DIS7\msLibMacro.h>

namespace DIS
{
	class EXPORT_MACRO CArticulatedPart
	{
		//For Articulation Parameter -
		//ParameterType consists of Type Class + Metric Type = ArticulatedPartsIndexNumber + ArticulatedPartsOffsetNumber
		VariableParameterRecord				_parameter;
	public:
		CArticulatedPart();
		~CArticulatedPart();

		//////////////////////////////////Sending & Receiving/////////////////////////////////////

		VariableParameterRecord* GetParameter();
		void Initialize(ENUMS::ArticulatedPartsIndexNumber typeClass,
			ENUMS::ArticulatedPartsOffsetNumber metricType, double value, unsigned char changeIndicator, bool isReceivingEnd);
		bool Compare(ENUMS::ArticulatedPartsIndexNumber typeClass, ENUMS::ArticulatedPartsOffsetNumber metricType);
		void Update(double value, unsigned char changeIndicator, bool isReceivingEnd);

		////////////////////////////////////////Sending///////////////////////////////////////////

		void UpdateChangeIndicator();
		void UpdateDataInPdu(EntityStatePdu& esPdu);
		static int ExtractIndexNumber(int parameterType);
		static int ExtractOffSetNumber(int parameterType, int iTypeMetric);
		static ENUMS::ArticulatedPartsIndexNumber getArticulatedPartIndexNumber(int iTypeClass);
		static ENUMS::ArticulatedPartsOffsetNumber getArticulatedPartOffSetNumber(int iTypeMetric);
	};
}