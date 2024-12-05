#pragma once
#include<common.hpp>
#include <initializer_list>
#include<chrono>

#include "callback.hpp"
#include "serialport.hpp"




namespace wifi {

	enum CMD_TYPE {
		OPEN_ECHO,
		CLOSE_ECHO,

		WIFI_STATUS,
		WIFI_SCAN,
		WIFI_CONNECT,
		WIFI_DISCONNECT,

		TCP_LINK,
		TCP_SEND,
		TCP_CLOSE,
		PING
	};

	class esp8266 : public ::serialport::Driver{

		enum status {
			DISCONNECTED,
			CONNECTED
		};

		enum class ResponseType {

			UNKONW,

			OK,
			ERROR,

			WIFI_DISCONNECT,
			WIFI_CONNECTED,

			TCP_SEND_SUCCESS,
			TCP_SEND_FAILED,

			TCP_CLOSE,
			PING
		};

		status m_status = DISCONNECTED;
		UART_HandleTypeDef* m_huart = nullptr;
	public:
		esp8266(UART_HandleTypeDef* esp8266_huart);
		void GetWifiStatus();

		bool ConnectWifi(const std::string& ssid, const std::string& password);
		bool DisconnectWifi();

		void Ping(const std::string& ip);
		void LinkTcp(const std::string& ip, unsigned short port);
		void SendTcp(const std::string& data);
		void CloseTcp();
	private:


	};

}