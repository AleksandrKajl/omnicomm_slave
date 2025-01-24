//
// Created by Aleksandr on 23.01.2025.
//
#include "sensor.h"
#include <stdint.h>
#include <time.h>
#include <stdlib.h>


void sensor_get_data(Sensor_data_t *sens_data)
{
    extern uint32_t SysTick_counter;
    srand(SysTick_counter);
    sens_data->temp = rand() % 0xFF;
    sens_data->min_lvl = rand() % 0xFF;
    sens_data->max_lvl = 0xFF + rand() % 0xFFFF - 0xFF;
    sens_data->freq = rand() % 0xFFFF;
}
