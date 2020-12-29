/*
 * @Author: canpinaremre
 * Purpose: Autopilot
 * Language:  C
 */

#ifndef __KUSBEGI_AUTOPILOT_H__
#define __KUSBEGI_AUTOPILOT_H__

#include "stm32f4xx_hal.h"
#include <drivers/imu/imu.h>
#include <lib/output_mixer/output_mixer.h>
#include <module/send_message/sendMsg.h>
#include <lib/parameters/parameters.h>

#define LOOP1DELAY_MS 1000 		//1 Hz
#define LOOP2DELAY_MS 2000 		//0.5 Hz
#define LOOP3DELAY_MS 250		//4 Hz
#define LOOP4DELAY_MS 100		//10 Hz
#define LOOP5DELAY_MS 10		//100 Hz
#define LOOP6DELAY_MS 5			//200 Hz

typedef enum{
	MODE_STABILIZE,
	MODE_ALT_HOLD,
	MODE_POS_HOLD,
	MODE_LAND,
	MODE_RTH,
	MODE_OFFBOARD,
	MODE_MISSION
}MC_FLIGHT_MODE;

typedef enum{
	DISARM,
	ARM
}MC_ARM_STATE;

typedef enum{
	KUSBEGI_INIT,
	KUSBEGI_OK,
	IMU_ERROR,
	RC_INPUT_ERROR,
	COM_ERROR
}MC_FC_STATE;

typedef enum{
	LANDED,
	GROUND_CONTACT,
	MAYBE_LANDED,
	FREEFALL,
	GROUND_EFFECT
}MC_LAND_STATE;

typedef enum{
	GPS_HEALT_OK,
	GPS_UNAVAILABLE,
	GPS_HEALT_BAD,
}MC_GPS_AVAILABLE;


typedef struct{
	MC_FLIGHT_MODE mc_flight_mode;
	MC_ARM_STATE mc_arm_state;
	MC_FC_STATE mc_fc_state;
	MC_LAND_STATE mc_land_state;
	MC_GPS_AVAILABLE mc_gps_available;

	uint8_t mc_battery_status;
	uint8_t mc_kill_switch;

	uint16_t PWM_US_MOTOR[4];

}KUSBEGI;

OUTPUT_MIXER output_mixer;

uint32_t kusbegi_tick;

/* This function initialize all Flight Controller */
int8_t kusbegi_init(I2C_HandleTypeDef *huartI2C,KUSBEGI *kusbegi,UART_HandleTypeDef* huart);

/* This is the main loop function */
void kusbegi_loop(UART_HandleTypeDef* huart,I2C_HandleTypeDef *huartI2C,KUSBEGI *kusbegi);

uint32_t last_tick_l1,last_tick_l2,last_tick_l3,last_tick_l4,last_tick_l5,last_tick_l6;
void loop1(UART_HandleTypeDef* huart);
void loop2(UART_HandleTypeDef* huart,I2C_HandleTypeDef *huartI2C);
void loop3(UART_HandleTypeDef* huart);
void loop4(UART_HandleTypeDef* huart,KUSBEGI *kusbegi,OUTPUT_MIXER *output_mixer);
void loop5(UART_HandleTypeDef* huart);
void loop6(UART_HandleTypeDef* huart);

/* #ifndef __KUSBEGI_AUTOPILOT_H__ */
#endif
