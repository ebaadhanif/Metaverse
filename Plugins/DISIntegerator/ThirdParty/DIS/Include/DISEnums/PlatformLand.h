#ifndef PLATFORMLAND__H
#define PLATFORMLAND__H

//Updated by Farhan Mirza on 15 Dec, 2017 as per DIS 7

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO PlatformLand : public Enumeration {
  public:
    static PlatformLand OTHER;
    static PlatformLand TANK;
    static PlatformLand ARMORED_FIGHTING_VEHICLE;
    static PlatformLand ARMORED_UTILITY_VEHICLE;
    static PlatformLand SELF_PROPELLED_ARTILLERY;
    static PlatformLand TOWED_ARTILLERY;
    static PlatformLand SMALL_WHEELED_UTILITY_VEHICLE;
    static PlatformLand LARGE_WHEELED_UTILITY_VEHICLE;
    static PlatformLand SMALL_TRACKED_UTILITY_VEHICLE;
    static PlatformLand LARGE_TRACKED_UTILITY_VEHICLE;
    static PlatformLand MORTAR;
    static PlatformLand MINE_PLOW;
    static PlatformLand MINE_RAKE;
    static PlatformLand MINE_ROLLER;
    static PlatformLand CARGO_TRAILER;
    static PlatformLand FUEL_TRAILER;
    static PlatformLand GENERATOR_TRAILER;
    static PlatformLand WATER_TRAILER;
    static PlatformLand ENGINEER_EQUIPMENT;
    static PlatformLand HEAVY_EQUIPMENT_TRANSPORT_TRAILER;
    static PlatformLand MAINTENANCE_EQUIPMENT_TRAILER;
    static PlatformLand LIMBER;
    static PlatformLand CHEMICAL_DECONTAMINATION_TRAILER;
    static PlatformLand WARNING_SYSTEM;
    static PlatformLand TRAIN_ENGINE;
    static PlatformLand TRAIN_CAR;
    static PlatformLand TRAIN_CABOOSE;
    static PlatformLand CIVILIAN_VEHICLE_DEPRECATED;
    static PlatformLand AIR_DEFENSE_MISSILE_DEFENSE_UNIT_EQUIPMENT;
    static PlatformLand COMMAND_CONTROL_COMMUNICATIONS_AND_INTELLIGENCE_C3I_SYSTEM;
    static PlatformLand OPERATIONS_FACILITY;
    static PlatformLand INTELLIGENCE_FACILITY;
    static PlatformLand SURVEILLANCE_FACILITY;
    static PlatformLand COMMUNICATIONS_FACILITY;
    static PlatformLand COMMAND_FACILITY;
    static PlatformLand C4I_FACILITY;
    static PlatformLand CONTROL_FACILITY;
    static PlatformLand FIRE_CONTROL_FACILITY;
    static PlatformLand MISSILE_DEFENSE_FACILITY;
    static PlatformLand FIELD_COMMAND_POST;
    static PlatformLand OBSERVATION_POST;
	static PlatformLand UNMANNED;
	static PlatformLand MOTORCYCLE;
	static PlatformLand CAR;
	static PlatformLand BUS;
	static PlatformLand SINGLE_UNIT_CARGO_TRUCK;
	static PlatformLand SINGLE_UNIT_UTILITY_EMERGENCY_TRUCK;
	static PlatformLand MULTIPLE_UNIT_CARGO_TRUCK;
	static PlatformLand MULTIPLE_UNIT_UTILITY_EMERGENCY_TRUCK;
	static PlatformLand CONSTRUCTION_SPECIALITY_VEHICLE;
	static PlatformLand FARM_SPECIALITY_VEHICLE;
	static PlatformLand TRAILER;
	static PlatformLand RECREATIONAL;
	static PlatformLand NON_MOTORIZED;
	static PlatformLand TRAINS;
	static PlatformLand UTILITY_EMERGENCY_CAR;
    
    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static PlatformLand getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,PlatformLand*> enumContainer;
    static enumContainer getEnumerations();

    PlatformLand& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  PlatformLand(int value, std::string description);

	  static PlatformLand* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* PlatformLand */


}  /* namespace DIS */ }

#endif /* PLATFORMLAND__H */

