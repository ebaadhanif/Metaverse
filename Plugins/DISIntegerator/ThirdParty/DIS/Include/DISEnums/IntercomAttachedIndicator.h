#ifndef IntercomAttachedIndicator__H
#define IntercomAttachedIndicator__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO IntercomAttachedIndicator : public Enumeration {
  public:
    static IntercomAttachedIndicator NO_STATEMENT;
    static IntercomAttachedIndicator UNATTACHED;
	static IntercomAttachedIndicator ATTACHED;
    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static IntercomAttachedIndicator getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,IntercomAttachedIndicator*> enumContainer;
    static enumContainer getEnumerations();

    IntercomAttachedIndicator& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  IntercomAttachedIndicator(int value, std::string description);

	  static IntercomAttachedIndicator* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* IntercomAttachedIndicator */
}  /* namespace DIS */ }

#endif  

