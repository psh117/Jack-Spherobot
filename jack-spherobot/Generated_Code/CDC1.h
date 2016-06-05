/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : CDC1.h
**     Project     : jack-spherobot
**     Processor   : MK64FN1M0VLL12
**     Component   : FSL_USB_CDC_Device
**     Version     : Component 01.081, Driver 01.00, CPU db: 3.00.000
**     Repository  : My Components
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-05-28, 12:15, # CodeGen: 7
**     Abstract    :
**
**     Settings    :
**          Component name                                 : CDC1
**          CPU                                            : Kinetis K64F
**          CDC Settings                                   : Enabled
**            .inf ClassGuid                               : 4D36E978-E325-11CE-BFC1-08002BE10318
**            .inf VID                                     : 0x2504
**            .inf PID                                     : 0x0300
**            .inf PRVDR                                   : Freescale
**            .inf MFGNAME                                 : My Company
**            .inf DESCRIPTION                             : Freescale CDC Device
**            .inf SERVICE                                 : Virtual Com Driver
**            Bus reported device                          : FSL CDC DEVICE
**            Bus reported vendor                          : FREESCALE INC.
**            Serial Number                                : 000123ABC
**          Configuration                                  : 
**            USB_EP0_SIZE (in)                            : 32
**            USB_EP1_SIZE (out)                           : 32
**            USB_EP2_SIZE (notify)                        : 32
**          Send Buffer                                    : RingBuffer
**          Receive Buffer                                 : RingBuffer
**          SendDataBlock                                  : 
**            Use Timeout                                  : Enabled
**              Timeout                                    : TMOUT1
**              App Task Timeout (ms)                      : 20
**            Waiting time (ms)                            : 10
**            Wait                                         : WAIT1
**          Power Options                                  : 
**            Bus Powered                                  : yes
**            Self Powered                                 : yes
**            Current Draw (mA)                            : 100
**     Contents    :
**         ClearRxBuffer       - void CDC1_ClearRxBuffer(void);
**         ClearTxBuffer       - void CDC1_ClearTxBuffer(void);
**         GetFreeInTxBuf      - uint16_t CDC1_GetFreeInTxBuf(void);
**         GetCharsInTxBuf     - uint16_t CDC1_GetCharsInTxBuf(void);
**         GetCharsInRxBuf     - uint16_t CDC1_GetCharsInRxBuf(void);
**         GetChar             - uint8_t CDC1_GetChar(CDC1_TComData *Chr);
**         RecvChar            - uint8_t CDC1_RecvChar(CDC1_TComData *Chr);
**         SendChar            - uint8_t CDC1_SendChar(CDC1_TComData Chr);
**         SendString          - uint8_t CDC1_SendString(CDC1_TComData *Chr);
**         SendBlock           - uint8_t CDC1_SendBlock(uint8_t *data, uint16_t dataSize);
**         PutBufferChecked    - uint8_t CDC1_PutBufferChecked(uint8_t *buf, size_t bufSize);
**         App_Callback        - void CDC1_App_Callback(uint8_t controller_ID, uint8_t event_type, void *val);
**         Notify_Callback     - void CDC1_Notify_Callback(uint8_t controller_ID, uint8_t event_type, void *val);
**         ApplicationStarted  - bool CDC1_ApplicationStarted(void);
**         TransactionsStarted - bool CDC1_TransactionsStarted(void);
**         App_Task            - uint8_t CDC1_App_Task(uint8_t *txBuf, size_t txBufSize);
**         StdIOKeyPressed     - bool CDC1_StdIOKeyPressed(void);
**         StdIOReadChar       - void CDC1_StdIOReadChar(uint8_t *c);
**         StdIOSendChar       - void CDC1_StdIOSendChar(uint8_t ch);
**         Deinit              - uint8_t CDC1_Deinit(void);
**         Init                - uint8_t CDC1_Init(void);
**
**     (c) Copyright Freescale, all rights reserved, 2013
**     Ported as Processor Expert component: Erich Styger
**     http: www.mcuoneclipse.com
** ###################################################################*/
/*!
** @file CDC1.h
** @version 01.00
** @brief
**
*/         
/*!
**  @addtogroup CDC1_module CDC1 module documentation
**  @{
*/         

#ifndef __CDC1_H
#define __CDC1_H

/* MODULE CDC1. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "Tx1.h"
#include "Rx1.h"
#include "TMOUT1.h"
#include "WAIT1.h"
#include <stddef.h> /* for size_t */

#include "Cpu.h"


#ifndef __BWUserType_CDC1_TComData
#define __BWUserType_CDC1_TComData
  typedef uint8_t CDC1_TComData ;      /* User type for communication data type. */
#endif

/*
   DATA_BUFF_SIZE should be greater than or equal to the endpoint buffer size,
   otherwise there will be data loss. For MC9S08JS16, maximum DATA_BUFF_SIZE
   supported is 16 Bytes
*/
#define CDC1_DATA_BUFF_SIZE    64

#define CDC1_USB_ERR_SEND            1  /* Error while sending */
#define CDC1_USB_ERR_BUSOFF          2  /* Bus not ready */
#define CDC1_USB_ERR_INIT            3  /* USB initialization error */
#define CDC1_USB_ERR_TX_CHAR         4  /* Error sending character */
#define CDC1_USB_ERR_TX_STRING       5  /* Error sending string */
#define CDC1_USB_ERR_CHECKED_TXFULL  6  /* Error during sending a checked block */
#define CDC1_USB_ERR_RECEIVE         7  /* Error while starting an receive transaction */
#define CDC1_USB_ERR_RX_PUT          8  /* Error while putting RX byte into buffer */
#define CDC1_USB_ERR_TX_BLOCK        9  /* Error sending data block */
#define CDC1_USB_TIMEOUT_SEND       10  /* Timeout while sending */
#define CDC1_USB_ERR_DEINIT         11  /* USB deinitialization error */


#define CDC1_GetFreeInTxBuf() \
  Tx1_NofFreeElements()
/*
** ===================================================================
**     Method      :  CDC1_GetFreeInTxBuf (component FSL_USB_CDC_Device)
**     Description :
**         Returns the number of free character in the send buffer
**     Parameters  : None
**     Returns     :
**         ---             - Number of free character in the receive
**                           buffer.
** ===================================================================
*/

uint8_t CDC1_RecvChar(CDC1_TComData *Chr);
/*
** ===================================================================
**     Method      :  CDC1_RecvChar (component FSL_USB_CDC_Device)
**     Description :
**         Receives a character from the USB interface. Function is
**         blocking if there is no character in the input buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Chr             - Pointer to where to store the character
**                           received
**     Returns     :
**         ---             - Error code, ERR_OK for success,
**                           ERR_RXEMPTY if nothing is in RX buffer.
** ===================================================================
*/

uint8_t CDC1_SendChar(CDC1_TComData Chr);
/*
** ===================================================================
**     Method      :  CDC1_SendChar (component FSL_USB_CDC_Device)
**     Description :
**         Method to send a character to the USB interface. Method is
**         non-blocking: If the output buffer is full, it tries to send
**         it over USB. If this fails or buffer is still full, the
**         character will be lost. If OnError() event is enabled, the
**         error event will be called in case of error.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Chr             - Character to send.
**     Returns     :
**         ---             - Error code. ERR_OK for success and
**                           ERR_FAILED otherwise.
** ===================================================================
*/

#define CDC1_GetCharsInTxBuf() \
  Tx1_NofElements()
/*
** ===================================================================
**     Method      :  CDC1_GetCharsInTxBuf (component FSL_USB_CDC_Device)
**     Description :
**         Returns the number of character in the send buffer
**     Parameters  : None
**     Returns     :
**         ---             - Number of character in the receive buffer.
** ===================================================================
*/

uint16_t CDC1_GetCharsInRxBuf(void);
/*
** ===================================================================
**     Method      :  CDC1_GetCharsInRxBuf (component FSL_USB_CDC_Device)
**     Description :
**         Returns the number of character in the receive buffer
**     Parameters  : None
**     Returns     :
**         ---             - Number of character in the receive buffer.
** ===================================================================
*/

uint8_t CDC1_Init(void);
/*
** ===================================================================
**     Method      :  CDC1_Init (component FSL_USB_CDC_Device)
**     Description :
**         Initializes the driver
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

uint8_t CDC1_App_Task(uint8_t *txBuf, size_t txBufSize);
/*
** ===================================================================
**     Method      :  CDC1_App_Task (component FSL_USB_CDC_Device)
**     Description :
**         Application task to be called periodically from the main
**         task.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * txBuf           - Pointer to temporary buffer used to
**                           transmit data over USB. Should be equal or
**                           greater than the endpoint buffer size. Data
**                           will be sent in an asynchronous way, so
**                           make sure the buffer is *not* on the stack.
**                           This buffer must be available until the
**                           next transmission.
**         txBufSize       - Size of the buffer in bytes
**     Returns     :
**         ---             - Error code, returns ERR_OK if USB
**                           enumeration has been finished, error code
**                           otherwise.
** ===================================================================
*/

uint8_t CDC1_SendString(CDC1_TComData *Chr);
/*
** ===================================================================
**     Method      :  CDC1_SendString (component FSL_USB_CDC_Device)
**     Description :
**         Method to send a string to the USB interface. Method is
**         non-blocking: if string cannot be sent, it will be lost. If
**         OnError() event is enabled, the error event will be called
**         in case of error.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Chr             - Pointer to string to send.
**     Returns     :
**         ---             - Error code. ERR_OK for success and
**                           ERR_FAILED otherwise.
** ===================================================================
*/

#define CDC1_GetChar(Chr) \
  Rx1_Get(Chr)

/*
** ===================================================================
**     Method      :  CDC1_GetChar (component FSL_USB_CDC_Device)
**     Description :
**         Receives a character from the USB interface. Function is not
**         blocking if there is no character in the input buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Chr             - Pointer to where to store the character
**                           received
**     Returns     :
**         ---             - Error code, ERR_OK for success,
**                           ERR_RXEMPTY if nothing is in RX buffer.
** ===================================================================
*/

uint8_t CDC1_PutBufferChecked(uint8_t *buf, size_t bufSize);
/*
** ===================================================================
**     Method      :  CDC1_PutBufferChecked (component FSL_USB_CDC_Device)
**     Description :
**         Puts a data block into the output buffer, but does not send
**         it. If there is not enough size available, then ERR_TXFULL
**         is returned, otherwise ERR_OK. The application then needs to
**         call USB_App_Callback() to actually send the buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * buf             - Pointer to buffer to be sent
**         bufsize         - Buffer size in bytes
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

void CDC1_App_Callback(uint8_t controller_ID, uint8_t event_type, void *val);
/*
** ===================================================================
**     Method      :  CDC1_App_Callback (component FSL_USB_CDC_Device)
**     Description :
**         Method to handle class callbacks from USB
**     Parameters  :
**         NAME            - DESCRIPTION
**         controller_ID   - controller ID
**         event_type      - value of the event
**         val             - gives the configuration value
**     Returns     : Nothing
** ===================================================================
*/

void CDC1_Notify_Callback(uint8_t controller_ID, uint8_t event_type, void *val);
/*
** ===================================================================
**     Method      :  CDC1_Notify_Callback (component FSL_USB_CDC_Device)
**     Description :
**         Method to handle PSTN Sub Class callbacks
**     Parameters  :
**         NAME            - DESCRIPTION
**         controller_ID   - controller ID
**         event_type      - value of the event
**         val             - 
**     Returns     : Nothing
** ===================================================================
*/

#define CDC1_ClearRxBuffer() \
    Rx1_Clear()
/*
** ===================================================================
**     Method      :  CDC1_ClearRxBuffer (component FSL_USB_CDC_Device)
**     Description :
**         Clears the receiver buffer content
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#define CDC1_ClearTxBuffer() \
    Tx1_Clear()
/*
** ===================================================================
**     Method      :  CDC1_ClearTxBuffer (component FSL_USB_CDC_Device)
**     Description :
**         Clears the transmit buffer content
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void CDC1_RunUsbEngine(void);
/*
** ===================================================================
**     Method      :  CDC1_RunUsbEngine (component FSL_USB_CDC_Device)
**
**     Description :
**         Runs the USB polling engine
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

uint8_t CDC1_SendBlock(uint8_t *data, uint16_t dataSize);
/*
** ===================================================================
**     Method      :  CDC1_SendBlock (component FSL_USB_CDC_Device)
**     Description :
**         Method to send a data block to the USB interface. Method is
**         non-blocking: if data cannot be sent, it will be lost. If
**         OnError() event is enabled, the error event will be called
**         in case of error.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * data            - Pointer to data to send.
**         dataSize        - Size of data in bytes
**     Returns     :
**         ---             - Error code. ERR_OK for success and
**                           ERR_FAILED otherwise.
** ===================================================================
*/

uint8_t CDC1_SendDataBlock(uint8_t *data, uint16_t dataSize);
/*
** ===================================================================
**     Method      :  CDC1_SendDataBlock (component FSL_USB_CDC_Device)
**
**     Description :
**         Sends a USB data block
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

uint8_t CDC1_Deinit(void);
/*
** ===================================================================
**     Method      :  CDC1_Deinit (component FSL_USB_CDC_Device)
**     Description :
**         Deinitializes the driver
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

bool CDC1_StdIOKeyPressed(void);
/*
** ===================================================================
**     Method      :  CDC1_StdIOKeyPressed (component FSL_USB_CDC_Device)
**     Description :
**         StdIO handler for Shell
**     Parameters  : None
**     Returns     :
**         ---             - True if there are characters in the
**                           input/RX buffer
** ===================================================================
*/

void CDC1_StdIOReadChar(uint8_t *c);
/*
** ===================================================================
**     Method      :  CDC1_StdIOReadChar (component FSL_USB_CDC_Device)
**     Description :
**         StdIO Handler for reading a character. It returns a zero
**         byte if there is no character.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * c               - Pointer to where to store the received
**                           character
**     Returns     : Nothing
** ===================================================================
*/

void CDC1_StdIOSendChar(uint8_t ch);
/*
** ===================================================================
**     Method      :  CDC1_StdIOSendChar (component FSL_USB_CDC_Device)
**     Description :
**         StdIO handler to sends a character.
**     Parameters  :
**         NAME            - DESCRIPTION
**         ch              - Character to send.
**     Returns     : Nothing
** ===================================================================
*/

bool CDC1_ApplicationStarted(void);
/*
** ===================================================================
**     Method      :  CDC1_ApplicationStarted (component FSL_USB_CDC_Device)
**     Description :
**         Returns true if USB ApplicationStarted has been started.
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

bool CDC1_TransactionsStarted(void);
/*
** ===================================================================
**     Method      :  CDC1_TransactionsStarted (component FSL_USB_CDC_Device)
**     Description :
**         Returns true if USB transactions  have been started.
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

/* END CDC1. */

#endif
/* ifndef __CDC1_H */
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
