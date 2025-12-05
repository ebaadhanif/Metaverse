#ifndef PAKISTAN_Air_SubCat_AttackStrike__H
#define PAKISTAN_Air_SubCat_AttackStrike__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace AFISE { namespace PAKISTAN { namespace AIR { namespace SubCategories {

class EXPORT_MACRO Air_SubCat_AttackStrike : public Enumeration {
  public:
    static Air_SubCat_AttackStrike OTHER;
	static Air_SubCat_AttackStrike GENERAL_DYNAMICS_F16_FIGHTING_FALCON;
	static Air_SubCat_AttackStrike PAC_JF17_THUNDER;
	static Air_SubCat_AttackStrike CHENGDU_F7_FISHBED;
	static Air_SubCat_AttackStrike MIRAGE_III;
	static Air_SubCat_AttackStrike MIRAGE_V;

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(unsigned short aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static Air_SubCat_AttackStrike getEnumerationForValue(unsigned short aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(unsigned short aVal);

    typedef hashMap<unsigned short, Air_SubCat_AttackStrike*> enumContainer;
    static enumContainer getEnumerations();

    Air_SubCat_AttackStrike& operator=(const unsigned short& aVal) throw(EnumException);

  private:
    /** Constructor */
	  Air_SubCat_AttackStrike(unsigned short aVal, std::string description);

	static Air_SubCat_AttackStrike* findEnumeration(unsigned short aVal);
    static enumContainer enumerations;

};  /* ActionID */


}  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ }

#endif  