#ifndef IFFSimulationMode__H
#define IFFSimulationMode__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO IFFSimulationMode : public Enumeration {
  public:
    static IFFSimulationMode REGENERATION;
    static IFFSimulationMode INTERACTIVE;

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static IFFSimulationMode getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,IFFSimulationMode*> enumContainer;
    static enumContainer getEnumerations();

    IFFSimulationMode& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  IFFSimulationMode(int value, std::string description);

	  static IFFSimulationMode* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* IFFSimulationMode */
}  /* namespace DIS */ }

#endif  

