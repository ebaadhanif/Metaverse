#ifndef ENTITYSTATEMARKINGS__H
#define ENTITYSTATEMARKINGS__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO EntityStateMarkings : public Enumeration {
  public:
	  static EntityStateMarkings MISSING_DESCRIPTION;
	  static EntityStateMarkings ASCII;
	  static EntityStateMarkings ARMY_MARKING_CCTT;
	  static EntityStateMarkings DIGIT_CHEVRON;
    

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static EntityStateMarkings getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int, EntityStateMarkings*> enumContainer;
    static enumContainer getEnumerations();

	EntityStateMarkings& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  EntityStateMarkings(int value, std::string description);

	  static EntityStateMarkings* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* ProtocolVersion */


}  /* namespace DIS */ }

#endif /* PROTOCOLVERSION__H */

