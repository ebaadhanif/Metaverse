#ifndef ARTICULATEDPARTSINDEXNUMBER__H
#define ARTICULATEDPARTSINDEXNUMBER__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO ArticulatedPartsIndexNumber : public Enumeration {
  public:
	static ArticulatedPartsIndexNumber NOT_SPECIFIED;
    static ArticulatedPartsIndexNumber RUDDER;
    static ArticulatedPartsIndexNumber LEFT_FLAP;
    static ArticulatedPartsIndexNumber RIGHT_FLAP;
    static ArticulatedPartsIndexNumber LEFT_AILERON;
    static ArticulatedPartsIndexNumber RIGHT_AILERON;
    static ArticulatedPartsIndexNumber HELICOPTER_MAIN_ROTOR;
    static ArticulatedPartsIndexNumber HELICOPTER_TAIL_ROTOR;
    static ArticulatedPartsIndexNumber OTHER_AIRCRAFT_CONTROL_SURFACES_DEFINED_AS_NEEDED;
	static ArticulatedPartsIndexNumber PROPELLER_NUMBER_1;
	static ArticulatedPartsIndexNumber PROPELLER_NUMBER_2;
	static ArticulatedPartsIndexNumber PROPELLER_NUMBER_3;
	static ArticulatedPartsIndexNumber PROPELLER_NUMBER_4;
	static ArticulatedPartsIndexNumber LEFT_STABILATOR;
	static ArticulatedPartsIndexNumber RIGHT_STABILATOR;
	static ArticulatedPartsIndexNumber LEFT_RUDDERVATOR;
	static ArticulatedPartsIndexNumber RIGHT_RUDDERVATOR;
	static ArticulatedPartsIndexNumber LEFT_LEADING_EDGE_FLAP_SLAT;
	static ArticulatedPartsIndexNumber RIGHT_LEADING_EDGE_FLAP_SLAT;
	static ArticulatedPartsIndexNumber LEFT_ELEVATOR;
	static ArticulatedPartsIndexNumber RIGHT_ELEVATOR;
    static ArticulatedPartsIndexNumber PERISCOPE;
    static ArticulatedPartsIndexNumber GENERIC_ANTENNA;
    static ArticulatedPartsIndexNumber SNORKEL;
    static ArticulatedPartsIndexNumber OTHER_EXTENDIBLE_PARTS_DEFINED_AS_NEEDED;
    static ArticulatedPartsIndexNumber LANDING_GEAR;
    static ArticulatedPartsIndexNumber TAIL_HOOK;
    static ArticulatedPartsIndexNumber SPEED_BRAKE;
    static ArticulatedPartsIndexNumber LEFT_WEAPON_BAY_DOOR;
    static ArticulatedPartsIndexNumber RIGHT_WEAPON_BAY_DOORS;
    static ArticulatedPartsIndexNumber TANK_OR_APC_HATCH;
    static ArticulatedPartsIndexNumber WINGSWEEP;
    static ArticulatedPartsIndexNumber BRIDGE_LAUNCHER;
    static ArticulatedPartsIndexNumber BRIDGE_SECTION_1;
    static ArticulatedPartsIndexNumber BRIDGE_SECTION_2;
    static ArticulatedPartsIndexNumber BRIDGE_SECTION_3;
    static ArticulatedPartsIndexNumber PRIMARY_BLADE_1;
    static ArticulatedPartsIndexNumber PRIMARY_BLADE_2;
    static ArticulatedPartsIndexNumber PRIMARY_BOOM;
    static ArticulatedPartsIndexNumber PRIMARY_LAUNCHER_ARM;
    static ArticulatedPartsIndexNumber OTHER_FIXED_POSITION_PARTS_DEFINED_AS_NEEDED;
	static ArticulatedPartsIndexNumber LANDING_GEAR_NOSE;
	static ArticulatedPartsIndexNumber LANDING_GEAR_LEFT_MAIN;
	static ArticulatedPartsIndexNumber LANDING_GEAR_RIGHT_MAIN;
	static ArticulatedPartsIndexNumber DOORS_LEFT_SIDE_WEAPON_BAY;
	static ArticulatedPartsIndexNumber DOORS_RIGHT_SIDE_WEAPON_BAY;
	static ArticulatedPartsIndexNumber SPOT_SEARCH_LIGHT_NUMBER_1;
	static ArticulatedPartsIndexNumber SPOT_SEARCH_LIGHT_NUMBER_2;
	static ArticulatedPartsIndexNumber SPOT_SEARCH_LIGHT_NUMBER_3;
	static ArticulatedPartsIndexNumber SPOT_SEARCH_LIGHT_NUMBER_4;
    static ArticulatedPartsIndexNumber PRIMARY_TURRET_NUMBER_1;
    static ArticulatedPartsIndexNumber PRIMARY_TURRET_NUMBER_2;
    static ArticulatedPartsIndexNumber PRIMARY_TURRET_NUMBER_3;
    static ArticulatedPartsIndexNumber PRIMARY_TURRET_NUMBER_4;
    static ArticulatedPartsIndexNumber PRIMARY_TURRET_NUMBER_5;
    static ArticulatedPartsIndexNumber PRIMARY_TURRET_NUMBER_6;
    static ArticulatedPartsIndexNumber PRIMARY_TURRET_NUMBER_7;
    static ArticulatedPartsIndexNumber PRIMARY_TURRET_NUMBER_8;
    static ArticulatedPartsIndexNumber PRIMARY_TURRET_NUMBER_9;
    static ArticulatedPartsIndexNumber PRIMARY_TURRET_NUMBER_10;
    static ArticulatedPartsIndexNumber PRIMARY_GUN_NUMBER_1;
    static ArticulatedPartsIndexNumber PRIMARY_GUN_NUMBER_2;
    static ArticulatedPartsIndexNumber PRIMARY_GUN_NUMBER_3;
    static ArticulatedPartsIndexNumber PRIMARY_GUN_NUMBER_4;
    static ArticulatedPartsIndexNumber PRIMARY_GUN_NUMBER_5;
    static ArticulatedPartsIndexNumber PRIMARY_GUN_NUMBER_6;
    static ArticulatedPartsIndexNumber PRIMARY_GUN_NUMBER_7;
    static ArticulatedPartsIndexNumber PRIMARY_GUN_NUMBER_8;
    static ArticulatedPartsIndexNumber PRIMARY_GUN_NUMBER_9;
    static ArticulatedPartsIndexNumber PRIMARY_GUN_NUMBER_10;
    static ArticulatedPartsIndexNumber PRIMARY_LAUNCHER_1;
    static ArticulatedPartsIndexNumber PRIMARY_LAUNCHER_2;
    static ArticulatedPartsIndexNumber PRIMARY_LAUNCHER_3;
    static ArticulatedPartsIndexNumber PRIMARY_LAUNCHER_4;
    static ArticulatedPartsIndexNumber PRIMARY_LAUNCHER_5;
    static ArticulatedPartsIndexNumber PRIMARY_LAUNCHER_6;
    static ArticulatedPartsIndexNumber PRIMARY_LAUNCHER_7;
    static ArticulatedPartsIndexNumber PRIMARY_LAUNCHER_8;
    static ArticulatedPartsIndexNumber PRIMARY_LAUNCHER_9;
    static ArticulatedPartsIndexNumber PRIMARY_LAUNCHER_10;
    static ArticulatedPartsIndexNumber PRIMARY_DEFENSE_SYSTEMS_1;
    static ArticulatedPartsIndexNumber PRIMARY_DEFENSE_SYSTEMS_2;
    static ArticulatedPartsIndexNumber PRIMARY_DEFENSE_SYSTEMS_3;
    static ArticulatedPartsIndexNumber PRIMARY_DEFENSE_SYSTEMS_4;
    static ArticulatedPartsIndexNumber PRIMARY_DEFENSE_SYSTEMS_5;
    static ArticulatedPartsIndexNumber PRIMARY_DEFENSE_SYSTEMS_6;
    static ArticulatedPartsIndexNumber PRIMARY_DEFENSE_SYSTEMS_7;
    static ArticulatedPartsIndexNumber PRIMARY_DEFENSE_SYSTEMS_8;
    static ArticulatedPartsIndexNumber PRIMARY_DEFENSE_SYSTEMS_9;
    static ArticulatedPartsIndexNumber PRIMARY_DEFENSE_SYSTEMS_10;
    static ArticulatedPartsIndexNumber PRIMARY_RADAR_1;
    static ArticulatedPartsIndexNumber PRIMARY_RADAR_2;
    static ArticulatedPartsIndexNumber PRIMARY_RADAR_3;
    static ArticulatedPartsIndexNumber PRIMARY_RADAR_4;
    static ArticulatedPartsIndexNumber PRIMARY_RADAR_5;
    static ArticulatedPartsIndexNumber PRIMARY_RADAR_6;
    static ArticulatedPartsIndexNumber PRIMARY_RADAR_7;
    static ArticulatedPartsIndexNumber PRIMARY_RADAR_8;
    static ArticulatedPartsIndexNumber PRIMARY_RADAR_9;
    static ArticulatedPartsIndexNumber PRIMARY_RADAR_10;
    static ArticulatedPartsIndexNumber SECONDARY_TURRET_NUMBER_1;
    static ArticulatedPartsIndexNumber SECONDARY_TURRET_NUMBER_2;
    static ArticulatedPartsIndexNumber SECONDARY_TURRET_NUMBER_3;
    static ArticulatedPartsIndexNumber SECONDARY_TURRET_NUMBER_4;
    static ArticulatedPartsIndexNumber SECONDARY_TURRET_NUMBER_5;
    static ArticulatedPartsIndexNumber SECONDARY_TURRET_NUMBER_6;
    static ArticulatedPartsIndexNumber SECONDARY_TURRET_NUMBER_7;
    static ArticulatedPartsIndexNumber SECONDARY_TURRET_NUMBER_8;
    static ArticulatedPartsIndexNumber SECONDARY_TURRET_NUMBER_9;
    static ArticulatedPartsIndexNumber SECONDARY_TURRET_NUMBER_10;
    static ArticulatedPartsIndexNumber SECONDARY_GUN_NUMBER_1;
    static ArticulatedPartsIndexNumber SECONDARY_GUN_NUMBER_2;
    static ArticulatedPartsIndexNumber SECONDARY_GUN_NUMBER_3;
    static ArticulatedPartsIndexNumber SECONDARY_GUN_NUMBER_4;
    static ArticulatedPartsIndexNumber SECONDARY_GUN_NUMBER_5;
    static ArticulatedPartsIndexNumber SECONDARY_GUN_NUMBER_6;
    static ArticulatedPartsIndexNumber SECONDARY_GUN_NUMBER_7;
    static ArticulatedPartsIndexNumber SECONDARY_GUN_NUMBER_8;
    static ArticulatedPartsIndexNumber SECONDARY_GUN_NUMBER_9;
    static ArticulatedPartsIndexNumber SECONDARY_GUN_NUMBER_10;
    static ArticulatedPartsIndexNumber SECONDARY_LAUNCHER_1;
    static ArticulatedPartsIndexNumber SECONDARY_LAUNCHER_2;
    static ArticulatedPartsIndexNumber SECONDARY_LAUNCHER_3;
    static ArticulatedPartsIndexNumber SECONDARY_LAUNCHER_4;
    static ArticulatedPartsIndexNumber SECONDARY_LAUNCHER_5;
    static ArticulatedPartsIndexNumber SECONDARY_LAUNCHER_6;
    static ArticulatedPartsIndexNumber SECONDARY_LAUNCHER_7;
    static ArticulatedPartsIndexNumber SECONDARY_LAUNCHER_8;
    static ArticulatedPartsIndexNumber SECONDARY_LAUNCHER_9;
    static ArticulatedPartsIndexNumber SECONDARY_LAUNCHER_10;
    static ArticulatedPartsIndexNumber SECONDARY_DEFENSE_SYSTEMS_1;
    static ArticulatedPartsIndexNumber SECONDARY_DEFENSE_SYSTEMS_2;
    static ArticulatedPartsIndexNumber SECONDARY_DEFENSE_SYSTEMS_3;
    static ArticulatedPartsIndexNumber SECONDARY_DEFENSE_SYSTEMS_4;
    static ArticulatedPartsIndexNumber SECONDARY_DEFENSE_SYSTEMS_5;
    static ArticulatedPartsIndexNumber SECONDARY_DEFENSE_SYSTEMS_6;
    static ArticulatedPartsIndexNumber SECONDARY_DEFENSE_SYSTEMS_7;
    static ArticulatedPartsIndexNumber SECONDARY_DEFENSE_SYSTEMS_8;
    static ArticulatedPartsIndexNumber SECONDARY_DEFENSE_SYSTEMS_9;
    static ArticulatedPartsIndexNumber SECONDARY_DEFENSE_SYSTEMS_10;
    static ArticulatedPartsIndexNumber SECONDARY_RADAR_1;
    static ArticulatedPartsIndexNumber SECONDARY_RADAR_2;
    static ArticulatedPartsIndexNumber SECONDARY_RADAR_3;
    static ArticulatedPartsIndexNumber SECONDARY_RADAR_4;
    static ArticulatedPartsIndexNumber SECONDARY_RADAR_5;
    static ArticulatedPartsIndexNumber SECONDARY_RADAR_6;
    static ArticulatedPartsIndexNumber SECONDARY_RADAR_7;
    static ArticulatedPartsIndexNumber SECONDARY_RADAR_8;
    static ArticulatedPartsIndexNumber SECONDARY_RADAR_9;
    static ArticulatedPartsIndexNumber SECONDARY_RADAR_10;
    static ArticulatedPartsIndexNumber DECK_ELEVATOR_1;
    static ArticulatedPartsIndexNumber DECK_ELEVATOR_2;
    static ArticulatedPartsIndexNumber CATAPULT_1;
    static ArticulatedPartsIndexNumber CATAPULT_2;
    static ArticulatedPartsIndexNumber JET_BLAST_DEFLECTOR_1;
    static ArticulatedPartsIndexNumber JET_BLAST_DEFLECTOR_2;
    static ArticulatedPartsIndexNumber ARRESTOR_WIRES_1;
    static ArticulatedPartsIndexNumber ARRESTOR_WIRES_2;
    static ArticulatedPartsIndexNumber ARRESTOR_WIRES_3;
    static ArticulatedPartsIndexNumber WING_OR_ROTOR_FOLD;
    static ArticulatedPartsIndexNumber FUSELAGE_FOLD;
	static ArticulatedPartsIndexNumber MAIN_CARGO_DOOR;
	static ArticulatedPartsIndexNumber CARGO_RAMP;
	static ArticulatedPartsIndexNumber AIR_TO_AIR_REFUELING_BOOM;
	static ArticulatedPartsIndexNumber PRIMARY_AERIAL_REFUELING_RECEPTACLE_DOOR;
	static ArticulatedPartsIndexNumber SECONDARY_AERIAL_REFUELING_RECEPTACLE_DOOR;
	static ArticulatedPartsIndexNumber AERIAL_REFUELING_RECEPTACLE_LATCH;
	static ArticulatedPartsIndexNumber CARGO_DOOR_NUMBER_1;
	static ArticulatedPartsIndexNumber CARGO_DOOR_NUMBER_2;
	static ArticulatedPartsIndexNumber CARGO_DOOR_NUMBER_3;
	static ArticulatedPartsIndexNumber CARGO_DOOR_NUMBER_4;
	static ArticulatedPartsIndexNumber CARGO_DOOR_NUMBER_5;
	static ArticulatedPartsIndexNumber CARGO_DOOR_NUMBER_6;
	static ArticulatedPartsIndexNumber CARGO_DOOR_NUMBER_7;
	static ArticulatedPartsIndexNumber CARGO_DOOR_NUMBER_8;
	static ArticulatedPartsIndexNumber CARGO_DOOR_NUMBER_9;
	static ArticulatedPartsIndexNumber CARGO_DOOR_NUMBER_10;
	static ArticulatedPartsIndexNumber CENTRE_REFUELLING_DROGUE;
	static ArticulatedPartsIndexNumber PORT_REFUELLING_DROGUE;
	static ArticulatedPartsIndexNumber STARBOARD_REFUELLING_DROGUE;
	static ArticulatedPartsIndexNumber SUBMARINE_ENGINE_EXHAUST_MAST;
	static ArticulatedPartsIndexNumber SUBMARINE_MAST_NUMBER_1;
	static ArticulatedPartsIndexNumber SUBMARINE_MAST_NUMBER_2;
	static ArticulatedPartsIndexNumber SUBMARINE_MAST_NUMBER_3;
	static ArticulatedPartsIndexNumber SUBMARINE_MAST_NUMBER_4;
	static ArticulatedPartsIndexNumber SUBMARINE_MAST_NUMBER_5;
	static ArticulatedPartsIndexNumber SUBMARINE_MAST_NUMBER_6;
	static ArticulatedPartsIndexNumber SUBMARINE_MAST_NUMBER_7;
	static ArticulatedPartsIndexNumber SUBMARINE_MAST_NUMBER_8;
	static ArticulatedPartsIndexNumber SUBMARINE_MAST_NUMBER_9;
	static ArticulatedPartsIndexNumber SUBMARINE_MAST_NUMBER_10;
	static ArticulatedPartsIndexNumber VECTORED_THRUST_NOZZLE;
	static ArticulatedPartsIndexNumber LEFT_DOOR_OF_THE_LEFT_WEAPON_BAY;
	static ArticulatedPartsIndexNumber RIGHT_DOOR_OF_THE_LEFT_WEAPON_BAY;
	static ArticulatedPartsIndexNumber LEFT_DOOR_OF_THE_RIGHT_WEAPON_BAY;
	static ArticulatedPartsIndexNumber RIGHT_DOOR_OF_THE_RIGHT_WEAPON_BAY;
	static ArticulatedPartsIndexNumber GUN_DOOR;
	static ArticulatedPartsIndexNumber COUNTERMEASURE_DOOR_LEFT;
	static ArticulatedPartsIndexNumber COUNTERMEASURE_DOOR_RIGHT;
	static ArticulatedPartsIndexNumber HOOK_DOOR_FORWARD;
	static ArticulatedPartsIndexNumber HOOK_DOOR_AFT;
	static ArticulatedPartsIndexNumber LIFT_FAN_UPPER_DOOR;
	static ArticulatedPartsIndexNumber LIFT_FAN_LOWER_DOOR_LEFT;
	static ArticulatedPartsIndexNumber LIFT_FAN_LOWER_DOOR_RIGHT;
	static ArticulatedPartsIndexNumber REFUEL_PROBE_DOOR;
	static ArticulatedPartsIndexNumber LEFT_ENGINE_NACELLE;
	static ArticulatedPartsIndexNumber RIGHT_ENGINE_NACELLE;
	static ArticulatedPartsIndexNumber LEFT_WHEEL_1ST;
	static ArticulatedPartsIndexNumber RIGHT_WHEEL_1ST;
	static ArticulatedPartsIndexNumber LEFT_WHEEL_2ND;
	static ArticulatedPartsIndexNumber RIGHT_WHEEL_2ND;
	static ArticulatedPartsIndexNumber LEFT_WHEEL_3RD;
	static ArticulatedPartsIndexNumber RIGHT_WHEEL_3RD;
	static ArticulatedPartsIndexNumber LEFT_WHEEL_4TH;
	static ArticulatedPartsIndexNumber RIGHT_WHEEL_4TH;
	static ArticulatedPartsIndexNumber LEFT_WHEEL_5TH;
	static ArticulatedPartsIndexNumber RIGHT_WHEEL_5TH;
	static ArticulatedPartsIndexNumber LEFT_WHEEL_6TH;
	static ArticulatedPartsIndexNumber RIGHT_WHEEL_6TH;
	static ArticulatedPartsIndexNumber LEFT_WHEEL_7TH;
	static ArticulatedPartsIndexNumber RIGHT_WHEEL_7TH;
	static ArticulatedPartsIndexNumber LEFT_WHEEL_8TH;
	static ArticulatedPartsIndexNumber RIGHT_WHEEL_8TH;
	static ArticulatedPartsIndexNumber LEFT_WHEEL_9TH;
	static ArticulatedPartsIndexNumber RIGHT_WHEEL_9TH;
	static ArticulatedPartsIndexNumber LEFT_WHEEL_10TH;
	static ArticulatedPartsIndexNumber RIGHT_WHEEL_10TH;

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static ArticulatedPartsIndexNumber getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,ArticulatedPartsIndexNumber*> enumContainer;
    static enumContainer getEnumerations();

    ArticulatedPartsIndexNumber& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  ArticulatedPartsIndexNumber(int value, std::string description);

	  static ArticulatedPartsIndexNumber* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* ArticulatedPartsIndexNumber */


}  /* namespace DIS */ }

#endif /* ARTICULATEDPARTSINDEXNUMBER__H */

