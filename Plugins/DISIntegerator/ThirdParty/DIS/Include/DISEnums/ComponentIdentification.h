#pragma once

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS {
	namespace ENUMS {
		class EXPORT_MACRO ComponentIdentification : public Enumeration {
		public:
			static ComponentIdentification ENTITY_CENTER;
			static ComponentIdentification ENTITY_STRUCTURE;
			static ComponentIdentification CONTROL_SYSTEM;
			static ComponentIdentification CONTROL_SURFACE;
			static ComponentIdentification ENGINE_OR_PROPULSION_SYSTEM;
			static ComponentIdentification CREW_MEMEBER;
			static ComponentIdentification FUSE;
			static ComponentIdentification ACQUISITION_SENSOR;
			static ComponentIdentification TRACKING_SENSOR;
			static ComponentIdentification FUEL_TANK_OR_SOLID_ROCKET_MOTOR;

			/** Returns the string description associated with the enumerated instance with this value.
			* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
			static std::string getDescriptionForValue(int aVal);

			/** Returns the enumerated instance with this value.
			* If there is no enumerated instance for this value, the exception is thrown.     */
			static ComponentIdentification getEnumerationForValue(int aVal) throw(EnumException);

			/** Returns true if there is an enumerated instance for this value, false otherwise. */
			static bool enumerationForValueExists(int aVal);

			typedef hashMap<int, ComponentIdentification*> enumContainer;
			static enumContainer getEnumerations();

			ComponentIdentification& operator=(const int& aVal) throw(EnumException);

		private:
			/** Constructor */
			ComponentIdentification(int value, std::string description);

			static ComponentIdentification* findEnumeration(int aVal);
			static enumContainer enumerations;

		};  /* ComponentIdentification */

	}
} /* namespace DIS */