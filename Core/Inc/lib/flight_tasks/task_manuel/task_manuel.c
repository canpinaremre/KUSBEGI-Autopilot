#include "task_manuel.h"

int8_t run_task_manuel(OUTPUT_MIXER *output_mixer, KUSBEGI_FLAGS *kusbegi_flags,
		float *task_yaw, float *task_pitch, float *task_roll, float *task_altitude) {

	*task_altitude = output_mixer->RC_INPUT.rc_channels[throttle].mapped_value;

	*task_pitch = output_mixer->RC_INPUT.rc_channels[pitch].mapped_value;
	*task_roll = output_mixer->RC_INPUT.rc_channels[roll].mapped_value;


	*task_yaw = output_mixer->RC_INPUT.rc_channels[yaw].mapped_value;


	kusbegi_flags->FLAG_ARM = output_mixer->RC_INPUT.arm_state;

	if(kusbegi_flags->FLAG_RC_FRAME_LOST || kusbegi_flags->FLAG_RC_FAILSAFE){
		kusbegi_flags->FLAG_ARM = 0;
	}


	return 0;
}
