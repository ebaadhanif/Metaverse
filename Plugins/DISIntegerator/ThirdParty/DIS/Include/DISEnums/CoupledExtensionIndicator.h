#ifndef CoupledExtensionIndicator__H
#define CoupledExtensionIndicator__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO CoupledExtensionIndicator : public Enumeration {
  public:
    static CoupledExtensionIndicator NOT_COUPLED;
    static CoupledExtensionIndicator COUPLED;

	/** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static CoupledExtensionIndicator getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,CoupledExtensionIndicator*> enumContainer;
    static enumContainer getEnumerations();

    CoupledExtensionIndicator& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  CoupledExtensionIndicator(int value, std::string description);

	  static CoupledExtensionIndicator* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* CoupledExtensionIndicator */
}  /* namespace DIS */ }

#endif  

