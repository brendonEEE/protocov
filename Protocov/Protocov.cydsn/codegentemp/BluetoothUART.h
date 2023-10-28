/*******************************************************************************
* File Name: BluetoothUART.h
* Version 2.50
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_BluetoothUART_H)
#define CY_UART_BluetoothUART_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
* Conditional Compilation Parameters
***************************************/

#define BluetoothUART_RX_ENABLED                     (1u)
#define BluetoothUART_TX_ENABLED                     (1u)
#define BluetoothUART_HD_ENABLED                     (0u)
#define BluetoothUART_RX_INTERRUPT_ENABLED           (0u)
#define BluetoothUART_TX_INTERRUPT_ENABLED           (0u)
#define BluetoothUART_INTERNAL_CLOCK_USED            (1u)
#define BluetoothUART_RXHW_ADDRESS_ENABLED           (0u)
#define BluetoothUART_OVER_SAMPLE_COUNT              (16u)
#define BluetoothUART_PARITY_TYPE                    (0u)
#define BluetoothUART_PARITY_TYPE_SW                 (0u)
#define BluetoothUART_BREAK_DETECT                   (0u)
#define BluetoothUART_BREAK_BITS_TX                  (11u)
#define BluetoothUART_BREAK_BITS_RX                  (11u)
#define BluetoothUART_TXCLKGEN_DP                    (1u)
#define BluetoothUART_USE23POLLING                   (1u)
#define BluetoothUART_FLOW_CONTROL                   (0u)
#define BluetoothUART_CLK_FREQ                       (0u)
#define BluetoothUART_TX_BUFFER_SIZE                 (4u)
#define BluetoothUART_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(BluetoothUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define BluetoothUART_CONTROL_REG_REMOVED            (0u)
#else
    #define BluetoothUART_CONTROL_REG_REMOVED            (1u)
#endif /* End BluetoothUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct BluetoothUART_backupStruct_
{
    uint8 enableState;

    #if(BluetoothUART_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End BluetoothUART_CONTROL_REG_REMOVED */

} BluetoothUART_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void BluetoothUART_Start(void) ;
void BluetoothUART_Stop(void) ;
uint8 BluetoothUART_ReadControlRegister(void) ;
void BluetoothUART_WriteControlRegister(uint8 control) ;

void BluetoothUART_Init(void) ;
void BluetoothUART_Enable(void) ;
void BluetoothUART_SaveConfig(void) ;
void BluetoothUART_RestoreConfig(void) ;
void BluetoothUART_Sleep(void) ;
void BluetoothUART_Wakeup(void) ;

/* Only if RX is enabled */
#if( (BluetoothUART_RX_ENABLED) || (BluetoothUART_HD_ENABLED) )

    #if (BluetoothUART_RX_INTERRUPT_ENABLED)
        #define BluetoothUART_EnableRxInt()  CyIntEnable (BluetoothUART_RX_VECT_NUM)
        #define BluetoothUART_DisableRxInt() CyIntDisable(BluetoothUART_RX_VECT_NUM)
        CY_ISR_PROTO(BluetoothUART_RXISR);
    #endif /* BluetoothUART_RX_INTERRUPT_ENABLED */

    void BluetoothUART_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void BluetoothUART_SetRxAddress1(uint8 address) ;
    void BluetoothUART_SetRxAddress2(uint8 address) ;

    void  BluetoothUART_SetRxInterruptMode(uint8 intSrc) ;
    uint8 BluetoothUART_ReadRxData(void) ;
    uint8 BluetoothUART_ReadRxStatus(void) ;
    uint8 BluetoothUART_GetChar(void) ;
    uint16 BluetoothUART_GetByte(void) ;
    uint8 BluetoothUART_GetRxBufferSize(void)
                                                            ;
    void BluetoothUART_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define BluetoothUART_GetRxInterruptSource   BluetoothUART_ReadRxStatus

#endif /* End (BluetoothUART_RX_ENABLED) || (BluetoothUART_HD_ENABLED) */

/* Only if TX is enabled */
#if(BluetoothUART_TX_ENABLED || BluetoothUART_HD_ENABLED)

    #if(BluetoothUART_TX_INTERRUPT_ENABLED)
        #define BluetoothUART_EnableTxInt()  CyIntEnable (BluetoothUART_TX_VECT_NUM)
        #define BluetoothUART_DisableTxInt() CyIntDisable(BluetoothUART_TX_VECT_NUM)
        #define BluetoothUART_SetPendingTxInt() CyIntSetPending(BluetoothUART_TX_VECT_NUM)
        #define BluetoothUART_ClearPendingTxInt() CyIntClearPending(BluetoothUART_TX_VECT_NUM)
        CY_ISR_PROTO(BluetoothUART_TXISR);
    #endif /* BluetoothUART_TX_INTERRUPT_ENABLED */

    void BluetoothUART_SetTxInterruptMode(uint8 intSrc) ;
    void BluetoothUART_WriteTxData(uint8 txDataByte) ;
    uint8 BluetoothUART_ReadTxStatus(void) ;
    void BluetoothUART_PutChar(uint8 txDataByte) ;
    void BluetoothUART_PutString(const char8 string[]) ;
    void BluetoothUART_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void BluetoothUART_PutCRLF(uint8 txDataByte) ;
    void BluetoothUART_ClearTxBuffer(void) ;
    void BluetoothUART_SetTxAddressMode(uint8 addressMode) ;
    void BluetoothUART_SendBreak(uint8 retMode) ;
    uint8 BluetoothUART_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define BluetoothUART_PutStringConst         BluetoothUART_PutString
    #define BluetoothUART_PutArrayConst          BluetoothUART_PutArray
    #define BluetoothUART_GetTxInterruptSource   BluetoothUART_ReadTxStatus

#endif /* End BluetoothUART_TX_ENABLED || BluetoothUART_HD_ENABLED */

#if(BluetoothUART_HD_ENABLED)
    void BluetoothUART_LoadRxConfig(void) ;
    void BluetoothUART_LoadTxConfig(void) ;
#endif /* End BluetoothUART_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_BluetoothUART) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    BluetoothUART_CyBtldrCommStart(void) CYSMALL ;
    void    BluetoothUART_CyBtldrCommStop(void) CYSMALL ;
    void    BluetoothUART_CyBtldrCommReset(void) CYSMALL ;
    cystatus BluetoothUART_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus BluetoothUART_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_BluetoothUART)
        #define CyBtldrCommStart    BluetoothUART_CyBtldrCommStart
        #define CyBtldrCommStop     BluetoothUART_CyBtldrCommStop
        #define CyBtldrCommReset    BluetoothUART_CyBtldrCommReset
        #define CyBtldrCommWrite    BluetoothUART_CyBtldrCommWrite
        #define CyBtldrCommRead     BluetoothUART_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_BluetoothUART) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define BluetoothUART_BYTE2BYTE_TIME_OUT (25u)
    #define BluetoothUART_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define BluetoothUART_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define BluetoothUART_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define BluetoothUART_SET_SPACE      (0x00u)
#define BluetoothUART_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (BluetoothUART_TX_ENABLED) || (BluetoothUART_HD_ENABLED) )
    #if(BluetoothUART_TX_INTERRUPT_ENABLED)
        #define BluetoothUART_TX_VECT_NUM            (uint8)BluetoothUART_TXInternalInterrupt__INTC_NUMBER
        #define BluetoothUART_TX_PRIOR_NUM           (uint8)BluetoothUART_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* BluetoothUART_TX_INTERRUPT_ENABLED */

    #define BluetoothUART_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define BluetoothUART_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define BluetoothUART_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(BluetoothUART_TX_ENABLED)
        #define BluetoothUART_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (BluetoothUART_HD_ENABLED) */
        #define BluetoothUART_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (BluetoothUART_TX_ENABLED) */

    #define BluetoothUART_TX_STS_COMPLETE            (uint8)(0x01u << BluetoothUART_TX_STS_COMPLETE_SHIFT)
    #define BluetoothUART_TX_STS_FIFO_EMPTY          (uint8)(0x01u << BluetoothUART_TX_STS_FIFO_EMPTY_SHIFT)
    #define BluetoothUART_TX_STS_FIFO_FULL           (uint8)(0x01u << BluetoothUART_TX_STS_FIFO_FULL_SHIFT)
    #define BluetoothUART_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << BluetoothUART_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (BluetoothUART_TX_ENABLED) || (BluetoothUART_HD_ENABLED)*/

#if( (BluetoothUART_RX_ENABLED) || (BluetoothUART_HD_ENABLED) )
    #if(BluetoothUART_RX_INTERRUPT_ENABLED)
        #define BluetoothUART_RX_VECT_NUM            (uint8)BluetoothUART_RXInternalInterrupt__INTC_NUMBER
        #define BluetoothUART_RX_PRIOR_NUM           (uint8)BluetoothUART_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* BluetoothUART_RX_INTERRUPT_ENABLED */
    #define BluetoothUART_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define BluetoothUART_RX_STS_BREAK_SHIFT             (0x01u)
    #define BluetoothUART_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define BluetoothUART_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define BluetoothUART_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define BluetoothUART_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define BluetoothUART_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define BluetoothUART_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define BluetoothUART_RX_STS_MRKSPC           (uint8)(0x01u << BluetoothUART_RX_STS_MRKSPC_SHIFT)
    #define BluetoothUART_RX_STS_BREAK            (uint8)(0x01u << BluetoothUART_RX_STS_BREAK_SHIFT)
    #define BluetoothUART_RX_STS_PAR_ERROR        (uint8)(0x01u << BluetoothUART_RX_STS_PAR_ERROR_SHIFT)
    #define BluetoothUART_RX_STS_STOP_ERROR       (uint8)(0x01u << BluetoothUART_RX_STS_STOP_ERROR_SHIFT)
    #define BluetoothUART_RX_STS_OVERRUN          (uint8)(0x01u << BluetoothUART_RX_STS_OVERRUN_SHIFT)
    #define BluetoothUART_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << BluetoothUART_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define BluetoothUART_RX_STS_ADDR_MATCH       (uint8)(0x01u << BluetoothUART_RX_STS_ADDR_MATCH_SHIFT)
    #define BluetoothUART_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << BluetoothUART_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define BluetoothUART_RX_HW_MASK                     (0x7Fu)
#endif /* End (BluetoothUART_RX_ENABLED) || (BluetoothUART_HD_ENABLED) */

/* Control Register definitions */
#define BluetoothUART_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define BluetoothUART_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define BluetoothUART_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define BluetoothUART_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define BluetoothUART_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define BluetoothUART_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define BluetoothUART_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define BluetoothUART_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define BluetoothUART_CTRL_HD_SEND               (uint8)(0x01u << BluetoothUART_CTRL_HD_SEND_SHIFT)
#define BluetoothUART_CTRL_HD_SEND_BREAK         (uint8)(0x01u << BluetoothUART_CTRL_HD_SEND_BREAK_SHIFT)
#define BluetoothUART_CTRL_MARK                  (uint8)(0x01u << BluetoothUART_CTRL_MARK_SHIFT)
#define BluetoothUART_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << BluetoothUART_CTRL_PARITY_TYPE0_SHIFT)
#define BluetoothUART_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << BluetoothUART_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define BluetoothUART_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define BluetoothUART_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define BluetoothUART_SEND_BREAK                         (0x00u)
#define BluetoothUART_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define BluetoothUART_REINIT                             (0x02u)
#define BluetoothUART_SEND_WAIT_REINIT                   (0x03u)

#define BluetoothUART_OVER_SAMPLE_8                      (8u)
#define BluetoothUART_OVER_SAMPLE_16                     (16u)

#define BluetoothUART_BIT_CENTER                         (BluetoothUART_OVER_SAMPLE_COUNT - 2u)

#define BluetoothUART_FIFO_LENGTH                        (4u)
#define BluetoothUART_NUMBER_OF_START_BIT                (1u)
#define BluetoothUART_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define BluetoothUART_TXBITCTR_BREAKBITS8X   ((BluetoothUART_BREAK_BITS_TX * BluetoothUART_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define BluetoothUART_TXBITCTR_BREAKBITS ((BluetoothUART_BREAK_BITS_TX * BluetoothUART_OVER_SAMPLE_COUNT) - 1u)

#define BluetoothUART_HALF_BIT_COUNT   \
                            (((BluetoothUART_OVER_SAMPLE_COUNT / 2u) + (BluetoothUART_USE23POLLING * 1u)) - 2u)
#if (BluetoothUART_OVER_SAMPLE_COUNT == BluetoothUART_OVER_SAMPLE_8)
    #define BluetoothUART_HD_TXBITCTR_INIT   (((BluetoothUART_BREAK_BITS_TX + \
                            BluetoothUART_NUMBER_OF_START_BIT) * BluetoothUART_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define BluetoothUART_RXBITCTR_INIT  ((((BluetoothUART_BREAK_BITS_RX + BluetoothUART_NUMBER_OF_START_BIT) \
                            * BluetoothUART_OVER_SAMPLE_COUNT) + BluetoothUART_HALF_BIT_COUNT) - 1u)

#else /* BluetoothUART_OVER_SAMPLE_COUNT == BluetoothUART_OVER_SAMPLE_16 */
    #define BluetoothUART_HD_TXBITCTR_INIT   ((8u * BluetoothUART_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define BluetoothUART_RXBITCTR_INIT      (((7u * BluetoothUART_OVER_SAMPLE_COUNT) - 1u) + \
                                                      BluetoothUART_HALF_BIT_COUNT)
#endif /* End BluetoothUART_OVER_SAMPLE_COUNT */

#define BluetoothUART_HD_RXBITCTR_INIT                   BluetoothUART_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 BluetoothUART_initVar;
#if (BluetoothUART_TX_INTERRUPT_ENABLED && BluetoothUART_TX_ENABLED)
    extern volatile uint8 BluetoothUART_txBuffer[BluetoothUART_TX_BUFFER_SIZE];
    extern volatile uint8 BluetoothUART_txBufferRead;
    extern uint8 BluetoothUART_txBufferWrite;
#endif /* (BluetoothUART_TX_INTERRUPT_ENABLED && BluetoothUART_TX_ENABLED) */
#if (BluetoothUART_RX_INTERRUPT_ENABLED && (BluetoothUART_RX_ENABLED || BluetoothUART_HD_ENABLED))
    extern uint8 BluetoothUART_errorStatus;
    extern volatile uint8 BluetoothUART_rxBuffer[BluetoothUART_RX_BUFFER_SIZE];
    extern volatile uint8 BluetoothUART_rxBufferRead;
    extern volatile uint8 BluetoothUART_rxBufferWrite;
    extern volatile uint8 BluetoothUART_rxBufferLoopDetect;
    extern volatile uint8 BluetoothUART_rxBufferOverflow;
    #if (BluetoothUART_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 BluetoothUART_rxAddressMode;
        extern volatile uint8 BluetoothUART_rxAddressDetected;
    #endif /* (BluetoothUART_RXHW_ADDRESS_ENABLED) */
#endif /* (BluetoothUART_RX_INTERRUPT_ENABLED && (BluetoothUART_RX_ENABLED || BluetoothUART_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define BluetoothUART__B_UART__AM_SW_BYTE_BYTE 1
#define BluetoothUART__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define BluetoothUART__B_UART__AM_HW_BYTE_BY_BYTE 3
#define BluetoothUART__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define BluetoothUART__B_UART__AM_NONE 0

#define BluetoothUART__B_UART__NONE_REVB 0
#define BluetoothUART__B_UART__EVEN_REVB 1
#define BluetoothUART__B_UART__ODD_REVB 2
#define BluetoothUART__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define BluetoothUART_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define BluetoothUART_NUMBER_OF_STOP_BITS    (1u)

#if (BluetoothUART_RXHW_ADDRESS_ENABLED)
    #define BluetoothUART_RX_ADDRESS_MODE    (0u)
    #define BluetoothUART_RX_HW_ADDRESS1     (0u)
    #define BluetoothUART_RX_HW_ADDRESS2     (0u)
#endif /* (BluetoothUART_RXHW_ADDRESS_ENABLED) */

#define BluetoothUART_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << BluetoothUART_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << BluetoothUART_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << BluetoothUART_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << BluetoothUART_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << BluetoothUART_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << BluetoothUART_RX_STS_BREAK_SHIFT) \
                                        | (0 << BluetoothUART_RX_STS_OVERRUN_SHIFT))

#define BluetoothUART_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << BluetoothUART_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << BluetoothUART_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << BluetoothUART_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << BluetoothUART_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef BluetoothUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define BluetoothUART_CONTROL_REG \
                            (* (reg8 *) BluetoothUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define BluetoothUART_CONTROL_PTR \
                            (  (reg8 *) BluetoothUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End BluetoothUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(BluetoothUART_TX_ENABLED)
    #define BluetoothUART_TXDATA_REG          (* (reg8 *) BluetoothUART_BUART_sTX_TxShifter_u0__F0_REG)
    #define BluetoothUART_TXDATA_PTR          (  (reg8 *) BluetoothUART_BUART_sTX_TxShifter_u0__F0_REG)
    #define BluetoothUART_TXDATA_AUX_CTL_REG  (* (reg8 *) BluetoothUART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define BluetoothUART_TXDATA_AUX_CTL_PTR  (  (reg8 *) BluetoothUART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define BluetoothUART_TXSTATUS_REG        (* (reg8 *) BluetoothUART_BUART_sTX_TxSts__STATUS_REG)
    #define BluetoothUART_TXSTATUS_PTR        (  (reg8 *) BluetoothUART_BUART_sTX_TxSts__STATUS_REG)
    #define BluetoothUART_TXSTATUS_MASK_REG   (* (reg8 *) BluetoothUART_BUART_sTX_TxSts__MASK_REG)
    #define BluetoothUART_TXSTATUS_MASK_PTR   (  (reg8 *) BluetoothUART_BUART_sTX_TxSts__MASK_REG)
    #define BluetoothUART_TXSTATUS_ACTL_REG   (* (reg8 *) BluetoothUART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define BluetoothUART_TXSTATUS_ACTL_PTR   (  (reg8 *) BluetoothUART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(BluetoothUART_TXCLKGEN_DP)
        #define BluetoothUART_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) BluetoothUART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define BluetoothUART_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) BluetoothUART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define BluetoothUART_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) BluetoothUART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define BluetoothUART_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) BluetoothUART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define BluetoothUART_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) BluetoothUART_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define BluetoothUART_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) BluetoothUART_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define BluetoothUART_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) BluetoothUART_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define BluetoothUART_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) BluetoothUART_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define BluetoothUART_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) BluetoothUART_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define BluetoothUART_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) BluetoothUART_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* BluetoothUART_TXCLKGEN_DP */

#endif /* End BluetoothUART_TX_ENABLED */

#if(BluetoothUART_HD_ENABLED)

    #define BluetoothUART_TXDATA_REG             (* (reg8 *) BluetoothUART_BUART_sRX_RxShifter_u0__F1_REG )
    #define BluetoothUART_TXDATA_PTR             (  (reg8 *) BluetoothUART_BUART_sRX_RxShifter_u0__F1_REG )
    #define BluetoothUART_TXDATA_AUX_CTL_REG     (* (reg8 *) BluetoothUART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define BluetoothUART_TXDATA_AUX_CTL_PTR     (  (reg8 *) BluetoothUART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define BluetoothUART_TXSTATUS_REG           (* (reg8 *) BluetoothUART_BUART_sRX_RxSts__STATUS_REG )
    #define BluetoothUART_TXSTATUS_PTR           (  (reg8 *) BluetoothUART_BUART_sRX_RxSts__STATUS_REG )
    #define BluetoothUART_TXSTATUS_MASK_REG      (* (reg8 *) BluetoothUART_BUART_sRX_RxSts__MASK_REG )
    #define BluetoothUART_TXSTATUS_MASK_PTR      (  (reg8 *) BluetoothUART_BUART_sRX_RxSts__MASK_REG )
    #define BluetoothUART_TXSTATUS_ACTL_REG      (* (reg8 *) BluetoothUART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define BluetoothUART_TXSTATUS_ACTL_PTR      (  (reg8 *) BluetoothUART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End BluetoothUART_HD_ENABLED */

#if( (BluetoothUART_RX_ENABLED) || (BluetoothUART_HD_ENABLED) )
    #define BluetoothUART_RXDATA_REG             (* (reg8 *) BluetoothUART_BUART_sRX_RxShifter_u0__F0_REG )
    #define BluetoothUART_RXDATA_PTR             (  (reg8 *) BluetoothUART_BUART_sRX_RxShifter_u0__F0_REG )
    #define BluetoothUART_RXADDRESS1_REG         (* (reg8 *) BluetoothUART_BUART_sRX_RxShifter_u0__D0_REG )
    #define BluetoothUART_RXADDRESS1_PTR         (  (reg8 *) BluetoothUART_BUART_sRX_RxShifter_u0__D0_REG )
    #define BluetoothUART_RXADDRESS2_REG         (* (reg8 *) BluetoothUART_BUART_sRX_RxShifter_u0__D1_REG )
    #define BluetoothUART_RXADDRESS2_PTR         (  (reg8 *) BluetoothUART_BUART_sRX_RxShifter_u0__D1_REG )
    #define BluetoothUART_RXDATA_AUX_CTL_REG     (* (reg8 *) BluetoothUART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define BluetoothUART_RXBITCTR_PERIOD_REG    (* (reg8 *) BluetoothUART_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define BluetoothUART_RXBITCTR_PERIOD_PTR    (  (reg8 *) BluetoothUART_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define BluetoothUART_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) BluetoothUART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define BluetoothUART_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) BluetoothUART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define BluetoothUART_RXBITCTR_COUNTER_REG   (* (reg8 *) BluetoothUART_BUART_sRX_RxBitCounter__COUNT_REG )
    #define BluetoothUART_RXBITCTR_COUNTER_PTR   (  (reg8 *) BluetoothUART_BUART_sRX_RxBitCounter__COUNT_REG )

    #define BluetoothUART_RXSTATUS_REG           (* (reg8 *) BluetoothUART_BUART_sRX_RxSts__STATUS_REG )
    #define BluetoothUART_RXSTATUS_PTR           (  (reg8 *) BluetoothUART_BUART_sRX_RxSts__STATUS_REG )
    #define BluetoothUART_RXSTATUS_MASK_REG      (* (reg8 *) BluetoothUART_BUART_sRX_RxSts__MASK_REG )
    #define BluetoothUART_RXSTATUS_MASK_PTR      (  (reg8 *) BluetoothUART_BUART_sRX_RxSts__MASK_REG )
    #define BluetoothUART_RXSTATUS_ACTL_REG      (* (reg8 *) BluetoothUART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define BluetoothUART_RXSTATUS_ACTL_PTR      (  (reg8 *) BluetoothUART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (BluetoothUART_RX_ENABLED) || (BluetoothUART_HD_ENABLED) */

#if(BluetoothUART_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define BluetoothUART_INTCLOCK_CLKEN_REG     (* (reg8 *) BluetoothUART_IntClock__PM_ACT_CFG)
    #define BluetoothUART_INTCLOCK_CLKEN_PTR     (  (reg8 *) BluetoothUART_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define BluetoothUART_INTCLOCK_CLKEN_MASK    BluetoothUART_IntClock__PM_ACT_MSK
#endif /* End BluetoothUART_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(BluetoothUART_TX_ENABLED)
    #define BluetoothUART_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End BluetoothUART_TX_ENABLED */

#if(BluetoothUART_HD_ENABLED)
    #define BluetoothUART_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End BluetoothUART_HD_ENABLED */

#if( (BluetoothUART_RX_ENABLED) || (BluetoothUART_HD_ENABLED) )
    #define BluetoothUART_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (BluetoothUART_RX_ENABLED) || (BluetoothUART_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define BluetoothUART_WAIT_1_MS      BluetoothUART_BL_CHK_DELAY_MS   

#define BluetoothUART_TXBUFFERSIZE   BluetoothUART_TX_BUFFER_SIZE
#define BluetoothUART_RXBUFFERSIZE   BluetoothUART_RX_BUFFER_SIZE

#if (BluetoothUART_RXHW_ADDRESS_ENABLED)
    #define BluetoothUART_RXADDRESSMODE  BluetoothUART_RX_ADDRESS_MODE
    #define BluetoothUART_RXHWADDRESS1   BluetoothUART_RX_HW_ADDRESS1
    #define BluetoothUART_RXHWADDRESS2   BluetoothUART_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define BluetoothUART_RXAddressMode  BluetoothUART_RXADDRESSMODE
#endif /* (BluetoothUART_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define BluetoothUART_initvar                    BluetoothUART_initVar

#define BluetoothUART_RX_Enabled                 BluetoothUART_RX_ENABLED
#define BluetoothUART_TX_Enabled                 BluetoothUART_TX_ENABLED
#define BluetoothUART_HD_Enabled                 BluetoothUART_HD_ENABLED
#define BluetoothUART_RX_IntInterruptEnabled     BluetoothUART_RX_INTERRUPT_ENABLED
#define BluetoothUART_TX_IntInterruptEnabled     BluetoothUART_TX_INTERRUPT_ENABLED
#define BluetoothUART_InternalClockUsed          BluetoothUART_INTERNAL_CLOCK_USED
#define BluetoothUART_RXHW_Address_Enabled       BluetoothUART_RXHW_ADDRESS_ENABLED
#define BluetoothUART_OverSampleCount            BluetoothUART_OVER_SAMPLE_COUNT
#define BluetoothUART_ParityType                 BluetoothUART_PARITY_TYPE

#if( BluetoothUART_TX_ENABLED && (BluetoothUART_TXBUFFERSIZE > BluetoothUART_FIFO_LENGTH))
    #define BluetoothUART_TXBUFFER               BluetoothUART_txBuffer
    #define BluetoothUART_TXBUFFERREAD           BluetoothUART_txBufferRead
    #define BluetoothUART_TXBUFFERWRITE          BluetoothUART_txBufferWrite
#endif /* End BluetoothUART_TX_ENABLED */
#if( ( BluetoothUART_RX_ENABLED || BluetoothUART_HD_ENABLED ) && \
     (BluetoothUART_RXBUFFERSIZE > BluetoothUART_FIFO_LENGTH) )
    #define BluetoothUART_RXBUFFER               BluetoothUART_rxBuffer
    #define BluetoothUART_RXBUFFERREAD           BluetoothUART_rxBufferRead
    #define BluetoothUART_RXBUFFERWRITE          BluetoothUART_rxBufferWrite
    #define BluetoothUART_RXBUFFERLOOPDETECT     BluetoothUART_rxBufferLoopDetect
    #define BluetoothUART_RXBUFFER_OVERFLOW      BluetoothUART_rxBufferOverflow
#endif /* End BluetoothUART_RX_ENABLED */

#ifdef BluetoothUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define BluetoothUART_CONTROL                BluetoothUART_CONTROL_REG
#endif /* End BluetoothUART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(BluetoothUART_TX_ENABLED)
    #define BluetoothUART_TXDATA                 BluetoothUART_TXDATA_REG
    #define BluetoothUART_TXSTATUS               BluetoothUART_TXSTATUS_REG
    #define BluetoothUART_TXSTATUS_MASK          BluetoothUART_TXSTATUS_MASK_REG
    #define BluetoothUART_TXSTATUS_ACTL          BluetoothUART_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(BluetoothUART_TXCLKGEN_DP)
        #define BluetoothUART_TXBITCLKGEN_CTR        BluetoothUART_TXBITCLKGEN_CTR_REG
        #define BluetoothUART_TXBITCLKTX_COMPLETE    BluetoothUART_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define BluetoothUART_TXBITCTR_PERIOD        BluetoothUART_TXBITCTR_PERIOD_REG
        #define BluetoothUART_TXBITCTR_CONTROL       BluetoothUART_TXBITCTR_CONTROL_REG
        #define BluetoothUART_TXBITCTR_COUNTER       BluetoothUART_TXBITCTR_COUNTER_REG
    #endif /* BluetoothUART_TXCLKGEN_DP */
#endif /* End BluetoothUART_TX_ENABLED */

#if(BluetoothUART_HD_ENABLED)
    #define BluetoothUART_TXDATA                 BluetoothUART_TXDATA_REG
    #define BluetoothUART_TXSTATUS               BluetoothUART_TXSTATUS_REG
    #define BluetoothUART_TXSTATUS_MASK          BluetoothUART_TXSTATUS_MASK_REG
    #define BluetoothUART_TXSTATUS_ACTL          BluetoothUART_TXSTATUS_ACTL_REG
#endif /* End BluetoothUART_HD_ENABLED */

#if( (BluetoothUART_RX_ENABLED) || (BluetoothUART_HD_ENABLED) )
    #define BluetoothUART_RXDATA                 BluetoothUART_RXDATA_REG
    #define BluetoothUART_RXADDRESS1             BluetoothUART_RXADDRESS1_REG
    #define BluetoothUART_RXADDRESS2             BluetoothUART_RXADDRESS2_REG
    #define BluetoothUART_RXBITCTR_PERIOD        BluetoothUART_RXBITCTR_PERIOD_REG
    #define BluetoothUART_RXBITCTR_CONTROL       BluetoothUART_RXBITCTR_CONTROL_REG
    #define BluetoothUART_RXBITCTR_COUNTER       BluetoothUART_RXBITCTR_COUNTER_REG
    #define BluetoothUART_RXSTATUS               BluetoothUART_RXSTATUS_REG
    #define BluetoothUART_RXSTATUS_MASK          BluetoothUART_RXSTATUS_MASK_REG
    #define BluetoothUART_RXSTATUS_ACTL          BluetoothUART_RXSTATUS_ACTL_REG
#endif /* End  (BluetoothUART_RX_ENABLED) || (BluetoothUART_HD_ENABLED) */

#if(BluetoothUART_INTERNAL_CLOCK_USED)
    #define BluetoothUART_INTCLOCK_CLKEN         BluetoothUART_INTCLOCK_CLKEN_REG
#endif /* End BluetoothUART_INTERNAL_CLOCK_USED */

#define BluetoothUART_WAIT_FOR_COMLETE_REINIT    BluetoothUART_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_BluetoothUART_H */


/* [] END OF FILE */
