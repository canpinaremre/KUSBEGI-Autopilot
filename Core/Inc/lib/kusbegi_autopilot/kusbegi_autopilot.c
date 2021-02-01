/*
 * @Author: canpinaremre
 * Purpose: Autopilot
 * Language:  C
 */
#include "kusbegi_autopilot.h"

int8_t kusbegi_init(UART_HandleTypeDef* huartMsg,I2C_HandleTypeDef *huartI2C,UART_HandleTypeDef* huartRC,KUSBEGI *kusbegi){
	int8_t rslt;
	/* init output_mixer */
	rslt = init_output_mixer(&output_mixer, huartI2C);

	/* init kusbegi autopilot*/
	kusbegi->mc_arm_state = MC_DISARM;
	kusbegi->mc_fc_state = KUSBEGI_INIT;
	kusbegi->mc_flight_mode = MC_MODE_STABILIZE;
	kusbegi->mc_gps_available = MC_GPS_UNAVAILABLE;
	kusbegi->mc_kill_switch = 0;
	kusbegi->mc_land_state = MC_LANDED;

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

	flight_mode.mode_type = mode_stabilize;
	flight_task.task_type = task_manuel;

	debugger_flag = 0;
	count_for_debug = 0;
	count_for_debug2 = 0;

	return rslt;
}

void kusbegi_loop(UART_HandleTypeDef* huartMsg,I2C_HandleTypeDef *huartI2C,UART_HandleTypeDef* huartRC,KUSBEGI *kusbegi){

	if (HAL_GetTick() - last_tick_l1 >= LOOP1DELAY_MS) {
		loop1(huartMsg,huartI2C,huartRC,kusbegi,&kusbegi_flags);
		last_tick_l1 = HAL_GetTick();

	}
	if (HAL_GetTick() - last_tick_l2 >= LOOP2DELAY_MS) {
		loop2(huartMsg,huartI2C,huartRC,kusbegi,&kusbegi_flags);
		last_tick_l2 = HAL_GetTick();
	}

//	if (kusbegi_tick - last_tick_l3 >= LOOP3DELAY_MS) {
//		loop3(huartMsg,huartI2C,huartRC,kusbegi,&kusbegi_flags);
//		last_tick_l3 = HAL_GetTick();
//	}
	if (HAL_GetTick() - last_tick_l4 >= LOOP4DELAY_MS) {
		loop4(huartMsg,huartI2C,huartRC,kusbegi,&kusbegi_flags);
		last_tick_l4 = HAL_GetTick();
	}
//	if (kusbegi_tick - last_tick_l5 >= LOOP5DELAY_MS) {
//		loop5(huartMsg,huartI2C,huartRC,kusbegi,&kusbegi_flags);
//		last_tick_l5 = HAL_GetTick();
//	}
//	if (kusbegi_tick - last_tick_l6 >= LOOP6DELAY_MS) {
//		loop6(huartMsg,huartI2C,huartRC,kusbegi,&kusbegi_flags);
//		last_tick_l6 = HAL_GetTick();
//	}

}

void loop1(UART_HandleTypeDef* huartMsg,I2C_HandleTypeDef *huartI2C,UART_HandleTypeDef* huartRC,KUSBEGI *kusbegi,KUSBEGI_FLAGS *kusbegi_flags){

	if(update_imu(&output_mixer, huartI2C,kusbegi_flags) == OUTPUT_MIXER_OK){
		kusbegi_flags->FLAG_IMU_READ_OK = 1;
	}
	else{
		kusbegi_flags->FLAG_IMU_READ_OK = 0;
	}

	flight_mode_update(&flight_mode, &output_mixer, kusbegi_flags);
	flight_task_update(&flight_task, &flight_mode, &output_mixer,
			kusbegi_flags);
	update_pid(&output_mixer,huartMsg);
	if ((kusbegi_flags->FLAG_ARM == 1) && (kusbegi_flags->KILL_S == 0)) {
		//TODO: For test.
		//Change later
//		output_mixer.PID_PITCH_OUTPUT = 0.0f;
//		output_mixer.PID_ROLL_OUTPUT = 0.0f;
//		output_mixer.PID_YAW_OUTPUT = 0.0f;
		set_motor_pwm_values(&output_mixer);
	}
	else{
		stop_motors(&output_mixer);
	}
	if(kusbegi_flags->FLAG_SPIN_MOTOR){
		output_mixer.PWM_US_MOTOR[0] = 1000;
		output_mixer.PWM_US_MOTOR[1] = 1000;
		output_mixer.PWM_US_MOTOR[2] = 1000;
		output_mixer.PWM_US_MOTOR[3] = 1000;
	}
	kusbegi->PWM_US_MOTOR[0] = output_mixer.PWM_US_MOTOR[0];
	kusbegi->PWM_US_MOTOR[1] = output_mixer.PWM_US_MOTOR[1];
	kusbegi->PWM_US_MOTOR[2] = output_mixer.PWM_US_MOTOR[2];
	kusbegi->PWM_US_MOTOR[3] = output_mixer.PWM_US_MOTOR[3];

}

void loop2(UART_HandleTypeDef* huartMsg,I2C_HandleTypeDef *huartI2C,UART_HandleTypeDef* huartRC,KUSBEGI *kusbegi,KUSBEGI_FLAGS *kusbegi_flags){

	update_rc(&output_mixer, huartRC,kusbegi_flags);


	if(update_barometer(&output_mixer, huartI2C) == OUTPUT_MIXER_OK){
			kusbegi_flags->FLAG_BARO_R_OK = 1;
		}
		else{
			kusbegi_flags->FLAG_BARO_R_OK = 0;
		}
}

void loop3(UART_HandleTypeDef* huartMsg,I2C_HandleTypeDef *huartI2C,UART_HandleTypeDef* huartRC,KUSBEGI *kusbegi,KUSBEGI_FLAGS *kusbegi_flags){

	/*
	 * TODO: LOGGER
	 */
}

void loop4(UART_HandleTypeDef* huartMsg,I2C_HandleTypeDef *huartI2C,UART_HandleTypeDef* huartRC,KUSBEGI *kusbegi,KUSBEGI_FLAGS *kusbegi_flags){

	/*
	 * TODO: SEND MSG
	 */



	sendString("Throttle: ", huartMsg, 0);
	sendFloat(output_mixer.RC_INPUT.rc_channels[throttle].mapped_value,huartMsg,1);
	sendString("roll: ", huartMsg, 0);
	sendFloat(output_mixer.RC_INPUT.rc_channels[roll].mapped_value,huartMsg,1);
	sendString("ARM: ", huartMsg, 0);
	if(kusbegi_flags->FLAG_ARM){
		sendString("ARMED ", huartMsg, 1);
	}
	else
		sendString("DISARM ", huartMsg, 1);

	sendString("Flag Arm change : ",huartMsg,0);
	sendInt(kusbegi_flags->FLAG_ARM_CHANGE,huartMsg,1);

	sendString("Imu Roll : ", huartMsg, 0);
	sendFloat(output_mixer.IMU.ypr[2], huartMsg, 1);

	sendString("Imu Pitch : ", huartMsg, 0);
	sendFloat(output_mixer.IMU.ypr[1], huartMsg, 1);

	sendString("Imu Yaw : ", huartMsg, 0);
	sendFloat(output_mixer.IMU.ypr[0], huartMsg, 1);

	sendString("YAW DPS : ", huartMsg, 0);
	sendFloat(output_mixer.IMU.yaw_dps, huartMsg, 1);

	sendString("1. Motor PWM :",huartMsg,0);
	sendInt(output_mixer.PWM_US_MOTOR[0],huartMsg,1);

	sendString("2. Motor PWM :", huartMsg, 0);
	sendInt(output_mixer.PWM_US_MOTOR[1], huartMsg, 1);

	sendString("3. Motor PWM :", huartMsg, 0);
	sendInt(output_mixer.PWM_US_MOTOR[2], huartMsg, 1);

	sendString("4. Motor PWM :", huartMsg, 0);
	sendInt(output_mixer.PWM_US_MOTOR[3], huartMsg, 1);

	sendString("IMU read Flag:",huartMsg,0);
	if(kusbegi_flags->FLAG_IMU_READ_OK){
		sendString("OK",huartMsg,1);
	}
	else{
		sendString("ERROR",huartMsg,1);
	}

	sendString("Mode :", huartMsg, 0);
	sendInt(flight_mode.mode_type, huartMsg, 1);

	sendString("Kill :", huartMsg, 0);
	sendInt(kusbegi_flags->KILL_S, huartMsg, 1);


}

void loop5(UART_HandleTypeDef* huartMsg,I2C_HandleTypeDef *huartI2C,UART_HandleTypeDef* huartRC,KUSBEGI *kusbegi,KUSBEGI_FLAGS *kusbegi_flags){

	sendString("IMU READ: ", huartMsg, 0);
	sendInt(kusbegi_flags->FLAG_IMU_READ_OK, huartMsg, 1);

	sendString("YAW: ", huartMsg, 0);
	sendFloat(output_mixer.IMU.eulerXYZ[0], huartMsg, 1);
	sendString("PITCH: ", huartMsg, 0);
	sendFloat(output_mixer.IMU.eulerXYZ[1], huartMsg, 1);
	sendString("ROLL: ", huartMsg, 0);
	sendFloat(output_mixer.IMU.eulerXYZ[2], huartMsg, 1);
	sendString("Pressure: ", huartMsg, 0);
	sendFloat(output_mixer.IMU.pressure, huartMsg, 1);
	sendString("Temperature: ", huartMsg, 0);
	sendFloat(output_mixer.IMU.temperature, huartMsg, 1);
}

void loop6(UART_HandleTypeDef* huartMsg,I2C_HandleTypeDef *huartI2C,UART_HandleTypeDef* huartRC,KUSBEGI *kusbegi,KUSBEGI_FLAGS *kusbegi_flags){


}
