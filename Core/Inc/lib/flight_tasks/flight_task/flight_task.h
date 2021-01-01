/*
 * @Author: canpinaremre
 * Purpose: Flight Task
 * Language:  C
 */
#ifndef __FLIGHT_TASK_H__
#define __FLIGHT_TASK_H__

#include "stm32f4xx_hal.h"
#include <lib/parameters/parameters.h>
#include <lib/flight_tasks/task_manuel/task_manuel.h>
#include <lib/output_mixer/output_mixer.h>
#include <lib/flight_modes/flight_mode/flight_mode.h>

typedef enum{
	task_manuel,
	task_manuel_altitude,
	task_manuel_position,
	task_mission,
	task_failsafe,
	task_land,
	task_offboard
}TASK_TYPE;

typedef struct{
	int32_t x;
	int32_t y;
	int32_t z;
	float yaw;
	float pitch;
	float roll;
	float altitude;
}FLIGHT_TASK_SETPOINT;

typedef struct{
	TASK_TYPE task_type;
	TASK_TYPE last_task_type;
	FLIGHT_TASK_SETPOINT flight_task_setpoint;
	FLIGHT_TASK_SETPOINT lastflight_task_setpoint;
}FLIGHT_TASK;
float task_yaw,task_pitch,task_roll,task_altitude;
int8_t flight_task_update(FLIGHT_TASK *flight_task,FLIGHT_MODE *flight_mode,OUTPUT_MIXER *output_mixer,KUSBEGI_FLAGS *kusbegi_flags);

/* #ifndef __FLIGHT_TASK_H__ */
#endif
