#ifndef APPLICATIONID__H
#define APPLICATIONID__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace AFISE {

class EXPORT_MACRO ApplicationID : public Enumeration {

	//Try to retain ApplicaionIDs below 2047 as FTS handling tail numbers at max 2047 for application id

  public:
    static ApplicationID OTHER;						//1
    static ApplicationID FIGHTER_STATION;			//31
	static ApplicationID RAID_STATION;				//61
	static ApplicationID INSTRUCTOR_STATION;		//91
	static ApplicationID NG_GMCC;					//121
	static ApplicationID ATC_SERVER;				//151
	static ApplicationID PAR;						//181
	static ApplicationID TPS_43;					//211
	static ApplicationID MOCC;						//241
	static ApplicationID YLC_II;					//271
	static ApplicationID CGF;						//301
	static ApplicationID ATC_PSEUDO_PILOT;			//331
	static ApplicationID SSS_SERVER;				//361
	static ApplicationID ZDK_SERVER;				//391
	static ApplicationID EW_STATION;				//421
	static ApplicationID SPADA;						//451
	static ApplicationID FTS;						//481
	static ApplicationID NG_GMCC_VSM;				//511
	static ApplicationID NG_GMCC_SERVER;			//541
	static ApplicationID SSS_ESM;					//571
	static ApplicationID EW_COMM;					//601
	static ApplicationID EW_COMM_PLATFORM;			//631
	static ApplicationID ATC_INSTRUCTOR;			//661
	static ApplicationID JTAC;						//691
	static ApplicationID JTAC_PSEUDO_PILOT;			//721
	static ApplicationID ISR;						//751
	static ApplicationID CGF_LAND_NAVAL;			//781
	static ApplicationID IMAGE_GENERATOR;			//811
	static ApplicationID SMCC_SERVER;				//841
	static ApplicationID SIM_LIVE_GATEWAY;			//871
	static ApplicationID VR_FORCES;					//901
	static ApplicationID TACVIEW_CONNECT;			//931
	static ApplicationID EXCON;						//961

	static ApplicationID VCP_GATEWAY_JAVA;			//5001
	static ApplicationID VCP_RECORDER;				//5031
	static ApplicationID VCP;						//5061

	
    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(unsigned short aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static ApplicationID getEnumerationForValue(unsigned short aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(unsigned short aVal);

    typedef hashMap<unsigned short, ApplicationID*> enumContainer;
    static enumContainer getEnumerations();

    ApplicationID& operator=(const unsigned short& aVal) throw(EnumException);

  private:
    /** Constructor */
	  ApplicationID(unsigned short aVal, std::string description);

	static ApplicationID* findEnumeration(unsigned short aVal);
    static enumContainer enumerations;

};  /* ActionID */


}  /* namespace DIS */ } /* namespace DIS */ }

#endif  