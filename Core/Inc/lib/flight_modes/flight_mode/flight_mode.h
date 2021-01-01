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
	mode_stabilize = RC_MODE_STABILIZE,
	mode_alt_hold = RC_MODE_ALT_HOLD,
	mode_pos_hold = RC_MODE_POS_HOLD,
	mode_offboard,
	mode_land,
	mode_auto = RC_MODE_AUTO,
	mode_failsafe
}MODE_TYPE;


typedef struct{
	MODE_TYPE mode_type;
	MODE_TYPE last_mode_type;
	uint32_t failsafe_timer;
	uint8_t failsafe_timer_active;
}FLIGHT_MODE;


int8_t flight_mode_update(FLIGHT_MODE *flight_mode,OUTPUT_MIXER *output_mixer,KUSBEGI_FLAGS *kusbegi_flags);
int8_t flight_mode_transition(FLIGHT_MODE *flight_mode,OUTPUT_MIXER *output_mixer,KUSBEGI_FLAGS *kusbegi_flags);
int8_t flight_mode_available(MODE_TYPE mode_type,KUSBEGI_FLAGS *kusbegi_flags);


/* #ifndef __FLIGHT_MODE_H__ */
#endif
