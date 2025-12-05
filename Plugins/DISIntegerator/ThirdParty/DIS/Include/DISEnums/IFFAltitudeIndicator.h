#ifndef IFFAltitudeIndicator__H
#define IFFAltitudeIndicator__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO IFFAltitudeIndicator : public Enumeration {
  public:
    static IFFAltitudeIndicator POSITIVE_ABOVE_MSL;
    static IFFAltitudeIndicator NEGATIVE_BELOW_MSL;

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static IFFAltitudeIndicator getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,IFFAltitudeIndicator*> enumContainer;
    static enumContainer getEnumerations();

    IFFAltitudeIndicator& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  IFFAltitudeIndicator(int value, std::string description);

	  static IFFAltitudeIndicator* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* IFFAltitudeIndicator */
}  /* namespace DIS */ }

#endif  

