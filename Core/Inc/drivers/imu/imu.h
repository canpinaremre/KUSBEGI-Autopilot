/*
 * @Author: canpinaremre
 * Purpose: IMU
 * Language:  C
 */

#ifndef __IMU_H__
#define __IMU_H__
#include "stm32f4xx_hal.h"
#include <drivers/BNO055/BNO055.h>
#include <drivers/BMP280/BMP280.h>
#include <lib/parameters/parameters.h>
#include <module/utility/utility_math.h>

typedef struct{
	float eulerXYZ[3];							//Euler IMU output
	double quaternionWXYZ[4];					//Quaternion IMU output
	float accelXYZ[3];
	float magXYZ[3];
	float liaXYZ[3];
	float grvXYZ[3];
	float gyrXYZ[3];
	float ypr[3];
	float altitude;
	float yaw_dps;
	uint32_t pressure;
	double temperature;
	uint32_t last_read_time;
	float deltaT;
}IMU;


//select IMU driver:
#define Selected_IMU_BNO055
#define Selected_BAR_BMP280

int8_t init_imu(IMU *imu,I2C_HandleTypeDef *huartI2C);
int8_t read_imu(IMU *imu,I2C_HandleTypeDef *huartI2C,KUSBEGI_FLAGS *kusbegi_flags);
int8_t reset_imu(IMU *imu,I2C_HandleTypeDef *huartI2C);
int8_t set_imu(IMU *imu,I2C_HandleTypeDef *huartI2C);


#ifdef Selected_BAR_BMP280


struct bmp280_dev bmp;
struct bmp280_config conf;
struct bmp280_uncomp_data ucomp_data;
uint32_t pres32, pres64;
double pres;
int32_t temp32;
double temp;
uint8_t bmp_i2c_buff[80];
uint8_t power_mode;

int8_t read_barometer(IMU *imu,I2C_HandleTypeDef *huartI2C);
void delay_ms(uint32_t period_ms);
int8_t i2c_reg_write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data,
		uint16_t length,I2C_HandleTypeDef *huartI2C);
int8_t i2c_reg_read(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data,
		uint16_t length,I2C_HandleTypeDef *huartI2C);


/*#ifdef Selected_BAR_BMP280*/
#endif

/* #ifndef __IMU_H__ */
#endif
