#pragma once

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace JAMMING_TECHNIQUE { namespace DECEPTION_NOISE { namespace GATE_STEALER_NOISE {

					class EXPORT_MACRO GateStealerAndNoiseSubcategory : public Enumeration {
					public:
						static GateStealerAndNoiseSubcategory OTHER;
						static GateStealerAndNoiseSubcategory NOISE_RGPO;
						static GateStealerAndNoiseSubcategory NOISE_VGPO;

						/** Returns the string description associated with the enumerated instance with this value.
						* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
						static std::string getDescriptionForValue(int aVal);

						/** Returns the enumerated instance with this value.
						* If there is no enumerated instance for this value, the exception is thrown.     */
						static GateStealerAndNoiseSubcategory getEnumerationForValue(int aVal) throw(EnumException);

						/** Returns true if there is an enumerated instance for this value, false otherwise. */
						static bool enumerationForValueExists(int aVal);

						typedef hashMap<int, GateStealerAndNoiseSubcategory*> enumContainer;
						static enumContainer getEnumerations();

						GateStealerAndNoiseSubcategory& operator=(const int& aVal) throw(EnumException);

					private:
						/** Constructor */
						GateStealerAndNoiseSubcategory(int value, std::string description);

						static GateStealerAndNoiseSubcategory* findEnumeration(int aVal);
						static enumContainer enumerations;

					};  /* GateStealerAndNoiseSubcategory */


				}  /* namespace DIS */
			}
		}
	}
}