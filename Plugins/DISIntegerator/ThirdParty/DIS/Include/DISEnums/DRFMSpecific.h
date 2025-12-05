#pragma once

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace JAMMING_TECHNIQUE { namespace DECEPTION { namespace REPEATER { namespace DRFM {
					class EXPORT_MACRO DRFMSpecific : public Enumeration {
					public:
						static DRFMSpecific OTHER;
						static DRFMSpecific DRFM_LEVEL_A;
						static DRFMSpecific DRFM_LEVEL_B;
						static DRFMSpecific DRFM_LEVEL_C;
						static DRFMSpecific DRFM_LEVEL_D;
						static DRFMSpecific DRFM_LEVEL_E;

						/** Returns the string description associated with the enumerated instance with this value.
						* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
						static std::string getDescriptionForValue(int aVal);

						/** Returns the enumerated instance with this value.
						* If there is no enumerated instance for this value, the exception is thrown.     */
						static DRFMSpecific getEnumerationForValue(int aVal) throw(EnumException);

						/** Returns true if there is an enumerated instance for this value, false otherwise. */
						static bool enumerationForValueExists(int aVal);

						typedef hashMap<int, DRFMSpecific*> enumContainer;
						static enumContainer getEnumerations();

						DRFMSpecific& operator=(const int& aVal) throw(EnumException);

					private:
						/** Constructor */
						DRFMSpecific(int value, std::string description);

						static DRFMSpecific* findEnumeration(int aVal);
						static enumContainer enumerations;

					};  /* DRFMSpecific */


				}  /* namespace DIS */
			}
		}
	}
} }