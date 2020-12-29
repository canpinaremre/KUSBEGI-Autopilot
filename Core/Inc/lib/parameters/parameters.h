/*
 * @Author: canpinaremre
 * Purpose: Defines all system parameters
 * Language:  C
 */

#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

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
#define RC_INPUT_OK                          INT8_C(0)

/*! @name RC_INPUT Error codes */


/*******************************************************/
/*! @name OUTPUT_MIXER Return codes */
/*! @name OUTPUT_MIXER Success code*/
#define OUTPUT_MIXER_OK                      INT8_C(0)


/*! @name OUTPUT_MIXER Error codes */


/*******************************************************/
/*! @name BNO055 Return codes */
/*! @name BNO055 Success code*/
#define BNO_OK                            INT8_C(0)

/*! @name BNO055 Error codes */






/* #ifndef __PARAMETERS_H_ */
#endif
