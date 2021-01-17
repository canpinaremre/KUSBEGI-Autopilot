/*
 * @Author: canpinaremre
 * Purpose: IMU
 * Language:  C
 */

#include "imu.h"


int8_t init_imu(IMU *imu,I2C_HandleTypeDef *huartI2C){
	int8_t rslt;

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

	imu->yaw_dps = 0.0f;

#ifdef Selected_IMU_BNO055

	rslt = BNO055_Init(huartI2C, OPERATION_MODE_NDOF, 10);
	if(rslt != BNO055_OK){
		return rslt;
	}

/* #ifdef Selected_IMU_BNO055 */
#endif

#ifdef Selected_BAR_BMP280

	//init Temp
	temp32 = 0;
	temp = 0;

	//init Barometer
	/* Map the delay function pointer with the function responsible for implementing the delay */
	bmp.delay_ms = delay_ms;

	/* Assign device I2C address based on the status of SDO pin (GND for PRIMARY(0x76) & VDD for SECONDARY(0x77)) */
	bmp.dev_id = BMP280_ADDR_R;

	/* Select the interface mode as I2C */
	bmp.intf = BMP280_I2C_INTF;

	/* Map the I2C read & write function pointer with the functions responsible for I2C bus transfer */
	bmp.read = i2c_reg_read;
	bmp.write = i2c_reg_write;

	rslt = bmp280_init(&bmp, huartI2C);
	if (rslt != BMP280_OK) {
		return rslt;
	}

	rslt = bmp280_get_config(&conf, &bmp, huartI2C);
	if (rslt != BMP280_OK) {
		return rslt;
	}
	conf.filter = BMP280_FILTER_COEFF_2;
	conf.os_temp = BMP280_OS_4X;
	/* Pressure oversampling set at 4x */
	conf.os_pres = BMP280_OS_4X;

	/* Setting the output data rate as 1HZ(1000ms) */
	conf.odr = BMP280_ODR_1000_MS;

	rslt = bmp280_set_config(&conf, &bmp, huartI2C);
	if (rslt != BMP280_OK) {
		return rslt;
	}

	/* Always set the power mode after setting the configuration */
	rslt = bmp280_set_power_mode(BMP280_NORMAL_MODE, &bmp, huartI2C);
	if (rslt != BMP280_OK) {
		return rslt;
	}

/* #ifdef Selected_BAR_BMP280 */
#endif

	return IMU_INIT_OK;
}

int8_t read_imu(IMU *imu,I2C_HandleTypeDef *huartI2C,KUSBEGI_FLAGS *kusbegi_flags){
	int8_t rslt;

#ifdef Selected_IMU_BNO055

	rslt = BNO055_Read_Gyr(huartI2C, imu->gyrXYZ);
	if (rslt != BNO055_OK) {
		kusbegi_flags->FLAG_IMU_GYR_R_OK = 0;
		return rslt;
	}
	kusbegi_flags->FLAG_IMU_GYR_R_OK = 1;

	rslt = BNO055_Read_Acc(huartI2C, imu->accelXYZ);
	if (rslt != BNO055_OK) {
		kusbegi_flags->FLAG_IMU_ACC_R_OK = 0;
		return rslt;
	}
	kusbegi_flags->FLAG_IMU_ACC_R_OK = 1;

	rslt = BNO055_Read_Eul(huartI2C, imu->eulerXYZ);
	if (rslt != BNO055_OK) {
		kusbegi_flags->FLAG_IMU_EUL_R_OK = 0;
		return rslt;
	}
	kusbegi_flags->FLAG_IMU_EUL_R_OK = 1;

	rslt = BNO055_Read_Qua(huartI2C, imu->quaternionWXYZ);
	if (rslt != BNO055_OK) {
		kusbegi_flags->FLAG_IMU_QUA_R_OK = 0;
		return rslt;
	}
	kusbegi_flags->FLAG_IMU_QUA_R_OK = 1;

	rslt = BNO055_Read_Lia(huartI2C, imu->liaXYZ);
	if (rslt != BNO055_OK) {
		kusbegi_flags->FLAG_IMU_LIA_R_OK = 0;
		return rslt;
	}
	kusbegi_flags->FLAG_IMU_LIA_R_OK = 1;

/* #ifdef Selected_IMU_BNO055 */
#endif

//	imu->ypr[0] = imu->eulerXYZ[1];
//	imu->ypr[2] = imu->eulerXYZ[2];
//	imu->ypr[1] = imu->eulerXYZ[0];

	//For Test Drone Confing
	imu->ypr[2] = (-1.0f) * imu->eulerXYZ[1];
	imu->ypr[0] = imu->eulerXYZ[0];
	imu->ypr[1] = (1.0f) * imu->eulerXYZ[2];
	imu->yaw_dps =(-1.0f) * imu->gyrXYZ[2];

	return IMU_READ_OK;
}

int8_t reset_imu(IMU *imu,I2C_HandleTypeDef *huartI2C){
	int8_t rslt;
	rslt = BNO055_E_EMPTY_FUNCTION;
	return rslt;
}

int8_t set_imu(IMU *imu,I2C_HandleTypeDef *huartI2C){
	int8_t rslt;
	rslt = BNO055_E_EMPTY_FUNCTION;
	return rslt;
}


#ifdef Selected_BAR_BMP280

int8_t read_barometer(IMU *imu,I2C_HandleTypeDef *huartI2C){
	int8_t rslt;

	rslt = bmp280_get_uncomp_data(&ucomp_data, &bmp, huartI2C);
	if (rslt != BMP280_OK) {
		return rslt;
	}
	/* Getting the compensated pressure using 32 bit precision */
	rslt = bmp280_get_comp_pres_32bit(&pres32, ucomp_data.uncomp_press, &bmp,
			huartI2C);
	if (rslt != BMP280_OK) {
		return rslt;
	}
	/* Getting the compensated pressure using 64 bit precision */
	rslt = bmp280_get_comp_pres_64bit(&pres64, ucomp_data.uncomp_press, &bmp,
			huartI2C);
	if (rslt != BMP280_OK) {
		return rslt;
	}
	/* Getting the compensated pressure as floating point value */
	rslt = bmp280_get_comp_pres_double(&pres, ucomp_data.uncomp_press, &bmp,
			huartI2C);
	if (rslt != BMP280_OK) {
		return rslt;
	}
	/* Reading the raw data from sensor */
	rslt = bmp280_get_uncomp_data(&ucomp_data, &bmp, huartI2C);
	if (rslt != BMP280_OK) {
		return rslt;
	}
	/* Getting the 32 bit compensated temperature */
	rslt = bmp280_get_comp_temp_32bit(&temp32, ucomp_data.uncomp_temp, &bmp,
			huartI2C);
	if (rslt != BMP280_OK) {
		return rslt;
	}
	/* Getting the compensated temperature as floating point value */
	rslt = bmp280_get_comp_temp_double(&temp, ucomp_data.uncomp_temp, &bmp,
			huartI2C);
	if (rslt != BMP280_OK) {
		return rslt;
	}
	imu->pressure = pres64 / 256;
	imu->temperature = temp;

	return IMU_READ_OK;
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
	int8_t rslt;
//	bmp_i2c_buff[0] = reg_addr;
//	for(uint8_t i=0;i<length;i++){
//		bmp_i2c_buff[i+1] = reg_data[i];
//	}
//
//	HAL_I2C_Master_Transmit(huartI2C, i2c_addr, bmp_i2c_buff, (length + 1), I2C_TRANSMIT_TIMEOUT);
	rslt = write8(huartI2C,0XEC,reg_addr,*reg_data);

    return rslt;
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
	int8_t rslt;
	bmp_i2c_buff[0] = reg_addr;


	rslt = HAL_I2C_Master_Transmit(huartI2C, i2c_addr, bmp_i2c_buff, 1, I2C_TRANSMIT_TIMEOUT);
	if (rslt != HAL_OK) {
		return rslt;
	}
	rslt = HAL_I2C_Master_Receive(huartI2C, i2c_addr, &bmp_i2c_buff[1], length, I2C_RECEIVE_TIMEOUT);
	for (uint8_t i = 0; i < length; i++) {
		reg_data[i] = bmp_i2c_buff[i + 1];
	}

    return rslt;
}



/* #ifdef Selected_BAR_BMP280 */
#endif

