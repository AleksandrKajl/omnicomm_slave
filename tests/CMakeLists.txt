cmake_minimum_required(VERSION 3.20)

project(omnicomm_slave_tests C)

enable_testing()

add_executable(crc_test
    crc_test.c
    ../src/crc.c
)

target_include_directories(crc_test PRIVATE
    ../inc
)

target_compile_features(crc_test PRIVATE
    c_std_99
)

target_compile_options(crc_test PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

add_test(NAME crc_test COMMAND crc_test)

add_executable(ring_buf_test
    ring_buf_test.c
    ../src/ring_buf.c
)

target_include_directories(ring_buf_test PRIVATE
    ../inc
)

target_compile_features(ring_buf_test PRIVATE
    c_std_99
)

target_compile_options(ring_buf_test PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

add_test(NAME ring_buf_test COMMAND ring_buf_test)

add_executable(transceiver_parser_test
    transceiver_parser_test.c
    ../src/crc.c
    ../src/transceiver.c
)

target_include_directories(transceiver_parser_test PRIVATE
    ../inc
    ../inc/hardware
)

target_compile_features(transceiver_parser_test PRIVATE
    c_std_99
)

target_compile_options(transceiver_parser_test PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

add_test(NAME transceiver_parser_test COMMAND transceiver_parser_test)
