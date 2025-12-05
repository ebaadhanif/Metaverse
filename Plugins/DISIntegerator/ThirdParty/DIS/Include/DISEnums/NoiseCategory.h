#pragma once

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace JAMMING_TECHNIQUE { namespace NOISE {

				class EXPORT_MACRO NoiseCategory : public Enumeration {
				public:
					static NoiseCategory OTHER;
					static NoiseCategory AMPLITUDE_MODULATION_NOISE;
					static NoiseCategory BARRAGE_NOISE;
					static NoiseCategory BISTATIC_CLUTTER;
					static NoiseCategory COMB;
					static NoiseCategory COOPERATIVE_BLINKED_NOISE;
					static NoiseCategory DOPPLER_NOISE;
					static NoiseCategory FREQUENCY_MODULATION_NOISE;
					static NoiseCategory IMPULSE_NOISE;
					static NoiseCategory PARTIAL_BAND;
					static NoiseCategory PSEUDORANDOM_AM;
					static NoiseCategory PULSE_NOISE;
					static NoiseCategory QUASI_NOISE;
					static NoiseCategory RANGE_BIN_MASKING;
					static NoiseCategory REPEATER_NOISE;
					static NoiseCategory SPOT_NOISE;
					static NoiseCategory SWEPT_NOISE;
					static NoiseCategory VELOCITY_BIN_MASKING;

					/** Returns the string description associated with the enumerated instance with this value.
					* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
					static std::string getDescriptionForValue(int aVal);

					/** Returns the enumerated instance with this value.
					* If there is no enumerated instance for this value, the exception is thrown.     */
					static NoiseCategory getEnumerationForValue(int aVal) throw(EnumException);

					/** Returns true if there is an enumerated instance for this value, false otherwise. */
					static bool enumerationForValueExists(int aVal);

					typedef hashMap<int, NoiseCategory*> enumContainer;
					static enumContainer getEnumerations();

					NoiseCategory& operator=(const int& aVal) throw(EnumException);

				private:
					/** Constructor */
					NoiseCategory(int value, std::string description);

					static NoiseCategory* findEnumeration(int aVal);
					static enumContainer enumerations;

				};  /* NoiseCategory */


			}  /* namespace DIS */
		}
	}
}
