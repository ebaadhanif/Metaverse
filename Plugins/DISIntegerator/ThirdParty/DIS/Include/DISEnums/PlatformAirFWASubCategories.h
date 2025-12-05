#ifndef PLATFORMAIR_FIXEDWINGAIRCRAFT_SUBCATEGORIES__H
#define PLATFORMAIR_FIXEDWINGAIRCRAFT_SUBCATEGORIES__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO PlatformAirFWASubCategories : public Enumeration {
  public:
    static PlatformAirFWASubCategories OTHER;
    static PlatformAirFWASubCategories SINGLE_PISTON_ENGINE;
    static PlatformAirFWASubCategories TWIN_PISTON_ENGINE;
    static PlatformAirFWASubCategories SINGLE_ENGINE_TURBOPROP;
    static PlatformAirFWASubCategories TWIN_ENGINE_TURBOPROP;
    static PlatformAirFWASubCategories FOUR_ENGINE_TURBOPROP;
    static PlatformAirFWASubCategories TWIN_JET;
    static PlatformAirFWASubCategories TRI_JET;
	static PlatformAirFWASubCategories FOUR_ENGINE_JET;

 
	
    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static PlatformAirFWASubCategories getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,PlatformAirFWASubCategories*> enumContainer;
    static enumContainer getEnumerations();

    PlatformAirFWASubCategories& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  PlatformAirFWASubCategories(int value, std::string description);

	  static PlatformAirFWASubCategories* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* PlatformAirFWASubCategories */


}  /* namespace DIS */ }

#endif /* PLATFORMAIR_FIXEDWINGAIRCRAFT_SUBCATEGORIES__H */

