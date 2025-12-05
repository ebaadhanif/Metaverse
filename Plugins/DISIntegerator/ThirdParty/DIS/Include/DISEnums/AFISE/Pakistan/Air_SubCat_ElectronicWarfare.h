#ifndef PAKISTAN_Air_SubCat_ElectronicWarfare__H
#define PAKISTAN_Air_SubCat_ElectronicWarfare__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace AFISE { namespace PAKISTAN { namespace AIR { namespace SubCategories {

class EXPORT_MACRO Air_SubCat_ElectronicWarfare : public Enumeration {
  public:
    static Air_SubCat_ElectronicWarfare OTHER;
	static Air_SubCat_ElectronicWarfare DASSAULT_FALCON_20_EF;
	
    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(unsigned short aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static Air_SubCat_ElectronicWarfare getEnumerationForValue(unsigned short aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(unsigned short aVal);

    typedef hashMap<unsigned short, Air_SubCat_ElectronicWarfare*> enumContainer;
    static enumContainer getEnumerations();

    Air_SubCat_ElectronicWarfare& operator=(const unsigned short& aVal) throw(EnumException);

  private:
    /** Constructor */
	  Air_SubCat_ElectronicWarfare(unsigned short aVal, std::string description);

	static Air_SubCat_ElectronicWarfare* findEnumeration(unsigned short aVal);
    static enumContainer enumerations;

};  /* ActionID */


}  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ }

#endif  