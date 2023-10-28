/*******************************************************************************
* File Name: VehicleCAN.h
* Version 3.0
*
* Description:
*  Contains the function prototypes, constants and register definition
*  of the CAN Component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAN_VehicleCAN_H)
#define CY_CAN_VehicleCAN_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"
#include "cyapicallbacks.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component CAN_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

extern uint8 VehicleCAN_initVar;

#define VehicleCAN_INT_ISR_DISABLE                (0u)


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define VehicleCAN_ARB_LOST                       (0u)
#define VehicleCAN_OVERLOAD                       (0u)
#define VehicleCAN_BIT_ERR                        (0u)
#define VehicleCAN_STUFF_ERR                      (0u)
#define VehicleCAN_ACK_ERR                        (0u)
#define VehicleCAN_FORM_ERR                       (0u)
#define VehicleCAN_CRC_ERR                        (0u)
#define VehicleCAN_BUS_OFF                        (1u)
#define VehicleCAN_RX_MSG_LOST                    (1u)
#define VehicleCAN_TX_MESSAGE                     (0u)
#define VehicleCAN_RX_MESSAGE                     (1u)
#define VehicleCAN_ARB_LOST_USE_HELPER            (1u)
#define VehicleCAN_OVERLOAD_USE_HELPER            (1u)
#define VehicleCAN_BIT_ERR_USE_HELPER             (1u)
#define VehicleCAN_STUFF_ERR_USE_HELPER           (1u)
#define VehicleCAN_ACK_ERR_USE_HELPER             (1u)
#define VehicleCAN_FORM_ERR_USE_HELPER            (1u)
#define VehicleCAN_CRC_ERR_USE_HELPER             (1u)
#define VehicleCAN_BUS_OFF_USE_HELPER             (1u)
#define VehicleCAN_RX_MSG_LOST_USE_HELPER         (1u)
#define VehicleCAN_TX_MESSAGE_USE_HELPER          (1u)
#define VehicleCAN_RX_MESSAGE_USE_HELPER          (1u)

#if (!(CY_PSOC3 || CY_PSOC5))
    #define VehicleCAN_RTR_AUTO_MSG_SENT          (0u)
    #define VehicleCAN_STUCK_AT_ZERO              (0u)
    #define VehicleCAN_SST_FAILURE                (0u)

    #define VehicleCAN_RTR_MESSAGE_USE_HELPER     (1u)
    #define VehicleCAN_STUCK_AT_ZERO_USE_HELPER   (1u)
    #define VehicleCAN_SST_FAILURE_USE_HELPER     (1u)
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

#define VehicleCAN_ADVANCED_INTERRUPT_CFG         (0u)

/* TX/RX Function Enable */
#define VehicleCAN_TX0_FUNC_ENABLE     (0u)
#define VehicleCAN_TX1_FUNC_ENABLE     (0u)
#define VehicleCAN_TX2_FUNC_ENABLE     (0u)
#define VehicleCAN_TX3_FUNC_ENABLE     (0u)
#define VehicleCAN_TX4_FUNC_ENABLE     (0u)
#define VehicleCAN_TX5_FUNC_ENABLE     (0u)
#define VehicleCAN_TX6_FUNC_ENABLE     (0u)
#define VehicleCAN_TX7_FUNC_ENABLE     (0u)
#define VehicleCAN_RX0_FUNC_ENABLE     (0u)
#define VehicleCAN_RX1_FUNC_ENABLE     (0u)
#define VehicleCAN_RX2_FUNC_ENABLE     (0u)
#define VehicleCAN_RX3_FUNC_ENABLE     (0u)
#define VehicleCAN_RX4_FUNC_ENABLE     (0u)
#define VehicleCAN_RX5_FUNC_ENABLE     (0u)
#define VehicleCAN_RX6_FUNC_ENABLE     (0u)
#define VehicleCAN_RX7_FUNC_ENABLE     (0u)
#define VehicleCAN_RX8_FUNC_ENABLE     (0u)
#define VehicleCAN_RX9_FUNC_ENABLE     (0u)
#define VehicleCAN_RX10_FUNC_ENABLE    (0u)
#define VehicleCAN_RX11_FUNC_ENABLE    (0u)
#define VehicleCAN_RX12_FUNC_ENABLE    (0u)
#define VehicleCAN_RX13_FUNC_ENABLE    (0u)
#define VehicleCAN_RX14_FUNC_ENABLE    (0u)
#define VehicleCAN_RX15_FUNC_ENABLE    (0u)
#define VehicleCAN_RX_MAILBOX_TYPE     (0x0u)
#define VehicleCAN_TX_MAILBOX_TYPE     (0x0u)


/***************************************
*        Data Struct Definition
***************************************/

/* Struct for DATA of BASIC CAN mailbox */
typedef struct
{
    uint8 byte[8u];
} VehicleCAN_DATA_BYTES_MSG;

/* Struct for DATA of CAN RX register */
typedef struct
{
    reg8 byte[8u];
} VehicleCAN_DATA_BYTES;

/* Struct for 32-bit CAN register */
typedef struct
{
    reg8 byte[4u];
} VehicleCAN_REG_32;

/* Struct for BASIC CAN mailbox to send messages */
typedef struct
{
    uint32 id;
    uint8 rtr;
    uint8 ide;
    uint8 dlc;
    uint8 irq;
    #if (!(CY_PSOC3 || CY_PSOC5))
        uint8 sst;
    #endif /* (!(CY_PSOC3 || CY_PSOC5)) */
    VehicleCAN_DATA_BYTES_MSG *msg;
} VehicleCAN_TX_MSG;

/* Constant configuration of CAN RX */
typedef struct
{
    uint8 rxmailbox;
    uint32 rxcmd;
    uint32 rxamr;
    uint32 rxacr;
} VehicleCAN_RX_CFG;

/* Constant configuration of CAN TX */
typedef struct
{
    uint8 txmailbox;
    uint32 txcmd;
    uint32 txid;
} VehicleCAN_TX_CFG;

/* CAN RX registers */
typedef struct
{
    VehicleCAN_REG_32 rxcmd;
    VehicleCAN_REG_32 rxid;
    VehicleCAN_DATA_BYTES rxdata;
    VehicleCAN_REG_32 rxamr;
    VehicleCAN_REG_32 rxacr;
    VehicleCAN_REG_32 rxamrd;
    VehicleCAN_REG_32 rxacrd;
} VehicleCAN_RX_STRUCT;

/* CAN TX registers */
typedef struct
{
    VehicleCAN_REG_32 txcmd;
    VehicleCAN_REG_32 txid;
    VehicleCAN_DATA_BYTES txdata;
} VehicleCAN_TX_STRUCT;

/* Sleep Mode API Support */
typedef struct
{
    uint8  enableState;
    #if (CY_PSOC3 || CY_PSOC5)
        uint32 intSr;
        uint32 intEn;
        uint32 cmd;
        uint32 cfg;
    #endif /* CY_PSOC3 || CY_PSOC5 */
} VehicleCAN_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

uint8  VehicleCAN_Init(void) ;
uint8  VehicleCAN_Start(void) ;
uint8  VehicleCAN_Stop(void) ;
uint8  VehicleCAN_Enable(void) ;
uint8  VehicleCAN_GlobalIntEnable(void) ;
uint8  VehicleCAN_GlobalIntDisable(void) ;
uint8  VehicleCAN_SetPreScaler(uint16 bitrate) ;
uint8  VehicleCAN_SetArbiter(uint8 arbiter) ;
uint8  VehicleCAN_SetTsegSample(uint8 cfgTseg1, uint8 cfgTseg2, uint8 sjw, uint8 sm)
                                                ;
uint8  VehicleCAN_SetRestartType(uint8 reset) ;
uint8  VehicleCAN_SetEdgeMode(uint8 edge) ;
uint8  VehicleCAN_SetOpMode(uint8 opMode) ;
uint8  VehicleCAN_RXRegisterInit(reg32 *regAddr, uint32 config)
                                            ;
uint8  VehicleCAN_SetIrqMask(uint16 mask) ;
uint8  VehicleCAN_GetTXErrorFlag(void) ;
uint8  VehicleCAN_GetRXErrorFlag(void) ;
uint8  VehicleCAN_GetTXErrorCount(void) ;
uint8  VehicleCAN_GetRXErrorCount(void) ;
uint8  VehicleCAN_GetErrorState(void) ;
void   VehicleCAN_Sleep(void) ;
void   VehicleCAN_Wakeup(void) ;
void   VehicleCAN_SaveConfig(void) ;
void   VehicleCAN_RestoreConfig(void) ;

#if (!(CY_PSOC3 || CY_PSOC5))
    uint8  VehicleCAN_SetSwapDataEndianness(uint8 swap);
    uint8  VehicleCAN_SetErrorCaptureRegisterMode(uint8 ecrMode);
    uint32 VehicleCAN_ReadErrorCaptureRegister(void);
    uint8  VehicleCAN_ArmErrorCaptureRegister(void);
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

#if (VehicleCAN_ARB_LOST)
    void VehicleCAN_ArbLostIsr(void) ;
#endif /* VehicleCAN_ARB_LOST */
#if (VehicleCAN_OVERLOAD)
    void VehicleCAN_OvrLdErrorIsr(void) ;
#endif /* VehicleCAN_OVERLOAD */
#if (VehicleCAN_BIT_ERR)
    void VehicleCAN_BitErrorIsr(void) ;
#endif /* VehicleCAN_BIT_ERR */
#if (VehicleCAN_STUFF_ERR)
    void VehicleCAN_BitStuffErrorIsr(void) ;
#endif /* VehicleCAN_STUFF_ERR */
#if (VehicleCAN_ACK_ERR)
    void VehicleCAN_AckErrorIsr(void) ;
#endif /* VehicleCAN_ACK_ERR */
#if (VehicleCAN_FORM_ERR)
    void VehicleCAN_MsgErrorIsr(void) ;
#endif /* VehicleCAN_FORM_ERR */
#if (VehicleCAN_CRC_ERR)
    void VehicleCAN_CrcErrorIsr(void) ;
#endif /* VehicleCAN_CRC_ERR */
#if (VehicleCAN_BUS_OFF)
    void VehicleCAN_BusOffIsr(void) ;
#endif /* VehicleCAN_BUS_OFF */
#if (VehicleCAN_RX_MSG_LOST)
    void VehicleCAN_MsgLostIsr(void) ;
#endif /* VehicleCAN_RX_MSG_LOST */
#if (VehicleCAN_TX_MESSAGE)
   void VehicleCAN_MsgTXIsr(void) ;
#endif /* VehicleCAN_TX_MESSAGE */
#if (VehicleCAN_RX_MESSAGE)
    void VehicleCAN_MsgRXIsr(void) ;
#endif /* VehicleCAN_RX_MESSAGE */

#if (!(CY_PSOC3 || CY_PSOC5))
    #if (VehicleCAN_RTR_AUTO_MSG_SENT)
        void VehicleCAN_RtrAutoMsgSentIsr(void);
    #endif /* VehicleCAN_RTR_MESSAGE */
    #if (VehicleCAN_STUCK_AT_ZERO)
        void VehicleCAN_StuckAtZeroIsr(void);
    #endif /* VehicleCAN_STUCK_AT_ZERO */
    #if (VehicleCAN_SST_FAILURE)
        void VehicleCAN_SSTErrorIsr(void);
    #endif /* VehicleCAN_SST_ERROR */
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

uint8 VehicleCAN_RxBufConfig(const VehicleCAN_RX_CFG *rxConfig) \
                                   ;
uint8 VehicleCAN_TxBufConfig(const VehicleCAN_TX_CFG *txConfig) \
                                   ;
uint8 VehicleCAN_RxTxBuffersConfig(void) ;                                
uint8 VehicleCAN_SendMsg(const VehicleCAN_TX_MSG *message) ;
void  VehicleCAN_TxCancel(uint8 bufferId) ;
void  VehicleCAN_ReceiveMsg(uint8 rxMailbox) ;

#if (VehicleCAN_TX0_FUNC_ENABLE)
    uint8 VehicleCAN_SendMsg0(void) ;
#endif /* VehicleCAN_TX0_FUNC_ENABLE */
#if (VehicleCAN_TX1_FUNC_ENABLE)
    uint8 VehicleCAN_SendMsg1(void) ;
#endif /* VehicleCAN_TX1_FUNC_ENABLE */
#if (VehicleCAN_TX2_FUNC_ENABLE)
    uint8 VehicleCAN_SendMsg2(void) ;
#endif /* VehicleCAN_TX2_FUNC_ENABLE */
#if (VehicleCAN_TX3_FUNC_ENABLE)
    uint8 VehicleCAN_SendMsg3(void) ;
#endif /* VehicleCAN_TX3_FUNC_ENABLE */
#if (VehicleCAN_TX4_FUNC_ENABLE)
    uint8 VehicleCAN_SendMsg4(void) ;
#endif /* VehicleCAN_TX4_FUNC_ENABLE */
#if (VehicleCAN_TX5_FUNC_ENABLE)
    uint8 VehicleCAN_SendMsg5(void) ;
#endif /* VehicleCAN_TX5_FUNC_ENABLE */
#if (VehicleCAN_TX6_FUNC_ENABLE)
    uint8 VehicleCAN_SendMsg6(void) ;
#endif /* VehicleCAN_TX6_FUNC_ENABLE */
#if (VehicleCAN_TX7_FUNC_ENABLE)
    uint8 VehicleCAN_SendMsg7(void) ;
#endif /* VehicleCAN_TX7_FUNC_ENABLE */
#if (VehicleCAN_RX0_FUNC_ENABLE)
    void VehicleCAN_ReceiveMsg0(void) ;
#endif /* VehicleCAN_RX0_FUNC_ENABLE */
#if (VehicleCAN_RX1_FUNC_ENABLE)
    void VehicleCAN_ReceiveMsg1(void) ;
#endif /* VehicleCAN_RX1_FUNC_ENABLE */
#if (VehicleCAN_RX2_FUNC_ENABLE)
    void VehicleCAN_ReceiveMsg2(void) ;
#endif /* VehicleCAN_RX2_FUNC_ENABLE */
#if (VehicleCAN_RX3_FUNC_ENABLE)
    void VehicleCAN_ReceiveMsg3(void) ;
#endif /* VehicleCAN_RX3_FUNC_ENABLE */
#if (VehicleCAN_RX4_FUNC_ENABLE)
    void VehicleCAN_ReceiveMsg4(void) ;
#endif /* VehicleCAN_RX4_FUNC_ENABLE */
#if (VehicleCAN_RX5_FUNC_ENABLE)
    void VehicleCAN_ReceiveMsg5(void) ;
#endif /* VehicleCAN_RX5_FUNC_ENABLE */
#if (VehicleCAN_RX6_FUNC_ENABLE)
    void VehicleCAN_ReceiveMsg6(void) ;
#endif /* VehicleCAN_RX6_FUNC_ENABLE */
#if (VehicleCAN_RX7_FUNC_ENABLE)
    void VehicleCAN_ReceiveMsg7(void) ;
#endif /* VehicleCAN_RX7_FUNC_ENABLE */
#if (VehicleCAN_RX8_FUNC_ENABLE)
    void VehicleCAN_ReceiveMsg8(void) ;
#endif /* VehicleCAN_RX8_FUNC_ENABLE */
#if (VehicleCAN_RX9_FUNC_ENABLE)
    void VehicleCAN_ReceiveMsg9(void) ;
#endif /* VehicleCAN_RX9_FUNC_ENABLE */
#if (VehicleCAN_RX10_FUNC_ENABLE)
    void VehicleCAN_ReceiveMsg10(void) ;
#endif /* VehicleCAN_RX10_FUNC_ENABLE */
#if (VehicleCAN_RX11_FUNC_ENABLE)
    void VehicleCAN_ReceiveMsg11(void) ;
#endif /* VehicleCAN_RX11_FUNC_ENABLE */
#if (VehicleCAN_RX12_FUNC_ENABLE)
    void VehicleCAN_ReceiveMsg12(void) ;
#endif /* VehicleCAN_RX12_FUNC_ENABLE */
#if (VehicleCAN_RX13_FUNC_ENABLE)
    void VehicleCAN_ReceiveMsg13(void) ;
#endif /* VehicleCAN_RX13_FUNC_ENABLE */
#if (VehicleCAN_RX14_FUNC_ENABLE)
    void VehicleCAN_ReceiveMsg14(void) ;
#endif /* VehicleCAN_RX14_FUNC_ENABLE */
#if (VehicleCAN_RX15_FUNC_ENABLE)
    void VehicleCAN_ReceiveMsg15(void) ;
#endif /* VehicleCAN_RX15_FUNC_ENABLE */

#if(!VehicleCAN_INT_ISR_DISABLE)
    /* Interrupt handler */
    CY_ISR_PROTO(VehicleCAN_ISR);
#endif /* !VehicleCAN_INT_ISR_DISABLE */


/***************************************
*           API Constants
***************************************/

#if (!VehicleCAN_INT_ISR_DISABLE)
    /* Number of VehicleCAN_isr interrupt */
    #define VehicleCAN_ISR_NUMBER            ((uint8) VehicleCAN_isr__INTC_NUMBER)
    /* Priority of VehicleCAN_isr interrupt */
    #define VehicleCAN_ISR_PRIORITY          ((uint8) VehicleCAN_isr__INTC_PRIOR_NUM)
#endif /* !VehicleCAN_INT_ISR_DISABLE */

/* One bit time in CAN clock cycles */
#define VehicleCAN_ONE_BIT_TIME              ((VehicleCAN_BITRATE + 1u) * \
        ((VehicleCAN_CFG_REG_TSEG1 + 1u) + (VehicleCAN_CFG_REG_TSEG2 + 1u) + 1u))

/* Timeout for CAN state machine to switch operation mode to Run */
#define VehicleCAN_MODE_STATE_RUN_TIMEOUT    (12u * VehicleCAN_ONE_BIT_TIME)
/* Timeout for CAN state machine to switch operation mode to Stop */
#define VehicleCAN_MODE_STATE_STOP_TIMEOUT   (160u * VehicleCAN_ONE_BIT_TIME)

/* One or more parameters to function were invalid. */
#define VehicleCAN_FAIL                      (0x01u)
#define VehicleCAN_OUT_OF_RANGE              (0x02u)

#if (CY_PSOC3 || CY_PSOC5)
    /* PM_ACT_CFG (Active Power Mode CFG Register) */
    #define VehicleCAN_ACT_PWR_EN            (VehicleCAN_CanIP__PM_ACT_MSK)    /* Power enable mask */
    /* PM_STBY_CFG (Alternate Active (Standby) Power Mode CFG Register) */
    #define VehicleCAN_STBY_PWR_EN           (VehicleCAN_CanIP__PM_STBY_MSK)   /* Power enable mask */
#endif /* CY_PSOC3 || CY_PSOC5 */

/* Number of TX and RX mailboxes */
#define VehicleCAN_NUMBER_OF_TX_MAILBOXES    (8u)
#define VehicleCAN_NUMBER_OF_RX_MAILBOXES    (16u)

/* Error status of CAN */
#define VehicleCAN_ERROR_ACTIVE              (0x00u)
#define VehicleCAN_ERROR_PASIVE              (0x01u)
#define VehicleCAN_ERROR_BUS_OFF             (0x10u)

/* Operation mode */
#define VehicleCAN_INITIAL_MODE              (0x00u)
#define VehicleCAN_STOP_MODE                 (0x00u)
#define VehicleCAN_ACTIVE_RUN_MODE           (0x01u)
#define VehicleCAN_LISTEN_ONLY_MODE          (0x02u)
#if (!(CY_PSOC3 || CY_PSOC5))
    #define VehicleCAN_INTERNAL_LOOP_BACK    (0x06u)
    #define VehicleCAN_EXTERNAL_LOOP_BACK    (0x04u)
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

/* TX Defines to link mailbox names with mailbox numbers */
#define VehicleCAN_TX_MAILBOX_0        (0u)
#define VehicleCAN_TX_MAILBOX_1        (1u)
#define VehicleCAN_TX_MAILBOX_2        (2u)
#define VehicleCAN_TX_MAILBOX_3        (3u)
#define VehicleCAN_TX_MAILBOX_4        (4u)
#define VehicleCAN_TX_MAILBOX_5        (5u)
#define VehicleCAN_TX_MAILBOX_6        (6u)
#define VehicleCAN_TX_MAILBOX_7        (7u)

/* RX Defines to link mailbox names with mailbox numbers */
#define VehicleCAN_RX_MAILBOX_0        (0u)
#define VehicleCAN_RX_MAILBOX_1        (1u)
#define VehicleCAN_RX_MAILBOX_2        (2u)
#define VehicleCAN_RX_MAILBOX_3        (3u)
#define VehicleCAN_RX_MAILBOX_4        (4u)
#define VehicleCAN_RX_MAILBOX_5        (5u)
#define VehicleCAN_RX_MAILBOX_6        (6u)
#define VehicleCAN_RX_MAILBOX_7        (7u)
#define VehicleCAN_RX_MAILBOX_8        (8u)
#define VehicleCAN_RX_MAILBOX_9        (9u)
#define VehicleCAN_RX_MAILBOX_10       (10u)
#define VehicleCAN_RX_MAILBOX_11       (11u)
#define VehicleCAN_RX_MAILBOX_12       (12u)
#define VehicleCAN_RX_MAILBOX_13       (13u)
#define VehicleCAN_RX_MAILBOX_14       (14u)
#define VehicleCAN_RX_MAILBOX_15       (15u)


/***************************************
*    Initial Parameter Constants
***************************************/

/* General */
#define VehicleCAN_BITRATE                   (5u)
#define VehicleCAN_CFG_REG_TSEG1             (7u - 1u)
#define VehicleCAN_CFG_REG_TSEG2             (5u - 1u)
#define VehicleCAN_CFG_REG_SJW               (4u - 1u)
#define VehicleCAN_SAMPLING_MODE             (1u)
#define VehicleCAN_ARBITER                   (0u)
#define VehicleCAN_RESET_TYPE                (1u)
#define VehicleCAN_SYNC_EDGE                 (1u)

#if (!(CY_PSOC3 || CY_PSOC5))
    #define VehicleCAN_SWAP_DATA_END         (0u)
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

/* Interrupts */
#define VehicleCAN_INT_ENABLE                (1u)

#if (CY_PSOC3 || CY_PSOC5)
    #define VehicleCAN_INIT_INTERRUPT_MASK (((uint16) VehicleCAN_INT_ENABLE) | \
                ((uint16) ((uint16) VehicleCAN_ARB_LOST    <<  VehicleCAN_ARBITRATION_LOST_SHIFT)) | \
                ((uint16) ((uint16) VehicleCAN_OVERLOAD    <<  VehicleCAN_OVERLOAD_ERROR_SHIFT))   | \
                ((uint16) ((uint16) VehicleCAN_BIT_ERR     <<  VehicleCAN_BIT_ERROR_SHIFT))        | \
                ((uint16) ((uint16) VehicleCAN_STUFF_ERR   <<  VehicleCAN_STUFF_ERROR_SHIFT))      | \
                ((uint16) ((uint16) VehicleCAN_ACK_ERR     <<  VehicleCAN_ACK_ERROR_SHIFT))        | \
                ((uint16) ((uint16) VehicleCAN_FORM_ERR    <<  VehicleCAN_FORM_ERROR_SHIFT))       | \
                ((uint16) ((uint16) VehicleCAN_CRC_ERR     << (VehicleCAN_ONE_BYTE_OFFSET          + \
                                                                     VehicleCAN_CRC_ERROR_SHIFT)))       | \
                ((uint16) ((uint16) VehicleCAN_BUS_OFF     << (VehicleCAN_ONE_BYTE_OFFSET          + \
                                                                     VehicleCAN_BUS_OFF_SHIFT)))         | \
                ((uint16) ((uint16) VehicleCAN_RX_MSG_LOST << (VehicleCAN_ONE_BYTE_OFFSET          + \
                                                                     VehicleCAN_RX_MSG_LOST_SHIFT)))     | \
                ((uint16) ((uint16) VehicleCAN_TX_MESSAGE  << (VehicleCAN_ONE_BYTE_OFFSET          + \
                                                                     VehicleCAN_TX_MESSAGE_SHIFT)))      | \
                ((uint16) ((uint16) VehicleCAN_RX_MESSAGE  << (VehicleCAN_ONE_BYTE_OFFSET          + \
                                                                     VehicleCAN_RX_MESSAGE_SHIFT))))
#else /* CY_PSOC4 */
    #define VehicleCAN_INIT_INTERRUPT_MASK    (((uint16) VehicleCAN_INT_ENABLE) | \
                ((uint16) ((uint16) VehicleCAN_ARB_LOST    <<  VehicleCAN_ARBITRATION_LOST_SHIFT)) | \
                ((uint16) ((uint16) VehicleCAN_OVERLOAD    <<  VehicleCAN_OVERLOAD_ERROR_SHIFT))   | \
                ((uint16) ((uint16) VehicleCAN_BIT_ERR     <<  VehicleCAN_BIT_ERROR_SHIFT))        | \
                ((uint16) ((uint16) VehicleCAN_STUFF_ERR   <<  VehicleCAN_STUFF_ERROR_SHIFT))      | \
                ((uint16) ((uint16) VehicleCAN_ACK_ERR     <<  VehicleCAN_ACK_ERROR_SHIFT))        | \
                ((uint16) ((uint16) VehicleCAN_FORM_ERR    <<  VehicleCAN_FORM_ERROR_SHIFT))       | \
                ((uint16) ((uint16) VehicleCAN_CRC_ERR     <<  VehicleCAN_CRC_ERROR_SHIFT))        | \
                ((uint16) ((uint16) VehicleCAN_BUS_OFF     <<  VehicleCAN_BUS_OFF_SHIFT))          | \
                ((uint16) ((uint16) VehicleCAN_RX_MSG_LOST <<  VehicleCAN_RX_MSG_LOST_SHIFT))      | \
                ((uint16) ((uint16) VehicleCAN_TX_MESSAGE  <<  VehicleCAN_TX_MESSAGE_SHIFT))       | \
                ((uint16) ((uint16) VehicleCAN_RX_MESSAGE  <<  VehicleCAN_RX_MESSAGE_SHIFT))       | \
                ((uint16) ((uint16) VehicleCAN_RTR_AUTO_MSG_SENT  << VehicleCAN_RTR_MSG_SHIFT))    | \
                ((uint16) ((uint16) VehicleCAN_STUCK_AT_ZERO << VehicleCAN_STUCK_AT_ZERO_SHIFT))   | \
                ((uint16) ((uint16) VehicleCAN_SST_FAILURE   << VehicleCAN_SST_FAILURE_SHIFT)))
#endif /* (CY_PSOC3 || CY_PSOC5) */


/***************************************
*             Registers
***************************************/

#if (CY_PSOC3 || CY_PSOC5)
#define VehicleCAN_TX          ( (volatile VehicleCAN_TX_STRUCT XDATA *) VehicleCAN_CanIP__TX0_CMD)
#define VehicleCAN_RX          ( (volatile VehicleCAN_RX_STRUCT XDATA *) VehicleCAN_CanIP__RX0_CMD)
#define VehicleCAN_INT_SR_REG  (*(volatile VehicleCAN_REG_32 XDATA *) VehicleCAN_CanIP__CSR_INT_SR)
#define VehicleCAN_INT_SR_PTR  ( (reg32 *) VehicleCAN_CanIP__CSR_INT_SR)
#define VehicleCAN_INT_EN_REG  (*(volatile VehicleCAN_REG_32 XDATA *) VehicleCAN_CanIP__CSR_INT_EN)
#define VehicleCAN_INT_EN_PTR  ( (reg32 *) VehicleCAN_CanIP__CSR_INT_EN)
#define VehicleCAN_BUF_SR_REG  (*(volatile VehicleCAN_REG_32 XDATA *) VehicleCAN_CanIP__CSR_BUF_SR)
#define VehicleCAN_BUF_SR_PTR  ( (reg32 *) VehicleCAN_CanIP__CSR_BUF_SR)
#define VehicleCAN_ERR_SR_REG  (*(volatile VehicleCAN_REG_32 XDATA *) VehicleCAN_CanIP__CSR_ERR_SR)
#define VehicleCAN_ERR_SR_PTR  ( (reg32 *) VehicleCAN_CanIP__CSR_ERR_SR)
#define VehicleCAN_CMD_REG     (*(volatile VehicleCAN_REG_32 XDATA *) VehicleCAN_CanIP__CSR_CMD)
#define VehicleCAN_CMD_PTR     ( (reg32 *) VehicleCAN_CanIP__CSR_CMD)
#define VehicleCAN_CFG_REG     (*(volatile VehicleCAN_REG_32 XDATA *) VehicleCAN_CanIP__CSR_CFG)
#define VehicleCAN_CFG_PTR     ( (reg32 *) VehicleCAN_CanIP__CSR_CFG)

/* Power manager */
#define VehicleCAN_PM_ACT_CFG_REG           (*(reg8 *) VehicleCAN_CanIP__PM_ACT_CFG)
#define VehicleCAN_PM_ACT_CFG_PTR           ( (reg8 *) VehicleCAN_CanIP__PM_ACT_CFG)
#define VehicleCAN_PM_STBY_CFG_REG          (*(reg8 *) VehicleCAN_CanIP__PM_STBY_CFG)
#define VehicleCAN_PM_STBY_CFG_PTR          ( (reg8 *) VehicleCAN_CanIP__PM_STBY_CFG)

#define VehicleCAN_RX_FIRST_REGISTER_PTR    ((reg32 *) VehicleCAN_CanIP__RX0_CMD)
#define VehicleCAN_RX_LAST_REGISTER_PTR     ((reg32 *) VehicleCAN_CanIP__RX15_ACRD)

#else /* CY_PSOC4 */
#define VehicleCAN_TX    ((volatile VehicleCAN_TX_STRUCT XDATA *) VehicleCAN_CanIP__CAN_TX0_CONTROL)
#define VehicleCAN_RX    ((volatile VehicleCAN_RX_STRUCT XDATA *) VehicleCAN_CanIP__CAN_RX0_CONTROL)
#define VehicleCAN_TX_REG                   (*(reg32 *) VehicleCAN_CanIP__CAN_TX0_CONTROL)
#define VehicleCAN_TX_PTR                   ( (reg32 *) VehicleCAN_CanIP__CAN_TX0_CONTROL)
#define VehicleCAN_RX_REG                   (*(reg32 *) VehicleCAN_CanIP__CAN_RX0_CONTROL)
#define VehicleCAN_RX_PTR                   ( (reg32 *) VehicleCAN_CanIP__CAN_RX0_CONTROL)
#define VehicleCAN_INT_SR_REG               (*(reg32 *) VehicleCAN_CanIP__INT_STATUS)
#define VehicleCAN_INT_SR_PTR               ( (reg32 *) VehicleCAN_CanIP__INT_STATUS)
#define VehicleCAN_INT_EN_REG               (*(reg32 *) VehicleCAN_CanIP__INT_EBL)
#define VehicleCAN_INT_EN_PTR               ( (reg32 *) VehicleCAN_CanIP__INT_EBL)
#define VehicleCAN_BUF_SR_REG               (*(reg32 *) VehicleCAN_CanIP__BUFFER_STATUS)
#define VehicleCAN_BUF_SR_PTR               ( (reg32 *) VehicleCAN_CanIP__BUFFER_STATUS)
#define VehicleCAN_ERR_SR_REG               (*(reg32 *) VehicleCAN_CanIP__ERROR_STATUS)
#define VehicleCAN_ERR_SR_PTR               ( (reg32 *) VehicleCAN_CanIP__ERROR_STATUS)
#define VehicleCAN_CNTL_REG                 (*(reg32 *) VehicleCAN_CanIP__CNTL)
#define VehicleCAN_CNTL_PTR                 ( (reg32 *) VehicleCAN_CanIP__CNTL)
#define VehicleCAN_CMD_REG                  (*(reg32 *) VehicleCAN_CanIP__COMMAND)
#define VehicleCAN_CMD_PTR                  ( (reg32 *) VehicleCAN_CanIP__COMMAND)
#define VehicleCAN_CFG_REG                  (*(reg32 *) VehicleCAN_CanIP__CONFIG)
#define VehicleCAN_CFG_PTR                  ( (reg32 *) VehicleCAN_CanIP__CONFIG)
#define VehicleCAN_ECR_REG                  (*(reg32 *) VehicleCAN_CanIP__ECR)
#define VehicleCAN_ECR_PTR                  ( (reg32 *) VehicleCAN_CanIP__ECR)
#define VehicleCAN_RX_FIRST_REGISTER_PTR    ( (reg32 *) VehicleCAN_CanIP__CAN_RX0_CONTROL)
#define VehicleCAN_RX_LAST_REGISTER_PTR     ( (reg32 *) VehicleCAN_CanIP__CAN_RX15_ACR_DATA)

#define VehicleCAN_TX_DATA_LO_REG(i)        (*(reg32 *) (&VehicleCAN_TX[i].txdata))
#define VehicleCAN_TX_DATA_HI_REG(i)        (*(reg32 *) ((uint32) (&VehicleCAN_TX[i].txdata) + \
                                                  VehicleCAN_DATA_HIGH_ADDR))
#define VehicleCAN_RX_DATA_LO_REG(i)        (*(reg32 *) (&VehicleCAN_RX[i].rxdata))
#define VehicleCAN_RX_DATA_HI_REG(i)        (*(reg32 *) ((uint32) (&VehicleCAN_RX[i].rxdata) + \
                                                  VehicleCAN_DATA_HIGH_ADDR))
#endif /* (CY_PSOC3 || CY_PSOC5) */

#define VehicleCAN_TX_CMD_PTR(i)            ( (reg32 *) (&VehicleCAN_TX[i].txcmd))
#define VehicleCAN_TX_CMD_REG(i)            (*(reg32 *) (&VehicleCAN_TX[i].txcmd))
#define VehicleCAN_RX_CMD_PTR(i)            ( (reg32 *) (&VehicleCAN_RX[i].rxcmd))
#define VehicleCAN_RX_CMD_REG(i)            (*(reg32 *) (&VehicleCAN_RX[i].rxcmd))
#define VehicleCAN_RX_ID_PTR(i)             ( (reg32 *) (&VehicleCAN_RX[i].rxid))
#define VehicleCAN_RX_ID_REG(i)             (*(reg32 *) (&VehicleCAN_RX[i].rxid))
#define VehicleCAN_TX_ID_PTR(i)             ( (reg32 *) (&VehicleCAN_TX[i].txid))
#define VehicleCAN_TX_ID_REG(i)             (*(reg32 *) (&VehicleCAN_TX[i].txid))


/***************************************
*        Register Constants
***************************************/

/* Run/Stop mode */
#define VehicleCAN_MODE_STOP                (0x00u)
#define VehicleCAN_MODE_START               (0x01u)

/* Transmit buffer arbiter */
#define VehicleCAN_ROUND_ROBIN              (0x00u)
#define VehicleCAN_FIXED_PRIORITY           (0x01u)

/* Restart type */
#define VehicleCAN_MANUAL_RESTART           (0x00u)
#define VehicleCAN_AUTO_RESTART             (0x01u)

/* Sampling mode */
#define VehicleCAN_ONE_SAMPLE_POINT         (0x00u)
#define VehicleCAN_THREE_SAMPLE_POINTS      (0x01u)

/* Edge mode */
#define VehicleCAN_EDGE_R_TO_D              (0x00u)
#define VehicleCAN_BOTH_EDGES               (0x01u)

/* Extended identifier */
#define VehicleCAN_STANDARD_MESSAGE         (0x00u)
#define VehicleCAN_EXTENDED_MESSAGE         (0x01u)

/* Write Protect Mask for Basic and Full mailboxes */
#define VehicleCAN_TX_WPN_CLEAR           ((uint32) (~VehicleCAN_TX_WPN_SET))
#define VehicleCAN_RX_WPN_CLEAR           ((uint32) (~VehicleCAN_RX_WPN_SET))
#define VehicleCAN_TX_RSVD_MASK           ((uint32) 0x00FF00FFu)
#define VehicleCAN_TX_READ_BACK_MASK      (VehicleCAN_TX_WPN_CLEAR & VehicleCAN_TX_RSVD_MASK)
#define VehicleCAN_RX_READ_BACK_MASK      (VehicleCAN_RX_WPN_CLEAR & VehicleCAN_TX_RSVD_MASK)
#define VehicleCAN_RX_CMD_REG_WIDTH       (0x20u)

#if (CY_PSOC3 || CY_PSOC5)
    #define VehicleCAN_TX_WPN_SET         (((uint32) ((uint32) 0x00000001u << VehicleCAN_TX_WPNL_SHIFT)) | \
            ((uint32) ((uint32) 0x00000001u << (VehicleCAN_TWO_BYTE_OFFSET + VehicleCAN_TX_WPNH_SHIFT))))
    #define VehicleCAN_RX_WPN_SET         (((uint32) ((uint32) 0x00000001u << VehicleCAN_RX_WPNL_SHIFT)) | \
            ((uint32) ((uint32) 0x00000001u << (VehicleCAN_TWO_BYTE_OFFSET + VehicleCAN_RX_WPNH_SHIFT))))
#else  /* CY_PSOC4 */
    #define VehicleCAN_TX_WPN_SET         (((uint32) ((uint32) 0x00000001u << VehicleCAN_TX_WPNL_SHIFT)) | \
            ((uint32) ((uint32) 0x00000001u << VehicleCAN_TX_WPNH_SHIFT)))
    #define VehicleCAN_RX_WPN_SET         (((uint32) ((uint32) 0x00000001u << VehicleCAN_RX_WPNL_SHIFT)) | \
            ((uint32) ((uint32) 0x00000001u << VehicleCAN_RX_WPNH_SHIFT)))

    /* CAN IP Block Enable */
    #define VehicleCAN_IP_ENABLE_SHIFT    (31u)
    #define VehicleCAN_IP_ENABLE          ((uint32) ((uint32) 0x00000001u << VehicleCAN_IP_ENABLE_SHIFT))

    /* Error Capture register mode setting */
    #define VehicleCAN_ECR_FREE_RUNNING   (0x00u)
    #define VehicleCAN_ECR_ERROR_CAPTURE  (0x01u)

    /* Swap Endian */
    #define VehicleCAN_SWAP_ENDIANNESS_DISABLE  (0x00u)
    #define VehicleCAN_SWAP_ENDIANNESS_ENABLE   (0x01u)
#endif /* (CY_PSOC3 || CY_PSOC5) */

/* TX send message */
#define VehicleCAN_TX_REQUEST_PENDING     (0x01u)
#define VehicleCAN_RETRY_NUMBER           (0x03u)
#define VehicleCAN_SEND_MESSAGE_SHIFT     (0u)
#define VehicleCAN_SEND_MESSAGE           ((uint32) ((uint32) 0x00000001u << VehicleCAN_SEND_MESSAGE_SHIFT))

/* Offsets to maintain bytes within uint32 */
#define VehicleCAN_ONE_BYTE_OFFSET        (8u)
#define VehicleCAN_TWO_BYTE_OFFSET        (16u)
#define VehicleCAN_THREE_BYTE_OFFSET      (24u)

#if (CY_PSOC3 || CY_PSOC5)
    /* Set/Clear bits macro for VehicleCAN_RX mailbox(i) */
    /* Bit 0 within RX_CMD[i] */
    #define VehicleCAN_RX_ACK_MSG_SHIFT       (0u)
    #define VehicleCAN_RX_ACK_MSG             ((uint8) ((uint8) 0x01u << VehicleCAN_RX_ACK_MSG_SHIFT))
    /* Bit 2 within RX_CMD[i] */
    #define VehicleCAN_RX_RTR_ABORT_SHIFT     (2u)
    #define VehicleCAN_RX_RTR_ABORT_MASK      ((uint8) ((uint8) 0x01u << VehicleCAN_RX_RTR_ABORT_SHIFT))
    /* Bit 3 within RX_CMD[i] */
    #define VehicleCAN_RX_BUF_ENABLE_SHIFT    (3u)
    #define VehicleCAN_RX_BUF_ENABLE_MASK     ((uint8) ((uint8) 0x01u << VehicleCAN_RX_BUF_ENABLE_SHIFT))
    /* Bit 4 within RX_CMD[i] */
    #define VehicleCAN_RX_RTRREPLY_SHIFT      (4u)
    #define VehicleCAN_RX_RTRREPLY_MASK       ((uint8) ((uint8) 0x01u << VehicleCAN_RX_RTRREPLY_SHIFT))
    /* Bit 5 within RX_CMD[i] */
    #define VehicleCAN_RX_INT_ENABLE_SHIFT    (5u)
    #define VehicleCAN_RX_INT_ENABLE_MASK     ((uint8) ((uint8) 0x01u << VehicleCAN_RX_INT_ENABLE_SHIFT))
    /* Bit 6 within RX_CMD[i] */
    #define VehicleCAN_RX_LINKING_SHIFT       (6u)
    #define VehicleCAN_RX_LINKING_MASK        ((uint8) ((uint8) 0x01u << VehicleCAN_RX_LINKING_SHIFT))
    /* Bit 7 within RX_CMD[i] */
    #define VehicleCAN_RX_WPNL_SHIFT          (7u)
    #define VehicleCAN_RX_WPNL_MASK           ((uint8) ((uint8) 0x01u << VehicleCAN_RX_WPNL_SHIFT))
    /* Bits 19-16 within RX_CMD[i] */
    #define VehicleCAN_RX_DLC_VALUE_SHIFT     (0u)
    #define VehicleCAN_RX_DLC_VALUE_MASK      ((uint8) ((uint8) 0x0Fu << VehicleCAN_RX_DLC_VALUE_SHIFT))
    /* Bit 20 within RX_CMD[i] */
    #define VehicleCAN_RX_IDE_SHIFT           (4u)
    #define VehicleCAN_RX_IDE_MASK            ((uint8) ((uint8) 0x01u << VehicleCAN_RX_IDE_SHIFT))
    /* Bit 23 within RX_CMD[i] */
    #define VehicleCAN_RX_WPNH_SHIFT          (7u)
    #define VehicleCAN_RX_WPNH_MASK           ((uint8) ((uint8) 0x01u << VehicleCAN_RX_WPNH_SHIFT))

    #define VehicleCAN_RX_ACK_MESSAGE(i)    (VehicleCAN_RX[i].rxcmd.byte[0u] |= VehicleCAN_RX_ACK_MSG)
    #define VehicleCAN_RX_RTR_ABORT_MESSAGE(i) \
            (VehicleCAN_RX[i].rxcmd.byte[0u] |= VehicleCAN_RX_RTR_ABORT_MASK)
    #define VehicleCAN_RX_BUF_ENABLE(i)      \
            (VehicleCAN_RX[i].rxcmd.byte[0u] |= VehicleCAN_RX_BUF_ENABLE_MASK)
    #define VehicleCAN_RX_BUF_DISABLE(i)     \
            (VehicleCAN_RX[i].rxcmd.byte[0u] &= (uint8) (~VehicleCAN_RX_BUF_ENABLE_MASK))
    #define VehicleCAN_SET_RX_RTRREPLY(i)    \
            (VehicleCAN_RX[i].rxcmd.byte[0u] |= VehicleCAN_RX_RTRREPLY_MASK)
    #define VehicleCAN_CLEAR_RX_RTRREPLY(i)  \
            (VehicleCAN_RX[i].rxcmd.byte[0u] &= (uint8) (~VehicleCAN_RX_RTRREPLY_MASK))
    #define VehicleCAN_RX_INT_ENABLE(i)      \
            (VehicleCAN_RX[i].rxcmd.byte[0u] |= VehicleCAN_RX_INT_ENABLE_MASK)
    #define VehicleCAN_RX_INT_DISABLE(i)     \
            (VehicleCAN_RX[i].rxcmd.byte[0u] &= (uint8) (~VehicleCAN_RX_INT_ENABLE_MASK))
    #define VehicleCAN_SET_RX_LINKING(i)     \
            (VehicleCAN_RX[i].rxcmd.byte[0u] |= VehicleCAN_RX_LINKING_MASK)
    #define VehicleCAN_CLEAR_RX_LINKING(i)   \
            (VehicleCAN_RX[i].rxcmd.byte[0u] &= (uint8) (~VehicleCAN_RX_LINKING_MASK))
    #define VehicleCAN_SET_RX_WNPL(i)     (VehicleCAN_RX[i].rxcmd.byte[0u] |= VehicleCAN_RX_WPNL_MASK)
    #define VehicleCAN_CLEAR_RX_WNPL(i)      \
            (VehicleCAN_RX[i].rxcmd.byte[0u] &= (uint8) (~VehicleCAN_RX_WPNL_MASK))
    #define VehicleCAN_SET_RX_WNPH(i)     (VehicleCAN_RX[i].rxcmd.byte[2u] |= VehicleCAN_RX_WPNH_MASK)
    #define VehicleCAN_CLEAR_RX_WNPH(i)      \
            (VehicleCAN_RX[i].rxcmd.byte[2u] &= (uint8) (~VehicleCAN_RX_WPNH_MASK))
    #define VehicleCAN_GET_DLC(i)            \
            (VehicleCAN_RX[i].rxcmd.byte[2u] & VehicleCAN_RX_DLC_VALUE_MASK)
    #define VehicleCAN_GET_RX_IDE(i)         ((uint8) \
            (VehicleCAN_RX[i].rxcmd.byte[2u] & VehicleCAN_RX_IDE_MASK) >> VehicleCAN_RX_IDE_SHIFT)
    #define VehicleCAN_GET_RX_ID(i)          ((VehicleCAN_GET_RX_IDE(i)) ? \
            (CY_GET_REG32(VehicleCAN_RX_ID_PTR(i)) >> VehicleCAN_SET_TX_ID_EXTENDED_MSG_SHIFT) : \
            (CY_GET_REG32(VehicleCAN_RX_ID_PTR(i)) >> VehicleCAN_SET_TX_ID_STANDARD_MSG_SHIFT))

    /* Set/Clear bits macro for VehicleCAN_TX mailbox(i) */
    /* Bit 0 within TX_CMD[i] */
    #define VehicleCAN_TX_TRANSMIT_REQUEST_SHIFT (0u)
    #define VehicleCAN_TX_TRANSMIT_REQUEST ((uint8) ((uint8) 0x01u << VehicleCAN_TX_TRANSMIT_REQUEST_SHIFT))
    /* Bit 1 within TX_CMD[i] */
    #define VehicleCAN_TX_ABORT_SHIFT        (1u)
    #define VehicleCAN_TX_ABORT_MASK         ((uint8) ((uint8) 0x01u << VehicleCAN_TX_ABORT_SHIFT))
    /* Bit 2 within TX_CMD[i] */
    #define VehicleCAN_TRANSMIT_INT_ENABLE   (0x01u)
    #define VehicleCAN_TRANSMIT_INT_DISABLE  (0x00u)
    #define VehicleCAN_TX_INT_ENABLE_SHIFT   (2u)
    #define VehicleCAN_TX_INT_ENABLE_MASK    \
            ((uint32) ((uint32) 0x00000001u << VehicleCAN_TX_INT_ENABLE_SHIFT))
    /* Bit 3 within TX_CMD[i] */
    #define VehicleCAN_TX_WPNL_SHIFT         (3u)
    #define VehicleCAN_TX_WPNL_MASK          ((uint8) ((uint8) 0x01u << VehicleCAN_TX_WPNL_SHIFT))
    /* Bits 19-16 within TX_CMD[i] */
    #define VehicleCAN_TX_DLC_VALUE_SHIFT    (0u)
    #define VehicleCAN_TX_DLC_UPPER_VALUE_SHIFT (19u)
    #define VehicleCAN_TX_DLC_UPPER_VALUE    \
            ((uint32) ((uint32) 0x00000001u << VehicleCAN_TX_DLC_UPPER_VALUE_SHIFT))
    #define VehicleCAN_TX_DLC_VALUE_MASK     ((uint8) ((uint8) 0x0Fu << VehicleCAN_TX_DLC_VALUE_SHIFT))
    #define VehicleCAN_TX_DLC_MAX_VALUE      (8u)
    /* Bit 20 within TX_CMD[i] */
    #define VehicleCAN_TX_IDE_SHIFT          (20u)
    #define VehicleCAN_TX_IDE_MASK           ((uint32) ((uint32) 0x00000001u << VehicleCAN_TX_IDE_SHIFT))
    /* Bit 21 within TX_CMD[i] */
    #define VehicleCAN_TX_RTR_SHIFT          (21u)
    #define VehicleCAN_TX_RTR_MASK           ((uint32) ((uint32) 0x00000001u <<  VehicleCAN_TX_RTR_SHIFT))
    /* Bit 23 within TX_CMD[i] */
    #define VehicleCAN_TX_WPNH_SHIFT         (7u)
    #define VehicleCAN_TX_WPNH_MASK          ((uint8) ((uint8) 0x01u << VehicleCAN_TX_WPNH_SHIFT))

    #define VehicleCAN_TX_TRANSMIT_MESSAGE(i) \
            (VehicleCAN_TX[i].txcmd.byte[0u] |= VehicleCAN_TX_TRANSMIT_REQUEST)
    #define VehicleCAN_TX_ABORT_MESSAGE(i)   \
            (VehicleCAN_TX[i].txcmd.byte[0u] = (VehicleCAN_TX[i].txcmd.byte[0u] & \
            (uint8) (~VehicleCAN_TX_TRANSMIT_REQUEST)) | VehicleCAN_TX_ABORT_MASK)
    #define VehicleCAN_TX_INT_ENABLE(i)      \
            (VehicleCAN_TX[i].txcmd.byte[0u] |= (uint8) VehicleCAN_TX_INT_ENABLE_MASK)
    #define VehicleCAN_TX_INT_DISABLE(i)     \
            (VehicleCAN_TX[i].txcmd.byte[0u] &= (uint8) (~VehicleCAN_TX_INT_ENABLE_MASK))
    #define VehicleCAN_SET_TX_WNPL(i)        \
            (VehicleCAN_TX[i].txcmd.byte[0u] |= VehicleCAN_TX_WPNL_MASK)
    #define VehicleCAN_CLEAR_TX_WNPL(i)      \
            (VehicleCAN_TX[i].txcmd.byte[0u] &= (uint8) (~VehicleCAN_TX_WPNL_MASK))
    #define VehicleCAN_SET_TX_IDE(i)         (VehicleCAN_TX[i].txcmd.byte[2u] |= \
            (uint8) (VehicleCAN_TX_IDE_MASK >> VehicleCAN_TWO_BYTE_OFFSET))
    #define VehicleCAN_CLEAR_TX_IDE(i)       (VehicleCAN_TX[i].txcmd.byte[2u] &= \
            (uint8) (((uint32) (~VehicleCAN_TX_IDE_MASK)) >> VehicleCAN_TWO_BYTE_OFFSET))
    #define VehicleCAN_SET_TX_RTR(i)         (VehicleCAN_TX[i].txcmd.byte[2u] |= \
            (uint8) (VehicleCAN_TX_RTR_MASK >> VehicleCAN_TWO_BYTE_OFFSET))
    #define VehicleCAN_CLEAR_TX_RTR(i)       (VehicleCAN_TX[i].txcmd.byte[2u] &= \
            (uint8) (((uint32) (~VehicleCAN_TX_RTR_MASK)) >> VehicleCAN_TWO_BYTE_OFFSET))
    #define VehicleCAN_SET_TX_WNPH(i)        \
            (VehicleCAN_TX[i].txcmd.byte[2u] |= VehicleCAN_TX_WPNH_MASK)
    #define VehicleCAN_CLEAR_TX_WNPH(i)      \
            (VehicleCAN_TX[i].txcmd.byte[2u] &= (uint8) (~VehicleCAN_TX_WPNH_MASK))

    #define VehicleCAN_RX_DATA_BYTE(mailbox, i) (VehicleCAN_RX[mailbox].rxdata.byte[((i) > 3u) ? \
                                                      (7u - ((i) - 4u)) : (3u - (i))])
    #define VehicleCAN_TX_DATA_BYTE(mailbox, i) (VehicleCAN_TX[mailbox].txdata.byte[((i) > 3u) ? \
                                                      (7u - ((i) - 4u)) : (3u - (i))])
#else  /* CY_PSOC4 */
    /* Set/Clear bits macro for VehicleCAN_RX mailbox(i) */
    /* Bit 0 within RX_CMD[i] */
    #define VehicleCAN_RX_ACK_MSG_SHIFT       (0u)
    #define VehicleCAN_RX_ACK_MSG             ((uint32) ((uint32) 0x01u << VehicleCAN_RX_ACK_MSG_SHIFT))
    /* Bit 2 within RX_CMD[i] */
    #define VehicleCAN_RX_RTR_ABORT_SHIFT     (2u)
    #define VehicleCAN_RX_RTR_ABORT_MASK      ((uint32) ((uint32) 0x01u << VehicleCAN_RX_RTR_ABORT_SHIFT))
    /* Bit 3 within RX_CMD[i] */
    #define VehicleCAN_RX_BUF_ENABLE_SHIFT    (3u)
    #define VehicleCAN_RX_BUF_ENABLE_MASK     ((uint32) ((uint32) 0x01u << VehicleCAN_RX_BUF_ENABLE_SHIFT))
    /* Bit 4 within RX_CMD[i] */
    #define VehicleCAN_RX_RTRREPLY_SHIFT      (4u)
    #define VehicleCAN_RX_RTRREPLY_MASK       ((uint32) ((uint32) 0x01u << VehicleCAN_RX_RTRREPLY_SHIFT))
    /* Bit 5 within RX_CMD[i] */
    #define VehicleCAN_RX_INT_ENABLE_SHIFT    (5u)
    #define VehicleCAN_RX_INT_ENABLE_MASK     ((uint32) ((uint32) 0x01u << VehicleCAN_RX_INT_ENABLE_SHIFT))
    /* Bit 6 within RX_CMD[i] */
    #define VehicleCAN_RX_LINKING_SHIFT       (6u)
    #define VehicleCAN_RX_LINKING_MASK        ((uint32) ((uint32) 0x01u << VehicleCAN_RX_LINKING_SHIFT))
    /* Bit 7 within RX_CMD[i] */
    #define VehicleCAN_RX_WPNL_SHIFT          (7u)
    #define VehicleCAN_RX_WPNL_MASK           ((uint32) ((uint32) 0x01u << VehicleCAN_RX_WPNL_SHIFT))
    /* Bits 19-16 within RX_CMD[i] */
    #define VehicleCAN_RX_DLC_VALUE_SHIFT     (16u)
    #define VehicleCAN_RX_DLC_VALUE_MASK      ((uint32) ((uint32) 0x0Fu << VehicleCAN_RX_DLC_VALUE_SHIFT))
    /* Bit 20 within RX_CMD[i] */
    #define VehicleCAN_RX_IDE_SHIFT           (20u)
    #define VehicleCAN_RX_IDE_MASK            ((uint32) ((uint32) 0x01u << VehicleCAN_RX_IDE_SHIFT))
    /* Bit 23 within RX_CMD[i] */
    #define VehicleCAN_RX_WPNH_SHIFT          (23u)
    #define VehicleCAN_RX_WPNH_MASK           ((uint32) ((uint32) 0x01u << VehicleCAN_RX_WPNH_SHIFT))

    #define VehicleCAN_RX_ACK_MESSAGE(i)       (VehicleCAN_RX_CMD_REG(i) |= VehicleCAN_RX_ACK_MSG)
    #define VehicleCAN_RX_RTR_ABORT_MESSAGE(i) (VehicleCAN_RX_CMD_REG(i) |= \
                                                     VehicleCAN_RX_RTR_ABORT_MASK)
    #define VehicleCAN_RX_BUF_ENABLE(i)      (VehicleCAN_RX_CMD_REG(i) |= \
                                                   VehicleCAN_RX_BUF_ENABLE_MASK)
    #define VehicleCAN_RX_BUF_DISABLE(i)     (VehicleCAN_RX_CMD_REG(i) &= \
                                                   (uint32) (~VehicleCAN_RX_BUF_ENABLE_MASK))
    #define VehicleCAN_SET_RX_RTRREPLY(i)    (VehicleCAN_RX_CMD_REG(i) |= \
                                                   VehicleCAN_RX_RTRREPLY_MASK)
    #define VehicleCAN_CLEAR_RX_RTRREPLY(i)  (VehicleCAN_RX_CMD_REG(i) &= \
                                                   (uint32) (~VehicleCAN_RX_RTRREPLY_MASK))
    #define VehicleCAN_RX_INT_ENABLE(i)      (VehicleCAN_RX_CMD_REG(i) |= \
                                                   VehicleCAN_RX_INT_ENABLE_MASK)
    #define VehicleCAN_RX_INT_DISABLE(i)     (VehicleCAN_RX_CMD_REG(i) &= \
                                                   (uint32) (~VehicleCAN_RX_INT_ENABLE_MASK))
    #define VehicleCAN_SET_RX_LINKING(i)     (VehicleCAN_RX_CMD_REG(i) |= VehicleCAN_RX_LINKING_MASK)
    #define VehicleCAN_CLEAR_RX_LINKING(i)   (VehicleCAN_RX_CMD_REG(i) &= \
                                                   (uint32) (~VehicleCAN_RX_LINKING_MASK))
    #define VehicleCAN_SET_RX_WNPL(i)        (VehicleCAN_RX_CMD_REG(i) |= VehicleCAN_RX_WPNL_MASK)
    #define VehicleCAN_CLEAR_RX_WNPL(i)      (VehicleCAN_RX_CMD_REG(i) &= \
                                                   (uint32) (~VehicleCAN_RX_WPNL_MASK))
    #define VehicleCAN_SET_RX_WNPH(i)        (VehicleCAN_RX_CMD_REG(i) |= VehicleCAN_RX_WPNH_MASK)
    #define VehicleCAN_CLEAR_RX_WNPH(i)      (VehicleCAN_RX_CMD_REG(i) &= \
                                                   (uint32) (~VehicleCAN_RX_WPNH_MASK))
    #define VehicleCAN_GET_DLC(i)            ((uint32) ((VehicleCAN_RX_CMD_REG(i) & \
            VehicleCAN_RX_DLC_VALUE_MASK) >> VehicleCAN_RX_DLC_VALUE_SHIFT))
    #define VehicleCAN_GET_RX_IDE(i)         ((uint32) ((VehicleCAN_RX_CMD_REG(i) & \
            VehicleCAN_RX_IDE_MASK) >> VehicleCAN_RX_IDE_SHIFT))
    #define VehicleCAN_GET_RX_ID(i)          ((VehicleCAN_GET_RX_IDE(i) == 0u) ? \
            (VehicleCAN_RX_ID_REG(i) >> VehicleCAN_SET_TX_ID_STANDARD_MSG_SHIFT) : \
            (VehicleCAN_RX_ID_REG(i) >> VehicleCAN_SET_TX_ID_EXTENDED_MSG_SHIFT))

    /* Set/Clear bits macro for VehicleCAN_TX mailbox(i) */
    /* Bit 0 within TX_CMD[i] */
    #define VehicleCAN_TX_TRANSMIT_REQUEST_SHIFT (0u)
    #define VehicleCAN_TX_TRANSMIT_REQUEST   \
            ((uint32) ((uint32) 0x01u << VehicleCAN_TX_TRANSMIT_REQUEST_SHIFT))
    /* Bit 1 within TX_CMD[i] */
    #define VehicleCAN_TX_ABORT_SHIFT        (1u)
    #define VehicleCAN_TX_ABORT_MASK         ((uint32) ((uint32) 0x01u << VehicleCAN_TX_ABORT_SHIFT))
    /* Bit 2 within TX_CMD[i] */
    #define VehicleCAN_TRANSMIT_INT_ENABLE   (0x01u)
    #define VehicleCAN_TRANSMIT_INT_DISABLE  (0x00u)
    #define VehicleCAN_TX_INT_ENABLE_SHIFT   (2u)
    #define VehicleCAN_TX_INT_ENABLE_MASK    \
            ((uint32) ((uint32) 0x00000001u << VehicleCAN_TX_INT_ENABLE_SHIFT))
    /* Bit 3 within TX_CMD[i] */
    #define VehicleCAN_TX_WPNL_SHIFT         (3u)
    #define VehicleCAN_TX_WPNL_MASK          ((uint32) ((uint32) 0x01u << VehicleCAN_TX_WPNL_SHIFT))
    /* Bits 19-16 within TX_CMD[i] */
    #define VehicleCAN_TX_DLC_VALUE_SHIFT    (0u)
    #define VehicleCAN_TX_DLC_UPPER_VALUE_SHIFT (19u)
    #define VehicleCAN_TX_DLC_UPPER_VALUE    \
            ((uint32) ((uint32) 0x00000001u << VehicleCAN_TX_DLC_UPPER_VALUE_SHIFT))
    #define VehicleCAN_TX_DLC_VALUE_MASK     ((uint32) ((uint32) 0x0Fu << VehicleCAN_TX_DLC_VALUE_SHIFT))
    #define VehicleCAN_TX_DLC_MAX_VALUE      (8u)
    /* Bit 20 within TX_CMD[i] */
    #define VehicleCAN_TX_IDE_SHIFT          (20u)
    #define VehicleCAN_TX_IDE_MASK           ((uint32) ((uint32) 0x00000001u << VehicleCAN_TX_IDE_SHIFT))
    /* Bit 21 within TX_CMD[i] */
    #define VehicleCAN_TX_RTR_SHIFT          (21u)
    #define VehicleCAN_TX_RTR_MASK           ((uint32) ((uint32) 0x00000001u <<  VehicleCAN_TX_RTR_SHIFT))
    /* Bit 23 within TX_CMD[i] */
    #define VehicleCAN_TX_WPNH_SHIFT         (23u)
    #define VehicleCAN_TX_WPNH_MASK          ((uint32) ((uint32) 0x01u << VehicleCAN_TX_WPNH_SHIFT))

    #define VehicleCAN_TX_TRANSMIT_MESSAGE(i) \
            (VehicleCAN_TX_CMD_REG(i) |= VehicleCAN_TX_TRANSMIT_REQUEST)
    #define VehicleCAN_TX_ABORT_MESSAGE(i) (VehicleCAN_TX_CMD_REG(i) = (VehicleCAN_TX_CMD_REG(i) & \
            (uint32) (~VehicleCAN_TX_TRANSMIT_REQUEST)) | VehicleCAN_TX_ABORT_MASK)
    #define VehicleCAN_TX_INT_ENABLE(i)    (VehicleCAN_TX_CMD_REG(i) |= VehicleCAN_TX_INT_ENABLE_MASK)
    #define VehicleCAN_TX_INT_DISABLE(i)   (VehicleCAN_TX_CMD_REG(i) &= \
                                                 (uint32) (~VehicleCAN_TX_INT_ENABLE_MASK))
    #define VehicleCAN_SET_TX_WNPL(i)     (VehicleCAN_TX_CMD_REG(i) |= VehicleCAN_TX_WPNL_MASK)
    #define VehicleCAN_CLEAR_TX_WNPL(i)   \
            (VehicleCAN_TX_CMD_REG(i) &= (uint32)(~VehicleCAN_TX_WPNL_MASK))
    #define VehicleCAN_SET_TX_IDE(i)      (VehicleCAN_TX_CMD_REG(i) |= VehicleCAN_TX_IDE_MASK)
    #define VehicleCAN_CLEAR_TX_IDE(i)    \
            (VehicleCAN_TX_CMD_REG(i) &= (uint32) (~VehicleCAN_TX_IDE_MASK))
    #define VehicleCAN_SET_TX_RTR(i)      (VehicleCAN_TX_CMD_REG(i) |= VehicleCAN_TX_RTR_MASK)
    #define VehicleCAN_CLEAR_TX_RTR(i)    \
            (VehicleCAN_TX_CMD_REG(i) &= (uint32) (~VehicleCAN_TX_RTR_MASK))
    #define VehicleCAN_SET_TX_WNPH(i)     (VehicleCAN_TX_CMD_REG(i) |= VehicleCAN_TX_WPNH_MASK)
    #define VehicleCAN_CLEAR_TX_WNPH(i)   \
            (VehicleCAN_TX_CMD_REG(i) &= (uint32)(~VehicleCAN_TX_WPNH_MASK))

    #define VehicleCAN_DATA_HIGH_ADDR     (4u)
    #define VehicleCAN_DATA_BYTE_MASK     ((uint32) 0xFFu)

    #define VehicleCAN_RX_DATA_BYTE(mailbox, i) (((i) > 3u) ? \
            (uint8) (VehicleCAN_RX_DATA_HI_REG(mailbox) >> ((7u - (i)) * VehicleCAN_ONE_BYTE_OFFSET)) : \
            (uint8) (VehicleCAN_RX_DATA_LO_REG(mailbox) >> ((3u - (i)) * VehicleCAN_ONE_BYTE_OFFSET)))

    #define VehicleCAN_TX_DATA_BYTE(mailbox, i, byte) (((i) > 3u) ? \
        (VehicleCAN_TX_DATA_HI_REG(mailbox) = (VehicleCAN_TX_DATA_HI_REG(mailbox) & \
        (uint32) (~((uint32) (VehicleCAN_DATA_BYTE_MASK << ((7u - (i)) * VehicleCAN_ONE_BYTE_OFFSET))))) | \
        (uint32) ((uint32) (byte) << ((7u - (i)) * VehicleCAN_ONE_BYTE_OFFSET))) : \
        (VehicleCAN_TX_DATA_LO_REG(mailbox) = (VehicleCAN_TX_DATA_LO_REG(mailbox) & \
        (uint32) (~((uint32) (VehicleCAN_DATA_BYTE_MASK << ((3u - (i)) * VehicleCAN_ONE_BYTE_OFFSET))))) | \
        (uint32) ((uint32) (byte) << ((3u - (i)) * VehicleCAN_ONE_BYTE_OFFSET))))
#endif /* CY_PSOC3 || CY_PSOC5 */

#if (CY_PSOC3 || CY_PSOC5)
    #define VehicleCAN_DATA_BYTE_1            (3u)
    #define VehicleCAN_DATA_BYTE_2            (2u)
    #define VehicleCAN_DATA_BYTE_3            (1u)
    #define VehicleCAN_DATA_BYTE_4            (0u)
    #define VehicleCAN_DATA_BYTE_5            (7u)
    #define VehicleCAN_DATA_BYTE_6            (6u)
    #define VehicleCAN_DATA_BYTE_7            (5u)
    #define VehicleCAN_DATA_BYTE_8            (4u)

    /* Macros for access to RX DATA for mailbox(i) */
    #define VehicleCAN_RX_DATA_BYTE1(i)       VehicleCAN_RX[i].rxdata.byte[VehicleCAN_DATA_BYTE_1]
    #define VehicleCAN_RX_DATA_BYTE2(i)       VehicleCAN_RX[i].rxdata.byte[VehicleCAN_DATA_BYTE_2]
    #define VehicleCAN_RX_DATA_BYTE3(i)       VehicleCAN_RX[i].rxdata.byte[VehicleCAN_DATA_BYTE_3]
    #define VehicleCAN_RX_DATA_BYTE4(i)       VehicleCAN_RX[i].rxdata.byte[VehicleCAN_DATA_BYTE_4]
    #define VehicleCAN_RX_DATA_BYTE5(i)       VehicleCAN_RX[i].rxdata.byte[VehicleCAN_DATA_BYTE_5]
    #define VehicleCAN_RX_DATA_BYTE6(i)       VehicleCAN_RX[i].rxdata.byte[VehicleCAN_DATA_BYTE_6]
    #define VehicleCAN_RX_DATA_BYTE7(i)       VehicleCAN_RX[i].rxdata.byte[VehicleCAN_DATA_BYTE_7]
    #define VehicleCAN_RX_DATA_BYTE8(i)       VehicleCAN_RX[i].rxdata.byte[VehicleCAN_DATA_BYTE_8]

    /* Macros for access to TX DATA for mailbox(i) */
    #define VehicleCAN_TX_DATA_BYTE1(i)       VehicleCAN_TX[i].txdata.byte[VehicleCAN_DATA_BYTE_1]
    #define VehicleCAN_TX_DATA_BYTE2(i)       VehicleCAN_TX[i].txdata.byte[VehicleCAN_DATA_BYTE_2]
    #define VehicleCAN_TX_DATA_BYTE3(i)       VehicleCAN_TX[i].txdata.byte[VehicleCAN_DATA_BYTE_3]
    #define VehicleCAN_TX_DATA_BYTE4(i)       VehicleCAN_TX[i].txdata.byte[VehicleCAN_DATA_BYTE_4]
    #define VehicleCAN_TX_DATA_BYTE5(i)       VehicleCAN_TX[i].txdata.byte[VehicleCAN_DATA_BYTE_5]
    #define VehicleCAN_TX_DATA_BYTE6(i)       VehicleCAN_TX[i].txdata.byte[VehicleCAN_DATA_BYTE_6]
    #define VehicleCAN_TX_DATA_BYTE7(i)       VehicleCAN_TX[i].txdata.byte[VehicleCAN_DATA_BYTE_7]
    #define VehicleCAN_TX_DATA_BYTE8(i)       VehicleCAN_TX[i].txdata.byte[VehicleCAN_DATA_BYTE_8]
#else  /* CY_PSOC4 */
    /* Macros for access to RX DATA for mailbox(i) */
    #define VehicleCAN_RX_DATA_BYTE1(i)       \
            ((uint8) (VehicleCAN_RX_DATA_LO_REG(i) >> VehicleCAN_THREE_BYTE_OFFSET))
    #define VehicleCAN_RX_DATA_BYTE2(i)       \
            ((uint8) (VehicleCAN_RX_DATA_LO_REG(i) >> VehicleCAN_TWO_BYTE_OFFSET))
    #define VehicleCAN_RX_DATA_BYTE3(i)       \
            ((uint8) (VehicleCAN_RX_DATA_LO_REG(i) >> VehicleCAN_ONE_BYTE_OFFSET))
    #define VehicleCAN_RX_DATA_BYTE4(i)       ((uint8) VehicleCAN_RX_DATA_LO_REG(i))
    #define VehicleCAN_RX_DATA_BYTE5(i)       \
            ((uint8) (VehicleCAN_RX_DATA_HI_REG(i) >> VehicleCAN_THREE_BYTE_OFFSET))
    #define VehicleCAN_RX_DATA_BYTE6(i)       \
            ((uint8) (VehicleCAN_RX_DATA_HI_REG(i) >> VehicleCAN_TWO_BYTE_OFFSET))
    #define VehicleCAN_RX_DATA_BYTE7(i)       \
            ((uint8) (VehicleCAN_RX_DATA_HI_REG(i) >> VehicleCAN_ONE_BYTE_OFFSET))
    #define VehicleCAN_RX_DATA_BYTE8(i)       ((uint8) VehicleCAN_RX_DATA_HI_REG(i))

    /* Macros for access to TX DATA for mailbox(i) */
    #define VehicleCAN_TX_DATA_BYTE1(i, byte) \
            (VehicleCAN_TX_DATA_LO_REG(i) = (VehicleCAN_TX_DATA_LO_REG(i) & \
            (uint32) (~((uint32) (VehicleCAN_DATA_BYTE_MASK << VehicleCAN_THREE_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << VehicleCAN_THREE_BYTE_OFFSET))
    #define VehicleCAN_TX_DATA_BYTE2(i, byte) \
            (VehicleCAN_TX_DATA_LO_REG(i) = (VehicleCAN_TX_DATA_LO_REG(i) & \
            (uint32) (~((uint32) (VehicleCAN_DATA_BYTE_MASK << VehicleCAN_TWO_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << VehicleCAN_TWO_BYTE_OFFSET))
    #define VehicleCAN_TX_DATA_BYTE3(i, byte) \
            (VehicleCAN_TX_DATA_LO_REG(i) = (VehicleCAN_TX_DATA_LO_REG(i) & \
            (uint32) (~((uint32) (VehicleCAN_DATA_BYTE_MASK << VehicleCAN_ONE_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << VehicleCAN_ONE_BYTE_OFFSET))
    #define VehicleCAN_TX_DATA_BYTE4(i, byte) \
            (VehicleCAN_TX_DATA_LO_REG(i) = (VehicleCAN_TX_DATA_LO_REG(i) & \
            (uint32) (~VehicleCAN_DATA_BYTE_MASK)) | (uint32) (byte))
    #define VehicleCAN_TX_DATA_BYTE5(i, byte) \
            (VehicleCAN_TX_DATA_HI_REG(i) = (VehicleCAN_TX_DATA_HI_REG(i) & \
            (uint32) (~((uint32) (VehicleCAN_DATA_BYTE_MASK << VehicleCAN_THREE_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << VehicleCAN_THREE_BYTE_OFFSET))
    #define VehicleCAN_TX_DATA_BYTE6(i, byte) \
            (VehicleCAN_TX_DATA_HI_REG(i) = (VehicleCAN_TX_DATA_HI_REG(i) & \
            (uint32) (~((uint32) (VehicleCAN_DATA_BYTE_MASK << VehicleCAN_TWO_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << VehicleCAN_TWO_BYTE_OFFSET))
    #define VehicleCAN_TX_DATA_BYTE7(i, byte) \
            (VehicleCAN_TX_DATA_HI_REG(i) = (VehicleCAN_TX_DATA_HI_REG(i) & \
            (uint32) (~((uint32) (VehicleCAN_DATA_BYTE_MASK << VehicleCAN_ONE_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << VehicleCAN_ONE_BYTE_OFFSET))
    #define VehicleCAN_TX_DATA_BYTE8(i, byte) \
            (VehicleCAN_TX_DATA_HI_REG(i) = (VehicleCAN_TX_DATA_HI_REG(i) & \
            (uint32) (~VehicleCAN_DATA_BYTE_MASK)) | (uint32) (byte))
#endif /* CY_PSOC3 || CY_PSOC5 */

/* Macros for setting Tx Msg Identifier in VehicleCAN_TX_ID register */
#define VehicleCAN_SET_TX_ID_STANDARD_MSG_SHIFT  (21u)
#define VehicleCAN_SET_TX_ID_EXTENDED_MSG_SHIFT  (3u)
#define VehicleCAN_SET_TX_ID_STANDARD_MSG(i, id) (CY_SET_REG32(VehicleCAN_TX_ID_PTR(i), \
        (uint32) ((uint32) (id) << VehicleCAN_SET_TX_ID_STANDARD_MSG_SHIFT)))
#define VehicleCAN_SET_TX_ID_EXTENDED_MSG(i, id) (CY_SET_REG32(VehicleCAN_TX_ID_PTR(i), \
        (uint32) ((uint32) (id) << VehicleCAN_SET_TX_ID_EXTENDED_MSG_SHIFT)))

/* Mask for bits within VehicleCAN_CSR_CFG */
#define VehicleCAN_EDGE_MODE_SHIFT           (0u)
/* Bit 0 within CSR_CFG */
#define VehicleCAN_EDGE_MODE_MASK            ((uint8) ((uint8) 0x01u << VehicleCAN_EDGE_MODE_SHIFT))
#define VehicleCAN_SAMPLE_MODE_SHIFT         (1u)
/* Bit 1 within CSR_CFG */
#define VehicleCAN_SAMPLE_MODE_MASK          ((uint8) ((uint8) 0x01u << VehicleCAN_SAMPLE_MODE_SHIFT))
#define VehicleCAN_CFG_REG_SJW_SHIFT         (2u)
/* Bits 3-2 within CSR_CFG */
#define VehicleCAN_CFG_REG_SJW_MASK          ((uint8) ((uint8) 0x03u << VehicleCAN_CFG_REG_SJW_SHIFT))
#define VehicleCAN_CFG_REG_SJW_LOWER_LIMIT   (0x03u)  /* the lowest allowed value of cfg_sjw */
#define VehicleCAN_RESET_SHIFT               (4u)
/* Bit 4 within CSR_CFG    */
#define VehicleCAN_RESET_MASK                ((uint8) ((uint8) 0x01u << VehicleCAN_RESET_SHIFT))
#define VehicleCAN_CFG_REG_TSEG2_SHIFT       (5u)
/* Bits 7-5 within CSR_CFG */
#define VehicleCAN_CFG_REG_TSEG2_MASK        ((uint8) ((uint8) 0x07u << VehicleCAN_CFG_REG_TSEG2_SHIFT))
/* Highest allowed value of cfg_tseg2 */
#define VehicleCAN_CFG_REG_TSEG2_UPPER_LIMIT (0x07u)
/* Lowest allowed value of cfg_tseg2 */
#define VehicleCAN_CFG_REG_TSEG2_LOWER_LIMIT (0x02u)
/* Lowest allowed value of cfg_tseg2 if sample point is one point */
#define VehicleCAN_CFG_REG_TSEG2_EXCEPTION   (0x01u)
/* Bits 11-8 within CSR_CFG */
#define VehicleCAN_CFG_REG_TSEG1_SHIFT       (8u)
#define VehicleCAN_CFG_REG_TSEG1_MASK        (0x0Fu)
/* Highest allowed value of cfg_tseg1 */
#define VehicleCAN_CFG_REG_TSEG1_UPPER_LIMIT (0x0Fu)
/* Lowest allowed value of cfg_tseg1 */
#define VehicleCAN_CFG_REG_TSEG1_LOWER_LIMIT (0x02u)
#define VehicleCAN_ARBITER_SHIFT             (12u)

#if (CY_PSOC3 || CY_PSOC5)
    #define VehicleCAN_ARBITRATION_SHIFT     (4u)
    /* Bit 12 within CSR_CFG */
    #define VehicleCAN_ARBITRATION_MASK      ((uint8) ((uint8) 0x01u << VehicleCAN_ARBITRATION_SHIFT))
#else  /* CY_PSOC4 */
    #define VehicleCAN_ARBITRATION_SHIFT     (12u)
    /* Bit 12 within CSR_CFG */
    #define VehicleCAN_ARBITRATION_MASK      ((uint32) ((uint32) 0x01u << VehicleCAN_ARBITRATION_SHIFT))
    /* Bit 13 within CSR_CFG */
    #define VehicleCAN_ENDIANNESS_SHIFT      (13u)
    #define VehicleCAN_ENDIANNESS_MASK       ((uint32) ((uint32) 0x01u << VehicleCAN_ENDIANNESS_SHIFT))
    /* Bit 14 within CSR_CFG */
    #define VehicleCAN_ECR_MODE_SHIFT        (14u)
    #define VehicleCAN_ECR_MODE_MASK         ((uint32) ((uint32) 0x01u << VehicleCAN_ECR_MODE_SHIFT))
#endif /* (CY_PSOC3 || CY_PSOC5) */

/* Bits 23-16 within CSR_CFG */
#define VehicleCAN_BITRATE_SHIFT             (16u)
#define VehicleCAN_BITRATE_MASK              (0x7FFFu)
#define VehicleCAN_BITRATE_MASK_SHIFTED      \
        ((uint32) ((uint32) VehicleCAN_BITRATE_MASK << VehicleCAN_BITRATE_SHIFT))

/* Mask for bits within VehicleCAN_CSR_CMD */
#define VehicleCAN_MODE_SHIFT                (0u)
/* Bit 0 within CSR_CMD */
#define VehicleCAN_MODE_MASK                 ((uint8) ((uint8) 0x01u << VehicleCAN_MODE_SHIFT))
#define VehicleCAN_OPMODE_MASK_SHIFT         (1u)
/* Bit 1 within CSR_CMD */
#define VehicleCAN_OPMODE_MASK               ((uint8) ((uint8) 0x01u << VehicleCAN_OPMODE_MASK_SHIFT))

#if (CY_PSOC3 || CY_PSOC5)
    #define VehicleCAN_OPMODE_FIELD_MASK     ((uint8) ((uint8) 0x03u << VehicleCAN_MODE_SHIFT))
#else  /* CY_PSOC4 */
    #define VehicleCAN_OPMODE_FIELD_MASK     ((uint8) ((uint8) 0x07u << VehicleCAN_MODE_SHIFT))
#endif /* (CY_PSOC3 || CY_PSOC5) */

/* Mask for bits within VehicleCAN_CSR_CMD */
#define VehicleCAN_ERROR_STATE_SHIFT         (0u)
/* Bit 17-16 within ERR_SR */
#define VehicleCAN_ERROR_STATE_MASK          ((uint8) ((uint8) 0x03u << VehicleCAN_ERROR_STATE_SHIFT))

#if (CY_PSOC3 || CY_PSOC5)
    #define VehicleCAN_TX_ERROR_FLAG_SHIFT   (2u)
    /* Bit 18 within ERR_SR */
    #define VehicleCAN_TX_ERROR_FLAG_MASK    ((uint8) ((uint8) 0x01u << VehicleCAN_TX_ERROR_FLAG_SHIFT))
    #define VehicleCAN_RX_ERROR_FLAG_SHIFT   (3u)
    /* Bit 19 within ERR_SR */
    #define VehicleCAN_RX_ERROR_FLAG_MASK    ((uint8) ((uint8) 0x01u << VehicleCAN_RX_ERROR_FLAG_SHIFT))
#else  /* CY_PSOC4 */
    #define VehicleCAN_TX_ERROR_FLAG_SHIFT   (18u)
    /* Bit 18 within ERR_SR */
    #define VehicleCAN_TX_ERROR_FLAG_MASK    ((uint32) ((uint32) 0x01u << VehicleCAN_TX_ERROR_FLAG_SHIFT))
    #define VehicleCAN_RX_ERROR_FLAG_SHIFT   (19u)
    /* Bit 19 within ERR_SR */
    #define VehicleCAN_RX_ERROR_FLAG_MASK    ((uint32) ((uint32) 0x01u << VehicleCAN_RX_ERROR_FLAG_SHIFT))

    /* Mask and Macros for bits within VehicleCAN_ECR_REG */
    #define VehicleCAN_ECR_STATUS_ARM        (0x01u)
    /* Mask for clearing VehicleCANINT_STATUS */
    #define VehicleCAN_INT_STATUS_MASK       (0x00001FFCu)
#endif /* (CY_PSOC3 || CY_PSOC5) */

/* Mask and Macros for bits within VehicleCAN_INT_EN_REG */
#define VehicleCAN_GLOBAL_INT_SHIFT          (0u)
#define VehicleCAN_ARBITRATION_LOST_SHIFT    (2u)
#define VehicleCAN_OVERLOAD_ERROR_SHIFT      (3u)
#define VehicleCAN_BIT_ERROR_SHIFT           (4u)
#define VehicleCAN_STUFF_ERROR_SHIFT         (5u)
#define VehicleCAN_ACK_ERROR_SHIFT           (6u)
#define VehicleCAN_FORM_ERROR_SHIFT          (7u)

#if (CY_PSOC3 || CY_PSOC5)
    #define VehicleCAN_CRC_ERROR_SHIFT       (0u)
    #define VehicleCAN_BUS_OFF_SHIFT         (1u)
    #define VehicleCAN_RX_MSG_LOST_SHIFT     (2u)
    #define VehicleCAN_TX_MESSAGE_SHIFT      (3u)
    #define VehicleCAN_RX_MESSAGE_SHIFT      (4u)

    /* Bit 0 within INT_EN */
    #define VehicleCAN_GLOBAL_INT_MASK       ((uint8) ((uint8) 0x01u << VehicleCAN_GLOBAL_INT_SHIFT))
    /* Bit 2 within INT_EN and INT_SR */
    #define VehicleCAN_ARBITRATION_LOST_MASK ((uint8) ((uint8) 0x01u << VehicleCAN_ARBITRATION_LOST_SHIFT))
    /* Bit 3 within INT_EN and INT_SR */
    #define VehicleCAN_OVERLOAD_ERROR_MASK   ((uint8) ((uint8) 0x01u << VehicleCAN_OVERLOAD_ERROR_SHIFT))
    /* Bit 4 within INT_EN and INT_SR */
    #define VehicleCAN_BIT_ERROR_MASK        ((uint8) ((uint8) 0x01u << VehicleCAN_BIT_ERROR_SHIFT))
    /* Bit 5 within INT_EN and INT_SR */
    #define VehicleCAN_STUFF_ERROR_MASK      ((uint8) ((uint8) 0x01u << VehicleCAN_STUFF_ERROR_SHIFT))
    /* Bit 6 within INT_EN and INT_SR */
    #define VehicleCAN_ACK_ERROR_MASK        ((uint8) ((uint8) 0x01u << VehicleCAN_ACK_ERROR_SHIFT))
    /* Bit 7 within INT_EN and INT_SR */
    #define VehicleCAN_FORM_ERROR_MASK       ((uint8) ((uint8) 0x01u << VehicleCAN_FORM_ERROR_SHIFT))
    /* Bit 8 within INT_EN and INT_SR */
    #define VehicleCAN_CRC_ERROR_MASK        ((uint8) ((uint8) 0x01u << VehicleCAN_CRC_ERROR_SHIFT))
    /* Bit 9 within INT_EN and INT_SR */
    #define VehicleCAN_BUS_OFF_MASK          ((uint8) ((uint8) 0x01u << VehicleCAN_BUS_OFF_SHIFT))
    /* Bit 10 within INT_EN and INT_SR */
    #define VehicleCAN_RX_MSG_LOST_MASK      ((uint8) ((uint8) 0x01u << VehicleCAN_RX_MSG_LOST_SHIFT))
    /* Bit 11 within INT_EN and INT_SR */
    #define VehicleCAN_TX_MESSAGE_MASK       ((uint8) ((uint8) 0x01u << VehicleCAN_TX_MESSAGE_SHIFT))
    /* Bit 12 within INT_EN and INT_SR */
    #define VehicleCAN_RX_MESSAGE_MASK       ((uint8) ((uint8) 0x01u << VehicleCAN_RX_MESSAGE_SHIFT))

    #define VehicleCAN_ARBITRATION_LOST_INT_ENABLE   \
            (VehicleCAN_INT_EN_REG.byte[0u] |= VehicleCAN_ARBITRATION_LOST_MASK)
    #define VehicleCAN_ARBITRATION_LOST_INT_DISABLE  \
            (VehicleCAN_INT_EN_REG.byte[0u] &= (uint8) (~VehicleCAN_ARBITRATION_LOST_MASK))
    #define VehicleCAN_OVERLOAD_ERROR_INT_ENABLE     \
            (VehicleCAN_INT_EN_REG.byte[0u] |= VehicleCAN_OVERLOAD_ERROR_MASK)
    #define VehicleCAN_OVERLOAD_ERROR_INT_DISABLE    \
            (VehicleCAN_INT_EN_REG.byte[0u] &= (uint8) (~VehicleCAN_OVERLOAD_ERROR_MASK))
    #define VehicleCAN_BIT_ERROR_LOST_INT_ENABLE     \
            (VehicleCAN_INT_EN_REG.byte[0u] |= VehicleCAN_BIT_ERROR_MASK)
    #define VehicleCAN_BIT_ERROR_LOST_INT_DISABLE    \
            (VehicleCAN_INT_EN_REG.byte[0u] &= (uint8) (~VehicleCAN_BIT_ERROR_MASK))
    #define VehicleCAN_STUFF_ERROR_INT_ENABLE        \
            (VehicleCAN_INT_EN_REG.byte[0u] |= VehicleCAN_STUFF_ERROR_MASK)
    #define VehicleCAN_STUFF_ERROR_INT_DISABLE       \
            (VehicleCAN_INT_EN_REG.byte[0u] &= (uint8) (~VehicleCAN_STUFF_ERROR_MASK))
    #define VehicleCAN_ACK_ERROR_INT_ENABLE          \
            (VehicleCAN_INT_EN_REG.byte[0u] |= VehicleCAN_ACK_ERROR_MASK)
    #define VehicleCAN_ACK_ERROR_INT_DISABLE         \
            (VehicleCAN_INT_EN_REG.byte[0u] &= (uint8) (~VehicleCAN_ACK_ERROR_MASK))
    #define VehicleCAN_FORM_ERROR_INT_ENABLE         \
            (VehicleCAN_INT_EN_REG.byte[0u] |= VehicleCAN_FORM_ERROR_MASK)
    #define VehicleCAN_FORM_ERROR_INT_DISABLE        \
            (VehicleCAN_INT_EN_REG.byte[0u] &= (uint8) (~VehicleCAN_FORM_ERROR_MASK))
    #define VehicleCAN_CRC_ERROR_INT_ENABLE          \
            (VehicleCAN_INT_EN_REG.byte[1u] |= VehicleCAN_CRC_ERROR_MASK)
    #define VehicleCAN_CRC_ERROR_INT_DISABLE         \
            (VehicleCAN_INT_EN_REG.byte[1u] &= (uint8) (~VehicleCAN_CRC_ERROR_MASK))
    #define VehicleCAN_BUS_OFF_INT_ENABLE            \
            (VehicleCAN_INT_EN_REG.byte[1u] |= VehicleCAN_BUS_OFF_MASK)
    #define VehicleCAN_BUS_OFF_INT_DISABLE           \
            (VehicleCAN_INT_EN_REG.byte[1u] &= (uint8) (~VehicleCAN_BUS_OFF_MASK))
    #define VehicleCAN_RX_MSG_LOST_INT_ENABLE        \
            (VehicleCAN_INT_EN_REG.byte[1u] |= VehicleCAN_RX_MSG_LOST_MASK)
    #define VehicleCAN_RX_MSG_LOST_INT_DISABLE       \
            (VehicleCAN_INT_EN_REG.byte[1u] &= (uint8) (~VehicleCAN_RX_MSG_LOST_MASK))
    #define VehicleCAN_TX_MSG_INT_ENABLE             \
            (VehicleCAN_INT_EN_REG.byte[1u] |= VehicleCAN_TX_MESSAGE_MASK)
    #define VehicleCAN_TX_MSG_INT_DISABLE            \
            (VehicleCAN_INT_EN_REG.byte[1u] &= (uint8) (~VehicleCAN_TX_MESSAGE_MASK))
    #define VehicleCAN_RX_MSG_INT_ENABLE             \
            (VehicleCAN_INT_EN_REG.byte[1u] |= VehicleCAN_RX_MESSAGE_MASK)
    #define VehicleCAN_RX_MSG_INT_DISABLE            \
            (VehicleCAN_INT_EN_REG.byte[1u] &= (uint8) (~VehicleCAN_RX_MESSAGE_MASK))
#else  /* CY_PSOC4 */
    #define VehicleCAN_CRC_ERROR_SHIFT       (8u)
    #define VehicleCAN_BUS_OFF_SHIFT         (9u)
    #define VehicleCAN_RX_MSG_LOST_SHIFT     (10u)
    #define VehicleCAN_TX_MESSAGE_SHIFT      (11u)
    #define VehicleCAN_RX_MESSAGE_SHIFT      (12u)

    /* Mask and Macros for bits within VehicleCAN_INT_EN_REG */
    /* Bit 0 within INT_EN */
    #define VehicleCAN_GLOBAL_INT_MASK       ((uint32) ((uint32) 0x01u << VehicleCAN_GLOBAL_INT_SHIFT))
    /* Bit 2 within INT_EN and INT_SR */
    #define VehicleCAN_ARBITRATION_LOST_MASK ((uint32) ((uint32) 0x01u << VehicleCAN_ARBITRATION_LOST_SHIFT))
    /* Bit 3 within INT_EN and INT_SR */
    #define VehicleCAN_OVERLOAD_ERROR_MASK   ((uint32) ((uint32) 0x01u << VehicleCAN_OVERLOAD_ERROR_SHIFT))
    /* Bit 4 within INT_EN and INT_SR */
    #define VehicleCAN_BIT_ERROR_MASK        ((uint32) ((uint32) 0x01u << VehicleCAN_BIT_ERROR_SHIFT))
    /* Bit 5 within INT_EN and INT_SR */
    #define VehicleCAN_STUFF_ERROR_MASK      ((uint32) ((uint32) 0x01u << VehicleCAN_STUFF_ERROR_SHIFT))
    /* Bit 6 within INT_EN and INT_SR */
    #define VehicleCAN_ACK_ERROR_MASK        ((uint32) ((uint32) 0x01u << VehicleCAN_ACK_ERROR_SHIFT))
    /* Bit 7 within INT_EN and INT_SR */
    #define VehicleCAN_FORM_ERROR_MASK       ((uint32) ((uint32) 0x01u << VehicleCAN_FORM_ERROR_SHIFT))
    /* Bit 8 within INT_EN and INT_SR */
    #define VehicleCAN_CRC_ERROR_MASK        ((uint32) ((uint32) 0x01u << VehicleCAN_CRC_ERROR_SHIFT))
    /* Bit 9 within INT_EN and INT_SR */
    #define VehicleCAN_BUS_OFF_MASK          ((uint32) ((uint32) 0x01u << VehicleCAN_BUS_OFF_SHIFT))
    /* Bit 10 within INT_EN and INT_SR */
    #define VehicleCAN_RX_MSG_LOST_MASK      ((uint32) ((uint32) 0x01u << VehicleCAN_RX_MSG_LOST_SHIFT))
    /* Bit 11 within INT_EN and INT_SR */
    #define VehicleCAN_TX_MESSAGE_MASK       ((uint32) ((uint32) 0x01u << VehicleCAN_TX_MESSAGE_SHIFT))
    /* Bit 12 within INT_EN and INT_SR */
    #define VehicleCAN_RX_MESSAGE_MASK       ((uint32) ((uint32) 0x01u << VehicleCAN_RX_MESSAGE_SHIFT))

    #define VehicleCAN_ARBITRATION_LOST_INT_ENABLE   \
            (VehicleCAN_INT_EN_REG |= VehicleCAN_ARBITRATION_LOST_MASK)
    #define VehicleCAN_ARBITRATION_LOST_INT_DISABLE  \
            (VehicleCAN_INT_EN_REG &= (uint32) (~VehicleCAN_ARBITRATION_LOST_MASK))
    #define VehicleCAN_OVERLOAD_ERROR_INT_ENABLE     \
            (VehicleCAN_INT_EN_REG |= VehicleCAN_OVERLOAD_ERROR_MASK)
    #define VehicleCAN_OVERLOAD_ERROR_INT_DISABLE    \
            (VehicleCAN_INT_EN_REG &= (uint32) (~VehicleCAN_OVERLOAD_ERROR_MASK))
    #define VehicleCAN_BIT_ERROR_LOST_INT_ENABLE     \
            (VehicleCAN_INT_EN_REG |= VehicleCAN_BIT_ERROR_MASK)
    #define VehicleCAN_BIT_ERROR_LOST_INT_DISABLE    \
            (VehicleCAN_INT_EN_REG &= (uint32) (~VehicleCAN_BIT_ERROR_MASK))
    #define VehicleCAN_STUFF_ERROR_INT_ENABLE        \
            (VehicleCAN_INT_EN_REG |= VehicleCAN_STUFF_ERROR_MASK)
    #define VehicleCAN_STUFF_ERROR_INT_DISABLE       \
            (VehicleCAN_INT_EN_REG &= (uint32) (~VehicleCAN_STUFF_ERROR_MASK))
    #define VehicleCAN_ACK_ERROR_INT_ENABLE          \
            (VehicleCAN_INT_EN_REG |= VehicleCAN_ACK_ERROR_MASK)
    #define VehicleCAN_ACK_ERROR_INT_DISABLE         \
            (VehicleCAN_INT_EN_REG &= (uint32) (~VehicleCAN_ACK_ERROR_MASK))
    #define VehicleCAN_FORM_ERROR_INT_ENABLE         \
            (VehicleCAN_INT_EN_REG |= VehicleCAN_FORM_ERROR_MASK)
    #define VehicleCAN_FORM_ERROR_INT_DISABLE        \
            (VehicleCAN_INT_EN_REG &= (uint32) (~VehicleCAN_FORM_ERROR_MASK))
    #define VehicleCAN_CRC_ERROR_INT_ENABLE          \
            (VehicleCAN_INT_EN_REG |= VehicleCAN_CRC_ERROR_MASK)
    #define VehicleCAN_CRC_ERROR_INT_DISABLE         \
            (VehicleCAN_INT_EN_REG &= (uint32) (~VehicleCAN_CRC_ERROR_MASK))
    #define VehicleCAN_BUS_OFF_INT_ENABLE            \
            (VehicleCAN_INT_EN_REG |= VehicleCAN_BUS_OFF_MASK)
    #define VehicleCAN_BUS_OFF_INT_DISABLE           \
            (VehicleCAN_INT_EN_REG &= (uint32) (~VehicleCAN_BUS_OFF_MASK))
    #define VehicleCAN_RX_MSG_LOST_INT_ENABLE        \
            (VehicleCAN_INT_EN_REG |= VehicleCAN_RX_MSG_LOST_MASK)
    #define VehicleCAN_RX_MSG_LOST_INT_DISABLE       \
            (VehicleCAN_INT_EN_REG &= (uint32) (~VehicleCAN_RX_MSG_LOST_MASK))
    #define VehicleCAN_TX_MSG_INT_ENABLE             \
            (VehicleCAN_INT_EN_REG |= VehicleCAN_TX_MESSAGE_MASK)
    #define VehicleCAN_TX_MSG_INT_DISABLE            \
            (VehicleCAN_INT_EN_REG &= (uint32) (~VehicleCAN_TX_MESSAGE_MASK))
    #define VehicleCAN_RX_MSG_INT_ENABLE             \
            (VehicleCAN_INT_EN_REG |= VehicleCAN_RX_MESSAGE_MASK)
    #define VehicleCAN_RX_MSG_INT_DISABLE            \
            (VehicleCAN_INT_EN_REG &= (uint32) (~VehicleCAN_RX_MESSAGE_MASK))

    /* Bit 13 within INT_EN and INT_SR */
    #define VehicleCAN_RTR_MSG_SHIFT              (13u)
    #define VehicleCAN_RTR_MSG_MASK               ((uint32) ((uint32) 0x01u << VehicleCAN_RTR_MSG_SHIFT))
    #define VehicleCAN_RTR_MSG_INT_ENABLE         (VehicleCAN_INT_EN_REG |= VehicleCAN_RTR_MSG_MASK)
    #define VehicleCAN_RTR_MSG_INT_DISABLE        \
            (VehicleCAN_INT_EN_REG &= (uint32) (~VehicleCAN_RTR_MSG_MASK))
    /* Bit 14 within INT_EN and INT_SR */
    #define VehicleCAN_STUCK_AT_ZERO_SHIFT        (14u)
    #define VehicleCAN_STUCK_AT_ZERO_MASK         \
            ((uint32) ((uint32) 0x01u << VehicleCAN_STUCK_AT_ZERO_SHIFT))
    #define VehicleCAN_STUCK_AT_ZERO_INT_ENABLE   \
            (VehicleCAN_INT_EN_REG |= VehicleCAN_STUCK_AT_ZERO_MASK)
    #define VehicleCAN_STUCK_AT_ZERO_INT_DISABLE  \
            (VehicleCAN_INT_EN_REG &= (uint32) (~VehicleCAN_STUCK_AT_ZERO_MASK))
    /* Bit 15 within INT_EN and INT_SR */
    #define VehicleCAN_SST_FAILURE_SHIFT          (15u)
    #define VehicleCAN_SST_FAILURE_MASK           \
            ((uint32) ((uint32) 0x01u << VehicleCAN_SST_FAILURE_SHIFT))
    #define VehicleCAN_SST_FAILURE_INT_ENABLE     \
            (VehicleCAN_INT_EN_REG |= VehicleCAN_SST_FAILURE_MASK)
    #define VehicleCAN_SST_FAILURE_INT_DISABLE    \
            (VehicleCAN_INT_EN_REG &= (uint32) (~VehicleCAN_SST_FAILURE_MASK))
#endif /* CY_PSOC3 || CY_PSOC5 */

#define VehicleCAN_GLOBAL_INT_ENABLE_SHIFT        (0u)
#define VehicleCAN_ARBITRATION_LOST_ENABLE_SHIFT  (2u)
#define VehicleCAN_OVERLOAD_ERROR_ENABLE_SHIFT    (3u)
#define VehicleCAN_BIT_ERROR_ENABLE_SHIFT         (4u)
#define VehicleCAN_STUFF_ERROR_ENABLE_SHIFT       (5u)
#define VehicleCAN_ACK_ERROR_ENABLE_SHIFT         (6u)
#define VehicleCAN_FORM_ERROR_ENABLE_SHIFT        (7u)
#define VehicleCAN_CRC_ERROR_ENABLE_SHIFT         (8u)
#define VehicleCAN_BUS_OFF_ENABLE_SHIFT           (9u)
#define VehicleCAN_RX_MSG_LOST_ENABLE_SHIFT       (10u)
#define VehicleCAN_TX_MESSAGE_ENABLE_SHIFT        (11u)
#define VehicleCAN_RX_MESSAGE_ENABLE_SHIFT        (12u)

#define VehicleCAN_GLOBAL_INT_ENABLE    ((uint16) ((uint16) 0x01u << VehicleCAN_GLOBAL_INT_ENABLE_SHIFT))
#define VehicleCAN_ARBITRATION_LOST_ENABLE \
        ((uint16) ((uint16) 0x01u << VehicleCAN_ARBITRATION_LOST_ENABLE_SHIFT))
#define VehicleCAN_OVERLOAD_ERROR_ENABLE   \
        ((uint16) ((uint16) 0x01u << VehicleCAN_OVERLOAD_ERROR_ENABLE_SHIFT))
#define VehicleCAN_BIT_ERROR_ENABLE     ((uint16) ((uint16) 0x01u << VehicleCAN_BIT_ERROR_ENABLE_SHIFT))
#define VehicleCAN_STUFF_ERROR_ENABLE   ((uint16) ((uint16) 0x01u << VehicleCAN_STUFF_ERROR_ENABLE_SHIFT))
#define VehicleCAN_ACK_ERROR_ENABLE     ((uint16) ((uint16) 0x01u << VehicleCAN_ACK_ERROR_ENABLE_SHIFT))
#define VehicleCAN_FORM_ERROR_ENABLE    ((uint16) ((uint16) 0x01u << VehicleCAN_FORM_ERROR_ENABLE_SHIFT))
#define VehicleCAN_CRC_ERROR_ENABLE     ((uint16) ((uint16) 0x01u << VehicleCAN_CRC_ERROR_ENABLE_SHIFT))
#define VehicleCAN_BUS_OFF_ENABLE       ((uint16) ((uint16) 0x01u << VehicleCAN_BUS_OFF_ENABLE_SHIFT))
#define VehicleCAN_RX_MSG_LOST_ENABLE   ((uint16) ((uint16) 0x01u << VehicleCAN_RX_MSG_LOST_ENABLE_SHIFT))
#define VehicleCAN_TX_MESSAGE_ENABLE    ((uint16) ((uint16) 0x01u << VehicleCAN_TX_MESSAGE_ENABLE_SHIFT))
#define VehicleCAN_RX_MESSAGE_ENABLE    ((uint16) ((uint16) 0x01u << VehicleCAN_RX_MESSAGE_ENABLE_SHIFT))

#if (!(CY_PSOC3 || CY_PSOC5))
    #define VehicleCAN_RTR_MESSAGE_ENABLE_SHIFT   (13u)
    #define VehicleCAN_STUCK_AT_ZERO_ENABLE_SHIFT (14u)
    #define VehicleCAN_SST_FAILURE_ENABLE_SHIFT   (15u)

    #define VehicleCAN_RTR_MESSAGE_ENABLE   \
            ((uint16) ((uint16) 0x01u << VehicleCAN_RTR_MESSAGE_ENABLE_SHIFT))
    #define VehicleCAN_STUCK_AT_ZERO_ENABLE \
            ((uint16) ((uint16) 0x01u << VehicleCAN_STUCK_AT_ZERO_ENABLE_SHIFT))
    #define VehicleCAN_SST_FAILURE_ENABLE   \
            ((uint16) ((uint16) 0x01u << VehicleCAN_SST_FAILURE_ENABLE_SHIFT))
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

#define VehicleCAN_REG_ADDR_MASK        ((uint32) 0x0000FFFFu)


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

#define VehicleCAN_TREE_BYTE_OFFSET     (VehicleCAN_THREE_BYTE_OFFSET)

/* VehicleCAN_SetRestartType() parameters */
#define VehicleCAN_RESTART_BY_HAND      (VehicleCAN_MANUAL_RESTART)

/* VehicleCAN_SetOpMode() parameters */
#define VehicleCAN_LISTEN_ONLY          (VehicleCAN_LISTEN_ONLY_MODE)
#define VehicleCAN_ACTIVE_MODE          (VehicleCAN_INITIAL_MODE)

#ifdef VehicleCAN_ISR_CALLBACK
    #define VehicleCAN_ISR_INTERRUPT_CALLBACK
    #define VehicleCAN_ISR_InterruptCallback  VehicleCAN_Isr_Callback
#endif

#endif /* CY_CAN_VehicleCAN_H */


/* [] END OF FILE */
