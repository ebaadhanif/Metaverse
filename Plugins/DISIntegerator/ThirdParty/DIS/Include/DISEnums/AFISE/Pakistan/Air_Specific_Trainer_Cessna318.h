#ifndef PAKISTAN_Air_Specific_Trainer_Cessna318__H
#define PAKISTAN_Air_Specific_Trainer_Cessna318__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace AFISE { namespace PAKISTAN { namespace AIR { namespace Specific {

class EXPORT_MACRO Air_Specific_Trainer_Cessna318 : public Enumeration {
  public:
    static Air_Specific_Trainer_Cessna318 OTHER;
	static Air_Specific_Trainer_Cessna318 T_37_B;
	static Air_Specific_Trainer_Cessna318 T_37_C;

	
    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(unsigned short aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static Air_Specific_Trainer_Cessna318 getEnumerationForValue(unsigned short aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(unsigned short aVal);

    typedef hashMap<unsigned short, Air_Specific_Trainer_Cessna318*> enumContainer;
    static enumContainer getEnumerations();

    Air_Specific_Trainer_Cessna318& operator=(const unsigned short& aVal) throw(EnumException);

  private:
    /** Constructor */
	  Air_Specific_Trainer_Cessna318(unsigned short aVal, std::string description);

	static Air_Specific_Trainer_Cessna318* findEnumeration(unsigned short aVal);
    static enumContainer enumerations;

};  /* ActionID */


}  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ }

#endif  