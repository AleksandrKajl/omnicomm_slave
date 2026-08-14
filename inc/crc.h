//
// Created by Aleksandr on 23.01.2025.
//

#ifndef OMNICOMM_SLAVE_CRC_H
#define OMNICOMM_SLAVE_CRC_H
#include <stdint.h>

/*!
 * @brief Добавление одного байта к CRC8.
 * @param[in] data - байт данных
 * @param[in] crc - CRC, рассчитанный для предыдущих байтов
 * @return Обновлённое значение CRC8
 */
uint8_t crc8_update(uint8_t data, uint8_t crc);

/*!
 * @brief Расчёт CRC8 для массива данных.
 * @param[in] data - константный указатель на буфер данных
 * @param[in] size - размер буфера данных
 * @return Значение CRC8
 */
uint8_t crc8_calculate(const uint8_t* data, uint16_t size);

#endif // OMNICOMM_SLAVE_CRC_H
