//
// Created by Aleksandr on 23.01.2025.
//
#include "uart.h"
#include "ring_buf.h"
#include "stm32f1xx_ll_usart.h"

extern RING_buffer_t g_rx_buff;

/*!
* @brief CallBack функция при поступлении данных по uart.
*/
void  UART1_RX_Callback(void)
{
    //Кладём поступившый байт в кольцевой буфер
    RING_put(LL_USART_ReceiveData8(USART1), &g_rx_buff);
}

void UART_TX(uint8_t* dt, uint16_t sz)
{
    uint16_t ind = 0;
    while (ind < sz)
    {
        //Ждём пока не уйдут все данные
        while (!LL_USART_IsActiveFlag_TXE(USART1)) {}
        //Передаём байт данных по uart
        LL_USART_TransmitData8(USART1,*(uint8_t*)(dt+ind));
        ind++;
    }
}

