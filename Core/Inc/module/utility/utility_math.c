/*
 * @Author: canpinaremre
 * Purpose: Math Lib
 * Language:  C
 */
#include "utility_math.h"

uint16_t MAP(uint16_t au32_IN, uint16_t au32_INmin, uint16_t au32_INmax,
		uint16_t au32_OUTmin, uint16_t au32_OUTmax) {
	return ((((au32_IN - au32_INmin) * (au32_OUTmax - au32_OUTmin))
			/ (au32_INmax - au32_INmin)) + au32_OUTmin);
}

float MAPF(uint16_t au32_IN, uint16_t au32_INmin, uint16_t au32_INmax,
		int16_t au32_OUTmin, int16_t au32_OUTmax){

	return (((((float)au32_IN - (float)au32_INmin) * ((float)au32_OUTmax - (float)au32_OUTmin))
			/ ((float)au32_INmax - (float)au32_INmin)) + (float)au32_OUTmin);
}

double roll_from_accel(double y_Buff , double z_Buff){
	return atan2(y_Buff , z_Buff) * 57.3;
}

double pitch_from_accel(double x_Buff , double y_Buff,double z_Buff){
	return atan2(x_Buff ,  z_Buff) * 57.3;
}
