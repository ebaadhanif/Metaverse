#ifndef LVCIndicator__H
#define LVCIndicator__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO LVCIndicator : public Enumeration {
  public:
    static LVCIndicator NO_STATEMENT;
    static LVCIndicator LIVE;
    static LVCIndicator VIRTUAL;
    static LVCIndicator CONSTRUCTIVE;

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static LVCIndicator getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,LVCIndicator*> enumContainer;
    static enumContainer getEnumerations();

    LVCIndicator& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  LVCIndicator(int value, std::string description);

	  static LVCIndicator* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* LVCIndicator */
}  /* namespace DIS */ }

#endif  

