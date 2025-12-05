#ifndef RADAR___H
#define RADAR___H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO RADAR_ : public Enumeration {
  public:
    static RADAR_ GENERIC;
    static RADAR_ GENERIC_GPR;
    static RADAR_ GSTAMIDS_I;
    static RADAR_ GSTAMIDS_II;
    static RADAR_ HSTAMIDS_I;
    static RADAR_ HSTAMIDS_II;
    

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static RADAR_ getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,RADAR_*> enumContainer;
    static enumContainer getEnumerations();

    RADAR_& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  RADAR_(int value, std::string description);

	  static RADAR_* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* RADAR_ */


}  /* namespace DIS */ }

#endif /* RADAR___H */

