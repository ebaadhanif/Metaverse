#ifndef PAKISTAN_Air_SubCat_CargoHelicopter__H
#define PAKISTAN_Air_SubCat_CargoHelicopter__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace AFISE { namespace PAKISTAN { namespace AIR { namespace SubCategories {

class EXPORT_MACRO Air_SubCat_CargoHelicopter : public Enumeration {
  public:
    static Air_SubCat_CargoHelicopter OTHER;
	static Air_SubCat_CargoHelicopter MI_171;
	
    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(unsigned short aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static Air_SubCat_CargoHelicopter getEnumerationForValue(unsigned short aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(unsigned short aVal);

    typedef hashMap<unsigned short, Air_SubCat_CargoHelicopter*> enumContainer;
    static enumContainer getEnumerations();

    Air_SubCat_CargoHelicopter& operator=(const unsigned short& aVal) throw(EnumException);

  private:
    /** Constructor */
	  Air_SubCat_CargoHelicopter(unsigned short aVal, std::string description);

	static Air_SubCat_CargoHelicopter* findEnumeration(unsigned short aVal);
    static enumContainer enumerations;

};  /* ActionID */


}  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ }

#endif  