/*
 * @Author: canpinaremre
 * Purpose: RC Mixer
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
	BNO055_Init(huart, OPERATION_MODE_NDOF, 10);
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
