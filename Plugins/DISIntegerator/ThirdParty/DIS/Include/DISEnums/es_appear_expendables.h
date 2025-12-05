#ifndef ES_APPEAR_EXPENDABLES__H
#define ES_APPEAR_EXPENDABLES__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

namespace es_appear_expendables {

	/** Bitmask declaration **/
	struct EXPORT_MACRO bitmask {
    unsigned int unused:32;

    bitmask& operator=(const unsigned int& i);
	  bitmask(const unsigned int& i);
	  bitmask();
	  unsigned int getValue();
	  void  setValue(const unsigned int& i);
	};

	/** Enumerations declaration **/



}; /* namespace es_appear_expendables */

}  /* namespace DIS */ }

#endif /* ES_APPEAR_EXPENDABLES__H */
