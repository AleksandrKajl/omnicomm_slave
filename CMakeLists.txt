cmake_minimum_required(VERSION 3.20)

# ==================================================================
# ПОДКЛЮЧЕНИЕ МОДУЛЕЙ
# ==================================================================
include(cmake/toolchain.cmake)
include(cmake/stm32_hal.cmake)
include(cmake/firmware.cmake)

# ==================================================================
# ПРОЕКТ
# ==================================================================
project(omnicomm_slave C CXX ASM)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==================================================================
# ОБЩИЕ ФЛАГИ И STM32 HAL
# ==================================================================
add_cortex_m3_flags(cortex_m3_flags)
add_stm32_hal(stm32_hal)

# ==================================================================
# ПРОШИВКА
# ==================================================================
add_executable(${PROJECT_NAME}.elf
    src/main.c
    src/crc.c
    src/ring_buf.c
    src/sensor.c
    src/transceiver.c
    src/hardware/gpio.c
    src/hardware/stm32f1xx_hal_msp.c
    src/hardware/stm32f1xx_hal_timebase_tim.c
    src/hardware/stm32f1xx_it.c
    src/hardware/syscalls.c
    src/hardware/sysmem.c
    src/hardware/system_stm32f1xx.c
    src/hardware/uart.c
    src/hardware/usart.c
    src/hardware/startup_stm32f103c8tx.s
)

target_include_directories(${PROJECT_NAME}.elf PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/hardware
)

target_link_libraries(${PROJECT_NAME}.elf PRIVATE
    stm32_hal
    cortex_m3_flags
)

target_link_options(${PROJECT_NAME}.elf PRIVATE
    -T${CMAKE_CURRENT_SOURCE_DIR}/STM32F103C8TX_FLASH.ld
    -Wl,-Map=${PROJECT_NAME}.map
    -Wl,-gc-sections
)

# ==================================================================
# ПОСТ-ОБРАБОТКА
# ==================================================================
add_firmware_artifacts(${PROJECT_NAME})
