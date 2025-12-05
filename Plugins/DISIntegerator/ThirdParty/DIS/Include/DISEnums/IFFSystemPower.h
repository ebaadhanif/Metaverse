#ifndef IFFSystemPower__H
#define IFFSystemPower__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO IFFSystemPower : public Enumeration {
  public:
    static IFFSystemPower PWR_NO_STATEMENT;
    static IFFSystemPower PWR_OFF;
    static IFFSystemPower PWR_STANDBY;
    static IFFSystemPower PWR_NORMAL;
    static IFFSystemPower PWR_EMERGENCY;
    static IFFSystemPower PWR_LOW_OR_LOW_SENSITIVITY;
    
    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static IFFSystemPower getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,IFFSystemPower*> enumContainer;
    static enumContainer getEnumerations();

    IFFSystemPower& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  IFFSystemPower(int value, std::string description);

	  static IFFSystemPower* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* IFFSystemPower */


}  /* namespace DIS */ }

#endif  

