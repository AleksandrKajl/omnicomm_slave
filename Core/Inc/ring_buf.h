//
// Created by Aleksandr on 22.01.2025.
//

#ifndef OMNICOMM_SLAVE_RING_BUF_H
#define OMNICOMM_SLAVE_RING_BUF_H
#include <stdint.h>

#define RING_BUFF_SZ                                                0x100

/*!@struct Структура реализующая кольцевой буфер
 */
typedef struct{
    uint8_t *buffer;
    uint16_t idxIn;
    uint16_t idxOut;
    uint16_t size;
}RING_buffer_t;

/*!
* @brief Запись одного байта в буфер.
 * @param[in] symbol - записываемый байт
 * @param[in] buf - Указатель на кольцевой буфер
*/
void RING_put(uint8_t symbol, RING_buffer_t* buf);
/*!
* @brief Получение одного байта из буфера с последующим его удалением.
 * @param[in] buf - Указатель на кольцевой буфер
* @return байт данных из колцевого буфера.
*/
uint8_t RING_pop(RING_buffer_t *buf);
/*!
* @brief Освобождение буфера на определённое количество данных.
 * @param[in] idx - количество освобождаемых байт
 * @param[in] buf - Указатель на кольцевой буфер
*/
void RING_leave(uint16_t idx, RING_buffer_t *buf);
/*!
* @brief Получение указателя на данные по смещению относительно начало данных.
 * @param[in] idx - Индекс указывающий смещение относительно начало данных
 * @param[in] buf - Указатель на кольцевой буфер
* @return указатель на начало данных.
*/
uint8_t* RING_get_ptrdata(uint16_t idx, RING_buffer_t *buf);
/*!
* @brief Получение количества байт записанных в буфер.
 * @param[in] buf - указатель на кольцевой буфер
* @return Количество полезных байт в буфере.
*/
uint16_t RING_get_count(RING_buffer_t *buf);
/*!
* @brief Получение символа без его удаления из буфера.
 * @param[in] symb_offset - Индекс указывающий смещение относительно начало данных
 * @param[in] buf - указатель на кольцевой буфер
* @return Возвращает байт данных или -1 если symb_offset больше чем полезных данных в буфере.
*/
int32_t RING_peek(uint16_t symb_offset ,RING_buffer_t *buf);
/*!
* @brief Отчищает буфер путём присвоения idxIn и idxOut 0.
 * @param[in] buf - Указатель на кольцевой буфер
*/
void RING_clear(RING_buffer_t* buf);
/*!
* @brief Инициализация буфера для начало работы с ним.
 * @param[in] ring - указатель на структуру кольцевого буфера
 * @param[in] buf - указатель на буфер данных, который будет использоваться как кольцевой буфер
 * @param[in] size - размер буфера, который будет использован как кольцевой буфер
*/
void RING_init(RING_buffer_t *ring, uint8_t *buf, uint16_t size);

#endif //OMNICOMM_SLAVE_RING_BUF_H
