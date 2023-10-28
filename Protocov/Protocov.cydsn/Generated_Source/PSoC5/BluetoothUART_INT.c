/*******************************************************************************
* File Name: BluetoothUARTINT.c
* Version 2.50
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "BluetoothUART.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */
#include "project.h"
#include "FreeRTOS.h"
#include "task.h"
#include "BluetoothComms.h"


extern uint8_t bluetoothRecMsgByte;

volatile int entryCounter = 0;


/* `#END` */

#if (BluetoothUART_RX_INTERRUPT_ENABLED && (BluetoothUART_RX_ENABLED || BluetoothUART_HD_ENABLED))
    /*******************************************************************************
    * Function Name: BluetoothUART_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BluetoothUART_rxBuffer - RAM buffer pointer for save received data.
    *  BluetoothUART_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  BluetoothUART_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  BluetoothUART_rxBufferOverflow - software overflow flag. Set to one
    *     when BluetoothUART_rxBufferWrite index overtakes
    *     BluetoothUART_rxBufferRead index.
    *  BluetoothUART_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when BluetoothUART_rxBufferWrite is equal to
    *    BluetoothUART_rxBufferRead
    *  BluetoothUART_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  BluetoothUART_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(BluetoothUART_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef BluetoothUART_RXISR_ENTRY_CALLBACK
        BluetoothUART_RXISR_EntryCallback();
    #endif /* BluetoothUART_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START BluetoothUART_RXISR_START` */
    
            
        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = BluetoothUART_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in BluetoothUART_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (BluetoothUART_RX_STS_BREAK | 
                            BluetoothUART_RX_STS_PAR_ERROR |
                            BluetoothUART_RX_STS_STOP_ERROR | 
                            BluetoothUART_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                BluetoothUART_errorStatus |= readStatus & ( BluetoothUART_RX_STS_BREAK | 
                                                            BluetoothUART_RX_STS_PAR_ERROR | 
                                                            BluetoothUART_RX_STS_STOP_ERROR | 
                                                            BluetoothUART_RX_STS_OVERRUN);
                /* `#START BluetoothUART_RXISR_ERROR` */
                    readData++;    
                /* `#END` */
                
            #ifdef BluetoothUART_RXISR_ERROR_CALLBACK
                BluetoothUART_RXISR_ERROR_Callback();
            #endif /* BluetoothUART_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & BluetoothUART_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = BluetoothUART_RXDATA_REG;
            #if (BluetoothUART_RXHW_ADDRESS_ENABLED)
                if(BluetoothUART_rxAddressMode == (uint8)BluetoothUART__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & BluetoothUART_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & BluetoothUART_RX_STS_ADDR_MATCH) != 0u)
                        {
                            BluetoothUART_rxAddressDetected = 1u;
                        }
                        else
                        {
                            BluetoothUART_rxAddressDetected = 0u;
                        }
                    }
                    if(BluetoothUART_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        BluetoothUART_rxBuffer[BluetoothUART_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    BluetoothUART_rxBuffer[BluetoothUART_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                BluetoothUART_rxBuffer[BluetoothUART_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (BluetoothUART_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(BluetoothUART_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        BluetoothUART_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    BluetoothUART_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(BluetoothUART_rxBufferWrite >= BluetoothUART_RX_BUFFER_SIZE)
                    {
                        BluetoothUART_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(BluetoothUART_rxBufferWrite == BluetoothUART_rxBufferRead)
                    {
                        BluetoothUART_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (BluetoothUART_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            BluetoothUART_RXSTATUS_MASK_REG  &= (uint8)~BluetoothUART_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(BluetoothUART_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (BluetoothUART_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & BluetoothUART_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START BluetoothUART_RXISR_END` */
        
        
    
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;  
  
        xTaskHandle temp = getBluetoothCommsTaskHandle();
  
        if(temp == NULL) return;
        
        xTaskNotifyFromISR(getBluetoothCommsTaskHandle(),eSetBits , 0, &xHigherPriorityTaskWoken);
               
        /* `#END` */

    #ifdef BluetoothUART_RXISR_EXIT_CALLBACK
        BluetoothUART_RXISR_ExitCallback();
    #endif /* BluetoothUART_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (BluetoothUART_RX_INTERRUPT_ENABLED && (BluetoothUART_RX_ENABLED || BluetoothUART_HD_ENABLED)) */


#if (BluetoothUART_TX_INTERRUPT_ENABLED && BluetoothUART_TX_ENABLED)
    /*******************************************************************************
    * Function Name: BluetoothUART_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BluetoothUART_txBuffer - RAM buffer pointer for transmit data from.
    *  BluetoothUART_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  BluetoothUART_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(BluetoothUART_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef BluetoothUART_TXISR_ENTRY_CALLBACK
        BluetoothUART_TXISR_EntryCallback();
    #endif /* BluetoothUART_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START BluetoothUART_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((BluetoothUART_txBufferRead != BluetoothUART_txBufferWrite) &&
             ((BluetoothUART_TXSTATUS_REG & BluetoothUART_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(BluetoothUART_txBufferRead >= BluetoothUART_TX_BUFFER_SIZE)
            {
                BluetoothUART_txBufferRead = 0u;
            }

            BluetoothUART_TXDATA_REG = BluetoothUART_txBuffer[BluetoothUART_txBufferRead];

            /* Set next pointer */
            BluetoothUART_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START BluetoothUART_TXISR_END` */

        /* `#END` */

    #ifdef BluetoothUART_TXISR_EXIT_CALLBACK
        BluetoothUART_TXISR_ExitCallback();
    #endif /* BluetoothUART_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (BluetoothUART_TX_INTERRUPT_ENABLED && BluetoothUART_TX_ENABLED) */


/* [] END OF FILE */
