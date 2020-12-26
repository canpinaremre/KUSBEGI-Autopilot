/*
 * @Author: canpinaremre
 * Purpose: Math Lib
 * Language:  C
 */

#ifndef UTILITY_MATH_H
#define UTILITY_MATH_H

#include "stm32f4xx_hal.h"
#include <math.h>

uint16_t MAP(uint16_t au32_IN, uint16_t au32_INmin, uint16_t au32_INmax,
		uint16_t au32_OUTmin, uint16_t au32_OUTmax);
float MAPF(uint16_t au32_IN, uint16_t au32_INmin, uint16_t au32_INmax,
		int16_t au32_OUTmin, int16_t au32_OUTmax);

double roll_from_accel(double y_Buff , double z_Buff);

double pitch_from_accel(double x_Buff , double y_Buff,double z_Buff);

/* #ifndef UTILITY_MATH_H */
#endif
