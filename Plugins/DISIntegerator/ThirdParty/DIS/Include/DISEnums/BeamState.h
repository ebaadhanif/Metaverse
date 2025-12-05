#pragma once

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS {
	namespace ENUMS {

		class EXPORT_MACRO BeamState : public Enumeration {
		public:
			static BeamState ACTIVE;
			static BeamState DEACTIVATED;

			/** Returns the string description associated with the enumerated instance with this value.
			* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
			static std::string getDescriptionForValue(int aVal);

			/** Returns the enumerated instance with this value.
			* If there is no enumerated instance for this value, the exception is thrown.     */
			static BeamState getEnumerationForValue(int aVal) throw(EnumException);

			/** Returns true if there is an enumerated instance for this value, false otherwise. */
			static bool enumerationForValueExists(int aVal);

			typedef hashMap<int, BeamState*> enumContainer;
			static enumContainer getEnumerations();

			BeamState& operator=(const int& aVal) throw(EnumException);

		private:
			/** Constructor */
			BeamState(int value, std::string description);

			static BeamState* findEnumeration(int aVal);
			static enumContainer enumerations;

		};  /* BeamState */


	}  /* namespace DIS */
}

