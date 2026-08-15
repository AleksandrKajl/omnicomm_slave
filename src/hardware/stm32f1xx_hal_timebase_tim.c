#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"

TIM_HandleTypeDef htim2;

HAL_StatusTypeDef HAL_InitTick(uint32_t tick_priority) {
    RCC_ClkInitTypeDef clock_config;
    uint32_t flash_latency;
    HAL_RCC_GetClockConfig(&clock_config, &flash_latency);

    uint32_t timer_clock = HAL_RCC_GetPCLK1Freq();
    if (clock_config.APB1CLKDivider != RCC_HCLK_DIV1) {
        timer_clock *= 2;
    }

    __HAL_RCC_TIM2_CLK_ENABLE();

    htim2.Instance = TIM2;
    htim2.Init.Period = 1000 - 1;
    htim2.Init.Prescaler = (timer_clock / 1000000) - 1;
    htim2.Init.ClockDivision = 0;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    HAL_StatusTypeDef status = HAL_TIM_Base_Init(&htim2);
    if (status != HAL_OK) {
        return status;
    }

    status = HAL_TIM_Base_Start_IT(&htim2);
    if (status != HAL_OK) {
        return status;
    }

    if (tick_priority >= (1UL << __NVIC_PRIO_BITS)) {
        return HAL_ERROR;
    }

    HAL_NVIC_SetPriority(TIM2_IRQn, tick_priority, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
    uwTickPrio = tick_priority;

    return HAL_OK;
}

void HAL_SuspendTick(void) {
    __HAL_TIM_DISABLE_IT(&htim2, TIM_IT_UPDATE);
}

void HAL_ResumeTick(void) {
    __HAL_TIM_ENABLE_IT(&htim2, TIM_IT_UPDATE);
}
