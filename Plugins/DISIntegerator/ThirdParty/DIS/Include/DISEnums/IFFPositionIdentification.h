#ifndef IFFPositionIdentification__H
#define IFFPositionIdentification__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO IFFPositionIdentification : public Enumeration {
  public:
    static IFFPositionIdentification OFF;
    static IFFPositionIdentification ON;

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static IFFPositionIdentification getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,IFFPositionIdentification*> enumContainer;
    static enumContainer getEnumerations();

    IFFPositionIdentification& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  IFFPositionIdentification(int value, std::string description);

	  static IFFPositionIdentification* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* IFFPositionIdentification */


}  /* namespace DIS */ }

#endif  

