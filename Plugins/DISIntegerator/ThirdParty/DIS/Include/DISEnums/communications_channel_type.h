#ifndef COMMUNICATIONS_CHANNEL_TYPE__H
#define COMMUNICATIONS_CHANNEL_TYPE__H

#include <string>
#include <DISEnums/Enumeration.h>

namespace DIS { namespace ENUMS {

namespace communications_channel_type {

	/** Bitmask declaration **/
	struct bitmask {
    unsigned int CommunicationType:7;
    unsigned int CommunicationClass:1;

    bitmask& operator=(const unsigned char& i);
	  bitmask(const unsigned char& i);
	  bitmask();
	  unsigned char getValue();
	  void  setValue(const unsigned char& i);
	};

}; /* communications_channel_type */

}  /* namespace DIS */ }

#endif /* COMMUNICATIONS_CHANNEL_TYPE__H */
