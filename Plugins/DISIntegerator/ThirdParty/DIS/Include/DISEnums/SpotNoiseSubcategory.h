#pragma once

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace JAMMING_TECHNIQUE { namespace NOISE { namespace SPOT_NOISE {

					class EXPORT_MACRO SpotNoiseSubcategory : public Enumeration {
					public:
						static SpotNoiseSubcategory OTHER;
						static SpotNoiseSubcategory AUTOMATIC_SPOT_NOISE;
						static SpotNoiseSubcategory BLINKING_SPOT_NOISE;
						static SpotNoiseSubcategory BURST_SPOT_NOISE;
						static SpotNoiseSubcategory DOPPLER_SPOT_NOISE;
						static SpotNoiseSubcategory SKIRT_FREQUENCY;

						/** Returns the string description associated with the enumerated instance with this value.
						* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
						static std::string getDescriptionForValue(int aVal);

						/** Returns the enumerated instance with this value.
						* If there is no enumerated instance for this value, the exception is thrown.     */
						static SpotNoiseSubcategory getEnumerationForValue(int aVal) throw(EnumException);

						/** Returns true if there is an enumerated instance for this value, false otherwise. */
						static bool enumerationForValueExists(int aVal);

						typedef hashMap<int, SpotNoiseSubcategory*> enumContainer;
						static enumContainer getEnumerations();

						SpotNoiseSubcategory& operator=(const int& aVal) throw(EnumException);

					private:
						/** Constructor */
						SpotNoiseSubcategory(int value, std::string description);

						static SpotNoiseSubcategory* findEnumeration(int aVal);
						static enumContainer enumerations;

					};  /* SpotNoiseSubcategory */


				}  /* namespace DIS */
			}
		}
	}
}