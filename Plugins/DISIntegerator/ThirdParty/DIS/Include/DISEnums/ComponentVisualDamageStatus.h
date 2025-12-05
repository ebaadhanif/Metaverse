#ifndef COMPONENT_VISUAL_DAMAGE_STATUS__H
#define COMPONENT_VISUAL_DAMAGE_STATUS__H

//Updated by Farhan on  22 March, 2018.
//Added EXPORT MACRO with bitmask struct to export to dll
//Enumerations updated w.r.t. DIS v7

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

namespace COMPONENT_VISUAL_DAMAGE_STATUS {

	/** Bitmask declaration **/
	struct EXPORT_MACRO bitmask 
	{
		unsigned int IsFirePresent : 1;
		unsigned int SmokeComponentVisualDamageStatus : 2;
		unsigned int SurfaceDamageComponentVisualDamageStatus : 2;

		bitmask& operator=(const unsigned int& i);
		bitmask(const unsigned int& i);
		bitmask();
		unsigned int getValue();
		void  setValue(const unsigned int& i);
	};

	/** Enumerations declaration **/
	class EXPORT_MACRO IsFirePresent : public Enumeration {
  public:
    static IsFirePresent NOT_PRESENT;
    static IsFirePresent PRESENT;

		/** Returns the string description associated with the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		 * If there is no enumerated instance for this value, the exception is thrown.     */
		static IsFirePresent getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, IsFirePresent*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		IsFirePresent(int value, std::string description);

		static IsFirePresent* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* IsFirePresent */

	class EXPORT_MACRO SmokeComponentVisualDamageStatus : public Enumeration {
	public:
		static SmokeComponentVisualDamageStatus NO_SMOKE;
		static SmokeComponentVisualDamageStatus LIGHT_SMOKE;
		static SmokeComponentVisualDamageStatus MODERATE_SMOKE;
		static SmokeComponentVisualDamageStatus HEAVY_SMOKE;

		/** Returns the string description associated with the enumerated instance with this value.
		* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		* If there is no enumerated instance for this value, the exception is thrown.     */
		static SmokeComponentVisualDamageStatus getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, SmokeComponentVisualDamageStatus*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit() { return endBit; };


	private:
		/** Constructor */
		SmokeComponentVisualDamageStatus(int value, std::string description);

		static SmokeComponentVisualDamageStatus* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* SmokeComponentVisualDamageStatus */

	class EXPORT_MACRO SurfaceDamageComponentVisualDamageStatus : public Enumeration {
	public:
		static SurfaceDamageComponentVisualDamageStatus NORMAL_APPEARANCE;
		static SurfaceDamageComponentVisualDamageStatus LIGHT_CHARRING;
		static SurfaceDamageComponentVisualDamageStatus HEAVY_CHARRING;
		static SurfaceDamageComponentVisualDamageStatus ONE_OR_MORE_HOLES_BURNED_COMPLETELY_THROUGH_SURFACE;

		/** Returns the string description associated with the enumerated instance with this value.
		* If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
		static std::string getDescriptionForValue(int aVal);

		/** Returns the enumerated instance with this value.
		* If there is no enumerated instance for this value, the exception is thrown.     */
		static SurfaceDamageComponentVisualDamageStatus getEnumerationForValue(int aVal) throw(EnumException);

		/** Returns true if there is an enumerated instance for this value, false otherwise. */
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, SurfaceDamageComponentVisualDamageStatus*> enumContainer;
		static enumContainer getEnumerations();

		/** Returns the start bit number for this subfield */
		static short  getStartBit() { return startBit; };

		/** Returns the end bit number for this subfield */
		static short  getEndBit() { return endBit; };


	private:
		/** Constructor */
		SurfaceDamageComponentVisualDamageStatus(int value, std::string description);

		static SurfaceDamageComponentVisualDamageStatus* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* SurfaceDamageComponentVisualDamageStatus */

}; /* namespace COMPONENT_VISUAL_DAMAGE_STATUS */

}  /* namespace DIS */ }

#endif /* COMPONENT_VISUAL_DAMAGE_STATUS__H */
