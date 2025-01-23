//
// Created by Aleksandr on 22.01.2025.
//

#ifndef OMNICOMM_SLAVE_RING_BUF_H
#define OMNICOMM_SLAVE_RING_BUF_H
#include <stdint.h>

typedef struct {
    uint8_t *buffer;
    unsigned short idxIn;
    unsigned short idxOut;
    unsigned short size;
}RING_buffer_t;

//enum RING_ErrorStatus {
//    RING_ERR_OK = 0,
//    RING_ERR_FAILD = 1
//};

void RING_Put(uint8_t symbol, RING_buffer_t* buf);
uint8_t RING_Pop(RING_buffer_t *buf);
uint16_t RING_GetCount(RING_buffer_t *buf);
int32_t RING_ShowSymbol(uint16_t symbolNumber ,RING_buffer_t *buf);
void RING_Clear(RING_buffer_t* buf);
void RING_Init(RING_buffer_t *ring, uint8_t *buf, uint16_t size);
#endif //OMNICOMM_SLAVE_RING_BUF_H
