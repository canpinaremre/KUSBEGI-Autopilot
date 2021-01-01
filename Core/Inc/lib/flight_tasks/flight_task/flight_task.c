/*
 * @Author: canpinaremre
 * Purpose: Flight Task
 * Language:  C
 */

#include "flight_task.h"

int8_t flight_task_update(FLIGHT_TASK *flight_task,FLIGHT_MODE *flight_mode,OUTPUT_MIXER *output_mixer,KUSBEGI_FLAGS *kusbegi_flags){


	if(flight_mode->mode_type == mode_stabilize){

		run_task_manuel(output_mixer,kusbegi_flags,&task_yaw,&task_pitch,&task_roll,&task_altitude);

	}

	flight_task->flight_task_setpoint.altitude = task_altitude;
	flight_task->flight_task_setpoint.yaw = task_yaw;
	flight_task->flight_task_setpoint.pitch = task_pitch;
	flight_task->flight_task_setpoint.roll = task_roll;


	flight_task->lastflight_task_setpoint = flight_task->flight_task_setpoint;

	return 0;
}
