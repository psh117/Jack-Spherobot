/*
 * quad_encoder.c
 *
 *  Created on: May 31, 2016
 *      Author: suhan
 */

#include "quad_encoder.h"

byte QUAD_ENCODER_TABLE[4] = {ENC(0,0), ENC(0,1), ENC(1,1), ENC(1,0)};
byte INV_QUAD_ENCODER_TABLE[4] = {0, 1, 3, 2};


void quad_decoding(quad_encoder *pqeData)
{
	byte bNowState = (pqeData->stateA<<1) + pqeData->stateB;

	if(bNowState == QUAD_ENCODER_TABLE[(pqeData->qetIndex+1) & 0b11]) // forward
	{
		pqeData->value++;
	}
	else if(bNowState == QUAD_ENCODER_TABLE[(pqeData->qetIndex+7) & 0b11])
	{
		pqeData->value--;
	}
	pqeData->qetIndex = INV_QUAD_ENCODER_TABLE[bNowState];

}
