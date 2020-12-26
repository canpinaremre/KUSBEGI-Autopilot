/*
 * @Author: canpinaremre
 * Purpose: PID
 * Language:  C
 */

#ifndef IMU_H
#define IMU_H
#include "stm32f4xx_hal.h"
#include <drivers/BNO055/BNO055.h>

typedef struct{
	float eulerXYZ[3];							//Euler IMU output
	float quaternionWXYZ[4];					//Quaternion IMU output
	float accelXYZ[3];
	float magXYZ[3];
	float liaXYZ[3];
	float grvXYZ[3];
	float gyrXYZ[3];
	float ypr[3];
	//TODO: IMU setter
}IMU;


//select IMU driver:
#define Selected_IMU_BNO055

uint8_t init_imu(IMU *imu,I2C_HandleTypeDef *huart);
uint8_t read_imu(IMU *imu,I2C_HandleTypeDef *huart);
uint8_t reset_imu(IMU *imu,I2C_HandleTypeDef *huart);
uint8_t set_imu(IMU *imu,I2C_HandleTypeDef *huart);




#endif
