//
// Created by Aleksandr on 22.01.2025.
//
#include "transceiver.h"
#include "ring_buf.h"
#include "crc.h"
#include "uart.h"
#include <string.h>

uint8_t transceiver_get_msg(RING_buffer_t *ring_buff)
{
    extern RING_buffer_t g_have_cmd;       //Кольцевой буфер для полученных команд
    const uint8_t cmd_offset = 2;       //Смещение cmd от начала сообщения
    uint8_t crc = 0;
    uint8_t symbol = 0;
    uint16_t data_cnt = RING_get_count(ring_buff);          //Количество принятых символов в буфере
    for (uint16_t i = 0; i < data_cnt; i++) {
        RING_peek(ring_buff, i, &symbol);
        if (symbol == CMD_PREFIX) {        //Начало запроса
            if (data_cnt - i < REQ_SZ) {
                break;
            }
            //Для подддержки команд разной длинны нужно их размер указывать в команде(запросе).
            crc = 0;
            for (uint16_t crc_idx = 0; crc_idx < REQ_SZ - 1; crc_idx++) {
                RING_peek(ring_buff, i + crc_idx, &symbol);
                crc = crc8_update(symbol, crc);
            }
            //Если crc сумма совпадает
            RING_peek(ring_buff, i + REQ_SZ - 1, &symbol);
            if (crc == symbol) {
                RING_peek(ring_buff, i + 1, &symbol);
                if (symbol != NET_ADDR) {          //Если не нам
                    i += REQ_SZ;                                                  //Пропускаем это сообщение
                    continue;
                }
                //Помещаем команду в кольцевой буфер для команд
                RING_peek(ring_buff, i + cmd_offset, &symbol);
                if (!RING_put(symbol, &g_have_cmd)) {
                    return -1;
                }
                //Удаляем из буфера
                RING_leave(i + REQ_SZ, ring_buff);
                return 0;
            }
        }
    }

    //Если нет не одного сообщения, удаляем проверенные данные
    RING_leave(data_cnt, ring_buff);

    return -1;
}

void transceiver_send_msg(uint8_t *data, uint8_t cmd , uint16_t size)
{
    //Заполняем структуру служебными данными
    Service_info_t src_info;
    src_info.prefix = 0x3E;
    src_info.net_addr = NET_ADDR;
    src_info.cmd = cmd;

    const uint16_t send_arrsz = size + sizeof(Service_info_t) + 1;
    //Создаём массив для отправляемых данных
    uint8_t send_arr[send_arrsz];
    //Заполняем служебными данными
    memcpy(send_arr, &src_info, sizeof(Service_info_t));
    //Сами данные
    memcpy(send_arr + sizeof(Service_info_t), data, size);
    //Вычесляем crc сумму всех данных
    uint8_t crc = crc8_calculate(send_arr, send_arrsz - 1);        //Размер массива без crc суммы
    send_arr[send_arrsz - 1] = crc;                             //Добавляем к передоваемым данным
    UART_TX(send_arr, send_arrsz);                              //Отправляем данные по uart
}

