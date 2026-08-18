#include "transceiver.h"

#include "crc.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

bool UART_TX(const uint8_t* data, uint16_t size) {
    (void)data;
    (void)size;
    return true;
}

static int check(bool condition, const char* message) {
    if (!condition) {
        printf("%s\n", message);
        return 1;
    }

    return 0;
}

static void make_request(uint8_t address, uint8_t command, uint8_t* request) {
    request[0] = CMD_PREFIX;
    request[1] = address;
    request[2] = command;
    request[3] = crc8_calculate(request, 3);
}

static bool parse_request(Transceiver_parser_t* parser, const uint8_t* request, uint16_t size, uint8_t* command) {
    bool received = false;

    for (uint16_t i = 0; i < size; i++) {
        if (transceiver_parse_byte(parser, request[i], command)) {
            received = true;
        }
    }

    return received;
}

static int test_valid_request(void) {
    uint8_t request[4];
    make_request(NET_ADDR, CMD_GET_DATA, request);

    Transceiver_parser_t parser;
    transceiver_parser_init(&parser);
    uint8_t command = 0;

    int failed = 0;
    failed += check(parse_request(&parser, request, sizeof(request), &command), "valid request was not accepted");
    failed += check(command == CMD_GET_DATA, "valid request returned an incorrect command");

    return failed;
}

static int test_incomplete_request(void) {
    uint8_t request[4];
    make_request(NET_ADDR, CMD_GET_DATA, request);

    Transceiver_parser_t parser;
    transceiver_parser_init(&parser);
    uint8_t command = 0;

    int failed = 0;
    failed += check(!parse_request(&parser, request, 2, &command), "incomplete request was accepted");
    failed += check(parse_request(&parser, request + 2, 2, &command), "continued request was not accepted");

    return failed;
}

static int test_noise_and_back_to_back_requests(void) {
    uint8_t first_request[4];
    uint8_t second_request[4];
    make_request(NET_ADDR, CMD_GET_DATA, first_request);
    make_request(NET_ADDR, CMD_EXAMPLE, second_request);

    Transceiver_parser_t parser;
    transceiver_parser_init(&parser);
    uint8_t command = 0;
    uint8_t received_count = 0;

    const uint8_t noise[] = {0x00, 0x12, 0x30};
    parse_request(&parser, noise, sizeof(noise), &command);

    for (uint16_t i = 0; i < sizeof(first_request); i++) {
        if (transceiver_parse_byte(&parser, first_request[i], &command)) {
            received_count++;
        }
    }
    for (uint16_t i = 0; i < sizeof(second_request); i++) {
        if (transceiver_parse_byte(&parser, second_request[i], &command)) {
            received_count++;
        }
    }

    int failed = 0;
    failed += check(received_count == 2, "back-to-back requests were not both accepted");
    failed += check(command == CMD_EXAMPLE, "second request returned an incorrect command");

    return failed;
}

static int test_wrong_address_and_crc(void) {
    uint8_t request[4];
    make_request(NET_ADDR + 1, CMD_GET_DATA, request);

    Transceiver_parser_t parser;
    transceiver_parser_init(&parser);
    uint8_t command = 0;

    int failed = 0;
    failed += check(!parse_request(&parser, request, sizeof(request), &command), "request for another address was accepted");

    make_request(NET_ADDR, CMD_GET_DATA, request);
    request[3] ^= 0x01;
    failed += check(!parse_request(&parser, request, sizeof(request), &command), "request with invalid CRC was accepted");

    return failed;
}

static int test_recovery_after_invalid_crc(void) {
    uint8_t request[4];
    make_request(NET_ADDR, CMD_GET_DATA, request);

    Transceiver_parser_t parser;
    transceiver_parser_init(&parser);
    uint8_t command = 0;

    const uint8_t damaged_request[] = {CMD_PREFIX, NET_ADDR, CMD_GET_DATA, CMD_PREFIX};
    int failed = 0;
    failed += check(!parse_request(&parser, damaged_request, sizeof(damaged_request), &command), "damaged request was accepted");
    failed += check(parse_request(&parser, request + 1, 3, &command), "parser did not recover at the next prefix");

    return failed;
}

static int test_recovery_after_abandoned_request(void) {
    uint8_t request[4];
    make_request(NET_ADDR, CMD_GET_DATA, request);

    Transceiver_parser_t parser;
    transceiver_parser_init(&parser);
    uint8_t command = 0;

    int failed = 0;
    failed += check(!parse_request(&parser, request, 2, &command), "incomplete request was accepted");
    failed += check(parse_request(&parser, request, sizeof(request), &command), "parser did not recover after an abandoned request");

    return failed;
}

int main(void) {
    int failed = 0;

    failed += test_valid_request();
    failed += test_incomplete_request();
    failed += test_noise_and_back_to_back_requests();
    failed += test_wrong_address_and_crc();
    failed += test_recovery_after_invalid_crc();
    failed += test_recovery_after_abandoned_request();

    if (failed == 0) {
        printf("Transceiver parser tests passed\n");
    }

    return failed;
}
