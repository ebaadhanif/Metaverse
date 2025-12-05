#ifndef ES_APPEAR_PLATFORM_AIR__H
#define ES_APPEAR_PLATFORM_AIR__H

//Updated by Farhan on  22 March, 2018.
//Added EXPORT MACRO with bitmask struct to export to dll
//Enumerations updated w.r.t. DIS v7

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

namespace es_appear_platform_air {

	/** Bitmask declaration **/
	struct EXPORT_MACRO bitmask 
	{

		unsigned int PaintScheme : 1;
		unsigned int Propulsion : 1;
		unsigned int NVGMode : 1;
		unsigned int Damage : 2;
		unsigned int IsEntityEmittingSmoke : 1;
		unsigned int IsEngineEmittingSmoke : 1;
		unsigned int TrailingEffects : 2;
		unsigned int Canopy_TroopDoor : 3;
		unsigned int LandingLightsOn : 1;
		unsigned int NavigationLightsOn : 1;
		unsigned int Anti_CollisionLightsOn : 1;
		unsigned int IsFlaming : 1;
		unsigned int AfterburnerOn : 1;
		unsigned int LowerAnti_CollisionLightOn : 1;
		unsigned int UpperAnti_CollisionLightOn : 1;
		unsigned int Anti_CollisionLightDayNight : 1;
		unsigned int IsBlinking : 1;
		unsigned int IsFrozen : 1;
		unsigned int PowerPlantOn : 1;
		unsigned int State : 1;
		unsigned int FormationLightsOn : 1;
		unsigned int LandingGearExtended : 1;
		unsigned int CargoDoorsOpened : 1;
		unsigned int NavigationPositionBrightness : 1;
		unsigned int SpotSearchLightNumber1On  : 1;
		unsigned int InteriorLightsOn : 1;
		unsigned int ReverseThrustEngaged : 1;
		unsigned int WeightOnWheels : 1;


		bitmask& operator=(const unsigned int& i);
		bitmask(const unsigned int& i);
		bitmask();
		unsigned int getValue();
		void  setValue(const unsigned int& i);
	};

	/** Enumerations declaration **/
	class EXPORT_MACRO PaintScheme : public Enumeration {
  public:
    static PaintScheme UNIFORM_COLOR;
    static PaintScheme CAMOUFLAGE;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static PaintScheme getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int,PaintScheme*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		PaintScheme(int value, std::string description);

		static PaintScheme* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* PaintScheme */

	class EXPORT_MACRO Propulsion : public Enumeration {
  public:
    static Propulsion NO_PROPULSION_KILL;
    static Propulsion PROPULSION_KILL;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static Propulsion getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int,Propulsion*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		Propulsion(int value, std::string description);

		static Propulsion* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* Propulsion */

	class EXPORT_MACRO NVGMode : public Enumeration {
	public:
		static NVGMode OVERT_LIGHTING;
		static NVGMode COVERT_LIGHTING_NVG_GOGGLES;

		/** Returns the string description associated with the enumerated instance with this value.
		* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		* If there is no enumerated instance for this value, the exception is thrown.     */
		static NVGMode getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, NVGMode*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit() { return endBit; };


	private:
		/** Constructor */
		NVGMode(int value, std::string description);

		static NVGMode* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* Propulsion */

	class EXPORT_MACRO Damage : public Enumeration {
  public:
    static Damage NO_DAMAGE;
    static Damage SLIGHT_DAMAGE;
    static Damage MODERATE_DAMAGE;
    static Damage DESTROYED;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static Damage getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int,Damage*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		Damage(int value, std::string description);

		static Damage* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* Damage */

	class EXPORT_MACRO IsEntityEmittingSmoke : public Enumeration {
  public:
    static IsEntityEmittingSmoke NOT_SMOKING;
    static IsEntityEmittingSmoke SMOKING;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static IsEntityEmittingSmoke getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, IsEntityEmittingSmoke*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		IsEntityEmittingSmoke(int value, std::string description);

		static IsEntityEmittingSmoke* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* IsEntityEmittingSmoke */

	class EXPORT_MACRO IsEngineEmittingSmoke : public Enumeration {
	public:
		static IsEngineEmittingSmoke NOT_SMOKING;
		static IsEngineEmittingSmoke SMOKING;

		/** Returns the string description associated with the enumerated instance with this value.
		* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		* If there is no enumerated instance for this value, the exception is thrown.     */
		static IsEngineEmittingSmoke getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, IsEngineEmittingSmoke*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit() { return endBit; };


	private:
		/** Constructor */
		IsEngineEmittingSmoke(int value, std::string description);

		static IsEngineEmittingSmoke* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* IsEngineEmittingSmoke */

	class EXPORT_MACRO TrailingEffects : public Enumeration {
  public:
    static TrailingEffects NONE;
    static TrailingEffects SMALL;
    static TrailingEffects MEDIUM;
    static TrailingEffects LARGE;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static TrailingEffects getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int,TrailingEffects*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		TrailingEffects(int value, std::string description);

		static TrailingEffects* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* TrailingEffects */
	
	class EXPORT_MACRO Canopy_TroopDoor : public Enumeration {
  public:
    static Canopy_TroopDoor NOT_APPLICABLE;
    static Canopy_TroopDoor SINGLE_CANOPY_SINGLE_TROOP_DOOR_CLOSED;
    static Canopy_TroopDoor FRONT_AND_REAR_CANOPY_LEFT_AND_RIGHT_TROOP_DOOR_CLOSED;
	static Canopy_TroopDoor FRONT_CANOPY_LEFT_TROOP_DOOR_OPEN;
	static Canopy_TroopDoor SINGLE_CANOPY_SINGLE_TROOP_DOOR_OPEN;
	static Canopy_TroopDoor REAR_CANOPY_RIGHT_TROOP_DOOR_OPEN;
	static Canopy_TroopDoor FRONT_AND_REAR_CANOPY_LEFT_AND_RIGHT_TROOP_DOOR_OPEN;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static Canopy_TroopDoor getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, Canopy_TroopDoor*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		Canopy_TroopDoor(int value, std::string description);

		static Canopy_TroopDoor* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* Canopy_TroopDoor */

	class EXPORT_MACRO LandingLightsOn : public Enumeration {
  public:
    static LandingLightsOn OFF;
    static LandingLightsOn ON;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static LandingLightsOn getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, LandingLightsOn*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		LandingLightsOn(int value, std::string description);

		static LandingLightsOn* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* LandingLightsOn */

	class EXPORT_MACRO NavigationLightsOn : public Enumeration {
  public:
    static NavigationLightsOn OFF;
    static NavigationLightsOn ON;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static NavigationLightsOn getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, NavigationLightsOn*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		NavigationLightsOn(int value, std::string description);

		static NavigationLightsOn* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* NavigationLightsOn */

	class EXPORT_MACRO Anti_CollisionLightsOn : public Enumeration {
  public:
    static Anti_CollisionLightsOn OFF;
    static Anti_CollisionLightsOn ON;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static Anti_CollisionLightsOn getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, Anti_CollisionLightsOn*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		Anti_CollisionLightsOn(int value, std::string description);

		static Anti_CollisionLightsOn* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* Anti_CollisionLightsOn */

	class EXPORT_MACRO IsFlaming : public Enumeration {
  public:
    static IsFlaming NONE;
    static IsFlaming FLAMES_PRESENT;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static IsFlaming getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, IsFlaming*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		IsFlaming(int value, std::string description);

		static IsFlaming* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* Flaming */

	class EXPORT_MACRO AfterburnerOn : public Enumeration {
  public:
    static AfterburnerOn AFTERBURNER_NOT_ON;
    static AfterburnerOn AFTERBURNER_ON;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static AfterburnerOn getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, AfterburnerOn*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		AfterburnerOn(int value, std::string description);

		static AfterburnerOn* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* AfterburnerOn */

	class EXPORT_MACRO LowerAnti_CollisionLightOn : public Enumeration {
	public:
		static LowerAnti_CollisionLightOn OFF;
		static LowerAnti_CollisionLightOn ON;

		/** Returns the string description associated with the enumerated instance with this value.
		* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		* If there is no enumerated instance for this value, the exception is thrown.     */
		static LowerAnti_CollisionLightOn getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, LowerAnti_CollisionLightOn*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit() { return endBit; };


	private:
		/** Constructor */
		LowerAnti_CollisionLightOn(int value, std::string description);

		static LowerAnti_CollisionLightOn* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* LowerAnti_CollisionLightOn */

	class EXPORT_MACRO UpperAnti_CollisionLightOn : public Enumeration {
	public:
		static UpperAnti_CollisionLightOn OFF;
		static UpperAnti_CollisionLightOn ON;

		/** Returns the string description associated with the enumerated instance with this value.
		* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		* If there is no enumerated instance for this value, the exception is thrown.     */
		static UpperAnti_CollisionLightOn getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, UpperAnti_CollisionLightOn*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit() { return endBit; };


	private:
		/** Constructor */
		UpperAnti_CollisionLightOn(int value, std::string description);

		static UpperAnti_CollisionLightOn* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* UpperAnti_CollisionLightOn */

	class EXPORT_MACRO Anti_CollisionLightDayNight : public Enumeration {
	public:
		static Anti_CollisionLightDayNight DAY;
		static Anti_CollisionLightDayNight NIGHT;

		/** Returns the string description associated with the enumerated instance with this value.
		* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		* If there is no enumerated instance for this value, the exception is thrown.     */
		static Anti_CollisionLightDayNight getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, Anti_CollisionLightDayNight*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit() { return endBit; };


	private:
		/** Constructor */
		Anti_CollisionLightDayNight(int value, std::string description);

		static Anti_CollisionLightDayNight* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* Anti_CollisionLightDayNight */

	class EXPORT_MACRO IsBlinking : public Enumeration {
	public:
		static IsBlinking NOT_BLINKING;
		static IsBlinking BLINKING;

		/** Returns the string description associated with the enumerated instance with this value.
		* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		* If there is no enumerated instance for this value, the exception is thrown.     */
		static IsBlinking getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, IsBlinking*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit() { return endBit; };


	private:
		/** Constructor */
		IsBlinking(int value, std::string description);

		static IsBlinking* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* IsBlinking */

	class EXPORT_MACRO IsFrozen : public Enumeration {
  public:
    static IsFrozen NOT_FROZEN;
    static IsFrozen FROZEN_FROZEN_ENTITIES_SHOULD_NOT_BE_DEAD_RECKONED_IE_THEY_SHOULD_BE_DISPLAYED_AS_FIXED_AT_THE_CURRENT_LOCATION_EVEN_IF_NONZERO_VELOCITY_ACCELERATION_OR_ROTATION_DATA_IS_RECEIVED_FROM_THE_FROZEN_ENTITY;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static IsFrozen getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, IsFrozen*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		IsFrozen(int value, std::string description);

		static IsFrozen* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* IsFrozen */

	class EXPORT_MACRO PowerPlantOn : public Enumeration {
  public:
    static PowerPlantOn POWER_PLANT_OFF;
    static PowerPlantOn POWER_PLANT_ON;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static PowerPlantOn getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, PowerPlantOn*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		PowerPlantOn(int value, std::string description);

		static PowerPlantOn* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* PowerPlantOn */

	class EXPORT_MACRO State : public Enumeration {
  public:
    static State ACTIVE;
    static State DEACTIVATED;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static State getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int,State*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		State(int value, std::string description);

		static State* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* State */

	class EXPORT_MACRO FormationLightsOn : public Enumeration {
  public:
    static FormationLightsOn OFF;
    static FormationLightsOn ON;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static FormationLightsOn getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, FormationLightsOn*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		FormationLightsOn(int value, std::string description);

		static FormationLightsOn* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* FormationLightsOn */

	class EXPORT_MACRO LandingGearExtended : public Enumeration {
	public:
		static LandingGearExtended RETRACTED;
		static LandingGearExtended EXTENDED;

		/** Returns the string description associated with the enumerated instance with this value.
		* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		* If there is no enumerated instance for this value, the exception is thrown.     */
		static LandingGearExtended getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, LandingGearExtended*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit() { return endBit; };


	private:
		/** Constructor */
		LandingGearExtended(int value, std::string description);

		static LandingGearExtended* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* LandingGearExtended */

	class EXPORT_MACRO CargoDoorsOpened : public Enumeration {
	public:
		static CargoDoorsOpened CLOSED;
		static CargoDoorsOpened OPENED;

		/** Returns the string description associated with the enumerated instance with this value.
		* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		* If there is no enumerated instance for this value, the exception is thrown.     */
		static CargoDoorsOpened getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, CargoDoorsOpened*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit() { return endBit; };


	private:
		/** Constructor */
		CargoDoorsOpened(int value, std::string description);

		static CargoDoorsOpened* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* CargoDoorsOpened */

	class EXPORT_MACRO NavigationPositionBrightness : public Enumeration {
  public:
    static NavigationPositionBrightness DIM;
    static NavigationPositionBrightness BRIGHT;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static NavigationPositionBrightness getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int,NavigationPositionBrightness*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		NavigationPositionBrightness(int value, std::string description);

		static NavigationPositionBrightness* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* NavigationPositionBrightness */

	class EXPORT_MACRO SpotSearchLightNumber1On : public Enumeration {
  public:
    static SpotSearchLightNumber1On OFF;
    static SpotSearchLightNumber1On ON;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static SpotSearchLightNumber1On getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, SpotSearchLightNumber1On*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		SpotSearchLightNumber1On(int value, std::string description);

		static SpotSearchLightNumber1On* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* SpotSearchLightNumber1On */

	class EXPORT_MACRO InteriorLightsOn : public Enumeration {
  public:
    static InteriorLightsOn OFF;
    static InteriorLightsOn ON;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static InteriorLightsOn getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, InteriorLightsOn*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		InteriorLightsOn(int value, std::string description);

		static InteriorLightsOn* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* InteriorLightsOn */

	class EXPORT_MACRO ReverseThrustEngaged : public Enumeration {
	public:
		static ReverseThrustEngaged NOT_ENGAGED;
		static ReverseThrustEngaged ENGAGED;

		/** Returns the string description associated with the enumerated instance with this value.
		* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		* If there is no enumerated instance for this value, the exception is thrown.     */
		static ReverseThrustEngaged getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, ReverseThrustEngaged*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit() { return endBit; };


	private:
		/** Constructor */
		ReverseThrustEngaged(int value, std::string description);

		static ReverseThrustEngaged* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* ReverseThrustEngaged */

	class EXPORT_MACRO WeightOnWheels : public Enumeration {
	public:
		static WeightOnWheels NO_WEIGHT_ON_MAIN_GEAR;
		static WeightOnWheels WEIGHT_ON_MAIN_GEAR;

		/** Returns the string description associated with the enumerated instance with this value.
		* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		* If there is no enumerated instance for this value, the exception is thrown.     */
		static WeightOnWheels getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, WeightOnWheels*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit() { return endBit; };


	private:
		/** Constructor */
		WeightOnWheels(int value, std::string description);

		static WeightOnWheels* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* WeightOnWheels */

}; /* namespace es_appear_platform_air */

}  /* namespace DIS */ }

#endif /* ES_APPEAR_PLATFORM_AIR__H */
