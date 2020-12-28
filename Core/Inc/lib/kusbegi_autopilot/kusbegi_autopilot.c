/*
 * @Author: canpinaremre
 * Purpose: Autopilot
 * Language:  C
 */
#include "kusbegi_autopilot.h"

uint8_t kusbegi_init(I2C_HandleTypeDef *huartI2C,KUSBEGI *kusbegi,UART_HandleTypeDef* huart){

	/* init output_mixer */
	init_output_mixer(&output_mixer, huartI2C,huart);

	/* init kusbegi autopilot*/
	kusbegi->mc_arm_state = DISARM;
	kusbegi->mc_fc_state = KUSBEGI_INIT;
	kusbegi->mc_flight_mode = MODE_STABILIZE;
	kusbegi->mc_gps_available = GPS_UNAVAILABLE;
	kusbegi->mc_kill_switch = 0;
	kusbegi->mc_land_state = LANDED;

	for(uint8_t i = 0;i<4;i++){
		kusbegi->PWM_US_MOTOR[i] = 0;
	}

	last_tick_l1 = 0;
	last_tick_l2 = 0;
	last_tick_l3 = 0;
	last_tick_l4 = 0;
	last_tick_l5 = 0;
	last_tick_l6 = 0;
	kusbegi_tick = 0;
	return 1;
}

void kusbegi_loop(UART_HandleTypeDef* huart,I2C_HandleTypeDef *huartI2C,KUSBEGI *kusbegi){

	kusbegi_tick = HAL_GetTick();

//	if (kusbegi_tick - last_tick_l1 >= LOOP1DELAY_MS) {
//		loop1(huart);
//		last_tick_l1 = HAL_GetTick();
//	}
	if (kusbegi_tick - last_tick_l2 >= LOOP2DELAY_MS) {
		loop2(huart,huartI2C);
		last_tick_l2 = HAL_GetTick();
	}
//	if (kusbegi_tick - last_tick_l3 >= LOOP3DELAY_MS) {
//		loop3(huart);
//		last_tick_l3 = HAL_GetTick();
//	}
//	if (kusbegi_tick - last_tick_l4 >= LOOP4DELAY_MS) {
//		update_imu(&output_mixer, huartI2C);
//		loop4(huart,kusbegi,&output_mixer);
//		last_tick_l4 = HAL_GetTick();
//	}
//	if (kusbegi_tick - last_tick_l5 >= LOOP5DELAY_MS) {
//		loop5();
//		last_tick_l5 = HAL_GetTick();
//	}
//	if (kusbegi_tick - last_tick_l6 >= LOOP6DELAY_MS) {
//		loop6();
//		last_tick_l6 = HAL_GetTick();
//	}


}

void loop1(UART_HandleTypeDef* huart){
	sendString("Loop1:", huart,1);
	sendInt(LOOP1DELAY_MS, huart,1);
}

void loop2(UART_HandleTypeDef *huart, I2C_HandleTypeDef *huartI2C) {

	update_barometer(&output_mixer,huartI2C);
	sendInt(imu.pressure, huart,1);
	sendFloat((float)imu.temperature, huart,1);
}
void loop3(UART_HandleTypeDef* huart){
	sendString("Loop3:", huart,1);
	sendInt(LOOP3DELAY_MS, huart,1);
}

/* This loop for IMU test*/
void loop4(UART_HandleTypeDef* huart,KUSBEGI *kusbegi,OUTPUT_MIXER *output_mixer){


	sendString("#ACC:,", huart,0);
	sendFloat((-1.0f)*output_mixer->IMU.eulerXYZ[1], huart,0);
	sendString(",", huart,0);
	sendFloat(output_mixer->IMU.eulerXYZ[2], huart,0);
	sendString(",", huart,0);
	sendFloat(output_mixer->IMU.eulerXYZ[0], huart,0);
	sendString(",", huart,1);
	//HAL_Delay(500);

}

void loop5(UART_HandleTypeDef* huart){
	sendString("Loop5:", huart,1);
	sendInt(LOOP5DELAY_MS, huart,1);
}
void loop6(UART_HandleTypeDef* huart){
	sendString("Loop6:", huart,1);
	sendInt(LOOP6DELAY_MS, huart,1);
}
