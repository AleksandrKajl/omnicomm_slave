function(add_firmware_artifacts target_name)
    set(hex_file ${CMAKE_CURRENT_BINARY_DIR}/${target_name}.hex)
    set(bin_file ${CMAKE_CURRENT_BINARY_DIR}/${target_name}.bin)

    add_custom_command(TARGET ${target_name}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${target_name}.elf> ${hex_file}
        COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${target_name}.elf> ${bin_file}
        COMMAND ${CMAKE_SIZE} -B $<TARGET_FILE:${target_name}.elf>
        COMMENT "Генерация HEX/BIN и вывод размера прошивки"
    )
endfunction()
