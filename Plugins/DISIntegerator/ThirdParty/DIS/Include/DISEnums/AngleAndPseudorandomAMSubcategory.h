#pragma once

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace JAMMING_TECHNIQUE { namespace DECEPTION_NOISE { namespace ANGLE_PSEUDORANDOM_AM {

					class EXPORT_MACRO AngleAndPseudorandomAMSubcategory : public Enumeration {
					public:
						static AngleAndPseudorandomAMSubcategory OTHER;
						static AngleAndPseudorandomAMSubcategory INVERSE_GAIN_PSEUDORANDOM_AM;
						static AngleAndPseudorandomAMSubcategory PSEUDORANDOM_AM_SSW;

						/** Returns the string description associated with the enumerated instance with this value.
						* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
						static std::string getDescriptionForValue(int aVal);

						/** Returns the enumerated instance with this value.
						* If there is no enumerated instance for this value, the exception is thrown.     */
						static AngleAndPseudorandomAMSubcategory getEnumerationForValue(int aVal) throw(EnumException);

						/** Returns true if there is an enumerated instance for this value, false otherwise. */
						static bool enumerationForValueExists(int aVal);

						typedef hashMap<int, AngleAndPseudorandomAMSubcategory*> enumContainer;
						static enumContainer getEnumerations();

						AngleAndPseudorandomAMSubcategory& operator=(const int& aVal) throw(EnumException);

					private:
						/** Constructor */
						AngleAndPseudorandomAMSubcategory(int value, std::string description);

						static AngleAndPseudorandomAMSubcategory* findEnumeration(int aVal);
						static enumContainer enumerations;

					};  /* AngleAndPseudorandomAMSubcategory */


				}  /* namespace DIS */
			}
		}
	}
}