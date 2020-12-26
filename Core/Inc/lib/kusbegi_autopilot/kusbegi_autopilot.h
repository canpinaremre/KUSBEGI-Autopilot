/*
 * @Author: canpinaremre
 * Purpose: Autopilot
 * Language:  C
 */

#ifndef KUSBEGI_AUTOPILOT_H
#define KUSBEGI_AUTOPILOT_H

#include "stm32f4xx_hal.h"
#include <drivers/imu/imu.h>
#include <lib/output_mixer/output_mixer.h>

#define LOOP1FREQ 1000 		//Hz
#define LOOP2FREQ 500 		//Hz
#define LOOP3FREQ 250		//Hz
#define LOOP4FREQ 100		//Hz
#define LOOP5FREQ 20		//Hz
#define LOOP6FREQ 1			//Hz

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

}KUSBEGI;


OUTPUT_MIXER output_mixer;

/* This function initialize all Flight Controller */
uint8_t kusbegi_init(I2C_HandleTypeDef *huart,KUSBEGI *kusbegi);

/* This is the main loop function */
void kusbegi_loop(void);

/* #ifndef KUSBEGI_AUTOPILOT_H */
#endif
