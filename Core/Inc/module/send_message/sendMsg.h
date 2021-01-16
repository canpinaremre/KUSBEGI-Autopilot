/*
 * @Author: canpinaremre
 * Purpose: To send messages via UART
 * Language:  C
 */

#ifndef __SEND_MSG_H__
#define __SEND_MSG_H__


#include "stm32f4xx_hal.h"
#include <string.h>
#include "stdio.h"
#include <lib/parameters/parameters.h>

void sendInt(int32_t myInt,UART_HandleTypeDef* huart,uint8_t newLine);
void sendString(char* myString,UART_HandleTypeDef* huart,uint8_t newLine);
void sendFloat(float myFloat,UART_HandleTypeDef* huart,uint8_t newLine);

/* #ifndef __SEND_MSG_H__ */
#endif
