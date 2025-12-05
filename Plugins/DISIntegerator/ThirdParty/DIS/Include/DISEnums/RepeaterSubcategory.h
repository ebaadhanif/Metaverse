#pragma once

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace JAMMING_TECHNIQUE { namespace DECEPTION { namespace REPEATER {

					class EXPORT_MACRO RepeaterSubcategory : public Enumeration {
					public:
						static RepeaterSubcategory OTHER;
						static RepeaterSubcategory CONTINUOUS_WAVE_REPEATER;
						static RepeaterSubcategory REPEATER_NOISE;
						static RepeaterSubcategory MULTIPLE_FREQUENCY_REPEATER;
						static RepeaterSubcategory NARROW_BAND_REPEATER_NOISE;
						static RepeaterSubcategory RANDOM_DOPPLER;
						static RepeaterSubcategory REPEATER_DIGITAL_RADIO_FREQUENCY_MEMORY;
						static RepeaterSubcategory REPEATER_SWEPT_AMPLITUDE_MODULATION;

						/** Returns the string description associated with the enumerated instance with this value.
						* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
						static std::string getDescriptionForValue(int aVal);

						/** Returns the enumerated instance with this value.
						* If there is no enumerated instance for this value, the exception is thrown.     */
						static RepeaterSubcategory getEnumerationForValue(int aVal) throw(EnumException);

						/** Returns true if there is an enumerated instance for this value, false otherwise. */
						static bool enumerationForValueExists(int aVal);

						typedef hashMap<int, RepeaterSubcategory*> enumContainer;
						static enumContainer getEnumerations();

						RepeaterSubcategory& operator=(const int& aVal) throw(EnumException);

					private:
						/** Constructor */
						RepeaterSubcategory(int value, std::string description);

						static RepeaterSubcategory* findEnumeration(int aVal);
						static enumContainer enumerations;

					};  /* RepeaterSubcategory */


				}  /* namespace DIS */
			}
		}
	}
}