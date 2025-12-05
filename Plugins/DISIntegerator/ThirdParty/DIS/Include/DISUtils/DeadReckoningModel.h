#pragma once

#include <DISUtils/DRAlgorithm.h>
#include <DISUtils/DISDefinitions.h>
#include <DISUtils/ThresholdCalculator.h>
#include <DIS7\EntityID.h>
#include <DISUtils/FactoryDrAlgorithm.h>
#include <list>
#include <DIS7/Vector3Double.h>
#include <DIS7\msLibMacro.h>

namespace DIS
{
	#define YAW_VELOCITY_HISTORY_COUNT 5


	class EXPORT_MACRO CDeadReckoningModel
	{
	private:

		//How may times per second to update this entity's positon
		int					_iFPS;

		//How far to change the location/orientation per update
		double				_fChangeDelta;

		//The time elapsed for the next dead reckoning render
		double				_fTimeRenderElapsed;

		//The last time for the state update
		double				_fTimeStateUpdate;

		//The delta time for the state update or it can be the time between two received messages
		double				_fTimeStateUpdateDelta;

		//The time for controlling of the lerp method
		double				_fTimeLerp;

		//The total time from start, of entity which contains this model
		double				_fEntityTime;
		bool				_isFrozen{ false };
		// The time for last threshold mode update time 
		// This time is used for induce some delay in threshold mode update time so that application
		// can have more time for other things when there are large number of entities
		double							_fTimeLastThresholdModeCheck;

		//The dead reckoning algorithm number
		int								_iSelectedDRAlgo;

		DEAD_RECKONING_STEP_MODE		_deadRecokingStepMode;

		//The dead reckoning algorithm object
		CDRAlgorithm* _deadReckoningAlgorithm{ nullptr };

		//Currently selected threshold mode of the entity
		THRESHOLD_MODE					_currentThresholdMode;

		//The dead reckoning factory pattren object
		CFactoryDrAlgorithm				_factoryDrAlgo;

		//The dead reckoning ownership mode (Owner, Remote)
		DR_CURRENT_OWNERSHIP_MODE		_drCurrentOwnership;

		//The current entity movement phase (Interpolation, Extrapolation)
		DR_ENTITY_MOVEMENT_PHASE		_drMovementPhase;

		//Control point for controlling the spline curve fitting
		Vector3Double				_splineControlPoint;

		bool							_isFrozenStateChanged{ true };

		bool							_bisDeadReckoningEnabled{ true };

	public:

		//Predicted point on the reception of Entity state so that we can steer the entity to that point
		Vector3Double				_predictedPoint;

		//Control point for controlling the bezier curve fitting
		Vector3Double				_controlPoint;

		//Start point when interpolation starts
		Vector3Double				_lerpStartPoint;

		CDeadReckoningModel(void);
		CDeadReckoningModel(int drAlgo);
		~CDeadReckoningModel(void);

		bool Render(double deltaTime, double appTime, unsigned short applicationType);

		THRESHOLD_MODE	GetCurrentThresholdMode() { return _currentThresholdMode; }
		void SetCurrentThresholdMode(THRESHOLD_MODE thresholdMode) { this->_currentThresholdMode = thresholdMode; }

		void SetDRAlgorithm(int drAlgo);

		//Initialize the dead reckoning model 
		void Initialize(int drAlgo,
			Vector3Double entityLocation,
			Vector3Float entityLinearVelocity,
			EulerAngles entityOrientation,
			DR_CURRENT_OWNERSHIP_MODE drMode,
			DEAD_RECKONING_STEP_MODE drStepMode,
			bool isDeadReckoningEnabled,
			int fps, Vector3Float entityAngularVelocity = Vector3Float(),
			Vector3Float entityLinearAcceleration = Vector3Float());

		//Setter Functions
		void SetFramesPerSecond(int fps);
		void SetEntityLocation(Vector3Double location);
		void SetEntityLinearVelocity(Vector3Float linearVelocity);
		void SetEntityLinearAcceleration(Vector3Float linearAcceleration);
		void SetEntityOrientation(EulerAngles orientation);

		//Getter Functions
		Vector3Double GetEntityLocation(int appType, GeodeticCoordinates& geodeticCoordinates);
		Vector3Double GetEntityGeocentricLocation();
		Vector3Float GetEntityLinearVelocity();
		Vector3Float GetEntityAngularVelocity();
		Vector3Float GetEntityLinearAcceleration();
		EulerAngles GetEntityOrientation(GeodeticCoordinates geodeticPosition);

		bool HasDeadReckoningAlgorithm();

		double GetChangeDelta() { return _fChangeDelta; }

		//Update the state of the dead reckoning
		void UpdateModelState(
			Vector3Double position,
			Vector3Float linearVelocity,
			EulerAngles  orientation,
			bool isDeadReckoningEnabled = true,
			int fps = 5,
			Vector3Float linearAcceleration = Vector3Float(),
			Vector3Float angularVelocity = Vector3Float(), bool isFrozen = false);

		//Check thresolds with DR model. Returns true if exceeds the thresholds and also sets new entity values to dr algo values.
		bool CheckThresholds(
			double fAppTime,
			double entitySpeed/*Meters Per Second*/,
			Vector3Double entityLocation,
			Vector3Float entityLinearVelocity,
			Vector3Float entityLinearAcceleration,
			EulerAngles entityOrientation,
			Vector3Float entityAngularVelocity,
			bool haveTrackerEntities,
			bool& isPositionOrOrientationThreshold);

		void MarshalDeadReckoningModel(DataStream& dataStream);
		void UnMarshalDeadReckoningModel(DataStream& dataStream);
		CDRAlgorithm* GetDeadReckoningAlgorithmPtr() { return _deadReckoningAlgorithm; };

		//Predict the next angle with respect to time and minAngle and maxAngle ...
		double LerpAngleRadian(double start, double end, double minAngle, double maxAngle, double elapsedTime);
		//Returns the radian angle on base of last two orientation update ..
		double GetValidAngleRadian(double angle, double minAngle, double maxAngle);

	};
}