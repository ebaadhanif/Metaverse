#ifndef TransferredEntityIndicator__H
#define TransferredEntityIndicator__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO TransferredEntityIndicator : public Enumeration {
  public:
    static TransferredEntityIndicator NO_DIFFERENCE;
    static TransferredEntityIndicator DIFFRENCE;

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static TransferredEntityIndicator getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,TransferredEntityIndicator*> enumContainer;
    static enumContainer getEnumerations();

    TransferredEntityIndicator& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  TransferredEntityIndicator(int value, std::string description);

	  static TransferredEntityIndicator* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* TransferredEntityIndicator */
}  /* namespace DIS */ }

#endif  

