/* ###################################################################
**     Filename    : Events.c
**     Project     : jack-spherobot
**     Processor   : MK64FN1M0VLL12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-05-24, 17:36, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Cpu_OnNMI - void Cpu_OnNMI(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"
#include "Init_Config.h"
#include "PDD_Includes.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */
#include "quad_encoder.h"
#include "pid_control.h"
#include "main.h"

// Quadrature encoder decoding
quad_encoder qeMotor[3] = {0, };


// Controller
unsigned long timerCounterControl;

unsigned int nADCStack[3] = {0, };
//unsigned int nADCStackCount = 0;
unsigned char nSampleSelection = 0;

const float currentFactor = 0.000359677; //  * 3.3 / 0.14 / 65535.0
float fCurrent[3] = {0, };
float fCurrent_now[3] = {0, };
float fCurrent_past[3] = {0, };


/*
** ===================================================================
**     Event       :  Cpu_OnNMI (module Events)
**
**     Component   :  Cpu [MK64FN1M0LL12]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMI(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  EInt_M3B_OnInterrupt (module Events)
**
**     Component   :  EInt_M3B [ExtInt_LDD]
*/
/*!
**     @brief
**         This event is called when an active signal edge/level has
**         occurred.
**     @param
**         UserDataPtr     - Pointer to RTOS device
**                           data structure pointer.
*/
/* ===================================================================*/
void EInt_M3B_OnInterrupt(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
	qeMotor[2].stateB = EInt_M3B_GetVal(UserDataPtr);
	quad_decoding(&qeMotor[2]);
}

/*
** ===================================================================
**     Event       :  EInt_M3A_OnInterrupt (module Events)
**
**     Component   :  EInt_M3A [ExtInt_LDD]
*/
/*!
**     @brief
**         This event is called when an active signal edge/level has
**         occurred.
**     @param
**         UserDataPtr     - Pointer to RTOS device
**                           data structure pointer.
*/
/* ===================================================================*/
void EInt_M3A_OnInterrupt(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
	qeMotor[2].stateA = EInt_M3A_GetVal(UserDataPtr);
	quad_decoding(&qeMotor[2]);
}

/*
** ===================================================================
**     Event       :  EInt_M2B_OnInterrupt (module Events)
**
**     Component   :  EInt_M2B [ExtInt_LDD]
*/
/*!
**     @brief
**         This event is called when an active signal edge/level has
**         occurred.
**     @param
**         UserDataPtr     - Pointer to RTOS device
**                           data structure pointer.
*/
/* ===================================================================*/
void EInt_M2B_OnInterrupt(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
	qeMotor[1].stateB = EInt_M2B_GetVal(UserDataPtr);
	quad_decoding(&qeMotor[1]);
}

/*
** ===================================================================
**     Event       :  EInt_M2A_OnInterrupt (module Events)
**
**     Component   :  EInt_M2A [ExtInt_LDD]
*/
/*!
**     @brief
**         This event is called when an active signal edge/level has
**         occurred.
**     @param
**         UserDataPtr     - Pointer to RTOS device
**                           data structure pointer.
*/
/* ===================================================================*/
void EInt_M2A_OnInterrupt(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
	qeMotor[1].stateA = EInt_M2A_GetVal(UserDataPtr);
	quad_decoding(&qeMotor[1]);
}

/*
** ===================================================================
**     Event       :  EInt_M1B_OnInterrupt (module Events)
**
**     Component   :  EInt_M1B [ExtInt_LDD]
*/
/*!
**     @brief
**         This event is called when an active signal edge/level has
**         occurred.
**     @param
**         UserDataPtr     - Pointer to RTOS device
**                           data structure pointer.
*/
/* ===================================================================*/
void EInt_M1B_OnInterrupt(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
	qeMotor[0].stateB = EInt_M1B_GetVal(UserDataPtr);
	quad_decoding(&qeMotor[0]);
}

/*
** ===================================================================
**     Event       :  EInt_M1A_OnInterrupt (module Events)
**
**     Component   :  EInt_M1A [ExtInt_LDD]
*/
/*!
**     @brief
**         This event is called when an active signal edge/level has
**         occurred.
**     @param
**         UserDataPtr     - Pointer to RTOS device
**                           data structure pointer.
*/
/* ===================================================================*/
void EInt_M1A_OnInterrupt(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
	qeMotor[0].stateA = EInt_M1A_GetVal(UserDataPtr);
	quad_decoding(&qeMotor[0]);
}

/*
** ===================================================================
**     Event       :  AD1_OnMeasurementComplete (module Events)
**
**     Component   :  AD1 [ADC_LDD]
*/
/*!
**     @brief
**         Called after measurement is done, [Interrupt service/event]
**         is enabled, OnMeasurementComplete event is enabled and ADC
**         device is enabled. See [SetEventMask()] method or [Event
**         mask] property group to enable this event and [Enable]
**         method or [Enabled in init. code] property to enable ADC
**         device. If DMA is enabled , this event is called after the
**         configured number of measurements and DMA transfer is done.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer is passed
**                           as the parameter of Init method. 
*/
/* ===================================================================*/
void AD1_OnMeasurementComplete(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
	//byte nIndex = (nADCStackCount & 63) * 3;
	//nADCStack[(nSampleSelection) + nIndex] = ADC_PDD_GetResultValueRaw(ADC1_BASE_PTR, 0U);
	nADCStack[nSampleSelection] = ADC_PDD_GetResultValueRaw(ADC1_BASE_PTR, 0U);

	nSampleSelection++;
    if(nSampleSelection == 3)
    {
    	nSampleSelection = 0;
    	//nADCStackCount++;
    }

	// Resample
	SampleGroup[0].ChannelIdx = nSampleSelection;
	(void)AD1_CreateSampleGroup(AD1_DeviceData, SampleGroup, 1U); /* Configure sample group */
    (void)AD1_StartSingleMeasurement(AD1_DeviceData);

}

/*
** ===================================================================
**     Event       :  TIMotorCtrl_OnInterrupt (module Events)
**
**     Component   :  TIMotorCtrl [TimerInt_LDD]
*/
/*!
**     @brief
**         Called if periodic event occur. Component and OnInterrupt
**         event must be enabled. See [SetEventMask] and [GetEventMask]
**         methods. This event is available only if a [Interrupt
**         service/event] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void TIMotorCtrl_OnInterrupt(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */


	unsigned long currentSum[3] = {0,};
	unsigned int meanCurrent[3] = {0,};
	int i,j;

	timerCounter1ms++;
	timerCounterControl++;


	if(isInitDone)
	{

		CAN_Loop();
		// 1. --- Calculate current
		for(i=0; i<3; i++)
		{
			/*
			for(j=0; j<2; j++) {
				currentSum[i] += nADCStack[i + j*3]; }
			meanCurrent[i] = currentSum[i] >> 2;
			*/
			fCurrent[i] = nADCStack[i] * currentFactor; // / 65535.0 * 3.3 / 0.14;

			if(fCurrent[i] < 0.09) fCurrent[i] = 0.0;
			//fCurrent_now[i] = fCurrent[i] * 0.9 + fCurrent_past[i] * 0.1;
			//fCurrent_past[i] = fCurrent_now[i];
			piCurrentCtrl[i].nowValue = fCurrent[i]; // Update now value
		}
		// nADCStackCount = 0;


		// 2. --- Whole body controller


		// 3. --- Motor Controller
		pi_control_loop(&piCurrentCtrl[0]);
		pi_control_loop(&piCurrentCtrl[1]);
		pi_control_loop(&piCurrentCtrl[2]);


		// 4. --- Write
		Motor1_PWM_SetRatio16((word)(piCurrentCtrl[0].nowOutput / 12.0 * 64224.3));
		Motor2_PWM_SetRatio16((word)(piCurrentCtrl[1].nowOutput / 12.0 * 64224.3));
		Motor3_PWM_SetRatio16((word)(piCurrentCtrl[2].nowOutput / 12.0 * 64224.3));





		if(timerCounterControl >= 10)
		{
			// Reset counter
			timerCounterControl = 0;


		}
	}
}

/*
** ===================================================================
**     Event       :  CAN1_OnFreeTxBuffer (module Events)
**
**     Component   :  CAN1 [CAN_LDD]
*/
/*!
**     @brief
**         This event is called when the buffer is empty after a
**         successful transmit of a message. This event is available
**         only if method SendFrame is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
**     @param
**         BufferIdx       - Receive message buffer index.
*/
/* ===================================================================*/
void CAN1_OnFreeTxBuffer(LDD_TUserData *UserDataPtr, LDD_CAN_TMBIndex BufferIdx)
{
  /* Write your code here ... */
	dataFrameTxFlg = TRUE;
}

/*
** ===================================================================
**     Event       :  CAN1_OnFullRxBuffer (module Events)
**
**     Component   :  CAN1 [CAN_LDD]
*/
/*!
**     @brief
**         This event is called when the buffer is full after a
**         successful receive a message. This event is available only
**         if method ReadFrame or SetRxBufferState is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
**     @param
**         BufferIdx       - Transmit buffer index.
*/
/* ===================================================================*/
void CAN1_OnFullRxBuffer(LDD_TUserData *UserDataPtr, LDD_CAN_TMBIndex BufferIdx)
{
  /* Write your code here ... */
	dataFrameRxFlg=TRUE;
}

/*
** ===================================================================
**     Event       :  ASDXL_OnError (module Events)
**
**     Component   :  ASDXL [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ASDXL_OnError(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  ASDXL_OnRxChar (module Events)
**
**     Component   :  ASDXL [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ASDXL_OnRxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  ASDXL_OnTxChar (module Events)
**
**     Component   :  ASDXL [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ASDXL_OnTxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  ASDXL_OnFullRxBuf (module Events)
**
**     Component   :  ASDXL [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ASDXL_OnFullRxBuf(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  ASDXL_OnFreeTxBuf (module Events)
**
**     Component   :  ASDXL [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ASDXL_OnFreeTxBuf(void)
{
  /* Write your code here ... */
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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
