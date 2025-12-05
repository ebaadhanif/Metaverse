#pragma once

#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <iphlpapi.h>
#include <string>
#include <mutex>
#include <functional>
#include <DISUtils/DISDefinitions.h>
#include <DIS7\msLibMacro.h>

namespace DIS
{
	class EXPORT_MACRO CMulticastSocket
	{
		char _messageBuffer[MAX_RECEIVE_BUFFER_SIZE];

	private:
		bool _isWSACleanupRequired{ false };
		bool _isGroupJoined{ false };
		bool _isReceivingSocketCreated{ false };
		bool _isSendingSocketCreated{ false };
		bool _isInitialized{ false };
		bool _isReceptionThreadStarted{ false };
		bool _threadJoinRequested{ false };

		std::mutex _socketLock{};
		std::thread _receptionThread{};

		SOCKET _receivingSocketHandle{};
		SOCKET _sendingSocketHandle{};

		struct sockaddr_in _bindAddress {}; // Can connect with any IP address.
		struct sockaddr_in _localAddress {}; // Local Interface Address.
		struct sockaddr_in _groupAddress {}; // Multicast Group Address.

		struct ip_mreq _multicastGroupConfiguration {}; // Multicast Group Config for joining and leaving the group.

		std::function<void(char* message, int messageSize)> _onReceive;

		bool GetLocalIPv4Address(std::string& addressString);
		bool GetLocalIPv4AddressFromHostEnt(std::string& addressString);

		bool CreateReceivingSocket(
			const char* group,
			int port,
			int ttl, int loopBack,
			std::function<void(char* message, int messageSize)> onReceive);

		bool CreateSendingSocket(const char* group, int port, int ttl);

	public:
		CMulticastSocket();
		virtual ~CMulticastSocket();

		void UpdateWindowHandle(HWND windowHandle);

		bool GetIsInitialized() const;

		bool Initialize(
			const char* group,
			int port,
			int ttl, int loopBack,
			std::function<void(char* message, int messageSize)> onReceive);

		bool LeaveGroup();

		int Send(const char* buffer, int bufferSize);

		bool CleanUp();
	};
}

