/*
 * @Author: canpinaremre
 * Purpose: To read and write 8bits on I2C by using HAL Library
 * Language:  C
 */
#ifndef __I2C_READ_WRITE_H__
#define __I2C_READ_WRITE_H__

#include "stm32f4xx_hal.h"
#include <lib/parameters/parameters.h>

#define I2C_TRANSMIT_TIMEOUT 10
#define I2C_RECEIVE_TIMEOUT 20

uint8_t buffer_i2c[2];
/*
 * I2C write 8 bits to bus
 */
int8_t write8(I2C_HandleTypeDef *huart,uint8_t device,uint8_t reg,uint8_t val);
/*
 * I2C Read 8 bits from bus
 */
int8_t read8(I2C_HandleTypeDef *huart,uint8_t device,uint8_t reg,uint8_t *val);
/*
 * I2C Anti-DeadLock
 */
void I2C1_ClearBusyFlagErratum(I2C_HandleTypeDef *instance);


/* #ifndef __I2C_READ_WRITE_H__ */
#endif
