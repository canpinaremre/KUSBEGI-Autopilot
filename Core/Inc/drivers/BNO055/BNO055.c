/*
 * @Author: canpinaremre
 * Purpose: To use BNO055 IMU
 * Language:  C
 */


#include <drivers/BNO055/BNO055.h>

void reset_Buffer(void){
	buffer[0] = 0;
	buffer[1] = 0;
	buffer[2] = 0;
	buffer[3] = 0;
	buffer[4] = 0;
	buffer[5] = 0;
	buffer[6] = 0;
	buffer[7] = 0;
	buffer[8] = 0;
}

int8_t BNO055_Chip_ID_Check(I2C_HandleTypeDef *huart) {
	uint8_t chip_id;
	int8_t rslt;
	reset_Buffer();
	rslt = read8(huart, BNO055_READ_ADDR, BNO055_CHIP_ID_ADDR, &chip_id);
	if (rslt == HAL_OK) {
		if (chip_id == BNO055_ID) {
			return BNO055_OK;
		} else
			return BNO055_E_DEV_NOT_FOUND;
	} else{
		return rslt;
	}


}

int8_t BNO055_Init(I2C_HandleTypeDef *huart, bno055_opmode_t mode,uint8_t delay_time) {
	int8_t rslt;
	rslt = BNO055_Chip_ID_Check(huart);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	//TODO: Add counter to count try. and try 5 times
	rslt = BNO055_SetMode(huart, mode);
	HAL_Delay(delay_time);
	return rslt;
}

int8_t BNO055_Get_Page(I2C_HandleTypeDef *huart,uint8_t *page_num_ptr) {
	int8_t rslt;
	uint8_t page_num;
	rslt = BNO055_Chip_ID_Check(huart);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	rslt = read8(huart,BNO055_READ_ADDR,BNO055_PAGE_ADDR,&page_num);

	if(rslt == HAL_OK){
		*page_num_ptr = page_num;
		return BNO055_OK;
	}

	return rslt;
}

int8_t BNO055_Set_Page(I2C_HandleTypeDef *huart,uint8_t page) {
	int8_t rslt;
	rslt = BNO055_Chip_ID_Check(huart);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	rslt = write8(huart,BNO055_READ_ADDR,BNO055_PAGE_ADDR,page);
	if(rslt == HAL_OK){
		return BNO055_OK;
	}
	return rslt;
}

//Reading Raw Data from BNO055
int8_t BNO055_Read_Eul(I2C_HandleTypeDef *huart,float *eulerXYZ) {
	int8_t rslt;
	uint8_t temp;
	rslt = BNO055_Chip_ID_Check(huart);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_EUL_DATA_x_LSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[1] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_EUL_DATA_x_MSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[2] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_EUL_DATA_y_LSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[3] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_EUL_DATA_y_MSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[4] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_EUL_DATA_z_LSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[5] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_EUL_DATA_z_MSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[6] = temp;

	data_read[0] = (buffer[1]) | ((buffer[2]) << 8);
	data_read[1] = (buffer[3]) | ((buffer[4]) << 8);
	data_read[2] = (buffer[5]) | ((buffer[6]) << 8);

	eulerXYZ[0] = ((float) data_read[0]) / 16.0;
	eulerXYZ[1] = (float) data_read[1] / 16.0;
	eulerXYZ[2] = (float) data_read[2] / 16.0;

	return BNO055_OK;
}

int8_t BNO055_Read_Qua(I2C_HandleTypeDef *huart,float *quaternionWXYZ) {
	int8_t rslt;
	uint8_t temp;
	rslt = BNO055_Chip_ID_Check(huart);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_QUATERNION_DATA_W_LSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[1] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_QUATERNION_DATA_W_MSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[2] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_QUATERNION_DATA_X_LSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[3] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_QUATERNION_DATA_X_MSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[4] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_QUATERNION_DATA_Y_LSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[5] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_QUATERNION_DATA_Y_MSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[6] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_QUATERNION_DATA_Z_LSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[7] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_QUATERNION_DATA_Z_MSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[8] = temp;

	//TODO: Check NDOF OR Other modes if they supports Quaternion

	data_read[0] = (buffer[1]) | ((buffer[2]) << 8);
	data_read[1] = (buffer[3]) | ((buffer[4]) << 8);
	data_read[2] = (buffer[5]) | ((buffer[6]) << 8);
	data_read[3] = (buffer[7]) | ((buffer[8]) << 8);

	quaternionWXYZ[0] = (float) data_read[0] / 16383.0;
	quaternionWXYZ[1] = (float) data_read[1] / 16383.0;
	quaternionWXYZ[2] = (float) data_read[2] / 16383.0;
	quaternionWXYZ[3] = (float) data_read[3] / 16383.0;

	return BNO055_OK;
}

int8_t BNO055_Read_Acc(I2C_HandleTypeDef *huart,float *accelXYZ) {
	int8_t rslt;
	uint8_t temp;
	rslt = BNO055_Chip_ID_Check(huart);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_ACCEL_DATA_X_LSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[1] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_ACCEL_DATA_X_MSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[2] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_ACCEL_DATA_Y_LSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[3] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_ACCEL_DATA_Y_MSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[4] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_ACCEL_DATA_Z_LSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[5] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_ACCEL_DATA_Z_MSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[6] = temp;

	//TODO: Sometimes goes 0 0 0 and errors when reading chip ID

	data_read[0] = (buffer[1]) | ((buffer[2]) << 8);
	data_read[1] = (buffer[3]) | ((buffer[4]) << 8);
	data_read[2] = (buffer[5]) | ((buffer[6]) << 8);
	accelXYZ[0] = ((float) data_read[0]) / 100.0;
	accelXYZ[1] = (float) data_read[1] / 100.0;
	accelXYZ[2] = (float) data_read[2] / 100.0;

	return BNO055_OK;
}
int8_t BNO055_Read_Mag(I2C_HandleTypeDef *huart,float *magXYZ) {
	int8_t rslt;
	uint8_t temp;
	rslt = BNO055_Chip_ID_Check(huart);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_MAG_DATA_X_LSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[1] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_MAG_DATA_X_MSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[2] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_MAG_DATA_Y_LSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[3] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_MAG_DATA_Y_MSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[4] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_MAG_DATA_Z_LSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[5] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_MAG_DATA_Z_MSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[6] = temp;

	data_read[0] = (buffer[1]) | ((buffer[2]) << 8);
	data_read[1] = (buffer[3]) | ((buffer[4]) << 8);
	data_read[2] = (buffer[5]) | ((buffer[6]) << 8);
	magXYZ[0] = ((float) data_read[0]) / 100.0;
	magXYZ[1] = (float) data_read[1] / 100.0;
	magXYZ[2] = (float) data_read[2] / 100.0;

	return BNO055_OK;
}
int8_t BNO055_Read_Gyr(I2C_HandleTypeDef *huart,float *gyrXYZ) {
	int8_t rslt;
	uint8_t temp;
	rslt = BNO055_Chip_ID_Check(huart);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_GYRO_DATA_X_LSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[1] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_GYRO_DATA_X_MSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[2] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_GYRO_DATA_Y_LSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[3] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_GYRO_DATA_Y_MSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[4] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_GYRO_DATA_Z_LSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[5] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_GYRO_DATA_Z_MSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[6] = temp;

	data_read[0] = (buffer[1]) | ((buffer[2]) << 8);
	data_read[1] = (buffer[3]) | ((buffer[4]) << 8);
	data_read[2] = (buffer[5]) | ((buffer[6]) << 8);
	gyrXYZ[0] = ((float) data_read[0]) / 100.0;
	gyrXYZ[1] = (float) data_read[1] / 100.0;
	gyrXYZ[2] = (float) data_read[2] / 100.0;

	return BNO055_OK;
}
int8_t BNO055_Read_Grv(I2C_HandleTypeDef *huart,float *grvXYZ) {
	int8_t rslt;
	uint8_t temp;
	rslt = BNO055_Chip_ID_Check(huart);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_GRAVITY_DATA_X_LSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[1] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_GRAVITY_DATA_X_MSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[2] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_GRAVITY_DATA_Y_LSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[3] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_GRAVITY_DATA_Y_MSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[4] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_GRAVITY_DATA_Z_LSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[5] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_GRAVITY_DATA_Z_MSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[6] = temp;

	data_read[0] = (buffer[1]) | ((buffer[2]) << 8);
	data_read[1] = (buffer[3]) | ((buffer[4]) << 8);
	data_read[2] = (buffer[5]) | ((buffer[6]) << 8);
	grvXYZ[0] = ((float) data_read[0]) / 100.0;
	grvXYZ[1] = (float) data_read[1] / 100.0;
	grvXYZ[2] = (float) data_read[2] / 100.0;

	return BNO055_OK;
}
int8_t BNO055_Read_Lia(I2C_HandleTypeDef *huart,float *liaXYZ) {
	int8_t rslt;
	uint8_t temp;
	rslt = BNO055_Chip_ID_Check(huart);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_LINEAR_ACCEL_DATA_X_LSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[1] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_LINEAR_ACCEL_DATA_X_MSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[2] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_LINEAR_ACCEL_DATA_Y_LSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[3] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_LINEAR_ACCEL_DATA_Y_MSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[4] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_LINEAR_ACCEL_DATA_Z_LSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[5] = temp;

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_LINEAR_ACCEL_DATA_Z_MSB_ADDR, &temp);
	if (rslt != HAL_OK)
		return rslt;
	buffer[6] = temp;

	data_read[0] = (buffer[1]) | ((buffer[2]) << 8);
	data_read[1] = (buffer[3]) | ((buffer[4]) << 8);
	data_read[2] = (buffer[5]) | ((buffer[6]) << 8);
	liaXYZ[0] = ((float) data_read[0]) / 100.0;
	liaXYZ[1] = (float) data_read[1] / 100.0;
	liaXYZ[2] = (float) data_read[2] / 100.0;

	return BNO055_OK;
}

//Sets parameters for measurements
int8_t BNO055_Set_Eul(I2C_HandleTypeDef *huart) {
	int8_t rslt;
	rslt = BNO055_Chip_ID_Check(huart);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	return BNO055_E_EMPTY_FUNCTION;
}

int8_t BNO055_Set_Qua(I2C_HandleTypeDef *huart) {
	int8_t rslt;
	rslt = BNO055_Chip_ID_Check(huart);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	return BNO055_E_EMPTY_FUNCTION;
}

int8_t BNO055_Set_Acc(I2C_HandleTypeDef *huart) {
	int8_t rslt;
	rslt = BNO055_Chip_ID_Check(huart);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	return BNO055_E_EMPTY_FUNCTION;
}

int8_t BNO055_Set_Mag(I2C_HandleTypeDef *huart) {
	int8_t rslt;
	rslt = BNO055_Chip_ID_Check(huart);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	return BNO055_E_EMPTY_FUNCTION;
}

int8_t BNO055_Set_Gyr(I2C_HandleTypeDef *huart) {
	int8_t rslt;
	rslt = BNO055_Chip_ID_Check(huart);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	return BNO055_E_EMPTY_FUNCTION;
}

int8_t BNO055_Set_Grv(I2C_HandleTypeDef *huart) {
	int8_t rslt;
	rslt = BNO055_Chip_ID_Check(huart);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	return BNO055_E_EMPTY_FUNCTION;
}

int8_t BNO055_Set_Lia(I2C_HandleTypeDef *huart) {
	int8_t rslt;
	rslt = BNO055_Chip_ID_Check(huart);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	return BNO055_E_EMPTY_FUNCTION;
}

int8_t BNO055_SetMode(I2C_HandleTypeDef *huart,bno055_opmode_t mode){
	int8_t rslt;
	rslt = BNO055_Chip_ID_Check(huart);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	rslt = write8(huart, BNO055_WRITE_ADDR, BNO055_OPR_MODE_ADDR, mode);
	HAL_Delay(20);
	if(rslt == HAL_OK)
		return BNO055_OK;
	else
		return BNO055_E_SET_MODE_FAIL;
}

int8_t BNO055_GetMode(I2C_HandleTypeDef *huart, bno055_opmode_t *mode) {
	int8_t rslt;
	bno055_opmode_t temp;
	rslt = BNO055_Chip_ID_Check(huart);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_OPR_MODE_ADDR, &temp);
	if (rslt == HAL_OK) {
		*mode = temp;
		if ((temp < OPERATION_MODE_CONFIG) || (temp > OPERATION_MODE_NDOF)) {
			return BNO055_E_GET_MODE_OFF_RANGE;
		}
		return BNO055_OK;
	} else
		return rslt;
}

int8_t BNO055_SetAxisRemap(I2C_HandleTypeDef *huart,
		bno055_axis_remap_config_t remapcode) {
	int8_t rslt;
	bno055_opmode_t modeback;
	rslt = BNO055_Chip_ID_Check(huart);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	rslt = BNO055_GetMode(huart, &modeback);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	rslt = BNO055_SetMode(huart, OPERATION_MODE_CONFIG);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	HAL_Delay(25);

	rslt = write8(huart, BNO055_WRITE_ADDR, BNO055_AXIS_MAP_CONFIG_ADDR,
			remapcode);
	if (rslt != HAL_OK) {
		return rslt;
	}

	HAL_Delay(15);

	rslt = BNO055_SetMode(huart, modeback);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	HAL_Delay(20);

	return BNO055_OK;
}

int8_t BNO055_SetAxisSign(I2C_HandleTypeDef *huart,
		bno055_axis_remap_sign_t remapsign) {
	int8_t rslt;
	bno055_opmode_t modeback;
	rslt = BNO055_Chip_ID_Check(huart);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	rslt = BNO055_GetMode(huart, &modeback);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	rslt = BNO055_SetMode(huart, OPERATION_MODE_CONFIG);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	HAL_Delay(25);

	rslt = write8(huart, BNO055_WRITE_ADDR, BNO055_AXIS_MAP_SIGN_ADDR,
			remapsign);
	if (rslt != HAL_OK) {
		return rslt;
	}

	HAL_Delay(10);

	rslt = BNO055_SetMode(huart, modeback);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	HAL_Delay(20);
	return BNO055_OK;
}

int8_t BNO055_GetTemp(I2C_HandleTypeDef *huart, double *temp_ptr) {
	int8_t rslt;
	uint8_t temp;
	rslt = BNO055_Chip_ID_Check(huart);
	if (rslt != BNO055_OK) {
		return rslt;
	}

	rslt = read8(huart, BNO055_READ_ADDR, BNO055_TEMP_ADDR, &temp);
	if (rslt != HAL_OK) {
		return rslt;
	}

	//TODO: Better temperature conversion
	*temp_ptr = (double) temp;

	return BNO055_OK;
}

