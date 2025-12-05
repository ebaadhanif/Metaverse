#pragma once

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace JAMMING_TECHNIQUE { namespace DECEPTION_NOISE {

				class EXPORT_MACRO DeceptionAndNoiseCategory : public Enumeration {
				public:
					static DeceptionAndNoiseCategory ANGLE_NOISE;
					static DeceptionAndNoiseCategory ANGLE_FM_NOISE;
					static DeceptionAndNoiseCategory ANGLE_PSEUDORANDOM_AM;
					static DeceptionAndNoiseCategory ANGLE_SPOT;
					static DeceptionAndNoiseCategory GATE_STEALER_NOISE;
					static DeceptionAndNoiseCategory FALSE_TARGET_DECEPTION_SWEPT_NOISE;


					/** Returns the string description associated with the enumerated instance with this value.
					* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
					static std::string getDescriptionForValue(int aVal);

					/** Returns the enumerated instance with this value.
					* If there is no enumerated instance for this value, the exception is thrown.     */
					static DeceptionAndNoiseCategory getEnumerationForValue(int aVal) throw(EnumException);

					/** Returns true if there is an enumerated instance for this value, false otherwise. */
					static bool enumerationForValueExists(int aVal);

					typedef hashMap<int, DeceptionAndNoiseCategory*> enumContainer;
					static enumContainer getEnumerations();

					DeceptionAndNoiseCategory& operator=(const int& aVal) throw(EnumException);

				private:
					/** Constructor */
					DeceptionAndNoiseCategory(int value, std::string description);

					static DeceptionAndNoiseCategory* findEnumeration(int aVal);
					static enumContainer enumerations;

				};  /* DeceptionAndNoiseCategory */


			}  /* namespace DIS */
		}
	}
}
