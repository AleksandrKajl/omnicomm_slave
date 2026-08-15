//
// Created by Aleksandr on 22.01.2025.
//
#include "ring_buf.h"

bool RING_put(uint8_t symbol, RING_buffer_t* ring) {
    uint16_t next_idx = ring->idxIn + 1;
    if (next_idx >= ring->size) {
        next_idx = 0;
    }

    if (next_idx == ring->idxOut) {
        return false;
    }

    ring->buffer[ring->idxIn] = symbol;
    ring->idxIn = next_idx;

    return true;
}

bool RING_pop(RING_buffer_t* ring, uint8_t* symbol) {
    if (ring->idxIn == ring->idxOut) {
        return false;
    }

    *symbol = ring->buffer[ring->idxOut];
    ring->idxOut++;
    if (ring->idxOut >= ring->size) {
        ring->idxOut = 0;
    }

    return true;
}

bool RING_peek(const RING_buffer_t* ring, uint16_t offset, uint8_t* symbol) {
    if (offset >= RING_get_count(ring)) {
        return false;
    }

    uint32_t index = (uint32_t)ring->idxOut + offset;
    if (index >= ring->size) {
        index -= ring->size;
    }
    *symbol = ring->buffer[(uint16_t)index];

    return true;
}

void RING_leave(uint16_t count, RING_buffer_t* ring) {
    uint16_t available = RING_get_count(ring);
    if (count > available) {
        count = available;
    }

    uint32_t index = (uint32_t)ring->idxOut + count;
    if (index >= ring->size) {
        index -= ring->size;
    }
    ring->idxOut = (uint16_t)index;
}

uint16_t RING_get_count(const RING_buffer_t* ring) {
    uint16_t idx_in = ring->idxIn;
    uint16_t idx_out = ring->idxOut;

    if (idx_in < idx_out) {
        return ring->size + idx_in - idx_out;
    }

    return idx_in - idx_out;
}

void RING_clear(RING_buffer_t* ring) {
    ring->idxIn = 0;
    ring->idxOut = 0;
}

void RING_init(RING_buffer_t* ring, uint8_t* buffer, uint16_t size) {
    ring->buffer = buffer;
    ring->size = size;
    RING_clear(ring);
}
