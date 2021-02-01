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
#include <lib/flight_tasks/flight_task/flight_task.h>
#include <lib/flight_modes/flight_mode/flight_mode.h>

#define LOOP1DELAY_MS 10
#define LOOP2DELAY_MS 20
#define LOOP3DELAY_MS 40
#define LOOP4DELAY_MS 100
#define LOOP5DELAY_MS 1000
#define LOOP6DELAY_MS 900

typedef enum{
	MC_MODE_STABILIZE,
	MC_MODE_ALT_HOLD,
	MC_MODE_POS_HOLD,
	MC_MODE_LAND,
	MC_MODE_RTH,
	MC_MODE_OFFBOARD,
	MC_MODE_MISSION
}MC_FLIGHT_MODE;

typedef enum{
	MC_DISARM,
	MC_ARM
}MC_ARM_STATE;

typedef enum{
	KUSBEGI_INIT,
	KUSBEGI_OK,
	IMU_ERROR,
	RC_INPUT_ERROR,
	COM_ERROR
}MC_FC_STATE;

typedef enum{
	MC_LANDED,
	MC_GROUND_CONTACT,
	MC_MAYBE_LANDED,
	MC_FREEFALL,
	MC_GROUND_EFFECT
}MC_LAND_STATE;

typedef enum{
	MC_GPS_HEALT_OK,
	MC_GPS_UNAVAILABLE,
	MC_GPS_HEALT_BAD,
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
FLIGHT_MODE flight_mode;
FLIGHT_TASK flight_task;
KUSBEGI_FLAGS kusbegi_flags;

uint32_t kusbegi_tick;

/* This function initialize all Flight Controller */
int8_t kusbegi_init(UART_HandleTypeDef* huartMsg,I2C_HandleTypeDef *huartI2C,UART_HandleTypeDef* huartRC,KUSBEGI *kusbegi);

/* This is the main loop function */
void kusbegi_loop(UART_HandleTypeDef* huartMsg,I2C_HandleTypeDef *huartI2C,UART_HandleTypeDef* huartRC,KUSBEGI *kusbegi);

uint32_t last_tick_l1,last_tick_l2,last_tick_l3,last_tick_l4,last_tick_l5,last_tick_l6;
void loop1(UART_HandleTypeDef* huartMsg,I2C_HandleTypeDef *huartI2C,UART_HandleTypeDef* huartRC,KUSBEGI *kusbegi,KUSBEGI_FLAGS *kusbegi_flags);
void loop2(UART_HandleTypeDef* huartMsg,I2C_HandleTypeDef *huartI2C,UART_HandleTypeDef* huartRC,KUSBEGI *kusbegi,KUSBEGI_FLAGS *kusbegi_flags);
void loop3(UART_HandleTypeDef* huartMsg,I2C_HandleTypeDef *huartI2C,UART_HandleTypeDef* huartRC,KUSBEGI *kusbegi,KUSBEGI_FLAGS *kusbegi_flags);
void loop4(UART_HandleTypeDef* huartMsg,I2C_HandleTypeDef *huartI2C,UART_HandleTypeDef* huartRC,KUSBEGI *kusbegi,KUSBEGI_FLAGS *kusbegi_flags);
void loop5(UART_HandleTypeDef* huartMsg,I2C_HandleTypeDef *huartI2C,UART_HandleTypeDef* huartRC,KUSBEGI *kusbegi,KUSBEGI_FLAGS *kusbegi_flags);
void loop6(UART_HandleTypeDef* huartMsg,I2C_HandleTypeDef *huartI2C,UART_HandleTypeDef* huartRC,KUSBEGI *kusbegi,KUSBEGI_FLAGS *kusbegi_flags);

/* #ifndef __KUSBEGI_AUTOPILOT_H__ */
#endif
