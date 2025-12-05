#ifndef IFFTestMode__H
#define IFFTestMode__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO IFFTestMode : public Enumeration {
  public:
    static IFFTestMode OFF;
    static IFFTestMode ON;

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static IFFTestMode getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,IFFTestMode*> enumContainer;
    static enumContainer getEnumerations();

    IFFTestMode& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  IFFTestMode(int value, std::string description);

	  static IFFTestMode* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* IFFTestMode */
}  /* namespace DIS */ }

#endif  

