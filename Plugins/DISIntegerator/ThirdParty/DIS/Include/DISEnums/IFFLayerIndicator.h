#ifndef IFFLayerIndicator__H
#define IFFLayerIndicator__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO IFFLayerIndicator : public Enumeration {
  public:
    static IFFLayerIndicator NOT_PRESENT;
    static IFFLayerIndicator PRESENT;

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static IFFLayerIndicator getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,IFFLayerIndicator*> enumContainer;
    static enumContainer getEnumerations();

    IFFLayerIndicator& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  IFFLayerIndicator(int value, std::string description);

	  static IFFLayerIndicator* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* IFFLayerIndicator */
}  /* namespace DIS */ }

#endif  

