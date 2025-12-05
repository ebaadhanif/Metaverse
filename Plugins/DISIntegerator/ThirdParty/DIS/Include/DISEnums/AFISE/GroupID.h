#ifndef GroupID__H
#define GroupID__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

class EXPORT_MACRO GroupID : public Enumeration {
  public:
    static GroupID OTHER;
    static GroupID ALPHA;
    static GroupID BRAVO;
    static GroupID CHARLIE;
    static GroupID DELTA;
    static GroupID ECHO;
	static GroupID FOXTROT;
    static GroupID GOLF;
    static GroupID HOTEL;
    static GroupID INDIA;
    static GroupID JULIET;
    static GroupID KILO;
    static GroupID LIMA;
    static GroupID MIKE;
	static GroupID NOVEMBER;
	static GroupID OSCAR;
	static GroupID PAPA;
	static GroupID QUEBEC;
	static GroupID ROMEO;
	static GroupID SIERRA;
	static GroupID TANGO;
	static GroupID UNIFORM;
	static GroupID VICTOR;
	static GroupID WHISKEY;
	static GroupID X_RAY;
	static GroupID YANKEE;
	static GroupID ZULU;
    

    /** Returns the string description associated with the enumerated instance with this value.
     * If there is no enumerated instance for this value, the string Invalid enumeration: <val> is returned.     */
    static std::string getDescriptionForValue(int aVal);

    /** Returns the enumerated instance with this value.
     * If there is no enumerated instance for this value, the exception is thrown.     */
    static GroupID getEnumerationForValue(int aVal) throw(EnumException);

    /** Returns true if there is an enumerated instance for this value, false otherwise. */
    static bool enumerationForValueExists(int aVal);

    typedef hashMap<int,GroupID*> enumContainer;
    static enumContainer getEnumerations();

    GroupID& operator=(const int& aVal) throw(EnumException);

  private:
    /** Constructor */
	  GroupID(int value, std::string description);

	  static GroupID* findEnumeration(int aVal);
    static enumContainer enumerations;

};  /* GroupID */


}  /* namespace DIS */ }

#endif /* GroupID__H */

