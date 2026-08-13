//
// Created by Aleksandr on 22.01.2025.
//
#include "ring_buf.h"

void RING_put(uint8_t symbol, RING_buffer_t* buf) {

    buf->buffer[buf->idxIn++] = symbol;
    if (buf->idxIn >= buf->size) {
        buf->idxIn = 0;
    }
}

uint8_t RING_pop(RING_buffer_t *buf)
{
    uint8_t retval = buf->buffer[buf->idxOut++];
    if (buf->idxOut >= buf->size) {
        buf->idxOut = 0;
    }

    return retval;
}

void RING_leave(uint16_t idx, RING_buffer_t *buf)
{
    for (uint16_t i = 0; i < idx; i++) {
        RING_pop(buf);
    }
}

int32_t RING_peek(uint16_t symb_offset, RING_buffer_t *buf)
{
    uint32_t pointer = buf->idxOut + symb_offset;
    int32_t  retval = -1;
    if (symb_offset < RING_get_count(buf))
    {
        if (pointer > buf->size) {
            pointer -= buf->size;
        }
        retval = buf->buffer[pointer];
    }

    return retval;
}

uint8_t* RING_get_ptrdata(uint16_t idx, RING_buffer_t *buf)
{
    return buf->buffer + buf->idxOut + idx;
}

uint16_t RING_get_count(RING_buffer_t *buf)
{
    uint16_t retval = 0;
    if (buf->idxIn < buf->idxOut) {
        retval = buf->size + buf->idxIn - buf->idxOut;
    } else {
        retval = buf->idxIn - buf->idxOut;
    }

    return retval;
}

void RING_clear(RING_buffer_t* buf)
{
    buf->idxIn = 0;
    buf->idxOut = 0;
}

void RING_init(RING_buffer_t *ring, uint8_t *buf, uint16_t size)
{
    ring->size = size;
    ring->buffer = buf;
    RING_clear(ring);
}