/*
 * @Author: canpinaremre
 * Purpose: RC Mixer
 * Language:  C
 */
#include "output_mixer.h"


uint8_t init_output_mixer(OUTPUT_MIXER *output_mixer,I2C_HandleTypeDef *huartI2C,UART_HandleTypeDef* huart){

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

	//init PID
	PIDController_Init(&pid_altitude);
	PIDController_Init(&pid_roll);
	PIDController_Init(&pid_pitch);
	PIDController_Init(&pid_yaw);

	//init output_mixer
	output_mixer->PWM_US_MOTOR[0] = 0;
	output_mixer->PWM_US_MOTOR[1] = 0;
	output_mixer->PWM_US_MOTOR[2] = 0;
	output_mixer->PWM_US_MOTOR[3] = 0;

	output_mixer->PID_ALTITUDE_OUTPUT = 0;
	output_mixer->PID_ROLL_OUTPUT = 0;
	output_mixer->PID_PITCH_OUTPUT = 0;
	output_mixer->PID_YAW_OUTPUT = 0;

	init_imu(&output_mixer->IMU, huartI2C);
	init_rc_input(&output_mixer->RC_INPUT);

	//init IMU
	init_imu(&imu, huartI2C);

	//init RC_input
	init_rc_input(&rc_input);

	//init Temp
	temp32 = 0;
	temp = 0;

	//init Barometer
	/* Map the delay function pointer with the function responsible for implementing the delay */
	bmp.delay_ms = delay_ms;

	/* Assign device I2C address based on the status of SDO pin (GND for PRIMARY(0x76) & VDD for SECONDARY(0x77)) */
	bmp.dev_id = 0xED;

	/* Select the interface mode as I2C */
	bmp.intf = BMP280_I2C_INTF;

	/* Map the I2C read & write function pointer with the functions responsible for I2C bus transfer */
	bmp.read = i2c_reg_read;
	bmp.write = i2c_reg_write;


	bmp280_rslt = bmp280_init(&bmp, huartI2C);

	sendString("bmp280_init", huart, 1);
	sendInt(bmp280_rslt, huart, 1);
	sendString("Chipid:", huart, 0);
	sendInt(read8(huartI2C,0xED,0xD0), huart, 1);

	bmp280_rslt = bmp280_get_config(&conf, &bmp, huartI2C);
	if (!bmp280_rslt) {
		sendString("bmp280_get_config = 0:", huart, 0);
		sendInt(bmp280_rslt, huart, 1);
		sendString("filter:", huart, 0);
		sendInt(conf.filter, huart, 1);
		sendString("os_pres:", huart, 0);
		sendInt(conf.os_pres, huart, 1);
		sendString("os_temp:", huart, 0);
		sendInt(conf.os_temp, huart, 1);
	}

	conf.filter = BMP280_FILTER_COEFF_2;
	conf.os_temp = BMP280_OS_4X;
	/* Pressure oversampling set at 4x */
	conf.os_pres = BMP280_OS_4X;

	/* Setting the output data rate as 1HZ(1000ms) */
	conf.odr = BMP280_ODR_1000_MS;
	bmp280_rslt = bmp280_set_config(&conf, &bmp, huartI2C);
	if (bmp280_rslt) {
		sendString("bmp280_set_config != 0", huart, 1);
		sendInt(bmp280_rslt, huart, 1);
	}

	bmp280_rslt = bmp280_get_config(&conf, &bmp, huartI2C);
	if (!bmp280_rslt) {
		sendString("bmp280_get_config = 0:", huart, 0);
		sendInt(bmp280_rslt, huart, 1);
		sendString("filter:", huart, 0);
		sendInt(conf.filter, huart, 1);
		sendString("os_pres:", huart, 0);
		sendInt(conf.os_pres, huart, 1);
		sendString("os_temp:", huart, 0);
		sendInt(conf.os_temp, huart, 1);
	}

	/* Always set the power mode after setting the configuration */
	bmp280_rslt = bmp280_set_power_mode(BMP280_NORMAL_MODE, &bmp, huartI2C);
	//print_rslt(" bmp280_set_power_mode status", rslt);
	if (bmp280_rslt) {
		sendString("bmp280_set_power_mode != 0", huart, 1);
		sendInt(bmp280_rslt, huart, 1);
	}
	power_mode = 0;
	bmp280_rslt = bmp280_get_power_mode(&power_mode,&bmp,huartI2C);
	if (!bmp280_rslt) {
		sendString("bmp280_get_power_mode = 0", huart, 1);
		sendInt(power_mode, huart, 1);
	}
	sendString("powemode:", huart, 0);
	sendInt(read8(huartI2C, 0xED, BMP280_CTRL_MEAS_ADDR), huart, 1);

	//TODO:Check all inits
	return 1;
}

uint8_t calculate_pid_values(OUTPUT_MIXER *output_mixer,RC_INPUT *rc_input,IMU *imu){

	output_mixer->PID_ROLL_OUTPUT = PIDController_Update(&pid_roll,rc_input->rc_channels[roll].mapped_value,imu->ypr[2]);
	output_mixer->PID_PITCH_OUTPUT = PIDController_Update(&pid_pitch,rc_input->rc_channels[pitch].mapped_value,imu->ypr[1]);
	output_mixer->PID_YAW_OUTPUT = PIDController_Update(&pid_yaw,rc_input->rc_channels[yaw].mapped_value,imu->ypr[0]);
	output_mixer->PID_ALTITUDE_OUTPUT = rc_input->rc_channels[throttle].pwm_value;
	return 1;
}

uint8_t set_motor_pwm_values(OUTPUT_MIXER *output_mixer){
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

	return 1;
}


uint8_t update_pid(OUTPUT_MIXER *output_mixer) {

	/* Calculate PID*/
	calculate_pid_values(output_mixer, &rc_input, &imu);
	return 1;
}

uint8_t update_imu(OUTPUT_MIXER *output_mixer, I2C_HandleTypeDef *huartI2C) {

	/* Read IMU*/
	read_imu(&imu, huartI2C);
	//TODO: get error

	/* Copy IMU to output_mixer struct*/
	output_mixer->IMU = imu;

	return 1;
}

uint8_t update_barometer(OUTPUT_MIXER *output_mixer, I2C_HandleTypeDef *huartI2C){

	/* Read Barometer*/
	read_barometer(&imu,huartI2C);


	//TODO: get error

	/* Copy IMU to output_mixer struct*/
	output_mixer->IMU = imu;

	return 1;
}

uint8_t update_rc(OUTPUT_MIXER *output_mixer, UART_HandleTypeDef *huartRC) {
	/*Read RC*/
	update_rc_input(huartRC, &rc_input);

	/* Copy RC to output_mixer struct*/
	output_mixer->RC_INPUT = rc_input;
	return 1;
}



