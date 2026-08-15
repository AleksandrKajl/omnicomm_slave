//
// Created by Aleksandr on 22.01.2025.
//

#ifndef OMNICOMM_SLAVE_RING_BUF_H
#define OMNICOMM_SLAVE_RING_BUF_H

#include <stdbool.h>
#include <stdint.h>

#define RING_BUFF_SZ 0x100

/*! @struct Структура кольцевого буфера для одного писателя и одного читателя. */
typedef struct {
    uint8_t* buffer;
    volatile uint16_t idxIn;
    volatile uint16_t idxOut;
    uint16_t size;
} RING_buffer_t;

/*!
 * @brief Запись одного байта в буфер.
 * @return true, если байт записан, false, если буфер заполнен
 */
bool RING_put(uint8_t symbol, RING_buffer_t* ring);

/*!
 * @brief Чтение и удаление одного байта из буфера.
 * @return true, если байт получен, false, если буфер пуст
 */
bool RING_pop(RING_buffer_t* ring, uint8_t* symbol);

/*!
 * @brief Чтение байта по смещению без удаления из буфера.
 * @return true, если смещение допустимо, false, если данных недостаточно
 */
bool RING_peek(const RING_buffer_t* ring, uint16_t offset, uint8_t* symbol);

/*! @brief Удаление указанного количества байтов из начала буфера. */
void RING_leave(uint16_t count, RING_buffer_t* ring);

/*! @brief Получение количества записанных байтов. */
uint16_t RING_get_count(const RING_buffer_t* ring);

/*! @brief Удаление всех данных из буфера. */
void RING_clear(RING_buffer_t* ring);

/*!
 * @brief Инициализация кольцевого буфера.
 * @param[in] size - размер массива, минимум два байта; один байт всегда остаётся свободным
 */
void RING_init(RING_buffer_t* ring, uint8_t* buffer, uint16_t size);

#endif // OMNICOMM_SLAVE_RING_BUF_H
