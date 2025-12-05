#ifndef PAKISTAN_Munition_SubCat_Anti_Air_H
#define PAKISTAN_Munition_SubCat_Anti_Air_H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace AFISE { namespace PAKISTAN { namespace MUNITION { namespace SubCategories {

class EXPORT_MACRO Munition_SubCat_Anti_Air : public Enumeration {
  public:
    static Munition_SubCat_Anti_Air OTHER;
	static Munition_SubCat_Anti_Air AIM_9_SIDEWINDER;
	static Munition_SubCat_Anti_Air AIM_120_AMRAAM;
	static Munition_SubCat_Anti_Air ASPIDE_2000_SAM;

	
    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(unsigned short aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static Munition_SubCat_Anti_Air getEnumerationForValue(unsigned short aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(unsigned short aVal);

    typedef hashMap<unsigned short, Munition_SubCat_Anti_Air*> enumContainer;
    static enumContainer getEnumerations();

    Munition_SubCat_Anti_Air& operator=(const unsigned short& aVal) throw(EnumException);

  private:
    /** Constructor */
	  Munition_SubCat_Anti_Air(unsigned short aVal, std::string description);

	static Munition_SubCat_Anti_Air* findEnumeration(unsigned short aVal);
    static enumContainer enumerations;

};  /* ActionID */


}  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ }

#endif  