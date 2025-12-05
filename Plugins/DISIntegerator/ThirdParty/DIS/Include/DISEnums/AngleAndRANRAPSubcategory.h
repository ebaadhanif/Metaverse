#pragma once

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace JAMMING_TECHNIQUE { namespace DECEPTION { namespace ANGLE_RANRAP {

					class EXPORT_MACRO AngleAndRANRAPSubcategory : public Enumeration {
					public:
						static AngleAndRANRAPSubcategory OTHER;
						static AngleAndRANRAPSubcategory RANRAP_SSW;

						/** Returns the string description associated with the enumerated instance with this value.
						* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
						static std::string getDescriptionForValue(int aVal);

						/** Returns the enumerated instance with this value.
						* If there is no enumerated instance for this value, the exception is thrown.     */
						static AngleAndRANRAPSubcategory getEnumerationForValue(int aVal) throw(EnumException);

						/** Returns true if there is an enumerated instance for this value, false otherwise. */
						static bool enumerationForValueExists(int aVal);

						typedef hashMap<int, AngleAndRANRAPSubcategory*> enumContainer;
						static enumContainer getEnumerations();

						AngleAndRANRAPSubcategory& operator=(const int& aVal) throw(EnumException);

					private:
						/** Constructor */
						AngleAndRANRAPSubcategory(int value, std::string description);

						static AngleAndRANRAPSubcategory* findEnumeration(int aVal);
						static enumContainer enumerations;

					};  /* AngleAndRANRAPSubcategory */


				}  /* namespace DIS */
			}
		}
	}
}