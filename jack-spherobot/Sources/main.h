/*
 * main.h
 *
 *  Created on: Jun 4, 2016
 *      Author: suhan
 */

#ifndef SOURCES_MAIN_H_
#define SOURCES_MAIN_H_

#include "PE_Types.h"


//////////////////////////////////////////////////
// Type

typedef struct
{
	double x;		///< -1.0 ~ 1.0, X Vector Magnitude
	double y;		///< -1.0 ~ 1.0, Y Vector Magnitude
	double theta;	///< -1.0 ~ 1.0, Rotation Magnitude
}control_input;

///////////////////////////////////////////////////
// Functions
void Motor_Init();
void ADC_Init();
void CAN_Init();

byte CAN_Write();
byte CAN_Read();
void wait_ms(unsigned long ms);

void dxl_write(int id, float degree, float min_deg, float max_deg);

void Motor_Drive(int index, double power);
void Motor_Control(int index, double power);
void Omni_Drive(control_input * input);

void USB_CDC_Loop();
void CAN_Loop();


// CAN Comm
extern volatile bool dataFrameTxFlg;
extern volatile bool dataFrameRxFlg;
extern unsigned long timerCounter1ms;

// ADC
extern LDD_TDeviceData *AD1_DeviceData;
extern LDD_ADC_TSample SampleGroup[1];

extern pi_control piCurrentCtrl[3];
extern pi_control piVelocityCtrl[3];

extern quad_encoder qeMotor[3];

extern float fCurrent[3];
extern unsigned char nSampleSelection;

extern uint8_t isInitDone;


#endif /* SOURCES_MAIN_H_ */
