//
// Created by Aleksandr on 23.01.2025.
//

#ifndef OMNICOMM_SLAVE_UART_H
#define OMNICOMM_SLAVE_UART_H
#include <stdint.h>

void UART1_RX_Callback(void);

/*!
* @brief Отправка данных по uart.
 * @param[in] dt - указатель на буфер с данными
 * @param[in] sz - размер буфера данных
*/
void UART_TX(uint8_t* dt, uint16_t sz);

/*! @brief Получение количества байтов, отброшенных из-за заполнения RX-буфера. */
uint32_t UART_get_rx_overflow_count(void);

#endif //OMNICOMM_SLAVE_UART_H
