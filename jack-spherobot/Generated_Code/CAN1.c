/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : CAN1.c
**     Project     : jack-spherobot
**     Processor   : MK64FN1M0VLL12
**     Component   : CAN_LDD
**     Version     : Component 01.112, Driver 01.07, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-06-01, 23:40, # CodeGen: 25
**     Abstract    :
**         This component "CAN_LDD" implements a CAN serial channel.
**     Settings    :
**          Component name                                 : CAN1
**          CAN channel                                    : CAN0
**          Interrupt service                              : Enabled
**            Interrupt error                              : INT_CAN0_Error
**            Interrupt error priority                     : medium priority
**            Interrupt bus off                            : INT_CAN0_Bus_Off
**            Interrupt bus off priority                   : medium priority
**            Interrupt message buffers                    : INT_CAN0_ORed_Message_buffer
**            Interrupt message buffers priority           : high priority
**            Interrupt Tx warning                         : INT_CAN0_Tx_Warning
**            Interrupt Tx warning priority                : medium priority
**            Interrupt Rx warning                         : INT_CAN0_Rx_Warning
**            Interrupt Rx warning priority                : medium priority
**            Interrupt wake up                            : INT_CAN0_Wake_Up
**            Interrupt wake up priority                   : medium priority
**          Settings                                       : 
**            Pins                                         : 
**              Rx pin                                     : 
**                Rx pin                                   : J1_3
**              Tx pin                                     : 
**                Tx pin                                   : J1_1
**            Global acceptance mask                       : yes
**              Acceptance mask for buffer 0 .. n          : 0x1FFFFFFF
**              Acceptance mask for buffer 14              : 0x1FFFFFFF
**              Acceptance mask for buffer 15              : 0x1FFFFFFF
**            Receiver FIFO                                : Disabled
**            Message buffers                              : 2
**              Buffer0                                    : 
**                Buffer type                              : Receive
**                  Accept frames                          : Standard
**                  Message ID                             : 0x7FF
**                  Invidual Acceptance Mask               : Disabled
**              Buffer1                                    : 
**                Buffer type                              : Transmit
**            Abort transmission mode                      : no
**            Remote request storing                       : Remote Request Frame is stored
**            Entire frame arbitration field comparison    : no
**            Local priority                               : no
**            Self reception                               : Disabled
**            Timer synchronization                        : Disabled
**            Lowest buffer transmitted first              : Lowest ID
**            Loop mode                                    : no
**            Bus off recovery mode                        : Automatic
**            Listen only mode                             : no
**            Wake up                                      : Disabled
**          Timing                                         : 
**            CAN timing calculator                        : click to run ->
**            Propagation segment                          : 1
**            Time segment 1                               : 5
**            Time segment 2                               : 3
**            Resync jump width                            : 1
**            Time quanta per bit                          : 10
**            Samples per bit                              : One sample
**            Bit rate                                     : 1000 kbit/s
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Auto initialization                          : no
**            Event mask                                   : 
**              OnFreeTxBuffer                             : Enabled
**              OnFullRxBuffer                             : Enabled
**              OnTransmitWarning                          : Disabled
**              OnReceiveWarning                           : Disabled
**              OnBusOff                                   : Disabled
**              OnWakeUp                                   : Disabled
**              OnError                                    : Disabled
**          CPU clock/configuration selection              : 
**            Clock configuration 0                        : This component enabled
**            Clock configuration 1                        : This component disabled
**            Clock configuration 2                        : This component disabled
**            Clock configuration 3                        : This component disabled
**            Clock configuration 4                        : This component disabled
**            Clock configuration 5                        : This component disabled
**            Clock configuration 6                        : This component disabled
**            Clock configuration 7                        : This component disabled
**     Contents    :
**         Init          - LDD_TDeviceData* CAN1_Init(LDD_TUserData *UserDataPtr);
**         SetRxBufferID - LDD_TError CAN1_SetRxBufferID(LDD_TDeviceData *DeviceDataPtr,...
**         SendFrame     - LDD_TError CAN1_SendFrame(LDD_TDeviceData *DeviceDataPtr, LDD_CAN_TMBIndex...
**         ReadFrame     - LDD_TError CAN1_ReadFrame(LDD_TDeviceData *DeviceDataPtr, LDD_CAN_TMBIndex...
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file CAN1.c
** @version 01.07
** @brief
**         This component "CAN_LDD" implements a CAN serial channel.
*/         
/*!
**  @addtogroup CAN1_module CAN1 module documentation
**  @{
*/         

/* MODULE CAN1. */

/* {Default RTOS Adapter} No RTOS includes */
#include "CAN1.h"
#include "IO_Map.h"
#include "Events.h"
#include "CAN_PDD.h"
#include "PORT_PDD.h"

/* {Default RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static CAN1_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;
/* {Default RTOS Adapter} Global variable used for passing a parameter into ISR */
static CAN1_TDeviceDataPtr INT_CAN0_Error__DEFAULT_RTOS_ISRPARAM;
/* {Default RTOS Adapter} Global variable used for passing a parameter into ISR */
static CAN1_TDeviceDataPtr INT_CAN0_Bus_Off__DEFAULT_RTOS_ISRPARAM;
/* {Default RTOS Adapter} Global variable used for passing a parameter into ISR */
static CAN1_TDeviceDataPtr INT_CAN0_ORed_Message_buffer__DEFAULT_RTOS_ISRPARAM;
/* {Default RTOS Adapter} Global variable used for passing a parameter into ISR */
static CAN1_TDeviceDataPtr INT_CAN0_Tx_Warning__DEFAULT_RTOS_ISRPARAM;
/* {Default RTOS Adapter} Global variable used for passing a parameter into ISR */
static CAN1_TDeviceDataPtr INT_CAN0_Rx_Warning__DEFAULT_RTOS_ISRPARAM;
/* {Default RTOS Adapter} Global variable used for passing a parameter into ISR */
static CAN1_TDeviceDataPtr INT_CAN0_Wake_Up__DEFAULT_RTOS_ISRPARAM;

#define AVAILABLE_EVENTS_MASK (LDD_CAN_ON_FULL_RXBUFFER | LDD_CAN_ON_FREE_TXBUFFER)
#define CAN1_CAN_MBUFFERS 0x02U        /* Number of message buffers */



/*
** ===================================================================
**     Method      :  CAN1_Init (component CAN_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc. If the "Enable
**         in init. code" is set to "yes" value then the device is also
**         enabled(see the description of the Enable() method). In this
**         case the Enable() method is not necessary and needn't to be
**         generated.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* CAN1_Init(LDD_TUserData *UserDataPtr)
{
  /* Allocate LDD device structure */
  CAN1_TDeviceDataPtr DeviceDataPrv;
  /* {Default RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;

  DeviceDataPrv->BaseAddr = CAN0_BASE_PTR; /* Device base address*/
  DeviceDataPrv->UserData = UserDataPtr; /* Store the RTOS device structure */
  DeviceDataPrv->MaxDataLen = 0x08U;   /* Max number of data to be sent in one frame */
  DeviceDataPrv->MaxBufferIndex = (LDD_CAN_TMBIndex)(CAN1_CAN_MBUFFERS-1U); /* Number of max. message buffer index */
  DeviceDataPrv->BuffersNumber = (LDD_CAN_TMBIndex)CAN1_CAN_MBUFFERS; /* Number of message buffers */
  DeviceDataPrv->RxBufferMask = 0x01U; /* Bit mask for message buffers configured as receive */
  DeviceDataPrv->TxBufferMask = 0x02U; /* Bit mask for message buffers configured as transmit */
  /*Clock Gating initialization*/
  /* SIM_SCGC6: FLEXCAN0=1 */
  SIM_SCGC6 |= SIM_SCGC6_FLEXCAN0_MASK;
  /* Allocate interrupt vectors */
  /* {Default RTOS Adapter} Set interrupt vector: IVT is static, ISR parameter is passed by the global variable */
  INT_CAN0_Error__DEFAULT_RTOS_ISRPARAM = DeviceDataPrv;
  /* {Default RTOS Adapter} Set interrupt vector: IVT is static, ISR parameter is passed by the global variable */
  INT_CAN0_Bus_Off__DEFAULT_RTOS_ISRPARAM = DeviceDataPrv;
  /* {Default RTOS Adapter} Set interrupt vector: IVT is static, ISR parameter is passed by the global variable */
  INT_CAN0_ORed_Message_buffer__DEFAULT_RTOS_ISRPARAM = DeviceDataPrv;
  /* {Default RTOS Adapter} Set interrupt vector: IVT is static, ISR parameter is passed by the global variable */
  INT_CAN0_Tx_Warning__DEFAULT_RTOS_ISRPARAM = DeviceDataPrv;
  /* {Default RTOS Adapter} Set interrupt vector: IVT is static, ISR parameter is passed by the global variable */
  INT_CAN0_Rx_Warning__DEFAULT_RTOS_ISRPARAM = DeviceDataPrv;
  /* {Default RTOS Adapter} Set interrupt vector: IVT is static, ISR parameter is passed by the global variable */
  INT_CAN0_Wake_Up__DEFAULT_RTOS_ISRPARAM = DeviceDataPrv;

  /* initialization of CAN RX pin�*/
    /* initialization of CAN TX pin */
  /* SIM_SCGC5: PORTB=1 */
  SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
  /* PORTB_PCR19: ISF=0,MUX=2 */
  PORTB_PCR19 = (uint32_t)((PORTB_PCR19 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK |
                 PORT_PCR_MUX(0x05)
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x02)
                ));
  /* PORTB_PCR18: ISF=0,MUX=2 */
  PORTB_PCR18 = (uint32_t)((PORTB_PCR18 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK |
                 PORT_PCR_MUX(0x05)
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x02)
                ));
  /*Interrupt priorities*/
  /* NVICIP77: PRI77=0x70 */
  NVICIP77 = NVIC_IP_PRI77(0x70);
  /* NVICISER2: SETENA|=0x2000 */
  NVICISER2 |= NVIC_ISER_SETENA(0x2000);
  /* NVICIP76: PRI76=0x70 */
  NVICIP76 = NVIC_IP_PRI76(0x70);
  /* NVICISER2: SETENA|=0x1000 */
  NVICISER2 |= NVIC_ISER_SETENA(0x1000);
  /* NVICIP75: PRI75=0x50 */
  NVICIP75 = NVIC_IP_PRI75(0x50);
  /* NVICISER2: SETENA|=0x0800 */
  NVICISER2 |= NVIC_ISER_SETENA(0x0800);
  /* NVICIP78: PRI78=0x70 */
  NVICIP78 = NVIC_IP_PRI78(0x70);
  /* NVICISER2: SETENA|=0x4000 */
  NVICISER2 |= NVIC_ISER_SETENA(0x4000);
  /* NVICIP79: PRI79=0x70 */
  NVICIP79 = NVIC_IP_PRI79(0x70);
  /* NVICISER2: SETENA|=0x8000 */
  NVICISER2 |= NVIC_ISER_SETENA(0x8000);
  /* NVICIP80: PRI80=0x70 */
  NVICIP80 = NVIC_IP_PRI80(0x70);
  /* NVICISER2: SETENA|=0x00010000 */
  NVICISER2 |= NVIC_ISER_SETENA(0x00010000);
  /* CAN0_MCR: MDIS=1 */
  CAN0_MCR |= CAN_MCR_MDIS_MASK;       /* Disable CAN module */
  /*Bus Clock selected*/
  /* CAN0_CTRL1: PRESDIV=0,RJW=0,PSEG1=0,PSEG2=0,BOFFMSK=0,ERRMSK=0,CLKSRC=1,LPB=0,TWRNMSK=0,RWRNMSK=0,??=0,??=0,SMP=0,BOFFREC=0,TSYN=0,LBUF=0,LOM=0,PROPSEG=0 */
  CAN0_CTRL1 = CAN_CTRL1_PRESDIV(0x00) |
               CAN_CTRL1_RJW(0x00) |
               CAN_CTRL1_PSEG1(0x00) |
               CAN_CTRL1_PSEG2(0x00) |
               CAN_CTRL1_CLKSRC_MASK |
               CAN_CTRL1_PROPSEG(0x00);
  /* CAN0_MCR: MDIS=0,SOFTRST=1 */
  CAN0_MCR = (uint32_t)((CAN0_MCR & (uint32_t)~(uint32_t)(
              CAN_MCR_MDIS_MASK
             )) | (uint32_t)(
              CAN_MCR_SOFTRST_MASK
             ));                       /* Soft Reset */
  while (CAN_PDD_GetSoftResetState(CAN0_BASE_PTR) == CAN_PDD_NOT_RESET){} /* Wait for Soft reset Acknowledge */
  while (CAN_PDD_GetFreezeAck(CAN0_BASE_PTR) == CAN_PDD_NOT_FREEZE){} /* Wait for entering the freeze mode */
  /* CAN0_MCR: WRNEN=1,SRXDIS=1,MAXMB&=~0x0E,MAXMB|=1 */
  CAN0_MCR = (uint32_t)((CAN0_MCR & (uint32_t)~(uint32_t)(
              CAN_MCR_MAXMB(0x0E)
             )) | (uint32_t)(
              CAN_MCR_WRNEN_MASK |
              CAN_MCR_SRXDIS_MASK |
              CAN_MCR_MAXMB(0x01)
             ));                       /* MCR reg. Settings */
  /* CAN0_CTRL1: PRESDIV|=5,PSEG1|=4,PSEG2|=2,LBUF=1 */
  CAN0_CTRL1 |= CAN_CTRL1_PRESDIV(0x05) |
                CAN_CTRL1_PSEG1(0x04) |
                CAN_CTRL1_PSEG2(0x02) |
                CAN_CTRL1_LBUF_MASK;   /* Setting CTRL1 register */
  /* CAN0_CTRL2: RRS=1 */
  CAN0_CTRL2 |= CAN_CTRL2_RRS_MASK;    /* Setting CTRL2 register */
  /* CAN0_RXMGMASK: MG=0x1FFFFFFF */
  CAN0_RXMGMASK = CAN_RXMGMASK_MG(0x1FFFFFFF); /* Set the Global acceptance mask register */
  /* CAN0_RX14MASK: RX14M=0x1FFFFFFF */
  CAN0_RX14MASK = CAN_RX14MASK_RX14M(0x1FFFFFFF); /* Set the acceptance mask register for buffers 14 */
  /* CAN0_RX15MASK: RX15M=0x1FFFFFFF */
  CAN0_RX15MASK = CAN_RX15MASK_RX15M(0x1FFFFFFF); /* Set the acceptance mask register for buffers 15 */
  /* Initialize the message buffer 0 - Rx */
  CAN_PDD_SetMessageBufferCode(CAN0_BASE_PTR, 0U, CAN_PDD_MB_RX_NOT_ACTIVE);
  CAN_PDD_EnableMessageBufferIDExt(CAN0_BASE_PTR, 0U, PDD_DISABLE); /* Extended Frame bit IDE clear*/
  CAN_PDD_SetMessageBufferID(CAN0_BASE_PTR, 0U, CAN_PDD_BUFFER_ID_STD, 0x07FFU); /* Set standard buffer ID */
  CAN_PDD_SetMessageBufferCode(CAN0_BASE_PTR, 0U, CAN_PDD_MB_RX_EMPTY); /* Empty Frame*/
  CAN_PDD_EnableMessageBufferSRR(CAN0_BASE_PTR, 0U, PDD_DISABLE); /* SRR set to 0 */
  CAN_PDD_EnableMessageBufferRTR(CAN0_BASE_PTR, 0U, PDD_DISABLE); /* RTR set to 0*/
  CAN_PDD_SetMessageBufferWORD0(CAN0_BASE_PTR, 0U, 0x00U); /*Clear Data field*/
  CAN_PDD_SetMessageBufferWORD1(CAN0_BASE_PTR, 0U, 0x00U); /*Clear Data field*/
  CAN_PDD_SetMessageBufferTimeStamp(CAN0_BASE_PTR, 0U, 0x00U); /* Empty Frame*/
  /* Initialize the message buffer 1 - Tx */
  CAN_PDD_SetMessageBufferCode(CAN0_BASE_PTR, 1U, CAN_PDD_MB_TX_NOT_ACTIVE); /* Control/status word to hold Tx message buffer 1 inactive */
  CAN_PDD_EnableMessageBufferSRR(CAN0_BASE_PTR, 1U, PDD_DISABLE); /* SRR set to 0 */
  CAN_PDD_EnableMessageBufferRTR(CAN0_BASE_PTR, 1U, PDD_DISABLE); /* RTR set to 0*/
  CAN_PDD_SetMessageBufferWORD0(CAN0_BASE_PTR, 1U, 0x00U); /*Clear Data field*/
  CAN_PDD_SetMessageBufferWORD1(CAN0_BASE_PTR, 1U, 0x00U); /*Clear Data field*/
  CAN_PDD_SetMessageBufferTimeStamp(CAN0_BASE_PTR, 1U, 0x00U); /* Empty Frame*/
  /* CAN0_IMASK1: BUFLM=3 */
  CAN0_IMASK1 = CAN_IMASK1_BUFLM(0x03); /* Enable Tx/Rx interrupt for message buffer/s */
  CAN_PDD_ExitFreezeMode(CAN0_BASE_PTR); /* Exit Freeze Mode */
  while(CAN_PDD_GetFreezeAck(CAN0_BASE_PTR) == CAN_PDD_IS_FREEZE){} /* Wait for exit the freeze mode */
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_CAN1_ID,DeviceDataPrv);
  return ((LDD_TDeviceDataPtr)DeviceDataPrv);
}

/*
** ===================================================================
**     Method      :  CAN1_SetRxBufferID (component CAN_LDD)
*/
/*!
**     @brief
**         Sets the ID of the receive message buffer specified by the
**         parameter BufferIdx.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         BufferIdx       - Index of the Rx message buffer.
**     @param
**         MessageID       - 11-bit Mask could be selected
**                           for a standard frame or 29-bit for an
**                           extended frame. 
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_DISABLED - This component is disabled
**                           by user.
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
**                           ERR_PARAM_RANGE - Value of message buffer
**                           index is out of range.
**                           ERR_PARAM_INDEX - Index of message buffer
**                           is not for data receive.
*/
/* ===================================================================*/
LDD_TError CAN1_SetRxBufferID(LDD_TDeviceData *DeviceDataPtr, LDD_CAN_TMBIndex BufferIdx, LDD_CAN_TMessageID MessageID)
{
  CAN1_TDeviceData *DeviceDataPrv = (CAN1_TDeviceData *)DeviceDataPtr;
  LDD_CAN_TMessageID TempMessageID;

  if (BufferIdx > DeviceDataPrv->MaxBufferIndex) { /* Is BufferIdx greater than Max Buffers*/
    return ERR_PARAM_RANGE;            /* If yes then error */
  }
  if (((LDD_CAN_TBufferMask)(0x01UL << BufferIdx) & DeviceDataPrv->RxBufferMask) == 0x00U) { /* Is used buffer defined of BufferIdx for receive? */
    return ERR_PARAM_INDEX;            /* If no then error */
  }
  TempMessageID = (LDD_CAN_TMessageID)(MessageID & (LDD_CAN_TMessageID)(~(LDD_CAN_TMessageID)LDD_CAN_MESSAGE_ID_EXT));
  if ((MessageID & LDD_CAN_MESSAGE_ID_EXT) != 0x00U) { /* Is MessageID extended value? */
    CAN_PDD_SetMessageBufferID(CAN0_BASE_PTR, BufferIdx, CAN_PDD_BUFFER_ID_EXT, TempMessageID); /*Assign extended ID to buffer */
    CAN_PDD_EnableMessageBufferIDExt(CAN0_BASE_PTR, BufferIdx, PDD_ENABLE);
  } else {
    CAN_PDD_SetMessageBufferID(CAN0_BASE_PTR, BufferIdx, CAN_PDD_BUFFER_ID_STD, TempMessageID); /*Assign Standard ID to buffer */
    CAN_PDD_EnableMessageBufferIDExt(CAN0_BASE_PTR, BufferIdx, PDD_DISABLE);
  }
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  CAN1_SendFrame (component CAN_LDD)
*/
/*!
**     @brief
**         Sends a frame via the CAN device. This method allow to
**         specify CAN buffer number, message ID, data to be sent,
**         frame type and whether the message will be sent after the
**         request comes. 
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         BufferIdx       - Index of the Tx message buffer.
**     @param
**         Frame           - Pointer to the CAN frame to send.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_DISABLED - This component is disabled
**                           by user
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
**                           ERR_PARAM_RANGE - Value of buffer index is
**                           out of range.
**                           ERR_PARAM_INDEX - Index of message buffer
**                           is not for transmit.
**                           ERR_PARAM_LENGTH - Number of data in the
**                           frame is greater than MaxDataLength.
**                           ERR_PARAM_ATTRIBUTE_SET - Frame type isn't
**                           supported.
**                           ERR_PARAM_VALUE - Value of Tx priority is
**                           fail.
**                           ERR_BUSY - CAN module is busy.
*/
/* ===================================================================*/
LDD_TError CAN1_SendFrame(LDD_TDeviceData *DeviceDataPtr, LDD_CAN_TMBIndex BufferIdx, LDD_CAN_TFrame *Frame)
{
  CAN1_TDeviceData *DeviceDataPrv = (CAN1_TDeviceData *)DeviceDataPtr;
  LDD_CAN_TBufferMask BufferMask;      /* Bitmask of the requested message buffer */
  uint8_t TxMBCode = 0x00U;            /* Temporary value of MB code */
  uint8_t DataIndex;

  if (BufferIdx > DeviceDataPrv->MaxBufferIndex) { /* Is BufferIdx greater than MaxBuffers? */
    return ERR_PARAM_RANGE;            /* If yes then error */
  }
  BufferMask = (LDD_CAN_TBufferMask)(0x01UL << BufferIdx);
  if ((BufferMask & DeviceDataPrv->TxBufferMask) == 0x00U) { /* Is used buffer defined of BufferIdx for transmit? */
    return ERR_PARAM_INDEX;            /* If no then error */
  }
  if (Frame->Length > DeviceDataPrv->MaxDataLen) { /* Is number of data greater than MaxDataLen? */
    return ERR_PARAM_LENGTH;           /* If yes then error */
  }
  if (Frame->FrameType > LDD_CAN_RESPONSE_FRAME) { /* Is FrameType other than LDD_CAN_DATA_FRAME_STD, LDD_CAN_DATA_FRAME_EXT or LDD_CAN_REMOTE_FRAME? */
    return ERR_PARAM_ATTRIBUTE_SET;    /* If yes then error */
  }
  /* {Default RTOS Adapter} Critical section begin, general PE function is used */
  EnterCritical();
  if (CAN_PDD_GetMessageBufferCode(CAN0_BASE_PTR, BufferIdx) != CAN_PDD_MB_TX_NOT_ACTIVE) { /* Is Tx buffer inactive */
    /* {Default RTOS Adapter} Critical section end, general PE function is used */
    ExitCritical();
    return ERR_BUSY;                   /* If no then error */
  }         
  if ((Frame->MessageID & LDD_CAN_MESSAGE_ID_EXT) != 0x00U) { /* Is the frame configured as Extended ID? */
    CAN_PDD_SetMessageBufferID(CAN0_BASE_PTR, BufferIdx, CAN_PDD_BUFFER_ID_EXT, (Frame->MessageID)&~(LDD_CAN_MESSAGE_ID_EXT)); /*Assign extended ID to buffer */
    CAN_PDD_EnableMessageBufferIDExt(CAN0_BASE_PTR, BufferIdx, PDD_ENABLE); /*Set ID extended */
  } else {
    CAN_PDD_SetMessageBufferID(CAN0_BASE_PTR, BufferIdx, CAN_PDD_BUFFER_ID_STD, Frame->MessageID); /*Assign Standard ID to buffer */
    CAN_PDD_EnableMessageBufferIDExt(CAN0_BASE_PTR, BufferIdx, PDD_DISABLE); /*Set ID standard */
  }
  if ((Frame->FrameType == LDD_CAN_DATA_FRAME)||(Frame->FrameType == LDD_CAN_RESPONSE_FRAME)) { /* Is it a data or WaitOnRemote frame? */
    for (DataIndex = 0x00U; DataIndex < Frame->Length; DataIndex++) { /* Fill message buffer data array */
      CAN_PDD_SetMessageBufferData(CAN0_BASE_PTR, BufferIdx, DataIndex, Frame->Data[DataIndex]);
    }
    CAN_PDD_SetMessageBufferDataLength(CAN0_BASE_PTR, BufferIdx, Frame->Length); /* Set the length of the message */
    CAN_PDD_EnableMessageBufferRTR(CAN0_BASE_PTR, BufferIdx, PDD_DISABLE); /* Clear RTR bit */
    CAN_PDD_EnableMessageBufferSRR(CAN0_BASE_PTR, BufferIdx, PDD_DISABLE); /* Clear SRR bit */
    if (Frame->FrameType == LDD_CAN_DATA_FRAME) {
      TxMBCode = CAN_PDD_MB_TX_DATA_FRAME; /* Set buffer as a transmit buffer */
    } else {
      TxMBCode = CAN_PDD_MB_TX_RESPONSE_FRAME; /* Set buffer as a response transmit buffer for remote frames */
    }
  } else {                             /* Remote frame */
    TxMBCode = CAN_PDD_MB_TX_REMOTE_FRAME; /* Set Tx buffer for remote frames */
    CAN_PDD_SetMessageBufferDataLength(CAN0_BASE_PTR, BufferIdx, 0x00U); /* Set the length of the message */
    CAN_PDD_EnableMessageBufferRTR(CAN0_BASE_PTR, BufferIdx, PDD_ENABLE); /* Set the message as a remote frame */
    if ((Frame->MessageID & LDD_CAN_MESSAGE_ID_EXT) != 0x00U) { /* Extended frame */
      CAN_PDD_EnableMessageBufferSRR(CAN0_BASE_PTR, BufferIdx, PDD_ENABLE); /* Set SRR bit */
    } else {                           /* Standard frame */
      CAN_PDD_EnableMessageBufferSRR(CAN0_BASE_PTR, BufferIdx, PDD_DISABLE); /* Clear SRR bit */
    }
  }
  CAN_PDD_SetMessageBufferCode(CAN0_BASE_PTR, BufferIdx, TxMBCode); /* Set code for Tx buffer of the message */
  /* {Default RTOS Adapter} Critical section end, general PE function is used */
  ExitCritical();
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  CAN1_ReadFrame (component CAN_LDD)
*/
/*!
**     @brief
**         Reads a frame from the CAN device. The user is informed
**         about CAN reception through OnFullRxBuffer event or
**         GetStateRX method.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         BufferIdx       - Index of the Rx message buffer.
**     @param
**         Frame           - Pointer to the received CAN frame.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_DISABLED - This component is disabled
**                           by user
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
**                           ERR_PARAM_RANGE - Value of buffer index is
**                           out of range.
**                           ERR_PARAM_INDEX - Index of message buffer
**                           is not for receive.
**                           ERR_BUSY - CAN module is busy.
**                           ERR_RXEMPTY - The receive buffer is empty.
**                           ERR_OVERRUN - The receive buffer is overrun.
*/
/* ===================================================================*/
LDD_TError CAN1_ReadFrame(LDD_TDeviceData *DeviceDataPtr, LDD_CAN_TMBIndex BufferIdx, LDD_CAN_TFrame *Frame)
{
  CAN1_TDeviceData *DeviceDataPrv = (CAN1_TDeviceData *)DeviceDataPtr;
  LDD_CAN_TBufferMask BufferMask;      /* Bitmask of the requested message buffer */
  uint8_t RxMBCode;                    /* Temporary variable */
  uint8_t DataIndex;

  if (BufferIdx > DeviceDataPrv->MaxBufferIndex) { /* Is the number of the required message buffer out of range?*/
    return ERR_PARAM_RANGE;            /* If yes then error */
  }
  BufferMask = (LDD_CAN_TBufferMask)(0x01UL << BufferIdx); /* Calculate bitmask of the requested message buffer */
  if ((BufferMask & DeviceDataPrv->RxBufferMask) == 0x00U) { /* Is used buffer defined of BufferIdx for receive? */
    return ERR_PARAM_INDEX;            /* If no then error */
  }
  RxMBCode = CAN_PDD_GetMessageBufferCode(CAN0_BASE_PTR, BufferIdx); /* Read the code of the given message buffer */
  if (RxMBCode == CAN_PDD_MB_RX_BUSY) { /* Is the receive buffer busy? */
    return ERR_BUSY;                   /* If yes then error */
  }
  if (RxMBCode == CAN_PDD_MB_RX_EMPTY) { /* Is the receive buffer empty? */
    (void)CAN_PDD_GetTimerValue(CAN0_BASE_PTR); /* Dummy read of Free running timer register release buffer lock */
    return ERR_RXEMPTY;                /* If yes then error */
  }
  /* {Default RTOS Adapter} Critical section begin, general PE function is used */
  EnterCritical();
  CAN_PDD_SetMessageBufferCode(CAN0_BASE_PTR, BufferIdx, CAN_PDD_MB_RX_NOT_ACTIVE); /* Hold inactive Rx buffer */
  if (CAN_PDD_GetMessageBufferIDExt(CAN0_BASE_PTR, BufferIdx) == PDD_ENABLE) { /* Extended ID? */
    Frame->MessageID = (LDD_CAN_TMessageID)(CAN_PDD_GetMessageBufferID(CAN0_BASE_PTR, BufferIdx, CAN_PDD_BUFFER_ID_EXT) | (uint32_t)LDD_CAN_MESSAGE_ID_EXT);
  } else {
    Frame->MessageID = (LDD_CAN_TMessageID)CAN_PDD_GetMessageBufferID(CAN0_BASE_PTR, BufferIdx, CAN_PDD_BUFFER_ID_STD);
  }
  if (CAN_PDD_GetMessageBufferRTR(CAN0_BASE_PTR, BufferIdx)) { /* Remote Frame type?*/
    Frame->FrameType = LDD_CAN_REMOTE_FRAME; /* Set the frame type */
  } else {
    Frame->FrameType = LDD_CAN_DATA_FRAME; /* Set the frame type */
  }
  Frame->Length = CAN_PDD_GetMessageBufferDataLength(CAN0_BASE_PTR, BufferIdx); /* Result length of the message */
  Frame->TimeStamp = CAN_PDD_GetMessageBufferTimeStamp(CAN0_BASE_PTR, BufferIdx); /* Value time stamp of the message */
  if (Frame->FrameType != LDD_CAN_REMOTE_FRAME) { /* Is it "data frame"? */
    for (DataIndex = 0x00U; DataIndex<Frame->Length; DataIndex++) {
      Frame->Data[DataIndex] = CAN_PDD_GetMessageBufferData(CAN0_BASE_PTR, BufferIdx, DataIndex);
    }
  }
  CAN_PDD_SetMessageBufferCode(CAN0_BASE_PTR, BufferIdx, CAN_PDD_MB_RX_EMPTY); /* Set the message buffer code*/
  (void)CAN_PDD_GetTimerValue(CAN0_BASE_PTR); /* Dummy read of Free running timer register release buffer lock */
  /* {Default RTOS Adapter} Critical section end, general PE function is used */
  ExitCritical();
  if (RxMBCode == CAN_PDD_MB_RX_OVERRUN) { /* Is the overrun flag set? */
    return ERR_OVERRUN;                /* Return error */
  }
  return ERR_OK;
}


/*
** ===================================================================
**     Method      :  CAN1_InterruptError (component CAN_LDD)
**
**     Description :
**         Error Interrupt for CAN
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(CAN1_InterruptError)
{
  /* {Default RTOS Adapter} ISR parameter is passed through the global variable */
  CAN1_TDeviceDataPtr DeviceDataPrv = INT_CAN0_Error__DEFAULT_RTOS_ISRPARAM;
  uint32_t ErrorFlags;

  (void)DeviceDataPrv;                 /* Parameter is not used, suppress unused argument warning */
  ErrorFlags = CAN_PDD_GetStatusInterruptFlags1(CAN0_BASE_PTR); /* Read the status register */
  CAN_PDD_ClearStatusInterruptFlags1(CAN0_BASE_PTR, CAN_PDD_ERROR_INT); /* Clear interrupt pending flag */
}

/*
** ===================================================================
**     Method      :  CAN1_InterruptBusOff (component CAN_LDD)
**
**     Description :
**         Bus Off interrupt for CAN
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(CAN1_InterruptBusOff)
{
  /* {Default RTOS Adapter} ISR parameter is passed through the global variable */
  CAN1_TDeviceDataPtr DeviceDataPrv = INT_CAN0_Bus_Off__DEFAULT_RTOS_ISRPARAM;
  (void)DeviceDataPrv;                 /* Parameter is not used, suppress unused argument warning */
  CAN_PDD_ClearStatusInterruptFlags1(CAN0_BASE_PTR, CAN_PDD_BUS_OFF_INT); /* Clear interrupt pending flag */
}

/*
** ===================================================================
**     Method      :  CAN1_InterruptRxTx (component CAN_LDD)
**
**     Description :
**         Or'ed Message Interrupt
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(CAN1_InterruptRxTx)
{
  /* {Default RTOS Adapter} ISR parameter is passed through the global variable */
  CAN1_TDeviceDataPtr DeviceDataPrv = INT_CAN0_ORed_Message_buffer__DEFAULT_RTOS_ISRPARAM;
  LDD_CAN_TBufferMask TxBufferMask;
  LDD_CAN_TBufferMask RxBufferMask;
  LDD_CAN_TBufferMask BufferMask;
  LDD_CAN_TMBIndex MBIndex,MBIndexMax = (LDD_CAN_TMBIndex)DeviceDataPrv->BuffersNumber;
  uint32_t StatusReg = CAN_PDD_GetMessageBufferInterruptFlag1(CAN0_BASE_PTR); /* Read content of the interrupt flags */
  CAN_PDD_ClearMessageBufferInterruptFlagMask1(CAN0_BASE_PTR, StatusReg); /* Clear pending interrupt flags */
  TxBufferMask = (LDD_CAN_TBufferMask)(DeviceDataPrv->TxBufferMask & StatusReg);
  if (TxBufferMask != 0x00U) {         /* Is Tx Buffer? */
    BufferMask = 0x01U;
    for (MBIndex=0x00U; MBIndex<MBIndexMax; MBIndex++) {
      if ((TxBufferMask & BufferMask) != 0x00U) {
        CAN1_OnFreeTxBuffer(DeviceDataPrv->UserData, MBIndex); /* Invoke user event */
      }
      BufferMask = (LDD_CAN_TBufferMask)(BufferMask << 0x01U);
    }
  }
  RxBufferMask = (LDD_CAN_TBufferMask)(DeviceDataPrv->RxBufferMask & StatusReg);
  if (RxBufferMask != 0x00U) {         /* Is Rx Buffer? */
    BufferMask = 0x01U;
    for (MBIndex=0x00U; MBIndex<MBIndexMax; MBIndex++) {
      if ((RxBufferMask & BufferMask) != 0x00U) {
        CAN1_OnFullRxBuffer(DeviceDataPrv->UserData, MBIndex); /* Invoke user event */
      }
      BufferMask = (LDD_CAN_TBufferMask)(BufferMask << 0x01U);
    }
  }
}

/*
** ===================================================================
**     Method      :  CAN1_InterruptTxWarn (component CAN_LDD)
**
**     Description :
**         Transmit Warning Interrupt
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(CAN1_InterruptTxWarn)
{
  /* {Default RTOS Adapter} ISR parameter is passed through the global variable */
  CAN1_TDeviceDataPtr DeviceDataPrv = INT_CAN0_Tx_Warning__DEFAULT_RTOS_ISRPARAM;
  (void)DeviceDataPrv;                 /* Parameter is not used, suppress unused argument warning */

  CAN_PDD_ClearStatusInterruptFlags1(CAN0_BASE_PTR, CAN_PDD_TX_WARNING_INT); /* Clear interrupt pending flag */
}

/*
** ===================================================================
**     Method      :  CAN1_InterruptRxWarn (component CAN_LDD)
**
**     Description :
**         Receive Warning Interrupt
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(CAN1_InterruptRxWarn)
{
  /* {Default RTOS Adapter} ISR parameter is passed through the global variable */
  CAN1_TDeviceDataPtr DeviceDataPrv = INT_CAN0_Rx_Warning__DEFAULT_RTOS_ISRPARAM;
  (void)DeviceDataPrv;                 /* Parameter is not used, suppress unused argument warning */

  CAN_PDD_ClearStatusInterruptFlags1(CAN0_BASE_PTR, CAN_PDD_RX_WARNING_INT); /* Clear interrupt pending flag */
}

/*
** ===================================================================
**     Method      :  CAN1_InterruptWakeUp (component CAN_LDD)
**
**     Description :
**         Wake Up Interrupt
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(CAN1_InterruptWakeUp)
{
  /* {Default RTOS Adapter} ISR parameter is passed through the global variable */
  CAN1_TDeviceDataPtr DeviceDataPrv = INT_CAN0_Wake_Up__DEFAULT_RTOS_ISRPARAM;
  (void)DeviceDataPrv;                 /* Parameter is not used, suppress unused argument warning */

  CAN_PDD_ClearStatusInterruptFlags1(CAN0_BASE_PTR, CAN_PDD_WAKEUP_INT); /* Clear interrupt pending flag */
}

/* END CAN1. */

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
