#ifndef OMNICOMM_SLAVE_MAIN_H
#define OMNICOMM_SLAVE_MAIN_H

#include "stm32f1xx_hal.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_cortex.h"
#include "stm32f1xx_ll_dma.h"
#include "stm32f1xx_ll_exti.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_pwr.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_usart.h"
#include "stm32f1xx_ll_utils.h"

void Error_Handler(void);

#endif // OMNICOMM_SLAVE_MAIN_H
