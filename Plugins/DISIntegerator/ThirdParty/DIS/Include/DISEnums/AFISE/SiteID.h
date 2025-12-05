#ifndef SiteID__H
#define SiteID__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace AFISE {

class EXPORT_MACRO SiteID : public Enumeration {
  public:
    static SiteID OTHER;						//
    static SiteID GMCC_487;						//Sumugli
    static SiteID GMCC_406;						//Sakkhar
    static SiteID GMCC_481;						//Lahore
    static SiteID GMCC_482;						//Malir
    static SiteID GMCC_483;						//Mianwali
    static SiteID GMCC_485;						//Shorkot
    static SiteID GMCC_486;						//Nur Khan
    static SiteID ADC;							//Chaklala
    static SiteID ADTS;							//Risalpur
    static SiteID COMTAS_CSS;					//Sargodha
    static SiteID NO_3_SQN_AEW_C;				//Kamra
    static SiteID NO_4_SQN_AWACS;				//Masroor
	static SiteID NO_4095_SQN;					//Peshawar
	static SiteID SADO;							//Sakesar
	static SiteID NO_4094_SQN;					//Jacobabad
	static SiteID SPADA_452;					//ShorKot
	static SiteID SPADA_453;					//Sihala
	static SiteID SPADA_456;					//Jacobabad
	static SiteID JTAC_CCS;						//Sargodha
	static SiteID CSC_CCS;						//Sargodha
    

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static SiteID getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,SiteID*> enumContainer;
    static enumContainer getEnumerations();

    SiteID& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  SiteID(int value, std::string description);

	  static SiteID* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* SiteID */

}	/* namespace AFISE */ }  /* namespace DIS */ }

#endif /* SiteID__H */

