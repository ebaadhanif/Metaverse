#ifndef PDU_STATUS__H
#define PDU_STATUS__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

namespace PDUStatus{

	/** Bitmask declaration **/
	struct bitmask {
	unsigned int TEI : 1;
	unsigned int LVC : 2;
	unsigned int CEI : 1;
	unsigned int FTI : 1;
	unsigned int DTI : 2;
	unsigned int RAI : 2;
	unsigned int IAI : 2;
	unsigned int ISM : 1;
	unsigned int AII : 1;

    bitmask& operator=(const unsigned char& i);
	  bitmask(const unsigned char& i);
	  bitmask();
	  unsigned char getValue();
	  void  setValue(const unsigned char& i);
	};

	/** Enumerations declaration **/
	class TransferredEntityIndicator : public Enumeration {
  public:
    static TransferredEntityIndicator NO_DIFFERENCE;
    static TransferredEntityIndicator DIFFERENCE1;

		static std::string getDescriptionForValue(int aVal);
		static TransferredEntityIndicator getEnumerationForValue(int aVal) throw(EnumException);
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int,TransferredEntityIndicator*> enumContainer;
		static enumContainer getEnumerations();
		static short  getStartBit() { return startBit; };
		static short  getEndBit()   { return endBit;   };


	private:
		TransferredEntityIndicator(int value, std::string description);

		static TransferredEntityIndicator* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};

	class LVCIndicator : public   Enumeration {
  public:
    static LVCIndicator NO_STATEMENT;
    static LVCIndicator LIVE;
	static LVCIndicator VIRTUAL;
	static LVCIndicator CONSTRUCTIVE;

		static std::string getDescriptionForValue(int aVal);
		static LVCIndicator getEnumerationForValue(int aVal) throw(EnumException);
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int,LVCIndicator*> enumContainer;
		static enumContainer getEnumerations();
		static short  getStartBit() { return startBit; };
		static short  getEndBit()   { return endBit;   };


	private:
		LVCIndicator(int value, std::string description);

		static LVCIndicator* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	}; 

	class CoupledExtensionIndicator : public   Enumeration {
  public:
    static CoupledExtensionIndicator NOT_COUPLED;
    static CoupledExtensionIndicator COUPLED;

		static std::string getDescriptionForValue(int aVal);
		static CoupledExtensionIndicator getEnumerationForValue(int aVal) throw(EnumException);
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int,CoupledExtensionIndicator*> enumContainer;
		static enumContainer getEnumerations();
		static short  getStartBit() { return startBit; };
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		CoupledExtensionIndicator(int value, std::string description);

		static CoupledExtensionIndicator* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* Lane */

	class FireTypeIndicator : public   Enumeration {
  public:
    static FireTypeIndicator MUNITION;
    static FireTypeIndicator EXPENDABLE;

		static std::string getDescriptionForValue(int aVal);
		static FireTypeIndicator getEnumerationForValue(int aVal) throw(EnumException);
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int,FireTypeIndicator*> enumContainer;
		static enumContainer getEnumerations();
		static short  getStartBit() { return startBit; };
		static short  getEndBit()   { return endBit;   };


	private:
		/** Constructor */
		FireTypeIndicator(int value, std::string description);

		static FireTypeIndicator* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* State */

	class DetonationTypeIndicator : public   Enumeration {
	public:
		static DetonationTypeIndicator MUNITION;
		static DetonationTypeIndicator EXPENDABLE;
		static DetonationTypeIndicator NON_MUNITION_EXPLOSION;

		static std::string getDescriptionForValue(int aVal);
		static DetonationTypeIndicator getEnumerationForValue(int aVal) throw(EnumException);
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, DetonationTypeIndicator*> enumContainer;
		static enumContainer getEnumerations();
		static short  getStartBit() { return startBit; };
		static short  getEndBit() { return endBit; };


	private:
		/** Constructor */
		DetonationTypeIndicator(int value, std::string description);

		static DetonationTypeIndicator* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* State */
	class  RadioAttachedIndicator : public   Enumeration {
	public:
		static RadioAttachedIndicator NO_STATEMENT;
		static RadioAttachedIndicator UNATTACHED;
		static RadioAttachedIndicator ATTACHED;

		static std::string getDescriptionForValue(int aVal);
		static RadioAttachedIndicator getEnumerationForValue(int aVal) throw(EnumException);
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, RadioAttachedIndicator*> enumContainer;
		static enumContainer getEnumerations();
		static short  getStartBit() { return startBit; };
		static short  getEndBit() { return endBit; };


	private:
		/** Constructor */
		RadioAttachedIndicator(int value, std::string description);

		static RadioAttachedIndicator* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* State */
	class IntercomAttachedIndicator : public   Enumeration {
	public:
		static IntercomAttachedIndicator NO_STATEMENT;
		static IntercomAttachedIndicator UNATTACHED;
		static IntercomAttachedIndicator ATTACHED;

		static std::string getDescriptionForValue(int aVal);
		static IntercomAttachedIndicator getEnumerationForValue(int aVal) throw(EnumException);
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, IntercomAttachedIndicator*> enumContainer;
		static enumContainer getEnumerations();
		static short  getStartBit() { return startBit; };
		static short  getEndBit() { return endBit; };


	private:
		/** Constructor */
		IntercomAttachedIndicator(int value, std::string description);

		static IntercomAttachedIndicator* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* State */

	class  ActiveInterrogationIndicator : public   Enumeration {
	public:
		static ActiveInterrogationIndicator ACTIVE;
		static ActiveInterrogationIndicator NOT_ACTIVE;

		static std::string getDescriptionForValue(int aVal);
		static ActiveInterrogationIndicator getEnumerationForValue(int aVal) throw(EnumException);
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, ActiveInterrogationIndicator*> enumContainer;
		static enumContainer getEnumerations();
		static short  getStartBit() { return startBit; };
		static short  getEndBit() { return endBit; };


	private:
		/** Constructor */
		ActiveInterrogationIndicator(int value, std::string description);

		static ActiveInterrogationIndicator* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};  /* State */
	class  IFFSimulationMode : public   Enumeration {
	public:
		static IFFSimulationMode REGENERATION;
		static IFFSimulationMode INTERACTIVE;

		static std::string getDescriptionForValue(int aVal);
		static IFFSimulationMode getEnumerationForValue(int aVal) throw(EnumException);
		static bool enumerationForValueExists(int aVal);

		typedef hashMap<int, IFFSimulationMode*> enumContainer;
		static enumContainer getEnumerations();
		static short  getStartBit() { return startBit; };
		static short  getEndBit() { return endBit; };

		
	private:
		IFFSimulationMode(int value, std::string description);

		static IFFSimulationMode* findEnumeration(int aVal);
		static enumContainer enumerations;

		static short startBit;
		static short endBit;

	};

} /* namespace PDU Status */

}  /* namespace DIS */ }

#endif /* PDU_STATUS__H */
