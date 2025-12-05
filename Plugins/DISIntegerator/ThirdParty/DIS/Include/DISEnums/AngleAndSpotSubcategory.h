#pragma once

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace JAMMING_TECHNIQUE { namespace DECEPTION_NOISE { namespace ANGLE_SPOT {

					class EXPORT_MACRO AngleAndSpotSubcategory : public Enumeration {
					public:
						static AngleAndSpotSubcategory OTHER;
						static AngleAndSpotSubcategory INVERSE_GAIN_LOW_LEVEL_NOISE;
						static AngleAndSpotSubcategory INVERSE_GAIN_SPOT_NOISE;
						static AngleAndSpotSubcategory SPOT_SSW;

						/** Returns the string description associated with the enumerated instance with this value.
						* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
						static std::string getDescriptionForValue(int aVal);

						/** Returns the enumerated instance with this value.
						* If there is no enumerated instance for this value, the exception is thrown.     */
						static AngleAndSpotSubcategory getEnumerationForValue(int aVal) throw(EnumException);

						/** Returns true if there is an enumerated instance for this value, false otherwise. */
						static bool enumerationForValueExists(int aVal);

						typedef hashMap<int, AngleAndSpotSubcategory*> enumContainer;
						static enumContainer getEnumerations();

						AngleAndSpotSubcategory& operator=(const int& aVal) throw(EnumException);

					private:
						/** Constructor */
						AngleAndSpotSubcategory(int value, std::string description);

						static AngleAndSpotSubcategory* findEnumeration(int aVal);
						static enumContainer enumerations;

					};  /* AngleAndSpotSubcategory */


				}  /* namespace DIS */
			}
		}
	}
}