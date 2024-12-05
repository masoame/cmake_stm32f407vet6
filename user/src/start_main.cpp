#include"start_main.hpp"
#include "atgm336h.hpp"
#include"esp8266.hpp"
#include "main.h"
#include "stm32f4xx_hal_gpio.h"

constexpr auto delay_ms = 150;

static wifi::esp8266 _wifi(&huart2);
static gps::atgm336h _gps(&huart1);

void start_main() {

	//_wifi.StartForwardSerialPort(_gps);
	//_gps.StartForwardSerialPort(_wifi);

	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
	while (true) {

		
		if(HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin) == GPIO_PIN_RESET) {

			if(_wifi.ConnectWifi("gt", "1658932642")){
				HAL_Delay(delay_ms);
				HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
				HAL_Delay(delay_ms);
				HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
				
			}

			while(HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin) == GPIO_PIN_RESET){}
		}else if(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_RESET) {
			if(_wifi.DisconnectWifi()){
				HAL_Delay(delay_ms);
				HAL_GPIO_TogglePin(LED1_GPIO_Port, LED2_Pin);
				HAL_Delay(delay_ms);
				HAL_GPIO_TogglePin(LED1_GPIO_Port, LED2_Pin);
			}
		}

		HAL_Delay(delay_ms);
	}


}

