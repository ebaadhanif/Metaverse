#pragma once

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace JAMMING_TECHNIQUE { namespace NOISE { namespace RANGE_BIN_MASKING {

					class EXPORT_MACRO RangeBinMaskingSubcategory : public Enumeration {
					public:
						static RangeBinMaskingSubcategory OTHER;
						static RangeBinMaskingSubcategory RANGE_BIN_MASKING_VELOCITY_BIN_MASKING;

						/** Returns the string description associated with the enumerated instance with this value.
						* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
						static std::string getDescriptionForValue(int aVal);

						/** Returns the enumerated instance with this value.
						* If there is no enumerated instance for this value, the exception is thrown.     */
						static RangeBinMaskingSubcategory getEnumerationForValue(int aVal) throw(EnumException);

						/** Returns true if there is an enumerated instance for this value, false otherwise. */
						static bool enumerationForValueExists(int aVal);

						typedef hashMap<int, RangeBinMaskingSubcategory*> enumContainer;
						static enumContainer getEnumerations();

						RangeBinMaskingSubcategory& operator=(const int& aVal) throw(EnumException);

					private:
						/** Constructor */
						RangeBinMaskingSubcategory(int value, std::string description);

						static RangeBinMaskingSubcategory* findEnumeration(int aVal);
						static enumContainer enumerations;

					};  /* RangeBinMaskingSubcategory */


				}  /* namespace DIS */
			}
		}
	}
}