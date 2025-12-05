#pragma once

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace JAMMING_TECHNIQUE { namespace NOISE { namespace REPEATER_NOISE {

					class EXPORT_MACRO RepeaterNoiseSubcategory : public Enumeration {
					public:
						static RepeaterNoiseSubcategory OTHER;
						static RepeaterNoiseSubcategory NARROWBAND_REPEATER_NOISE;
						static RepeaterNoiseSubcategory WIDE_BAND_REPEATER_NOISE;

						/** Returns the string description associated with the enumerated instance with this value.
						* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
						static std::string getDescriptionForValue(int aVal);

						/** Returns the enumerated instance with this value.
						* If there is no enumerated instance for this value, the exception is thrown.     */
						static RepeaterNoiseSubcategory getEnumerationForValue(int aVal) throw(EnumException);

						/** Returns true if there is an enumerated instance for this value, false otherwise. */
						static bool enumerationForValueExists(int aVal);

						typedef hashMap<int, RepeaterNoiseSubcategory*> enumContainer;
						static enumContainer getEnumerations();

						RepeaterNoiseSubcategory& operator=(const int& aVal) throw(EnumException);

					private:
						/** Constructor */
						RepeaterNoiseSubcategory(int value, std::string description);

						static RepeaterNoiseSubcategory* findEnumeration(int aVal);
						static enumContainer enumerations;

					};  /* RepeaterNoiseSubcategory */


				}  /* namespace DIS */
			}
		}
	}
}