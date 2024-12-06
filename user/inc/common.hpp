#pragma once

#include "common.hpp"
#include<stm32f4xx_hal.h>
#include<main.h>
#include<optional>
#include<memory>
#include<string>
#include <cstdint>
#include<chrono>
#include<thread>


namespace common {

    using namespace std::chrono_literals;
    constexpr std::chrono::milliseconds Delay_Time(100ms);

    using GPIO_PORT = GPIO_TypeDef*;
    using GPIO_PIN = uint16_t;

    inline void LED_Blink(GPIO_PORT port, GPIO_PIN pin ,std::size_t count){
        for(std::size_t i=0; i<count*2; ++i){
            HAL_GPIO_TogglePin(port, pin);
            HAL_Delay(Delay_Time.count());
        }
    }
}
