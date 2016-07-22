/*
 * pid_control.c
 *
 *  Created on: 2016. 4. 30.
 *      Author: Suhan Park
 */

#include "pid_control.h"

void pi_control_init(pi_control *dst, float p_gain, float i_gain, float antiwind_gain, float output_low_limit, float output_high_limit, float delta_time)
{
	dst->nowValue = 0;
	dst->nowError = 0;
	dst->nowOutput = 0;

	dst->outputLowLimit = output_low_limit;
	dst->outputHighLimit = output_high_limit;

	dst->desiredValue=0;

	dst->errorSum = 0;

	dst->kP = p_gain;
	dst->kA = antiwind_gain;
	dst->kI = i_gain;

	dst->dt = delta_time;
}

void pi_control_loop(pi_control *dst)
{
	dst->nowError = dst->desiredValue - dst->nowValue;
	dst->errorSum += (dst->nowError * dst->dt);

	dst->nowOutput = dst->kP * dst->nowError + dst->kI * dst->errorSum;

	if		(dst->errorSum >  dst->errorSumLimit) dst->errorSum =  dst->errorSumLimit;
	else if	(dst->errorSum < -dst->errorSumLimit) dst->errorSum = -dst->errorSumLimit;


	if (dst->nowOutput > dst->outputHighLimit)
	{
		dst->errorSum -= (dst->nowOutput - dst->outputHighLimit) * dst->kA * dst->dt;
		dst->nowOutput = dst->outputHighLimit;
	}
	else if ( dst->nowOutput < dst->outputLowLimit )
	{
		dst->errorSum -= (dst->nowOutput + dst->outputLowLimit) * dst->kA * dst->dt;
		dst->nowOutput = dst->outputLowLimit;
	}
}


