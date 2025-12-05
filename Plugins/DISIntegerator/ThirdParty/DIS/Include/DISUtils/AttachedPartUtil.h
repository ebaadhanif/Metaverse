#pragma once

#include <DISUtils/ArticulationParameterRecord.h>
#include <DISEnums/ParameterTypeDesignator.h>
#include <DIS7/VariableParameterRecord.h>
#include <DISEnums/AttachedParts.h>
#include <DIS7/EntityStatePdu.h>
#include <DISUtils/DISDefinitions.h>
#include <vector>
#include <DIS7\msLibMacro.h>

//**********************************//          
//			Attached Part			//
//**********************************//
//			ATTACHED_PART			//
//**********************************//
//**********************************//
//			Attached				//
//**********************************//
//			aircraftChassis(0)		//
//**********************************//
//			LEFT_WING + StationNo	//
//**********************************//
//			EntityType				//
//**********************************//


//**********************************//
//     Articulated Part VP Record	//
//**********************************//
//			ARTICULATED_PART		//
//**********************************//
//			ChangeIndicator			//
//**********************************//
//			LEFT_WING + StationNo	//
//**********************************//
// OTHERFIXEDPOSITIONPARTS+QUANTITY	//
//**********************************//
//**********************************//
//          value of Quantity		//
//**********************************//

namespace DIS
{
	class EXPORT_MACRO CAttachedPart
	{
		//For Attached Part
		//ParameterType consists of Entity Type converted to int
		VariableParameterRecord					_parameter;
		int												_quantity;
		unsigned char									_quantityChangeIndicator;
		std::vector<VariableParameterRecord>		_articulationParaVec;
	public:
		CAttachedPart();
		~CAttachedPart();

		/////////////////////////////////Sending & Receiving//////////////////////////////////

		VariableParameterRecord* GetParameter();
		void Initialize(ENUMS::AttachedParts part, EntityType eType, unsigned char detachIndicator, int stationNo, int quantity);

		static double ConvertEntityTypeToParameterValue(EntityType eType);
		void UpdateDataInPdu(EntityStatePdu& esPdu);
		bool UpdateAttachedParameterRecord(bool isAttached, int quantity);
		bool Compare(ENUMS::AttachedParts part, int stationNo);
		void SetQuantity(int quantity);
		int GetQuantity();
		static ENUMS::AttachedParts GetAttachedPart(int type);

		//////////////////////////////////////////  Sending //////////////////////////////////

		static EntityType ConvertParameterValueToEntityType(double parameterValue);

	private:
		struct EntityType // Defined in order to copy memory
		{
			unsigned char _entityKind;
			unsigned char _domain;
			unsigned char _country[2];
			unsigned char _category;
			unsigned char _subcategory;
			unsigned char _specific;
			unsigned char _extra;
		};

		void UpdateQuantityChangeIndicatorCount();
		unsigned char GetChangeIndicatorCount();

	public:
		//AFISE Specific functions
		static StandardAttachedPart GetAircraftWing(int afiseType, int stationNo);
		static int GetAircraftStationNo(int afiseType, int standardStationNo, int standardAttachPart);
	};
}

