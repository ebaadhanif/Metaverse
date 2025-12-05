#ifndef INDIA_Air_SubCat_Unmanned__H
#define INDIA_Air_SubCat_Unmanned__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace AFISE { namespace INDIA { namespace AIR { namespace SubCategories {

class EXPORT_MACRO INDIA_Air_SubCat_Unmanned : public Enumeration {
  public:
    static INDIA_Air_SubCat_Unmanned OTHER;
	static INDIA_Air_SubCat_Unmanned IAI_HERON;
	static INDIA_Air_SubCat_Unmanned IAI_SEARCHER;
	static INDIA_Air_SubCat_Unmanned DRDO_AURA;
	static INDIA_Air_SubCat_Unmanned DRDO_RUSTOM;
	
    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(unsigned short aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static INDIA_Air_SubCat_Unmanned getEnumerationForValue(unsigned short aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(unsigned short aVal);

    typedef hashMap<unsigned short, INDIA_Air_SubCat_Unmanned*> enumContainer;
    static enumContainer getEnumerations();

    INDIA_Air_SubCat_Unmanned& operator=(const unsigned short& aVal) throw(EnumException);

  private:
    /** Constructor */
	  INDIA_Air_SubCat_Unmanned(unsigned short aVal, std::string description);

	static INDIA_Air_SubCat_Unmanned* findEnumeration(unsigned short aVal);
    static enumContainer enumerations;

};  /* ActionID */


}  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ }

#endif  