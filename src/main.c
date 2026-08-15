#include "main.h"

#include "gpio.h"
#include "ring_buf.h"
#include "sensor.h"
#include "transceiver.h"
#include "usart.h"

#include <string.h>

RING_buffer_t g_rx_buff;
RING_buffer_t g_have_cmd;

static void system_clock_init(void);

int main(void) {
    HAL_Init();
    system_clock_init();
    GPIO_init();
    USART_init();

    SysTick_Config(SystemCoreClock / 1000);

    uint8_t rx_buffer_data[RING_BUFF_SZ];
    uint8_t command_buffer_data[RING_BUFF_SZ];

    RING_init(&g_rx_buff, rx_buffer_data, RING_BUFF_SZ);
    RING_init(&g_have_cmd, command_buffer_data, RING_BUFF_SZ);

    LL_USART_EnableIT_RXNE(USART1);
    LL_USART_EnableIT_ERROR(USART1);

    Sensor_data_t sensor_data;
    memset(&sensor_data, 0, sizeof(sensor_data));

    while (1) {
        if (RING_get_count(&g_rx_buff) >= REQ_SZ) {
            transceiver_get_msg(&g_rx_buff);
        }

        uint8_t command = 0;
        if (RING_pop(&g_have_cmd, &command)) {
            if (command == CMD_GET_DATA) {
                sensor_get_data(&sensor_data);
                transceiver_send_msg((uint8_t*)&sensor_data, CMD_GET_DATA, sizeof(sensor_data));
            } else if (command == CMD_EXAMPLE) {
                // Резерв для добавления следующей команды протокола.
            }
        }

        LL_mDelay(100);
    }
}

static void system_clock_init(void) {
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
    while (LL_FLASH_GetLatency() != LL_FLASH_LATENCY_2) {
    }

    LL_RCC_HSE_Enable();
    while (LL_RCC_HSE_IsReady() != 1) {
    }

    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, LL_RCC_PLL_MUL_9);
    LL_RCC_PLL_Enable();
    while (LL_RCC_PLL_IsReady() != 1) {
    }

    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) {
    }

    LL_SetSystemCoreClock(72000000);
    if (HAL_InitTick(TICK_INT_PRIORITY) != HAL_OK) {
        Error_Handler();
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* timer) {
    if (timer->Instance == TIM2) {
        HAL_IncTick();
    }
}

void Error_Handler(void) {
    __disable_irq();
    while (1) {
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
    (void)file;
    (void)line;
}
#endif
