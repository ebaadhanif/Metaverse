#ifndef SERVICEREQUEST__H
#define SERVICEREQUEST__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO ServiceRequest : public Enumeration {
  public:
    static ServiceRequest OTHER;
    static ServiceRequest RESUPPLY;
    static ServiceRequest REPAIR;
	static ServiceRequest AERIAL_REFUELING_HIGH_FIDELITY;
	static ServiceRequest AERIAL_REFUELING_LOW_FIDELITY;
    

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static ServiceRequest getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int, ServiceRequest*> enumContainer;
    static enumContainer getEnumerations();

	ServiceRequest& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  ServiceRequest(int value, std::string description);

	  static ServiceRequest* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* ServiceRequestPDU */


}  /* namespace DIS */ }

#endif /* SERVICEREQUESTPDU__H */

