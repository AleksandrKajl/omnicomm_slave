set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m3)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(TOOLCHAIN_PREFIX arm-none-eabi-)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_AR ${TOOLCHAIN_PREFIX}ar)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}size)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

function(add_cortex_m3_flags target_name)
    add_library(${target_name} INTERFACE)

    target_compile_options(${target_name} INTERFACE
        -mcpu=cortex-m3
        -mthumb
        -mthumb-interwork
        -mfloat-abi=soft
        -ffunction-sections
        -fdata-sections
        -fno-common
        -fmessage-length=0
        -Wall
        -Wextra
        -Wno-unused-parameter
        $<$<CONFIG:Debug>:-g3>
        $<$<CONFIG:Release>:-Os>
    )

    target_link_options(${target_name} INTERFACE
        -mcpu=cortex-m3
        -mthumb
        -mthumb-interwork
        -mfloat-abi=soft
        -Wl,--print-memory-usage
    )
endfunction()
