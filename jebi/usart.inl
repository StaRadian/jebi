#pragma once

#include "stm32g4xx_ll_gpio.h"
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_rcc.h"
#include "stm32g4xx_ll_usart.h"

#include "usart.hpp"

namespace jebi
{
inline USART::USART()
{
    /* (2) NVIC Configuration for USART interrupts */
    /*  - Set priority for USARTx_IRQn */
    /*  - Enable USARTx_IRQn */
    // NVIC_SetPriority(USART1_IRQn, 0);  
    // NVIC_EnableIRQ(USART1_IRQn);

    /* (3) Enable USART peripheral clock and clock source ***********************/
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

    /* Set clock source */
    LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK2);

    /* (4) Configure USART functional parameters ********************************/

    /* Disable USART prior modifying configuration registers */
    /* Note: Commented as corresponding to Reset value */
    // LL_USART_Disable(USARTx_INSTANCE);

    /* TX/RX direction */
    LL_USART_SetTransferDirection(USART1, LL_USART_DIRECTION_TX_RX);

    /* 8 data bit, 1 start bit, 1 stop bit, no parity */
    LL_USART_ConfigCharacter(USART1, LL_USART_DATAWIDTH_8B, LL_USART_PARITY_NONE, LL_USART_STOPBITS_1);

    /* No Hardware Flow control */
    /* Reset value is LL_USART_HWCONTROL_NONE */
    // LL_USART_SetHWFlowCtrl(USARTx_INSTANCE, LL_USART_HWCONTROL_NONE);

    /* Oversampling by 16 */
    /* Reset value is LL_USART_OVERSAMPLING_16 */
    //LL_USART_SetOverSampling(USARTx_INSTANCE, LL_USART_OVERSAMPLING_16);

    /* Set Baudrate to 115200 using APB frequency set to 170000000 Hz */
    /* Frequency available for USART peripheral can also be calculated through LL RCC macro */
    /* Ex :
        Periphclk = LL_RCC_GetUSARTClockFreq(Instance); or LL_RCC_GetUARTClockFreq(Instance); depending on USART/UART instance

        In this example, Peripheral Clock is expected to be equal to 170000000 Hz => equal to SystemCoreClock
    */
    LL_USART_SetBaudRate(USART1, SystemCoreClock, LL_USART_PRESCALER_DIV1, LL_USART_OVERSAMPLING_16, 115200); 

    /* (5) Enable USART *********************************************************/
    LL_USART_Enable(USART1);

    /* Polling USART initialisation */
    while((!(LL_USART_IsActiveFlag_TEACK(USART1))) || (!(LL_USART_IsActiveFlag_REACK(USART1))))
    {
    }

    // /* Enable RXNE and Error interrupts */
    LL_USART_EnableIT_RXNE(USART1);
    LL_USART_EnableIT_ERROR(USART1);
}

inline void USART::gpio(GPIO_TypeDef *GPIOx, const uint32_t Pin)
{
    LL_GPIO_SetPinMode(GPIOx, Pin, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetAFPin_0_7(GPIOx, Pin, LL_GPIO_AF_7);
    LL_GPIO_SetPinSpeed(GPIOx, Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(GPIOx, Pin, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinPull(GPIOx, Pin, LL_GPIO_PULL_UP);
}

inline void USART::tx(uint8_t value)
{
    LL_USART_TransmitData8(USART1, value);
}

} // namespace jebi