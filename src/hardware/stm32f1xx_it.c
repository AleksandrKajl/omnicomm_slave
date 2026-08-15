#include "stm32f1xx_it.h"

#include "main.h"
#include "uart.h"

extern TIM_HandleTypeDef htim2;
volatile uint32_t SysTick_counter = 0;

void NMI_Handler(void) {
    while (1) {
    }
}

void HardFault_Handler(void) {
    while (1) {
    }
}

void MemManage_Handler(void) {
    while (1) {
    }
}

void BusFault_Handler(void) {
    while (1) {
    }
}

void UsageFault_Handler(void) {
    while (1) {
    }
}

void SVC_Handler(void) {
}

void DebugMon_Handler(void) {
}

void PendSV_Handler(void) {
}

void SysTick_Handler(void) {
    SysTick_counter++;
}

void TIM2_IRQHandler(void) {
    HAL_TIM_IRQHandler(&htim2);
}

void USART1_IRQHandler(void) {
    if (LL_USART_IsActiveFlag_RXNE(USART1) && LL_USART_IsEnabledIT_RXNE(USART1)) {
        UART1_RX_Callback();
    } else if (LL_USART_IsActiveFlag_ORE(USART1)) {
        LL_USART_ClearFlag_ORE(USART1);
    } else if (LL_USART_IsActiveFlag_FE(USART1)) {
        LL_USART_ClearFlag_FE(USART1);
    } else if (LL_USART_IsActiveFlag_NE(USART1)) {
        LL_USART_ClearFlag_NE(USART1);
    }
}
