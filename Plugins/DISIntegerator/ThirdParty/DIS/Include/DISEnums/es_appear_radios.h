#ifndef ES_APPEAR_RADIOS__H
#define ES_APPEAR_RADIOS__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

namespace es_appear_radios {

	/** Bitmask declaration **/
	struct EXPORT_MACRO  bitmask {
    unsigned int unused:32;

    bitmask& operator=(const unsigned int& i);
	  bitmask(const unsigned int& i);
	  bitmask();
	  unsigned int getValue();
	  void  setValue(const unsigned int& i);
	};

	/** Enumerations declaration **/



}; /* namespace es_appear_radios */

}  /* namespace DIS */ }

#endif /* ES_APPEAR_RADIOS__H */
