#ifndef PAKISTAN_SENSOR_EMITTER_SubCat_H
#define PAKISTAN_SENSOR_EMITTER_SubCat_H
#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace AFISE { namespace PAKISTAN { namespace LAND { namespace SPECIFIC {

class EXPORT_MACRO Land_Specific_Sensor_Emitter : public Enumeration {
  public:
    static Land_Specific_Sensor_Emitter OTHER;
	static Land_Specific_Sensor_Emitter MPDR_45;
	static Land_Specific_Sensor_Emitter MPDR_60;
	static Land_Specific_Sensor_Emitter MPDR_90;
	static Land_Specific_Sensor_Emitter TPS_43G;
	static Land_Specific_Sensor_Emitter YLC_2;
	static Land_Specific_Sensor_Emitter YLC_6;
	static Land_Specific_Sensor_Emitter TPS_77;
	static Land_Specific_Sensor_Emitter ATCR;
    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(unsigned short aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static Land_Specific_Sensor_Emitter getEnumerationForValue(unsigned short aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(unsigned short aVal);

    typedef hashMap<unsigned short, Land_Specific_Sensor_Emitter*> enumContainer;
    static enumContainer getEnumerations();

    Land_Specific_Sensor_Emitter& operator=(const unsigned short& aVal) throw(EnumException);

  private:
    /** Constructor */
	  Land_Specific_Sensor_Emitter(unsigned short aVal, std::string description);

	static Land_Specific_Sensor_Emitter* findEnumeration(unsigned short aVal);
    static enumContainer enumerations;

};  /* ActionID */


}  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ }

#endif  