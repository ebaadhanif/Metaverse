#ifndef Munition_Specific_Anti_Air_AIM_120_H
#define Munition_Specific_Anti_Air_AIM_120_H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace AFISE { namespace PAKISTAN { namespace MUNITION { namespace SPECIFIC {

class EXPORT_MACRO Munition_Specific_Anti_Air_AIM_120 : public Enumeration {
  public:
    static Munition_Specific_Anti_Air_AIM_120 OTHER;
	static Munition_Specific_Anti_Air_AIM_120 AIM_120_A;
	static Munition_Specific_Anti_Air_AIM_120 AIM_120_B;
	static Munition_Specific_Anti_Air_AIM_120 AIM_120_C_5;

	
    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(unsigned short aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static Munition_Specific_Anti_Air_AIM_120 getEnumerationForValue(unsigned short aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(unsigned short aVal);

    typedef hashMap<unsigned short, Munition_Specific_Anti_Air_AIM_120*> enumContainer;
    static enumContainer getEnumerations();

    Munition_Specific_Anti_Air_AIM_120& operator=(const unsigned short& aVal) throw(EnumException);

  private:
    /** Constructor */
	  Munition_Specific_Anti_Air_AIM_120(unsigned short aVal, std::string description);

	static Munition_Specific_Anti_Air_AIM_120* findEnumeration(unsigned short aVal);
    static enumContainer enumerations;

};  /* ActionID */


}  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ }

#endif  