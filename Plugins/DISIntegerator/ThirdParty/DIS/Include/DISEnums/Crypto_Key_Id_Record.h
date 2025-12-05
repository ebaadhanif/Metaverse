#ifndef CRYPTO_KEY_ID_RECORD
#define CRYPTO_KEY_ID_RECORD

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS {
	namespace ENUMS {

		namespace Crypto_Key_Id_Record {

			/** Bitmask declaration **/
			struct EXPORT_MACRO bitmask {
				unsigned short CryptoKey : 15;
				unsigned short CryptoMode : 1;

				bitmask& operator=(const unsigned short& i);
				bitmask(const unsigned short& i);
				bitmask();
				unsigned short getValue();
				void  setValue(const unsigned short& i);
			};

			/** Enumerations declaration **/
			class EXPORT_MACRO CryptoMode : public Enumeration {
			public:
				static CryptoMode BASEBAND;
				static CryptoMode DIPHASE;


				/** Returns the string description associated with the enumerated instance with this value.
				* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
				static std::string getDescriptionForValue(int aVal);

				/** Returns the enumerated instance with this value.
				* If there is no enumerated instance for this value, the exception is thrown.     */
				static CryptoMode getEnumerationForValue(int aVal) throw(EnumException);

				/** Returns true if there is an enumerated instance for this value, false otherwise. */
				static bool enumerationForValueExists(int aVal);

				typedef hashMap<int, CryptoMode*> enumContainer;
				static enumContainer getEnumerations();

				/** Returns the start bit number for this subfield */
				static short  getStartBit() { return startBit; };

				/** Returns the end bit number for this subfield */
				static short  getEndBit() { return endBit; };


			private:
				/** Constructor */
				CryptoMode(int value, std::string description);

				static CryptoMode* findEnumeration(int aVal);
				static enumContainer enumerations;

				static short startBit;
				static short endBit;

			};

		}; /* namespace env_obj_appear_areal_minefield */

	}  /* namespace DIS */
}

#endif 
