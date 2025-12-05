#ifndef PAKISTAN_Air_SubCat_CargoTanker__H
#define PAKISTAN_Air_SubCat_CargoTanker__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace AFISE { namespace PAKISTAN { namespace AIR { namespace SubCategories {

class EXPORT_MACRO Air_SubCat_CargoTanker : public Enumeration {
  public:
    static Air_SubCat_CargoTanker OTHER;
    static Air_SubCat_CargoTanker C_130;
	static Air_SubCat_CargoTanker CASA_CN235_220;
	static Air_SubCat_CargoTanker ILYUSHIN_IL_78_MP;

	
    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(unsigned short aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static Air_SubCat_CargoTanker getEnumerationForValue(unsigned short aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(unsigned short aVal);

    typedef hashMap<unsigned short, Air_SubCat_CargoTanker*> enumContainer;
    static enumContainer getEnumerations();

    Air_SubCat_CargoTanker& operator=(const unsigned short& aVal) throw(EnumException);

  private:
    /** Constructor */
	  Air_SubCat_CargoTanker(unsigned short aVal, std::string description);

	static Air_SubCat_CargoTanker* findEnumeration(unsigned short aVal);
    static enumContainer enumerations;

};  /* ActionID */


}  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ }

#endif  