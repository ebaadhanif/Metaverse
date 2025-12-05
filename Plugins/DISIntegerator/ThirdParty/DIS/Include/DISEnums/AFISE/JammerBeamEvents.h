#ifndef JammerBeamEvents__H
#define JammerBeamEvents__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace AFISE {

class EXPORT_MACRO JammerBeamEvents : public Enumeration {
  public:
    static JammerBeamEvents OTHER;
    static JammerBeamEvents FRONT;
	static JammerBeamEvents REAR;

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(unsigned short aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static JammerBeamEvents getEnumerationForValue(unsigned short aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(unsigned short aVal);

    typedef hashMap<unsigned short, JammerBeamEvents*> enumContainer;
    static enumContainer getEnumerations();

    JammerBeamEvents& operator=(const unsigned short& aVal) throw(EnumException);

  private:
    /** Constructor */
	  JammerBeamEvents(unsigned short aVal, std::string description);

	static JammerBeamEvents* findEnumeration(unsigned short aVal);
    static enumContainer enumerations;

};  /* ActionID */


}  /* namespace DIS */ } /* namespace DIS */ }
#endif  