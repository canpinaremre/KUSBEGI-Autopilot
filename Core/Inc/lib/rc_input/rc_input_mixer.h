/*
 * @Author: canpinaremre
 * Purpose: RC Mixer
 * Language:  C
 */

#ifndef __RC_INPUT_MIXER_H__
#define __RC_INPUT_MIXER_H__

#define RC_INPUT_MIXER_CHANNEL_CNT 	9
#define RC_INPUT_MIXER_CH_THROTTLE 	0
#define RC_INPUT_MIXER_CH_YAW 		3
#define RC_INPUT_MIXER_CH_PITCH 	2
#define RC_INPUT_MIXER_CH_ROLL 		1
#define RC_INPUT_MIXER_CH_MODE 		4
#define RC_INPUT_MIXER_CH_KILL 		5
#define RC_INPUT_MIXER_CH_RTH 		6
#define RC_INPUT_MIXER_CH_LAND 		7
#define RC_INPUT_MIXER_CH_OFFBOARD 	8

#define RC_INPUT_MIXER_YAW_MINMAX	20   // +- degrees per second
#define RC_INPUT_MIXER_PITCH_MINMAX	20   // +- degrees
#define RC_INPUT_MIXER_ROLL_MINMAX	60 	 // +- degrees
#define RC_INPUT_MIXER_SWITCH_TH	1500 // PWM needed to activate the switch
#define RC_INPUT_MIXER_MODE1_TH		1350 // MODE1 PWM between 1000 and RC_INPUT_MIXER_MODE1_TH
#define RC_INPUT_MIXER_MODE2_TH		1700 // MODE2 PWM between RC_INPUT_MIXER_MODE1_TH and RC_INPUT_MIXER_MODE2_TH
										 // MODE3 PWM between RC_INPUT_MIXER_MODE2_TH and 2000

#include <module/utility/utility_math.h>
#include <lib/parameters/parameters.h>

typedef enum{
	throttle = 	RC_INPUT_MIXER_CH_THROTTLE,
	yaw		 = 	RC_INPUT_MIXER_CH_YAW,
	pitch 	 = 	RC_INPUT_MIXER_CH_PITCH,
	roll     = 	RC_INPUT_MIXER_CH_ROLL,
	mode 	 = 	RC_INPUT_MIXER_CH_MODE,
	kill_s 	 = 	RC_INPUT_MIXER_CH_KILL,
	rth 	 = 	RC_INPUT_MIXER_CH_RTH,
	land 	 = 	RC_INPUT_MIXER_CH_LAND,
	offboard = 	RC_INPUT_MIXER_CH_OFFBOARD
}RC_CHANNEL_MAP;

typedef struct{
	RC_CHANNEL_MAP 	channel_name;
	uint16_t 		pwm_value;
	float 			mapped_value;
	uint8_t 		bool_value;
}RC_CHANNEL;

typedef struct{
	RC_CHANNEL 	rc_channels[RC_INPUT_MIXER_CHANNEL_CNT];
	uint8_t 	arm_state;
	uint8_t 	failsafe_state;
	uint8_t 	connection_error;
	uint8_t		frame_lost;
}RC_INPUT;

/* If RC input is SBUS define RC_INPUT_IS_SBUS*/
#define RC_INPUT_IS_SBUS
/* If RC input is SBUS define RC_INPUT_IS_SBUS*/
#ifdef RC_INPUT_IS_SBUS
#include "rc_input_sbus.h"
SBUS sbus;

int8_t update_rc_input(UART_HandleTypeDef *huart,RC_INPUT *rc_input);
int8_t init_rc_input(RC_INPUT *rc_input);



/* #ifdef RC_INPUT_IS_SBUS */
#endif




/* If RC input is PWM define RC_INPUT_IS_PWM*/
//#define RC_INPUT_IS_PWM
/* If RC input is PWM define RC_INPUT_IS_PWM*/
#ifdef RC_INPUT_IS_PWM
//TODO
#endif




/* #ifndef __RC_INPUT_MIXER_H__ */
#endif
