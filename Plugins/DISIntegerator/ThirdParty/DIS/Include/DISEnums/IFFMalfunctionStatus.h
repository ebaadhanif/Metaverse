#ifndef IFFMalfunctionStatus__H
#define IFFMalfunctionStatus__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO IFFMalfunctionStatus : public Enumeration {
  public:
    static IFFMalfunctionStatus NO_MALFUNCTION;
    static IFFMalfunctionStatus MALFUNCTION;

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static IFFMalfunctionStatus getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,IFFMalfunctionStatus*> enumContainer;
    static enumContainer getEnumerations();

    IFFMalfunctionStatus& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  IFFMalfunctionStatus(int value, std::string description);

	  static IFFMalfunctionStatus* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* IFFMalfunctionStatus */
}  /* namespace DIS */ }

#endif  

