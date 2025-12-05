#pragma once
#include <DISUtils/DISHandler.h>
#include <DIS7\msLibMacro.h>

namespace DIS
{
	struct CNetworkLinkInfo
	{
		double _averageClockSkew{};
		double _averageLatency{};
		double alpha{};
	};

	class EXPORT_MACRO CHostTimeHandler
	{
		static CHostTimeHandler* _instanceHandle;
		std::unordered_map<EntityID, CNetworkLinkInfo> _uMapNetworkLinkMetrics;
		CHostTimeHandler();

	public:
		static CHostTimeHandler* GetInstance();
		~CHostTimeHandler();

		void AddNetworkLink(EntityID entityID, _Time currPduTime, _Time localTopOfHourTime);
		void UpdateClockSkew(CNetworkLinkInfo& networkLinkInfo, _Time currPduTime, _Time localTopOfHourTime);
		double GetTimeDifference(EntityID entityID, _Time currPduTime, _Time localTopOfHourTime, COMPARISON_RESULT& result);
		void UpdateLinkInfo(CNetworkLinkInfo& networkLinkInfo, double newCalculatedClockSkew);
		void UpdateAvgLatency(CNetworkLinkInfo& networkLinkInfo, double latency);
		double GetAverageLatency(EntityID entityID);
	};
}

