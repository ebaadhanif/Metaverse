#pragma once

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace JAMMING_TECHNIQUE { namespace DECEPTION { namespace ANGLE_FAST_TARGET { namespace ANGLE_VFT {

					class EXPORT_MACRO AngleAndVFTSpecific : public Enumeration {
					public:
						static AngleAndVFTSpecific OTHER;
						static AngleAndVFTSpecific INVERSE_GAIN_VFT;
						static AngleAndVFTSpecific SSW_VFT;

						/** Returns the string description associated with the enumerated instance with this value.
						* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
						static std::string getDescriptionForValue(int aVal);

						/** Returns the enumerated instance with this value.
						* If there is no enumerated instance for this value, the exception is thrown.     */
						static AngleAndVFTSpecific getEnumerationForValue(int aVal) throw(EnumException);

						/** Returns true if there is an enumerated instance for this value, false otherwise. */
						static bool enumerationForValueExists(int aVal);

						typedef hashMap<int, AngleAndVFTSpecific*> enumContainer;
						static enumContainer getEnumerations();

						AngleAndVFTSpecific& operator=(const int& aVal) throw(EnumException);

					private:
						/** Constructor */
						AngleAndVFTSpecific(int value, std::string description);

						static AngleAndVFTSpecific* findEnumeration(int aVal);
						static enumContainer enumerations;

					};  /* AngleAndVFTSpecific */


				}  /* namespace DIS */
			}
		}
	}
} }