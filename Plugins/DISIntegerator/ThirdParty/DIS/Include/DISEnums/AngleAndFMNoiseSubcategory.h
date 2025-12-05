#pragma once

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace JAMMING_TECHNIQUE { namespace DECEPTION_NOISE { namespace ANGLE_FM_NOISE {

					class EXPORT_MACRO AngleAndFMNoiseSubcategory : public Enumeration {
					public:
						static AngleAndFMNoiseSubcategory OTHER;
						static AngleAndFMNoiseSubcategory FM_NOISE_INVERSION_GAIN;
						static AngleAndFMNoiseSubcategory FM_NOISE_SSW;

						/** Returns the string description associated with the enumerated instance with this value.
						* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
						static std::string getDescriptionForValue(int aVal);

						/** Returns the enumerated instance with this value.
						* If there is no enumerated instance for this value, the exception is thrown.     */
						static AngleAndFMNoiseSubcategory getEnumerationForValue(int aVal) throw(EnumException);

						/** Returns true if there is an enumerated instance for this value, false otherwise. */
						static bool enumerationForValueExists(int aVal);

						typedef hashMap<int, AngleAndFMNoiseSubcategory*> enumContainer;
						static enumContainer getEnumerations();

						AngleAndFMNoiseSubcategory& operator=(const int& aVal) throw(EnumException);

					private:
						/** Constructor */
						AngleAndFMNoiseSubcategory(int value, std::string description);

						static AngleAndFMNoiseSubcategory* findEnumeration(int aVal);
						static enumContainer enumerations;

					};  /* AngleAndFMNoiseSubcategory */


				}  /* namespace DIS */
			}
		}
	}
}