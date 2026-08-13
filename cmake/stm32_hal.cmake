set(STM32_DRIVERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Drivers)
set(STM32_HAL_DIR ${STM32_DRIVERS_DIR}/STM32F1xx_HAL_Driver)
set(STM32_CMSIS_DIR ${STM32_DRIVERS_DIR}/CMSIS)

function(add_stm32_hal target_name)
    add_library(${target_name} STATIC
        ${STM32_HAL_DIR}/Src/stm32f1xx_hal.c
        ${STM32_HAL_DIR}/Src/stm32f1xx_hal_cortex.c
        ${STM32_HAL_DIR}/Src/stm32f1xx_hal_dma.c
        ${STM32_HAL_DIR}/Src/stm32f1xx_hal_exti.c
        ${STM32_HAL_DIR}/Src/stm32f1xx_hal_flash.c
        ${STM32_HAL_DIR}/Src/stm32f1xx_hal_flash_ex.c
        ${STM32_HAL_DIR}/Src/stm32f1xx_hal_gpio.c
        ${STM32_HAL_DIR}/Src/stm32f1xx_hal_gpio_ex.c
        ${STM32_HAL_DIR}/Src/stm32f1xx_hal_pwr.c
        ${STM32_HAL_DIR}/Src/stm32f1xx_hal_rcc.c
        ${STM32_HAL_DIR}/Src/stm32f1xx_hal_rcc_ex.c
        ${STM32_HAL_DIR}/Src/stm32f1xx_hal_tim.c
        ${STM32_HAL_DIR}/Src/stm32f1xx_hal_tim_ex.c
        ${STM32_HAL_DIR}/Src/stm32f1xx_ll_dma.c
        ${STM32_HAL_DIR}/Src/stm32f1xx_ll_exti.c
        ${STM32_HAL_DIR}/Src/stm32f1xx_ll_gpio.c
        ${STM32_HAL_DIR}/Src/stm32f1xx_ll_rcc.c
        ${STM32_HAL_DIR}/Src/stm32f1xx_ll_usart.c
        ${STM32_HAL_DIR}/Src/stm32f1xx_ll_utils.c
    )

    target_include_directories(${target_name} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc/hardware
        ${STM32_HAL_DIR}/Inc
        ${STM32_HAL_DIR}/Inc/Legacy
        ${STM32_CMSIS_DIR}/Device/ST/STM32F1xx/Include
        ${STM32_CMSIS_DIR}/Include
    )

    target_compile_definitions(${target_name} PUBLIC
        DEBUG
        STM32F103xB
        USE_FULL_LL_DRIVER
        USE_HAL_DRIVER
    )

    target_link_libraries(${target_name} PUBLIC
        cortex_m3_flags
    )
endfunction()
