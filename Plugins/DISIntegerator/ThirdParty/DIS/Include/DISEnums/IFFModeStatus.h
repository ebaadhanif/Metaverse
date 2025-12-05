#ifndef IFFModeStatus__H
#define IFFModeStatus__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO IFFModeStatus : public Enumeration {
  public:
    static IFFModeStatus OFF;
    static IFFModeStatus ON;

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static IFFModeStatus getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,IFFModeStatus*> enumContainer;
    static enumContainer getEnumerations();

    IFFModeStatus& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  IFFModeStatus(int value, std::string description);

	  static IFFModeStatus* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* IFFModeStatus */
}  /* namespace DIS */ }

#endif  

