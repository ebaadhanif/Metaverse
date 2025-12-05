#ifndef REPAIRRESPONSE__H
#define REPAIRRESPONSE__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO RepairResponse : public Enumeration {
  public:
    static RepairResponse OTHER;
    static RepairResponse REPAIR_ENDED;
    static RepairResponse INVALID_REPAIR;
    static RepairResponse REPAIR_INTERRUPTED;
    static RepairResponse SERVICE_CANCELED_BY_THE_SUPPLIER;
    

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static RepairResponse getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int, RepairResponse*> enumContainer;
    static enumContainer getEnumerations();

	RepairResponse& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  RepairResponse(int value, std::string description);

	  static RepairResponse* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* RepairResponsePDU */


}  /* namespace DIS */ }

#endif /* REPAIRRESPONSEPDU__H */

