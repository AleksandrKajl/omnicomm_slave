//
// Created by Aleksandr on 23.01.2025.
//
#include "sensor.h"
#include <stdint.h>
#include <time.h>
#include <stdlib.h>


void sensor_get_data(Sensor_data_t *sens_data)
{
    //Заполняем псевдоданными
    extern uint32_t SysTick_counter;
    srand(SysTick_counter);
    sens_data->temp = rand() % 0xFF;
    sens_data->min_lvl = rand() % 0x0F;
    sens_data->max_lvl = 0x0F + rand() % 0xFF - 0x0F;
    sens_data->freq = rand() % 0xFFFF;
}
