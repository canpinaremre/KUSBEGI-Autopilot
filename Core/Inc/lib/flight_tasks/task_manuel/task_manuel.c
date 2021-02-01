#include "task_manuel.h"

int8_t run_task_manuel(OUTPUT_MIXER *output_mixer, KUSBEGI_FLAGS *kusbegi_flags,
		float *task_yaw, float *task_pitch, float *task_roll, float *task_altitude) {

	*task_altitude = output_mixer->RC_INPUT.rc_channels[throttle].mapped_value;

	*task_pitch = output_mixer->RC_INPUT.rc_channels[pitch].mapped_value;
	*task_roll = output_mixer->RC_INPUT.rc_channels[roll].mapped_value;


	*task_yaw = output_mixer->RC_INPUT.rc_channels[yaw].mapped_value;

	if(kusbegi_flags->FLAG_ARM_CHANGE){

		if (output_mixer->RC_INPUT.arm_state) {
			first_arm = 1;
			time_arm = HAL_GetTick();
		}
		else {
			first_arm = 0;
		}

		kusbegi_flags->FLAG_ARM_CHANGE = 0;
	}

	if(((HAL_GetTick() - time_arm) < ARM_SPIN_MOTOR_TIME)&&(first_arm)){

		kusbegi_flags->FLAG_SPIN_MOTOR = 1;

	}
	else if(((HAL_GetTick() - time_arm) > ARM_SPIN_MOTOR_TIME)&&(first_arm)){
		kusbegi_flags->FLAG_SPIN_MOTOR = 0;
		first_arm = 0;
		}
	if(!output_mixer->RC_INPUT.arm_state){
		kusbegi_flags->FLAG_SPIN_MOTOR = 0;
	}


	kusbegi_flags->FLAG_ARM = output_mixer->RC_INPUT.arm_state;

	if(kusbegi_flags->FLAG_RC_FRAME_LOST || kusbegi_flags->FLAG_RC_FAILSAFE){
		kusbegi_flags->FLAG_ARM = 0;
	}


	return 0;
}
