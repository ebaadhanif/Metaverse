#pragma once

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS {
	namespace ENUMS {

		class EXPORT_MACRO EEAttributeStateIndicator : public Enumeration {
		public:
			static EEAttributeStateIndicator HEARTBEAT_UPDATE;
			static EEAttributeStateIndicator CHANGED_DATA;
			static EEAttributeStateIndicator HAS_CEASED;


			/** Returns the string description associated with the enumerated instance with this value.
			* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
			static std::string getDescriptionForValue(int aVal);

			/** Returns the enumerated instance with this value.
			* If there is no enumerated instance for this value, the exception is thrown.     */
			static EEAttributeStateIndicator getEnumerationForValue(int aVal) throw(EnumException);

			/** Returns true if there is an enumerated instance for this value, false otherwise. */
			static bool enumerationForValueExists(int aVal);

			typedef hashMap<int, EEAttributeStateIndicator*> enumContainer;
			static enumContainer getEnumerations();

			EEAttributeStateIndicator& operator=(const int& aVal) throw(EnumException);

		private:
			/** Constructor */
			EEAttributeStateIndicator(int value, std::string description);

			static EEAttributeStateIndicator* findEnumeration(int aVal);
			static enumContainer enumerations;

		};  /* EEAttributeStateIndicator */


	}  /* namespace DIS */
}
