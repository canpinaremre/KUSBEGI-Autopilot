/*
 * @Author: canpinaremre
 * Purpose: IMU
 * Language:  C
 */

#ifndef IMU_H
#define IMU_H
#include "stm32f4xx_hal.h"
#include <drivers/BNO055/BNO055.h>
#include <drivers/BMP280/BMP280.h>

typedef struct{
	float eulerXYZ[3];							//Euler IMU output
	float quaternionWXYZ[4];					//Quaternion IMU output
	float accelXYZ[3];
	float magXYZ[3];
	float liaXYZ[3];
	float grvXYZ[3];
	float gyrXYZ[3];
	float ypr[3];
	float altitude;
	uint32_t pressure;
	double temperature;
	//TODO: IMU setter
}IMU;


//select IMU driver:
#define Selected_IMU_BNO055
#define Selected_BAR_BMP280

uint8_t init_imu(IMU *imu,I2C_HandleTypeDef *huart);
uint8_t read_imu(IMU *imu,I2C_HandleTypeDef *huart);
uint8_t reset_imu(IMU *imu,I2C_HandleTypeDef *huart);
uint8_t set_imu(IMU *imu,I2C_HandleTypeDef *huart);


#ifdef Selected_BAR_BMP280

int8_t bmp280_rslt;
struct bmp280_dev bmp;
struct bmp280_config conf;
struct bmp280_uncomp_data ucomp_data;
uint32_t pres32, pres64;
double pres;
int32_t temp32;
double temp;
uint8_t bmp_i2c_buff[80];
uint8_t power_mode;

uint8_t read_barometer(IMU *imu,I2C_HandleTypeDef *huartI2C);
void delay_ms(uint32_t period_ms);
int8_t i2c_reg_write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data,
		uint16_t length,I2C_HandleTypeDef *huartI2C);
int8_t i2c_reg_read(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data,
		uint16_t length,I2C_HandleTypeDef *huartI2C);
void print_rslt(const char api_name[], int8_t rslt,IMU *imu);

/*#ifdef Selected_BAR_BMP280*/
#endif

/* #ifndef IMU_H */
#endif
