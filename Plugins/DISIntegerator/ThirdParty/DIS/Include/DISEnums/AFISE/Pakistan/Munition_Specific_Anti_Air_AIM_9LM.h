#ifndef Munition_Specific_Anti_Air_AIM_9LM_H
#define Munition_Specific_Anti_Air_AIM_9LM_H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace AFISE { namespace PAKISTAN { namespace MUNITION { namespace SPECIFIC {

class EXPORT_MACRO Munition_Specific_Anti_Air_AIM_9LM : public Enumeration {
  public:
    static Munition_Specific_Anti_Air_AIM_9LM OTHER;
	static Munition_Specific_Anti_Air_AIM_9LM AIM_9_L;
	static Munition_Specific_Anti_Air_AIM_9LM AIM_9_M;
	static Munition_Specific_Anti_Air_AIM_9LM AIM_9_M_7;
	static Munition_Specific_Anti_Air_AIM_9LM AIM_9_M_8_7;

	
    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(unsigned short aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static Munition_Specific_Anti_Air_AIM_9LM getEnumerationForValue(unsigned short aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(unsigned short aVal);

    typedef hashMap<unsigned short, Munition_Specific_Anti_Air_AIM_9LM*> enumContainer;
    static enumContainer getEnumerations();

    Munition_Specific_Anti_Air_AIM_9LM& operator=(const unsigned short& aVal) throw(EnumException);

  private:
    /** Constructor */
	  Munition_Specific_Anti_Air_AIM_9LM(unsigned short aVal, std::string description);

	static Munition_Specific_Anti_Air_AIM_9LM* findEnumeration(unsigned short aVal);
    static enumContainer enumerations;

};  /* ActionID */


}  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ }

#endif  