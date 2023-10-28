/***************************************************************************//**
* \file ProtocovUSB_cdc.h
* \version 3.20
*
* \brief
*  This file provides function prototypes and constants for the USBFS component 
*  CDC class.
*
* Related Document:
*  Universal Serial Bus Class Definitions for Communication Devices Version 1.1
*
********************************************************************************
* \copyright
* Copyright 2012-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_ProtocovUSB_cdc_H)
#define CY_USBFS_ProtocovUSB_cdc_H

#include "ProtocovUSB.h"


/*******************************************************************************
* Prototypes of the ProtocovUSB_cdc API.
*******************************************************************************/
/**
* \addtogroup group_cdc
* @{
*/
#if (ProtocovUSB_ENABLE_CDC_CLASS_API != 0u)
    uint8 ProtocovUSB_CDC_Init(void)            ;
    void ProtocovUSB_PutData(const uint8* pData, uint16 length) ;
    void ProtocovUSB_PutString(const char8 string[])            ;
    void ProtocovUSB_PutChar(char8 txDataByte) ;
    void ProtocovUSB_PutCRLF(void)             ;
    uint16 ProtocovUSB_GetCount(void)          ;
    uint8  ProtocovUSB_CDCIsReady(void)        ;
    uint8  ProtocovUSB_DataIsReady(void)       ;
    uint16 ProtocovUSB_GetData(uint8* pData, uint16 length)     ;
    uint16 ProtocovUSB_GetAll(uint8* pData)    ;
    uint8  ProtocovUSB_GetChar(void)           ;
    uint8  ProtocovUSB_IsLineChanged(void)     ;
    uint32 ProtocovUSB_GetDTERate(void)        ;
    uint8  ProtocovUSB_GetCharFormat(void)     ;
    uint8  ProtocovUSB_GetParityType(void)     ;
    uint8  ProtocovUSB_GetDataBits(void)       ;
    uint16 ProtocovUSB_GetLineControl(void)    ;
    void ProtocovUSB_SendSerialState (uint16 serialState) ;
    uint16 ProtocovUSB_GetSerialState (void)   ;
    void ProtocovUSB_SetComPort (uint8 comNumber) ;
    uint8 ProtocovUSB_GetComPort (void)        ;
    uint8 ProtocovUSB_NotificationIsReady(void) ;

#endif  /* (ProtocovUSB_ENABLE_CDC_CLASS_API) */
/** @} cdc */

/*******************************************************************************
*  Constants for ProtocovUSB_cdc API.
*******************************************************************************/

/* CDC Class-Specific Request Codes (CDC ver 1.2 Table 19) */
#define ProtocovUSB_CDC_SET_LINE_CODING        (0x20u)
#define ProtocovUSB_CDC_GET_LINE_CODING        (0x21u)
#define ProtocovUSB_CDC_SET_CONTROL_LINE_STATE (0x22u)

/*PSTN Subclass Specific Notifications (CDC ver 1.2 Table 30)*/
#define ProtocovUSB_SERIAL_STATE               (0x20u)

#define ProtocovUSB_LINE_CODING_CHANGED        (0x01u)
#define ProtocovUSB_LINE_CONTROL_CHANGED       (0x02u)

#define ProtocovUSB_1_STOPBIT                  (0x00u)
#define ProtocovUSB_1_5_STOPBITS               (0x01u)
#define ProtocovUSB_2_STOPBITS                 (0x02u)

#define ProtocovUSB_PARITY_NONE                (0x00u)
#define ProtocovUSB_PARITY_ODD                 (0x01u)
#define ProtocovUSB_PARITY_EVEN                (0x02u)
#define ProtocovUSB_PARITY_MARK                (0x03u)
#define ProtocovUSB_PARITY_SPACE               (0x04u)

#define ProtocovUSB_LINE_CODING_SIZE           (0x07u)
#define ProtocovUSB_LINE_CODING_RATE           (0x00u)
#define ProtocovUSB_LINE_CODING_STOP_BITS      (0x04u)
#define ProtocovUSB_LINE_CODING_PARITY         (0x05u)
#define ProtocovUSB_LINE_CODING_DATA_BITS      (0x06u)

#define ProtocovUSB_LINE_CONTROL_DTR           (0x01u)
#define ProtocovUSB_LINE_CONTROL_RTS           (0x02u)

#define ProtocovUSB_MAX_MULTI_COM_NUM          (2u) 

#define ProtocovUSB_COM_PORT1                  (0u) 
#define ProtocovUSB_COM_PORT2                  (1u) 

#define ProtocovUSB_SUCCESS                    (0u)
#define ProtocovUSB_FAILURE                    (1u)

#define ProtocovUSB_SERIAL_STATE_SIZE          (10u)

/* SerialState constants*/
#define ProtocovUSB_SERIAL_STATE_REQUEST_TYPE  (0xA1u)
#define ProtocovUSB_SERIAL_STATE_LENGTH        (0x2u)

/*******************************************************************************
* External data references
*******************************************************************************/
/**
* \addtogroup group_cdc
* @{
*/
extern volatile uint8  ProtocovUSB_linesCoding[ProtocovUSB_MAX_MULTI_COM_NUM][ProtocovUSB_LINE_CODING_SIZE];
extern volatile uint8  ProtocovUSB_linesChanged[ProtocovUSB_MAX_MULTI_COM_NUM];
extern volatile uint16 ProtocovUSB_linesControlBitmap[ProtocovUSB_MAX_MULTI_COM_NUM];
extern volatile uint16 ProtocovUSB_serialStateBitmap[ProtocovUSB_MAX_MULTI_COM_NUM];
extern volatile uint8  ProtocovUSB_cdcDataInEp[ProtocovUSB_MAX_MULTI_COM_NUM];
extern volatile uint8  ProtocovUSB_cdcDataOutEp[ProtocovUSB_MAX_MULTI_COM_NUM];
extern volatile uint8  ProtocovUSB_cdcCommInInterruptEp[ProtocovUSB_MAX_MULTI_COM_NUM];
/** @} cdc */

/*******************************************************************************
* The following code is DEPRECATED and
* must not be used.
*******************************************************************************/


#define ProtocovUSB_lineCoding             ProtocovUSB_linesCoding[0]
#define ProtocovUSB_lineChanged            ProtocovUSB_linesChanged[0]
#define ProtocovUSB_lineControlBitmap      ProtocovUSB_linesControlBitmap[0]
#define ProtocovUSB_cdc_data_in_ep         ProtocovUSB_cdcDataInEp[0]
#define ProtocovUSB_cdc_data_out_ep        ProtocovUSB_cdcDataOutEp[0]

#endif /* (CY_USBFS_ProtocovUSB_cdc_H) */


/* [] END OF FILE */
