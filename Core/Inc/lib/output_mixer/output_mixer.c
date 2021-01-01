/*
 * @Author: canpinaremre
 * Purpose: RC Mixer
 * Language:  C
 */
#include "output_mixer.h"


int8_t init_output_mixer(OUTPUT_MIXER *output_mixer,I2C_HandleTypeDef *huartI2C){
	int8_t rslt;

	//Set PID values
	pid_roll.Kp = PID_ROLL_PITCH_KP;
	pid_altitude.Kp = PID_ALTITUDE_KP;
	pid_pitch.Kp = PID_ROLL_PITCH_KP;
	pid_yaw.Kp = PID_YAW_KP;

	pid_roll.Ki = PID_ROLL_PITCH_KI;
	pid_altitude.Ki = PID_ALTITUDE_KI;
	pid_pitch.Ki = PID_ROLL_PITCH_KI;
	pid_yaw.Ki = PID_YAW_KI;

	pid_roll.Kd = PID_ROLL_PITCH_KD;
	pid_altitude.Kd = PID_ALTITUDE_KD;
	pid_pitch.Kd = PID_ROLL_PITCH_KD;
	pid_yaw.Kd = PID_YAW_KD;

	pid_roll.tau = PID_TAU;
	pid_altitude.tau = PID_TAU;
	pid_pitch.tau = PID_TAU;
	pid_yaw.tau = PID_TAU;

	pid_roll.limMin = PID_ROLL_PITCH_LIM_MIN;
	pid_altitude.limMin = PID_ALTITUDE_LIM_MIN;
	pid_pitch.limMin = PID_ROLL_PITCH_LIM_MIN;
	pid_yaw.limMin = PID_YAW_LIM_MIN;

	pid_roll.limMax = PID_ROLL_PITCH_LIM_MAX;
	pid_altitude.limMax = PID_ALTITUDE_LIM_MAX;
	pid_pitch.limMax = PID_ROLL_PITCH_LIM_MAX;
	pid_yaw.limMax = PID_YAW_LIM_MAX;

	pid_roll.limMinInt = PID_ROLL_PITCH_LIM_MIN_INT;
	pid_altitude.limMinInt = PID_ALTITUDE_LIM_MIN_INT;
	pid_pitch.limMinInt = PID_ROLL_PITCH_LIM_MIN_INT;
	pid_yaw.limMinInt = PID_YAW_LIM_MIN_INT;

	pid_roll.limMaxInt = PID_ROLL_PITCH_LIM_MAX_INT;
	pid_altitude.limMaxInt = PID_ALTITUDE_LIM_MAX_INT;
	pid_pitch.limMaxInt = PID_ROLL_PITCH_LIM_MAX_INT;
	pid_yaw.limMaxInt = PID_YAW_LIM_MAX_INT;

	pid_roll.T = SAMPLE_TIME_S;
	pid_altitude.T = SAMPLE_TIME_S;
	pid_pitch.T = SAMPLE_TIME_S;
	pid_yaw.T = SAMPLE_TIME_S;

	//Init PID
	PIDController_Init(&pid_altitude);
	PIDController_Init(&pid_roll);
	PIDController_Init(&pid_pitch);
	PIDController_Init(&pid_yaw);

	//Init output_mixer
	output_mixer->PWM_US_MOTOR[0] = 0;
	output_mixer->PWM_US_MOTOR[1] = 0;
	output_mixer->PWM_US_MOTOR[2] = 0;
	output_mixer->PWM_US_MOTOR[3] = 0;

	output_mixer->PID_ALTITUDE_OUTPUT = 0;
	output_mixer->PID_ROLL_OUTPUT = 0;
	output_mixer->PID_PITCH_OUTPUT = 0;
	output_mixer->PID_YAW_OUTPUT = 0;

	output_mixer->IMU.eulerXYZ[0] = 0;
	output_mixer->IMU.eulerXYZ[1] = 0;
	output_mixer->IMU.eulerXYZ[2] = 0;

	output_mixer->IMU.quaternionWXYZ[0] = 0;
	output_mixer->IMU.quaternionWXYZ[1] = 0;
	output_mixer->IMU.quaternionWXYZ[2] = 0;
	output_mixer->IMU.quaternionWXYZ[3] = 0;

	output_mixer->IMU.accelXYZ[0] = 0;
	output_mixer->IMU.accelXYZ[1] = 0;
	output_mixer->IMU.accelXYZ[2] = 0;

	output_mixer->IMU.magXYZ[0] = 0;
	output_mixer->IMU.magXYZ[1] = 0;
	output_mixer->IMU.magXYZ[2] = 0;

	output_mixer->IMU.liaXYZ[0] = 0;
	output_mixer->IMU.liaXYZ[1] = 0;
	output_mixer->IMU.liaXYZ[2] = 0;

	output_mixer->IMU.grvXYZ[0] = 0;
	output_mixer->IMU.grvXYZ[1] = 0;
	output_mixer->IMU.grvXYZ[2] = 0;

	output_mixer->IMU.gyrXYZ[0] = 0;
	output_mixer->IMU.gyrXYZ[1] = 0;
	output_mixer->IMU.gyrXYZ[2] = 0;

	output_mixer->IMU.ypr[0] = 0;
	output_mixer->IMU.ypr[1] = 0;
	output_mixer->IMU.ypr[2] = 0;

	output_mixer->IMU.temperature = 0;
	output_mixer->IMU.pressure = 0;

	output_mixer->RC_INPUT.rc_channels[throttle].pwm_value = 0;
	output_mixer->RC_INPUT.rc_channels[yaw].pwm_value = 0;
	output_mixer->RC_INPUT.rc_channels[pitch].pwm_value = 0;
	output_mixer->RC_INPUT.rc_channels[roll].pwm_value = 0;

	//init IMU
	rslt = init_imu(&imu, huartI2C);
	if(rslt != IMU_INIT_OK){
		return rslt;
	}

	//init RC_input
	rslt = init_rc_input(&rc_input);
	if (rslt != RC_INPUT_OK) {
		return rslt;
	}

	return OUTPUT_MIXER_OK;
}

int8_t calculate_pid_values(OUTPUT_MIXER *output_mixer,IMU *imu,float setpoint_yaw,float setpoint_pitch,float setpoint_roll,float setpoint_altitude){

	output_mixer->PID_YAW_OUTPUT = PIDController_Update(&pid_yaw,setpoint_yaw,imu->ypr[0]);
	output_mixer->PID_PITCH_OUTPUT = PIDController_Update(&pid_pitch,setpoint_pitch,imu->ypr[1]);
	output_mixer->PID_ROLL_OUTPUT = PIDController_Update(&pid_roll,setpoint_roll,imu->ypr[2]);
	output_mixer->PID_ALTITUDE_OUTPUT = PIDController_Update(&pid_altitude,setpoint_altitude,imu->altitude);

	return OUTPUT_MIXER_OK;
}

int8_t set_motor_pwm_values(OUTPUT_MIXER *output_mixer){
	//TODO: Check ARM, failsafe etc.

	/*
	 * QUAD X FRAME:
	 *
	 * 3		1			 [2]		[0]
	 *
	 * 	   ^		 ----> 		   ^
	 *
	 * 2		4			 [1]		[3]
	 *
	 *
	 */
	output_mixer->PWM_US_MOTOR[0] =
			(uint16_t) (output_mixer->PID_ALTITUDE_OUTPUT
					- output_mixer->PID_ROLL_OUTPUT
					+ output_mixer->PID_PITCH_OUTPUT
					+ output_mixer->PID_YAW_OUTPUT);
	output_mixer->PWM_US_MOTOR[1] =
			(uint16_t) (output_mixer->PID_ALTITUDE_OUTPUT
					+ output_mixer->PID_ROLL_OUTPUT
					- output_mixer->PID_PITCH_OUTPUT
					+ output_mixer->PID_YAW_OUTPUT);
	output_mixer->PWM_US_MOTOR[2] =
			(uint16_t) (output_mixer->PID_ALTITUDE_OUTPUT
					+ output_mixer->PID_ROLL_OUTPUT
					+ output_mixer->PID_PITCH_OUTPUT
					- output_mixer->PID_YAW_OUTPUT);
	output_mixer->PWM_US_MOTOR[3] =
			(uint16_t) (output_mixer->PID_ALTITUDE_OUTPUT
					- output_mixer->PID_ROLL_OUTPUT
					- output_mixer->PID_PITCH_OUTPUT
					- output_mixer->PID_YAW_OUTPUT);
	/* Clamp output*/
	for (uint8_t i = 0; i < 4; i++) {
		if (output_mixer->PWM_US_MOTOR[i] > OUTPUT_MIXER_MAX_PWM) {
			output_mixer->PWM_US_MOTOR[i] = OUTPUT_MIXER_MAX_PWM;
		} else if (output_mixer->PWM_US_MOTOR[i] < OUTPUT_MIXER_MIN_PWM) {
			output_mixer->PWM_US_MOTOR[i] = OUTPUT_MIXER_MIN_PWM;
		}
	}

	return OUTPUT_MIXER_OK;
}

int8_t stop_motors(OUTPUT_MIXER *output_mixer){

	output_mixer->PWM_US_MOTOR[0] = 0;
	output_mixer->PWM_US_MOTOR[1] = 0;
	output_mixer->PWM_US_MOTOR[2] = 0;
	output_mixer->PWM_US_MOTOR[3] = 0;

	return 1;
}

int8_t update_pid(OUTPUT_MIXER *output_mixer, float setpoint_yaw,
		float setpoint_pitch, float setpoint_roll, float setpoint_altitude) {
	int8_t rslt;
	/* Calculate PID*/
	rslt = calculate_pid_values(output_mixer, &imu, setpoint_yaw,
			setpoint_pitch, setpoint_roll, setpoint_altitude);

	return rslt;
}

int8_t update_imu(OUTPUT_MIXER *output_mixer, I2C_HandleTypeDef *huartI2C,
		KUSBEGI_FLAGS *kusbegi_flags) {
	int8_t rslt;

	/* Read IMU*/
	rslt = read_imu(&imu, huartI2C, kusbegi_flags);
	if (rslt != IMU_READ_OK) {
		return rslt;
	}
	/* Copy IMU to output_mixer struct*/
	output_mixer->IMU = imu;

	return OUTPUT_MIXER_OK;
}

int8_t update_barometer(OUTPUT_MIXER *output_mixer, I2C_HandleTypeDef *huartI2C){
	int8_t rslt;
	/* Read Barometer*/
	rslt = read_barometer(&imu,huartI2C);
	if (rslt != IMU_READ_OK) {
		return rslt;
	}

	/* Copy IMU to output_mixer struct*/
	output_mixer->IMU = imu;

	return OUTPUT_MIXER_OK;
}

int8_t update_rc(OUTPUT_MIXER *output_mixer, UART_HandleTypeDef *huartRC,KUSBEGI_FLAGS *kusbegi_flags) {
	int8_t rslt;
	/*Read RC*/
	rslt = update_rc_input(huartRC, &rc_input);
	if (rslt != RC_INPUT_OK) {
		return rslt;
	}

	if(rc_input.connection_error){
		kusbegi_flags->FLAG_RC_CONNECTION_E = 1;
		return RC_INPUT_E_CONN_LOST;
	}

	if(rc_input.failsafe_state){
		kusbegi_flags->FLAG_RC_FAILSAFE = 1;
		return RC_INPUT_E_FAILSAFE;
	}

	if(rc_input.frame_lost){
		kusbegi_flags->FLAG_RC_FRAME_LOST = 1;
		return RC_INPUT_E_FRAME_LOST;
	}

	if(rc_input.rc_channels[kill_s].bool_value == 1){
		kusbegi_flags->KILL_S = 1;
		kusbegi_flags->KILL_S_CHANGE = 1;
	}

	if(output_mixer->RC_INPUT.arm_state !=rc_input.arm_state){
		kusbegi_flags->FLAG_ARM_CHANGE = 1;
	}

	if ((output_mixer->RC_INPUT.rc_channels[mode].bool_value
			!= rc_input.rc_channels[mode].bool_value)) {

		kusbegi_flags->FLAG_MODE_CHANGE = 1;
	}


	/* Copy RC to output_mixer struct*/
	output_mixer->RC_INPUT = rc_input;





	return rc_input.rc_channels[throttle].pwm_value;
}



