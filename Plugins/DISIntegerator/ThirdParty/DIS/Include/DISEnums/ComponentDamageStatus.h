#pragma once

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS {
	namespace ENUMS {
		class EXPORT_MACRO ComponentDamageStatus : public Enumeration {
		public:
			static ComponentDamageStatus NO_DAMAGE;
			static ComponentDamageStatus MINOR_DAMAGE;
			static ComponentDamageStatus MEDIUM_DAMAGE;
			static ComponentDamageStatus MAJOR_DAMAGE;
			static ComponentDamageStatus DESTROYED;

			/** Returns the string description associated with the enumerated instance with this value.
			* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
			static std::string getDescriptionForValue(int aVal);

			/** Returns the enumerated instance with this value.
			* If there is no enumerated instance for this value, the exception is thrown.     */
			static ComponentDamageStatus getEnumerationForValue(int aVal) throw(EnumException);

			/** Returns true if there is an enumerated instance for this value, false otherwise. */
			static bool enumerationForValueExists(int aVal);

			typedef hashMap<int, ComponentDamageStatus*> enumContainer;
			static enumContainer getEnumerations();

			ComponentDamageStatus& operator=(const int& aVal) throw(EnumException);

		private:
			/** Constructor */
			ComponentDamageStatus(int value, std::string description);

			static ComponentDamageStatus* findEnumeration(int aVal);
			static enumContainer enumerations;

		};  /* ComponentDamageStatus */

	}
} /* namespace DIS */