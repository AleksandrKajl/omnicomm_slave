//
// Created by Aleksandr on 22.01.2025.
//

#ifndef OMNICOMM_SLAVE_TRANSCEIVER_H
#define OMNICOMM_SLAVE_TRANSCEIVER_H

#include <stdint.h>

#define GET_DATA_SZ                                 0x04

#define CMD_PREFIX                                  0x31
#define CMD_GET_DATA                                0x06
#define NET_ADDR                                    0x71


typedef struct {
    uint8_t prefix;
    uint16_t addr;
    uint16_t cmd;
    uint16_t crc;
}Request_data_t;

uint8_t check_crc();

#endif //OMNICOMM_SLAVE_TRANSCEIVER_H
