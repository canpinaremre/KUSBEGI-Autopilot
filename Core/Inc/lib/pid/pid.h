/*
 * @Author: canpinaremre
 * Purpose: PID
 * Language:  C
 */

#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H
#include <lib/parameters/parameters.h>
#include <module/send_message/sendMsg.h>

typedef struct {

	/*Time passed since last PID */
	uint32_t last_pid_time;

	/* Controller gains */
	float Kp;
	float Ki;
	float Kd;

	/* Output limits */
	float limMin;
	float limMax;

	/* Integrator limits */
	float limMinInt;
	float limMaxInt;

	/* Sample time (in seconds) */
	float deltaT;

	/* Controller "memory" */
	float integrator;
	float prevError;			/* Required for integrator */
	float differentiator;
	float prevMeasurement;		/* Required for differentiator */

	/* Controller output */
	float out;

} PIDController;


void  PIDController_Init(PIDController *pid);
float PIDController_Update(PIDController *pid, float setpoint, float measurement,UART_HandleTypeDef* huartMsg);

/* #ifndef PID_CONTROLLER_H */
#endif
