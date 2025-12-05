#pragma once

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS {
	namespace ENUMS {

		class EXPORT_MACRO DeadReckoningParametersType : public Enumeration {
		public:
			static DeadReckoningParametersType NONE;
			static DeadReckoningParametersType LOCAL_EULER_ANGLES_YAW_PITCH_ROLL;
			static DeadReckoningParametersType WORLD_ORIENTATION_QUATERNION;

			/** Returns the string description associated with the enumerated instance with this value.
			* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
			static std::string getDescriptionForValue(int aVal);

			/** Returns the enumerated instance with this value.
			* If there is no enumerated instance for this value, the exception is thrown.     */
			static DeadReckoningParametersType getEnumerationForValue(int aVal) throw(EnumException);

			/** Returns true if there is an enumerated instance for this value, false otherwise. */
			static bool enumerationForValueExists(int aVal);

			typedef hashMap<int, DeadReckoningParametersType*> enumContainer;
			static enumContainer getEnumerations();

			DeadReckoningParametersType& operator=(const int& aVal) throw(EnumException);

		private:
			/** Constructor */
			DeadReckoningParametersType(int value, std::string description);

			static DeadReckoningParametersType* findEnumeration(int aVal);
			static enumContainer enumerations;

		};  /* BeamState */


	}  /* namespace DIS */
}

