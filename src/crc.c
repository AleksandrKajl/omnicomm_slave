//
// Created by Aleksandr on 23.01.2025.
//
#include "crc.h"

uint8_t crc8_update(uint8_t data, uint8_t crc) {
    uint8_t value = data ^ crc;
    crc = 0;

    if (value & 0x01) {
        crc ^= 0x5e;
    }
    if (value & 0x02) {
        crc ^= 0xbc;
    }
    if (value & 0x04) {
        crc ^= 0x61;
    }
    if (value & 0x08) {
        crc ^= 0xc2;
    }
    if (value & 0x10) {
        crc ^= 0x9d;
    }
    if (value & 0x20) {
        crc ^= 0x23;
    }
    if (value & 0x40) {
        crc ^= 0x46;
    }
    if (value & 0x80) {
        crc ^= 0x8c;
    }

    return crc;
}

uint8_t crc8_calculate(const uint8_t* data, uint16_t size) {
    uint8_t crc = 0;

    for (uint16_t i = 0; i < size; i++) {
        crc = crc8_update(data[i], crc);
    }

    return crc;
}
