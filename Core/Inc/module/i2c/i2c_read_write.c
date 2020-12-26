/*
 * @Author: canpinaremre
 * Purpose: To read and write 8bits on I2C by using HAL Library
 * Language:  C
 */


#include <module/i2c/i2c_read_write.h>




uint8_t write8(I2C_HandleTypeDef *huart,uint8_t device,uint8_t reg,uint8_t val){
	buffer[0] = reg;
	buffer[1] = val;
	HAL_I2C_Master_Transmit(huart, device, buffer, 2, I2C_TRANSMIT_TIMEOUT);

	return 1;
}

uint8_t read8(I2C_HandleTypeDef *huart,uint8_t device,uint8_t reg){
	buffer[0] = reg;
	HAL_I2C_Master_Transmit(huart, device, buffer, 1, I2C_TRANSMIT_TIMEOUT);
	HAL_I2C_Master_Receive(huart, device, &buffer[2], 1, I2C_RECEIVE_TIMEOUT);
	return buffer[2];
}
