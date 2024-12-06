#include"start_main.hpp"
#include "atgm336h.hpp"
#include"esp8266.hpp"
#include "main.h"
#include "serialport.hpp"
#include "stm32f407xx.h"
#include "stm32f4xx_hal_gpio.h"
#include <string>
#include<thread>

constexpr auto delay_ms = 1000;



void start_main() {

	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);

	wifi::esp8266 _wifi(&huart2);
	//gps::atgm336h _gps(&huart1);
	// serialport::Driver _serialport(&huart1);
	// serialport::Driver _serialport2(&huart2);

	// _serialport.StartForwardSerialPort(_serialport2);
	// _serialport2.StartForwardSerialPort(_serialport);

	int i=0;
	std::string str = "hello world: ";


	while (true) {
		i++;
		_wifi.SendTcp(str + std::to_string(i) + "\n");
		HAL_Delay(delay_ms);
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	}

}

