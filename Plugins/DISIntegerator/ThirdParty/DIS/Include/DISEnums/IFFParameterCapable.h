#ifndef IFFParameterCapable__H
#define IFFParameterCapable__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO IFFParameterCapable : public Enumeration {
  public:
    static IFFParameterCapable CAPABLE;
    static IFFParameterCapable NOT_CAPABLE;
 
    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static IFFParameterCapable getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,IFFParameterCapable*> enumContainer;
    static enumContainer getEnumerations();

    IFFParameterCapable& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  IFFParameterCapable(int value, std::string description);

	  static IFFParameterCapable* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* IFFParameterCapable */


}  /* namespace DIS */ }

#endif  

