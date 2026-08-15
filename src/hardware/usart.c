#include "usart.h"

#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_usart.h"

void USART_init(void) {
    LL_USART_InitTypeDef usart_config = {0};
    LL_GPIO_InitTypeDef gpio_config = {0};

    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);

    gpio_config.Pin = LL_GPIO_PIN_9;
    gpio_config.Mode = LL_GPIO_MODE_ALTERNATE;
    gpio_config.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    gpio_config.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    LL_GPIO_Init(GPIOA, &gpio_config);

    gpio_config.Pin = LL_GPIO_PIN_10;
    gpio_config.Mode = LL_GPIO_MODE_FLOATING;
    LL_GPIO_Init(GPIOA, &gpio_config);

    NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_EnableIRQ(USART1_IRQn);

    usart_config.BaudRate = 19200;
    usart_config.DataWidth = LL_USART_DATAWIDTH_8B;
    usart_config.StopBits = LL_USART_STOPBITS_1;
    usart_config.Parity = LL_USART_PARITY_NONE;
    usart_config.TransferDirection = LL_USART_DIRECTION_TX_RX;
    usart_config.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
    usart_config.OverSampling = LL_USART_OVERSAMPLING_16;
    LL_USART_Init(USART1, &usart_config);
    LL_USART_ConfigAsyncMode(USART1);
    LL_USART_Enable(USART1);
}
