#ifndef IFFChangeOptionsType__H
#define IFFChangeOptionsType__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO IFFChangeOptionsType : public Enumeration {
  public:
    static IFFChangeOptionsType NO;
    static IFFChangeOptionsType TIME;
    static IFFChangeOptionsType CHANGE;
  
    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static IFFChangeOptionsType getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,IFFChangeOptionsType*> enumContainer;
    static enumContainer getEnumerations();

    IFFChangeOptionsType& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  IFFChangeOptionsType(int value, std::string description);

	  static IFFChangeOptionsType* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* IFFChangeOptionsType */
}  /* namespace DIS */ }

#endif  

