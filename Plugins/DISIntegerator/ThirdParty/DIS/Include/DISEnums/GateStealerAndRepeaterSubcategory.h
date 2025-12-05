#pragma once

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace JAMMING_TECHNIQUE { namespace DECEPTION { namespace GATE_STEALER_REPEATER {

					class EXPORT_MACRO GateStealerAndRepeaterSubcategory : public Enumeration {
					public:
						static GateStealerAndRepeaterSubcategory OTHER;
						static GateStealerAndRepeaterSubcategory RSAM_VGPO;

						/** Returns the string description associated with the enumerated instance with this value.
						* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
						static std::string getDescriptionForValue(int aVal);

						/** Returns the enumerated instance with this value.
						* If there is no enumerated instance for this value, the exception is thrown.     */
						static GateStealerAndRepeaterSubcategory getEnumerationForValue(int aVal) throw(EnumException);

						/** Returns true if there is an enumerated instance for this value, false otherwise. */
						static bool enumerationForValueExists(int aVal);

						typedef hashMap<int, GateStealerAndRepeaterSubcategory*> enumContainer;
						static enumContainer getEnumerations();

						GateStealerAndRepeaterSubcategory& operator=(const int& aVal) throw(EnumException);

					private:
						/** Constructor */
						GateStealerAndRepeaterSubcategory(int value, std::string description);

						static GateStealerAndRepeaterSubcategory* findEnumeration(int aVal);
						static enumContainer enumerations;

					};  /* GateStealerAndRepeaterSubcategory */


				}  /* namespace DIS */
			}
		}
	}
}