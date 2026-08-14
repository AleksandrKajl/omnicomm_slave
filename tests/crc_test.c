#include "crc.h"

#include <stdint.h>
#include <stdio.h>

static int check_crc(const char* name, const uint8_t* data, uint16_t size, uint8_t expected) {
    uint8_t actual = crc8_calculate(data, size);

    if (actual != expected) {
        printf("%s: expected %02X, got %02X\n", name, expected, actual);
        return 1;
    }

    return 0;
}

int main(void) {
    const uint8_t empty[] = {0x00};
    const uint8_t request[] = {0x31, 0x71, 0x06};
    const uint8_t damaged_request[] = {0x31, 0x70, 0x06};
    const uint8_t response[] = {0x3e, 0x71, 0x06, 0x19, 0x34, 0x12, 0x78, 0x56};
    int failed = 0;

    failed += check_crc("empty data", empty, 0, 0x00);
    failed += check_crc("request", request, sizeof(request), 0xda);
    failed += check_crc("damaged request", damaged_request, sizeof(damaged_request), 0x1e);
    failed += check_crc("response", response, sizeof(response), 0x13);

    if (crc8_update(0x31, 0) != 0xe0) {
        printf("single byte update: expected E0\n");
        failed++;
    }

    if (failed == 0) {
        printf("CRC tests passed\n");
    }

    return failed;
}
