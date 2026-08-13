//
// Created by Aleksandr on 23.01.2025.
//

#ifndef OMNICOMM_SLAVE_UART_H
#define OMNICOMM_SLAVE_UART_H
#include <stdint.h>

/*!
* @brief Отправка данных по uart.
 * @param[in] dt - указатель на буфер с данными
 * @param[in] sz - размер буфера данных
*/
void UART_TX(uint8_t* dt, uint16_t sz);

#endif //OMNICOMM_SLAVE_UART_H
