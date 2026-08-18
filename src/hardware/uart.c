#include "uart.h"

#include "ring_buf.h"
#include "stm32f1xx_ll_usart.h"

extern RING_buffer_t g_rx_buff;

static uint8_t tx_buffer_data[RING_BUFF_SZ];
static RING_buffer_t tx_buffer;
static volatile uint32_t rx_overflow_count = 0;
static volatile uint32_t tx_overflow_count = 0;

void UART_init(void) {
    RING_init(&tx_buffer, tx_buffer_data, RING_BUFF_SZ);
}

void UART1_RX_Callback(void) {
    if (!RING_put(LL_USART_ReceiveData8(USART1), &g_rx_buff)) {
        rx_overflow_count++;
    }
}

void UART1_TX_Callback(void) {
    uint8_t byte = 0;

    if (RING_pop(&tx_buffer, &byte)) {
        LL_USART_TransmitData8(USART1, byte);
    } else {
        LL_USART_DisableIT_TXE(USART1);
    }
}

bool UART_TX(const uint8_t* data, uint16_t size) {
    uint16_t free_space = tx_buffer.size - 1 - RING_get_count(&tx_buffer);
    if (size > free_space) {
        tx_overflow_count++;
        return false;
    }

    for (uint16_t i = 0; i < size; i++) {
        RING_put(data[i], &tx_buffer);
    }

    LL_USART_EnableIT_TXE(USART1);

    return true;
}

uint32_t UART_get_rx_overflow_count(void) {
    return rx_overflow_count;
}

uint32_t UART_get_tx_overflow_count(void) {
    return tx_overflow_count;
}
