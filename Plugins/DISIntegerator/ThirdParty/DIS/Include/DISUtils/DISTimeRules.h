#pragma once
#include <tuple>
#include <DIS7/EntityID.h>
#include <DIS7\msLibMacro.h>

namespace DIS
{
	class EXPORT_MACRO CDISTimeRules
	{
	public:
		CDISTimeRules();
		~CDISTimeRules();
		static std::tuple<double, bool> IsTimestampValid(unsigned int currentPduTimeStamp, unsigned int prevPduTimeStamp, EntityID entityID);
	};
}

