#ifndef USA_Air_SubCat_Unmanned__H
#define USA_Air_SubCat_Unmanned__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace AFISE { namespace USA { namespace AIR { namespace SubCategories {

class EXPORT_MACRO USA_Air_SubCat_Unmanned : public Enumeration {
  public:
    static USA_Air_SubCat_Unmanned OTHER;
	static USA_Air_SubCat_Unmanned RQ_170_SENTINEL;
	static USA_Air_SubCat_Unmanned RQ_7_SHADOW_UAV;
	
    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(unsigned short aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static USA_Air_SubCat_Unmanned getEnumerationForValue(unsigned short aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(unsigned short aVal);

    typedef hashMap<unsigned short, USA_Air_SubCat_Unmanned*> enumContainer;
    static enumContainer getEnumerations();

    USA_Air_SubCat_Unmanned& operator=(const unsigned short& aVal) throw(EnumException);

  private:
    /** Constructor */
	  USA_Air_SubCat_Unmanned(unsigned short aVal, std::string description);

	static USA_Air_SubCat_Unmanned* findEnumeration(unsigned short aVal);
    static enumContainer enumerations;

};  /* ActionID */


}  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ }

#endif  