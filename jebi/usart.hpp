#pragma once
#include "stm32g4xx.h"

namespace jebi
{
  
class USART
{
  public:
    inline USART();
    inline void gpio(GPIO_TypeDef *GPIOx, const uint32_t Pin);

    inline void tx(uint8_t value);
    
  private:

};

} // namespace jebi

extern "C" void USART1_IRQHandler(void) {

}

#include "usart.inl"
