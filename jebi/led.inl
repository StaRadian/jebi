#pragma once

#include "stm32g4xx_ll_gpio.h"

#include "led.hpp"

namespace jebi
{
inline LED::LED(GPIO_TypeDef *GPIOx, const uint32_t Pin)
    :m_GPIOx(GPIOx), m_Pin(Pin)
{
    LL_GPIO_SetPinMode(GPIOx, Pin, LL_GPIO_MODE_OUTPUT);
}

inline void LED::on()
{
    LL_GPIO_SetOutputPin(m_GPIOx, m_Pin);
}

inline void LED::off()
{
    LL_GPIO_ResetOutputPin(m_GPIOx, m_Pin);
}

inline void LED::toggle()
{
    LL_GPIO_TogglePin(m_GPIOx, m_Pin);
}

} // namespace jebi