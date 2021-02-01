/*
 * @Author: canpinaremre
 * Purpose: PID
 * Language:  C
 */

#include "PID.h"

void PIDController_Init(PIDController *pid) {

	/* Clear controller variables */
	pid->integrator = 0.0f;
	pid->prevError  = 0.0f;

	pid->differentiator  = 0.0f;
	pid->prevMeasurement = 0.0f;

	pid->out = 0.0f;

	/* In order to avoid divide by zero error*/
	pid->deltaT = 0.01f;

}

float PIDController_Update(PIDController *pid, float setpoint, float measurement,UART_HandleTypeDef* huartMsg) {

	/*
	 * Get time passed
	 */
	pid->deltaT = (float)(HAL_GetTick() - pid->last_pid_time);

	/*
	 * Time should be in second. Should translate from ms to s.
	 */
	pid->deltaT = pid->deltaT / 1000.0f;

	/*
	* Error signal
	*/
    float error = setpoint - measurement;

	/*
	* Proportional
	*/
    float proportional = pid->Kp * error;

	/*
	* Integral
	*/
    pid->integrator = pid->integrator + 0.5f * pid->Ki * pid->deltaT * (error + pid->prevError);

	/* Anti-wind-up via integrator clamping */
    if (pid->integrator > pid->limMaxInt) {

        pid->integrator = pid->limMaxInt;

    } else if (pid->integrator < pid->limMinInt) {

        pid->integrator = pid->limMinInt;

    }

	/*
	* Derivative (band-limited differentiator)
	* To eleminate derivative kick we use change in measurement
	*/
    pid->differentiator = -1.0f * pid->Kd * (measurement - pid->prevMeasurement)/ pid->deltaT;

	/*
	* Compute output and clamp
	*/
    pid->out = proportional + pid->integrator + pid->differentiator;

    if (pid->out > pid->limMax) {

        pid->out = pid->limMax;

    } else if (pid->out < pid->limMin) {

        pid->out = pid->limMin;

    }

	/* Store error and measurement for later use */
    pid->prevError       = error;
    pid->prevMeasurement = measurement;

	/* Return controller output */
    return pid->out;

}
