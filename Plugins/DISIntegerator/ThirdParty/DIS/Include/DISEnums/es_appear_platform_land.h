#ifndef ES_APPEAR_PLATFORM_LAND__H
#define ES_APPEAR_PLATFORM_LAND__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

namespace  es_appear_platform_land {

	/** Bitmask declaration **/
	struct EXPORT_MACRO bitmask {
    unsigned int PaintScheme:1;
    unsigned int Mobility:1;
    unsigned int FirePower:1;
    unsigned int Damage:2;
	unsigned int IsEntityEmittingSmoke : 1;
	unsigned int IsEngineEmittingSmoke : 1;
    unsigned int TrailingDustCloud:2;
    unsigned int PrimaryHatch:3;
    unsigned int HeadLightsOn:1;
    unsigned int TailLightsOn:1;
    unsigned int BrakeLightsOn:1;
    unsigned int IsFlaming :1;
    unsigned int LauncherOperational:1;
    unsigned int CamouflageType:2;
    unsigned int ConcealedPosition:1;
	unsigned int UnusedBit : 1;
    unsigned int IsFrozen:1;
    unsigned int Power_plantOn:1;
    unsigned int State:1;
    unsigned int TentExtended:1;
    unsigned int RampExtended:1;
    unsigned int BlackoutLightsOn:1;
    unsigned int BlackoutBrakeLightsOn:1;
    unsigned int SpotSearchLightNumber1On:1;
    unsigned int InteriorLightsForwardOn:1;
    unsigned int OccupantsSurrendered:1;
    unsigned int Masked_Cloaked:1;

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

	class EXPORT_MACRO Mobility : public Enumeration {
  public:
    static Mobility NO_MOBILITY_KILL;
    static Mobility MOBILITY_KILL;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static Mobility getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int,Mobility*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		Mobility(int value, std::string description);

		static Mobility* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* Mobility */

	class EXPORT_MACRO FirePower : public Enumeration {
  public:
    static FirePower NO_FIRE_POWER_KILL;
    static FirePower FIRE_POWER_KILL;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static FirePower getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int,FirePower*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		FirePower(int value, std::string description);

		static FirePower* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* FirePower */

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
		static short  getEndBit() { return endBit; };


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

	class EXPORT_MACRO TrailingDustCloud : public Enumeration {
  public:
    static TrailingDustCloud NONE;
    static TrailingDustCloud SMALL;
    static TrailingDustCloud MEDIUM;
    static TrailingDustCloud LARGE;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static TrailingDustCloud getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, TrailingDustCloud*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		TrailingDustCloud(int value, std::string description);

		static TrailingDustCloud* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* TrailingDustCloud */

	class EXPORT_MACRO PrimaryHatch : public Enumeration {
  public:
    static PrimaryHatch NOT_APPLICABLE;
    static PrimaryHatch PRIMARY_HATCH_IS_CLOSED;
    static PrimaryHatch PRIMARY_HATCH_IS_POPPED;
    static PrimaryHatch PRIMARY_HATCH_IS_POPPED_AND_A_PERSON_IS_VISIBLE_UNDER_HATCH;
    static PrimaryHatch PRIMARY_HATCH_IS_OPEN;
    static PrimaryHatch PRIMARY_HATCH_IS_OPEN_AND_PERSON_IS_VISIBLE;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static PrimaryHatch getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, PrimaryHatch*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		PrimaryHatch(int value, std::string description);

		static PrimaryHatch* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* PrimaryHatch */

	class EXPORT_MACRO HeadLightsOn : public Enumeration {
  public:
    static HeadLightsOn OFF;
    static HeadLightsOn ON;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static HeadLightsOn getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, HeadLightsOn*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		HeadLightsOn(int value, std::string description);

		static HeadLightsOn* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* HeadLightsOn */

	class EXPORT_MACRO TailLightsOn : public Enumeration {
  public:
    static TailLightsOn OFF;
    static TailLightsOn ON;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static TailLightsOn getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, TailLightsOn*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		TailLightsOn(int value, std::string description);

		static TailLightsOn* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* TailLights */
	
	class EXPORT_MACRO BrakeLightsOn : public Enumeration {
  public:
    static BrakeLightsOn OFF;
    static BrakeLightsOn ON;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static BrakeLightsOn getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, BrakeLightsOn*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		BrakeLightsOn(int value, std::string description);

		static BrakeLightsOn* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* BrakeLights */

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
		static short  getEndBit() { return endBit; };


	private:
		/** Constructor */
		IsFlaming(int value, std::string description);

		static IsFlaming* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* Flaming */

	class EXPORT_MACRO LauncherOperational : public Enumeration {
  public:
    static LauncherOperational NOT_RAISED_NOT_OPERATIONAL;
	static LauncherOperational RAISED_OPERATIONAL;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static LauncherOperational getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, LauncherOperational*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		LauncherOperational(int value, std::string description);

		static LauncherOperational* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* LauncherOperational */

	class EXPORT_MACRO CamouflageType : public Enumeration {
  public:
    static CamouflageType DESERT_CAMOUFLAGE;
    static CamouflageType WINTER_CAMOUFLAGE;
    static CamouflageType FOREST_CAMOUFLAGE;
	static CamouflageType OTHER;
		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static CamouflageType getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int,CamouflageType*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		CamouflageType(int value, std::string description);

		static CamouflageType* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* CamouflageType */

	class EXPORT_MACRO ConcealedPosition : public Enumeration {
  public:
    static ConcealedPosition NOT_CONCEALED;
    static ConcealedPosition ENTITY_IN_A_PREPARED_CONCEALED_POSITION_WITH_NETTING_ETC;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static ConcealedPosition getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, ConcealedPosition*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		ConcealedPosition(int value, std::string description);

		static ConcealedPosition* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* ConcealedPosition */

	class EXPORT_MACRO UnusedBit : public Enumeration {
	public:
		static UnusedBit UNUSED;

		/** Returns the string description associated with the enumerated instance with this value.
		* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		* If there is no enumerated instance for this value, the exception is thrown.     */
		static UnusedBit getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, UnusedBit*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit() { return endBit; };


	private:
		/** Constructor */
		UnusedBit(int value, std::string description);

		static UnusedBit* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* UnusedBit */

	class EXPORT_MACRO IsFrozen : public Enumeration {
  public:
    static IsFrozen NOT_FROZEN;
    static IsFrozen FROZEN_FROZEN_ENTITIES_SHOULD_NOT_BE_DEAD_RECKONED_IE_SHOULD_BE_DISPLAYED_AS_FIXED_AT_THE_CURRENT_LOCATION_EVEN_IF_NON_ZERO_VELOCITY_ACCELERATION_OR_ROTATION_DATA_RECEIVED_FROM_THE_FROZEN_ENTITY;

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

	};  /* FrozenStatus */

	class EXPORT_MACRO Power_plantOn : public Enumeration {
  public:
    static Power_plantOn POWER_PLANT_OFF;
    static Power_plantOn POWER_PLANT_ON;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static Power_plantOn getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, Power_plantOn*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		Power_plantOn(int value, std::string description);

		static Power_plantOn* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* Power_plantOn */

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

	class EXPORT_MACRO TentExtended : public Enumeration {
  public:
    static TentExtended NOT_EXTENDED;
    static TentExtended EXTENDED;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static TentExtended getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, TentExtended*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		TentExtended(int value, std::string description);

		static TentExtended* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* TentExtended */

	class EXPORT_MACRO RampExtended : public Enumeration {
  public:
    static RampExtended NOT_EXTENDED;
    static RampExtended EXTENDED;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static RampExtended getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, RampExtended*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		RampExtended(int value, std::string description);

		static RampExtended* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* RampExtended */

	class EXPORT_MACRO BlackoutLightsOn : public Enumeration {
  public:
    static BlackoutLightsOn OFF;
    static BlackoutLightsOn ON;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static BlackoutLightsOn getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, BlackoutLightsOn*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		BlackoutLightsOn(int value, std::string description);

		static BlackoutLightsOn* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* BlackoutLights */

	class EXPORT_MACRO BlackoutBrakeLightsOn : public Enumeration {
  public:
    static BlackoutBrakeLightsOn OFF;
    static BlackoutBrakeLightsOn ON;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static BlackoutBrakeLightsOn getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, BlackoutBrakeLightsOn*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		BlackoutBrakeLightsOn(int value, std::string description);

		static BlackoutBrakeLightsOn* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* BlackoutBrakeLightsOn */

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
		static short  getEndBit() { return endBit; };


	private:
		/** Constructor */
		SpotSearchLightNumber1On(int value, std::string description);

		static SpotSearchLightNumber1On* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* SpotSearchLightNumber1On */

	class EXPORT_MACRO InteriorLightsForwardOn : public Enumeration {
  public:
    static InteriorLightsForwardOn OFF;
    static InteriorLightsForwardOn ON;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static InteriorLightsForwardOn getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, InteriorLightsForwardOn*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		InteriorLightsForwardOn(int value, std::string description);

		static InteriorLightsForwardOn* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* InteriorLightsForwardOn */

	class EXPORT_MACRO OccupantsSurrendered : public Enumeration {
  public:
    static OccupantsSurrendered NOT_SURRENDERED;
    static OccupantsSurrendered SURRENDER;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static OccupantsSurrendered getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, OccupantsSurrendered*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		OccupantsSurrendered(int value, std::string description);

		static OccupantsSurrendered* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* OccupantsSurrendered */

	class EXPORT_MACRO Masked_Cloaked : public Enumeration {
	public:
    static Masked_Cloaked NOT_MASKED_NOT_CLOAKED;
    static Masked_Cloaked MASKED_CLOAKED;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static Masked_Cloaked getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int,Masked_Cloaked*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		Masked_Cloaked(int value, std::string description);

		static Masked_Cloaked* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* Masked_Cloaked */




}; /* namespace es_appear_platform_land */

}  /* namespace DIS */ }

#endif /* ES_APPEAR_PLATFORM_LAND__H */
