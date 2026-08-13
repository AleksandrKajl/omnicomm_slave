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
    uint16_t data_cnt = RING_get_count(ring_buff);          //Количество принятых символов в буфере
    for (uint16_t i = 0; i < data_cnt; i++) {
        if (RING_peek(i, ring_buff) == CMD_PREFIX) {        //Начало запроса
            //Для подддержки команд разной длинны нужно их размер указывать в команде(запросе).
            crc = get_crc(RING_get_ptrdata(i, ring_buff), REQ_SZ);
            //Если crc сумма совпадает
            if (crc == RING_peek(i + REQ_SZ - 1, ring_buff)) {
                if (RING_peek(i+1, ring_buff) != NET_ADDR) {          //Если не нам
                    i += REQ_SZ;                                                  //Пропускаем это сообщение
                    continue;
                }
                //Помещаем команду в кольцевой буфер для команд
                RING_put(RING_peek(i+cmd_offset, ring_buff), &g_have_cmd);
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
    uint8_t crc = get_crc(send_arr, send_arrsz - 2);        //Размер массива без crc суммы
    send_arr[send_arrsz - 1] = crc;                             //Добавляем к передоваемым данным
    UART_TX(send_arr, send_arrsz);                              //Отправляем данные по uart
}

