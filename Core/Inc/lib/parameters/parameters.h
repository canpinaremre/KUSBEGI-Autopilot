/*
 * @Author: canpinaremre
 * Purpose: Defines all system parameters
 * Language:  C
 */

#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__
#include "stm32f4xx_hal.h"

#define ARM_SPIN_MOTOR_TIME					1500
#define RC_YAW_MAX_DEGREE_PER_SECOND		20
#define RC_FAILSAFE_TIME_MS					300

/*
 * DO NOT GIVE SAME NUMBER.
 * 1, 2 and 3 IS USED ONLY
 * RC mode channel mapped to 1,2 and 3
 */
#define RC_MODE_STABILIZE					1
#define RC_MODE_ALT_HOLD					2
#define RC_MODE_POS_HOLD					3
#define RC_MODE_AUTO						99

/*******************************************************/
/*! @name BMP280 Return codes */
/*! @name BMP280 Success code*/
#define BMP280_OK                            INT8_C(0)
#define BMP280_BOND_WIRE_OK                  INT8_C(0)

/*! @name BMP280 Error codes */
#define BMP280_E_NULL_PTR                    INT8_C(-1)
#define BMP280_E_DEV_NOT_FOUND               INT8_C(-2)
#define BMP280_E_INVALID_LEN                 INT8_C(-3)
#define BMP280_E_COMM_FAIL                   INT8_C(-4)
#define BMP280_E_INVALID_MODE                INT8_C(-5)
#define BMP280_E_BOND_WIRE                   INT8_C(-6)
#define BMP280_E_IMPLAUS_TEMP                INT8_C(-7)
#define BMP280_E_IMPLAUS_PRESS               INT8_C(-8)
#define BMP280_E_CAL_PARAM_RANGE             INT8_C(-9)
#define BMP280_E_UNCOMP_TEMP_RANGE           INT8_C(-10)
#define BMP280_E_UNCOMP_PRES_RANGE           INT8_C(-11)
#define BMP280_E_UNCOMP_TEMP_AND_PRESS_RANGE INT8_C(-12)
#define BMP280_E_UNCOMP_DATA_CALC            INT8_C(-13)
#define BMP280_E_32BIT_COMP_TEMP             INT8_C(-14)
#define BMP280_E_32BIT_COMP_PRESS            INT8_C(-15)
#define BMP280_E_64BIT_COMP_PRESS            INT8_C(-16)
#define BMP280_E_DOUBLE_COMP_TEMP            INT8_C(-17)
#define BMP280_E_DOUBLE_COMP_PRESS           INT8_C(-18)


/*******************************************************/
/*! @name BNO055 Return codes */
/*! @name BNO055 Success code*/
#define BNO055_OK                            INT8_C(0)

/*! @name BNO055 Error codes */
#define BNO055_E_DEV_NOT_FOUND 	             INT8_C(-19)
#define BNO055_E_EMPTY_FUNCTION	             INT8_C(-20)
#define BNO055_E_SET_MODE_FAIL	             INT8_C(-21)
#define BNO055_E_GET_MODE_OFF_RANGE			 INT8_C(-22)


/*******************************************************/
/*! @name IMU Return codes */
/*! @name IMU Success code*/
#define IMU_INIT_OK                          INT8_C(0)
#define IMU_READ_OK                          INT8_C(0)

/*! @name IMU Error codes */


/*******************************************************/
/*! @name RC_INPUT Return codes */
/*! @name RC_INPUT Success code*/
#define RC_INPUT_OK                         INT8_C(0)

/*! @name RC_INPUT Error codes */
#define RC_INPUT_E_CONN_LOST			 	INT8_C(-23)
#define RC_INPUT_E_FRAME_LOST			 	INT8_C(-24)
#define RC_INPUT_E_FAILSAFE			 		INT8_C(-25)
#define RC_INPUT_E_UNKOWN					INT8_C(-26)


/*******************************************************/
/*! @name OUTPUT_MIXER Return codes */
/*! @name OUTPUT_MIXER Success code*/
#define OUTPUT_MIXER_OK                      INT8_C(0)


/*! @name OUTPUT_MIXER Error codes */


/*******************************************************/
/*! @name FLIGHT_MODE Return codes */
/*! @name FLIGHT_MODE Success code*/
#define FLIGHT_MODE_AVAILABLE               INT8_C(0)

/*! @name FLIGHT_MODE Error codes */
#define FLIGHT_MODE_E_NO_GPS   				INT8_C(-27)
#define FLIGHT_MODE_E_NO_BAR   				INT8_C(-28)
#define FLIGHT_MODE_E_NO_IMU   				INT8_C(-29)
#define FLIGHT_MODE_E_NO_LINK  				INT8_C(-30)
#define FLIGHT_MODE_E_UNKOWN_MODE			INT8_C(-31)

typedef struct{
	uint8_t FLAG_IMU_READ_OK;
	uint8_t FLAG_IMU_ACC_R_OK;
	uint8_t FLAG_IMU_GYR_R_OK;
	uint8_t FLAG_IMU_LIA_R_OK;
	uint8_t FLAG_IMU_QUA_R_OK;
	uint8_t FLAG_IMU_EUL_R_OK;
	uint8_t FLAG_BARO_R_OK;
	uint8_t FLAG_ARM;
	uint8_t KILL_S;
	uint8_t KILL_S_CHANGE;
	uint8_t FLAG_MODE_CHANGE;
	uint8_t FLAG_ARM_CHANGE;
	uint8_t FLAG_RC_FRAME_LOST;
	uint8_t FLAG_RC_CONNECTION_E;
	uint8_t FLAG_RC_FAILSAFE;
	uint8_t FLAG_SPIN_MOTOR;
}KUSBEGI_FLAGS;

/* If debugger_flag is -1 program stops*/
int8_t debugger_flag;
uint32_t count_for_debug;
uint32_t count_for_debug2;
uint32_t count_for_debug3;

/* #ifndef __PARAMETERS_H_ */
#endif
