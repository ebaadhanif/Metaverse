#ifndef INDIA_Air_SubCat_FighterAirDefence__H
#define INDIA_Air_SubCat_FighterAirDefence__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace AFISE { namespace INDIA { namespace AIR { namespace SubCategories {

class EXPORT_MACRO INDIA_Air_SubCat_FighterAirDefence : public Enumeration {
  public:
    static INDIA_Air_SubCat_FighterAirDefence OTHER;
    static INDIA_Air_SubCat_FighterAirDefence HAL_TEJAS;
	static INDIA_Air_SubCat_FighterAirDefence MIRAGE_2000;
	static INDIA_Air_SubCat_FighterAirDefence MIG_21;
	static INDIA_Air_SubCat_FighterAirDefence MIG_23;
	static INDIA_Air_SubCat_FighterAirDefence MIG_25;
	static INDIA_Air_SubCat_FighterAirDefence MIG_27;
	static INDIA_Air_SubCat_FighterAirDefence MIG_29;
	static INDIA_Air_SubCat_FighterAirDefence SU_30_MK_I;

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(unsigned short aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static INDIA_Air_SubCat_FighterAirDefence getEnumerationForValue(unsigned short aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(unsigned short aVal);

    typedef hashMap<unsigned short, INDIA_Air_SubCat_FighterAirDefence*> enumContainer;
    static enumContainer getEnumerations();

    INDIA_Air_SubCat_FighterAirDefence& operator=(const unsigned short& aVal) throw(EnumException);

  private:
    /** Constructor */
	  INDIA_Air_SubCat_FighterAirDefence(unsigned short aVal, std::string description);

	static INDIA_Air_SubCat_FighterAirDefence* findEnumeration(unsigned short aVal);
    static enumContainer enumerations;

};  /* ActionID */


}  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ }

#endif  