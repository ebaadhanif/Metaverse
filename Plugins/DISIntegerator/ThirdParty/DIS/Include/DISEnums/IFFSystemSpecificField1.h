#ifndef IFFSystemSpecificField1__H
#define IFFSystemSpecificField1__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO IFFSystemSpecificField1 : public Enumeration {
  public:
    static IFFSystemSpecificField1 NOT_PRESENT;
    static IFFSystemSpecificField1 PRESENT;

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static IFFSystemSpecificField1 getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,IFFSystemSpecificField1*> enumContainer;
    static enumContainer getEnumerations();

    IFFSystemSpecificField1& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  IFFSystemSpecificField1(int value, std::string description);

	  static IFFSystemSpecificField1* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* IFFSystemSpecificField1 */


}  /* namespace DIS */ }

#endif  

