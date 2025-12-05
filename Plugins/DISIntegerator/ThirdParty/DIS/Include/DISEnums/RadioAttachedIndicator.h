#ifndef RadioAttachedIndicator__H
#define RadioAttachedIndicator__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO RadioAttachedIndicator : public Enumeration {
  public:
    static RadioAttachedIndicator NO_STATEMENT;
	static RadioAttachedIndicator UNATTACHED;
	static RadioAttachedIndicator ATTACHED;

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static RadioAttachedIndicator getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,RadioAttachedIndicator*> enumContainer;
    static enumContainer getEnumerations();

    RadioAttachedIndicator& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  RadioAttachedIndicator(int value, std::string description);

	  static RadioAttachedIndicator* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* RadioAttachedIndicator */
}  /* namespace DIS */ }

#endif  

