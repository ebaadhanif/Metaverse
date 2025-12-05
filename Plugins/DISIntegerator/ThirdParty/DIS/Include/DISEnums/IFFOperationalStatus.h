#ifndef IFFOperationalStatus__H
#define IFFOperationalStatus__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO IFFOperationalStatus : public Enumeration {
  public:
    static IFFOperationalStatus OPERATIONAL;
    static IFFOperationalStatus SYSTEM_FAILED;

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static IFFOperationalStatus getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,IFFOperationalStatus*> enumContainer;
    static enumContainer getEnumerations();

    IFFOperationalStatus& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  IFFOperationalStatus(int value, std::string description);

	  static IFFOperationalStatus* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* IFFOperationalStatus */


}  /* namespace DIS */ }

#endif  

