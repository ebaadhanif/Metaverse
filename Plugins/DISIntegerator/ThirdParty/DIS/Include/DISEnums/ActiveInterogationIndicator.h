#ifndef ACTIVEInterogationIndicator__H
#define ACTIVEInterogationIndicator__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO ACTIVEInterogationIndicator : public Enumeration {
  public:
    static ACTIVEInterogationIndicator NOT_ACTIVE;
    static ACTIVEInterogationIndicator ACTIVE;

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static ACTIVEInterogationIndicator getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,ACTIVEInterogationIndicator*> enumContainer;
    static enumContainer getEnumerations();

    ACTIVEInterogationIndicator& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  ACTIVEInterogationIndicator(int value, std::string description);

	  static ACTIVEInterogationIndicator* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* ACTIVEInterogationIndicator */
}  /* namespace DIS */ }

#endif  

