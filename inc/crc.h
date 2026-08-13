//
// Created by Aleksandr on 23.01.2025.
//

#ifndef OMNICOMM_SLAVE_CRC_H
#define OMNICOMM_SLAVE_CRC_H
#include <stdint.h>

/*!
* @brief Расчёт crc суммы.
 * @param[in] data - константный указатель на буфер данных
 * @param[in] size - размер буфера данных
 * @return Сумма crc8
*/
uint8_t get_crc(const uint8_t *data, uint16_t size);

#endif //OMNICOMM_SLAVE_CRC_H
