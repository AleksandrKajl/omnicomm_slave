#ifndef OMNICOMM_SLAVE_TRANSCEIVER_H
#define OMNICOMM_SLAVE_TRANSCEIVER_H

#include <stdbool.h>
#include <stdint.h>

#define CMD_PREFIX 0x31
#define CMD_GET_DATA 0x06
#define CMD_EXAMPLE 0x77
#define NET_ADDR 0x71

typedef struct {
    uint8_t prefix;
    uint8_t net_addr;
    uint8_t cmd;
} __attribute__((packed)) Service_info_t;

typedef enum {
    TRANSCEIVER_WAIT_PREFIX,
    TRANSCEIVER_WAIT_ADDRESS,
    TRANSCEIVER_WAIT_COMMAND,
    TRANSCEIVER_WAIT_CRC,
} Transceiver_parser_state_t;

typedef struct {
    Transceiver_parser_state_t state;
    uint8_t address;
    uint8_t command;
    uint8_t crc;
} Transceiver_parser_t;

void transceiver_parser_init(Transceiver_parser_t* parser);

/*! @return true, если получен корректный запрос, адресованный устройству. */
bool transceiver_parse_byte(Transceiver_parser_t* parser, uint8_t byte, uint8_t* command);

/*! @return Размер сформированного ответа или 0, если буфер слишком мал. */
uint16_t transceiver_build_response(uint8_t* response, uint16_t response_capacity, const uint8_t* data, uint8_t command, uint16_t size);

#endif // OMNICOMM_SLAVE_TRANSCEIVER_H
