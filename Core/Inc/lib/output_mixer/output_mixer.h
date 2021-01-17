/*
 * @Author: canpinaremre
 * Purpose: RC Mixer
 * Language:  C
 */

#ifndef __OUTPUT_MIXER_H__
#define __OUTPUT_MIXER_H__

#include <lib/rc_input/rc_input_mixer.h>
#include <drivers/imu/imu.h>
#include <lib/pid/pid.h>
#include "stm32f4xx_hal.h"
#include <module/send_message/sendMsg.h>
#include <lib/parameters/parameters.h>


#define OUTPUT_MIXER_MAX_PWM 2000
#define OUTPUT_MIXER_MIN_PWM 1000
/* ROLL and PITCH PID VALUES */
#define PID_ROLL_PITCH_KP  2.1f
#define PID_ROLL_PITCH_KI  3.1f
#define PID_ROLL_PITCH_KD  0.55f

#define PID_ROLL_PITCH_LIM_MIN -500.0f
#define PID_ROLL_PITCH_LIM_MAX  500.0f

#define PID_ROLL_PITCH_LIM_MIN_INT -15.0f
#define PID_ROLL_PITCH_LIM_MAX_INT  15.0f

/* YAW PID VALUES*/
#define PID_YAW_KP  1.0f
#define PID_YAW_KI  0.0f
#define PID_YAW_KD  0.25f

#define PID_YAW_LIM_MIN -10.0f
#define PID_YAW_LIM_MAX  10.0f

#define PID_YAW_LIM_MIN_INT -5.0f
#define PID_YAW_LIM_MAX_INT  5.0f

/* ALTITUDE PID VALUES*/
#define PID_ALTITUDE_KP  2.0f
#define PID_ALTITUDE_KI  0.5f
#define PID_ALTITUDE_KD  0.25f

#define PID_ALTITUDE_LIM_MIN -10.0f
#define PID_ALTITUDE_LIM_MAX  10.0f

#define PID_ALTITUDE_LIM_MIN_INT -5.0f
#define PID_ALTITUDE_LIM_MAX_INT  5.0f

/* PID SAMPLING VALUES FOR 100 Hz*/
#define SAMPLE_TIME_S 0.01f
#define PID_TAU 0.02f

typedef struct{
	uint16_t PWM_US_MOTOR[4];
	float PID_ROLL_OUTPUT;
	float PID_PITCH_OUTPUT;
	float PID_YAW_OUTPUT;
	float PID_ALTITUDE_OUTPUT;
	float SETPOINT_YPRA[4];
	float MEASURE_YPRA[4];
	RC_INPUT RC_INPUT;
	IMU IMU;
}OUTPUT_MIXER;

RC_INPUT rc_input;
PIDController pid_roll,pid_pitch,pid_altitude,pid_yaw;
IMU imu;
float old_yaw;

/* This function initiliaze IMU, PID, RC_input and output_mixer */
int8_t init_output_mixer(OUTPUT_MIXER *output_mixer,I2C_HandleTypeDef *huartI2C);

/* This function calculates PID values with IMU and RC readings*/
int8_t calculate_pid_values(OUTPUT_MIXER *output_mixer,IMU *imu);

/* This function set motor pwm values*/
int8_t set_motor_pwm_values(OUTPUT_MIXER *output_mixer);

/* This ducntion stops motors*/
int8_t stop_motors(OUTPUT_MIXER *output_mixer);

/* This function updates the PID */
int8_t update_pid(OUTPUT_MIXER *output_mixer);

/* This function updates the imu and output_mixer struct */
int8_t update_imu(OUTPUT_MIXER *output_mixer, I2C_HandleTypeDef *huartI2C,KUSBEGI_FLAGS *kusbegi_flags);

/* This function updates the rc and output_mixer struct */
int8_t update_rc(OUTPUT_MIXER *output_mixer, UART_HandleTypeDef *huartRC,KUSBEGI_FLAGS *kusbegi_flags);

int8_t update_barometer(OUTPUT_MIXER *output_mixer, I2C_HandleTypeDef *huartI2C);


/* #ifndef __OUTPUT_MIXER_H__ */
#endif
