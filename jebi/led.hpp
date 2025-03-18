#pragma once
#include "stm32g4xx.h"

namespace jebi
{

class LED
{
  public:
    inline LED(GPIO_TypeDef *GPIOx, const uint32_t Pin);
    inline void on();
    inline void off();
    inline void toggle();
    
  private:
    GPIO_TypeDef *m_GPIOx;
    const uint32_t m_Pin;

};

} // namespace jebi

#include "led.inl"