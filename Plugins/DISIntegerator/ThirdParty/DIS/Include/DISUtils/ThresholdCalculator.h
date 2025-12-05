#pragma once
#include <DIS7/EntityID.h>
#include <DIS7/Vector3Double.h>
#include <DIS7/EulerAngles.h>
#include <DIS7\msLibMacro.h>

namespace DIS {
	enum THRESHOLD_MODE
	{
		SENSITIVE_REGION = 3,
		AREA_OF_INTEREST = 2,
		NORMAL = 1,
		OUT_OF_SIGHT = 0,
	};

	class EXPORT_MACRO CThresholdCalculator
	{

	public:
		CThresholdCalculator(void);
		~CThresholdCalculator(void);

		// Checks the threshold w.r.t. position and returns true if meet.
		static bool CheckPositionThreshold(bool haveTrackerEntities, THRESHOLD_MODE& mode, double velocity/*meter per second*/,
			Vector3Double entityLocation, Vector3Double drLocation, double& fLastThresholdModeCheckTime, double fAppTime);
		static THRESHOLD_MODE CheckPositionThresholdMode(Vector3Double entityLocation);

		static float FindAngleDifference(float finalAngleDeg, float initialAngleDeg);
		//Checks the threshold w.r.t. orientation and returns true if meet.
		static bool CheckOrientationThreshold(THRESHOLD_MODE thresholdMode, EulerAngles entityOrientation, EulerAngles drEntityOrientation);

	};
}