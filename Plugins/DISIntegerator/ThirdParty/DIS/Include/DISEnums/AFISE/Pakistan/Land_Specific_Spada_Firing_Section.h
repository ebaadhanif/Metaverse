#ifndef PAKISTAN_SPADA_FIRING_SECTION_H
#define PAKISTAN_SPADA_FIRING_SECTION_H
#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace AFISE { namespace PAKISTAN { namespace LAND { namespace SPECIFIC {

class EXPORT_MACRO Land_Specific_Spada_Firing_Section : public Enumeration {
  public:
    static Land_Specific_Spada_Firing_Section OTHER;
	static Land_Specific_Spada_Firing_Section Aspide_6R_ML;
	static Land_Specific_Spada_Firing_Section TIR;

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(unsigned short aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static Land_Specific_Spada_Firing_Section getEnumerationForValue(unsigned short aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(unsigned short aVal);

    typedef hashMap<unsigned short, Land_Specific_Spada_Firing_Section*> enumContainer;
    static enumContainer getEnumerations();

    Land_Specific_Spada_Firing_Section& operator=(const unsigned short& aVal) throw(EnumException);

  private:
    /** Constructor */
	  Land_Specific_Spada_Firing_Section(unsigned short aVal, std::string description);

	static Land_Specific_Spada_Firing_Section* findEnumeration(unsigned short aVal);
    static enumContainer enumerations;

};  /* ActionID */


}  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ }

#endif  