#include "ring_buf.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static int check(bool condition, const char* message) {
    if (!condition) {
        printf("%s\n", message);
        return 1;
    }

    return 0;
}

static int test_empty(void) {
    uint8_t storage[4] = {0};
    RING_buffer_t ring;
    uint8_t value = 0;

    RING_init(&ring, storage, sizeof(storage));

    int failed = 0;
    failed += check(RING_get_count(&ring) == 0, "new buffer is not empty");
    failed += check(!RING_pop(&ring, &value), "pop succeeded for empty buffer");
    failed += check(!RING_peek(&ring, 0, &value), "peek succeeded for empty buffer");

    return failed;
}

static int test_full_and_fifo(void) {
    uint8_t storage[4] = {0};
    RING_buffer_t ring;
    uint8_t value = 0;

    RING_init(&ring, storage, sizeof(storage));

    int failed = 0;
    failed += check(RING_put(0x11, &ring), "first put failed");
    failed += check(RING_put(0x22, &ring), "second put failed");
    failed += check(RING_put(0x33, &ring), "third put failed");
    failed += check(!RING_put(0x44, &ring), "full buffer accepted a byte");
    failed += check(RING_get_count(&ring) == 3, "full buffer count is incorrect");

    failed += check(RING_pop(&ring, &value) && value == 0x11, "first pop is incorrect");
    failed += check(RING_pop(&ring, &value) && value == 0x22, "second pop is incorrect");
    failed += check(RING_pop(&ring, &value) && value == 0x33, "third pop is incorrect");
    failed += check(!RING_pop(&ring, &value), "empty buffer returned another byte");

    return failed;
}

static int test_wrap_and_peek(void) {
    uint8_t storage[4] = {0};
    RING_buffer_t ring;
    uint8_t value = 0;

    RING_init(&ring, storage, sizeof(storage));
    RING_put(0x11, &ring);
    RING_put(0x22, &ring);
    RING_put(0x33, &ring);
    RING_pop(&ring, &value);
    RING_pop(&ring, &value);
    RING_put(0x44, &ring);
    RING_put(0x55, &ring);

    int failed = 0;
    failed += check(RING_peek(&ring, 0, &value) && value == 0x33, "peek before wrap is incorrect");
    failed += check(RING_peek(&ring, 1, &value) && value == 0x44, "peek at wrap is incorrect");
    failed += check(RING_peek(&ring, 2, &value) && value == 0x55, "peek after wrap is incorrect");
    failed += check(!RING_peek(&ring, 3, &value), "peek accepted an invalid offset");

    return failed;
}

static int test_leave_and_clear(void) {
    uint8_t storage[4] = {0};
    RING_buffer_t ring;
    uint8_t value = 0;

    RING_init(&ring, storage, sizeof(storage));
    RING_put(0x11, &ring);
    RING_put(0x22, &ring);
    RING_put(0x33, &ring);
    RING_leave(2, &ring);

    int failed = 0;
    failed += check(RING_get_count(&ring) == 1, "leave removed an incorrect number of bytes");
    failed += check(RING_pop(&ring, &value) && value == 0x33, "leave kept an incorrect byte");

    RING_put(0x44, &ring);
    RING_leave(5, &ring);
    failed += check(RING_get_count(&ring) == 0, "leave beyond count did not empty buffer");

    RING_put(0x55, &ring);
    RING_clear(&ring);
    failed += check(RING_get_count(&ring) == 0, "clear did not empty buffer");

    return failed;
}

static int test_large_buffer_wrap(void) {
    static uint8_t storage[UINT16_MAX];
    RING_buffer_t ring;
    uint8_t value = 0;

    RING_init(&ring, storage, UINT16_MAX);
    ring.idxIn = UINT16_MAX - 2;
    ring.idxOut = UINT16_MAX - 3;
    storage[UINT16_MAX - 3] = 0x11;

    int failed = 0;
    failed += check(RING_put(0x22, &ring), "put before large buffer wrap failed");
    failed += check(RING_put(0x33, &ring), "put at large buffer wrap failed");
    failed += check(RING_peek(&ring, 2, &value) && value == 0x33, "large buffer peek wrap is incorrect");

    RING_leave(2, &ring);
    failed += check(RING_pop(&ring, &value) && value == 0x33, "large buffer leave wrap is incorrect");

    return failed;
}

int main(void) {
    int failed = 0;

    failed += test_empty();
    failed += test_full_and_fifo();
    failed += test_wrap_and_peek();
    failed += test_leave_and_clear();
    failed += test_large_buffer_wrap();

    if (failed == 0) {
        printf("Ring buffer tests passed\n");
    }

    return failed;
}
