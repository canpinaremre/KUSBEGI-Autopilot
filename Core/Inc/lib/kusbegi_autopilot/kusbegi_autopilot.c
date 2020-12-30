/*
 * @Author: canpinaremre
 * Purpose: Autopilot
 * Language:  C
 */
#include "kusbegi_autopilot.h"

int8_t kusbegi_init(I2C_HandleTypeDef *huartI2C,KUSBEGI *kusbegi,UART_HandleTypeDef* huart){
	int8_t rslt;
	/* init output_mixer */
	rslt = init_output_mixer(&output_mixer, huartI2C,huart);

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



	return rslt;
}

void kusbegi_loop(UART_HandleTypeDef* huart,I2C_HandleTypeDef *huartI2C,KUSBEGI *kusbegi){

	kusbegi_tick = HAL_GetTick();

	if (kusbegi_tick - last_tick_l1 >= LOOP1DELAY_MS) {
		loop1(huart,huartI2C,kusbegi,&kusbegi_flags);
		last_tick_l1 = HAL_GetTick();
	}
	if (kusbegi_tick - last_tick_l2 >= LOOP2DELAY_MS) {
		loop2(huart,huartI2C,kusbegi,&kusbegi_flags);
		last_tick_l2 = HAL_GetTick();
	}
	if (kusbegi_tick - last_tick_l3 >= LOOP3DELAY_MS) {
		loop3(huart,huartI2C,kusbegi,&kusbegi_flags);
		last_tick_l3 = HAL_GetTick();
	}
	if (kusbegi_tick - last_tick_l4 >= LOOP4DELAY_MS) {
		loop4(huart,huartI2C,kusbegi,&kusbegi_flags);
		last_tick_l4 = HAL_GetTick();
	}
	if (kusbegi_tick - last_tick_l5 >= LOOP5DELAY_MS) {
		loop5(huart,huartI2C,kusbegi,&kusbegi_flags);
		last_tick_l5 = HAL_GetTick();
	}
	if (kusbegi_tick - last_tick_l6 >= LOOP6DELAY_MS) {
		loop6(huart,huartI2C,kusbegi,&kusbegi_flags);
		last_tick_l6 = HAL_GetTick();
	}

}

void loop1(UART_HandleTypeDef* huart,I2C_HandleTypeDef *huartI2C,KUSBEGI *kusbegi,KUSBEGI_FLAGS *kusbegi_flags){

	if(update_imu(&output_mixer, huartI2C,kusbegi_flags) == OUTPUT_MIXER_OK){
		kusbegi_flags->FLAG_IMU_READ_OK = 1;
	}
	else{
		kusbegi_flags->FLAG_IMU_READ_OK = 0;
	}

	if (kusbegi_flags->FLAG_IMU_READ_OK == 1) {

		flight_mode_update(&flight_mode, &output_mixer, kusbegi_flags);
		flight_task_update(&flight_task,&flight_mode, &output_mixer, kusbegi_flags);
		update_pid(&output_mixer, flight_task.flight_task_setpoint.yaw,
				flight_task.flight_task_setpoint.pitch,
				flight_task.flight_task_setpoint.roll,
				flight_task.flight_task_setpoint.altitude);
		if((kusbegi_flags->FLAG_ARM == 1) && (kusbegi_flags->KILL_S == 0)){
			set_motor_pwm_values(&output_mixer);
		}

	}

}

void loop2(UART_HandleTypeDef* huart,I2C_HandleTypeDef *huartI2C,KUSBEGI *kusbegi,KUSBEGI_FLAGS *kusbegi_flags){
}

void loop3(UART_HandleTypeDef* huart,I2C_HandleTypeDef *huartI2C,KUSBEGI *kusbegi,KUSBEGI_FLAGS *kusbegi_flags){
}

void loop4(UART_HandleTypeDef* huart,I2C_HandleTypeDef *huartI2C,KUSBEGI *kusbegi,KUSBEGI_FLAGS *kusbegi_flags){
}

void loop5(UART_HandleTypeDef* huart,I2C_HandleTypeDef *huartI2C,KUSBEGI *kusbegi,KUSBEGI_FLAGS *kusbegi_flags){
}

void loop6(UART_HandleTypeDef* huart,I2C_HandleTypeDef *huartI2C,KUSBEGI *kusbegi,KUSBEGI_FLAGS *kusbegi_flags){
}
