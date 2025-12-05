#pragma once

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace JAMMING_TECHNIQUE { namespace NOISE { namespace SWEPT_NOISE {

					class EXPORT_MACRO SweptNoiseSubcategory : public Enumeration {
					public:
						static SweptNoiseSubcategory OTHER;
						static SweptNoiseSubcategory FREQUENCY_SWEPT;
						static SweptNoiseSubcategory SWEPT_AM;

						/** Returns the string description associated with the enumerated instance with this value.
						* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
						static std::string getDescriptionForValue(int aVal);

						/** Returns the enumerated instance with this value.
						* If there is no enumerated instance for this value, the exception is thrown.     */
						static SweptNoiseSubcategory getEnumerationForValue(int aVal) throw(EnumException);

						/** Returns true if there is an enumerated instance for this value, false otherwise. */
						static bool enumerationForValueExists(int aVal);

						typedef hashMap<int, SweptNoiseSubcategory*> enumContainer;
						static enumContainer getEnumerations();

						SweptNoiseSubcategory& operator=(const int& aVal) throw(EnumException);

					private:
						/** Constructor */
						SweptNoiseSubcategory(int value, std::string description);

						static SweptNoiseSubcategory* findEnumeration(int aVal);
						static enumContainer enumerations;

					};  /* SweptNoiseSubcategory */


				}  /* namespace DIS */
			}
		}
	}
}