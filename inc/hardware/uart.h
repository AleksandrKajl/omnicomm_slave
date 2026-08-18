#ifndef OMNICOMM_SLAVE_UART_H
#define OMNICOMM_SLAVE_UART_H

#include <stdbool.h>
#include <stdint.h>

void UART_init(void);
void UART1_RX_Callback(void);
void UART1_TX_Callback(void);

/*! @return true, если всё сообщение помещено в очередь передачи. */
bool UART_TX(const uint8_t* data, uint16_t size);

/*! @brief Получение количества байтов, отброшенных из-за заполнения RX-буфера. */
uint32_t UART_get_rx_overflow_count(void);

/*! @brief Получение количества сообщений, не поместившихся в очередь передачи. */
uint32_t UART_get_tx_overflow_count(void);

#endif // OMNICOMM_SLAVE_UART_H
