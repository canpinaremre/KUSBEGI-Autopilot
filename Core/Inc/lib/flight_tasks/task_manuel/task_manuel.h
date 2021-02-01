/*
 * @Author: canpinaremre
 * Purpose: Flight Task Manuel
 * Language:  C
 */
#ifndef __FLIGHT_TASK_MANUEL_H__
#define __FLIGHT_TASK_MANUEL_H__
#include "stm32f4xx_hal.h"
#include <lib/parameters/parameters.h>
#include <lib/output_mixer/output_mixer.h>

uint8_t first_arm;
uint32_t time_arm;

int8_t run_task_manuel(OUTPUT_MIXER *output_mixer, KUSBEGI_FLAGS *kusbegi_flags,
		float *task_yaw, float *task_pitch, float *task_roll, float *task_altitude);






/* #ifndef __FLIGHT_TASK_MANUEL_H__ */
#endif
