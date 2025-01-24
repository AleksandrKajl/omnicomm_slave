//
// Created by Aleksandr on 22.01.2025.
//
#include "transceiver.h"
#include "ring_buf.h"
#include "crc.h"

uint16_t treansceiver_get_msg_sz(uint8_t cmd)
{
    uint16_t size = 0;
    if (cmd == CMD_GET_DATA) {
        size = GET_DATA_SZ;
    } else if (cmd == CMD_EXAMPLE) {
        size = EXAMPLE_SZ;
    }


    return size;
}

uint8_t transceiver_get_msg(RING_buffer_t *ring_buff, uint8_t msg)
{
    extern RING_buffer_t have_cmd;
    const uint8_t cmd_offset = 2;       //Смещение cmd от начала сообщения
    uint8_t crc = 0;
    uint16_t data_cnt = RING_get_count(ring_buff);          //Количество принятых символов в буфере
    for (uint16_t i = 0; i < data_cnt; i++) {
        if (RING_peek(i, ring_buff) == CMD_PREFIX) {        //Начало запроса
            if (RING_peek(i, ring_buff) != NET_ADDR) {      //Если не нам
                i += treansceiver_get_msg_sz(RING_peek(i + cmd_offset, ring_buff));      //Пропускаем это сообщение
                ring_buff->idxOut += i;                                       //Удаляем из буфера
            }

            if (RING_peek(i + cmd_offset, ring_buff) == msg) {
                if (msg == CMD_GET_DATA) {
                    crc = get_crc((ring_buff->buffer+ring_buff->idxOut+i), GET_DATA_SZ);
                    if (crc == RING_peek(i + GET_DATA_SZ - 1, ring_buff)) {
                        ring_buff->idxOut += (i + GET_DATA_SZ);                                       //Удаляем из буфера
                        RING_put(CMD_GET_DATA, &have_cmd);                                            //Помещаем команду в кольцевой буфер для команд
                        return 0;
                    }
                } else if (msg == CMD_EXAMPLE) {                                    //Пример разных команд с разным размером
                    //ring_buff->idxOut += (i + EXAMPLE_SZ);
                    //RING_put(CMD_EXAMPLE, &have_cmd);
                    //RING_put(data1, &have_cmd);
                    //RING_put(data2, &have_cmd);
                    /*
                        ANY CODE
                    */
                }

            }
        }
    }

    ring_buff->idxOut = data_cnt;           //Удаляем проверенные данные

    return -1;
}

