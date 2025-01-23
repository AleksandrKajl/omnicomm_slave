//
// Created by Aleksandr on 22.01.2025.
//
#include "ring_buf.h"

void RING_Put(uint8_t symbol, RING_buffer_t* buf) {
    buf->buffer[buf->idxIn++] = symbol;
    if (buf->idxIn >= buf->size) {
        buf->idxIn = 0;
    }
}

uint8_t RING_Pop(RING_buffer_t *buf)
{
    uint8_t retval = buf->buffer[buf->idxOut++];
    if (buf->idxOut >= buf->size) {
        buf->idxOut = 0;
    }

    return retval;
}

uint16_t RING_GetCount(RING_buffer_t *buf)
{
    uint16_t retval = 0;
    if (buf->idxIn < buf->idxOut) {
        retval = buf->size + buf->idxIn - buf->idxOut;
    } else {
        retval = buf->idxIn - buf->idxOut;
    }

    return retval;
}

void RING_Clear(RING_buffer_t* buf)
{
    buf->idxIn = 0;
    buf->idxOut = 0;
}

void RING_Init(RING_buffer_t *ring, uint8_t *buf, uint16_t size)
{
    ring->size = size;
    ring->buffer = buf;
    RING_Clear( ring );
}