#pragma once

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace JAMMING_TECHNIQUE {

			class EXPORT_MACRO JammingTechniqueKind : public Enumeration {
			public:
				static JammingTechniqueKind OTHER;
				static JammingTechniqueKind NOISE;
				static JammingTechniqueKind DECEPTION;
				static JammingTechniqueKind DECEPTION_NOISE;
				static JammingTechniqueKind SPECIAL;

				/** Returns the string description associated with the enumerated instance with this value.
				* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
				static std::string getDescriptionForValue(int aVal);

				/** Returns the enumerated instance with this value.
				* If there is no enumerated instance for this value, the exception is thrown.     */
				static JammingTechniqueKind getEnumerationForValue(int aVal) throw(EnumException);

				/** Returns true if there is an enumerated instance for this value, false otherwise. */
				static bool enumerationForValueExists(int aVal);

				typedef hashMap<int, JammingTechniqueKind*> enumContainer;
				static enumContainer getEnumerations();

				JammingTechniqueKind& operator=(const int& aVal) throw(EnumException);

			private:
				/** Constructor */
				JammingTechniqueKind(int value, std::string description);

				static JammingTechniqueKind* findEnumeration(int aVal);
				static enumContainer enumerations;

			};  /* JammingTechniqueKind */

		}
	}  
} /* namespace DIS */