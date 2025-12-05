#ifndef PAKISTAN_Articulated_Parameters_H
#define PAKISTAN_Articulated_Parameters_H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace AFISE { namespace PAKISTAN { namespace ArticulatedParameters { namespace Type {

class EXPORT_MACRO Articulated_Parameters : public Enumeration {
  public:
    static Articulated_Parameters OTHER;
	static Articulated_Parameters CHAFF;
	static Articulated_Parameters FLARE;
	static Articulated_Parameters GUN;
	static Articulated_Parameters AIM_9_SIDEWINDER;
	static Articulated_Parameters AIM_120_AMRAAM;
	static Articulated_Parameters ASPIDE_2000_SAM;
	static Articulated_Parameters GBU_32;
	static Articulated_Parameters GBU_38;


	
    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(unsigned short aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static Articulated_Parameters getEnumerationForValue(unsigned short aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(unsigned short aVal);

    typedef hashMap<unsigned short, Articulated_Parameters*> enumContainer;
    static enumContainer getEnumerations();

    Articulated_Parameters& operator=(const unsigned short& aVal) throw(EnumException);

  private:
    /** Constructor */
	  Articulated_Parameters(unsigned short aVal, std::string description);

	static Articulated_Parameters* findEnumeration(unsigned short aVal);
    static enumContainer enumerations;

};  /* ActionID */


}  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ }

#endif  