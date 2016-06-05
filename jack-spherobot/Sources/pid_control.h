/*
 * pid_control.h
 *
 *  Created on: 2016. 4. 30.
 *      Author: bdmm0
 */

#ifndef SOURCES_PID_CONTROL_H_
#define SOURCES_PID_CONTROL_H_

#include <math.h>



typedef struct {

	float nowValue;
	float nowError;
	float nowOutput;

	float outputLowLimit;
	float outputHighLimit;

	float desiredValue;

	float errorSum;
	float errorSumLimit;

	float kP;	// P gain
	float kA;	// Anti wind-up
	float kI;	// I Gain

	float dt;	// delta time

}pi_control;

void pi_control_init(pi_control *dst, float p_gain, float i_gain, float antiwind_gain, float output_low_limit, float output_high_limit, float delta_time);

void pi_control_loop(pi_control *dst);
#endif /* SOURCES_PID_CONTROL_H_ */
