#pragma once
#include <DIS7/EulerAngles.h>
#include <DIS7/JammingTechnique.h>
#include <DIS7/FalseTargetsAttribute.h>
#include <DISUtils/DISDefinitions.h>
#include <DISUtils/Vector2D.h>
#include <bitset>
#include <DIS7\msLibMacro.h>
#include <DISEnums/es_appear_platform_air.h>
#include <DISEnums/es_appear_platform_land.h>
#include <DISEnums/es_appear_cultural.h>
#include <DISEnums/es_appear_sensoremitter.h>
#include <DISEnums/es_appear_expendables.h>
#include <DISEnums/es_appear_lifeform.h>
#include <DISEnums/es_appear_platform_surface.h>
#include <DISEnums/es_appear_munition.h>

namespace DIS
{
	template <typename T>
	int sgn(T val)
	{
		return (T(0) < val) - (val < T(0));
	}

	class EXPORT_MACRO CDISConversions
	{
	public:
		CDISConversions(void);
		~CDISConversions(void);

#pragma region COMMON_CONVERSION_FUNCTIONS_HEADER

		/*******************     COMMON CONVERSION FUNCTIONS START   ********************/

		//******* Conversion to/from Geocentric(ECEF) & Local(App Specific) Location Coordinates Start ********//
		static void ConvertLocalToNEDLocation(LocalFrameInformation frameInformation, DIS::Vector3Double& localPosition);

		static void ConvertNEDToLocalLocation(LocalFrameInformation frameInformation, DIS::Vector3Double&);
		static void ConvertLocalPositionToGeocentricPosition(GeodeticCoordinates  geodeticCoordinates,Vector3Double& geoPosition );

		static Vector3Double ConvertGeocentricPositionToLocalPosition(Vector3Double geoPosition, GeodeticCoordinates& geodeticCoordinates);
		static GeodeticCoordinates ConvertXYToLatLong(Vector3Double localPos);
		static Vector3Double ConvertLatLongToXY(double lat, double lng, double height);

		static Vector3Double ConvertGeocentricPositionToGeodeticPosition(Vector3Double geoPosition);
		//******* Conversion to/from Geocentric(ECEF) & Local(App Specific) Location Coordinates End ********//

		//******* Conversion to/from local yaw, pitch, roll & ECEF psi,theta,phi Orientation Angles Conversion Start ********//

		// Sending Side
		static void ConvertBodyToWorldAngles(BodyAngles bodyAngles, GeodeticCoordinates geodeticCoodinates, EulerAngles& worldAngles);

		/**
		* Gets the Euler Psi value (in radians) from position and Tait-Brayn yaw and pitch angles
		* @param lat Entity's latitude,    IN RADIANS
		* @param lon Entity's longitude,   IN RADIANS
		* @param yaw   ettity's yaw angle (also know as the entity's bearing or heading angle), in radian
		* @param pitch entity's pitch angle, in radian
		* @return the Psi value in radians
		*/
		static double getPsiFromTaitBryanAngles(double lat, double lon, double yaw, double pitch);

		/**
		* Gets the Euler Theta value (in radians) from position and Tait-Brayn yaw and pitch angles
		* @param lat Entity's latitude,    IN RADIANS
		* @param lon Entity's longitude,   IN RADIANS
		* @param yaw   entity's yaw angle (also know as the entity's bearing or heading angle), in radian
		* @param pitch entity's pitch angle, in radian
		* @return the Theta value in radians
		*/
		static double getThetaFromTaitBryanAngles(double lat, double lon, double yaw, double pitch);

		/**
		* Gets the Euler Phi value (in radians) from position and Tait-Brayn yaw, pitch and roll angles
		* @param lat Entity's latitude,    IN RADIANS
		* @param lon Entity's longitude,   IN RADIANS
		* @param yaw yaw angle (also know as the entity's bearing or heading angle), in radian
		* @param pitch entity's pitch angle, in radian
		* @param roll  entity's roll angle (0 is level flight, + roll is clockwise looking out the nose), in radian
		* @return the Phi value in radians
		*/
		static double getPhiFromTaitBryanAngles(double lat, double lon, double yaw, double pitch, double roll);

		// Receiving Side
		static void ConvertWorldtoBodyAngles(unsigned short currentAppType, EulerAngles worldAngles, GeodeticCoordinates geodeticCoordintes, BodyAngles& bodyAngles);
		static void ConvertWorldtoBodyAngles(unsigned short currentAppType, EulerAngles worldAngles, GeodeticCoordinates geodeticCoordintes, BodyAngles& bodyAngles, EulerAngles& bodyEulerAngles);
		/**
		* Gets a radians heading for an entity based on euler angles. All angular values passed in must be in radians.
		* @param lat Entity's latitude,    IN RADIANS
		* @param lon Entity's longitude,   IN RADIANS
		* @param psi Psi angle,            IN RADIANS
		* @param theta Theta angle,        IN RADIANS
		* @return the heading, in radians, with 0 being north, positive angles going clockwise,
		* and negative angles going counterclockwise (i.e., 90 deg is east, -90 is west)
		*  Range is -pi to pi
		*/
		static double getOrientationFromEuler(double lat, double lon, double psi, double theta);

		/**
		* Gets a radians pitch for an entity based on euler angles. All angular values passed in must be in radians.
		* @param lat Entity's latitude,    IN RADIANS
		* @param lon Entity's longitude,   IN RADIANS
		* @param psi Psi angle,            IN RADIANS
		* @param theta Theta angle,        IN RADIANS
		* @return the pitch, in radians, with 0 being level. A negative values is when the entity's
		* nose is pointing downward, positive value is when the entity's nose is pointing upward.
		* Range is -pi/2 to pi/2
		*/
		static double getPitchFromEuler(double lat, double lon, double psi, double theta);

		/**
		* Gets the radians roll for an entity based on euler angles. All angular values passed in must be in radians.
		* @param lat Entity's latitude,    IN RADIANS
		* @param lon Entity's longitude,   IN RADIANS
		* @param psi Psi angle,            IN RADIANS
		* @param theta Theta angle,        IN RADIANS
		* @param phi Phi angle,            IN RADIANS
		* @return the roll, in radians, with 0 being level flight, + roll is clockwise when looking out the front of the entity.
		* Range is -pi to pi
		*/
		static double getRollFromEuler(double lat, double lon, double psi, double theta, double phi);

		//******* Conversion to/from NED yaw, pitch, roll & ECEF psi,theta,phi Orientation Angles Conversion End ********//

		static es_appear_platform_air::bitmask GetEsAppearancePatformAir(unsigned int entityAppear);
		static es_appear_platform_land::bitmask GetEsAppearancePlatformLand(unsigned int entityAppear);
		static es_appear_cultural::bitmask GetEsAppearancePlatformCultural(unsigned int entityAppear);
		static es_appear_sensoremitter::bitmask GetEsAppearancePlatformSensorEmitter(unsigned int entityAppear);
		static es_appear_expendables::bitmask GetEsAppearancePlatformExpendables(unsigned int entityAppear);
		static es_appear_lifeform::bitmask GetEsAppearancePlatformLifeform(unsigned int entityAppear);
		static es_appear_platform_surface::bitmask GetEsAppearancePlatformSurface(unsigned int entityAppear);
		static es_appear_munition::bitmask GetEsAppearancePlatformMunition(unsigned int entityAppear);

		//******* Calculation of World Angular Velocity from World Orientation Angles & Conversion to Body Angular Velocity  Start ********//

		static Vector3Float CalculateWorldAngularVelocity(EulerAngles, EulerAngles, float);
		static Vector3Float ConvertWorldtoBodyAngularVelocity(Vector3Float, double, double);
		static float CalculateAngularVelocityFromEulerAngle(float previousAngle, float currentAngle, float deltaTime);

		static Vector3Float ConvertEntityLocalVelocityToGeocentricVelocity(Vector3Double positionInWorldCoordinates, Vector3Float velocityInWorldCoordinates);

		//******* Calculation of World Angular Velocity from World Orientation Angles & Conversion to Body Angular Velocity  End ********//

		//******* Extraction & Storage of Gs & Airspeed in Knots to/from DR Other Parameters Start ********//

		static void StoreDatainOtherDRParameters(float Gs, short airSpeed, unsigned char(&otherParameters)[15]);
		static void GetDataFromOtherDRParameters(const unsigned char* otherParameters, float& Gs, short& airSpeed);

		//******* Extraction & Storage of Gs & Airspeed in Knots to/from DR Other Parameters End ********//

		static int GetComponentDamageStatusFromLocalHealth(LocalHealth health);
		static LocalHealth GetLocalHealthFromComponentDamageStatus(int componentDamageStatus);

		static void ConvertFalseTargetAttributeToBytes(FalseTargetsAttribute falseTarget, char(&bytes)[FALSE_TARGET_ATTRIBUTE_RECORD_SIZE]);
		static void ConvertBytesToFalseTargetAttribute(const char* bytes, FalseTargetsAttribute& falseTarget);

		static Vector2D Lerp(Vector2D vector1, Vector2D vector2, float multiplier);
		/*******************    FUNCTIONS FOR DATA CONVERSIONS ********************/
		static int ConvertDecimalToOctal(int number);
		static int ConvertOctalToDecimal(int number);
		static int ConvertBinaryToDecimal(std::bitset<12> binaryArray, int size);

		template <typename T>
		static void	CopyValueInCharString(T value, int& index, char* dest)
		{
			int size = sizeof(T);
			memcpy(dest, (void*)& value, size);
			index += size;
		}

		template <typename T>
		static void	CopyValueFromCharString(T& value, int& index, char* src)
		{
			int size = sizeof(T);
			memcpy((void*)& value, (void*)src, size);
			index += size;
		}

		template <typename T>
		static void CopyValueFromCharString(T& value, int& index, const char* src)
		{
			int size = sizeof(T);
			memcpy((void*)& value, (void*)src, size);
			index += size;
		}
		/*******************     COMMON CONVERSION FUNCTIONS END   ********************/

		static unsigned char GetBeamFunctionFromTargetType(TargetType targetType);
		static TargetType GetTargetTypeFromBeamFunction(unsigned char beamFunction);
		static unsigned int GetCharlieHieghtInFeet(Vector3Double position);
#pragma endregion COMMON_CONVERSION_FUNCTIONS_HEADER
	};
}


