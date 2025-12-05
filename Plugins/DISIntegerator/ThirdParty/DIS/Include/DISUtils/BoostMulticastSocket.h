pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <string>
#include <QEvent>

namespace DIS
{
	const int BOOST_MULTICAST_BUFFER_SIZE = 3000;

	class CBoostMulticastSocket
	{
	private:
		bool m_isWSACleanupRequired{ false };
		bool m_isGroupJoined{ false };
		bool m_isReceivingSocketCreated{ false };
		bool m_isSendingSocketCreated{ false };
		bool m_isInitialized{ false };

		char m_buffer[BOOST_MULTICAST_BUFFER_SIZE]{};

		boost::asio::io_service m_receivingIOService{};
		boost::asio::io_service m_sendingIOService{};

		boost::asio::ip::udp::socket m_receivingSocket{ boost::asio::ip::udp::socket(m_receivingIOService) };
		boost::asio::ip::udp::socket m_sendingSocket{ boost::asio::ip::udp::socket(m_sendingIOService, boost::asio::ip::udp::v4()) };

		boost::asio::ip::udp::endpoint m_sourceEndpoint{};
		boost::asio::ip::udp::endpoint m_sendingEndpoint{};

		bool CreateReceivingSocket(
			HWND windowHandle,
			const char* group,
			int port,
			int ttl, int loopBack);

		bool CreateSendingSocket(const char* group, int port);

		void OnReceive(const boost::system::error_code& error, size_t bytesReceived);
		void OnSend(const boost::system::error_code& error);

	public:
		CBoostMulticastSocket();
		virtual ~CBoostMulticastSocket();

		bool GetIsInitialized() const;

		bool Initialize(
			HWND windowHandle,
			const char* group,
			int port,
			int ttl, int loopBack);

		bool LeaveGroup();
		int Send(const char* buffer, int bufferSize);
		void CleanUp();
	};
}

