#pragma once

#include <DISEnums/ArticulatedPartsOffsetNumber.h>
#include <DISEnums/ArticulatedPartsIndexNumber.h>
#include <DISEnums/StateChangeUpdateIndicator.h>
#include <DISEnums/DetachedIndicator.h>
#include <DIS7\msLibMacro.h>

namespace DIS
{
	class EXPORT_MACRO CArticulationParameterRecord
	{
		//ArticulatedPartsOffsetNumber.h in DIS ENUMS - store value in _type
		//static ArticulatedPartsOffsetNumber NOT_SPECIFIED;
		//static ArticulatedPartsOffsetNumber POSITION;
		//static ArticulatedPartsOffsetNumber POSITION_RATE;
		//static ArticulatedPartsOffsetNumber EXTENSION;
		//static ArticulatedPartsOffsetNumber EXTENSION_RATE;
		//static ArticulatedPartsOffsetNumber X;
		//static ArticulatedPartsOffsetNumber X_RATE;
		//static ArticulatedPartsOffsetNumber Y;
		//static ArticulatedPartsOffsetNumber Y_RATE;
		//static ArticulatedPartsOffsetNumber Z;
		//static ArticulatedPartsOffsetNumber Z_RATE;
		//static ArticulatedPartsOffsetNumber AZIMUTH;
		//static ArticulatedPartsOffsetNumber AZIMUTH_RATE;
		//static ArticulatedPartsOffsetNumber ELEVATION;
		//static ArticulatedPartsOffsetNumber ELEVATION_RATE;
		//static ArticulatedPartsOffsetNumber ROTATION;
		//static ArticulatedPartsOffsetNumber ROTATION_RATE;
		int													_type;
		double												_value;
		//Change indicator and Attach/Detach will be used alternatively
		//static StateChangeUpdateIndicator STATE_UPDATE;
		//static StateChangeUpdateIndicator CHANGED_DATA_UPDATE;
		unsigned char										_changeIndicator;		//It will be used for articulated part
		//static DetachedIndicator ATTACHED;
		//static DetachedIndicator DETACHED;
		unsigned char										_detachIndicator;			//It will be used for attached part

	public:
		CArticulationParameterRecord();
		~CArticulationParameterRecord();

		ENUMS::ArticulatedPartsOffsetNumber GetType();
		void SetType(ENUMS::ArticulatedPartsOffsetNumber type);


		int Type();
		void SetType(int type);

		double GetValue();
		void SetValue(double value);

		void UpdateChangeIndicatorCount();
		unsigned char GetChangeIndicatorCount();
		void SetChangeIndicator(ENUMS::StateChangeUpdateIndicator changeIndicator);
		void SetChangeIndicator(unsigned char changeIndicatorCount);
		ENUMS::StateChangeUpdateIndicator GetChangeIndicator();

		void SetDetachIndicator(ENUMS::DetachedIndicator detachIndicator);
		ENUMS::DetachedIndicator GetDetachIndicator();
	};
}