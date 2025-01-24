//
// Created by Aleksandr on 22.01.2025.
//
#include "transceiver.h"
#include "ring_buf.h"
#include "crc.h"

uint8_t transceiver_get_msg(RING_buffer_t *ring_buff)
{
    extern RING_buffer_t have_cmd;       //Кольцевой буфер для полученных команд
    const uint8_t cmd_offset = 2;       //Смещение cmd от начала сообщения
    uint8_t crc = 0;
    uint16_t data_cnt = RING_get_count(ring_buff);          //Количество принятых символов в буфере
    for (uint16_t i = 0; i < data_cnt; i++) {
        if (RING_peek(i, ring_buff) == CMD_PREFIX) {        //Начало запроса
            //Для подддержки команд разной длинны нужно их размер указывать в команде(запросе).
            crc = get_crc(RING_get_ptrdata(i, ring_buff), REQ_SZ);
            if (crc == RING_peek(i + REQ_SZ - 1, ring_buff)) {
                if (RING_peek(i+1, ring_buff) != NET_ADDR) {          //Если не нам
                    i += REQ_SZ;                                                  //Пропускаем это сообщение
                    RING_leave(i, ring_buff);                                     //Удаляем из буфера
                }

                RING_put(RING_peek(i+cmd_offset, ring_buff), &have_cmd);                                            //Помещаем команду в кольцевой буфер для команд
                RING_leave(i + REQ_SZ, ring_buff);                                                                                  //Удаляем из буфера
                return 0;
            }
        }
    }

    RING_leave(data_cnt, ring_buff);                        //Удаляем проверенные данные

    return -1;
}

