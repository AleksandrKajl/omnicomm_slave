//
// Created by Aleksandr on 22.01.2025.
//
#include "transceiver.h"
#include "ring_buf.h"
#include <string.h>

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

uint8_t check_crc()
{

}


uint16_t get_msg_sz(uint8_t cmd)
{
    uint16_t size = 0;
    if (cmd == CMD_GET_DATA) {
        size = GET_DATA_SZ;
    }

    return size;
}

uint8_t get_msg(RING_buffer_t *ring_buff, uint8_t msg)
{
    extern RING_buffer_t have_cmd;
    const uint8_t cmd_offset = 2;       //Смещение cmd от начала сообщения
    uint8_t crc = 0;
    uint16_t data_cnt = RING_get_count(ring_buff);          //Количество принятых символов в буфере
    for (uint16_t i = 0; i < data_cnt; i++) {
        if (RING_peek(i, ring_buff) == CMD_PREFIX) {        //Начало запроса
            if (RING_peek(i, ring_buff) != NET_ADDR) {      //Если не нам
                i += get_msg_sz(RING_peek(i + cmd_offset, ring_buff));      //Пропускаем это сообщение
                ring_buff->idxOut += (i + GET_DATA_SZ);                                       //Удаляем из буфера
            }

            if (RING_peek(i + cmd_offset, ring_buff) == msg) {
                if (msg == CMD_GET_DATA) {
                    crc = get_crc((ring_buff->buffer+ring_buff->idxOut+i), GET_DATA_SZ);
                    if (crc == RING_peek(i + GET_DATA_SZ - 1, ring_buff)) {
                        ring_buff->idxOut += (i + GET_DATA_SZ);                                       //Удаляем из буфера
                        RING_put(CMD_GET_DATA, &have_cmd);
                        return 0;
                    }
                }
            }
        }
    }

    return -1;
}

