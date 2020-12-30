/*
 * @Author: canpinaremre
 * Purpose: Flight Mode
 * Language:  C
 */
#ifndef __FLIGHT_MODE_H__
#define __FLIGHT_MODE_H__

#include "stm32f4xx_hal.h"
#include <lib/parameters/parameters.h>
#include <lib/output_mixer/output_mixer.h>

typedef enum{
	mode_stabilize,
	mode_alt_hold,
	mode_pos_hold,
	mode_offboard,
	mode_land,
	mode_auto
}MODE_TYPE;

typedef struct{
	MODE_TYPE mode_type;
	MODE_TYPE last_mode_type;
}FLIGHT_MODE;


int8_t flight_mode_update(FLIGHT_MODE *flight_mode,OUTPUT_MIXER *output_mixer,KUSBEGI_FLAGS *kusbegi_flags);




/* #ifndef __FLIGHT_MODE_H__ */
#endif
