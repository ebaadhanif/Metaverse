#ifndef IFFSystemStatus__H
#define IFFSystemStatus__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO IFFSystemStatus : public Enumeration {
  public:
    static IFFSystemStatus OFF;
    static IFFSystemStatus ON;
    
    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static IFFSystemStatus getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,IFFSystemStatus*> enumContainer;
    static enumContainer getEnumerations();

    IFFSystemStatus& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  IFFSystemStatus(int value, std::string description);

	  static IFFSystemStatus* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* IFFSystemStatus */


}  /* namespace DIS */ }

#endif  

