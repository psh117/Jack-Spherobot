/* ###################################################################
**     Filename    : Events.h
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
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
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

#ifdef __cplusplus
extern "C" {
#endif 

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
void Cpu_OnNMI(void);


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
void EInt_M3B_OnInterrupt(LDD_TUserData *UserDataPtr);

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
void EInt_M3A_OnInterrupt(LDD_TUserData *UserDataPtr);

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
void EInt_M2B_OnInterrupt(LDD_TUserData *UserDataPtr);

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
void EInt_M2A_OnInterrupt(LDD_TUserData *UserDataPtr);

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
void EInt_M1B_OnInterrupt(LDD_TUserData *UserDataPtr);

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
void EInt_M1A_OnInterrupt(LDD_TUserData *UserDataPtr);

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
void AD1_OnMeasurementComplete(LDD_TUserData *UserDataPtr);

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
void TIMotorCtrl_OnInterrupt(LDD_TUserData *UserDataPtr);

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
void CAN1_OnFreeTxBuffer(LDD_TUserData *UserDataPtr, LDD_CAN_TMBIndex BufferIdx);

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
void CAN1_OnFullRxBuffer(LDD_TUserData *UserDataPtr, LDD_CAN_TMBIndex BufferIdx);

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
void ASDXL_OnError(void);

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
void ASDXL_OnRxChar(void);

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
void ASDXL_OnTxChar(void);

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
void ASDXL_OnFullRxBuf(void);

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
void ASDXL_OnFreeTxBuf(void);

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
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
