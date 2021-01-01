/*
 * @Author: canpinaremre
 * Purpose: Flight Mode
 * Language:  C
 */

#include "flight_mode.h"


int8_t flight_mode_update(FLIGHT_MODE *flight_mode,OUTPUT_MIXER *output_mixer,KUSBEGI_FLAGS *kusbegi_flags){
	int8_t rslt;
	/*
	 * First wee need to check what values we have
	 * Then we will determine that we can still use this flight mode
	 * If we have to switch another mode we will call:
	 * flight_mode_transition
	 * After we get mode update will set up for flight task
	 */
	if ((kusbegi_flags->FLAG_RC_FAILSAFE) || (kusbegi_flags->FLAG_RC_FRAME_LOST)
			|| (kusbegi_flags->FLAG_RC_CONNECTION_E)
			|| (kusbegi_flags->FLAG_IMU_READ_OK == 0)) {

		if (flight_mode->failsafe_timer_active == 0) {
			flight_mode->failsafe_timer = HAL_GetTick();
			flight_mode->failsafe_timer_active = 1;
		}

		if((HAL_GetTick() - flight_mode->failsafe_timer) > RC_FAILSAFE_TIME_MS){
			/*
			 * We set the flag up
			 * Because new mod is Failsafe
			 * We want to start mode transition
			 */
			kusbegi_flags->FLAG_MODE_CHANGE = 1;
			flight_mode->mode_type = mode_failsafe;
		}
	}


	if(kusbegi_flags->FLAG_MODE_CHANGE){
		/*
		 * Set flag down to detect next mode change
		 */
		kusbegi_flags->FLAG_MODE_CHANGE = 0;
		flight_mode_transition(flight_mode, output_mixer, kusbegi_flags);

	}


	rslt = flight_mode_available(flight_mode->mode_type,kusbegi_flags);
	if(rslt == FLIGHT_MODE_AVAILABLE){
		/*
		 * We will pass the new mode
		 * Before we return, We set last mode as new mode
		 * This means mode change is success
		 */
		flight_mode->last_mode_type = flight_mode->mode_type;
	}
	else{
		/*
		 * If we can not change mode
		 * We have to continue pass old mode
		 * Failsafe is handled above but TODO: need to handle imu err
		 */
		flight_mode->mode_type = flight_mode->last_mode_type;
	}



	return rslt;
}

int8_t flight_mode_transition(FLIGHT_MODE *flight_mode,OUTPUT_MIXER *output_mixer,KUSBEGI_FLAGS *kusbegi_flags){

	if(output_mixer->RC_INPUT.rc_channels[mode].mapped_value == RC_MODE_STABILIZE){
		flight_mode->mode_type = mode_stabilize;
		return FLIGHT_MODE_AVAILABLE;
	}



	return FLIGHT_MODE_E_UNKOWN_MODE;
}

int8_t flight_mode_available(MODE_TYPE mode_type,KUSBEGI_FLAGS *kusbegi_flags){

	if(mode_type == mode_stabilize){
		return FLIGHT_MODE_AVAILABLE;
	}


	return FLIGHT_MODE_E_UNKOWN_MODE;
}
