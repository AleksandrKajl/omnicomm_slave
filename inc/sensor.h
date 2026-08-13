//
// Created by Aleksandr on 23.01.2025.
//

#ifndef OMNICOMM_SLAVE_SENSOR_H
#define OMNICOMM_SLAVE_SENSOR_H
#include <stdint.h>

/*!@struct Упакованная структура описывающая данные получаемые от датчика
 */
typedef struct Sensor_data {
    int8_t temp;
    uint8_t min_lvl;
    uint8_t max_lvl;
    uint16_t freq;
}__attribute__((packed))Sensor_data_t;

/*!
* @brief Псевдополучение данных от сенсора.
 * @param[in] sens_data - указатель на структуру описывающую данные получаемые от датчика
*/
void sensor_get_data(Sensor_data_t *sens_data);

#endif //OMNICOMM_SLAVE_SENSOR_H
