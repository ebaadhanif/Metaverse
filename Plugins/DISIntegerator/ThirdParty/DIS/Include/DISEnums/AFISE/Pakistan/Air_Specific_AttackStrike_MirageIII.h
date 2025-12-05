#ifndef PAKISTAN_Air_Specific_AttackStrike_MirageIII__H
#define PAKISTAN_Air_Specific_AttackStrike_MirageIII__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace AFISE { namespace PAKISTAN { namespace AIR { namespace Specific {

class EXPORT_MACRO Air_Specific_AttackStrike_MirageIII : public Enumeration {
  public:
    static Air_Specific_AttackStrike_MirageIII OTHER;
	static Air_Specific_AttackStrike_MirageIII MIRAGE_III_EA;
	static Air_Specific_AttackStrike_MirageIII MIRAGE_III_DP;
	static Air_Specific_AttackStrike_MirageIII MIRAGE_III_DA;
	static Air_Specific_AttackStrike_MirageIII MIRAGE_III_EP;
	static Air_Specific_AttackStrike_MirageIII MIRAGE_III_RP;
	static Air_Specific_AttackStrike_MirageIII MIRAGE_III_DL;
	static Air_Specific_AttackStrike_MirageIII MIRAGE_III_DF;
	static Air_Specific_AttackStrike_MirageIII MIRAGE_III_EL;
	
    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(unsigned short aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static Air_Specific_AttackStrike_MirageIII getEnumerationForValue(unsigned short aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(unsigned short aVal);

    typedef hashMap<unsigned short, Air_Specific_AttackStrike_MirageIII*> enumContainer;
    static enumContainer getEnumerations();

    Air_Specific_AttackStrike_MirageIII& operator=(const unsigned short& aVal) throw(EnumException);

  private:
    /** Constructor */
	  Air_Specific_AttackStrike_MirageIII(unsigned short aVal, std::string description);

	static Air_Specific_AttackStrike_MirageIII* findEnumeration(unsigned short aVal);
    static enumContainer enumerations;

};  /* ActionID */


}  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ }

#endif  