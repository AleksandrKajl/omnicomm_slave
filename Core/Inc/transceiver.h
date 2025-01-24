//
// Created by Aleksandr on 22.01.2025.
//

#ifndef OMNICOMM_SLAVE_TRANSCEIVER_H
#define OMNICOMM_SLAVE_TRANSCEIVER_H

#include <stdint.h>
#include "ring_buf.h"

//Константы
#define REQ_SZ                                      0x04

#define CMD_PREFIX                                  0x31
#define CMD_GET_DATA                                0x06
#define CMD_EXAMPLE                                 0x77
#define NET_ADDR                                    0x71

/*!
* @brief Получение сообщения из кольцевого буфера с последующим извлечением команды.
 * @param[in] ring_buff - указатель на кольцевой буфер с данными
 * @return 0 если сообщение получено и -1 если один мусор
*/
uint8_t transceiver_get_msg(RING_buffer_t *ring_buff);
/*!
* @brief Отправка сообщения.
 * @param[in] data - указатель на буфер с данными
 * @param[in] size - размер буфера данных
*/
void transceiver_send_msg(uint8_t *data, uint16_t size);

#endif //OMNICOMM_SLAVE_TRANSCEIVER_H
