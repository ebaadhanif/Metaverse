#ifndef EmitterSystemFunction__H
#define EmitterSystemFunction__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO EmitterSystemFunction : public Enumeration {
  public:
    static EmitterSystemFunction OTHER;
    static EmitterSystemFunction MULTI_FUNCTION;
	static EmitterSystemFunction EARLY_WARNING_SURVEILLANCE;
	static EmitterSystemFunction HEIGHT_FINDER;
	static EmitterSystemFunction FIRE_CONTROL;
	static EmitterSystemFunction ACQUISITION_DETECTION;
	static EmitterSystemFunction TRACKER;
	static EmitterSystemFunction GUIDANCE_ILLUMINATION;
	static EmitterSystemFunction FIRING_POINT_LAUNCH_POINT_LOCATION;
	static EmitterSystemFunction RANGE_ONLY;
	static EmitterSystemFunction RADAR_ALTIMETER;
	static EmitterSystemFunction IMAGING;
	static EmitterSystemFunction MOTION_DETECTION;
	static EmitterSystemFunction NAVIGATION;
	static EmitterSystemFunction WEATHER_METEROLOGICAL;
	static EmitterSystemFunction INSTRUMENTATION;
	static EmitterSystemFunction IDENTIFICATION_CLASSIFICATION_INCLUDING_IFF;
	static EmitterSystemFunction AAA_ANTI_AIRCRAFT_ARTILLERY_FIRE_CONTROL;
	static EmitterSystemFunction AIR_SEARCH_BOMB;
	static EmitterSystemFunction AIR_INTERCEPT;
	static EmitterSystemFunction ALTIMETER;
	static EmitterSystemFunction AIR_MAPPING;
	static EmitterSystemFunction AIR_TRAFFIC_CONTROL;
	static EmitterSystemFunction BEACON;
	static EmitterSystemFunction BATTLEFIELD_SURVEILLANCE;
	static EmitterSystemFunction GROUND_CONTROL_APPROACH;
	static EmitterSystemFunction GROUND_CONTROL_INTERCEPT;
	static EmitterSystemFunction COASTAL_SURVEILLANCE;
	static EmitterSystemFunction DECOY_MIMIC;
	static EmitterSystemFunction DATA_TRANSMISSION;
	static EmitterSystemFunction EARTH_SURVEILLANCE;
	static EmitterSystemFunction GUN_LAY_BEACON;
	static EmitterSystemFunction GROUND_MAPPING;
	static EmitterSystemFunction HARBOR_SURVEILLANCE;
	static EmitterSystemFunction IFF_DEPRECATED;
	static EmitterSystemFunction ILS_INSTRUMENT_LANDING_SYSTEM;
	static EmitterSystemFunction IONOSPHERIC_SOUND;
	static EmitterSystemFunction INTERROGATOR;
	static EmitterSystemFunction BARRAGE_JAMMING_DEPRECATED;
	static EmitterSystemFunction CLICK_JAMMING_DEPRECATED;
	static EmitterSystemFunction DECEPTIVE_JAMMING_DEPRECATED;
	static EmitterSystemFunction FREQUENCY_SWEPT_JAMMING_DEPRECATED;
	static EmitterSystemFunction JAMMER;
	static EmitterSystemFunction NOISE_JAMMING_DEPRECATED;
	static EmitterSystemFunction PULSED_JAMMING_DEPRECATED;
	static EmitterSystemFunction REPEATER_JAMMING_DEPRECATED;
	static EmitterSystemFunction SPOT_NOISE_JAMMING_DEPRECATED;
	static EmitterSystemFunction MISSILE_ACQUISITION;
	static EmitterSystemFunction MISSILE_DOWNLINK;
	static EmitterSystemFunction METEOROLOGICAL_DEPRECATED;
	static EmitterSystemFunction SPACE;
	static EmitterSystemFunction SURFACE_SEARCH;
	static EmitterSystemFunction SHELL_TRACKING;
	static EmitterSystemFunction TELEVISION;
	static EmitterSystemFunction UNKNOWN;
	static EmitterSystemFunction VIDEO_REMOTING;
	static EmitterSystemFunction EXPERIMENTAL_OR_TRAINING;
	static EmitterSystemFunction MISSILE_GUIDANCE;
	static EmitterSystemFunction MISSILE_HOMING;
	static EmitterSystemFunction MISSILE_TRACKING;
	static EmitterSystemFunction JAMMING_NOISE_DEPRECATED;
	static EmitterSystemFunction JAMMING_DECEPTION_DEPRECATED;
	static EmitterSystemFunction DECOY_DEPRECATED;
	static EmitterSystemFunction NAVIGATION_DISTANCE_MEASURING_EQUIPMENT;
	static EmitterSystemFunction TERRAIN_FOLLOWING;
	static EmitterSystemFunction WEATHER_AVOIDANCE;
	static EmitterSystemFunction PROXIMITY_FUSE;
	static EmitterSystemFunction INSTRUMENTATION_DEPRECATED;
	static EmitterSystemFunction RADIOSONDE;
	static EmitterSystemFunction SONOBUOY;
	static EmitterSystemFunction BATHYTHERMAL_SENSOR;
	static EmitterSystemFunction TOWED_COUNTER_MEASURE;
	static EmitterSystemFunction WEAPON_NON_LETHAL;
	static EmitterSystemFunction WEAPON_LETHAL;
    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(unsigned short aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static EmitterSystemFunction getEnumerationForValue(unsigned short aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(unsigned short aVal);

    typedef hashMap<unsigned short, EmitterSystemFunction*> enumContainer;
    static enumContainer getEnumerations();

    EmitterSystemFunction& operator=(const unsigned short& aVal) throw(EnumException);

  private:
    /** Constructor */
	  EmitterSystemFunction(unsigned short aVal, std::string description);

	static EmitterSystemFunction* findEnumeration(unsigned short aVal);
    static enumContainer enumerations;

};  /* ActionID */


}  /* namespace DIS */ }
#endif  