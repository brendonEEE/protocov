/***************************************************************************//**
* \file  ProtocovUSB.h
* \version 3.20
*
* \brief
*  This file provides function prototypes and constants for the USBFS component. 
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_ProtocovUSB_H)
#define CY_USBFS_ProtocovUSB_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"
#include "cyapicallbacks.h"

/*  User supplied definitions. */
/* `#START USER_DEFINITIONS` Place your declaration here */

/* `#END` */

/***************************************
* Enumerated Types and Parameters
***************************************/

/* USB IP memory management options. */
#define ProtocovUSB__EP_MANUAL    (0u)
#define ProtocovUSB__EP_DMAMANUAL (1u)
#define ProtocovUSB__EP_DMAAUTO   (2u)

/* USB IP memory allocation options. */
#define ProtocovUSB__MA_STATIC    (0u)
#define ProtocovUSB__MA_DYNAMIC   (1u)


/***************************************
*    Initial Parameter Constants
***************************************/

#define ProtocovUSB_NUM_DEVICES                (1u)
#define ProtocovUSB_ENABLE_MIDI_CLASS          (0u)
#define ProtocovUSB_ENABLE_MSC_CLASS           (0u)
#define ProtocovUSB_BOS_ENABLE                 (0u)
#define ProtocovUSB_MAX_REPORTID_NUMBER        (0u)

#define ProtocovUSB_MON_VBUS               (0u)
#define ProtocovUSB_EXTERN_VBUS            (1u)
#define ProtocovUSB_POWER_PAD_VBUS         (0u)
#define ProtocovUSB_EXTERN_VND             (0u)
#define ProtocovUSB_EXTERN_CLS             (0u)
#define ProtocovUSB_MAX_INTERFACES_NUMBER  (1u)
#define ProtocovUSB_EP_MM                  (0u)
#define ProtocovUSB_EP_MA                  (0u)
#define ProtocovUSB_ENABLE_BATT_CHARG_DET  (0u)
#define ProtocovUSB_GEN_16BITS_EP_ACCESS   (0u)

/* Enable Class APIs: MIDI, CDC, MSC. */         
#define ProtocovUSB_ENABLE_CDC_CLASS_API   (0u != (1u))

/* General parameters */
#define ProtocovUSB_EP_ALLOC_STATIC            (ProtocovUSB_EP_MA == ProtocovUSB__MA_STATIC)
#define ProtocovUSB_EP_ALLOC_DYNAMIC           (ProtocovUSB_EP_MA == ProtocovUSB__MA_DYNAMIC)
#define ProtocovUSB_EP_MANAGEMENT_MANUAL       (ProtocovUSB_EP_MM == ProtocovUSB__EP_MANUAL)
#define ProtocovUSB_EP_MANAGEMENT_DMA          (ProtocovUSB_EP_MM != ProtocovUSB__EP_MANUAL)
#define ProtocovUSB_EP_MANAGEMENT_DMA_MANUAL   (ProtocovUSB_EP_MM == ProtocovUSB__EP_DMAMANUAL)
#define ProtocovUSB_EP_MANAGEMENT_DMA_AUTO     (ProtocovUSB_EP_MM == ProtocovUSB__EP_DMAAUTO)
#define ProtocovUSB_BATT_CHARG_DET_ENABLE      (CY_PSOC4 && (0u != ProtocovUSB_ENABLE_BATT_CHARG_DET))
#define ProtocovUSB_16BITS_EP_ACCESS_ENABLE    (CY_PSOC4 && (0u != ProtocovUSB_GEN_16BITS_EP_ACCESS))
#define ProtocovUSB_VBUS_MONITORING_ENABLE     (0u != ProtocovUSB_MON_VBUS)
#define ProtocovUSB_VBUS_MONITORING_INTERNAL   (0u == ProtocovUSB_EXTERN_VBUS)
#define ProtocovUSB_VBUS_POWER_PAD_ENABLE      (0u != ProtocovUSB_POWER_PAD_VBUS)

/* Control endpoints availability */
#define ProtocovUSB_SOF_ISR_REMOVE       (1u)
#define ProtocovUSB_BUS_RESET_ISR_REMOVE (0u)
#define ProtocovUSB_EP0_ISR_REMOVE       (0u)
#define ProtocovUSB_ARB_ISR_REMOVE       (0u)
#define ProtocovUSB_DP_ISR_REMOVE        (0u)
#define ProtocovUSB_LPM_REMOVE           (1u)
#define ProtocovUSB_SOF_ISR_ACTIVE       ((0u == ProtocovUSB_SOF_ISR_REMOVE) ? 1u: 0u)
#define ProtocovUSB_BUS_RESET_ISR_ACTIVE ((0u == ProtocovUSB_BUS_RESET_ISR_REMOVE) ? 1u: 0u)
#define ProtocovUSB_EP0_ISR_ACTIVE       ((0u == ProtocovUSB_EP0_ISR_REMOVE) ? 1u: 0u)
#define ProtocovUSB_ARB_ISR_ACTIVE       ((0u == ProtocovUSB_ARB_ISR_REMOVE) ? 1u: 0u)
#define ProtocovUSB_DP_ISR_ACTIVE        ((0u == ProtocovUSB_DP_ISR_REMOVE) ? 1u: 0u)
#define ProtocovUSB_LPM_ACTIVE           ((CY_PSOC4 && (0u == ProtocovUSB_LPM_REMOVE)) ? 1u: 0u)

/* Data endpoints availability */
#define ProtocovUSB_EP1_ISR_REMOVE     (0u)
#define ProtocovUSB_EP2_ISR_REMOVE     (1u)
#define ProtocovUSB_EP3_ISR_REMOVE     (1u)
#define ProtocovUSB_EP4_ISR_REMOVE     (1u)
#define ProtocovUSB_EP5_ISR_REMOVE     (1u)
#define ProtocovUSB_EP6_ISR_REMOVE     (1u)
#define ProtocovUSB_EP7_ISR_REMOVE     (1u)
#define ProtocovUSB_EP8_ISR_REMOVE     (1u)
#define ProtocovUSB_EP1_ISR_ACTIVE     ((0u == ProtocovUSB_EP1_ISR_REMOVE) ? 1u: 0u)
#define ProtocovUSB_EP2_ISR_ACTIVE     ((0u == ProtocovUSB_EP2_ISR_REMOVE) ? 1u: 0u)
#define ProtocovUSB_EP3_ISR_ACTIVE     ((0u == ProtocovUSB_EP3_ISR_REMOVE) ? 1u: 0u)
#define ProtocovUSB_EP4_ISR_ACTIVE     ((0u == ProtocovUSB_EP4_ISR_REMOVE) ? 1u: 0u)
#define ProtocovUSB_EP5_ISR_ACTIVE     ((0u == ProtocovUSB_EP5_ISR_REMOVE) ? 1u: 0u)
#define ProtocovUSB_EP6_ISR_ACTIVE     ((0u == ProtocovUSB_EP6_ISR_REMOVE) ? 1u: 0u)
#define ProtocovUSB_EP7_ISR_ACTIVE     ((0u == ProtocovUSB_EP7_ISR_REMOVE) ? 1u: 0u)
#define ProtocovUSB_EP8_ISR_ACTIVE     ((0u == ProtocovUSB_EP8_ISR_REMOVE) ? 1u: 0u)

#define ProtocovUSB_EP_DMA_AUTO_OPT    ((CY_PSOC4) ? (1u) : (0u))
#define ProtocovUSB_DMA1_REMOVE        (1u)
#define ProtocovUSB_DMA2_REMOVE        (1u)
#define ProtocovUSB_DMA3_REMOVE        (1u)
#define ProtocovUSB_DMA4_REMOVE        (1u)
#define ProtocovUSB_DMA5_REMOVE        (1u)
#define ProtocovUSB_DMA6_REMOVE        (1u)
#define ProtocovUSB_DMA7_REMOVE        (1u)
#define ProtocovUSB_DMA8_REMOVE        (1u)
#define ProtocovUSB_DMA1_ACTIVE        ((0u == ProtocovUSB_DMA1_REMOVE) ? 1u: 0u)
#define ProtocovUSB_DMA2_ACTIVE        ((0u == ProtocovUSB_DMA2_REMOVE) ? 1u: 0u)
#define ProtocovUSB_DMA3_ACTIVE        ((0u == ProtocovUSB_DMA3_REMOVE) ? 1u: 0u)
#define ProtocovUSB_DMA4_ACTIVE        ((0u == ProtocovUSB_DMA4_REMOVE) ? 1u: 0u)
#define ProtocovUSB_DMA5_ACTIVE        ((0u == ProtocovUSB_DMA5_REMOVE) ? 1u: 0u)
#define ProtocovUSB_DMA6_ACTIVE        ((0u == ProtocovUSB_DMA6_REMOVE) ? 1u: 0u)
#define ProtocovUSB_DMA7_ACTIVE        ((0u == ProtocovUSB_DMA7_REMOVE) ? 1u: 0u)
#define ProtocovUSB_DMA8_ACTIVE        ((0u == ProtocovUSB_DMA8_REMOVE) ? 1u: 0u)


/***************************************
*    Data Structures Definition
***************************************/

typedef struct
{
    uint8  attrib;
    uint8  apiEpState;
    uint8  hwEpState;
    uint8  epToggle;
    uint8  addr;
    uint8  epMode;
    uint16 buffOffset;
    uint16 bufferSize;
    uint8  interface;
} T_ProtocovUSB_EP_CTL_BLOCK;

typedef struct
{
    uint8  interface;
    uint8  altSetting;
    uint8  addr;
    uint8  attributes;
    uint16 bufferSize;
    uint8  bMisc;
} T_ProtocovUSB_EP_SETTINGS_BLOCK;

typedef struct
{
    uint8  status;
    uint16 length;
} T_ProtocovUSB_XFER_STATUS_BLOCK;

typedef struct
{
    uint16  count;
    volatile uint8 *pData;
    T_ProtocovUSB_XFER_STATUS_BLOCK *pStatusBlock;
} T_ProtocovUSB_TD;

typedef struct
{
    uint8   c;
    const void *p_list;
} T_ProtocovUSB_LUT;

/* Resume/Suspend API Support */
typedef struct
{
    uint8 enableState;
    uint8 mode;
#if (CY_PSOC4)
    uint8 intrSeiMask;
#endif /* (CY_PSOC4) */
} ProtocovUSB_BACKUP_STRUCT;

/* Number of endpoint 0 data registers. */
#define ProtocovUSB_EP0_DR_MAPPED_REG_CNT  (8u)

/* Structure to access data registers for EP0. */
typedef struct
{
    uint8 epData[ProtocovUSB_EP0_DR_MAPPED_REG_CNT];
} ProtocovUSB_ep0_data_struct;

/* Number of SIE endpoint registers group. */
#define ProtocovUSB_SIE_EP_REG_SIZE   (ProtocovUSB_USB__SIE_EP1_CR0 - \
                                            ProtocovUSB_USB__SIE_EP1_CNT0)

/* Size of gap between SIE endpoint registers groups. */
#define ProtocovUSB_SIE_GAP_CNT        (((ProtocovUSB_USB__SIE_EP2_CNT0 - \
                                             (ProtocovUSB_USB__SIE_EP1_CNT0 + \
                                              ProtocovUSB_SIE_EP_REG_SIZE)) / sizeof(reg8)) - 1u)

/* Structure to access to SIE registers for endpoint. */
typedef struct
{
    uint8 epCnt0;
    uint8 epCnt1;
    uint8 epCr0;
    uint8 gap[ProtocovUSB_SIE_GAP_CNT];
} ProtocovUSB_sie_ep_struct;

/* Number of ARB endpoint registers group. */
#define ProtocovUSB_ARB_EP_REG_SIZE    (ProtocovUSB_USB__ARB_RW1_DR - \
                                             ProtocovUSB_USB__ARB_EP1_CFG)

/* Size of gap between ARB endpoint registers groups. */
#define ProtocovUSB_ARB_GAP_CNT        (((ProtocovUSB_USB__ARB_EP2_CFG - \
                                             (ProtocovUSB_USB__ARB_EP1_CFG + \
                                              ProtocovUSB_ARB_EP_REG_SIZE)) / sizeof(reg8)) - 1u)

/* Structure to access to ARB registers for endpoint. */
typedef struct
{
    uint8 epCfg;
    uint8 epIntEn;
    uint8 epSr;
    uint8 reserved;
    uint8 rwWa;
    uint8 rwWaMsb;
    uint8 rwRa;
    uint8 rwRaMsb;
    uint8 rwDr;
    uint8 gap[ProtocovUSB_ARB_GAP_CNT];
} ProtocovUSB_arb_ep_struct;

#if (CY_PSOC4)
    /* Number of ARB endpoint registers group (16-bits access). */
    #define ProtocovUSB_ARB_EP_REG16_SIZE      (ProtocovUSB_USB__ARB_RW1_DR16 - \
                                                     ProtocovUSB_USB__ARB_RW1_WA16)

    /* Size of gap between ARB endpoint registers groups (16-bits access). */
    #define ProtocovUSB_ARB_EP_REG16_GAP_CNT   (((ProtocovUSB_USB__ARB_RW2_WA16 - \
                                                     (ProtocovUSB_USB__ARB_RW1_WA16 + \
                                                      ProtocovUSB_ARB_EP_REG16_SIZE)) / sizeof(reg8)) - 1u)

    /* Structure to access to ARB registers for endpoint (16-bits access). */
    typedef struct
    {
        uint8 rwWa16;
        uint8 reserved0;
        uint8 rwRa16;
        uint8 reserved1;
        uint8 rwDr16;
        uint8 gap[ProtocovUSB_ARB_EP_REG16_GAP_CNT];
    } ProtocovUSB_arb_ep_reg16_struct;
#endif /* (CY_PSOC4) */

/* Number of endpoint (takes to account that endpoints numbers are 1-8). */
#define ProtocovUSB_NUMBER_EP  (9u)

/* Consoled SIE register groups for endpoints 1-8. */
typedef struct
{
    ProtocovUSB_sie_ep_struct sieEp[ProtocovUSB_NUMBER_EP];
} ProtocovUSB_sie_eps_struct;

/* Consolidate ARB register groups for endpoints 1-8.*/
typedef struct
{
    ProtocovUSB_arb_ep_struct arbEp[ProtocovUSB_NUMBER_EP];
} ProtocovUSB_arb_eps_struct;

#if (CY_PSOC4)
    /* Consolidate ARB register groups for endpoints 1-8 (16-bits access). */
    typedef struct
    {
        ProtocovUSB_arb_ep_reg16_struct arbEp[ProtocovUSB_NUMBER_EP];
    } ProtocovUSB_arb_eps_reg16_struct;
#endif /* (CY_PSOC4) */


/***************************************
*       Function Prototypes
***************************************/
/**
* \addtogroup group_general
* @{
*/
void   ProtocovUSB_InitComponent(uint8 device, uint8 mode) ;
void   ProtocovUSB_Start(uint8 device, uint8 mode)         ;
void   ProtocovUSB_Init(void)                              ;
void   ProtocovUSB_Stop(void)                              ;
uint8  ProtocovUSB_GetConfiguration(void)                  ;
uint8  ProtocovUSB_IsConfigurationChanged(void)            ;
uint8  ProtocovUSB_GetInterfaceSetting(uint8 interfaceNumber) ;
uint8  ProtocovUSB_GetEPState(uint8 epNumber)              ;
uint16 ProtocovUSB_GetEPCount(uint8 epNumber)              ;
void   ProtocovUSB_LoadInEP(uint8 epNumber, const uint8 pData[], uint16 length)
                                                                ;
uint16 ProtocovUSB_ReadOutEP(uint8 epNumber, uint8 pData[], uint16 length)
                                                                ;
void   ProtocovUSB_EnableOutEP(uint8 epNumber)             ;
void   ProtocovUSB_DisableOutEP(uint8 epNumber)            ;
void   ProtocovUSB_Force(uint8 bState)                     ;
uint8  ProtocovUSB_GetEPAckState(uint8 epNumber)           ;
void   ProtocovUSB_SetPowerStatus(uint8 powerStatus)       ;
void   ProtocovUSB_TerminateEP(uint8 epNumber)             ;

uint8 ProtocovUSB_GetDeviceAddress(void) ;

void ProtocovUSB_EnableSofInt(void)  ;
void ProtocovUSB_DisableSofInt(void) ;


#if defined(ProtocovUSB_ENABLE_FWSN_STRING)
    void   ProtocovUSB_SerialNumString(uint8 snString[]) ;
#endif  /* ProtocovUSB_ENABLE_FWSN_STRING */

#if (ProtocovUSB_VBUS_MONITORING_ENABLE)
    uint8  ProtocovUSB_VBusPresent(void) ;
#endif /*  (ProtocovUSB_VBUS_MONITORING_ENABLE) */

#if (ProtocovUSB_16BITS_EP_ACCESS_ENABLE)
    /* PSoC4 specific functions for 16-bit data register access. */
    void   ProtocovUSB_LoadInEP16 (uint8 epNumber, const uint8 pData[], uint16 length);
    uint16 ProtocovUSB_ReadOutEP16(uint8 epNumber,       uint8 pData[], uint16 length);
#endif /* (ProtocovUSB_16BITS_EP_ACCESS_ENABLE) */

#if (ProtocovUSB_BATT_CHARG_DET_ENABLE)
        uint8 ProtocovUSB_Bcd_DetectPortType(void);
#endif /* (ProtocovUSB_BATT_CHARG_DET_ENABLE) */

#if (ProtocovUSB_EP_MANAGEMENT_DMA)
    void ProtocovUSB_InitEP_DMA(uint8 epNumber, const uint8 *pData) ;   
    void ProtocovUSB_Stop_DMA(uint8 epNumber) ;
/** @} general */ 
#endif /* (ProtocovUSB_EP_MANAGEMENT_DMA) */

/**
* \addtogroup group_power
* @{
*/
uint8  ProtocovUSB_CheckActivity(void) ;
void   ProtocovUSB_Suspend(void)       ;
void   ProtocovUSB_Resume(void)        ;
uint8  ProtocovUSB_RWUEnabled(void)    ;

#if (ProtocovUSB_LPM_ACTIVE)
    uint32 ProtocovUSB_Lpm_GetBeslValue(void);
    uint32 ProtocovUSB_Lpm_RemoteWakeUpAllowed(void);
    void   ProtocovUSB_Lpm_SetResponse(uint32 response);
    uint32 ProtocovUSB_Lpm_GetResponse(void);
#endif /* (ProtocovUSB_LPM_ACTIVE) */

/** @} power */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ProtocovUSB) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
/**
* \addtogroup group_bootloader
* @{
*/
    void ProtocovUSB_CyBtldrCommStart(void)        ;
    void ProtocovUSB_CyBtldrCommStop(void)         ;
    void ProtocovUSB_CyBtldrCommReset(void)        ;
    cystatus ProtocovUSB_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 *count, uint8 timeOut) CYSMALL
                                                        ;
    cystatus ProtocovUSB_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 *count, uint8 timeOut) CYSMALL
                                                        ;
/** @} bootloader */

    #define ProtocovUSB_BTLDR_OUT_EP   (0x01u)
    #define ProtocovUSB_BTLDR_IN_EP    (0x02u)

    #define ProtocovUSB_BTLDR_SIZEOF_WRITE_BUFFER  (64u)   /* Endpoint 1 (OUT) buffer size. */
    #define ProtocovUSB_BTLDR_SIZEOF_READ_BUFFER   (64u)   /* Endpoint 2 (IN)  buffer size. */
    #define ProtocovUSB_BTLDR_MAX_PACKET_SIZE      ProtocovUSB_BTLDR_SIZEOF_WRITE_BUFFER

    #define ProtocovUSB_BTLDR_WAIT_1_MS            (1u)    /* Time Out quantity equal 1mS */

    /* Map-specific USB bootloader communication functions to common bootloader functions */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ProtocovUSB)
        #define CyBtldrCommStart        ProtocovUSB_CyBtldrCommStart
        #define CyBtldrCommStop         ProtocovUSB_CyBtldrCommStop
        #define CyBtldrCommReset        ProtocovUSB_CyBtldrCommReset
        #define CyBtldrCommWrite        ProtocovUSB_CyBtldrCommWrite
        #define CyBtldrCommRead         ProtocovUSB_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ProtocovUSB) */
#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/

#define ProtocovUSB_EP0                        (0u)
#define ProtocovUSB_EP1                        (1u)
#define ProtocovUSB_EP2                        (2u)
#define ProtocovUSB_EP3                        (3u)
#define ProtocovUSB_EP4                        (4u)
#define ProtocovUSB_EP5                        (5u)
#define ProtocovUSB_EP6                        (6u)
#define ProtocovUSB_EP7                        (7u)
#define ProtocovUSB_EP8                        (8u)
#define ProtocovUSB_MAX_EP                     (9u)

#define ProtocovUSB_TRUE                       (1u)
#define ProtocovUSB_FALSE                      (0u)

#define ProtocovUSB_NO_EVENT_ALLOWED           (2u)
#define ProtocovUSB_EVENT_PENDING              (1u)
#define ProtocovUSB_NO_EVENT_PENDING           (0u)

#define ProtocovUSB_IN_BUFFER_FULL             ProtocovUSB_NO_EVENT_PENDING
#define ProtocovUSB_IN_BUFFER_EMPTY            ProtocovUSB_EVENT_PENDING
#define ProtocovUSB_OUT_BUFFER_FULL            ProtocovUSB_EVENT_PENDING
#define ProtocovUSB_OUT_BUFFER_EMPTY           ProtocovUSB_NO_EVENT_PENDING

#define ProtocovUSB_FORCE_J                    (0xA0u)
#define ProtocovUSB_FORCE_K                    (0x80u)
#define ProtocovUSB_FORCE_SE0                  (0xC0u)
#define ProtocovUSB_FORCE_NONE                 (0x00u)

#define ProtocovUSB_IDLE_TIMER_RUNNING         (0x02u)
#define ProtocovUSB_IDLE_TIMER_EXPIRED         (0x01u)
#define ProtocovUSB_IDLE_TIMER_INDEFINITE      (0x00u)

#define ProtocovUSB_DEVICE_STATUS_BUS_POWERED  (0x00u)
#define ProtocovUSB_DEVICE_STATUS_SELF_POWERED (0x01u)

#define ProtocovUSB_3V_OPERATION               (0x00u)
#define ProtocovUSB_5V_OPERATION               (0x01u)
#define ProtocovUSB_DWR_POWER_OPERATION        (0x02u)

#define ProtocovUSB_MODE_DISABLE               (0x00u)
#define ProtocovUSB_MODE_NAK_IN_OUT            (0x01u)
#define ProtocovUSB_MODE_STATUS_OUT_ONLY       (0x02u)
#define ProtocovUSB_MODE_STALL_IN_OUT          (0x03u)
#define ProtocovUSB_MODE_RESERVED_0100         (0x04u)
#define ProtocovUSB_MODE_ISO_OUT               (0x05u)
#define ProtocovUSB_MODE_STATUS_IN_ONLY        (0x06u)
#define ProtocovUSB_MODE_ISO_IN                (0x07u)
#define ProtocovUSB_MODE_NAK_OUT               (0x08u)
#define ProtocovUSB_MODE_ACK_OUT               (0x09u)
#define ProtocovUSB_MODE_RESERVED_1010         (0x0Au)
#define ProtocovUSB_MODE_ACK_OUT_STATUS_IN     (0x0Bu)
#define ProtocovUSB_MODE_NAK_IN                (0x0Cu)
#define ProtocovUSB_MODE_ACK_IN                (0x0Du)
#define ProtocovUSB_MODE_RESERVED_1110         (0x0Eu)
#define ProtocovUSB_MODE_ACK_IN_STATUS_OUT     (0x0Fu)
#define ProtocovUSB_MODE_MASK                  (0x0Fu)
#define ProtocovUSB_MODE_STALL_DATA_EP         (0x80u)

#define ProtocovUSB_MODE_ACKD                  (0x10u)
#define ProtocovUSB_MODE_OUT_RCVD              (0x20u)
#define ProtocovUSB_MODE_IN_RCVD               (0x40u)
#define ProtocovUSB_MODE_SETUP_RCVD            (0x80u)

#define ProtocovUSB_RQST_TYPE_MASK             (0x60u)
#define ProtocovUSB_RQST_TYPE_STD              (0x00u)
#define ProtocovUSB_RQST_TYPE_CLS              (0x20u)
#define ProtocovUSB_RQST_TYPE_VND              (0x40u)
#define ProtocovUSB_RQST_DIR_MASK              (0x80u)
#define ProtocovUSB_RQST_DIR_D2H               (0x80u)
#define ProtocovUSB_RQST_DIR_H2D               (0x00u)
#define ProtocovUSB_RQST_RCPT_MASK             (0x03u)
#define ProtocovUSB_RQST_RCPT_DEV              (0x00u)
#define ProtocovUSB_RQST_RCPT_IFC              (0x01u)
#define ProtocovUSB_RQST_RCPT_EP               (0x02u)
#define ProtocovUSB_RQST_RCPT_OTHER            (0x03u)

#if (ProtocovUSB_LPM_ACTIVE)
    #define ProtocovUSB_LPM_REQ_ACK            (0x01u << ProtocovUSB_LPM_CTRL_LPM_ACK_RESP_POS)
    #define ProtocovUSB_LPM_REQ_NACK           (0x00u)
    #define ProtocovUSB_LPM_REQ_NYET           (0x01u << ProtocovUSB_LPM_CTRL_NYET_EN_POS)
#endif /*(ProtocovUSB_LPM_ACTIVE)*/

/* USB Class Codes */
#define ProtocovUSB_CLASS_DEVICE               (0x00u)     /* Use class code info from Interface Descriptors */
#define ProtocovUSB_CLASS_AUDIO                (0x01u)     /* Audio device */
#define ProtocovUSB_CLASS_CDC                  (0x02u)     /* Communication device class */
#define ProtocovUSB_CLASS_HID                  (0x03u)     /* Human Interface Device */
#define ProtocovUSB_CLASS_PDC                  (0x05u)     /* Physical device class */
#define ProtocovUSB_CLASS_IMAGE                (0x06u)     /* Still Imaging device */
#define ProtocovUSB_CLASS_PRINTER              (0x07u)     /* Printer device  */
#define ProtocovUSB_CLASS_MSD                  (0x08u)     /* Mass Storage device  */
#define ProtocovUSB_CLASS_HUB                  (0x09u)     /* Full/Hi speed Hub */
#define ProtocovUSB_CLASS_CDC_DATA             (0x0Au)     /* CDC data device */
#define ProtocovUSB_CLASS_SMART_CARD           (0x0Bu)     /* Smart Card device */
#define ProtocovUSB_CLASS_CSD                  (0x0Du)     /* Content Security device */
#define ProtocovUSB_CLASS_VIDEO                (0x0Eu)     /* Video device */
#define ProtocovUSB_CLASS_PHD                  (0x0Fu)     /* Personal Health care device */
#define ProtocovUSB_CLASS_WIRELESSD            (0xDCu)     /* Wireless Controller */
#define ProtocovUSB_CLASS_MIS                  (0xE0u)     /* Miscellaneous */
#define ProtocovUSB_CLASS_APP                  (0xEFu)     /* Application Specific */
#define ProtocovUSB_CLASS_VENDOR               (0xFFu)     /* Vendor specific */

/* Standard Request Types (Table 9-4) */
#define ProtocovUSB_GET_STATUS                 (0x00u)
#define ProtocovUSB_CLEAR_FEATURE              (0x01u)
#define ProtocovUSB_SET_FEATURE                (0x03u)
#define ProtocovUSB_SET_ADDRESS                (0x05u)
#define ProtocovUSB_GET_DESCRIPTOR             (0x06u)
#define ProtocovUSB_SET_DESCRIPTOR             (0x07u)
#define ProtocovUSB_GET_CONFIGURATION          (0x08u)
#define ProtocovUSB_SET_CONFIGURATION          (0x09u)
#define ProtocovUSB_GET_INTERFACE              (0x0Au)
#define ProtocovUSB_SET_INTERFACE              (0x0Bu)
#define ProtocovUSB_SYNCH_FRAME                (0x0Cu)

/* Vendor Specific Request Types */
/* Request for Microsoft OS String Descriptor */
#define ProtocovUSB_GET_EXTENDED_CONFIG_DESCRIPTOR (0x01u)

/* Descriptor Types (Table 9-5) */
#define ProtocovUSB_DESCR_DEVICE                   (1u)
#define ProtocovUSB_DESCR_CONFIG                   (2u)
#define ProtocovUSB_DESCR_STRING                   (3u)
#define ProtocovUSB_DESCR_INTERFACE                (4u)
#define ProtocovUSB_DESCR_ENDPOINT                 (5u)
#define ProtocovUSB_DESCR_DEVICE_QUALIFIER         (6u)
#define ProtocovUSB_DESCR_OTHER_SPEED              (7u)
#define ProtocovUSB_DESCR_INTERFACE_POWER          (8u)
#if (ProtocovUSB_BOS_ENABLE)
    #define ProtocovUSB_DESCR_BOS                  (15u)
#endif /* (ProtocovUSB_BOS_ENABLE) */
/* Device Descriptor Defines */
#define ProtocovUSB_DEVICE_DESCR_LENGTH            (18u)
#define ProtocovUSB_DEVICE_DESCR_SN_SHIFT          (16u)

/* Config Descriptor Shifts and Masks */
#define ProtocovUSB_CONFIG_DESCR_LENGTH                (0u)
#define ProtocovUSB_CONFIG_DESCR_TYPE                  (1u)
#define ProtocovUSB_CONFIG_DESCR_TOTAL_LENGTH_LOW      (2u)
#define ProtocovUSB_CONFIG_DESCR_TOTAL_LENGTH_HI       (3u)
#define ProtocovUSB_CONFIG_DESCR_NUM_INTERFACES        (4u)
#define ProtocovUSB_CONFIG_DESCR_CONFIG_VALUE          (5u)
#define ProtocovUSB_CONFIG_DESCR_CONFIGURATION         (6u)
#define ProtocovUSB_CONFIG_DESCR_ATTRIB                (7u)
#define ProtocovUSB_CONFIG_DESCR_ATTRIB_SELF_POWERED   (0x40u)
#define ProtocovUSB_CONFIG_DESCR_ATTRIB_RWU_EN         (0x20u)

#if (ProtocovUSB_BOS_ENABLE)
    /* Config Descriptor BOS */
    #define ProtocovUSB_BOS_DESCR_LENGTH               (0u)
    #define ProtocovUSB_BOS_DESCR_TYPE                 (1u)
    #define ProtocovUSB_BOS_DESCR_TOTAL_LENGTH_LOW     (2u)
    #define ProtocovUSB_BOS_DESCR_TOTAL_LENGTH_HI      (3u)
    #define ProtocovUSB_BOS_DESCR_NUM_DEV_CAPS         (4u)
#endif /* (ProtocovUSB_BOS_ENABLE) */

/* Feature Selectors (Table 9-6) */
#define ProtocovUSB_DEVICE_REMOTE_WAKEUP           (0x01u)
#define ProtocovUSB_ENDPOINT_HALT                  (0x00u)
#define ProtocovUSB_TEST_MODE                      (0x02u)

/* USB Device Status (Figure 9-4) */
#define ProtocovUSB_DEVICE_STATUS_BUS_POWERED      (0x00u)
#define ProtocovUSB_DEVICE_STATUS_SELF_POWERED     (0x01u)
#define ProtocovUSB_DEVICE_STATUS_REMOTE_WAKEUP    (0x02u)

/* USB Endpoint Status (Figure 9-4) */
#define ProtocovUSB_ENDPOINT_STATUS_HALT           (0x01u)

/* USB Endpoint Directions */
#define ProtocovUSB_DIR_IN                         (0x80u)
#define ProtocovUSB_DIR_OUT                        (0x00u)
#define ProtocovUSB_DIR_UNUSED                     (0x7Fu)

/* USB Endpoint Attributes */
#define ProtocovUSB_EP_TYPE_CTRL                   (0x00u)
#define ProtocovUSB_EP_TYPE_ISOC                   (0x01u)
#define ProtocovUSB_EP_TYPE_BULK                   (0x02u)
#define ProtocovUSB_EP_TYPE_INT                    (0x03u)
#define ProtocovUSB_EP_TYPE_MASK                   (0x03u)

#define ProtocovUSB_EP_SYNC_TYPE_NO_SYNC           (0x00u)
#define ProtocovUSB_EP_SYNC_TYPE_ASYNC             (0x04u)
#define ProtocovUSB_EP_SYNC_TYPE_ADAPTIVE          (0x08u)
#define ProtocovUSB_EP_SYNC_TYPE_SYNCHRONOUS       (0x0Cu)
#define ProtocovUSB_EP_SYNC_TYPE_MASK              (0x0Cu)

#define ProtocovUSB_EP_USAGE_TYPE_DATA             (0x00u)
#define ProtocovUSB_EP_USAGE_TYPE_FEEDBACK         (0x10u)
#define ProtocovUSB_EP_USAGE_TYPE_IMPLICIT         (0x20u)
#define ProtocovUSB_EP_USAGE_TYPE_RESERVED         (0x30u)
#define ProtocovUSB_EP_USAGE_TYPE_MASK             (0x30u)

/* Point Status defines */
#define ProtocovUSB_EP_STATUS_LENGTH               (0x02u)

/* Point Device defines */
#define ProtocovUSB_DEVICE_STATUS_LENGTH           (0x02u)

#define ProtocovUSB_STATUS_LENGTH_MAX \
                 ((ProtocovUSB_EP_STATUS_LENGTH > ProtocovUSB_DEVICE_STATUS_LENGTH) ? \
                        ProtocovUSB_EP_STATUS_LENGTH : ProtocovUSB_DEVICE_STATUS_LENGTH)

/* Transfer Completion Notification */
#define ProtocovUSB_XFER_IDLE                      (0x00u)
#define ProtocovUSB_XFER_STATUS_ACK                (0x01u)
#define ProtocovUSB_XFER_PREMATURE                 (0x02u)
#define ProtocovUSB_XFER_ERROR                     (0x03u)

/* Driver State defines */
#define ProtocovUSB_TRANS_STATE_IDLE               (0x00u)
#define ProtocovUSB_TRANS_STATE_CONTROL_READ       (0x02u)
#define ProtocovUSB_TRANS_STATE_CONTROL_WRITE      (0x04u)
#define ProtocovUSB_TRANS_STATE_NO_DATA_CONTROL    (0x06u)

/* String Descriptor defines */
#define ProtocovUSB_STRING_MSOS                    (0xEEu)
#define ProtocovUSB_MSOS_DESCRIPTOR_LENGTH         (18u)
#define ProtocovUSB_MSOS_CONF_DESCR_LENGTH         (40u)

/* Return values */
#define ProtocovUSB_BCD_PORT_SDP       (1u) /* Standard downstream port detected */
#define ProtocovUSB_BCD_PORT_CDP       (2u) /* Charging downstream port detected */
#define ProtocovUSB_BCD_PORT_DCP       (3u) /* Dedicated charging port detected */
#define ProtocovUSB_BCD_PORT_UNKNOWN   (0u) /* Unable to detect charging port */
#define ProtocovUSB_BCD_PORT_ERR       (4u) /* Error condition in detection process*/


/* Timeouts for BCD */
#define ProtocovUSB_BCD_TIMEOUT                (400u)  /* Copied from PBK#163 TIMEOUT (300 ms) */
#define ProtocovUSB_BCD_TDCD_DBNC              (10u)  /*BCD v1.2: DCD debounce time 10 ms*/
#define ProtocovUSB_BCD_PRIMARY_WAIT           (40u)   /* Copied from PBK#163 TIMEOUT (40 ms)  */
#define ProtocovUSB_BCD_SECONDARY_WAIT         (47u)   /* Copied from PBK#163 TIMEOUT (40 ms)  */
#define ProtocovUSB_BCD_SUSPEND_DISABLE_WAIT   (2u)    /* Copied from PBK#163 TIMEOUT (2 us)   */

/* Wait cycles required before clearing SUSPEND_DEL in POWER_CTRL: 2us */
#define ProtocovUSB_WAIT_SUSPEND_DEL_DISABLE   (2u)

/* Wait cycles required for USB regulator stabilization after it is enabled : 50ns */
#define ProtocovUSB_WAIT_VREF_STABILITY        (0u)

#if (CY_PSOC3 || CY_PSOC5LP)
/* Wait cycles required for USB reference restore: 40us */
#define ProtocovUSB_WAIT_VREF_RESTORE          (40u)

/* Wait cycles required for stabilization after register is written : 50ns */
#define ProtocovUSB_WAIT_REG_STABILITY_50NS    (0u)
#define ProtocovUSB_WAIT_REG_STABILITY_1US     (1u)

/* Wait cycles required after CR0 register write: 1 cycle */
#define ProtocovUSB_WAIT_CR0_REG_STABILITY     (1u)

/* Wait cycles required after PD_PULLUP_N bit is set in PM_USB_CR0: 2us */
#define ProtocovUSB_WAIT_PD_PULLUP_N_ENABLE    (2u)
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

#if (CY_PSOC4)
    #if (ProtocovUSB_EP_MANAGEMENT_DMA)
        #define ProtocovUSB_DMA_DESCR0         (0u)
        #define ProtocovUSB_DMA_DESCR1         (1u)
    #endif /* (ProtocovUSB_EP_MANAGEMENT_DMA) */

    #if (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)
        /* BUF_SIZE-BYTES_PER_BURST examples: 0x55 - 32 bytes, 0x44 - 16 bytes, 0x33 - 8 bytes, etc. */
        #define ProtocovUSB_DMA_BUF_SIZE             (0x55u)
        #define ProtocovUSB_DMA_BYTES_PER_BURST      (32u)
        #define ProtocovUSB_DMA_HALFWORDS_PER_BURST  (16u)
        #define ProtocovUSB_DMA_BURST_BYTES_MASK     (ProtocovUSB_DMA_BYTES_PER_BURST - 1u)

        #define ProtocovUSB_DMA_DESCR0_MASK        (0x00u)
        #define ProtocovUSB_DMA_DESCR1_MASK        (0x80u)
        #define ProtocovUSB_DMA_DESCR_REVERT       (0x40u)
        #define ProtocovUSB_DMA_DESCR_16BITS       (0x20u)
        #define ProtocovUSB_DMA_DESCR_SHIFT        (7u)

        #define ProtocovUSB_DMA_GET_DESCR_NUM(desrc)
        #define ProtocovUSB_DMA_GET_BURST_CNT(dmaBurstCnt) \
                    (((dmaBurstCnt) > 2u)? ((dmaBurstCnt) - 2u) : 0u)

        #define ProtocovUSB_DMA_GET_MAX_ELEM_PER_BURST(dmaLastBurstEl) \
                    ((0u != ((dmaLastBurstEl) & ProtocovUSB_DMA_DESCR_16BITS)) ? \
                                (ProtocovUSB_DMA_HALFWORDS_PER_BURST - 1u) : (ProtocovUSB_DMA_BYTES_PER_BURST - 1u))
    #endif /* (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO) */
#else
    #if (ProtocovUSB_EP_MANAGEMENT_DMA_MANUAL)
        #define ProtocovUSB_DMA_BYTES_PER_BURST    (0u)
        #define ProtocovUSB_DMA_REQUEST_PER_BURST  (0u)
    #endif /* (ProtocovUSB_EP_MANAGEMENT_DMA_MANUAL) */

    #if (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)
        #define ProtocovUSB_DMA_BYTES_PER_BURST    (32u)
        #define ProtocovUSB_DMA_BYTES_REPEAT       (2u)

        /* BUF_SIZE-BYTES_PER_BURST examples: 0x55 - 32 bytes, 0x44 - 16 bytes, 0x33 - 8 bytes, etc. */
        #define ProtocovUSB_DMA_BUF_SIZE           (0x55u)
        #define ProtocovUSB_DMA_REQUEST_PER_BURST  (1u)

        #define ProtocovUSB_EP17_SR_MASK           (0x7Fu)
        #define ProtocovUSB_EP8_SR_MASK            (0x03u)
    #endif /* (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO) */
#endif /* (CY_PSOC4) */

/* DIE ID string descriptor defines */
#if defined(ProtocovUSB_ENABLE_IDSN_STRING)
    #define ProtocovUSB_IDSN_DESCR_LENGTH      (0x22u)
#endif /* (ProtocovUSB_ENABLE_IDSN_STRING) */


/***************************************
*     Vars with External Linkage
***************************************/

/**
* \addtogroup group_globals
* @{
*/
extern uint8 ProtocovUSB_initVar;
extern volatile uint8 ProtocovUSB_device;
extern volatile uint8 ProtocovUSB_transferState;
extern volatile uint8 ProtocovUSB_configuration;
extern volatile uint8 ProtocovUSB_configurationChanged;
extern volatile uint8 ProtocovUSB_deviceStatus;
/** @} globals */

/**
* \addtogroup group_hid
* @{
*/
/* HID Variables */
#if defined(ProtocovUSB_ENABLE_HID_CLASS)
    extern volatile uint8 ProtocovUSB_hidProtocol [ProtocovUSB_MAX_INTERFACES_NUMBER]; 
    extern volatile uint8 ProtocovUSB_hidIdleRate [ProtocovUSB_MAX_INTERFACES_NUMBER];
    extern volatile uint8 ProtocovUSB_hidIdleTimer[ProtocovUSB_MAX_INTERFACES_NUMBER];
#endif /* (ProtocovUSB_ENABLE_HID_CLASS) */
/** @} hid */


/***************************************
*              Registers
***************************************/

/* Common registers for all PSoCs: 3/4/5LP */
#define ProtocovUSB_ARB_CFG_PTR        ( (reg8 *) ProtocovUSB_USB__ARB_CFG)
#define ProtocovUSB_ARB_CFG_REG        (*(reg8 *) ProtocovUSB_USB__ARB_CFG)

#define ProtocovUSB_ARB_EP1_CFG_PTR    ( (reg8 *) ProtocovUSB_USB__ARB_EP1_CFG)
#define ProtocovUSB_ARB_EP1_CFG_REG    (*(reg8 *) ProtocovUSB_USB__ARB_EP1_CFG)
#define ProtocovUSB_ARB_EP1_INT_EN_PTR ( (reg8 *) ProtocovUSB_USB__ARB_EP1_INT_EN)
#define ProtocovUSB_ARB_EP1_INT_EN_REG (*(reg8 *) ProtocovUSB_USB__ARB_EP1_INT_EN)
#define ProtocovUSB_ARB_EP1_SR_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_EP1_SR)
#define ProtocovUSB_ARB_EP1_SR_REG     (*(reg8 *) ProtocovUSB_USB__ARB_EP1_SR)
#define ProtocovUSB_ARB_EP1_CFG_IND    ProtocovUSB_USB__ARB_EP1_CFG
#define ProtocovUSB_ARB_EP1_INT_EN_IND ProtocovUSB_USB__ARB_EP1_INT_EN
#define ProtocovUSB_ARB_EP1_SR_IND     ProtocovUSB_USB__ARB_EP1_SR
#define ProtocovUSB_ARB_EP_BASE        (*(volatile ProtocovUSB_arb_eps_struct CYXDATA *) \
                                            (ProtocovUSB_USB__ARB_EP1_CFG - sizeof(ProtocovUSB_arb_ep_struct)))

#define ProtocovUSB_ARB_EP2_CFG_PTR    ( (reg8 *) ProtocovUSB_USB__ARB_EP2_CFG)
#define ProtocovUSB_ARB_EP2_CFG_REG    (*(reg8 *) ProtocovUSB_USB__ARB_EP2_CFG)
#define ProtocovUSB_ARB_EP2_INT_EN_PTR ( (reg8 *) ProtocovUSB_USB__ARB_EP2_INT_EN)
#define ProtocovUSB_ARB_EP2_INT_EN_REG (*(reg8 *) ProtocovUSB_USB__ARB_EP2_INT_EN)
#define ProtocovUSB_ARB_EP2_SR_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_EP2_SR)
#define ProtocovUSB_ARB_EP2_SR_REG     (*(reg8 *) ProtocovUSB_USB__ARB_EP2_SR)

#define ProtocovUSB_ARB_EP3_CFG_PTR    ( (reg8 *) ProtocovUSB_USB__ARB_EP3_CFG)
#define ProtocovUSB_ARB_EP3_CFG_REG    (*(reg8 *) ProtocovUSB_USB__ARB_EP3_CFG)
#define ProtocovUSB_ARB_EP3_INT_EN_PTR ( (reg8 *) ProtocovUSB_USB__ARB_EP3_INT_EN)
#define ProtocovUSB_ARB_EP3_INT_EN_REG (*(reg8 *) ProtocovUSB_USB__ARB_EP3_INT_EN)
#define ProtocovUSB_ARB_EP3_SR_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_EP3_SR)
#define ProtocovUSB_ARB_EP3_SR_REG     (*(reg8 *) ProtocovUSB_USB__ARB_EP3_SR)

#define ProtocovUSB_ARB_EP4_CFG_PTR    ( (reg8 *) ProtocovUSB_USB__ARB_EP4_CFG)
#define ProtocovUSB_ARB_EP4_CFG_REG    (*(reg8 *) ProtocovUSB_USB__ARB_EP4_CFG)
#define ProtocovUSB_ARB_EP4_INT_EN_PTR ( (reg8 *) ProtocovUSB_USB__ARB_EP4_INT_EN)
#define ProtocovUSB_ARB_EP4_INT_EN_REG (*(reg8 *) ProtocovUSB_USB__ARB_EP4_INT_EN)
#define ProtocovUSB_ARB_EP4_SR_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_EP4_SR)
#define ProtocovUSB_ARB_EP4_SR_REG     (*(reg8 *) ProtocovUSB_USB__ARB_EP4_SR)

#define ProtocovUSB_ARB_EP5_CFG_PTR    ( (reg8 *) ProtocovUSB_USB__ARB_EP5_CFG)
#define ProtocovUSB_ARB_EP5_CFG_REG    (*(reg8 *) ProtocovUSB_USB__ARB_EP5_CFG)
#define ProtocovUSB_ARB_EP5_INT_EN_PTR ( (reg8 *) ProtocovUSB_USB__ARB_EP5_INT_EN)
#define ProtocovUSB_ARB_EP5_INT_EN_REG (*(reg8 *) ProtocovUSB_USB__ARB_EP5_INT_EN)
#define ProtocovUSB_ARB_EP5_SR_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_EP5_SR)
#define ProtocovUSB_ARB_EP5_SR_REG     (*(reg8 *) ProtocovUSB_USB__ARB_EP5_SR)

#define ProtocovUSB_ARB_EP6_CFG_PTR    ( (reg8 *) ProtocovUSB_USB__ARB_EP6_CFG)
#define ProtocovUSB_ARB_EP6_CFG_REG    (*(reg8 *) ProtocovUSB_USB__ARB_EP6_CFG)
#define ProtocovUSB_ARB_EP6_INT_EN_PTR ( (reg8 *) ProtocovUSB_USB__ARB_EP6_INT_EN)
#define ProtocovUSB_ARB_EP6_INT_EN_REG (*(reg8 *) ProtocovUSB_USB__ARB_EP6_INT_EN)
#define ProtocovUSB_ARB_EP6_SR_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_EP6_SR)
#define ProtocovUSB_ARB_EP6_SR_REG     (*(reg8 *) ProtocovUSB_USB__ARB_EP6_SR)

#define ProtocovUSB_ARB_EP7_CFG_PTR    ( (reg8 *) ProtocovUSB_USB__ARB_EP7_CFG)
#define ProtocovUSB_ARB_EP7_CFG_REG    (*(reg8 *) ProtocovUSB_USB__ARB_EP7_CFG)
#define ProtocovUSB_ARB_EP7_INT_EN_PTR ( (reg8 *) ProtocovUSB_USB__ARB_EP7_INT_EN)
#define ProtocovUSB_ARB_EP7_INT_EN_REG (*(reg8 *) ProtocovUSB_USB__ARB_EP7_INT_EN)
#define ProtocovUSB_ARB_EP7_SR_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_EP7_SR)
#define ProtocovUSB_ARB_EP7_SR_REG     (*(reg8 *) ProtocovUSB_USB__ARB_EP7_SR)

#define ProtocovUSB_ARB_EP8_CFG_PTR    ( (reg8 *) ProtocovUSB_USB__ARB_EP8_CFG)
#define ProtocovUSB_ARB_EP8_CFG_REG    (*(reg8 *) ProtocovUSB_USB__ARB_EP8_CFG)
#define ProtocovUSB_ARB_EP8_INT_EN_PTR ( (reg8 *) ProtocovUSB_USB__ARB_EP8_INT_EN)
#define ProtocovUSB_ARB_EP8_INT_EN_REG (*(reg8 *) ProtocovUSB_USB__ARB_EP8_INT_EN)
#define ProtocovUSB_ARB_EP8_SR_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_EP8_SR)
#define ProtocovUSB_ARB_EP8_SR_REG     (*(reg8 *) ProtocovUSB_USB__ARB_EP8_SR)

#define ProtocovUSB_ARB_INT_EN_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_INT_EN)
#define ProtocovUSB_ARB_INT_EN_REG     (*(reg8 *) ProtocovUSB_USB__ARB_INT_EN)
#define ProtocovUSB_ARB_INT_SR_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_INT_SR)
#define ProtocovUSB_ARB_INT_SR_REG     (*(reg8 *) ProtocovUSB_USB__ARB_INT_SR)

#define ProtocovUSB_ARB_RW1_DR_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_RW1_DR)
#define ProtocovUSB_ARB_RW1_RA_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_RW1_RA)

#define ProtocovUSB_ARB_RW1_RA_MSB_PTR ( (reg8 *) ProtocovUSB_USB__ARB_RW1_RA_MSB)
#define ProtocovUSB_ARB_RW1_WA_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_RW1_WA)
#define ProtocovUSB_ARB_RW1_WA_MSB_PTR ( (reg8 *) ProtocovUSB_USB__ARB_RW1_WA_MSB)
#define ProtocovUSB_ARB_RW1_DR_IND     ProtocovUSB_USB__ARB_RW1_DR
#define ProtocovUSB_ARB_RW1_RA_IND     ProtocovUSB_USB__ARB_RW1_RA
#define ProtocovUSB_ARB_RW1_RA_MSB_IND ProtocovUSB_USB__ARB_RW1_RA_MSB
#define ProtocovUSB_ARB_RW1_WA_IND     ProtocovUSB_USB__ARB_RW1_WA
#define ProtocovUSB_ARB_RW1_WA_MSB_IND ProtocovUSB_USB__ARB_RW1_WA_MSB

#define ProtocovUSB_ARB_RW2_DR_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_RW2_DR)
#define ProtocovUSB_ARB_RW2_RA_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_RW2_RA)
#define ProtocovUSB_ARB_RW2_RA_MSB_PTR ( (reg8 *) ProtocovUSB_USB__ARB_RW2_RA_MSB)
#define ProtocovUSB_ARB_RW2_WA_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_RW2_WA)
#define ProtocovUSB_ARB_RW2_WA_MSB_PTR ( (reg8 *) ProtocovUSB_USB__ARB_RW2_WA_MSB)

#define ProtocovUSB_ARB_RW3_DR_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_RW3_DR)
#define ProtocovUSB_ARB_RW3_RA_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_RW3_RA)
#define ProtocovUSB_ARB_RW3_RA_MSB_PTR ( (reg8 *) ProtocovUSB_USB__ARB_RW3_RA_MSB)
#define ProtocovUSB_ARB_RW3_WA_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_RW3_WA)
#define ProtocovUSB_ARB_RW3_WA_MSB_PTR ( (reg8 *) ProtocovUSB_USB__ARB_RW3_WA_MSB)

#define ProtocovUSB_ARB_RW4_DR_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_RW4_DR)
#define ProtocovUSB_ARB_RW4_RA_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_RW4_RA)
#define ProtocovUSB_ARB_RW4_RA_MSB_PTR ( (reg8 *) ProtocovUSB_USB__ARB_RW4_RA_MSB)
#define ProtocovUSB_ARB_RW4_WA_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_RW4_WA)
#define ProtocovUSB_ARB_RW4_WA_MSB_PTR ( (reg8 *) ProtocovUSB_USB__ARB_RW4_WA_MSB)

#define ProtocovUSB_ARB_RW5_DR_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_RW5_DR)
#define ProtocovUSB_ARB_RW5_RA_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_RW5_RA)
#define ProtocovUSB_ARB_RW5_RA_MSB_PTR ( (reg8 *) ProtocovUSB_USB__ARB_RW5_RA_MSB)
#define ProtocovUSB_ARB_RW5_WA_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_RW5_WA)
#define ProtocovUSB_ARB_RW5_WA_MSB_PTR ( (reg8 *) ProtocovUSB_USB__ARB_RW5_WA_MSB)

#define ProtocovUSB_ARB_RW6_DR_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_RW6_DR)
#define ProtocovUSB_ARB_RW6_RA_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_RW6_RA)
#define ProtocovUSB_ARB_RW6_RA_MSB_PTR ( (reg8 *) ProtocovUSB_USB__ARB_RW6_RA_MSB)
#define ProtocovUSB_ARB_RW6_WA_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_RW6_WA)
#define ProtocovUSB_ARB_RW6_WA_MSB_PTR ( (reg8 *) ProtocovUSB_USB__ARB_RW6_WA_MSB)

#define ProtocovUSB_ARB_RW7_DR_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_RW7_DR)
#define ProtocovUSB_ARB_RW7_RA_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_RW7_RA)
#define ProtocovUSB_ARB_RW7_RA_MSB_PTR ( (reg8 *) ProtocovUSB_USB__ARB_RW7_RA_MSB)
#define ProtocovUSB_ARB_RW7_WA_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_RW7_WA)
#define ProtocovUSB_ARB_RW7_WA_MSB_PTR ( (reg8 *) ProtocovUSB_USB__ARB_RW7_WA_MSB)

#define ProtocovUSB_ARB_RW8_DR_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_RW8_DR)
#define ProtocovUSB_ARB_RW8_RA_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_RW8_RA)
#define ProtocovUSB_ARB_RW8_RA_MSB_PTR ( (reg8 *) ProtocovUSB_USB__ARB_RW8_RA_MSB)
#define ProtocovUSB_ARB_RW8_WA_PTR     ( (reg8 *) ProtocovUSB_USB__ARB_RW8_WA)
#define ProtocovUSB_ARB_RW8_WA_MSB_PTR ( (reg8 *) ProtocovUSB_USB__ARB_RW8_WA_MSB)

#define ProtocovUSB_BUF_SIZE_PTR       ( (reg8 *) ProtocovUSB_USB__BUF_SIZE)
#define ProtocovUSB_BUF_SIZE_REG       (*(reg8 *) ProtocovUSB_USB__BUF_SIZE)
#define ProtocovUSB_BUS_RST_CNT_PTR    ( (reg8 *) ProtocovUSB_USB__BUS_RST_CNT)
#define ProtocovUSB_BUS_RST_CNT_REG    (*(reg8 *) ProtocovUSB_USB__BUS_RST_CNT)
#define ProtocovUSB_CWA_PTR            ( (reg8 *) ProtocovUSB_USB__CWA)
#define ProtocovUSB_CWA_REG            (*(reg8 *) ProtocovUSB_USB__CWA)
#define ProtocovUSB_CWA_MSB_PTR        ( (reg8 *) ProtocovUSB_USB__CWA_MSB)
#define ProtocovUSB_CWA_MSB_REG        (*(reg8 *) ProtocovUSB_USB__CWA_MSB)
#define ProtocovUSB_CR0_PTR            ( (reg8 *) ProtocovUSB_USB__CR0)
#define ProtocovUSB_CR0_REG            (*(reg8 *) ProtocovUSB_USB__CR0)
#define ProtocovUSB_CR1_PTR            ( (reg8 *) ProtocovUSB_USB__CR1)
#define ProtocovUSB_CR1_REG            (*(reg8 *) ProtocovUSB_USB__CR1)

#define ProtocovUSB_DMA_THRES_PTR      ( (reg8 *) ProtocovUSB_USB__DMA_THRES)
#define ProtocovUSB_DMA_THRES_REG      (*(reg8 *) ProtocovUSB_USB__DMA_THRES)
#define ProtocovUSB_DMA_THRES_MSB_PTR  ( (reg8 *) ProtocovUSB_USB__DMA_THRES_MSB)
#define ProtocovUSB_DMA_THRES_MSB_REG  (*(reg8 *) ProtocovUSB_USB__DMA_THRES_MSB)

#define ProtocovUSB_EP_ACTIVE_PTR      ( (reg8 *) ProtocovUSB_USB__EP_ACTIVE)
#define ProtocovUSB_EP_ACTIVE_REG      (*(reg8 *) ProtocovUSB_USB__EP_ACTIVE)
#define ProtocovUSB_EP_TYPE_PTR        ( (reg8 *) ProtocovUSB_USB__EP_TYPE)
#define ProtocovUSB_EP_TYPE_REG        (*(reg8 *) ProtocovUSB_USB__EP_TYPE)

#define ProtocovUSB_EP0_CNT_PTR        ( (reg8 *) ProtocovUSB_USB__EP0_CNT)
#define ProtocovUSB_EP0_CNT_REG        (*(reg8 *) ProtocovUSB_USB__EP0_CNT)
#define ProtocovUSB_EP0_CR_PTR         ( (reg8 *) ProtocovUSB_USB__EP0_CR)
#define ProtocovUSB_EP0_CR_REG         (*(reg8 *) ProtocovUSB_USB__EP0_CR)
#define ProtocovUSB_EP0_DR0_PTR        ( (reg8 *) ProtocovUSB_USB__EP0_DR0)
#define ProtocovUSB_EP0_DR0_REG        (*(reg8 *) ProtocovUSB_USB__EP0_DR0)
#define ProtocovUSB_EP0_DR1_PTR        ( (reg8 *) ProtocovUSB_USB__EP0_DR1)
#define ProtocovUSB_EP0_DR1_REG        (*(reg8 *) ProtocovUSB_USB__EP0_DR1)
#define ProtocovUSB_EP0_DR2_PTR        ( (reg8 *) ProtocovUSB_USB__EP0_DR2)
#define ProtocovUSB_EP0_DR2_REG        (*(reg8 *) ProtocovUSB_USB__EP0_DR2)
#define ProtocovUSB_EP0_DR3_PTR        ( (reg8 *) ProtocovUSB_USB__EP0_DR3)
#define ProtocovUSB_EP0_DR3_REG        (*(reg8 *) ProtocovUSB_USB__EP0_DR3)
#define ProtocovUSB_EP0_DR4_PTR        ( (reg8 *) ProtocovUSB_USB__EP0_DR4)
#define ProtocovUSB_EP0_DR4_REG        (*(reg8 *) ProtocovUSB_USB__EP0_DR4)
#define ProtocovUSB_EP0_DR5_PTR        ( (reg8 *) ProtocovUSB_USB__EP0_DR5)
#define ProtocovUSB_EP0_DR5_REG        (*(reg8 *) ProtocovUSB_USB__EP0_DR5)
#define ProtocovUSB_EP0_DR6_PTR        ( (reg8 *) ProtocovUSB_USB__EP0_DR6)
#define ProtocovUSB_EP0_DR6_REG        (*(reg8 *) ProtocovUSB_USB__EP0_DR6)
#define ProtocovUSB_EP0_DR7_PTR        ( (reg8 *) ProtocovUSB_USB__EP0_DR7)
#define ProtocovUSB_EP0_DR7_REG        (*(reg8 *) ProtocovUSB_USB__EP0_DR7)
#define ProtocovUSB_EP0_DR0_IND        ProtocovUSB_USB__EP0_DR0
#define ProtocovUSB_EP0_DR_BASE        (*(volatile ProtocovUSB_ep0_data_struct CYXDATA *) ProtocovUSB_USB__EP0_DR0)

#define ProtocovUSB_OSCLK_DR0_PTR      ( (reg8 *) ProtocovUSB_USB__OSCLK_DR0)
#define ProtocovUSB_OSCLK_DR0_REG      (*(reg8 *) ProtocovUSB_USB__OSCLK_DR0)
#define ProtocovUSB_OSCLK_DR1_PTR      ( (reg8 *) ProtocovUSB_USB__OSCLK_DR1)
#define ProtocovUSB_OSCLK_DR1_REG      (*(reg8 *) ProtocovUSB_USB__OSCLK_DR1)

#define ProtocovUSB_SIE_EP_INT_EN_PTR  ( (reg8 *) ProtocovUSB_USB__SIE_EP_INT_EN)
#define ProtocovUSB_SIE_EP_INT_EN_REG  (*(reg8 *) ProtocovUSB_USB__SIE_EP_INT_EN)
#define ProtocovUSB_SIE_EP_INT_SR_PTR  ( (reg8 *) ProtocovUSB_USB__SIE_EP_INT_SR)
#define ProtocovUSB_SIE_EP_INT_SR_REG  (*(reg8 *) ProtocovUSB_USB__SIE_EP_INT_SR)

#define ProtocovUSB_SIE_EP1_CNT0_PTR   ( (reg8 *) ProtocovUSB_USB__SIE_EP1_CNT0)
#define ProtocovUSB_SIE_EP1_CNT0_REG   (*(reg8 *) ProtocovUSB_USB__SIE_EP1_CNT0)
#define ProtocovUSB_SIE_EP1_CNT1_PTR   ( (reg8 *) ProtocovUSB_USB__SIE_EP1_CNT1)
#define ProtocovUSB_SIE_EP1_CNT1_REG   (*(reg8 *) ProtocovUSB_USB__SIE_EP1_CNT1)
#define ProtocovUSB_SIE_EP1_CR0_PTR    ( (reg8 *) ProtocovUSB_USB__SIE_EP1_CR0)
#define ProtocovUSB_SIE_EP1_CR0_REG    (*(reg8 *) ProtocovUSB_USB__SIE_EP1_CR0)
#define ProtocovUSB_SIE_EP1_CNT1_IND   ProtocovUSB_USB__SIE_EP1_CNT1
#define ProtocovUSB_SIE_EP1_CNT0_IND   ProtocovUSB_USB__SIE_EP1_CNT0
#define ProtocovUSB_SIE_EP1_CR0_IND    ProtocovUSB_USB__SIE_EP1_CR0
#define ProtocovUSB_SIE_EP_BASE        (*(volatile ProtocovUSB_sie_eps_struct CYXDATA *) \
                                            (ProtocovUSB_USB__SIE_EP1_CNT0 - sizeof(ProtocovUSB_sie_ep_struct)))

#define ProtocovUSB_SIE_EP2_CNT0_PTR   ( (reg8 *) ProtocovUSB_USB__SIE_EP2_CNT0)
#define ProtocovUSB_SIE_EP2_CNT0_REG   (*(reg8 *) ProtocovUSB_USB__SIE_EP2_CNT0)
#define ProtocovUSB_SIE_EP2_CNT1_PTR   ( (reg8 *) ProtocovUSB_USB__SIE_EP2_CNT1)
#define ProtocovUSB_SIE_EP2_CNT1_REG   (*(reg8 *) ProtocovUSB_USB__SIE_EP2_CNT1)
#define ProtocovUSB_SIE_EP2_CR0_PTR    ( (reg8 *) ProtocovUSB_USB__SIE_EP2_CR0)
#define ProtocovUSB_SIE_EP2_CR0_REG    (*(reg8 *) ProtocovUSB_USB__SIE_EP2_CR0)

#define ProtocovUSB_SIE_EP3_CNT0_PTR   ( (reg8 *) ProtocovUSB_USB__SIE_EP3_CNT0)
#define ProtocovUSB_SIE_EP3_CNT0_REG   (*(reg8 *) ProtocovUSB_USB__SIE_EP3_CNT0)
#define ProtocovUSB_SIE_EP3_CNT1_PTR   ( (reg8 *) ProtocovUSB_USB__SIE_EP3_CNT1)
#define ProtocovUSB_SIE_EP3_CNT1_REG   (*(reg8 *) ProtocovUSB_USB__SIE_EP3_CNT1)
#define ProtocovUSB_SIE_EP3_CR0_PTR    ( (reg8 *) ProtocovUSB_USB__SIE_EP3_CR0)
#define ProtocovUSB_SIE_EP3_CR0_REG    (*(reg8 *) ProtocovUSB_USB__SIE_EP3_CR0)

#define ProtocovUSB_SIE_EP4_CNT0_PTR   ( (reg8 *) ProtocovUSB_USB__SIE_EP4_CNT0)
#define ProtocovUSB_SIE_EP4_CNT0_REG   (*(reg8 *) ProtocovUSB_USB__SIE_EP4_CNT0)
#define ProtocovUSB_SIE_EP4_CNT1_PTR   ( (reg8 *) ProtocovUSB_USB__SIE_EP4_CNT1)
#define ProtocovUSB_SIE_EP4_CNT1_REG   (*(reg8 *) ProtocovUSB_USB__SIE_EP4_CNT1)
#define ProtocovUSB_SIE_EP4_CR0_PTR    ( (reg8 *) ProtocovUSB_USB__SIE_EP4_CR0)
#define ProtocovUSB_SIE_EP4_CR0_REG    (*(reg8 *) ProtocovUSB_USB__SIE_EP4_CR0)

#define ProtocovUSB_SIE_EP5_CNT0_PTR   ( (reg8 *) ProtocovUSB_USB__SIE_EP5_CNT0)
#define ProtocovUSB_SIE_EP5_CNT0_REG   (*(reg8 *) ProtocovUSB_USB__SIE_EP5_CNT0)
#define ProtocovUSB_SIE_EP5_CNT1_PTR   ( (reg8 *) ProtocovUSB_USB__SIE_EP5_CNT1)
#define ProtocovUSB_SIE_EP5_CNT1_REG   (*(reg8 *) ProtocovUSB_USB__SIE_EP5_CNT1)
#define ProtocovUSB_SIE_EP5_CR0_PTR    ( (reg8 *) ProtocovUSB_USB__SIE_EP5_CR0)
#define ProtocovUSB_SIE_EP5_CR0_REG    (*(reg8 *) ProtocovUSB_USB__SIE_EP5_CR0)

#define ProtocovUSB_SIE_EP6_CNT0_PTR   ( (reg8 *) ProtocovUSB_USB__SIE_EP6_CNT0)
#define ProtocovUSB_SIE_EP6_CNT0_REG   (*(reg8 *) ProtocovUSB_USB__SIE_EP6_CNT0)
#define ProtocovUSB_SIE_EP6_CNT1_PTR   ( (reg8 *) ProtocovUSB_USB__SIE_EP6_CNT1)
#define ProtocovUSB_SIE_EP6_CNT1_REG   (*(reg8 *) ProtocovUSB_USB__SIE_EP6_CNT1)
#define ProtocovUSB_SIE_EP6_CR0_PTR    ( (reg8 *) ProtocovUSB_USB__SIE_EP6_CR0)
#define ProtocovUSB_SIE_EP6_CR0_REG    (*(reg8 *) ProtocovUSB_USB__SIE_EP6_CR0)

#define ProtocovUSB_SIE_EP7_CNT0_PTR   ( (reg8 *) ProtocovUSB_USB__SIE_EP7_CNT0)
#define ProtocovUSB_SIE_EP7_CNT0_REG   (*(reg8 *) ProtocovUSB_USB__SIE_EP7_CNT0)
#define ProtocovUSB_SIE_EP7_CNT1_PTR   ( (reg8 *) ProtocovUSB_USB__SIE_EP7_CNT1)
#define ProtocovUSB_SIE_EP7_CNT1_REG   (*(reg8 *) ProtocovUSB_USB__SIE_EP7_CNT1)
#define ProtocovUSB_SIE_EP7_CR0_PTR    ( (reg8 *) ProtocovUSB_USB__SIE_EP7_CR0)
#define ProtocovUSB_SIE_EP7_CR0_REG    (*(reg8 *) ProtocovUSB_USB__SIE_EP7_CR0)

#define ProtocovUSB_SIE_EP8_CNT0_PTR   ( (reg8 *) ProtocovUSB_USB__SIE_EP8_CNT0)
#define ProtocovUSB_SIE_EP8_CNT0_REG   (*(reg8 *) ProtocovUSB_USB__SIE_EP8_CNT0)
#define ProtocovUSB_SIE_EP8_CNT1_PTR   ( (reg8 *) ProtocovUSB_USB__SIE_EP8_CNT1)
#define ProtocovUSB_SIE_EP8_CNT1_REG   (*(reg8 *) ProtocovUSB_USB__SIE_EP8_CNT1)
#define ProtocovUSB_SIE_EP8_CR0_PTR    ( (reg8 *) ProtocovUSB_USB__SIE_EP8_CR0)
#define ProtocovUSB_SIE_EP8_CR0_REG    (*(reg8 *) ProtocovUSB_USB__SIE_EP8_CR0)

#define ProtocovUSB_SOF0_PTR           ( (reg8 *) ProtocovUSB_USB__SOF0)
#define ProtocovUSB_SOF0_REG           (*(reg8 *) ProtocovUSB_USB__SOF0)
#define ProtocovUSB_SOF1_PTR           ( (reg8 *) ProtocovUSB_USB__SOF1)
#define ProtocovUSB_SOF1_REG           (*(reg8 *) ProtocovUSB_USB__SOF1)

#define ProtocovUSB_USB_CLK_EN_PTR     ( (reg8 *) ProtocovUSB_USB__USB_CLK_EN)
#define ProtocovUSB_USB_CLK_EN_REG     (*(reg8 *) ProtocovUSB_USB__USB_CLK_EN)

#define ProtocovUSB_USBIO_CR0_PTR      ( (reg8 *) ProtocovUSB_USB__USBIO_CR0)
#define ProtocovUSB_USBIO_CR0_REG      (*(reg8 *) ProtocovUSB_USB__USBIO_CR0)
#define ProtocovUSB_USBIO_CR1_PTR      ( (reg8 *) ProtocovUSB_USB__USBIO_CR1)
#define ProtocovUSB_USBIO_CR1_REG      (*(reg8 *) ProtocovUSB_USB__USBIO_CR1)

#define ProtocovUSB_DYN_RECONFIG_PTR   ( (reg8 *) ProtocovUSB_USB__DYN_RECONFIG)
#define ProtocovUSB_DYN_RECONFIG_REG   (*(reg8 *) ProtocovUSB_USB__DYN_RECONFIG)

#if (CY_PSOC4)
    #define ProtocovUSB_ARB_RW1_RA16_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW1_RA16)
    #define ProtocovUSB_ARB_RW1_RA16_REG   (*(reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW1_RA16)
    #define ProtocovUSB_ARB_RW1_WA16_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW1_WA16)
    #define ProtocovUSB_ARB_RW1_WA16_REG   (*(reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW1_WA16)
    #define ProtocovUSB_ARB_RW1_DR16_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW1_DR16)
    #define ProtocovUSB_ARB_RW1_DR16_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW1_DR16)
    #define ProtocovUSB_ARB_EP16_BASE      (*(volatile ProtocovUSB_arb_eps_reg16_struct CYXDATA *) \
                                                (ProtocovUSB_USB__ARB_RW1_WA16 - sizeof(ProtocovUSB_arb_ep_reg16_struct)))

    #define ProtocovUSB_ARB_RW2_DR16_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW2_DR16)
    #define ProtocovUSB_ARB_RW2_RA16_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW2_RA16)
    #define ProtocovUSB_ARB_RW2_WA16_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW2_WA16)

    #define ProtocovUSB_ARB_RW3_DR16_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW3_DR16)
    #define ProtocovUSB_ARB_RW3_RA16_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW3_RA16)
    #define ProtocovUSB_ARB_RW3_WA16_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW3_WA16)

    #define ProtocovUSB_ARB_RW4_DR16_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW4_DR16)
    #define ProtocovUSB_ARB_RW4_RA16_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW4_RA16)
    #define ProtocovUSB_ARB_RW4_WA16_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW4_WA16)

    #define ProtocovUSB_ARB_RW5_DR16_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW5_DR16)
    #define ProtocovUSB_ARB_RW5_RA16_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW5_RA16)
    #define ProtocovUSB_ARB_RW5_WA16_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW5_WA16)

    #define ProtocovUSB_ARB_RW6_DR16_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW6_DR16)
    #define ProtocovUSB_ARB_RW6_RA16_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW6_RA16)
    #define ProtocovUSB_ARB_RW6_WA16_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW6_WA16)

    #define ProtocovUSB_ARB_RW7_DR16_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW7_DR16)
    #define ProtocovUSB_ARB_RW7_RA16_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW7_RA16)
    #define ProtocovUSB_ARB_RW7_WA16_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW7_WA16)

    #define ProtocovUSB_ARB_RW8_DR16_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW8_DR16)
    #define ProtocovUSB_ARB_RW8_RA16_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW8_RA16)
    #define ProtocovUSB_ARB_RW8_WA16_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__ARB_RW8_WA16)

    #define ProtocovUSB_OSCLK_DR16_PTR     ( (reg32 *) ProtocovUSB_cy_m0s8_usb__OSCLK_DR16)
    #define ProtocovUSB_OSCLK_DR16_REG     (*(reg32 *) ProtocovUSB_cy_m0s8_usb__OSCLK_DR16)

    #define ProtocovUSB_SOF16_PTR          ( (reg32 *) ProtocovUSB_cy_m0s8_usb__SOF16)
    #define ProtocovUSB_SOF16_REG          (*(reg32 *) ProtocovUSB_cy_m0s8_usb__SOF16)
    
    #define ProtocovUSB_CWA16_PTR          ( (reg32 *) ProtocovUSB_cy_m0s8_usb__CWA16)
    #define ProtocovUSB_CWA16_REG          (*(reg32 *) ProtocovUSB_cy_m0s8_usb__CWA16)

    #define ProtocovUSB_DMA_THRES16_PTR    ( (reg32 *) ProtocovUSB_cy_m0s8_usb__DMA_THRES16)
    #define ProtocovUSB_DMA_THRES16_REG    (*(reg32 *) ProtocovUSB_cy_m0s8_usb__DMA_THRES16)

    #define ProtocovUSB_USB_CLK_EN_PTR     ( (reg32 *) ProtocovUSB_cy_m0s8_usb__USB_CLK_EN)
    #define ProtocovUSB_USB_CLK_EN_REG     (*(reg32 *) ProtocovUSB_cy_m0s8_usb__USB_CLK_EN)

    #define ProtocovUSB_USBIO_CR2_PTR      ( (reg32 *) ProtocovUSB_cy_m0s8_usb__USBIO_CR2)
    #define ProtocovUSB_USBIO_CR2_REG      (*(reg32 *) ProtocovUSB_cy_m0s8_usb__USBIO_CR2)

    #define ProtocovUSB_USB_MEM            ( (reg32 *) ProtocovUSB_cy_m0s8_usb__MEM_DATA0)

    #define ProtocovUSB_POWER_CTRL_REG      (*(reg32 *) ProtocovUSB_cy_m0s8_usb__USB_POWER_CTRL)
    #define ProtocovUSB_POWER_CTRL_PTR      ( (reg32 *) ProtocovUSB_cy_m0s8_usb__USB_POWER_CTRL)

    #define ProtocovUSB_CHGDET_CTRL_REG     (*(reg32 *) ProtocovUSB_cy_m0s8_usb__USB_CHGDET_CTRL)
    #define ProtocovUSB_CHGDET_CTRL_PTR     ( (reg32 *) ProtocovUSB_cy_m0s8_usb__USB_CHGDET_CTRL)

    #define ProtocovUSB_USBIO_CTRL_REG      (*(reg32 *) ProtocovUSB_cy_m0s8_usb__USB_USBIO_CTRL)
    #define ProtocovUSB_USBIO_CTRL_PTR      ( (reg32 *) ProtocovUSB_cy_m0s8_usb__USB_USBIO_CTRL)

    #define ProtocovUSB_FLOW_CTRL_REG       (*(reg32 *) ProtocovUSB_cy_m0s8_usb__USB_FLOW_CTRL)
    #define ProtocovUSB_FLOW_CTRL_PTR       ( (reg32 *) ProtocovUSB_cy_m0s8_usb__USB_FLOW_CTRL)

    #define ProtocovUSB_LPM_CTRL_REG        (*(reg32 *) ProtocovUSB_cy_m0s8_usb__USB_LPM_CTRL)
    #define ProtocovUSB_LPM_CTRL_PTR        ( (reg32 *) ProtocovUSB_cy_m0s8_usb__USB_LPM_CTRL)

    #define ProtocovUSB_LPM_STAT_REG        (*(reg32 *) ProtocovUSB_cy_m0s8_usb__USB_LPM_STAT)
    #define ProtocovUSB_LPM_STAT_PTR        ( (reg32 *) ProtocovUSB_cy_m0s8_usb__USB_LPM_STAT)

    #define ProtocovUSB_PHY_CONTROL_REG     (*(reg32 *) ProtocovUSB_cy_m0s8_usb__USB_PHY_CONTROL)
    #define ProtocovUSB_PHY_CONTROL_PTR     ( (reg32 *) ProtocovUSB_cy_m0s8_usb__USB_PHY_CONTROL)

    #define ProtocovUSB_INTR_SIE_REG        (*(reg32 *) ProtocovUSB_cy_m0s8_usb__USB_INTR_SIE)
    #define ProtocovUSB_INTR_SIE_PTR        ( (reg32 *) ProtocovUSB_cy_m0s8_usb__USB_INTR_SIE)

    #define ProtocovUSB_INTR_SIE_SET_REG    (*(reg32 *) ProtocovUSB_cy_m0s8_usb__USB_INTR_SIE_SET)
    #define ProtocovUSB_INTR_SIE_SET_PTR    ( (reg32 *) ProtocovUSB_cy_m0s8_usb__USB_INTR_SIE_SET)

    #define ProtocovUSB_INTR_SIE_MASK_REG   (*(reg32 *) ProtocovUSB_cy_m0s8_usb__USB_INTR_SIE_MASK)
    #define ProtocovUSB_INTR_SIE_MASK_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__USB_INTR_SIE_MASK)

    #define ProtocovUSB_INTR_SIE_MASKED_REG (*(reg32 *) ProtocovUSB_cy_m0s8_usb__USB_INTR_SIE_MASKED)
    #define ProtocovUSB_INTR_SIE_MASKED_PTR ( (reg32 *) ProtocovUSB_cy_m0s8_usb__USB_INTR_SIE_MASKED)

    #define ProtocovUSB_INTR_LVL_SEL_REG    (*(reg32 *) ProtocovUSB_cy_m0s8_usb__USB_INTR_LVL_SEL)
    #define ProtocovUSB_INTR_LVL_SEL_PTR    ( (reg32 *) ProtocovUSB_cy_m0s8_usb__USB_INTR_LVL_SEL)

    #define ProtocovUSB_INTR_CAUSE_HI_REG   (*(reg32 *) ProtocovUSB_cy_m0s8_usb__USB_INTR_CAUSE_HI)
    #define ProtocovUSB_INTR_CAUSE_HI_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__USB_INTR_CAUSE_HI)

    #define ProtocovUSB_INTR_CAUSE_LO_REG   (*(reg32 *) ProtocovUSB_cy_m0s8_usb__USB_INTR_CAUSE_LO)
    #define ProtocovUSB_INTR_CAUSE_LO_PTR   ( (reg32 *) ProtocovUSB_cy_m0s8_usb__USB_INTR_CAUSE_LO)

    #define ProtocovUSB_INTR_CAUSE_MED_REG  (*(reg32 *) ProtocovUSB_cy_m0s8_usb__USB_INTR_CAUSE_MED)
    #define ProtocovUSB_INTR_CAUSE_MED_PTR  ( (reg32 *) ProtocovUSB_cy_m0s8_usb__USB_INTR_CAUSE_MED)

    #define ProtocovUSB_DFT_CTRL_REG        (*(reg32 *) ProtocovUSB_cy_m0s8_usb__USB_DFT_CTRL)
    #define ProtocovUSB_DFT_CTRL_PTR        ( (reg32 *) ProtocovUSB_cy_m0s8_usb__USB_DFT_CTRL)

    #if (ProtocovUSB_VBUS_MONITORING_ENABLE)
        #if (ProtocovUSB_VBUS_POWER_PAD_ENABLE)
            /* Vbus power pad pin is hard wired to P13[2] */
            #define ProtocovUSB_VBUS_STATUS_REG    (*(reg32 *) CYREG_GPIO_PRT13_PS)
            #define ProtocovUSB_VBUS_STATUS_PTR    ( (reg32 *) CYREG_GPIO_PRT13_PS)
            #define ProtocovUSB_VBUS_VALID         (0x04u)
        #else
            /* Vbus valid pin is hard wired to P0[0] */
            #define ProtocovUSB_VBUS_STATUS_REG    (*(reg32 *) CYREG_GPIO_PRT0_PS)
            #define ProtocovUSB_VBUS_STATUS_PTR    ( (reg32 *) CYREG_GPIO_PRT0_PS)
            #define ProtocovUSB_VBUS_VALID         (0x01u)
        #endif
    #endif /*(ProtocovUSB_VBUS_MONITORING_ENABLE) */

    #define ProtocovUSB_BURSTEND_0_TR_OUTPUT    (ProtocovUSB_cy_m0s8_usb__BURSTEND0_TR_OUTPUT)
    #define ProtocovUSB_BURSTEND_1_TR_OUTPUT    (ProtocovUSB_cy_m0s8_usb__BURSTEND1_TR_OUTPUT)
    #define ProtocovUSB_BURSTEND_2_TR_OUTPUT    (ProtocovUSB_cy_m0s8_usb__BURSTEND2_TR_OUTPUT)
    #define ProtocovUSB_BURSTEND_3_TR_OUTPUT    (ProtocovUSB_cy_m0s8_usb__BURSTEND3_TR_OUTPUT)
    #define ProtocovUSB_BURSTEND_4_TR_OUTPUT    (ProtocovUSB_cy_m0s8_usb__BURSTEND4_TR_OUTPUT)
    #define ProtocovUSB_BURSTEND_5_TR_OUTPUT    (ProtocovUSB_cy_m0s8_usb__BURSTEND5_TR_OUTPUT)
    #define ProtocovUSB_BURSTEND_6_TR_OUTPUT    (ProtocovUSB_cy_m0s8_usb__BURSTEND6_TR_OUTPUT)
    #define ProtocovUSB_BURSTEND_7_TR_OUTPUT    (ProtocovUSB_cy_m0s8_usb__BURSTEND7_TR_OUTPUT)
    
#else /* (CY_PSOC3 || CY_PSOC5LP) */

    /* ProtocovUSB_PM_USB_CR0 */
    #define ProtocovUSB_PM_USB_CR0_PTR     ( (reg8 *) CYREG_PM_USB_CR0)
    #define ProtocovUSB_PM_USB_CR0_REG     (*(reg8 *) CYREG_PM_USB_CR0)

    /* ProtocovUSB_PM_ACT/STBY_CFG */
    #define ProtocovUSB_PM_ACT_CFG_PTR     ( (reg8 *) ProtocovUSB_USB__PM_ACT_CFG)
    #define ProtocovUSB_PM_ACT_CFG_REG     (*(reg8 *) ProtocovUSB_USB__PM_ACT_CFG)
    #define ProtocovUSB_PM_STBY_CFG_PTR    ( (reg8 *) ProtocovUSB_USB__PM_STBY_CFG)
    #define ProtocovUSB_PM_STBY_CFG_REG    (*(reg8 *) ProtocovUSB_USB__PM_STBY_CFG)

    #if (!CY_PSOC5LP)
        #define ProtocovUSB_USBIO_CR2_PTR  (  (reg8 *) ProtocovUSB_USB__USBIO_CR2)
        #define ProtocovUSB_USBIO_CR2_REG  (* (reg8 *) ProtocovUSB_USB__USBIO_CR2)
    #endif /* (!CY_PSOC5LP) */

    /* ProtocovUSB_USB_MEM - USB IP memory buffer */
    #define ProtocovUSB_USB_MEM            ((reg8 *) CYDEV_USB_MEM_BASE)

    #if (ProtocovUSB_VBUS_MONITORING_ENABLE)
        #if (ProtocovUSB_VBUS_MONITORING_INTERNAL)
            #define ProtocovUSB_VBUS_STATUS_REG    (*(reg8 *) ProtocovUSB_VBUS__PS)
            #define ProtocovUSB_VBUS_STATUS_PTR    ( (reg8 *) ProtocovUSB_VBUS__PS)
            #define ProtocovUSB_VBUS_VALID         (ProtocovUSB_VBUS__MASK)
        #else
            #define ProtocovUSB_VBUS_STATUS_REG    (*(reg8 *) ProtocovUSB_Vbus_ps_sts_sts_reg__STATUS_REG)
            #define ProtocovUSB_VBUS_STATUS_PTR    ( (reg8 *) ProtocovUSB_Vbus_ps_sts_sts_reg__STATUS_REG)
            #define ProtocovUSB_VBUS_VALID         (ProtocovUSB_Vbus_ps_sts_sts_reg__MASK)
        #endif /* (ProtocovUSB_VBUS_MONITORING_INTERNAL) */
    #endif /*(ProtocovUSB_VBUS_MONITORING_ENABLE) */
#endif /* (CY_PSOC4) */


/***************************************
*       Interrupt source constants
***************************************/

#define ProtocovUSB_DP_INTC_PRIORITY       ProtocovUSB_dp_int__INTC_PRIOR_NUM
#define ProtocovUSB_DP_INTC_VECT_NUM       ProtocovUSB_dp_int__INTC_NUMBER

#if (CY_PSOC4)
    #define ProtocovUSB_DMA_AUTO_INTR_PRIO (0u)
    
    #define ProtocovUSB_INTR_HI_PRIORITY   ProtocovUSB_high_int__INTC_PRIOR_NUM
    #define ProtocovUSB_INTR_HI_VECT_NUM   ProtocovUSB_high_int__INTC_NUMBER

    #define ProtocovUSB_INTR_MED_PRIORITY  ProtocovUSB_med_int__INTC_PRIOR_NUM
    #define ProtocovUSB_INTR_MED_VECT_NUM  ProtocovUSB_med_int__INTC_NUMBER

    #define ProtocovUSB_INTR_LO_PRIORITY   ProtocovUSB_lo_int__INTC_PRIOR_NUM
    #define ProtocovUSB_INTR_LO_VECT_NUM   ProtocovUSB_lo_int__INTC_NUMBER

    /* Interrupt sources in ProtocovUSB_isrCallbacks[] table */
    #define ProtocovUSB_SOF_INTR_NUM       (0u)
    #define ProtocovUSB_BUS_RESET_INT_NUM  (1u)
    #define ProtocovUSB_EP0_INTR_NUM       (2u)
    #define ProtocovUSB_LPM_INTR_NUM       (3u)
    #define ProtocovUSB_ARB_EP_INTR_NUM    (4u)
    #define ProtocovUSB_EP1_INTR_NUM       (5u)
    #define ProtocovUSB_EP2_INTR_NUM       (6u)
    #define ProtocovUSB_EP3_INTR_NUM       (7u)
    #define ProtocovUSB_EP4_INTR_NUM       (8u)
    #define ProtocovUSB_EP5_INTR_NUM       (9u)
    #define ProtocovUSB_EP6_INTR_NUM       (10u)
    #define ProtocovUSB_EP7_INTR_NUM       (11u)
    #define ProtocovUSB_EP8_INTR_NUM       (12u)

#else
    #define ProtocovUSB_BUS_RESET_PRIOR    ProtocovUSB_bus_reset__INTC_PRIOR_NUM
    #define ProtocovUSB_BUS_RESET_MASK     ProtocovUSB_bus_reset__INTC_MASK
    #define ProtocovUSB_BUS_RESET_VECT_NUM ProtocovUSB_bus_reset__INTC_NUMBER

    #define ProtocovUSB_SOF_PRIOR          ProtocovUSB_sof_int__INTC_PRIOR_NUM
    #define ProtocovUSB_SOF_MASK           ProtocovUSB_sof_int__INTC_MASK
    #define ProtocovUSB_SOF_VECT_NUM       ProtocovUSB_sof_int__INTC_NUMBER

    #define ProtocovUSB_EP_0_PRIOR         ProtocovUSB_ep_0__INTC_PRIOR_NUM
    #define ProtocovUSB_EP_0_MASK          ProtocovUSB_ep_0__INTC_MASK
    #define ProtocovUSB_EP_0_VECT_NUM      ProtocovUSB_ep_0__INTC_NUMBER

    #define ProtocovUSB_EP_1_PRIOR         ProtocovUSB_ep_1__INTC_PRIOR_NUM
    #define ProtocovUSB_EP_1_MASK          ProtocovUSB_ep_1__INTC_MASK
    #define ProtocovUSB_EP_1_VECT_NUM      ProtocovUSB_ep_1__INTC_NUMBER

    #define ProtocovUSB_EP_2_PRIOR         ProtocovUSB_ep_2__INTC_PRIOR_NUM
    #define ProtocovUSB_EP_2_MASK          ProtocovUSB_ep_2__INTC_MASK
    #define ProtocovUSB_EP_2_VECT_NUM      ProtocovUSB_ep_2__INTC_NUMBER

    #define ProtocovUSB_EP_3_PRIOR         ProtocovUSB_ep_3__INTC_PRIOR_NUM
    #define ProtocovUSB_EP_3_MASK          ProtocovUSB_ep_3__INTC_MASK
    #define ProtocovUSB_EP_3_VECT_NUM      ProtocovUSB_ep_3__INTC_NUMBER

    #define ProtocovUSB_EP_4_PRIOR         ProtocovUSB_ep_4__INTC_PRIOR_NUM
    #define ProtocovUSB_EP_4_MASK          ProtocovUSB_ep_4__INTC_MASK
    #define ProtocovUSB_EP_4_VECT_NUM      ProtocovUSB_ep_4__INTC_NUMBER

    #define ProtocovUSB_EP_5_PRIOR         ProtocovUSB_ep_5__INTC_PRIOR_NUM
    #define ProtocovUSB_EP_5_MASK          ProtocovUSB_ep_5__INTC_MASK
    #define ProtocovUSB_EP_5_VECT_NUM      ProtocovUSB_ep_5__INTC_NUMBER

    #define ProtocovUSB_EP_6_PRIOR         ProtocovUSB_ep_6__INTC_PRIOR_NUM
    #define ProtocovUSB_EP_6_MASK          ProtocovUSB_ep_6__INTC_MASK
    #define ProtocovUSB_EP_6_VECT_NUM      ProtocovUSB_ep_6__INTC_NUMBER

    #define ProtocovUSB_EP_7_PRIOR         ProtocovUSB_ep_7__INTC_PRIOR_NUM
    #define ProtocovUSB_EP_7_MASK          ProtocovUSB_ep_7__INTC_MASK
    #define ProtocovUSB_EP_7_VECT_NUM      ProtocovUSB_ep_7__INTC_NUMBER

    #define ProtocovUSB_EP_8_PRIOR         ProtocovUSB_ep_8__INTC_PRIOR_NUM
    #define ProtocovUSB_EP_8_MASK          ProtocovUSB_ep_8__INTC_MASK
    #define ProtocovUSB_EP_8_VECT_NUM      ProtocovUSB_ep_8__INTC_NUMBER

    /* Set ARB ISR priority 0 to be highest for all EPX ISRs. */
    #define ProtocovUSB_ARB_PRIOR          (0u)
    #define ProtocovUSB_ARB_MASK           ProtocovUSB_arb_int__INTC_MASK
    #define ProtocovUSB_ARB_VECT_NUM       ProtocovUSB_arb_int__INTC_NUMBER
#endif /* (CY_PSOC4) */


/***************************************
*       Endpoint 0 offsets (Table 9-2)
***************************************/
#define ProtocovUSB_bmRequestTypeReg      ProtocovUSB_EP0_DR_BASE.epData[0u]
#define ProtocovUSB_bRequestReg           ProtocovUSB_EP0_DR_BASE.epData[1u]
#define ProtocovUSB_wValueLoReg           ProtocovUSB_EP0_DR_BASE.epData[2u]
#define ProtocovUSB_wValueHiReg           ProtocovUSB_EP0_DR_BASE.epData[3u]
#define ProtocovUSB_wIndexLoReg           ProtocovUSB_EP0_DR_BASE.epData[4u]
#define ProtocovUSB_wIndexHiReg           ProtocovUSB_EP0_DR_BASE.epData[5u]
#define ProtocovUSB_wLengthLoReg          ProtocovUSB_EP0_DR_BASE.epData[6u]
#define ProtocovUSB_wLengthHiReg          ProtocovUSB_EP0_DR_BASE.epData[7u]

/* Compatibility defines */
#define ProtocovUSB_lengthLoReg           ProtocovUSB_EP0_DR_BASE.epData[6u]
#define ProtocovUSB_lengthHiReg           ProtocovUSB_EP0_DR_BASE.epData[7u]


/***************************************
*       Register Constants
***************************************/

#define ProtocovUSB_3500MV     (3500u)
#if (CY_PSOC4)
    #define ProtocovUSB_VDDD_MV    (CYDEV_VBUS_MV)
#else
    #define ProtocovUSB_VDDD_MV    (CYDEV_VDDD_MV)
#endif /* (CY_PSOC4) */


/* ProtocovUSB_USB_CLK */
#define ProtocovUSB_USB_CLK_CSR_CLK_EN_POS (0u)
#define ProtocovUSB_USB_CLK_CSR_CLK_EN     ((uint8) ((uint8) 0x1u << ProtocovUSB_USB_CLK_CSR_CLK_EN_POS))
#define ProtocovUSB_USB_CLK_ENABLE         (ProtocovUSB_USB_CLK_CSR_CLK_EN)

/* ProtocovUSB_CR0 */
#define ProtocovUSB_CR0_DEVICE_ADDRESS_POS     (0u)
#define ProtocovUSB_CR0_ENABLE_POS             (7u)
#define ProtocovUSB_CR0_DEVICE_ADDRESS_MASK    ((uint8) ((uint8) 0x7Fu << ProtocovUSB_CR0_DEVICE_ADDRESS_POS))
#define ProtocovUSB_CR0_ENABLE                 ((uint8) ((uint8) 0x01u << ProtocovUSB_CR0_ENABLE_POS))


/* ProtocovUSB_CR1 */
#define ProtocovUSB_CR1_REG_ENABLE_POS         (0u)
#define ProtocovUSB_CR1_ENABLE_LOCK_POS        (1u)
#define ProtocovUSB_CR1_BUS_ACTIVITY_POS       (2u)
#define ProtocovUSB_CR1_TRIM_OFFSET_MSB_POS    (3u)
#define ProtocovUSB_CR1_REG_ENABLE             ((uint8) ((uint8) 0x1u << ProtocovUSB_CR1_REG_ENABLE_POS))
#define ProtocovUSB_CR1_ENABLE_LOCK            ((uint8) ((uint8) 0x1u << ProtocovUSB_CR1_ENABLE_LOCK_POS))
#define ProtocovUSB_CR1_BUS_ACTIVITY           ((uint8) ((uint8) 0x1u << ProtocovUSB_CR1_BUS_ACTIVITY_POS))
#define ProtocovUSB_CR1_TRIM_OFFSET_MSB        ((uint8) ((uint8) 0x1u << ProtocovUSB_CR1_TRIM_OFFSET_MSB_POS))

/* ProtocovUSB_EPX_CNT */
#define ProtocovUSB_EP0_CNT_DATA_TOGGLE        (0x80u)
#define ProtocovUSB_EPX_CNT_DATA_TOGGLE        (0x80u)
#define ProtocovUSB_EPX_CNT0_MASK              (0x0Fu)
#define ProtocovUSB_EPX_CNTX_MSB_MASK          (0x07u)
#define ProtocovUSB_EPX_CNTX_ADDR_SHIFT        (0x04u)
#define ProtocovUSB_EPX_CNTX_ADDR_OFFSET       (0x10u)
#define ProtocovUSB_EPX_CNTX_CRC_COUNT         (0x02u)
#define ProtocovUSB_EPX_DATA_BUF_MAX           (512u)

/* ProtocovUSB_USBIO_CR0 */

#define ProtocovUSB_USBIO_CR0_TEN              (0x80u)
#define ProtocovUSB_USBIO_CR0_TSE0             (0x40u)
#define ProtocovUSB_USBIO_CR0_TD               (0x20u)
#define ProtocovUSB_USBIO_CR0_RD               (0x01u)

/* ProtocovUSB_USBIO_CR1 */
#define ProtocovUSB_USBIO_CR1_DM0_POS      (0u)
#define ProtocovUSB_USBIO_CR1_DP0_POS      (1u)
#define ProtocovUSB_USBIO_CR1_USBPUEN_POS  (2u)
#define ProtocovUSB_USBIO_CR1_IOMODE_POS   (5u)
#define ProtocovUSB_USBIO_CR1_DM0          ((uint8) ((uint8) 0x1u << ProtocovUSB_USBIO_CR1_DM0_POS))
#define ProtocovUSB_USBIO_CR1_DP0          ((uint8) ((uint8) 0x1u << ProtocovUSB_USBIO_CR1_DP0_POS))
#define ProtocovUSB_USBIO_CR1_USBPUEN      ((uint8) ((uint8) 0x1u << ProtocovUSB_USBIO_CR1_USBPUEN_POS))
#define ProtocovUSB_USBIO_CR1_IOMODE       ((uint8) ((uint8) 0x1u << ProtocovUSB_USBIO_CR1_IOMODE_POS))

/* ProtocovUSB_FASTCLK_IMO_CR */
#define ProtocovUSB_FASTCLK_IMO_CR_USBCLK_ON   (0x40u)
#define ProtocovUSB_FASTCLK_IMO_CR_XCLKEN      (0x20u)
#define ProtocovUSB_FASTCLK_IMO_CR_FX2ON       (0x10u)

/* ProtocovUSB_ARB_EPX_CFG */
#define ProtocovUSB_ARB_EPX_CFG_IN_DATA_RDY_POS    (0u)
#define ProtocovUSB_ARB_EPX_CFG_DMA_REQ_POS        (1u)
#define ProtocovUSB_ARB_EPX_CFG_CRC_BYPASS_POS     (2u)
#define ProtocovUSB_ARB_EPX_CFG_RESET_POS          (3u)
#define ProtocovUSB_ARB_EPX_CFG_IN_DATA_RDY        ((uint8) ((uint8) 0x1u << ProtocovUSB_ARB_EPX_CFG_IN_DATA_RDY_POS))
#define ProtocovUSB_ARB_EPX_CFG_DMA_REQ            ((uint8) ((uint8) 0x1u << ProtocovUSB_ARB_EPX_CFG_DMA_REQ_POS))
#define ProtocovUSB_ARB_EPX_CFG_CRC_BYPASS         ((uint8) ((uint8) 0x1u << ProtocovUSB_ARB_EPX_CFG_CRC_BYPASS_POS))
#define ProtocovUSB_ARB_EPX_CFG_RESET              ((uint8) ((uint8) 0x1u << ProtocovUSB_ARB_EPX_CFG_RESET_POS))

/* ProtocovUSB_ARB_EPX_INT / SR */
#define ProtocovUSB_ARB_EPX_INT_IN_BUF_FULL_POS    (0u)
#define ProtocovUSB_ARB_EPX_INT_DMA_GNT_POS        (1u)
#define ProtocovUSB_ARB_EPX_INT_BUF_OVER_POS       (2u)
#define ProtocovUSB_ARB_EPX_INT_BUF_UNDER_POS      (3u)
#define ProtocovUSB_ARB_EPX_INT_ERR_INT_POS        (4u)
#define ProtocovUSB_ARB_EPX_INT_IN_BUF_FULL        ((uint8) ((uint8) 0x1u << ProtocovUSB_ARB_EPX_INT_IN_BUF_FULL_POS))
#define ProtocovUSB_ARB_EPX_INT_DMA_GNT            ((uint8) ((uint8) 0x1u << ProtocovUSB_ARB_EPX_INT_DMA_GNT_POS))
#define ProtocovUSB_ARB_EPX_INT_BUF_OVER           ((uint8) ((uint8) 0x1u << ProtocovUSB_ARB_EPX_INT_BUF_OVER_POS))
#define ProtocovUSB_ARB_EPX_INT_BUF_UNDER          ((uint8) ((uint8) 0x1u << ProtocovUSB_ARB_EPX_INT_BUF_UNDER_POS))
#define ProtocovUSB_ARB_EPX_INT_ERR_INT            ((uint8) ((uint8) 0x1u << ProtocovUSB_ARB_EPX_INT_ERR_INT_POS))

#if (CY_PSOC4)
#define ProtocovUSB_ARB_EPX_INT_DMA_TERMIN_POS     (5u)
#define ProtocovUSB_ARB_EPX_INT_DMA_TERMIN         ((uint8) ((uint8) 0x1u << ProtocovUSB_ARB_EPX_INT_DMA_TERMIN_POS))
#endif /* (CY_PSOC4) */

/* Common arbiter interrupt sources for all PSoC devices. */
#define ProtocovUSB_ARB_EPX_INT_COMMON    (ProtocovUSB_ARB_EPX_INT_IN_BUF_FULL | \
                                                ProtocovUSB_ARB_EPX_INT_DMA_GNT     | \
                                                ProtocovUSB_ARB_EPX_INT_BUF_OVER    | \
                                                ProtocovUSB_ARB_EPX_INT_BUF_UNDER   | \
                                                ProtocovUSB_ARB_EPX_INT_ERR_INT)

#if (CY_PSOC4)
    #define ProtocovUSB_ARB_EPX_INT_ALL    (ProtocovUSB_ARB_EPX_INT_COMMON | ProtocovUSB_ARB_EPX_INT_DMA_TERMIN)
#else
    #define ProtocovUSB_ARB_EPX_INT_ALL    (ProtocovUSB_ARB_EPX_INT_COMMON)
#endif /* (CY_PSOC4) */

/* ProtocovUSB_ARB_CFG */
#define ProtocovUSB_ARB_CFG_AUTO_MEM_POS   (4u)
#define ProtocovUSB_ARB_CFG_DMA_CFG_POS    (5u)
#define ProtocovUSB_ARB_CFG_CFG_CMP_POS    (7u)
#define ProtocovUSB_ARB_CFG_AUTO_MEM       ((uint8) ((uint8) 0x1u << ProtocovUSB_ARB_CFG_AUTO_MEM_POS))
#define ProtocovUSB_ARB_CFG_DMA_CFG_MASK   ((uint8) ((uint8) 0x3u << ProtocovUSB_ARB_CFG_DMA_CFG_POS))
#define ProtocovUSB_ARB_CFG_DMA_CFG_NONE   ((uint8) ((uint8) 0x0u << ProtocovUSB_ARB_CFG_DMA_CFG_POS))
#define ProtocovUSB_ARB_CFG_DMA_CFG_MANUAL ((uint8) ((uint8) 0x1u << ProtocovUSB_ARB_CFG_DMA_CFG_POS))
#define ProtocovUSB_ARB_CFG_DMA_CFG_AUTO   ((uint8) ((uint8) 0x2u << ProtocovUSB_ARB_CFG_DMA_CFG_POS))
#define ProtocovUSB_ARB_CFG_CFG_CMP        ((uint8) ((uint8) 0x1u << ProtocovUSB_ARB_CFG_CFG_CMP_POS))

/* ProtocovUSB_DYN_RECONFIG */
#define ProtocovUSB_DYN_RECONFIG_EP_SHIFT      (1u)
#define ProtocovUSB_DYN_RECONFIG_ENABLE_POS    (0u)
#define ProtocovUSB_DYN_RECONFIG_EPNO_POS      (1u)
#define ProtocovUSB_DYN_RECONFIG_RDY_STS_POS   (4u)
#define ProtocovUSB_DYN_RECONFIG_ENABLE        ((uint8) ((uint8) 0x1u << ProtocovUSB_DYN_RECONFIG_ENABLE_POS))
#define ProtocovUSB_DYN_RECONFIG_EPNO_MASK     ((uint8) ((uint8) 0x7u << ProtocovUSB_DYN_RECONFIG_EPNO_POS))
#define ProtocovUSB_DYN_RECONFIG_RDY_STS       ((uint8) ((uint8) 0x1u << ProtocovUSB_DYN_RECONFIG_RDY_STS_POS))

/* ProtocovUSB_ARB_INT */
#define ProtocovUSB_ARB_INT_EP1_INTR_POS          (0u) /* [0] Interrupt for USB EP1 */
#define ProtocovUSB_ARB_INT_EP2_INTR_POS          (1u) /* [1] Interrupt for USB EP2 */
#define ProtocovUSB_ARB_INT_EP3_INTR_POS          (2u) /* [2] Interrupt for USB EP3 */
#define ProtocovUSB_ARB_INT_EP4_INTR_POS          (3u) /* [3] Interrupt for USB EP4 */
#define ProtocovUSB_ARB_INT_EP5_INTR_POS          (4u) /* [4] Interrupt for USB EP5 */
#define ProtocovUSB_ARB_INT_EP6_INTR_POS          (5u) /* [5] Interrupt for USB EP6 */
#define ProtocovUSB_ARB_INT_EP7_INTR_POS          (6u) /* [6] Interrupt for USB EP7 */
#define ProtocovUSB_ARB_INT_EP8_INTR_POS          (7u) /* [7] Interrupt for USB EP8 */
#define ProtocovUSB_ARB_INT_EP1_INTR              ((uint8) ((uint8) 0x1u << ProtocovUSB_ARB_INT_EP1_INTR_POS))
#define ProtocovUSB_ARB_INT_EP2_INTR              ((uint8) ((uint8) 0x1u << ProtocovUSB_ARB_INT_EP2_INTR_POS))
#define ProtocovUSB_ARB_INT_EP3_INTR              ((uint8) ((uint8) 0x1u << ProtocovUSB_ARB_INT_EP3_INTR_POS))
#define ProtocovUSB_ARB_INT_EP4_INTR              ((uint8) ((uint8) 0x1u << ProtocovUSB_ARB_INT_EP4_INTR_POS))
#define ProtocovUSB_ARB_INT_EP5_INTR              ((uint8) ((uint8) 0x1u << ProtocovUSB_ARB_INT_EP5_INTR_POS))
#define ProtocovUSB_ARB_INT_EP6_INTR              ((uint8) ((uint8) 0x1u << ProtocovUSB_ARB_INT_EP6_INTR_POS))
#define ProtocovUSB_ARB_INT_EP7_INTR              ((uint8) ((uint8) 0x1u << ProtocovUSB_ARB_INT_EP7_INTR_POS))
#define ProtocovUSB_ARB_INT_EP8_INTR              ((uint8) ((uint8) 0x1u << ProtocovUSB_ARB_INT_EP8_INTR_POS))

/* ProtocovUSB_SIE_INT */
#define ProtocovUSB_SIE_INT_EP1_INTR_POS          (0u) /* [0] Interrupt for USB EP1 */
#define ProtocovUSB_SIE_INT_EP2_INTR_POS          (1u) /* [1] Interrupt for USB EP2 */
#define ProtocovUSB_SIE_INT_EP3_INTR_POS          (2u) /* [2] Interrupt for USB EP3 */
#define ProtocovUSB_SIE_INT_EP4_INTR_POS          (3u) /* [3] Interrupt for USB EP4 */
#define ProtocovUSB_SIE_INT_EP5_INTR_POS          (4u) /* [4] Interrupt for USB EP5 */
#define ProtocovUSB_SIE_INT_EP6_INTR_POS          (5u) /* [5] Interrupt for USB EP6 */
#define ProtocovUSB_SIE_INT_EP7_INTR_POS          (6u) /* [6] Interrupt for USB EP7 */
#define ProtocovUSB_SIE_INT_EP8_INTR_POS          (7u) /* [7] Interrupt for USB EP8 */
#define ProtocovUSB_SIE_INT_EP1_INTR              ((uint8) ((uint8) 0x01u << ProtocovUSB_SIE_INT_EP1_INTR_POS))
#define ProtocovUSB_SIE_INT_EP2_INTR              ((uint8) ((uint8) 0x01u << ProtocovUSB_SIE_INT_EP2_INTR_POS))
#define ProtocovUSB_SIE_INT_EP3_INTR              ((uint8) ((uint8) 0x01u << ProtocovUSB_SIE_INT_EP3_INTR_POS))
#define ProtocovUSB_SIE_INT_EP4_INTR              ((uint8) ((uint8) 0x01u << ProtocovUSB_SIE_INT_EP4_INTR_POS))
#define ProtocovUSB_SIE_INT_EP5_INTR              ((uint8) ((uint8) 0x01u << ProtocovUSB_SIE_INT_EP5_INTR_POS))
#define ProtocovUSB_SIE_INT_EP6_INTR              ((uint8) ((uint8) 0x01u << ProtocovUSB_SIE_INT_EP6_INTR_POS))
#define ProtocovUSB_SIE_INT_EP7_INTR              ((uint8) ((uint8) 0x01u << ProtocovUSB_SIE_INT_EP7_INTR_POS))
#define ProtocovUSB_SIE_INT_EP8_INTR              ((uint8) ((uint8) 0x01u << ProtocovUSB_SIE_INT_EP8_INTR_POS))

#if (CY_PSOC4)
    /* ProtocovUSB_POWER_CTRL_REG */
    #define ProtocovUSB_POWER_CTRL_VBUS_VALID_OVR_POS       (0u)  /* [0] */
    #define ProtocovUSB_POWER_CTRL_SUSPEND_POS              (2u)  /* [1] */
    #define ProtocovUSB_POWER_CTRL_SUSPEND_DEL_POS          (3u)  /* [3] */
    #define ProtocovUSB_POWER_CTRL_ISOLATE_POS              (4u)  /* [4] */
    #define ProtocovUSB_POWER_CTRL_CHDET_PWR_CTL_POS        (5u)  /* [5] */
    #define ProtocovUSB_POWER_CTRL_ENABLE_DM_PULLDOWN_POS   (25u) /* [25] */
    #define ProtocovUSB_POWER_CTRL_ENABLE_VBUS_PULLDOWN_POS (26u) /* [26] */
    #define ProtocovUSB_POWER_CTRL_ENABLE_RCVR_POS          (27u) /* [27] */
    #define ProtocovUSB_POWER_CTRL_ENABLE_DPO_POS           (28u) /* [28] */
    #define ProtocovUSB_POWER_CTRL_ENABLE_DMO_POS           (29u) /* [29] */
    #define ProtocovUSB_POWER_CTRL_ENABLE_CHGDET_POS        (30u) /* [30] */
    #define ProtocovUSB_POWER_CTRL_ENABLE_POS               (31u) /* [31] */
    #define ProtocovUSB_POWER_CTRL_VBUS_VALID_OVR_MASK      ((uint32) 0x03u << ProtocovUSB_POWER_CTRL_VBUS_VALID_OVR_POS)
    #define ProtocovUSB_POWER_CTRL_VBUS_VALID_OVR_0         ((uint32) 0x00u << ProtocovUSB_POWER_CTRL_VBUS_VALID_OVR_POS)
    #define ProtocovUSB_POWER_CTRL_VBUS_VALID_OVR_1         ((uint32) 0x01u << ProtocovUSB_POWER_CTRL_VBUS_VALID_OVR_POS)
    #define ProtocovUSB_POWER_CTRL_VBUS_VALID_OVR_GPIO      ((uint32) 0x02u << ProtocovUSB_POWER_CTRL_VBUS_VALID_OVR_POS)
    #define ProtocovUSB_POWER_CTRL_VBUS_VALID_OVR_PHY       ((uint32) 0x03u << ProtocovUSB_POWER_CTRL_VBUS_VALID_OVR_POS)
    #define ProtocovUSB_POWER_CTRL_SUSPEND                  ((uint32) 0x01u << ProtocovUSB_POWER_CTRL_SUSPEND_POS)
    #define ProtocovUSB_POWER_CTRL_SUSPEND_DEL              ((uint32) 0x01u << ProtocovUSB_POWER_CTRL_SUSPEND_DEL_POS)
    #define ProtocovUSB_POWER_CTRL_ISOLATE                  ((uint32) 0x01u << ProtocovUSB_POWER_CTRL_ISOLATE_POS)
    #define ProtocovUSB_POWER_CTRL_CHDET_PWR_CTL_MASK       ((uint32) 0x03u << ProtocovUSB_POWER_CTRL_CHDET_PWR_CTL_POS)
    #define ProtocovUSB_POWER_CTRL_ENABLE_DM_PULLDOWN       ((uint32) 0x01u << ProtocovUSB_POWER_CTRL_ENABLE_DM_PULLDOWN_POS)
    #define ProtocovUSB_POWER_CTRL_ENABLE_VBUS_PULLDOWN     ((uint32) 0x01u << ProtocovUSB_POWER_CTRL_ENABLE_VBUS_PULLDOWN_POS)
    #define ProtocovUSB_POWER_CTRL_ENABLE_RCVR              ((uint32) 0x01u << ProtocovUSB_POWER_CTRL_ENABLE_RCVR_POS)
    #define ProtocovUSB_POWER_CTRL_ENABLE_DPO               ((uint32) 0x01u << ProtocovUSB_POWER_CTRL_ENABLE_DPO_POS)
    #define ProtocovUSB_POWER_CTRL_ENABLE_DMO               ((uint32) 0x01u << ProtocovUSB_POWER_CTRL_ENABLE_DMO_POS)
    #define ProtocovUSB_POWER_CTRL_ENABLE_CHGDET            ((uint32) 0x01u << ProtocovUSB_POWER_CTRL_ENABLE_CHGDET_POS)
    #define ProtocovUSB_POWER_CTRL_ENABLE                   ((uint32) 0x01u << ProtocovUSB_POWER_CTRL_ENABLE_POS)

    /* ProtocovUSB_CHGDET_CTRL_REG */
    #define ProtocovUSB_CHGDET_CTRL_COMP_DP_POS        (0u)  /* [0] */
    #define ProtocovUSB_CHGDET_CTRL_COMP_DM_POS        (1u)  /* [1] */
    #define ProtocovUSB_CHGDET_CTRL_COMP_EN_POS        (2u)  /* [2] */
    #define ProtocovUSB_CHGDET_CTRL_REF_DP_POS         (3u)  /* [3] */
    #define ProtocovUSB_CHGDET_CTRL_REF_DM_POS         (4u)  /* [4] */
    #define ProtocovUSB_CHGDET_CTRL_REF_EN_POS         (5u)  /* [5] */
    #define ProtocovUSB_CHGDET_CTRL_DCD_SRC_EN_POS     (6u)  /* [6] */
    #define ProtocovUSB_CHGDET_CTRL_ADFT_CTRL_POS      (12u) /* [12] */
    #define ProtocovUSB_CHGDET_CTRL_COMP_OUT_POS       (31u) /* [31] */
    #define ProtocovUSB_CHGDET_CTRL_COMP_DP            ((uint32) 0x01u << ProtocovUSB_CHGDET_CTRL_COMP_DP_POS)
    #define ProtocovUSB_CHGDET_CTRL_COMP_DM            ((uint32) 0x01u << ProtocovUSB_CHGDET_CTRL_COMP_DM_POS)
    #define ProtocovUSB_CHGDET_CTRL_COMP_EN            ((uint32) 0x01u << ProtocovUSB_CHGDET_CTRL_COMP_EN_POS)
    #define ProtocovUSB_CHGDET_CTRL_REF_DP             ((uint32) 0x01u << ProtocovUSB_CHGDET_CTRL_REF_DP_POS)
    #define ProtocovUSB_CHGDET_CTRL_REF_DM             ((uint32) 0x01u << ProtocovUSB_CHGDET_CTRL_REF_DM_POS)
    #define ProtocovUSB_CHGDET_CTRL_REF_EN             ((uint32) 0x01u << ProtocovUSB_CHGDET_CTRL_REF_EN_POS)
    #define ProtocovUSB_CHGDET_CTRL_DCD_SRC_EN         ((uint32) 0x01u << ProtocovUSB_CHGDET_CTRL_DCD_SRC_EN_POS)
    #define ProtocovUSB_CHGDET_CTRL_ADFT_CTRL_MASK     ((uint32) 0x03u << ProtocovUSB_CHGDET_CTRL_ADFT_CTRL_POS)
    #define ProtocovUSB_CHGDET_CTRL_ADFT_CTRL_NORMAL   ((uint32) 0x00u << ProtocovUSB_CHGDET_CTRL_ADFT_CTRL_POS)
    #define ProtocovUSB_CHGDET_CTRL_ADFT_CTRL_VBG      ((uint32) 0x01u << ProtocovUSB_CHGDET_CTRL_ADFT_CTRL_POS)
    #define ProtocovUSB_CHGDET_CTRL_ADFT_CTRL_DONTUSE  ((uint32) 0x02u << ProtocovUSB_CHGDET_CTRL_ADFT_CTRL_POS)
    #define ProtocovUSB_CHGDET_CTRL_ADFT_CTRL_ADFTIN   ((uint32) 0x03u << ProtocovUSB_CHGDET_CTRL_ADFT_CTRL_POS)
    #define ProtocovUSB_CHGDET_CTRL_COMP_OUT           ((uint32) 0x01u << ProtocovUSB_CHGDET_CTRL_COMP_OUT_POS)

    /* ProtocovUSB_LPM_CTRL */
    #define ProtocovUSB_LPM_CTRL_LPM_EN_POS        (0u)
    #define ProtocovUSB_LPM_CTRL_LPM_ACK_RESP_POS  (1u)
    #define ProtocovUSB_LPM_CTRL_NYET_EN_POS       (2u)
    #define ProtocovUSB_LPM_CTRL_SUB_RESP_POS      (4u)
    #define ProtocovUSB_LPM_CTRL_LPM_EN            ((uint32) 0x01u << ProtocovUSB_LPM_CTRL_LPM_EN_POS)
    #define ProtocovUSB_LPM_CTRL_LPM_ACK_RESP      ((uint32) 0x01u << ProtocovUSB_LPM_CTRL_LPM_ACK_RESP_POS)
    #define ProtocovUSB_LPM_CTRL_NYET_EN           ((uint32) 0x01u << ProtocovUSB_LPM_CTRL_NYET_EN_POS)
    #define ProtocovUSB_LPM_CTRL_ACK_NYET_MASK     ((uint32) 0x03u << ProtocovUSB_LPM_CTRL_LPM_ACK_RESP_POS)
    #define ProtocovUSB_LPM_CTRL_SUB_RESP          ((uint32) 0x01u << ProtocovUSB_LPM_CTRL_SUB_RESP_POS)

    #define ProtocovUSB_LPM_STAT_LPM_BESL_POS          (0u)
    #define ProtocovUSB_LPM_STAT_LPM_REMOTE_WAKE_POS   (4u)
    #define ProtocovUSB_LPM_STAT_LPM_BESL_MASK         ((uint32) 0x0Fu << ProtocovUSB_LPM_STAT_LPM_BESL_POS)
    #define ProtocovUSB_LPM_STAT_LPM_REMOTE_WAKE       ((uint32) 0x01u << ProtocovUSB_LPM_STAT_LPM_REMOTE_WAKE_POS)

    /* ProtocovUSB_INTR_SIE */
    #define ProtocovUSB_INTR_SIE_SOF_INTR_POS          (0u) /* [0] Interrupt for USB SOF   */
    #define ProtocovUSB_INTR_SIE_BUS_RESET_INTR_POS    (1u) /* [1] Interrupt for BUS RESET */
    #define ProtocovUSB_INTR_SIE_EP0_INTR_POS          (2u) /* [2] Interrupt for EP0       */
    #define ProtocovUSB_INTR_SIE_LPM_INTR_POS          (3u) /* [3] Interrupt for LPM       */
    #define ProtocovUSB_INTR_SIE_RESUME_INTR_POS       (4u) /* [4] Interrupt for RESUME (not used by component) */
    #define ProtocovUSB_INTR_SIE_SOF_INTR              ((uint32) 0x01u << ProtocovUSB_INTR_SIE_SOF_INTR_POS)
    #define ProtocovUSB_INTR_SIE_BUS_RESET_INTR        ((uint32) 0x01u << ProtocovUSB_INTR_SIE_BUS_RESET_INTR_POS)
    #define ProtocovUSB_INTR_SIE_EP0_INTR              ((uint32) 0x01u << ProtocovUSB_INTR_SIE_EP0_INTR_POS)
    #define ProtocovUSB_INTR_SIE_LPM_INTR              ((uint32) 0x01u << ProtocovUSB_INTR_SIE_LPM_INTR_POS)
    #define ProtocovUSB_INTR_SIE_RESUME_INTR           ((uint32) 0x01u << ProtocovUSB_INTR_SIE_RESUME_INTR_POS)

    /* ProtocovUSB_INTR_CAUSE_LO, MED and HI */
    #define ProtocovUSB_INTR_CAUSE_SOF_INTR_POS       (0u)  /* [0] Interrupt status for USB SOF    */
    #define ProtocovUSB_INTR_CAUSE_BUS_RESET_INTR_POS (1u)  /* [1] Interrupt status for USB BUS RSET */
    #define ProtocovUSB_INTR_CAUSE_EP0_INTR_POS       (2u)  /* [2] Interrupt status for USB EP0    */
    #define ProtocovUSB_INTR_CAUSE_LPM_INTR_POS       (3u)  /* [3] Interrupt status for USB LPM    */
    #define ProtocovUSB_INTR_CAUSE_RESUME_INTR_POS    (4u)  /* [4] Interrupt status for USB RESUME */
    #define ProtocovUSB_INTR_CAUSE_ARB_INTR_POS       (7u)  /* [7] Interrupt status for USB ARB    */
    #define ProtocovUSB_INTR_CAUSE_EP1_INTR_POS       (8u)  /* [8] Interrupt status for USB EP1    */
    #define ProtocovUSB_INTR_CAUSE_EP2_INTR_POS       (9u)  /* [9] Interrupt status for USB EP2    */
    #define ProtocovUSB_INTR_CAUSE_EP3_INTR_POS       (10u) /* [10] Interrupt status for USB EP3   */
    #define ProtocovUSB_INTR_CAUSE_EP4_INTR_POS       (11u) /* [11] Interrupt status for USB EP4   */
    #define ProtocovUSB_INTR_CAUSE_EP5_INTR_POS       (12u) /* [12] Interrupt status for USB EP5   */
    #define ProtocovUSB_INTR_CAUSE_EP6_INTR_POS       (13u) /* [13] Interrupt status for USB EP6   */
    #define ProtocovUSB_INTR_CAUSE_EP7_INTR_POS       (14u) /* [14] Interrupt status for USB EP7   */
    #define ProtocovUSB_INTR_CAUSE_EP8_INTR_POS       (15u) /* [15] Interrupt status for USB EP8   */
    #define ProtocovUSB_INTR_CAUSE_SOF_INTR           ((uint32) 0x01u << ProtocovUSB_INTR_CAUSE_SOF_INTR_POS)
    #define ProtocovUSB_INTR_CAUSE_BUS_RESET_INTR     ((uint32) 0x01u << ProtocovUSB_INTR_CAUSE_BUS_RESET_INTR_POS)
    #define ProtocovUSB_INTR_CAUSE_EP0_INTR           ((uint32) 0x01u << ProtocovUSB_INTR_CAUSE_EP0_INTR_POS)
    #define ProtocovUSB_INTR_CAUSE_LPM_INTR           ((uint32) 0x01u << ProtocovUSB_INTR_CAUSE_LPM_INTR_POS)
    #define ProtocovUSB_INTR_CAUSE_RESUME_INTR        ((uint32) 0x01u << ProtocovUSB_INTR_CAUSE_RESUME_INTR_POS)
    #define ProtocovUSB_INTR_CAUSE_ARB_INTR           ((uint32) 0x01u << ProtocovUSB_INTR_CAUSE_ARB_INTR_POS)
    #define ProtocovUSB_INTR_CAUSE_EP1_INTR           ((uint32) 0x01u << ProtocovUSB_INTR_CAUSE_EP1_INTR_POS)
    #define ProtocovUSB_INTR_CAUSE_EP2_INTR           ((uint32) 0x01u << ProtocovUSB_INTR_CAUSE_EP2_INTR_POS)
    #define ProtocovUSB_INTR_CAUSE_EP3_INTR           ((uint32) 0x01u << ProtocovUSB_INTR_CAUSE_EP3_INTR_POS)
    #define ProtocovUSB_INTR_CAUSE_EP4_INTR           ((uint32) 0x01u << ProtocovUSB_INTR_CAUSE_EP4_INTR_POS)
    #define ProtocovUSB_INTR_CAUSE_EP5_INTR           ((uint32) 0x01u << ProtocovUSB_INTR_CAUSE_EP5_INTR_POS)
    #define ProtocovUSB_INTR_CAUSE_EP6_INTR           ((uint32) 0x01u << ProtocovUSB_INTR_CAUSE_EP6_INTR_POS)
    #define ProtocovUSB_INTR_CAUSE_EP7_INTR           ((uint32) 0x01u << ProtocovUSB_INTR_CAUSE_EP7_INTR_POS)
    #define ProtocovUSB_INTR_CAUSE_EP8_INTR           ((uint32) 0x01u << ProtocovUSB_INTR_CAUSE_EP8_INTR_POS)

    #define ProtocovUSB_INTR_CAUSE_CTRL_INTR_MASK     (ProtocovUSB_INTR_CAUSE_SOF_INTR       | \
                                                            ProtocovUSB_INTR_CAUSE_BUS_RESET_INTR | \
                                                            ProtocovUSB_INTR_CAUSE_EP0_INTR       | \
                                                            ProtocovUSB_INTR_CAUSE_LPM_INTR)

    #define ProtocovUSB_INTR_CAUSE_EP1_8_INTR_MASK    (ProtocovUSB_INTR_CAUSE_EP1_INTR       | \
                                                            ProtocovUSB_INTR_CAUSE_EP2_INTR       | \
                                                            ProtocovUSB_INTR_CAUSE_EP3_INTR       | \
                                                            ProtocovUSB_INTR_CAUSE_EP4_INTR       | \
                                                            ProtocovUSB_INTR_CAUSE_EP5_INTR       | \
                                                            ProtocovUSB_INTR_CAUSE_EP6_INTR       | \
                                                            ProtocovUSB_INTR_CAUSE_EP7_INTR       | \
                                                            ProtocovUSB_INTR_CAUSE_EP8_INTR)

    #define ProtocovUSB_INTR_CAUSE_EP_INTR_SHIFT      (ProtocovUSB_INTR_CAUSE_ARB_INTR_POS - \
                                                           (ProtocovUSB_INTR_CAUSE_LPM_INTR_POS + 1u))
    #define ProtocovUSB_INTR_CAUSE_SRC_COUNT          (13u)

    #define ProtocovUSB_CHGDET_CTRL_PRIMARY    (ProtocovUSB_CHGDET_CTRL_COMP_EN | \
                                                     ProtocovUSB_CHGDET_CTRL_COMP_DM | \
                                                     ProtocovUSB_CHGDET_CTRL_REF_EN  | \
                                                     ProtocovUSB_CHGDET_CTRL_REF_DP)

    #define ProtocovUSB_CHGDET_CTRL_SECONDARY  (ProtocovUSB_CHGDET_CTRL_COMP_EN | \
                                                     ProtocovUSB_CHGDET_CTRL_COMP_DP | \
                                                     ProtocovUSB_CHGDET_CTRL_REF_EN  | \
                                                     ProtocovUSB_CHGDET_CTRL_REF_DM)

    #define ProtocovUSB_CHGDET_CTRL_DEFAULT    (0x00000900u)


#else /* (CY_PSOC3 || CY_PSOC5LP) */
    #define ProtocovUSB_PM_ACT_EN_FSUSB            ProtocovUSB_USB__PM_ACT_MSK
    #define ProtocovUSB_PM_STBY_EN_FSUSB           ProtocovUSB_USB__PM_STBY_MSK
    #define ProtocovUSB_PM_AVAIL_EN_FSUSBIO        (0x10u)

    #define ProtocovUSB_PM_USB_CR0_REF_EN          (0x01u)
    #define ProtocovUSB_PM_USB_CR0_PD_N            (0x02u)
    #define ProtocovUSB_PM_USB_CR0_PD_PULLUP_N     (0x04u)
#endif /* (CY_PSOC4) */


/***************************************
*       Macros Definitions
***************************************/

#if (CY_PSOC4)
    #define ProtocovUSB_ClearSieInterruptSource(intMask) \
                do{ \
                    ProtocovUSB_INTR_SIE_REG = (uint32) (intMask); \
                }while(0)
#else
    #define ProtocovUSB_ClearSieInterruptSource(intMask) \
                do{ /* Does nothing. */ }while(0)
#endif /* (CY_PSOC4) */

#define ProtocovUSB_ClearSieEpInterruptSource(intMask) \
            do{ \
                ProtocovUSB_SIE_EP_INT_SR_REG = (uint8) (intMask); \
            }while(0)

#define ProtocovUSB_GET_ACTIVE_IN_EP_CR0_MODE(epType)  (((epType) == ProtocovUSB_EP_TYPE_ISOC) ? \
                                                                (ProtocovUSB_MODE_ISO_IN) : (ProtocovUSB_MODE_ACK_IN))

#define ProtocovUSB_GET_ACTIVE_OUT_EP_CR0_MODE(epType) (((epType) == ProtocovUSB_EP_TYPE_ISOC) ? \
                                                                (ProtocovUSB_MODE_ISO_OUT) : (ProtocovUSB_MODE_ACK_OUT))

#define ProtocovUSB_GET_EP_TYPE(epNumber)  (ProtocovUSB_EP[epNumber].attrib & ProtocovUSB_EP_TYPE_MASK)

#define ProtocovUSB_GET_UINT16(hi, low)    (((uint16) ((uint16) (hi) << 8u)) | ((uint16) (low) & 0xFFu))


/***************************************
*    Initialization Register Settings
***************************************/

/* Clear device address and enable USB IP respond to USB traffic. */
#define ProtocovUSB_DEFUALT_CR0    (ProtocovUSB_CR0_ENABLE)

/* Arbiter configuration depends on memory management mode. */
#define ProtocovUSB_DEFAULT_ARB_CFG    ((ProtocovUSB_EP_MANAGEMENT_MANUAL) ? (ProtocovUSB_ARB_CFG_DMA_CFG_NONE) : \
                                                ((ProtocovUSB_EP_MANAGEMENT_DMA_MANUAL) ? \
                                                    (ProtocovUSB_ARB_CFG_DMA_CFG_MANUAL) : \
                                                        (ProtocovUSB_ARB_CFG_AUTO_MEM | ProtocovUSB_ARB_CFG_DMA_CFG_AUTO)))

/* Enable arbiter interrupt for active endpoints only */
#define ProtocovUSB_DEFAULT_ARB_INT_EN \
        ((uint8) ((uint8) ProtocovUSB_DMA1_ACTIVE << ProtocovUSB_ARB_INT_EP1_INTR_POS) | \
         (uint8) ((uint8) ProtocovUSB_DMA2_ACTIVE << ProtocovUSB_ARB_INT_EP2_INTR_POS) | \
         (uint8) ((uint8) ProtocovUSB_DMA3_ACTIVE << ProtocovUSB_ARB_INT_EP3_INTR_POS) | \
         (uint8) ((uint8) ProtocovUSB_DMA4_ACTIVE << ProtocovUSB_ARB_INT_EP4_INTR_POS) | \
         (uint8) ((uint8) ProtocovUSB_DMA5_ACTIVE << ProtocovUSB_ARB_INT_EP5_INTR_POS) | \
         (uint8) ((uint8) ProtocovUSB_DMA6_ACTIVE << ProtocovUSB_ARB_INT_EP6_INTR_POS) | \
         (uint8) ((uint8) ProtocovUSB_DMA7_ACTIVE << ProtocovUSB_ARB_INT_EP7_INTR_POS) | \
         (uint8) ((uint8) ProtocovUSB_DMA8_ACTIVE << ProtocovUSB_ARB_INT_EP8_INTR_POS))

/* Enable all SIE endpoints interrupts */
#define ProtocovUSB_DEFAULT_SIE_EP_INT_EN  (ProtocovUSB_SIE_INT_EP1_INTR | \
                                                 ProtocovUSB_SIE_INT_EP2_INTR | \
                                                 ProtocovUSB_SIE_INT_EP3_INTR | \
                                                 ProtocovUSB_SIE_INT_EP4_INTR | \
                                                 ProtocovUSB_SIE_INT_EP5_INTR | \
                                                 ProtocovUSB_SIE_INT_EP6_INTR | \
                                                 ProtocovUSB_SIE_INT_EP7_INTR | \
                                                 ProtocovUSB_SIE_INT_EP8_INTR)

#define ProtocovUSB_ARB_EPX_CFG_DEFAULT    (ProtocovUSB_ARB_EPX_CFG_RESET | \
                                                 ProtocovUSB_ARB_EPX_CFG_CRC_BYPASS)

/* Default EP arbiter interrupt source register */
#define ProtocovUSB_ARB_EPX_INT_COMMON_MASK   (ProtocovUSB_ARB_EPX_INT_IN_BUF_FULL | \
                                                    ProtocovUSB_ARB_EPX_INT_BUF_OVER    | \
                                                    ProtocovUSB_ARB_EPX_INT_BUF_UNDER   | \
                                                    ProtocovUSB_ARB_EPX_INT_ERR_INT     | \
                                                    (ProtocovUSB_EP_MANAGEMENT_DMA_MANUAL ? ProtocovUSB_ARB_EPX_INT_DMA_GNT : 0u))

#define ProtocovUSB_CLEAR_REG      (0u)

#if (CY_PSOC4)
    /* Set USB lock option when IMO is locked to USB traffic. */
    #define ProtocovUSB_DEFUALT_CR1    ((0u != CySysClkImoGetUsbLock()) ? (ProtocovUSB_CR1_ENABLE_LOCK) : (0u))

    /* Recommended value is increased from 3 to 10 due to suppress glitch on  
     * RSE0 with USB2.0 hubs (LF CLK = 32kHz equal to 350us). */
    #define ProtocovUSB_DEFUALT_BUS_RST_CNT  (10u)

    /* Select VBUS sources as: valid, PHY of GPIO, and clears isolate bit. */
    /* Application level must ensure that VBUS is valid valid to use. */
    #define ProtocovUSB_DEFAULT_POWER_CTRL_VBUS    (ProtocovUSB_POWER_CTRL_ENABLE_VBUS_PULLDOWN | \
                                                         ((!ProtocovUSB_VBUS_MONITORING_ENABLE) ? \
                                                            (ProtocovUSB_POWER_CTRL_VBUS_VALID_OVR_1) : \
                                                                (ProtocovUSB_VBUS_POWER_PAD_ENABLE ? \
                                                                    (ProtocovUSB_POWER_CTRL_VBUS_VALID_OVR_PHY) : \
                                                                    (ProtocovUSB_POWER_CTRL_VBUS_VALID_OVR_GPIO))))
    /* Enable USB IP. */
    #define ProtocovUSB_DEFAULT_POWER_CTRL_PHY (ProtocovUSB_POWER_CTRL_SUSPEND     | \
                                                     ProtocovUSB_POWER_CTRL_SUSPEND_DEL | \
                                                     ProtocovUSB_POWER_CTRL_ENABLE_RCVR | \
                                                     ProtocovUSB_POWER_CTRL_ENABLE_DPO  | \
                                                     ProtocovUSB_POWER_CTRL_ENABLE_DMO  | \
                                                     ProtocovUSB_POWER_CTRL_ENABLE)

    /* Assign interrupt between levels lo, med, hi. */
    #define ProtocovUSB_DEFAULT_INTR_LVL_SEL   ((uint32) (ProtocovUSB_INTR_LVL_SEL))

    /* Enable interrupt source in the INTR_SIE. The SOF is always disabled and EP0 is enabled. */
    #define ProtocovUSB_DEFAULT_INTR_SIE_MASK \
                ((uint32) ((uint32) ProtocovUSB_BUS_RESET_ISR_ACTIVE << ProtocovUSB_INTR_SIE_BUS_RESET_INTR_POS) | \
                 (uint32) ((uint32) ProtocovUSB_SOF_ISR_ACTIVE       << ProtocovUSB_INTR_SIE_SOF_INTR_POS)       | \
                 (uint32) ((uint32) ProtocovUSB_LPM_ACTIVE           << ProtocovUSB_INTR_SIE_LPM_INTR_POS)       | \
                 (uint32) ((uint32) ProtocovUSB_INTR_SIE_EP0_INTR))

    /* Arbiter interrupt sources */
    #define ProtocovUSB_ARB_EPX_INT_MASK   (ProtocovUSB_ARB_EPX_INT_COMMON_MASK | \
                                                (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO ? ProtocovUSB_ARB_EPX_INT_DMA_TERMIN : 0u))

    /* Common DMA configuration */
    #define ProtocovUSB_DMA_COMMON_CFG     (CYDMA_PULSE | CYDMA_ENTIRE_DESCRIPTOR | \
                                                 CYDMA_NON_PREEMPTABLE)


#else
    #define ProtocovUSB_ARB_EPX_INT_MASK   (ProtocovUSB_ARB_EPX_INT_COMMON_MASK)

    #define ProtocovUSB_DEFUALT_CR1        (ProtocovUSB_CR1_ENABLE_LOCK)

    /* Recommended value is 3 for LF CLK = 100kHz equal to 100us. */
    #define ProtocovUSB_DEFUALT_BUS_RST_CNT    (10u)
#endif /* (CY_PSOC4) */

/*
* \addtogroup group_deprecated
* @{
*/

/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Renamed type definitions */
#define ProtocovUSB_CODE CYCODE
#define ProtocovUSB_FAR CYFAR
#if defined(__C51__) || defined(__CX51__)
    #define ProtocovUSB_DATA data
    #define ProtocovUSB_XDATA xdata
#else
    #define ProtocovUSB_DATA
    #define ProtocovUSB_XDATA
#endif /*  __C51__ */
#define ProtocovUSB_NULL       NULL
/** @} deprecated */
/* Renamed structure fields */
#define wBuffOffset         buffOffset
#define wBufferSize         bufferSize
#define bStatus             status
#define wLength             length
#define wCount              count

/* Renamed global variable */
#define CurrentTD           ProtocovUSB_currentTD
#define ProtocovUSB_interfaceSetting_last       ProtocovUSB_interfaceSettingLast

/* Renamed global constants */
#define ProtocovUSB_DWR_VDDD_OPERATION         (ProtocovUSB_DWR_POWER_OPERATION)

/* Renamed functions */
#define ProtocovUSB_bCheckActivity             ProtocovUSB_CheckActivity
#define ProtocovUSB_bGetConfiguration          ProtocovUSB_GetConfiguration
#define ProtocovUSB_bGetInterfaceSetting       ProtocovUSB_GetInterfaceSetting
#define ProtocovUSB_bGetEPState                ProtocovUSB_GetEPState
#define ProtocovUSB_wGetEPCount                ProtocovUSB_GetEPCount
#define ProtocovUSB_bGetEPAckState             ProtocovUSB_GetEPAckState
#define ProtocovUSB_bRWUEnabled                ProtocovUSB_RWUEnabled
#define ProtocovUSB_bVBusPresent               ProtocovUSB_VBusPresent

#define ProtocovUSB_bConfiguration             ProtocovUSB_configuration
#define ProtocovUSB_bInterfaceSetting          ProtocovUSB_interfaceSetting
#define ProtocovUSB_bDeviceAddress             ProtocovUSB_deviceAddress
#define ProtocovUSB_bDeviceStatus              ProtocovUSB_deviceStatus
#define ProtocovUSB_bDevice                    ProtocovUSB_device
#define ProtocovUSB_bTransferState             ProtocovUSB_transferState
#define ProtocovUSB_bLastPacketSize            ProtocovUSB_lastPacketSize

#define ProtocovUSB_LoadEP                     ProtocovUSB_LoadInEP
#define ProtocovUSB_LoadInISOCEP               ProtocovUSB_LoadInEP
#define ProtocovUSB_EnableOutISOCEP            ProtocovUSB_EnableOutEP

#define ProtocovUSB_SetVector                  CyIntSetVector
#define ProtocovUSB_SetPriority                CyIntSetPriority
#define ProtocovUSB_EnableInt                  CyIntEnable

/* Replace with register access. */
#define ProtocovUSB_bmRequestType      ProtocovUSB_EP0_DR0_PTR
#define ProtocovUSB_bRequest           ProtocovUSB_EP0_DR1_PTR
#define ProtocovUSB_wValue             ProtocovUSB_EP0_DR2_PTR
#define ProtocovUSB_wValueHi           ProtocovUSB_EP0_DR3_PTR
#define ProtocovUSB_wValueLo           ProtocovUSB_EP0_DR2_PTR
#define ProtocovUSB_wIndex             ProtocovUSB_EP0_DR4_PTR
#define ProtocovUSB_wIndexHi           ProtocovUSB_EP0_DR5_PTR
#define ProtocovUSB_wIndexLo           ProtocovUSB_EP0_DR4_PTR
#define ProtocovUSB_length             ProtocovUSB_EP0_DR6_PTR
#define ProtocovUSB_lengthHi           ProtocovUSB_EP0_DR7_PTR
#define ProtocovUSB_lengthLo           ProtocovUSB_EP0_DR6_PTR

/* Rename VBUS monitoring registers. */
#if (CY_PSOC3 || CY_PSOC5LP)
    #if (ProtocovUSB_VBUS_MONITORING_ENABLE)
        #if (ProtocovUSB_VBUS_MONITORING_INTERNAL)
            #define ProtocovUSB_VBUS_DR_PTR    ( (reg8 *) ProtocovUSB_VBUS__DR)
            #define ProtocovUSB_VBUS_DR_REG    (*(reg8 *) ProtocovUSB_VBUS__DR)
            #define ProtocovUSB_VBUS_PS_PTR    ( (reg8 *) ProtocovUSB_VBUS__PS)
            #define ProtocovUSB_VBUS_PS_REG    (*(reg8 *) ProtocovUSB_VBUS__PS)
            #define ProtocovUSB_VBUS_MASK          ProtocovUSB_VBUS__MASK
        #else
            #define ProtocovUSB_VBUS_PS_PTR    ( (reg8 *) ProtocovUSB_Vbus_ps_sts_sts_reg__STATUS_REG)
            #define ProtocovUSB_VBUS_MASK      (0x01u)
        #endif /* (ProtocovUSB_VBUS_MONITORING_INTERNAL) */
    #endif /*(ProtocovUSB_VBUS_MONITORING_ENABLE) */
        
    /* Pointer DIE structure in flash (8 bytes): Y and X location, wafer, lot msb, lot lsb, 
    *  work week, fab/year, minor. */
    #define ProtocovUSB_DIE_ID             CYDEV_FLSHID_CUST_TABLES_BASE

     #if (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)
        #if (ProtocovUSB_DMA1_ACTIVE)
            #define ProtocovUSB_ep1_TD_TERMOUT_EN  (ProtocovUSB_ep1__TD_TERMOUT_EN)
        #else
            #define ProtocovUSB_ep1_TD_TERMOUT_EN  (0u)
        #endif /* (ProtocovUSB_DMA1_ACTIVE) */

        #if (ProtocovUSB_DMA2_ACTIVE)
            #define ProtocovUSB_ep2_TD_TERMOUT_EN  (ProtocovUSB_ep2__TD_TERMOUT_EN)
        #else
            #define ProtocovUSB_ep2_TD_TERMOUT_EN  (0u)
        #endif /* (ProtocovUSB_DMA2_ACTIVE) */

        #if (ProtocovUSB_DMA3_ACTIVE)
            #define ProtocovUSB_ep3_TD_TERMOUT_EN  (ProtocovUSB_ep3__TD_TERMOUT_EN)
        #else
            #define ProtocovUSB_ep3_TD_TERMOUT_EN  (0u)
        #endif /* (ProtocovUSB_DMA3_ACTIVE) */

        #if (ProtocovUSB_DMA4_ACTIVE)
            #define ProtocovUSB_ep4_TD_TERMOUT_EN  (ProtocovUSB_ep4__TD_TERMOUT_EN)
        #else
            #define ProtocovUSB_ep4_TD_TERMOUT_EN  (0u)
        #endif /* (ProtocovUSB_DMA4_ACTIVE) */

        #if (ProtocovUSB_DMA5_ACTIVE)
            #define ProtocovUSB_ep5_TD_TERMOUT_EN  (ProtocovUSB_ep5__TD_TERMOUT_EN)
        #else
            #define ProtocovUSB_ep5_TD_TERMOUT_EN  (0u)
        #endif /* (ProtocovUSB_DMA5_ACTIVE) */

        #if (ProtocovUSB_DMA6_ACTIVE)
            #define ProtocovUSB_ep6_TD_TERMOUT_EN  (ProtocovUSB_ep6__TD_TERMOUT_EN)
        #else
            #define ProtocovUSB_ep6_TD_TERMOUT_EN  (0u)
        #endif /* (ProtocovUSB_DMA6_ACTIVE) */

        #if (ProtocovUSB_DMA7_ACTIVE)
            #define ProtocovUSB_ep7_TD_TERMOUT_EN  (ProtocovUSB_ep7__TD_TERMOUT_EN)
        #else
            #define ProtocovUSB_ep7_TD_TERMOUT_EN  (0u)
        #endif /* (ProtocovUSB_DMA7_ACTIVE) */

        #if (ProtocovUSB_DMA8_ACTIVE)
            #define ProtocovUSB_ep8_TD_TERMOUT_EN  (ProtocovUSB_ep8__TD_TERMOUT_EN)
        #else
            #define ProtocovUSB_ep8_TD_TERMOUT_EN  (0u)
        #endif /* (ProtocovUSB_DMA8_ACTIVE) */
    #endif /* (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO) */   
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

/* Rename USB IP registers. */
#define ProtocovUSB_ARB_CFG        ProtocovUSB_ARB_CFG_PTR

#define ProtocovUSB_ARB_EP1_CFG    ProtocovUSB_ARB_EP1_CFG_PTR
#define ProtocovUSB_ARB_EP1_INT_EN ProtocovUSB_ARB_EP1_INT_EN_PTR
#define ProtocovUSB_ARB_EP1_SR     ProtocovUSB_ARB_EP1_SR_PTR

#define ProtocovUSB_ARB_EP2_CFG    ProtocovUSB_ARB_EP2_CFG_PTR
#define ProtocovUSB_ARB_EP2_INT_EN ProtocovUSB_ARB_EP2_INT_EN_PTR
#define ProtocovUSB_ARB_EP2_SR     ProtocovUSB_ARB_EP2_SR_PTR

#define ProtocovUSB_ARB_EP3_CFG    ProtocovUSB_ARB_EP3_CFG_PTR
#define ProtocovUSB_ARB_EP3_INT_EN ProtocovUSB_ARB_EP3_INT_EN_PTR
#define ProtocovUSB_ARB_EP3_SR     ProtocovUSB_ARB_EP3_SR_PTR

#define ProtocovUSB_ARB_EP4_CFG    ProtocovUSB_ARB_EP4_CFG_PTR
#define ProtocovUSB_ARB_EP4_INT_EN ProtocovUSB_ARB_EP4_INT_EN_PTR
#define ProtocovUSB_ARB_EP4_SR     ProtocovUSB_ARB_EP4_SR_PTR

#define ProtocovUSB_ARB_EP5_CFG    ProtocovUSB_ARB_EP5_CFG_PTR
#define ProtocovUSB_ARB_EP5_INT_EN ProtocovUSB_ARB_EP5_INT_EN_PTR
#define ProtocovUSB_ARB_EP5_SR     ProtocovUSB_ARB_EP5_SR_PTR

#define ProtocovUSB_ARB_EP6_CFG    ProtocovUSB_ARB_EP6_CFG_PTR
#define ProtocovUSB_ARB_EP6_INT_EN ProtocovUSB_ARB_EP6_INT_EN_PTR
#define ProtocovUSB_ARB_EP6_SR     ProtocovUSB_ARB_EP6_SR_PTR

#define ProtocovUSB_ARB_EP7_CFG    ProtocovUSB_ARB_EP7_CFG_PTR
#define ProtocovUSB_ARB_EP7_INT_EN ProtocovUSB_ARB_EP7_INT_EN_PTR
#define ProtocovUSB_ARB_EP7_SR     ProtocovUSB_ARB_EP7_SR_PTR

#define ProtocovUSB_ARB_EP8_CFG    ProtocovUSB_ARB_EP8_CFG_PTR
#define ProtocovUSB_ARB_EP8_INT_EN ProtocovUSB_ARB_EP8_INT_EN_PTR
#define ProtocovUSB_ARB_EP8_SR     ProtocovUSB_ARB_EP8_SR_PTR

#define ProtocovUSB_ARB_INT_EN     ProtocovUSB_ARB_INT_EN_PTR
#define ProtocovUSB_ARB_INT_SR     ProtocovUSB_ARB_INT_SR_PTR

#define ProtocovUSB_ARB_RW1_DR     ProtocovUSB_ARB_RW1_DR_PTR
#define ProtocovUSB_ARB_RW1_RA     ProtocovUSB_ARB_RW1_RA_PTR
#define ProtocovUSB_ARB_RW1_RA_MSB ProtocovUSB_ARB_RW1_RA_MSB_PTR
#define ProtocovUSB_ARB_RW1_WA     ProtocovUSB_ARB_RW1_WA_PTR
#define ProtocovUSB_ARB_RW1_WA_MSB ProtocovUSB_ARB_RW1_WA_MSB_PTR

#define ProtocovUSB_ARB_RW2_DR     ProtocovUSB_ARB_RW2_DR_PTR
#define ProtocovUSB_ARB_RW2_RA     ProtocovUSB_ARB_RW2_RA_PTR
#define ProtocovUSB_ARB_RW2_RA_MSB ProtocovUSB_ARB_RW2_RA_MSB_PTR
#define ProtocovUSB_ARB_RW2_WA     ProtocovUSB_ARB_RW2_WA_PTR
#define ProtocovUSB_ARB_RW2_WA_MSB ProtocovUSB_ARB_RW2_WA_MSB_PTR

#define ProtocovUSB_ARB_RW3_DR     ProtocovUSB_ARB_RW3_DR_PTR
#define ProtocovUSB_ARB_RW3_RA     ProtocovUSB_ARB_RW3_RA_PTR
#define ProtocovUSB_ARB_RW3_RA_MSB ProtocovUSB_ARB_RW3_RA_MSB_PTR
#define ProtocovUSB_ARB_RW3_WA     ProtocovUSB_ARB_RW3_WA_PTR
#define ProtocovUSB_ARB_RW3_WA_MSB ProtocovUSB_ARB_RW3_WA_MSB_PTR

#define ProtocovUSB_ARB_RW4_DR     ProtocovUSB_ARB_RW4_DR_PTR
#define ProtocovUSB_ARB_RW4_RA     ProtocovUSB_ARB_RW4_RA_PTR
#define ProtocovUSB_ARB_RW4_RA_MSB ProtocovUSB_ARB_RW4_RA_MSB_PTR
#define ProtocovUSB_ARB_RW4_WA     ProtocovUSB_ARB_RW4_WA_PTR
#define ProtocovUSB_ARB_RW4_WA_MSB ProtocovUSB_ARB_RW4_WA_MSB_PTR

#define ProtocovUSB_ARB_RW5_DR     ProtocovUSB_ARB_RW5_DR_PTR
#define ProtocovUSB_ARB_RW5_RA     ProtocovUSB_ARB_RW5_RA_PTR
#define ProtocovUSB_ARB_RW5_RA_MSB ProtocovUSB_ARB_RW5_RA_MSB_PTR
#define ProtocovUSB_ARB_RW5_WA     ProtocovUSB_ARB_RW5_WA_PTR
#define ProtocovUSB_ARB_RW5_WA_MSB ProtocovUSB_ARB_RW5_WA_MSB_PTR

#define ProtocovUSB_ARB_RW6_DR     ProtocovUSB_ARB_RW6_DR_PTR
#define ProtocovUSB_ARB_RW6_RA     ProtocovUSB_ARB_RW6_RA_PTR
#define ProtocovUSB_ARB_RW6_RA_MSB ProtocovUSB_ARB_RW6_RA_MSB_PTR
#define ProtocovUSB_ARB_RW6_WA     ProtocovUSB_ARB_RW6_WA_PTR
#define ProtocovUSB_ARB_RW6_WA_MSB ProtocovUSB_ARB_RW6_WA_MSB_PTR

#define ProtocovUSB_ARB_RW7_DR     ProtocovUSB_ARB_RW7_DR_PTR
#define ProtocovUSB_ARB_RW7_RA     ProtocovUSB_ARB_RW7_RA_PTR
#define ProtocovUSB_ARB_RW7_RA_MSB ProtocovUSB_ARB_RW7_RA_MSB_PTR
#define ProtocovUSB_ARB_RW7_WA     ProtocovUSB_ARB_RW7_WA_PTR
#define ProtocovUSB_ARB_RW7_WA_MSB ProtocovUSB_ARB_RW7_WA_MSB_PTR

#define ProtocovUSB_ARB_RW8_DR     ProtocovUSB_ARB_RW8_DR_PTR
#define ProtocovUSB_ARB_RW8_RA     ProtocovUSB_ARB_RW8_RA_PTR
#define ProtocovUSB_ARB_RW8_RA_MSB ProtocovUSB_ARB_RW8_RA_MSB_PTR
#define ProtocovUSB_ARB_RW8_WA     ProtocovUSB_ARB_RW8_WA_PTR
#define ProtocovUSB_ARB_RW8_WA_MSB ProtocovUSB_ARB_RW8_WA_MSB_PTR

#define ProtocovUSB_BUF_SIZE       ProtocovUSB_BUF_SIZE_PTR
#define ProtocovUSB_BUS_RST_CNT    ProtocovUSB_BUS_RST_CNT_PTR
#define ProtocovUSB_CR0            ProtocovUSB_CR0_PTR
#define ProtocovUSB_CR1            ProtocovUSB_CR1_PTR
#define ProtocovUSB_CWA            ProtocovUSB_CWA_PTR
#define ProtocovUSB_CWA_MSB        ProtocovUSB_CWA_MSB_PTR

#define ProtocovUSB_DMA_THRES      ProtocovUSB_DMA_THRES_PTR
#define ProtocovUSB_DMA_THRES_MSB  ProtocovUSB_DMA_THRES_MSB_PTR

#define ProtocovUSB_EP_ACTIVE      ProtocovUSB_EP_ACTIVE_PTR
#define ProtocovUSB_EP_TYPE        ProtocovUSB_EP_TYPE_PTR

#define ProtocovUSB_EP0_CNT        ProtocovUSB_EP0_CNT_PTR
#define ProtocovUSB_EP0_CR         ProtocovUSB_EP0_CR_PTR
#define ProtocovUSB_EP0_DR0        ProtocovUSB_EP0_DR0_PTR
#define ProtocovUSB_EP0_DR1        ProtocovUSB_EP0_DR1_PTR
#define ProtocovUSB_EP0_DR2        ProtocovUSB_EP0_DR2_PTR
#define ProtocovUSB_EP0_DR3        ProtocovUSB_EP0_DR3_PTR
#define ProtocovUSB_EP0_DR4        ProtocovUSB_EP0_DR4_PTR
#define ProtocovUSB_EP0_DR5        ProtocovUSB_EP0_DR5_PTR
#define ProtocovUSB_EP0_DR6        ProtocovUSB_EP0_DR6_PTR
#define ProtocovUSB_EP0_DR7        ProtocovUSB_EP0_DR7_PTR

#define ProtocovUSB_OSCLK_DR0      ProtocovUSB_OSCLK_DR0_PTR
#define ProtocovUSB_OSCLK_DR1      ProtocovUSB_OSCLK_DR1_PTR

#define ProtocovUSB_PM_ACT_CFG     ProtocovUSB_PM_ACT_CFG_PTR
#define ProtocovUSB_PM_STBY_CFG    ProtocovUSB_PM_STBY_CFG_PTR

#define ProtocovUSB_SIE_EP_INT_EN  ProtocovUSB_SIE_EP_INT_EN_PTR
#define ProtocovUSB_SIE_EP_INT_SR  ProtocovUSB_SIE_EP_INT_SR_PTR

#define ProtocovUSB_SIE_EP1_CNT0   ProtocovUSB_SIE_EP1_CNT0_PTR
#define ProtocovUSB_SIE_EP1_CNT1   ProtocovUSB_SIE_EP1_CNT1_PTR
#define ProtocovUSB_SIE_EP1_CR0    ProtocovUSB_SIE_EP1_CR0_PTR

#define ProtocovUSB_SIE_EP2_CNT0   ProtocovUSB_SIE_EP2_CNT0_PTR
#define ProtocovUSB_SIE_EP2_CNT1   ProtocovUSB_SIE_EP2_CNT1_PTR
#define ProtocovUSB_SIE_EP2_CR0    ProtocovUSB_SIE_EP2_CR0_PTR

#define ProtocovUSB_SIE_EP3_CNT0   ProtocovUSB_SIE_EP3_CNT0_PTR
#define ProtocovUSB_SIE_EP3_CNT1   ProtocovUSB_SIE_EP3_CNT1_PTR
#define ProtocovUSB_SIE_EP3_CR0    ProtocovUSB_SIE_EP3_CR0_PTR

#define ProtocovUSB_SIE_EP4_CNT0   ProtocovUSB_SIE_EP4_CNT0_PTR
#define ProtocovUSB_SIE_EP4_CNT1   ProtocovUSB_SIE_EP4_CNT1_PTR
#define ProtocovUSB_SIE_EP4_CR0    ProtocovUSB_SIE_EP4_CR0_PTR

#define ProtocovUSB_SIE_EP5_CNT0   ProtocovUSB_SIE_EP5_CNT0_PTR
#define ProtocovUSB_SIE_EP5_CNT1   ProtocovUSB_SIE_EP5_CNT1_PTR
#define ProtocovUSB_SIE_EP5_CR0    ProtocovUSB_SIE_EP5_CR0_PTR

#define ProtocovUSB_SIE_EP6_CNT0   ProtocovUSB_SIE_EP6_CNT0_PTR
#define ProtocovUSB_SIE_EP6_CNT1   ProtocovUSB_SIE_EP6_CNT1_PTR
#define ProtocovUSB_SIE_EP6_CR0    ProtocovUSB_SIE_EP6_CR0_PTR

#define ProtocovUSB_SIE_EP7_CNT0   ProtocovUSB_SIE_EP7_CNT0_PTR
#define ProtocovUSB_SIE_EP7_CNT1   ProtocovUSB_SIE_EP7_CNT1_PTR
#define ProtocovUSB_SIE_EP7_CR0    ProtocovUSB_SIE_EP7_CR0_PTR

#define ProtocovUSB_SIE_EP8_CNT0   ProtocovUSB_SIE_EP8_CNT0_PTR
#define ProtocovUSB_SIE_EP8_CNT1   ProtocovUSB_SIE_EP8_CNT1_PTR
#define ProtocovUSB_SIE_EP8_CR0    ProtocovUSB_SIE_EP8_CR0_PTR

#define ProtocovUSB_SOF0           ProtocovUSB_SOF0_PTR
#define ProtocovUSB_SOF1           ProtocovUSB_SOF1_PTR

#define ProtocovUSB_USB_CLK_EN     ProtocovUSB_USB_CLK_EN_PTR

#define ProtocovUSB_USBIO_CR0      ProtocovUSB_USBIO_CR0_PTR
#define ProtocovUSB_USBIO_CR1      ProtocovUSB_USBIO_CR1_PTR
#define ProtocovUSB_USBIO_CR2      ProtocovUSB_USBIO_CR2_PTR

#define ProtocovUSB_DM_INP_DIS_PTR     ( (reg8 *) ProtocovUSB_Dm__INP_DIS)
#define ProtocovUSB_DM_INP_DIS_REG     (*(reg8 *) ProtocovUSB_Dm__INP_DIS)
#define ProtocovUSB_DP_INP_DIS_PTR     ( (reg8 *) ProtocovUSB_Dp__INP_DIS)
#define ProtocovUSB_DP_INP_DIS_REG     (*(reg8 *) ProtocovUSB_Dp__INP_DIS)
#define ProtocovUSB_DP_INTSTAT_PTR     ( (reg8 *) ProtocovUSB_Dp__INTSTAT)
#define ProtocovUSB_DP_INTSTAT_REG     (*(reg8 *) ProtocovUSB_Dp__INTSTAT)
#define ProtocovUSB_DM_MASK            ProtocovUSB_Dm__0__MASK
#define ProtocovUSB_DP_MASK            ProtocovUSB_Dp__0__MASK

#define USBFS_SIE_EP_INT_EP1_MASK        (0x01u)
#define USBFS_SIE_EP_INT_EP2_MASK        (0x02u)
#define USBFS_SIE_EP_INT_EP3_MASK        (0x04u)
#define USBFS_SIE_EP_INT_EP4_MASK        (0x08u)
#define USBFS_SIE_EP_INT_EP5_MASK        (0x10u)
#define USBFS_SIE_EP_INT_EP6_MASK        (0x20u)
#define USBFS_SIE_EP_INT_EP7_MASK        (0x40u)
#define USBFS_SIE_EP_INT_EP8_MASK        (0x80u)

#define ProtocovUSB_ARB_EPX_SR_IN_BUF_FULL     (0x01u)
#define ProtocovUSB_ARB_EPX_SR_DMA_GNT         (0x02u)
#define ProtocovUSB_ARB_EPX_SR_BUF_OVER        (0x04u)
#define ProtocovUSB_ARB_EPX_SR_BUF_UNDER       (0x08u)

#define ProtocovUSB_ARB_EPX_INT_EN_ALL ProtocovUSB_ARB_EPX_INT_ALL

#define ProtocovUSB_CR1_BUS_ACTIVITY_SHIFT     (0x02u)

#define ProtocovUSB_BUS_RST_COUNT      ProtocovUSB_DEFUALT_BUS_RST_CNT

#define ProtocovUSB_ARB_INT_MASK       ProtocovUSB_DEFAULT_ARB_INT_EN

#if (CYDEV_CHIP_DIE_EXPECT == CYDEV_CHIP_DIE_LEOPARD)
    /* CY_PSOC3 interrupt registers */
    #define ProtocovUSB_USB_ISR_PRIOR  ((reg8 *) CYDEV_INTC_PRIOR0)
    #define ProtocovUSB_USB_ISR_SET_EN ((reg8 *) CYDEV_INTC_SET_EN0)
    #define ProtocovUSB_USB_ISR_CLR_EN ((reg8 *) CYDEV_INTC_CLR_EN0)
    #define ProtocovUSB_USB_ISR_VECT   ((cyisraddress *) CYDEV_INTC_VECT_MBASE)
#elif (CYDEV_CHIP_DIE_EXPECT == CYDEV_CHIP_DIE_PANTHER)
    /* CY_PSOC5LP interrupt registers */
    #define ProtocovUSB_USB_ISR_PRIOR  ((reg8 *) CYDEV_NVIC_PRI_0)
    #define ProtocovUSB_USB_ISR_SET_EN ((reg8 *) CYDEV_NVIC_SETENA0)
    #define ProtocovUSB_USB_ISR_CLR_EN ((reg8 *) CYDEV_NVIC_CLRENA0)
    #define ProtocovUSB_USB_ISR_VECT   ((cyisraddress *) CYDEV_NVIC_VECT_OFFSET)
#endif /*  CYDEV_CHIP_DIE_EXPECT */


#endif /* (CY_USBFS_ProtocovUSB_H) */


/* [] END OF FILE */
