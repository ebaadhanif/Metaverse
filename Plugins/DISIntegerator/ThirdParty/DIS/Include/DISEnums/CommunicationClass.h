#ifndef COMMUNICATIONCLASS__H
#define COMMUNICATIONCLASS__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO CommunicationClass : public Enumeration {
  public:
    static CommunicationClass SIMULATED_COMMUNICATIONS_CHANNEL;
    static CommunicationClass SIMULATED_SUPPORT_COMMUNICATIONS_CHANNEL;

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static CommunicationClass getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,CommunicationClass*> enumContainer;
    static enumContainer getEnumerations();

    CommunicationClass& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  CommunicationClass(int value, std::string description);

	  static CommunicationClass* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* CommunicationClass */


}  /* namespace DIS */ }

#endif /* COMMUNICATIONCLASS__H */

