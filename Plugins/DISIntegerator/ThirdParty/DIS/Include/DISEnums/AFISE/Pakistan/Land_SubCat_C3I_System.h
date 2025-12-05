#ifndef PAKISTAN_C3I_SYSTEMS_H
#define PAKISTAN_C3I_SYSTEMS_H
#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace AFISE { namespace PAKISTAN { namespace LAND { namespace SubCategories {

class EXPORT_MACRO Land_SubCat_C3I_System : public Enumeration {
  public:
    static Land_SubCat_C3I_System OTHER;
	static Land_SubCat_C3I_System GENERIC_MISSION_CONTROL_CENTER;
	static Land_SubCat_C3I_System SECTOR_MISSION_CONTROL_CENTER;
	
    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(unsigned short aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static Land_SubCat_C3I_System getEnumerationForValue(unsigned short aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(unsigned short aVal);

    typedef hashMap<unsigned short, Land_SubCat_C3I_System*> enumContainer;
    static enumContainer getEnumerations();

    Land_SubCat_C3I_System& operator=(const unsigned short& aVal) throw(EnumException);

  private:
    /** Constructor */
	  Land_SubCat_C3I_System(unsigned short aVal, std::string description);

	static Land_SubCat_C3I_System* findEnumeration(unsigned short aVal);
    static enumContainer enumerations;

};  /* ActionID */


}  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ }

#endif  