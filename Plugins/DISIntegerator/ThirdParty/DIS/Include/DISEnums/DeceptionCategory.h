#pragma once

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace JAMMING_TECHNIQUE { namespace DECEPTION {

				class EXPORT_MACRO DeceptionCategory : public Enumeration {
				public:
					static DeceptionCategory OTHER;
					static DeceptionCategory ANALYZER;
					static DeceptionCategory ANGLE;
					static DeceptionCategory ANGLE_GATE_STEALER;
					static DeceptionCategory ANGLE_FALSE_TARGET;
					static DeceptionCategory ANGLE_RANDOM_RANGE_PROGRAMS;
					static DeceptionCategory ANGLE_VELOCITY;
					static DeceptionCategory AUTOMATIC_GAIN_CONTROL;
					static DeceptionCategory AGC_GATE_STEALER;
					static DeceptionCategory COLINEAR;
					static DeceptionCategory CONSTANT_FALSE_ALARM_RATE;
					static DeceptionCategory DOUBLE_CROSS;
					static DeceptionCategory DOWN_LINK;
					static DeceptionCategory FALSE_TARGET;
					static DeceptionCategory FIGURE_EIGHT;
					static DeceptionCategory GATE_STEALER;
					static DeceptionCategory GATE_STEALER_REPEATER;
					static DeceptionCategory GLINT_ENHANCE;
					static DeceptionCategory IMAGE_FREQUENCY;
					static DeceptionCategory JITTERED_PULSE_REPETITION_FREQUENCY;
					static DeceptionCategory JITTERED_PULSE_WIDTH;
					static DeceptionCategory PSEUDORANDOM_NOISE;
					static DeceptionCategory PULSE;
					static DeceptionCategory PULSE_COMPRESSION_DECEPTION;
					static DeceptionCategory RANDOM_RANGE_PROGRAMS;
					static DeceptionCategory REFRACTION;
					static DeceptionCategory REPEATER;
					static DeceptionCategory SCINTILLATION;
					static DeceptionCategory SERRODYNE;
					static DeceptionCategory VELOCITY;


					/** Returns the string description associated with the enumerated instance with this value.
					* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
					static std::string getDescriptionForValue(int aVal);

					/** Returns the enumerated instance with this value.
					* If there is no enumerated instance for this value, the exception is thrown.     */
					static DeceptionCategory getEnumerationForValue(int aVal) throw(EnumException);

					/** Returns true if there is an enumerated instance for this value, false otherwise. */
					static bool enumerationForValueExists(int aVal);

					typedef hashMap<int, DeceptionCategory*> enumContainer;
					static enumContainer getEnumerations();

					DeceptionCategory& operator=(const int& aVal) throw(EnumException);

				private:
					/** Constructor */
					DeceptionCategory(int value, std::string description);

					static DeceptionCategory* findEnumeration(int aVal);
					static enumContainer enumerations;

				};  /* DeceptionCategory */


			}  /* namespace DIS */
		}
	}
}
