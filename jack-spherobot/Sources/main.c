/* ###################################################################
**     Filename    : main.c
**     Project     : jack-spherobot
**     Processor   : MK64FN1M0VLL12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-05-24, 17:36, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Pins1.h"
#include "TU1.h"
#include "TU2.h"
#include "Motor1_PWM.h"
#include "PwmLdd1.h"
#include "Motor2_PWM.h"
#include "PwmLdd2.h"
#include "Motor3_PWM.h"
#include "PwmLdd3.h"
#include "Motor1_Dir_A.h"
#include "BitIoLdd1.h"
#include "Motor1_Dir_B.h"
#include "BitIoLdd2.h"
#include "CAN1.h"
#include "ASBluetooth.h"
#include "ASerialLdd1.h"
#include "ASDXL.h"
#include "ASerialLdd2.h"
#include "TIMotorCtrl.h"
#include "AD1.h"
#include "EInt_M1A.h"
#include "EInt_M1B.h"
#include "EInt_M2A.h"
#include "EInt_M2B.h"
#include "EInt_M3A.h"
#include "EInt_M3B.h"
#include "Motor2_Dir_A.h"
#include "BitIoLdd3.h"
#include "Motor2_Dir_B.h"
#include "BitIoLdd4.h"
#include "Motor3_Dir_A.h"
#include "BitIoLdd5.h"
#include "Motor3_Dir_B.h"
#include "BitIoLdd6.h"
#include "LED_RED.h"
#include "BitIoLdd7.h"
#include "LED_BLUE.h"
#include "BitIoLdd8.h"
#include "LED_GREEN.h"
#include "BitIoLdd9.h"
#include "USB1.h"
#include "CDC1.h"
#include "Tx1.h"
#include "Rx1.h"
#include "KSDK1.h"
#include "CS1.h"
#include "TMOUT1.h"
#include "WAIT1.h"
#include "CsIO1.h"
#include "IO1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "MW-AHRSv1.h"
#include "pid_control.h"
#include "quad_encoder.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"


////////////////////////////////////////////////////
// Global Variables
MW_AHRS ahrs_obj = {0, };

unsigned long timerCounter1ms = 0;

volatile bool dataFrameTxFlg=FALSE;
volatile bool dataFrameRxFlg=FALSE;

LDD_TDeviceData *CAN1_DeviceData;
LDD_TDeviceData *AD1_DeviceData;
LDD_ADC_TSample SampleGroup[1];

LDD_CAN_TFrame txFrame; // CAN Frame ������ ����ü ����
LDD_CAN_TFrame rxFrame; // CAN Frame ������ ����ü ����


/////////////// PC CMD ////////////////////
enum PCCMDFLAG {READY, START, DONE};

char szPCCmd[30] = {0, };
char nPCCmdLen = 0;
uint8_t nPCCmdFlag = READY;

const double COS30DEG = 0.866025404;
const double INVCOS30DEG = 1.154700538;
const double SIN30DEG = 0.5;
const double INVSIN30DEG = 2.0;
const double SINCOSSUM30 = 3.154700538;

control_input ctrlInput = {0, };

static uint8_t cdc_buffer[USB1_DATA_BUFF_SIZE];
static uint8_t in_buffer[USB1_DATA_BUFF_SIZE];

pi_control piCurrentCtrl[3];
pi_control piVelocityCtrl[3];
uint8_t isInitDone = false;

uint8_t nowDirection[3] = {0, };

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
  int i;
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */

  ADC_Init();
  CAN_Init();
  LED_BLUE_PutVal(0);
  wait_ms(1000);
  LED_BLUE_PutVal(1);
  LED_GREEN_PutVal(0);
  Motor_Init();
  wait_ms(500);
  LED_GREEN_PutVal(1);
  LED_RED_PutVal(0);

  mw_ahrs_set_data_type(&ahrs_obj,1,1,1,0);
  CAN_Write();

  mw_ahrs_set_period(&ahrs_obj,1);
  CAN_Write();

  LED_RED_PutVal(1);
  LED_GREEN_PutVal(0);

  isInitDone = true;
  // First Trigger
  nSampleSelection = 0;
  AD1_StartSingleMeasurement(AD1_DeviceData);


  for(;;)
  {

	 dxl_write(1,ahrs_obj.e_pitch,-15.0,15.0);
	 dxl_write(6,ahrs_obj.e_roll,-15.0,15.0);
	USB_CDC_Loop();	// Joystick, ROS

	//printf("[T: %d] M1: %4d:%04d, M2: %4d:%04d, M3: %4d:%04d \r\n",
	//	  (timerCounter1ms/100), qeMotor[0].value, (int)(fCurrent[0]*1000), qeMotor[1].value, (int)(fCurrent[1]*1000), qeMotor[2].value, (int)(fCurrent[2]*1000));
  }




  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

void CAN_Loop()
{
  if(CAN_Read())	// IMU Update
  {
	 mw_ahrs_input_data(&ahrs_obj);
  }
}
void USB_CDC_Loop()
{

	  if(CDC1_App_Task(cdc_buffer, sizeof(cdc_buffer)) != ERR_BUSOFF)	// Serial Update
	  {
		  while(CDC1_GetCharsInRxBuf()!=0)
		  {
			  char data;
			  CDC1_RecvChar(&szPCCmd[nPCCmdLen]);
			  if( nPCCmdFlag == READY )
			  {
				  if( szPCCmd[0] == '$' )
				  {
					  nPCCmdFlag = START;
				  }
			  }
			  else if ( nPCCmdFlag == START)
			  {
				  if(szPCCmd[nPCCmdLen] == '\n')
				  {
					  double l_x, l_y, r_x;
					  char *pt;
					  szPCCmd[nPCCmdLen+1] = 0;	// NULL Add
					  pt = strtok (szPCCmd,",");
					  ctrlInput.x = atof(pt);
					  pt = strtok (NULL,",");
					  ctrlInput.y = atof(pt);
					  pt = strtok (NULL,",");
					  ctrlInput.theta = atof(pt);

					  if(fabs(ctrlInput.x) < 0.1) ctrlInput.x = 0.0;
					  if(fabs(ctrlInput.y) < 0.1) ctrlInput.y = 0.0;
					  if(fabs(ctrlInput.theta) < 0.1) ctrlInput.theta = 0.0;
					  Omni_Drive(&ctrlInput);
					  // Do Process
					  nPCCmdLen = 0;
					  nPCCmdFlag = READY;
				  } else {
					  nPCCmdLen++;
				  }

			  }
			  // CDC1_SendChar(data);
		  }
	  }
}
void Motor_Drive(int index, double power)
{
	int direction = 0;
	int pwm = 0;

	if(fabs(power) < 0.1) power = 0.0;

	if(power >= 0)
	{
		direction = 1;
		pwm = power * 65535;
	}
	else
	{
		direction = 0;
		pwm = power * -65535;
	}

	switch(index)
	{
	case 0:
		Motor1_Dir_A_PutVal(direction);
		Motor1_Dir_B_PutVal(!direction);
		Motor1_PWM_SetRatio16(pwm);
		break;
	case 1:
		Motor2_Dir_A_PutVal(direction);
		Motor2_Dir_B_PutVal(!direction);
		Motor2_PWM_SetRatio16(pwm);
		break;
	case 2:
		Motor3_Dir_A_PutVal(direction);
		Motor3_Dir_B_PutVal(!direction);
		Motor3_PWM_SetRatio16(pwm);
		break;
	}

}
void Omni_Drive(control_input * input)
{
	Motor_Control(0, input->theta + (input->x * INVSIN30DEG - input->y * INVCOS30DEG) / SINCOSSUM30 * 6.0);
	Motor_Control(1, input->theta + -(input->x) / SINCOSSUM30 * 6.0);
	Motor_Control(2, input->theta + (input->x * INVSIN30DEG + input->y * INVCOS30DEG) / SINCOSSUM30 * 6.0);
			/*
	Motor_Drive(0, -(input->x * INVSIN30DEG + input->y * INVCOS30DEG) / SINCOSSUM30);
	Motor_Drive(1, (input->x) / SINCOSSUM30);
	Motor_Drive(2, (input->x * INVSIN30DEG + input->y * INVCOS30DEG) / SINCOSSUM30);
	*/
}

void Motor_Control(int index, double power)
{

	uint8_t direction = 0;
	if(fabs(power) < 0.01) power = 0.0;

	if(power >= 0)
	{
		direction = 1;
	}
	else
	{
		direction = 0;
	}


	if(fCurrent[index] < 0.200)	// when current is 100mA
	{
		switch(index)
		{
		case 0:
			Motor1_Dir_A_PutVal(direction);
			Motor1_Dir_B_PutVal(!direction);
			nowDirection[index] = direction;
			break;
		case 1:
			Motor2_Dir_A_PutVal(direction);
			Motor2_Dir_B_PutVal(!direction);
			nowDirection[index] = direction;
			break;
		case 2:
			Motor3_Dir_A_PutVal(direction);
			Motor3_Dir_B_PutVal(!direction);
			nowDirection[index] = direction;
			break;
		}
		piCurrentCtrl[index].desiredValue = fabs(power);
	}
	else
	{
		if(direction != nowDirection[index])
			piCurrentCtrl[index].desiredValue = 0.0;
		else
			piCurrentCtrl[index].desiredValue = fabs(power);
	}



}
void Motor_Init()
{
	Motor1_Dir_A_PutVal(1);
	Motor1_Dir_B_PutVal(0);
	Motor2_Dir_A_PutVal(1);
	Motor2_Dir_B_PutVal(0);
	Motor3_Dir_A_PutVal(1);
	Motor3_Dir_B_PutVal(0);
	Motor1_PWM_SetRatio16(0000);
	Motor2_PWM_SetRatio16(0000);
	Motor3_PWM_SetRatio16(0000);
	//								  kP kI kA  low high dt
	pi_control_init(&piCurrentCtrl[0], 62, 628, 1/62.0, 0, 12.0, 0.001);
	pi_control_init(&piCurrentCtrl[1], 62, 628, 1/62.0, 0, 12.0, 0.001);
	pi_control_init(&piCurrentCtrl[2], 62, 628, 1/62.0, 0, 12.0, 0.001);
	pi_control_init(&piVelocityCtrl[0], 1, 0, 0, 0, 12.0, 0.01);
	pi_control_init(&piVelocityCtrl[1], 1, 0, 0, 0, 12.0, 0.01);
	pi_control_init(&piVelocityCtrl[2], 1, 0, 0, 0, 12.0, 0.01);

	piCurrentCtrl[0].errorSumLimit = 1e6;
	piCurrentCtrl[1].errorSumLimit = 1e6;
	piCurrentCtrl[2].errorSumLimit = 1e6;

	piCurrentCtrl[0].desiredValue = 0.000;
	piCurrentCtrl[1].desiredValue = 0.000;
	piCurrentCtrl[2].desiredValue = 0.000;
}

void ADC_Init()
{
	AD1_DeviceData = AD1_Init(NULL);
	AD1_CreateSampleGroup(AD1_DeviceData,SampleGroup,1U);
}

void CAN_Init()
{
	CAN1_DeviceData = CAN1_Init(NULL);
	CAN1_SetRxBufferID(CAN1_DeviceData, 0, 0x001);


	rxFrame.Data = ahrs_obj.can_read_data;

	txFrame.MessageID = 0x001; // �����͸� ���� ���̵� ����
	txFrame.FrameType = LDD_CAN_DATA_FRAME; // Frame ���� ����
	txFrame.Length = 8; // ������ ���� ����
	txFrame.Data = ahrs_obj.can_write_data; // ���� ������ ������ �ּ� ����
}

void wait_ms(unsigned long ms)
{
	timerCounter1ms = 0;
	while(timerCounter1ms < ms) {}
}

byte CAN_Write()
{
	byte err;
	err = CAN1_SendFrame(CAN1_DeviceData, 1, &txFrame);
	if(err != ERR_OK) return err;

	while(!dataFrameTxFlg) {} // �۽� �Ϸ���� ���
	dataFrameTxFlg=FALSE;

	return err;
}

byte CAN_Read()
  {
	int err = CAN1_ReadFrame(CAN1_DeviceData, 0, &rxFrame);
	if(err == ERR_OK || err == ERR_OVERRUN )
	{
	  return 1;
	}
	return 0;
}


void dxl_write(int id, float degree, float min_deg, float max_deg)
{
	byte packet[20], i;
	word sent;

	if(degree < min_deg) degree = min_deg;
	else if(degree > max_deg) degree = max_deg;
	// if(degree > 150.0 || degree < -150.0) return;
	int position = (int)((degree + 150.0) * 3.4133 + 0.5);	// �ݿø�


	packet[0] = 0xFF;
	packet[1] = 0xFF;
	packet[2] = id;
	packet[3] = 5;
	packet[4] = 0x03;
	packet[5] = 0x1E;
	packet[6] = position & 0xFF;
	packet[7] = (position >> 8) & 0xFF;

	packet[8] = 0;

	for(i=2;i<8;i++)
	{
		packet[8] += packet[i];
	}
	packet[8] = ~ packet[8];


	ASDXL_SendBlock(packet,9,&sent);



}

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
