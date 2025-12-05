#pragma once

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS {
	namespace ENUMS {
		class EXPORT_MACRO StateUpdateFlag : public Enumeration {
		public:
			static StateUpdateFlag UPDATE_DUE_TO_HEARTBEAT_TIMER;
			static StateUpdateFlag STATE_CHANGE;

			/** Returns the string description associated with the enumerated instance with this value.
			* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
			static std::string getDescriptionForValue(int aVal);

			/** Returns the enumerated instance with this value.
			* If there is no enumerated instance for this value, the exception is thrown.     */
			static StateUpdateFlag getEnumerationForValue(int aVal) throw(EnumException);

			/** Returns true if there is an enumerated instance for this value, false otherwise. */
			static bool enumerationForValueExists(int aVal);

			typedef hashMap<int, StateUpdateFlag*> enumContainer;
			static enumContainer getEnumerations();

			StateUpdateFlag& operator=(const int& aVal) throw(EnumException);

		private:
			/** Constructor */
			StateUpdateFlag(int value, std::string description);

			static StateUpdateFlag* findEnumeration(int aVal);
			static enumContainer enumerations;

		};  /* StateUpdateFlag */

	}
} /* namespace DIS */