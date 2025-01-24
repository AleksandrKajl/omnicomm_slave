//
// Created by Aleksandr on 23.01.2025.
//
#include "uart.h"
#include "ring_buf.h"
#include "stm32f1xx_ll_usart.h"

extern RING_buffer_t rx_buff;

void  UART1_RX_Callback(void)
{
    RING_put(LL_USART_ReceiveData8(USART1), &rx_buff);
}

void UART_TX(uint8_t* dt, uint16_t sz)
{
    uint16_t ind = 0;
    while (ind < sz)
    {
        while (!LL_USART_IsActiveFlag_TXE(USART1)) {}
        LL_USART_TransmitData8(USART1,*(uint8_t*)(dt+ind));
        ind++;
    }
}

