#ifndef PAKISTAN_Land_SubCat_Spada_SAM_System_H
#define PAKISTAN_Land_SubCat_Spada_SAM_System_H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace AFISE { namespace PAKISTAN { namespace LAND { namespace SubCategories {

class EXPORT_MACRO Land_SubCat_Spada_SAM_System : public Enumeration {
  public:
    static Land_SubCat_Spada_SAM_System OTHER;
	static Land_SubCat_Spada_SAM_System DETECTION_CENTER;
	static Land_SubCat_Spada_SAM_System SPADA_FIRING_SECTION;

	
    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(unsigned short aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static Land_SubCat_Spada_SAM_System getEnumerationForValue(unsigned short aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(unsigned short aVal);

    typedef hashMap<unsigned short, Land_SubCat_Spada_SAM_System*> enumContainer;
    static enumContainer getEnumerations();

    Land_SubCat_Spada_SAM_System& operator=(const unsigned short& aVal) throw(EnumException);

  private:
    /** Constructor */
	  Land_SubCat_Spada_SAM_System(unsigned short aVal, std::string description);

	static Land_SubCat_Spada_SAM_System* findEnumeration(unsigned short aVal);
    static enumContainer enumerations;

};  /* ActionID */


}  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ }

#endif  