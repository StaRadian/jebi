#pragma once
#include "stm32g4xx.h"

namespace jebi
{
  
class USART
{
  public:
  inline constexpr USART(USART_TypeDef *USARTx);
    inline void gpio(GPIO_TypeDef *GPIOx, const uint32_t Pin);

    inline void tx(uint8_t value);
    inline uint8_t rx();
    
  private:
    inline void config();
    USART_TypeDef *m_usartx;

};

} // namespace jebi

extern "C" void USART1_IRQHandler(void) {

}

extern "C" void USART2_IRQHandler(void) {

}

extern "C" void USART3_IRQHandler(void) {

}

extern "C" void UART4_IRQHandler(void) {

}

extern "C" void UART5_IRQHandler(void) {

}

#include "usart.inl"
