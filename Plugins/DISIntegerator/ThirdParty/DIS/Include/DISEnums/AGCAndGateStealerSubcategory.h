#pragma once

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace JAMMING_TECHNIQUE { namespace DECEPTION { namespace AGC_GATE_STEALER {

					class EXPORT_MACRO AGCAndGateStealerSubcategory : public Enumeration {
					public:
						static AGCAndGateStealerSubcategory OTHER;
						static AGCAndGateStealerSubcategory AGC_RGPO;
						static AGCAndGateStealerSubcategory AGC_VGPO;
						static AGCAndGateStealerSubcategory AGC_RGPO_VGPO;

						/** Returns the string description associated with the enumerated instance with this value.
						* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
						static std::string getDescriptionForValue(int aVal);

						/** Returns the enumerated instance with this value.
						* If there is no enumerated instance for this value, the exception is thrown.     */
						static AGCAndGateStealerSubcategory getEnumerationForValue(int aVal) throw(EnumException);

						/** Returns true if there is an enumerated instance for this value, false otherwise. */
						static bool enumerationForValueExists(int aVal);

						typedef hashMap<int, AGCAndGateStealerSubcategory*> enumContainer;
						static enumContainer getEnumerations();

						AGCAndGateStealerSubcategory& operator=(const int& aVal) throw(EnumException);

					private:
						/** Constructor */
						AGCAndGateStealerSubcategory(int value, std::string description);

						static AGCAndGateStealerSubcategory* findEnumeration(int aVal);
						static enumContainer enumerations;

					};  /* AGCAndGateStealerSubcategory */


				}  /* namespace DIS */
			}
		}
	}
}