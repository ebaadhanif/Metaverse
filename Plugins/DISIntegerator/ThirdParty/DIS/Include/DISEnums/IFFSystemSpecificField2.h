#ifndef IFFSystemSpecificField2__H
#define IFFSystemSpecificField2__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO IFFSystemSpecificField2 : public Enumeration {
  public:
    static IFFSystemSpecificField2 NOT_PRESENT;
    static IFFSystemSpecificField2 PRESENT;

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static IFFSystemSpecificField2 getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,IFFSystemSpecificField2*> enumContainer;
    static enumContainer getEnumerations();

    IFFSystemSpecificField2& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  IFFSystemSpecificField2(int value, std::string description);

	  static IFFSystemSpecificField2* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* IFFSystemSpecificField2 */
}  /* namespace DIS */ }

#endif  

