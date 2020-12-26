/*
 * @Author: canpinaremre
 * Purpose: Autopilot
 * Language:  C
 */
#include "kusbegi_autopilot.h"

uint8_t kusbegi_init(I2C_HandleTypeDef *huart,KUSBEGI *kusbegi){

	/* init output_mixer */
	init_output_mixer(&output_mixer, huart);

	/* init kusbegi autopilot*/
	kusbegi->mc_arm_state = DISARM;
	kusbegi->mc_fc_state = KUSBEGI_INIT;
	kusbegi->mc_flight_mode = MODE_STABILIZE;
	kusbegi->mc_gps_available = GPS_UNAVAILABLE;
	kusbegi->mc_kill_switch = 0;
	kusbegi->mc_land_state = LANDED;

	return 1;
}

void kusbegi_loop(void){

}
