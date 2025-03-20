#include "runtime.hpp"

#include "stm32g4xx_ll_bus.h"

#include "stm32g4xx_ll_rcc.h"
#include "stm32g4xx_ll_system.h"
#include "stm32g4xx_ll_utils.h"
#include "stm32g4xx_ll_exti.h"
#include "stm32g4xx_ll_pwr.h"

#include "led.hpp"
#include "usart.hpp"

void SystemClock_Config(void);

inline void init(void)
{
	SystemClock_Config();

	LL_AHB2_GRP1_EnableClock(
		LL_AHB2_GRP1_PERIPH_GPIOC |
		LL_AHB2_GRP1_PERIPH_GPIOF
	);
}

int main(void)
{
	init();

	jebi::LED red_led(GPIOF, LL_GPIO_PIN_10);
	jebi::USART usart(USART1);

	usart.gpio(GPIOC, LL_GPIO_PIN_4);
	usart.gpio(GPIOC, LL_GPIO_PIN_5);

	while(1)
	{
		usart.tx('a');
		red_led.on();
		LL_mDelay(500);
		red_led.off();
		LL_mDelay(500);
	}
	return 0;
}

void SystemClock_Config(void)
{
	/* Flash Latency configuration */
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_4);

	/* Enable boost mode to be able to reach 170MHz */
	LL_PWR_EnableRange1BoostMode();

	/* HSI configuration and activation */
	LL_RCC_HSI_Enable();
	while(LL_RCC_HSI_IsReady() != 1)
	{
	};

	/* Main PLL configuration and activation */
	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_4, 85, LL_RCC_PLLR_DIV_2);
	LL_RCC_PLL_Enable();
	LL_RCC_PLL_EnableDomain_SYS();
	while(LL_RCC_PLL_IsReady() != 1)
	{
	};

	/* Sysclk activation on the main PLL */
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_2);
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
	while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
	{
	};

	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	/* Insure 1µs transition state at intermediate medium speed clock based on DWT */
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
	while(DWT->CYCCNT < 100);
	/* Set APB1 & APB2 prescaler*/
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
	LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

	/* Set systick to 1ms in using frequency set to 170MHz */
	/* This frequency can be calculated through LL RCC macro */
	/* ex: __LL_RCC_CALC_PLLCLK_FREQ(__LL_RCC_CALC_HSI_FREQ(),
									LL_RCC_PLLM_DIV_4, 85, LL_RCC_PLLR_DIV_2)*/
	LL_Init1msTick(170000000);

	/* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
	LL_SetSystemCoreClock(170000000);
}