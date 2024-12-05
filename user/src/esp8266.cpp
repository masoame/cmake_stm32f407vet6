#include"esp8266.hpp"
#include "serialport.hpp"
#include "stm32f4xx_hal_uart.h"
#include <cstdio>



namespace wifi{
	using namespace std::chrono_literals;
	esp8266::esp8266(UART_HandleTypeDef* esp8266_huart): ::serialport::Driver(esp8266_huart) {
	}


	void esp8266::GetWifiStatus()
	{
		HAL_UARTEx_ReceiveToIdle_IT(this->m_huart, this->m_huart->pRxBuffPtr, this->m_huart->RxXferSize);
	}
	
	bool esp8266::ConnectWifi(const std::string& ssid, const std::string& password)
	{
		std::string _cmd;
		int sz = std::snprintf(nullptr, 0, "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid.c_str(),password.c_str());
		_cmd.resize(sz + 1); 
		std::sprintf(_cmd.data(), "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid.c_str(),password.c_str());

		return this->GetResponse(_cmd,6s, {"WIFI CONNECTED"}) == serialport::Driver::RESPONSE_TYPE_OK;
	}
	bool esp8266::DisconnectWifi()
	{
		std::string _cmd = "AT+CWQAP\r\n";
		return this->GetResponse(_cmd,2s, {"OK"}) == serialport::Driver::RESPONSE_TYPE_OK;
	}
	
	void esp8266::Ping(const std::string& ip)
	{
		std::string _cmd = std::vformat("AT+PING={}\r\n", std::make_format_args(ip));
	}


	void esp8266::LinkTcp(const std::string& ip, unsigned short port)
	{
		std::string _cmd = std::format("AT+CIPSTART=\"TCP\",\"{}\",{}\r\n",ip,port);

		HAL_UART_Transmit(this->m_huart,reinterpret_cast<const uint8_t*>(_cmd.c_str()),_cmd.size(),1000);
	}
	void esp8266::SendTcp(const std::string& data)
	{
		std::string _cmd = std::format("AT+CIPSEND={}\r\n",data.size());
		HAL_UART_Transmit(this->m_huart,reinterpret_cast<const uint8_t*>(_cmd.c_str()),_cmd.size(),1000);

		HAL_UART_Transmit(this->m_huart,reinterpret_cast<const uint8_t*>(data.c_str()),data.size(),1000);
	}
	void esp8266::CloseTcp()
	{
	}


}