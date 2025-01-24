//
// Created by Aleksandr on 22.01.2025.
//

#ifndef OMNICOMM_SLAVE_TRANSCEIVER_H
#define OMNICOMM_SLAVE_TRANSCEIVER_H

#include <stdint.h>
#include "ring_buf.h"

#define REQ_SZ                                      0x04

#define CMD_PREFIX                                  0x31
#define CMD_GET_DATA                                0x06
#define CMD_EXAMPLE                                 0x77
#define NET_ADDR                                    0x71


uint8_t transceiver_get_msg(RING_buffer_t *ring_buff);

#endif //OMNICOMM_SLAVE_TRANSCEIVER_H
