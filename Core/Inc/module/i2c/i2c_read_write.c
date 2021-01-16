/*
 * @Author: canpinaremre
 * Purpose: To read and write 8bits on I2C by using HAL Library
 * Language:  C
 */


#include <module/i2c/i2c_read_write.h>




int8_t write8(I2C_HandleTypeDef *huart,uint8_t device,uint8_t reg,uint8_t val){
	int8_t rslt;
	buffer_i2c[0] = reg;
	buffer_i2c[1] = val;
	rslt = HAL_I2C_Master_Transmit(huart, device, buffer_i2c, 2, I2C_TRANSMIT_TIMEOUT);

	return rslt;
}

int8_t read8(I2C_HandleTypeDef *huart,uint8_t device,uint8_t reg,uint8_t *val){
	int8_t rslt;
	int8_t cnt = 3;
	buffer_i2c[0] = reg;

	while(cnt){
		rslt = HAL_I2C_Master_Transmit(huart, device, buffer_i2c, 1, I2C_TRANSMIT_TIMEOUT);
		if(rslt == HAL_OK){
			rslt = HAL_I2C_Master_Receive(huart, device, &buffer_i2c[1], 1, I2C_RECEIVE_TIMEOUT);
			if(rslt == HAL_OK){
				break;
			}
			else{
				I2C1_ClearBusyFlagErratum(huart);
			}
		}
		else{
			I2C1_ClearBusyFlagErratum(huart);
		}
		cnt--;

	}


	*val = buffer_i2c[1];
	return rslt;
}

void I2C1_ClearBusyFlagErratum(I2C_HandleTypeDef *instance)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    int timeout =100;
    int timeout_cnt=0;
//    GPIOB = GPIOB;
//    GPIOB = GPIOB;
    uint32_t I2C1_SCL_PIN = GPIO_PIN_6;
    uint32_t I2C1_SDA_PIN = GPIO_PIN_7;
    // 1. Clear PE bit.
    instance->Instance->CR1 &= ~(0x0001);

    //  2. Configure the SCL and SDA I/Os as General Purpose Output Open-Drain, High level (Write 1 to GPIOx_ODR).
    GPIO_InitStruct.Mode         = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Alternate    = GPIO_AF4_I2C1;
    GPIO_InitStruct.Pull         = GPIO_PULLUP;
    GPIO_InitStruct.Speed        = GPIO_SPEED_FREQ_HIGH;

    GPIO_InitStruct.Pin          = I2C1_SCL_PIN;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOB, I2C1_SCL_PIN, GPIO_PIN_SET);

    GPIO_InitStruct.Pin          = I2C1_SDA_PIN;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOB, I2C1_SDA_PIN, GPIO_PIN_SET);


    // 3. Check SCL and SDA High level in GPIOx_IDR.
    while (GPIO_PIN_SET != HAL_GPIO_ReadPin(GPIOB, I2C1_SCL_PIN))
    {
        timeout_cnt++;
        if(timeout_cnt>timeout)
            return;
    }

    while (GPIO_PIN_SET != HAL_GPIO_ReadPin(GPIOB, I2C1_SDA_PIN))
    {
        //Move clock to release I2C
        HAL_GPIO_WritePin(GPIOB, I2C1_SCL_PIN, GPIO_PIN_RESET);
        asm("nop");
        HAL_GPIO_WritePin(GPIOB, I2C1_SCL_PIN, GPIO_PIN_SET);

        timeout_cnt++;
        if(timeout_cnt>timeout)
            return;
    }

    // 4. Configure the SDA I/O as General Purpose Output Open-Drain, Low level (Write 0 to GPIOx_ODR).
    HAL_GPIO_WritePin(GPIOB, I2C1_SDA_PIN, GPIO_PIN_RESET);

    //  5. Check SDA Low level in GPIOx_IDR.
    while (GPIO_PIN_RESET != HAL_GPIO_ReadPin(GPIOB, I2C1_SDA_PIN))
    {
        timeout_cnt++;
        if(timeout_cnt>timeout)
            return;
    }

    // 6. Configure the SCL I/O as General Purpose Output Open-Drain, Low level (Write 0 to GPIOx_ODR).
    HAL_GPIO_WritePin(GPIOB, I2C1_SCL_PIN, GPIO_PIN_RESET);

    //  7. Check SCL Low level in GPIOx_IDR.
    while (GPIO_PIN_RESET != HAL_GPIO_ReadPin(GPIOB, I2C1_SCL_PIN))
    {
        timeout_cnt++;
        if(timeout_cnt>timeout)
            return;
    }

    // 8. Configure the SCL I/O as General Purpose Output Open-Drain, High level (Write 1 to GPIOx_ODR).
    HAL_GPIO_WritePin(GPIOB, I2C1_SCL_PIN, GPIO_PIN_SET);

    // 9. Check SCL High level in GPIOx_IDR.
    while (GPIO_PIN_SET != HAL_GPIO_ReadPin(GPIOB, I2C1_SCL_PIN))
    {
        timeout_cnt++;
        if(timeout_cnt>timeout)
            return;
    }

    // 10. Configure the SDA I/O as General Purpose Output Open-Drain , High level (Write 1 to GPIOx_ODR).
    HAL_GPIO_WritePin(GPIOB, I2C1_SDA_PIN, GPIO_PIN_SET);

    // 11. Check SDA High level in GPIOx_IDR.
    while (GPIO_PIN_SET != HAL_GPIO_ReadPin(GPIOB, I2C1_SDA_PIN))
    {
        timeout_cnt++;
        if(timeout_cnt>timeout)
            return;
    }

    // 12. Configure the SCL and SDA I/Os as Alternate function Open-Drain.
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;

    GPIO_InitStruct.Pin = I2C1_SCL_PIN;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = I2C1_SDA_PIN;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOB, I2C1_SCL_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, I2C1_SDA_PIN, GPIO_PIN_SET);

    // 13. Set SWRST bit in I2Cx_CR1 register.
    instance->Instance->CR1 |= 0x8000;

    asm("nop");

    // 14. Clear SWRST bit in I2Cx_CR1 register.
    instance->Instance->CR1 &= ~0x8000;

    asm("nop");

    // 15. Enable the I2C peripheral by setting the PE bit in I2Cx_CR1 register
    instance->Instance->CR1 |= 0x0001;

    // Call initialization function.
    HAL_I2C_Init(instance);
}

//uint32_t read24(I2C_HandleTypeDef *huart,uint8_t device,uint8_t reg){
//	buffer_i2c[0] = reg;
//	HAL_I2C_Master_Transmit(huart, device, buffer_i2c, 1, I2C_TRANSMIT_TIMEOUT);
//	HAL_I2C_Master_Receive(huart, device, &buffer_i2c[1], 3, I2C_RECEIVE_TIMEOUT);
//
//	return (buffer_i2c[3]) | ((buffer_i2c[2]) << 8) | ((buffer_i2c[1]) << 16);
//}
