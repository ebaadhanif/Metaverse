#ifndef PAKISTAN_Munition_SubCat_Anti_Radar_H
#define PAKISTAN_Munition_SubCat_Anti_Radar_H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS { namespace AFISE { namespace PAKISTAN { namespace MUNITION { namespace SubCategories {

class EXPORT_MACRO Munition_SubCat_Anti_Radar : public Enumeration {
  public:
    static Munition_SubCat_Anti_Radar OTHER;
	static Munition_SubCat_Anti_Radar AGM_88_HARM;

	
    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(unsigned short aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static Munition_SubCat_Anti_Radar getEnumerationForValue(unsigned short aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(unsigned short aVal);

    typedef hashMap<unsigned short, Munition_SubCat_Anti_Radar*> enumContainer;
    static enumContainer getEnumerations();

    Munition_SubCat_Anti_Radar& operator=(const unsigned short& aVal) throw(EnumException);

  private:
    /** Constructor */
	  Munition_SubCat_Anti_Radar(unsigned short aVal, std::string description);

	static Munition_SubCat_Anti_Radar* findEnumeration(unsigned short aVal);
    static enumContainer enumerations;

};  /* ActionID */


}  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ } /* namespace DIS */ }  /* namespace DIS */ }

#endif  