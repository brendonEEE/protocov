/***************************************************************************//**
* \file .h
* \version 3.20
*
* \brief
*  This file provides private function prototypes and constants for the 
*  USBFS component. It is not intended to be used in the user project.
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_ProtocovUSB_pvt_H)
#define CY_USBFS_ProtocovUSB_pvt_H

#include "ProtocovUSB.h"
   
#ifdef ProtocovUSB_ENABLE_AUDIO_CLASS
    #include "ProtocovUSB_audio.h"
#endif /* ProtocovUSB_ENABLE_AUDIO_CLASS */

#ifdef ProtocovUSB_ENABLE_CDC_CLASS
    #include "ProtocovUSB_cdc.h"
#endif /* ProtocovUSB_ENABLE_CDC_CLASS */

#if (ProtocovUSB_ENABLE_MIDI_CLASS)
    #include "ProtocovUSB_midi.h"
#endif /* (ProtocovUSB_ENABLE_MIDI_CLASS) */

#if (ProtocovUSB_ENABLE_MSC_CLASS)
    #include "ProtocovUSB_msc.h"
#endif /* (ProtocovUSB_ENABLE_MSC_CLASS) */

#if (ProtocovUSB_EP_MANAGEMENT_DMA)
    #if (CY_PSOC4)
        #include <CyDMA.h>
    #else
        #include <CyDmac.h>
        #if ((ProtocovUSB_EP_MANAGEMENT_DMA_AUTO) && (ProtocovUSB_EP_DMA_AUTO_OPT == 0u))
            #include "ProtocovUSB_EP_DMA_Done_isr.h"
            #include "ProtocovUSB_EP8_DMA_Done_SR.h"
            #include "ProtocovUSB_EP17_DMA_Done_SR.h"
        #endif /* ((ProtocovUSB_EP_MANAGEMENT_DMA_AUTO) && (ProtocovUSB_EP_DMA_AUTO_OPT == 0u)) */
    #endif /* (CY_PSOC4) */
#endif /* (ProtocovUSB_EP_MANAGEMENT_DMA) */

#if (ProtocovUSB_DMA1_ACTIVE)
    #include "ProtocovUSB_ep1_dma.h"
    #define ProtocovUSB_EP1_DMA_CH     (ProtocovUSB_ep1_dma_CHANNEL)
#endif /* (ProtocovUSB_DMA1_ACTIVE) */

#if (ProtocovUSB_DMA2_ACTIVE)
    #include "ProtocovUSB_ep2_dma.h"
    #define ProtocovUSB_EP2_DMA_CH     (ProtocovUSB_ep2_dma_CHANNEL)
#endif /* (ProtocovUSB_DMA2_ACTIVE) */

#if (ProtocovUSB_DMA3_ACTIVE)
    #include "ProtocovUSB_ep3_dma.h"
    #define ProtocovUSB_EP3_DMA_CH     (ProtocovUSB_ep3_dma_CHANNEL)
#endif /* (ProtocovUSB_DMA3_ACTIVE) */

#if (ProtocovUSB_DMA4_ACTIVE)
    #include "ProtocovUSB_ep4_dma.h"
    #define ProtocovUSB_EP4_DMA_CH     (ProtocovUSB_ep4_dma_CHANNEL)
#endif /* (ProtocovUSB_DMA4_ACTIVE) */

#if (ProtocovUSB_DMA5_ACTIVE)
    #include "ProtocovUSB_ep5_dma.h"
    #define ProtocovUSB_EP5_DMA_CH     (ProtocovUSB_ep5_dma_CHANNEL)
#endif /* (ProtocovUSB_DMA5_ACTIVE) */

#if (ProtocovUSB_DMA6_ACTIVE)
    #include "ProtocovUSB_ep6_dma.h"
    #define ProtocovUSB_EP6_DMA_CH     (ProtocovUSB_ep6_dma_CHANNEL)
#endif /* (ProtocovUSB_DMA6_ACTIVE) */

#if (ProtocovUSB_DMA7_ACTIVE)
    #include "ProtocovUSB_ep7_dma.h"
    #define ProtocovUSB_EP7_DMA_CH     (ProtocovUSB_ep7_dma_CHANNEL)
#endif /* (ProtocovUSB_DMA7_ACTIVE) */

#if (ProtocovUSB_DMA8_ACTIVE)
    #include "ProtocovUSB_ep8_dma.h"
    #define ProtocovUSB_EP8_DMA_CH     (ProtocovUSB_ep8_dma_CHANNEL)
#endif /* (ProtocovUSB_DMA8_ACTIVE) */


/***************************************
*     Private Variables
***************************************/

/* Generated external references for descriptors. */
extern const uint8 CYCODE ProtocovUSB_DEVICE0_DESCR[18u];
extern const uint8 CYCODE ProtocovUSB_DEVICE0_CONFIGURATION0_DESCR[25u];
extern const T_ProtocovUSB_EP_SETTINGS_BLOCK CYCODE ProtocovUSB_DEVICE0_CONFIGURATION0_EP_SETTINGS_TABLE[1u];
extern const uint8 CYCODE ProtocovUSB_DEVICE0_CONFIGURATION0_INTERFACE_CLASS[1u];
extern const T_ProtocovUSB_LUT CYCODE ProtocovUSB_DEVICE0_CONFIGURATION0_TABLE[4u];
extern const T_ProtocovUSB_LUT CYCODE ProtocovUSB_DEVICE0_TABLE[3u];
extern const T_ProtocovUSB_LUT CYCODE ProtocovUSB_TABLE[1u];


extern const uint8 CYCODE ProtocovUSB_MSOS_DESCRIPTOR[ProtocovUSB_MSOS_DESCRIPTOR_LENGTH];
extern const uint8 CYCODE ProtocovUSB_MSOS_CONFIGURATION_DESCR[ProtocovUSB_MSOS_CONF_DESCR_LENGTH];
#if defined(ProtocovUSB_ENABLE_IDSN_STRING)
    extern uint8 ProtocovUSB_idSerialNumberStringDescriptor[ProtocovUSB_IDSN_DESCR_LENGTH];
#endif /* (ProtocovUSB_ENABLE_IDSN_STRING) */

extern volatile uint8 ProtocovUSB_interfaceNumber;
extern volatile uint8 ProtocovUSB_interfaceSetting[ProtocovUSB_MAX_INTERFACES_NUMBER];
extern volatile uint8 ProtocovUSB_interfaceSettingLast[ProtocovUSB_MAX_INTERFACES_NUMBER];
extern volatile uint8 ProtocovUSB_deviceAddress;
extern volatile uint8 ProtocovUSB_interfaceStatus[ProtocovUSB_MAX_INTERFACES_NUMBER];
extern const uint8 CYCODE *ProtocovUSB_interfaceClass;

extern volatile T_ProtocovUSB_EP_CTL_BLOCK ProtocovUSB_EP[ProtocovUSB_MAX_EP];
extern volatile T_ProtocovUSB_TD ProtocovUSB_currentTD;

#if (ProtocovUSB_EP_MANAGEMENT_DMA)
    #if (CY_PSOC4)
        extern const uint8 ProtocovUSB_DmaChan[ProtocovUSB_MAX_EP];
    #else
        extern uint8 ProtocovUSB_DmaChan[ProtocovUSB_MAX_EP];
        extern uint8 ProtocovUSB_DmaTd  [ProtocovUSB_MAX_EP];
    #endif /* (CY_PSOC4) */
#endif /* (ProtocovUSB_EP_MANAGEMENT_DMA) */

#if (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)
#if (CY_PSOC4)
    extern uint8  ProtocovUSB_DmaEpBurstCnt   [ProtocovUSB_MAX_EP];
    extern uint8  ProtocovUSB_DmaEpLastBurstEl[ProtocovUSB_MAX_EP];

    extern uint8  ProtocovUSB_DmaEpBurstCntBackup  [ProtocovUSB_MAX_EP];
    extern uint32 ProtocovUSB_DmaEpBufferAddrBackup[ProtocovUSB_MAX_EP];
    
    extern const uint8 ProtocovUSB_DmaReqOut     [ProtocovUSB_MAX_EP];    
    extern const uint8 ProtocovUSB_DmaBurstEndOut[ProtocovUSB_MAX_EP];
#else
    #if (ProtocovUSB_EP_DMA_AUTO_OPT == 0u)
        extern uint8 ProtocovUSB_DmaNextTd[ProtocovUSB_MAX_EP];
        extern volatile uint16 ProtocovUSB_inLength [ProtocovUSB_MAX_EP];
        extern volatile uint8  ProtocovUSB_inBufFull[ProtocovUSB_MAX_EP];
        extern const uint8 ProtocovUSB_epX_TD_TERMOUT_EN[ProtocovUSB_MAX_EP];
        extern const uint8 *ProtocovUSB_inDataPointer[ProtocovUSB_MAX_EP];
    #endif /* (ProtocovUSB_EP_DMA_AUTO_OPT == 0u) */
#endif /* CY_PSOC4 */
#endif /* (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO) */

extern volatile uint8 ProtocovUSB_ep0Toggle;
extern volatile uint8 ProtocovUSB_lastPacketSize;
extern volatile uint8 ProtocovUSB_ep0Mode;
extern volatile uint8 ProtocovUSB_ep0Count;
extern volatile uint16 ProtocovUSB_transferByteCount;


/***************************************
*     Private Function Prototypes
***************************************/
void  ProtocovUSB_ReInitComponent(void)            ;
void  ProtocovUSB_HandleSetup(void)                ;
void  ProtocovUSB_HandleIN(void)                   ;
void  ProtocovUSB_HandleOUT(void)                  ;
void  ProtocovUSB_LoadEP0(void)                    ;
uint8 ProtocovUSB_InitControlRead(void)            ;
uint8 ProtocovUSB_InitControlWrite(void)           ;
void  ProtocovUSB_ControlReadDataStage(void)       ;
void  ProtocovUSB_ControlReadStatusStage(void)     ;
void  ProtocovUSB_ControlReadPrematureStatus(void) ;
uint8 ProtocovUSB_InitControlWrite(void)           ;
uint8 ProtocovUSB_InitZeroLengthControlTransfer(void) ;
void  ProtocovUSB_ControlWriteDataStage(void)      ;
void  ProtocovUSB_ControlWriteStatusStage(void)    ;
void  ProtocovUSB_ControlWritePrematureStatus(void);
uint8 ProtocovUSB_InitNoDataControlTransfer(void)  ;
void  ProtocovUSB_NoDataControlStatusStage(void)   ;
void  ProtocovUSB_InitializeStatusBlock(void)      ;
void  ProtocovUSB_UpdateStatusBlock(uint8 completionCode) ;
uint8 ProtocovUSB_DispatchClassRqst(void)          ;

void ProtocovUSB_Config(uint8 clearAltSetting) ;
void ProtocovUSB_ConfigAltChanged(void)        ;
void ProtocovUSB_ConfigReg(void)               ;
void ProtocovUSB_EpStateInit(void)             ;


const T_ProtocovUSB_LUT CYCODE *ProtocovUSB_GetConfigTablePtr(uint8 confIndex);
const T_ProtocovUSB_LUT CYCODE *ProtocovUSB_GetDeviceTablePtr(void)           ;
#if (ProtocovUSB_BOS_ENABLE)
    const T_ProtocovUSB_LUT CYCODE *ProtocovUSB_GetBOSPtr(void)               ;
#endif /* (ProtocovUSB_BOS_ENABLE) */
const uint8 CYCODE *ProtocovUSB_GetInterfaceClassTablePtr(void)                    ;
uint8 ProtocovUSB_ClearEndpointHalt(void)                                          ;
uint8 ProtocovUSB_SetEndpointHalt(void)                                            ;
uint8 ProtocovUSB_ValidateAlternateSetting(void)                                   ;

void ProtocovUSB_SaveConfig(void)      ;
void ProtocovUSB_RestoreConfig(void)   ;

#if (CY_PSOC3 || CY_PSOC5LP)
    #if (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO && (ProtocovUSB_EP_DMA_AUTO_OPT == 0u))
        void ProtocovUSB_LoadNextInEP(uint8 epNumber, uint8 mode)  ;
    #endif /* (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO && (ProtocovUSB_EP_DMA_AUTO_OPT == 0u)) */
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

#if defined(ProtocovUSB_ENABLE_IDSN_STRING)
    void ProtocovUSB_ReadDieID(uint8 descr[])  ;
#endif /* ProtocovUSB_ENABLE_IDSN_STRING */

#if defined(ProtocovUSB_ENABLE_HID_CLASS)
    uint8 ProtocovUSB_DispatchHIDClassRqst(void) ;
#endif /* (ProtocovUSB_ENABLE_HID_CLASS) */

#if defined(ProtocovUSB_ENABLE_AUDIO_CLASS)
    uint8 ProtocovUSB_DispatchAUDIOClassRqst(void) ;
#endif /* (ProtocovUSB_ENABLE_AUDIO_CLASS) */

#if defined(ProtocovUSB_ENABLE_CDC_CLASS)
    uint8 ProtocovUSB_DispatchCDCClassRqst(void) ;
#endif /* (ProtocovUSB_ENABLE_CDC_CLASS) */

#if (ProtocovUSB_ENABLE_MSC_CLASS)
    #if (ProtocovUSB_HANDLE_MSC_REQUESTS)
        uint8 ProtocovUSB_DispatchMSCClassRqst(void) ;
    #endif /* (ProtocovUSB_HANDLE_MSC_REQUESTS) */
#endif /* (ProtocovUSB_ENABLE_MSC_CLASS */

CY_ISR_PROTO(ProtocovUSB_EP_0_ISR);
CY_ISR_PROTO(ProtocovUSB_BUS_RESET_ISR);

#if (ProtocovUSB_SOF_ISR_ACTIVE)
    CY_ISR_PROTO(ProtocovUSB_SOF_ISR);
#endif /* (ProtocovUSB_SOF_ISR_ACTIVE) */

#if (ProtocovUSB_EP1_ISR_ACTIVE)
    CY_ISR_PROTO(ProtocovUSB_EP_1_ISR);
#endif /* (ProtocovUSB_EP1_ISR_ACTIVE) */

#if (ProtocovUSB_EP2_ISR_ACTIVE)
    CY_ISR_PROTO(ProtocovUSB_EP_2_ISR);
#endif /* (ProtocovUSB_EP2_ISR_ACTIVE) */

#if (ProtocovUSB_EP3_ISR_ACTIVE)
    CY_ISR_PROTO(ProtocovUSB_EP_3_ISR);
#endif /* (ProtocovUSB_EP3_ISR_ACTIVE) */

#if (ProtocovUSB_EP4_ISR_ACTIVE)
    CY_ISR_PROTO(ProtocovUSB_EP_4_ISR);
#endif /* (ProtocovUSB_EP4_ISR_ACTIVE) */

#if (ProtocovUSB_EP5_ISR_ACTIVE)
    CY_ISR_PROTO(ProtocovUSB_EP_5_ISR);
#endif /* (ProtocovUSB_EP5_ISR_ACTIVE) */

#if (ProtocovUSB_EP6_ISR_ACTIVE)
    CY_ISR_PROTO(ProtocovUSB_EP_6_ISR);
#endif /* (ProtocovUSB_EP6_ISR_ACTIVE) */

#if (ProtocovUSB_EP7_ISR_ACTIVE)
    CY_ISR_PROTO(ProtocovUSB_EP_7_ISR);
#endif /* (ProtocovUSB_EP7_ISR_ACTIVE) */

#if (ProtocovUSB_EP8_ISR_ACTIVE)
    CY_ISR_PROTO(ProtocovUSB_EP_8_ISR);
#endif /* (ProtocovUSB_EP8_ISR_ACTIVE) */

#if (ProtocovUSB_EP_MANAGEMENT_DMA)
    CY_ISR_PROTO(ProtocovUSB_ARB_ISR);
#endif /* (ProtocovUSB_EP_MANAGEMENT_DMA) */

#if (ProtocovUSB_DP_ISR_ACTIVE)
    CY_ISR_PROTO(ProtocovUSB_DP_ISR);
#endif /* (ProtocovUSB_DP_ISR_ACTIVE) */

#if (CY_PSOC4)
    CY_ISR_PROTO(ProtocovUSB_INTR_HI_ISR);
    CY_ISR_PROTO(ProtocovUSB_INTR_MED_ISR);
    CY_ISR_PROTO(ProtocovUSB_INTR_LO_ISR);
    #if (ProtocovUSB_LPM_ACTIVE)
        CY_ISR_PROTO(ProtocovUSB_LPM_ISR);
    #endif /* (ProtocovUSB_LPM_ACTIVE) */
#endif /* (CY_PSOC4) */

#if (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)
#if (CY_PSOC4)
    #if (ProtocovUSB_DMA1_ACTIVE)
        void ProtocovUSB_EP1_DMA_DONE_ISR(void);
    #endif /* (ProtocovUSB_DMA1_ACTIVE) */

    #if (ProtocovUSB_DMA2_ACTIVE)
        void ProtocovUSB_EP2_DMA_DONE_ISR(void);
    #endif /* (ProtocovUSB_DMA2_ACTIVE) */

    #if (ProtocovUSB_DMA3_ACTIVE)
        void ProtocovUSB_EP3_DMA_DONE_ISR(void);
    #endif /* (ProtocovUSB_DMA3_ACTIVE) */

    #if (ProtocovUSB_DMA4_ACTIVE)
        void ProtocovUSB_EP4_DMA_DONE_ISR(void);
    #endif /* (ProtocovUSB_DMA4_ACTIVE) */

    #if (ProtocovUSB_DMA5_ACTIVE)
        void ProtocovUSB_EP5_DMA_DONE_ISR(void);
    #endif /* (ProtocovUSB_DMA5_ACTIVE) */

    #if (ProtocovUSB_DMA6_ACTIVE)
        void ProtocovUSB_EP6_DMA_DONE_ISR(void);
    #endif /* (ProtocovUSB_DMA6_ACTIVE) */

    #if (ProtocovUSB_DMA7_ACTIVE)
        void ProtocovUSB_EP7_DMA_DONE_ISR(void);
    #endif /* (ProtocovUSB_DMA7_ACTIVE) */

    #if (ProtocovUSB_DMA8_ACTIVE)
        void ProtocovUSB_EP8_DMA_DONE_ISR(void);
    #endif /* (ProtocovUSB_DMA8_ACTIVE) */

#else
    #if (ProtocovUSB_EP_DMA_AUTO_OPT == 0u)
        CY_ISR_PROTO(ProtocovUSB_EP_DMA_DONE_ISR);
    #endif /* (ProtocovUSB_EP_DMA_AUTO_OPT == 0u) */
#endif /* (CY_PSOC4) */
#endif /* (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO) */


/***************************************
*         Request Handlers
***************************************/

uint8 ProtocovUSB_HandleStandardRqst(void) ;
uint8 ProtocovUSB_DispatchClassRqst(void)  ;
uint8 ProtocovUSB_HandleVendorRqst(void)   ;


/***************************************
*    HID Internal references
***************************************/

#if defined(ProtocovUSB_ENABLE_HID_CLASS)
    void ProtocovUSB_FindReport(void)            ;
    void ProtocovUSB_FindReportDescriptor(void)  ;
    void ProtocovUSB_FindHidClassDecriptor(void) ;
#endif /* ProtocovUSB_ENABLE_HID_CLASS */


/***************************************
*    MIDI Internal references
***************************************/

#if defined(ProtocovUSB_ENABLE_MIDI_STREAMING)
    void ProtocovUSB_MIDI_IN_EP_Service(void)  ;
#endif /* (ProtocovUSB_ENABLE_MIDI_STREAMING) */


/***************************************
*    CDC Internal references
***************************************/

#if defined(ProtocovUSB_ENABLE_CDC_CLASS)

    typedef struct
    {
        uint8  bRequestType;
        uint8  bNotification;
        uint8  wValue;
        uint8  wValueMSB;
        uint8  wIndex;
        uint8  wIndexMSB;
        uint8  wLength;
        uint8  wLengthMSB;
        uint8  wSerialState;
        uint8  wSerialStateMSB;
    } t_ProtocovUSB_cdc_notification;

    uint8 ProtocovUSB_GetInterfaceComPort(uint8 interface) ;
    uint8 ProtocovUSB_Cdc_EpInit( const T_ProtocovUSB_EP_SETTINGS_BLOCK CYCODE *pEP, uint8 epNum, uint8 cdcComNums) ;

    extern volatile uint8  ProtocovUSB_cdc_dataInEpList[ProtocovUSB_MAX_MULTI_COM_NUM];
    extern volatile uint8  ProtocovUSB_cdc_dataOutEpList[ProtocovUSB_MAX_MULTI_COM_NUM];
    extern volatile uint8  ProtocovUSB_cdc_commInEpList[ProtocovUSB_MAX_MULTI_COM_NUM];
#endif /* (ProtocovUSB_ENABLE_CDC_CLASS) */


#endif /* CY_USBFS_ProtocovUSB_pvt_H */


/* [] END OF FILE */
