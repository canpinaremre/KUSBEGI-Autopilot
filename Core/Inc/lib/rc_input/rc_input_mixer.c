/*
 * @Author: canpinaremre
 * Purpose: RC Mixer
 * Language:  C
 */

#include "rc_input_mixer.h"

#ifdef RC_INPUT_IS_SBUS
#include "rc_input_sbus.h"

int8_t update_rc_input(UART_HandleTypeDef *huartRC,RC_INPUT *rc_input){
	if(RC_READ_SBUS(huartRC,&sbus)){

		/* Reading channel pwm values */
		for (uint8_t i = 0; i < RC_INPUT_MIXER_CHANNEL_CNT; i++) {
			rc_input->rc_channels[i].pwm_value = sbus.PWM_US_RC_CH[i];
			rc_input->rc_channels[i].channel_name = i;

			/* Now Map the values.
			 * Each channel has its own mapping or bool state.
			 */
			if (rc_input->rc_channels[i].channel_name == throttle) {
				rc_input->rc_channels[i].mapped_value = MAPF(
						rc_input->rc_channels[i].pwm_value, 1000, 2000, 1000, 2000);
			} else if (rc_input->rc_channels[i].channel_name == yaw) {
				rc_input->rc_channels[i].mapped_value = MAPF(
						rc_input->rc_channels[i].pwm_value, 1000, 2000,
						-RC_INPUT_MIXER_YAW_MINMAX, RC_INPUT_MIXER_YAW_MINMAX);
			} else if (rc_input->rc_channels[i].channel_name == pitch) {
				rc_input->rc_channels[i].mapped_value = MAPF(
						rc_input->rc_channels[i].pwm_value, 1000, 2000,
						-RC_INPUT_MIXER_PITCH_MINMAX,
						RC_INPUT_MIXER_PITCH_MINMAX);
			} else if (rc_input->rc_channels[i].channel_name == roll) {
				rc_input->rc_channels[i].mapped_value = MAPF(
						rc_input->rc_channels[i].pwm_value, 1000, 2000,
						-RC_INPUT_MIXER_ROLL_MINMAX,
						RC_INPUT_MIXER_ROLL_MINMAX);
			} else if (rc_input->rc_channels[i].channel_name == mode) {
				if (rc_input->rc_channels[i].pwm_value
						< RC_INPUT_MIXER_MODE1_TH)
					rc_input->rc_channels[i].bool_value = 1;
				else if(rc_input->rc_channels[i].pwm_value
						< RC_INPUT_MIXER_MODE2_TH)
					rc_input->rc_channels[i].bool_value = 2;
				else
					rc_input->rc_channels[i].bool_value = 3;
			} else if (rc_input->rc_channels[i].channel_name == kill_s) {
				if (rc_input->rc_channels[i].pwm_value
						>= RC_INPUT_MIXER_SWITCH_TH)
					rc_input->rc_channels[i].bool_value = 1;
				else
					rc_input->rc_channels[i].bool_value = 0;
			} else if (rc_input->rc_channels[i].channel_name == rth) {
				if (rc_input->rc_channels[i].pwm_value
						>= RC_INPUT_MIXER_SWITCH_TH)
					rc_input->rc_channels[i].bool_value = 1;
				else
					rc_input->rc_channels[i].bool_value = 0;
			} else if (rc_input->rc_channels[i].channel_name == land) {
				if (rc_input->rc_channels[i].pwm_value
						>= RC_INPUT_MIXER_SWITCH_TH)
					rc_input->rc_channels[i].bool_value = 1;
				else
					rc_input->rc_channels[i].bool_value = 0;
			} else if (rc_input->rc_channels[i].channel_name == offboard) {
				if (rc_input->rc_channels[i].pwm_value
						>= RC_INPUT_MIXER_SWITCH_TH)
					rc_input->rc_channels[i].bool_value = 1;
				else
					rc_input->rc_channels[i].bool_value = 0;
			}

		}

		/* Check if arm state changed*/
		if(sbus.arm){
			rc_input->arm_state = 1;
		}

		/* Check if arm state changed*/
		if(sbus.disarm){
			rc_input->arm_state = 0;
		}

		/* Check failsafe*/
		if(sbus.failsafe){
			rc_input->failsafe_state = 1;
		}
		else{
			rc_input->failsafe_state = 0;
		}

		/* Check frame lost */
		if(sbus.frame_lost){
			rc_input->failsafe_state = 1;
		}
		else{
			rc_input->failsafe_state = 0;
		}




	}
	if(sbus.error){
		rc_input->connection_error = 1;
	}
	else{
		rc_input->connection_error = 0;
	}

	return RC_INPUT_OK;
}


int8_t init_rc_input(RC_INPUT *rc_input){
	rc_input->rc_channels[throttle].pwm_value = 0;
	rc_input->rc_channels[yaw].pwm_value = 0;
	rc_input->rc_channels[pitch].pwm_value = 0;
	rc_input->rc_channels[roll].pwm_value = 0;
	rc_input->arm_state = 0;
	sbus.arm = 0;
	sbus.disarm = 0;
	sbus.arm_cnt = 0;
	sbus.disarm_cnt = 0;

	return RC_INPUT_OK;
}
/* #ifdef RC_INPUT_IS_SBUS */
#endif

#ifdef RC_INPUT_IS_PWM
//TODO
#endif
