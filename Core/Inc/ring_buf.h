//
// Created by Aleksandr on 22.01.2025.
//

#ifndef OMNICOMM_SLAVE_RING_BUF_H
#define OMNICOMM_SLAVE_RING_BUF_H
#include <stdint.h>

#define RING_BUFF_SZ                                                0x100

typedef struct{
    uint8_t *buffer;
    uint16_t idxIn;
    uint16_t idxOut;
    uint16_t size;
}RING_buffer_t;

void RING_put(uint8_t symbol, RING_buffer_t* buf);
uint8_t RING_pop(RING_buffer_t *buf);
void RING_leave(uint16_t idx, RING_buffer_t *buf);
uint8_t* RING_get_ptrdata(uint16_t idx, RING_buffer_t *buf);
uint16_t RING_get_count(RING_buffer_t *buf);
int32_t RING_peek(uint16_t symbolNumber ,RING_buffer_t *buf);
void RING_clear(RING_buffer_t* buf);
void RING_init(RING_buffer_t *ring, uint8_t *buf, uint16_t size);
#endif //OMNICOMM_SLAVE_RING_BUF_H
