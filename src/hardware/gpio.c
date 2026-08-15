#include "gpio.h"

#include "stm32f1xx_ll_bus.h"

void GPIO_init(void) {
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOD);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
}
