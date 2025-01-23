//
// Created by Aleksandr on 22.01.2025.
//

#ifndef OMNICOMM_SLAVE_TRANSCEIVER_H
#define OMNICOMM_SLAVE_TRANSCEIVER_H

typedef struct {
    unsigned char prefix;
    unsigned char addr;
    unsigned char cmd;
    unsigned char crc;
}Request_t;



#endif //OMNICOMM_SLAVE_TRANSCEIVER_H
