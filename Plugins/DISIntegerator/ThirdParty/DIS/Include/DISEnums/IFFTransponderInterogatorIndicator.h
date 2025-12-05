#ifndef IFFTransponderInterogatorIndicator__H
#define IFFTransponderInterogatorIndicator__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO IFFTransponderInterogatorIndicator : public Enumeration {
  public:
    static IFFTransponderInterogatorIndicator TRANSPONDER;
    static IFFTransponderInterogatorIndicator INTERROGATOR;

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static IFFTransponderInterogatorIndicator getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,IFFTransponderInterogatorIndicator*> enumContainer;
    static enumContainer getEnumerations();

    IFFTransponderInterogatorIndicator& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  IFFTransponderInterogatorIndicator(int value, std::string description);

	  static IFFTransponderInterogatorIndicator* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* IFFTransponderInterogatorIndicator */


}  /* namespace DIS */ }

#endif  

