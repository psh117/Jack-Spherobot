/*
 * quad_encoder.h
 *
 *  Created on: May 31, 2016
 *      Author: suhan
 */

#ifndef SOURCES_QUAD_ENCODER_H_
#define SOURCES_QUAD_ENCODER_H_

#include "PE_Types.h"

#define ENC(X,Y) (X<<1)+Y

typedef struct
{
	byte stateA;
	byte stateB;
	byte qetIndex; // quadrature encoder table index
	long value;
	long prev_value;
	long delta_value;
}quad_encoder;

void quad_decoding(quad_encoder *pqeData);

#endif /* SOURCES_QUAD_ENCODER_H_ */
