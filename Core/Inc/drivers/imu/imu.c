/*
 * @Author: canpinaremre
 * Purpose: IMU
 * Language:  C
 */

#include "imu.h"


uint8_t init_imu(IMU *imu,I2C_HandleTypeDef *huart){
	imu->eulerXYZ[0] = 0;
	imu->eulerXYZ[1] = 0;
	imu->eulerXYZ[2] = 0;

	imu->quaternionWXYZ[0] = 0;
	imu->quaternionWXYZ[1] = 0;
	imu->quaternionWXYZ[2] = 0;
	imu->quaternionWXYZ[3] = 0;

	imu->accelXYZ[0] = 0;
	imu->accelXYZ[1] = 0;
	imu->accelXYZ[2] = 0;

	imu->magXYZ[0] = 0;
	imu->magXYZ[1] = 0;
	imu->magXYZ[2] = 0;

	imu->liaXYZ[0] = 0;
	imu->liaXYZ[1] = 0;
	imu->liaXYZ[2] = 0;

	imu->grvXYZ[0] = 0;
	imu->grvXYZ[1] = 0;
	imu->grvXYZ[2] = 0;

	imu->gyrXYZ[0] = 0;
	imu->gyrXYZ[1] = 0;
	imu->gyrXYZ[2] = 0;

	imu->ypr[0] = 0;
	imu->ypr[1] = 0;
	imu->ypr[2] = 0;
#ifdef Selected_IMU_BNO055
	return BNO055_Init(huart, OPERATION_MODE_NDOF, 10);
#endif
	return 1;
}

uint8_t read_imu(IMU *imu,I2C_HandleTypeDef *huart){

#ifdef Selected_IMU_BNO055

	BNO055_Read_Acc(huart, imu->accelXYZ);
	BNO055_Read_Eul(huart, imu->eulerXYZ);


#endif


	return 1;
}

uint8_t reset_imu(IMU *imu,I2C_HandleTypeDef *huart){
	return 1;
}

uint8_t set_imu(IMU *imu,I2C_HandleTypeDef *huart){
	return 1;
}


#ifdef Selected_BAR_BMP280

uint8_t read_barometer(IMU *imu,I2C_HandleTypeDef *huartI2C){

	bmp280_rslt = bmp280_get_uncomp_data(&ucomp_data, &bmp,huartI2C);

	/* Getting the compensated pressure using 32 bit precision */
	bmp280_rslt = bmp280_get_comp_pres_32bit(&pres32, ucomp_data.uncomp_press, &bmp,huartI2C);

	/* Getting the compensated pressure using 64 bit precision */
	bmp280_rslt = bmp280_get_comp_pres_64bit(&pres64, ucomp_data.uncomp_press, &bmp,huartI2C);

	/* Getting the compensated pressure as floating point value */
	bmp280_rslt = bmp280_get_comp_pres_double(&pres, ucomp_data.uncomp_press, &bmp,huartI2C);

	/* Reading the raw data from sensor */
	bmp280_rslt = bmp280_get_uncomp_data(&ucomp_data, &bmp,huartI2C);

	/* Getting the 32 bit compensated temperature */
	bmp280_rslt = bmp280_get_comp_temp_32bit(&temp32, ucomp_data.uncomp_temp, &bmp,huartI2C);

	/* Getting the compensated temperature as floating point value */
	bmp280_rslt = bmp280_get_comp_temp_double(&temp, ucomp_data.uncomp_temp, &bmp,huartI2C);

	imu->pressure = pres64 / 256;
	imu->temperature = temp;

	return 1;
}

void delay_ms(uint32_t period_ms)
{
    HAL_Delay(period_ms);
}

/*!
 *  @brief Function for writing the sensor's registers through I2C bus.
 *
 *  @param[in] i2c_addr : sensor I2C address.
 *  @param[in] reg_addr : Register address.
 *  @param[in] reg_data : Pointer to the data buffer whose value is to be written.
 *  @param[in] length   : No of bytes to write.
 *
 *  @return Status of execution
 *  @retval 0 -> Success
 *  @retval >0 -> Failure Info
 *
 */
int8_t i2c_reg_write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length,I2C_HandleTypeDef *huartI2C)
{
//	bmp_i2c_buff[0] = reg_addr;
//	for(uint8_t i=0;i<length;i++){
//		bmp_i2c_buff[i+1] = reg_data[i];
//	}
//
//	HAL_I2C_Master_Transmit(huartI2C, i2c_addr, bmp_i2c_buff, (length + 1), I2C_TRANSMIT_TIMEOUT);
	write8(huartI2C,0XEC,reg_addr,*reg_data);

    return 0;
}

/*!
 *  @brief Function for reading the sensor's registers through I2C bus.
 *
 *  @param[in] i2c_addr : Sensor I2C address.
 *  @param[in] reg_addr : Register address.
 *  @param[out] reg_data    : Pointer to the data buffer to store the read data.
 *  @param[in] length   : No of bytes to read.
 *
 *  @return Status of execution
 *  @retval 0 -> Success
 *  @retval >0 -> Failure Info
 *
 */
int8_t i2c_reg_read(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length,I2C_HandleTypeDef *huartI2C)
{
	bmp_i2c_buff[0] = reg_addr;


	HAL_I2C_Master_Transmit(huartI2C, i2c_addr, bmp_i2c_buff, 1, I2C_TRANSMIT_TIMEOUT);
	HAL_I2C_Master_Receive(huartI2C, i2c_addr, &bmp_i2c_buff[1], length, I2C_RECEIVE_TIMEOUT);
	for (uint8_t i = 0; i < length; i++) {
		reg_data[i] = bmp_i2c_buff[i + 1];
	}
	//*reg_data = read8(huartI2C,0xED,reg_addr);

    return 0;
}



/*!
 *  @brief Prints the execution status of the APIs.
 *
 *  @param[in] api_name : name of the API whose execution status has to be printed.
 *  @param[in] rslt     : error code returned by the API whose execution status has to be printed.
 *
 *  @return void.
 */
void print_rslt(const char api_name[], int8_t rslt,IMU *imu)
{
    if (rslt != BMP280_OK)
    {
    	//TODO: Better error catch
    	imu->temperature = -1.0f;
//        printf("%s\t", api_name);
//        if (rslt == BMP280_E_NULL_PTR)
//        {
//            printf("Error [%d] : Null pointer error\r\n", rslt);
//        }
//        else if (rslt == BMP280_E_COMM_FAIL)
//        {
//            printf("Error [%d] : Bus communication failed\r\n", rslt);
//        }
//        else if (rslt == BMP280_E_IMPLAUS_TEMP)
//        {
//            printf("Error [%d] : Invalid Temperature\r\n", rslt);
//        }
//        else if (rslt == BMP280_E_DEV_NOT_FOUND)
//        {
//            printf("Error [%d] : Device not found\r\n", rslt);
//        }
//        else
//        {
//            /* For more error codes refer "*_defs.h" */
//            printf("Error [%d] : Unknown error code\r\n", rslt);
//        }
    }
}



#endif

