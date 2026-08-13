//
// Created by Aleksandr on 23.01.2025.
//
#include "crc.h"

uint8_t get_crc(const uint8_t *data, uint16_t size)
{
    uint8_t crc = 0;
    uint8_t res = 0;
    for (uint16_t i = 0; i < size; i++) {
        res = data[i] ^ crc;
        if(res & 0x01) crc ^= 0x5e;
        if(res & 0x02) crc ^= 0xbc;
        if(res & 0x04) crc ^= 0x61;
        if(res & 0x08) crc ^= 0xc2;
        if(res & 0x10) crc ^= 0x9d;
        if(res & 0x20) crc ^= 0x23;
        if(res & 0x40) crc ^= 0x46;
        if(res & 0x80) crc ^= 0x8c;
    }

    return crc;
}