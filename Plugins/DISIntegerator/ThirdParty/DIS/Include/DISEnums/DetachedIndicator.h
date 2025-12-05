#ifndef DETACHEDINDICATOR__H
#define DETACHEDINDICATOR__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO DetachedIndicator : public Enumeration {
  public:
    static DetachedIndicator ATTACHED;
    static DetachedIndicator DETACHED;
    

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static DetachedIndicator getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int, DetachedIndicator*> enumContainer;
    static enumContainer getEnumerations();

	DetachedIndicator& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  DetachedIndicator(int value, std::string description);

	  static DetachedIndicator* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* DetachedIndicator */


}  /* namespace DIS */ }

#endif /* DETACHEDINDICATOR__H */

