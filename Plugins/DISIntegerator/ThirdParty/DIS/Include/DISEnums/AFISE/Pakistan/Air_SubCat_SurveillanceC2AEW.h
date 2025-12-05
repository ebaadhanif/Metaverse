#ifndef PAKISTAN_Air_SubCat_SurveillanceC2AEW__H
#define PAKISTAN_Air_SubCat_SurveillanceC2AEW__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace AFISE { namespace PAKISTAN { namespace AIR { namespace SubCategories {

class EXPORT_MACRO Air_SubCat_SurveillanceC2AEW : public Enumeration {
  public:
    static Air_SubCat_SurveillanceC2AEW OTHER;
	static Air_SubCat_SurveillanceC2AEW SAAB_2000_AEW_C;
	static Air_SubCat_SurveillanceC2AEW KE_03_AEW_C;
	static Air_SubCat_SurveillanceC2AEW C_130_B_ISR;

	
    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(unsigned short aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static Air_SubCat_SurveillanceC2AEW getEnumerationForValue(unsigned short aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(unsigned short aVal);

    typedef hashMap<unsigned short, Air_SubCat_SurveillanceC2AEW*> enumContainer;
    static enumContainer getEnumerations();

    Air_SubCat_SurveillanceC2AEW& operator=(const unsigned short& aVal) throw(EnumException);

  private:
    /** Constructor */
	  Air_SubCat_SurveillanceC2AEW(unsigned short aVal, std::string description);

	static Air_SubCat_SurveillanceC2AEW* findEnumeration(unsigned short aVal);
    static enumContainer enumerations;

};  /* ActionID */


}  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ }

#endif  