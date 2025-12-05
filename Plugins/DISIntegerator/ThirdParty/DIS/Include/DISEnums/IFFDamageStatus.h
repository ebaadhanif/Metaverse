#ifndef IFFDamageStatus__H
#define IFFDamageStatus__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO IFFDamageStatus : public Enumeration {
  public:
    static IFFDamageStatus NO_DAMAGE;
    static IFFDamageStatus DAMAGED;
    
    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static IFFDamageStatus getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,IFFDamageStatus*> enumContainer;
    static enumContainer getEnumerations();

    IFFDamageStatus& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  IFFDamageStatus(int value, std::string description);

	  static IFFDamageStatus* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* IFFDamageStatus */


}  /* namespace DIS */ }

#endif  

