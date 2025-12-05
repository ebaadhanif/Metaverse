#pragma once

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace JAMMING_TECHNIQUE { namespace DECEPTION_NOISE { namespace ANGLE_NOISE {

					class EXPORT_MACRO AngleAndNoiseSubcategory : public Enumeration {
					public:
						static AngleAndNoiseSubcategory OTHER;
						static AngleAndNoiseSubcategory ANDGLE_AND_BARRAGE;

						/** Returns the string description associated with the enumerated instance with this value.
						* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
						static std::string getDescriptionForValue(int aVal);

						/** Returns the enumerated instance with this value.
						* If there is no enumerated instance for this value, the exception is thrown.     */
						static AngleAndNoiseSubcategory getEnumerationForValue(int aVal) throw(EnumException);

						/** Returns true if there is an enumerated instance for this value, false otherwise. */
						static bool enumerationForValueExists(int aVal);

						typedef hashMap<int, AngleAndNoiseSubcategory*> enumContainer;
						static enumContainer getEnumerations();

						AngleAndNoiseSubcategory& operator=(const int& aVal) throw(EnumException);

					private:
						/** Constructor */
						AngleAndNoiseSubcategory(int value, std::string description);

						static AngleAndNoiseSubcategory* findEnumeration(int aVal);
						static enumContainer enumerations;

					};  /* AngleAndNoiseSubcategory */


				}  /* namespace DIS */
			}
		}
	}
}