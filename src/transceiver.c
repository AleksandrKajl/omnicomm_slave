#include "transceiver.h"

#include "crc.h"
#include "uart.h"

#include <string.h>

static void parser_wait_for_prefix(Transceiver_parser_t* parser, uint8_t byte) {
    parser->state = TRANSCEIVER_WAIT_PREFIX;
    parser->crc = 0;

    if (byte == CMD_PREFIX) {
        parser->crc = crc8_update(byte, parser->crc);
        parser->state = TRANSCEIVER_WAIT_ADDRESS;
    }
}

static void parser_recover(Transceiver_parser_t* parser, uint8_t byte) {
    uint8_t previous_address = parser->address;
    uint8_t previous_command = parser->command;

    if (previous_address == CMD_PREFIX) {
        parser->crc = crc8_update(CMD_PREFIX, 0);
        parser->address = previous_command;
        parser->crc = crc8_update(parser->address, parser->crc);
        parser->command = byte;
        parser->crc = crc8_update(parser->command, parser->crc);
        parser->state = TRANSCEIVER_WAIT_CRC;
    } else if (previous_command == CMD_PREFIX) {
        parser->crc = crc8_update(CMD_PREFIX, 0);
        parser->address = byte;
        parser->crc = crc8_update(parser->address, parser->crc);
        parser->state = TRANSCEIVER_WAIT_COMMAND;
    } else {
        parser_wait_for_prefix(parser, byte);
    }
}

void transceiver_parser_init(Transceiver_parser_t* parser) {
    parser->address = 0;
    parser->command = 0;
    parser_wait_for_prefix(parser, 0);
}

bool transceiver_parse_byte(Transceiver_parser_t* parser, uint8_t byte, uint8_t* command) {
    switch (parser->state) {
    case TRANSCEIVER_WAIT_PREFIX:
        parser_wait_for_prefix(parser, byte);
        break;

    case TRANSCEIVER_WAIT_ADDRESS:
        parser->address = byte;
        parser->crc = crc8_update(byte, parser->crc);
        parser->state = TRANSCEIVER_WAIT_COMMAND;
        break;

    case TRANSCEIVER_WAIT_COMMAND:
        parser->command = byte;
        parser->crc = crc8_update(byte, parser->crc);
        parser->state = TRANSCEIVER_WAIT_CRC;
        break;

    case TRANSCEIVER_WAIT_CRC:
        if (byte == parser->crc) {
            bool addressed_to_device = parser->address == NET_ADDR;
            if (addressed_to_device) {
                *command = parser->command;
            }
            parser_wait_for_prefix(parser, 0);
            return addressed_to_device;
        }

        parser_recover(parser, byte);
        break;
    }

    return false;
}

void transceiver_send_msg(const uint8_t* data, uint8_t command, uint16_t size) {
    Service_info_t service_info;
    service_info.prefix = 0x3E;
    service_info.net_addr = NET_ADDR;
    service_info.cmd = command;

    const uint16_t message_size = size + sizeof(Service_info_t) + 1;
    uint8_t message[message_size];

    memcpy(message, &service_info, sizeof(Service_info_t));
    memcpy(message + sizeof(Service_info_t), data, size);

    message[message_size - 1] = crc8_calculate(message, message_size - 1);
    (void)UART_TX(message, message_size);
}
