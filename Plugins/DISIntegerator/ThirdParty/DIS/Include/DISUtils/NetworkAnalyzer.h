#pragma once
#include <string>
#include <DIS7/EntityID.h>
#include <list>
#include <DIS7\msLibMacro.h>

namespace DIS
{
	enum class SOURCE_TYPE
	{
		LOCAL,
		REMOTE
	};

	class RawDisPduHeader
	{
	public:
		/** The version of the protocol. 5=DIS-1995, 6=DIS-1998, 7=DIS-2009. */
		unsigned char _protocolVersion;

		/** Exercise ID */
		unsigned char _exerciseID;

		/** Type of pdu, unique for each PDU class */
		unsigned char _pduType;

		/** value that refers to the protocol family, eg SimulationManagement, et */
		unsigned char _protocolFamily;

		/** Timestamp value */
		unsigned int _timestamp;

		/** Length, in bytes, of the PDU */
		unsigned short _length;

		/** PDU Status Record. Described in 6.2.67. This field is not present in earlier DIS versions  */
		unsigned char _pduStatus;

		/** zero-filled array of padding */
		unsigned char _padding;
	};

	class EXPORT_MACRO CNetworkSource
	{
	public:
		std::string	_applicationType{ "NA" };

		std::string _ipAddress{};
		double _localTime{};
		double _sourceTime{};
		double _timeOffset{};
		int _totalPDUsRecv{};
		int _numberOfRecvPDUs{};
		int _numberOfPDUsPerSec{};
		long int _totalBytesRecv{};
		int _bytesRecv{};
		int _bytesPerSec{};

		long int _maxBytesPerSec{};
		int _maxPdusPerSec{};

		float _lastUpdateTime{};

		SOURCE_TYPE	_sourceType{};

		EntityID _simulationID{};

	public:
		CNetworkSource() = default;
		CNetworkSource(const CNetworkSource&) = default;

		std::string GetString();
	};

	class CNetworkAnalyzer
	{
		static CNetworkAnalyzer* _instanceHandle;

		float _lastUpdateTime{};

		std::list<CNetworkSource> _networkSources;

		CNetworkAnalyzer();
	public:
		static CNetworkAnalyzer* GetInstance();
		~CNetworkAnalyzer();

		void AddNetworkSource(char* buffer, int bytesRecv, std::string ipAddress, SOURCE_TYPE type);

		void UpdateNetwrokSource(char* buffer, int bytesRecv, std::string ipAddress, SOURCE_TYPE type);

		void Update(float fDeltaTime, float fAppTime);

		std::string GetIpAddressBySimulationAddress(EntityID simulationID);
	};
}
