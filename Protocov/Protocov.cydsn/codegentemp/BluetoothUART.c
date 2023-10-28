/*******************************************************************************
* File Name: BluetoothUART.c
* Version 2.50
*
* Description:
*  This file provides all API functionality of the UART component
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "BluetoothUART.h"
#if (BluetoothUART_INTERNAL_CLOCK_USED)
    #include "BluetoothUART_IntClock.h"
#endif /* End BluetoothUART_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 BluetoothUART_initVar = 0u;

#if (BluetoothUART_TX_INTERRUPT_ENABLED && BluetoothUART_TX_ENABLED)
    volatile uint8 BluetoothUART_txBuffer[BluetoothUART_TX_BUFFER_SIZE];
    volatile uint8 BluetoothUART_txBufferRead = 0u;
    uint8 BluetoothUART_txBufferWrite = 0u;
#endif /* (BluetoothUART_TX_INTERRUPT_ENABLED && BluetoothUART_TX_ENABLED) */

#if (BluetoothUART_RX_INTERRUPT_ENABLED && (BluetoothUART_RX_ENABLED || BluetoothUART_HD_ENABLED))
    uint8 BluetoothUART_errorStatus = 0u;
    volatile uint8 BluetoothUART_rxBuffer[BluetoothUART_RX_BUFFER_SIZE];
    volatile uint8 BluetoothUART_rxBufferRead  = 0u;
    volatile uint8 BluetoothUART_rxBufferWrite = 0u;
    volatile uint8 BluetoothUART_rxBufferLoopDetect = 0u;
    volatile uint8 BluetoothUART_rxBufferOverflow   = 0u;
    #if (BluetoothUART_RXHW_ADDRESS_ENABLED)
        volatile uint8 BluetoothUART_rxAddressMode = BluetoothUART_RX_ADDRESS_MODE;
        volatile uint8 BluetoothUART_rxAddressDetected = 0u;
    #endif /* (BluetoothUART_RXHW_ADDRESS_ENABLED) */
#endif /* (BluetoothUART_RX_INTERRUPT_ENABLED && (BluetoothUART_RX_ENABLED || BluetoothUART_HD_ENABLED)) */


/*******************************************************************************
* Function Name: BluetoothUART_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  BluetoothUART_Start() sets the initVar variable, calls the
*  BluetoothUART_Init() function, and then calls the
*  BluetoothUART_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The BluetoothUART_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time BluetoothUART_Start() is called. This
*  allows for component initialization without re-initialization in all
*  subsequent calls to the BluetoothUART_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void BluetoothUART_Start(void) 
{
    /* If not initialized then initialize all required hardware and software */
    if(BluetoothUART_initVar == 0u)
    {
        BluetoothUART_Init();
        BluetoothUART_initVar = 1u;
    }

    BluetoothUART_Enable();
}


/*******************************************************************************
* Function Name: BluetoothUART_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call BluetoothUART_Init() because
*  the BluetoothUART_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void BluetoothUART_Init(void) 
{
    #if(BluetoothUART_RX_ENABLED || BluetoothUART_HD_ENABLED)

        #if (BluetoothUART_RX_INTERRUPT_ENABLED)
            /* Set RX interrupt vector and priority */
            (void) CyIntSetVector(BluetoothUART_RX_VECT_NUM, &BluetoothUART_RXISR);
            CyIntSetPriority(BluetoothUART_RX_VECT_NUM, BluetoothUART_RX_PRIOR_NUM);
            BluetoothUART_errorStatus = 0u;
        #endif /* (BluetoothUART_RX_INTERRUPT_ENABLED) */

        #if (BluetoothUART_RXHW_ADDRESS_ENABLED)
            BluetoothUART_SetRxAddressMode(BluetoothUART_RX_ADDRESS_MODE);
            BluetoothUART_SetRxAddress1(BluetoothUART_RX_HW_ADDRESS1);
            BluetoothUART_SetRxAddress2(BluetoothUART_RX_HW_ADDRESS2);
        #endif /* End BluetoothUART_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        BluetoothUART_RXBITCTR_PERIOD_REG = BluetoothUART_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        BluetoothUART_RXSTATUS_MASK_REG  = BluetoothUART_INIT_RX_INTERRUPTS_MASK;
    #endif /* End BluetoothUART_RX_ENABLED || BluetoothUART_HD_ENABLED*/

    #if(BluetoothUART_TX_ENABLED)
        #if (BluetoothUART_TX_INTERRUPT_ENABLED)
            /* Set TX interrupt vector and priority */
            (void) CyIntSetVector(BluetoothUART_TX_VECT_NUM, &BluetoothUART_TXISR);
            CyIntSetPriority(BluetoothUART_TX_VECT_NUM, BluetoothUART_TX_PRIOR_NUM);
        #endif /* (BluetoothUART_TX_INTERRUPT_ENABLED) */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if (BluetoothUART_TXCLKGEN_DP)
            BluetoothUART_TXBITCLKGEN_CTR_REG = BluetoothUART_BIT_CENTER;
            BluetoothUART_TXBITCLKTX_COMPLETE_REG = ((BluetoothUART_NUMBER_OF_DATA_BITS +
                        BluetoothUART_NUMBER_OF_START_BIT) * BluetoothUART_OVER_SAMPLE_COUNT) - 1u;
        #else
            BluetoothUART_TXBITCTR_PERIOD_REG = ((BluetoothUART_NUMBER_OF_DATA_BITS +
                        BluetoothUART_NUMBER_OF_START_BIT) * BluetoothUART_OVER_SAMPLE_8) - 1u;
        #endif /* End BluetoothUART_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if (BluetoothUART_TX_INTERRUPT_ENABLED)
            BluetoothUART_TXSTATUS_MASK_REG = BluetoothUART_TX_STS_FIFO_EMPTY;
        #else
            BluetoothUART_TXSTATUS_MASK_REG = BluetoothUART_INIT_TX_INTERRUPTS_MASK;
        #endif /*End BluetoothUART_TX_INTERRUPT_ENABLED*/

    #endif /* End BluetoothUART_TX_ENABLED */

    #if(BluetoothUART_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        BluetoothUART_WriteControlRegister( \
            (BluetoothUART_ReadControlRegister() & (uint8)~BluetoothUART_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(BluetoothUART_PARITY_TYPE << BluetoothUART_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End BluetoothUART_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: BluetoothUART_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary
*  to call BluetoothUART_Enable() because the BluetoothUART_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.

* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  BluetoothUART_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void BluetoothUART_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if (BluetoothUART_RX_ENABLED || BluetoothUART_HD_ENABLED)
        /* RX Counter (Count7) Enable */
        BluetoothUART_RXBITCTR_CONTROL_REG |= BluetoothUART_CNTR_ENABLE;

        /* Enable the RX Interrupt */
        BluetoothUART_RXSTATUS_ACTL_REG  |= BluetoothUART_INT_ENABLE;

        #if (BluetoothUART_RX_INTERRUPT_ENABLED)
            BluetoothUART_EnableRxInt();

            #if (BluetoothUART_RXHW_ADDRESS_ENABLED)
                BluetoothUART_rxAddressDetected = 0u;
            #endif /* (BluetoothUART_RXHW_ADDRESS_ENABLED) */
        #endif /* (BluetoothUART_RX_INTERRUPT_ENABLED) */
    #endif /* (BluetoothUART_RX_ENABLED || BluetoothUART_HD_ENABLED) */

    #if(BluetoothUART_TX_ENABLED)
        /* TX Counter (DP/Count7) Enable */
        #if(!BluetoothUART_TXCLKGEN_DP)
            BluetoothUART_TXBITCTR_CONTROL_REG |= BluetoothUART_CNTR_ENABLE;
        #endif /* End BluetoothUART_TXCLKGEN_DP */

        /* Enable the TX Interrupt */
        BluetoothUART_TXSTATUS_ACTL_REG |= BluetoothUART_INT_ENABLE;
        #if (BluetoothUART_TX_INTERRUPT_ENABLED)
            BluetoothUART_ClearPendingTxInt(); /* Clear history of TX_NOT_EMPTY */
            BluetoothUART_EnableTxInt();
        #endif /* (BluetoothUART_TX_INTERRUPT_ENABLED) */
     #endif /* (BluetoothUART_TX_INTERRUPT_ENABLED) */

    #if (BluetoothUART_INTERNAL_CLOCK_USED)
        BluetoothUART_IntClock_Start();  /* Enable the clock */
    #endif /* (BluetoothUART_INTERNAL_CLOCK_USED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BluetoothUART_Stop
********************************************************************************
*
* Summary:
*  Disables the UART operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void BluetoothUART_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if (BluetoothUART_RX_ENABLED || BluetoothUART_HD_ENABLED)
        BluetoothUART_RXBITCTR_CONTROL_REG &= (uint8) ~BluetoothUART_CNTR_ENABLE;
    #endif /* (BluetoothUART_RX_ENABLED || BluetoothUART_HD_ENABLED) */

    #if (BluetoothUART_TX_ENABLED)
        #if(!BluetoothUART_TXCLKGEN_DP)
            BluetoothUART_TXBITCTR_CONTROL_REG &= (uint8) ~BluetoothUART_CNTR_ENABLE;
        #endif /* (!BluetoothUART_TXCLKGEN_DP) */
    #endif /* (BluetoothUART_TX_ENABLED) */

    #if (BluetoothUART_INTERNAL_CLOCK_USED)
        BluetoothUART_IntClock_Stop();   /* Disable the clock */
    #endif /* (BluetoothUART_INTERNAL_CLOCK_USED) */

    /* Disable internal interrupt component */
    #if (BluetoothUART_RX_ENABLED || BluetoothUART_HD_ENABLED)
        BluetoothUART_RXSTATUS_ACTL_REG  &= (uint8) ~BluetoothUART_INT_ENABLE;

        #if (BluetoothUART_RX_INTERRUPT_ENABLED)
            BluetoothUART_DisableRxInt();
        #endif /* (BluetoothUART_RX_INTERRUPT_ENABLED) */
    #endif /* (BluetoothUART_RX_ENABLED || BluetoothUART_HD_ENABLED) */

    #if (BluetoothUART_TX_ENABLED)
        BluetoothUART_TXSTATUS_ACTL_REG &= (uint8) ~BluetoothUART_INT_ENABLE;

        #if (BluetoothUART_TX_INTERRUPT_ENABLED)
            BluetoothUART_DisableTxInt();
        #endif /* (BluetoothUART_TX_INTERRUPT_ENABLED) */
    #endif /* (BluetoothUART_TX_ENABLED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BluetoothUART_ReadControlRegister
********************************************************************************
*
* Summary:
*  Returns the current value of the control register.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the control register.
*
*******************************************************************************/
uint8 BluetoothUART_ReadControlRegister(void) 
{
    #if (BluetoothUART_CONTROL_REG_REMOVED)
        return(0u);
    #else
        return(BluetoothUART_CONTROL_REG);
    #endif /* (BluetoothUART_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: BluetoothUART_WriteControlRegister
********************************************************************************
*
* Summary:
*  Writes an 8-bit value into the control register
*
* Parameters:
*  control:  control register value
*
* Return:
*  None.
*
*******************************************************************************/
void  BluetoothUART_WriteControlRegister(uint8 control) 
{
    #if (BluetoothUART_CONTROL_REG_REMOVED)
        if(0u != control)
        {
            /* Suppress compiler warning */
        }
    #else
       BluetoothUART_CONTROL_REG = control;
    #endif /* (BluetoothUART_CONTROL_REG_REMOVED) */
}


#if(BluetoothUART_RX_ENABLED || BluetoothUART_HD_ENABLED)
    /*******************************************************************************
    * Function Name: BluetoothUART_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the RX interrupt sources enabled.
    *
    * Parameters:
    *  IntSrc:  Bit field containing the RX interrupts to enable. Based on the 
    *  bit-field arrangement of the status register. This value must be a 
    *  combination of status register bit-masks shown below:
    *      BluetoothUART_RX_STS_FIFO_NOTEMPTY    Interrupt on byte received.
    *      BluetoothUART_RX_STS_PAR_ERROR        Interrupt on parity error.
    *      BluetoothUART_RX_STS_STOP_ERROR       Interrupt on stop error.
    *      BluetoothUART_RX_STS_BREAK            Interrupt on break.
    *      BluetoothUART_RX_STS_OVERRUN          Interrupt on overrun error.
    *      BluetoothUART_RX_STS_ADDR_MATCH       Interrupt on address match.
    *      BluetoothUART_RX_STS_MRKSPC           Interrupt on address detect.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void BluetoothUART_SetRxInterruptMode(uint8 intSrc) 
    {
        BluetoothUART_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: BluetoothUART_ReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Returns the next byte of received data. This function returns data without
    *  checking the status. You must check the status separately.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Received data from RX register
    *
    * Global Variables:
    *  BluetoothUART_rxBuffer - RAM buffer pointer for save received data.
    *  BluetoothUART_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  BluetoothUART_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  BluetoothUART_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 BluetoothUART_ReadRxData(void) 
    {
        uint8 rxData;

    #if (BluetoothUART_RX_INTERRUPT_ENABLED)

        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        BluetoothUART_DisableRxInt();

        locRxBufferRead  = BluetoothUART_rxBufferRead;
        locRxBufferWrite = BluetoothUART_rxBufferWrite;

        if( (BluetoothUART_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = BluetoothUART_rxBuffer[locRxBufferRead];
            locRxBufferRead++;

            if(locRxBufferRead >= BluetoothUART_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            BluetoothUART_rxBufferRead = locRxBufferRead;

            if(BluetoothUART_rxBufferLoopDetect != 0u)
            {
                BluetoothUART_rxBufferLoopDetect = 0u;
                #if ((BluetoothUART_RX_INTERRUPT_ENABLED) && (BluetoothUART_FLOW_CONTROL != 0u))
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( BluetoothUART_HD_ENABLED )
                        if((BluetoothUART_CONTROL_REG & BluetoothUART_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only in RX
                            *  configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            BluetoothUART_RXSTATUS_MASK_REG  |= BluetoothUART_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        BluetoothUART_RXSTATUS_MASK_REG  |= BluetoothUART_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end BluetoothUART_HD_ENABLED */
                #endif /* ((BluetoothUART_RX_INTERRUPT_ENABLED) && (BluetoothUART_FLOW_CONTROL != 0u)) */
            }
        }
        else
        {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
            rxData = BluetoothUART_RXDATA_REG;
        }

        BluetoothUART_EnableRxInt();

    #else

        /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
        rxData = BluetoothUART_RXDATA_REG;

    #endif /* (BluetoothUART_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: BluetoothUART_ReadRxStatus
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the receiver status register and the software
    *  buffer overflow status.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Current state of the status register.
    *
    * Side Effect:
    *  All status register bits are clear-on-read except
    *  BluetoothUART_RX_STS_FIFO_NOTEMPTY.
    *  BluetoothUART_RX_STS_FIFO_NOTEMPTY clears immediately after RX data
    *  register read.
    *
    * Global Variables:
    *  BluetoothUART_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn't free space in
    *   BluetoothUART_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   BluetoothUART_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 BluetoothUART_ReadRxStatus(void) 
    {
        uint8 status;

        status = BluetoothUART_RXSTATUS_REG & BluetoothUART_RX_HW_MASK;

    #if (BluetoothUART_RX_INTERRUPT_ENABLED)
        if(BluetoothUART_rxBufferOverflow != 0u)
        {
            status |= BluetoothUART_RX_STS_SOFT_BUFF_OVER;
            BluetoothUART_rxBufferOverflow = 0u;
        }
    #endif /* (BluetoothUART_RX_INTERRUPT_ENABLED) */

        return(status);
    }


    /*******************************************************************************
    * Function Name: BluetoothUART_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Returns the last received byte of data. BluetoothUART_GetChar() is
    *  designed for ASCII characters and returns a uint8 where 1 to 255 are values
    *  for valid characters and 0 indicates an error occurred or no data is present.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Character read from UART RX buffer. ASCII characters from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Global Variables:
    *  BluetoothUART_rxBuffer - RAM buffer pointer for save received data.
    *  BluetoothUART_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  BluetoothUART_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  BluetoothUART_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 BluetoothUART_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

    #if (BluetoothUART_RX_INTERRUPT_ENABLED)
        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        BluetoothUART_DisableRxInt();

        locRxBufferRead  = BluetoothUART_rxBufferRead;
        locRxBufferWrite = BluetoothUART_rxBufferWrite;

        if( (BluetoothUART_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = BluetoothUART_rxBuffer[locRxBufferRead];
            locRxBufferRead++;
            if(locRxBufferRead >= BluetoothUART_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            BluetoothUART_rxBufferRead = locRxBufferRead;

            if(BluetoothUART_rxBufferLoopDetect != 0u)
            {
                BluetoothUART_rxBufferLoopDetect = 0u;
                #if( (BluetoothUART_RX_INTERRUPT_ENABLED) && (BluetoothUART_FLOW_CONTROL != 0u) )
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( BluetoothUART_HD_ENABLED )
                        if((BluetoothUART_CONTROL_REG & BluetoothUART_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only if
                            *  RX configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            BluetoothUART_RXSTATUS_MASK_REG |= BluetoothUART_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        BluetoothUART_RXSTATUS_MASK_REG |= BluetoothUART_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end BluetoothUART_HD_ENABLED */
                #endif /* BluetoothUART_RX_INTERRUPT_ENABLED and Hardware flow control*/
            }

        }
        else
        {   rxStatus = BluetoothUART_RXSTATUS_REG;
            if((rxStatus & BluetoothUART_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO */
                rxData = BluetoothUART_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (BluetoothUART_RX_STS_BREAK | BluetoothUART_RX_STS_PAR_ERROR |
                                BluetoothUART_RX_STS_STOP_ERROR | BluetoothUART_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        }

        BluetoothUART_EnableRxInt();

    #else

        rxStatus =BluetoothUART_RXSTATUS_REG;
        if((rxStatus & BluetoothUART_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read received data from FIFO */
            rxData = BluetoothUART_RXDATA_REG;

            /*Check status on error*/
            if((rxStatus & (BluetoothUART_RX_STS_BREAK | BluetoothUART_RX_STS_PAR_ERROR |
                            BluetoothUART_RX_STS_STOP_ERROR | BluetoothUART_RX_STS_OVERRUN)) != 0u)
            {
                rxData = 0u;
            }
        }
    #endif /* (BluetoothUART_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: BluetoothUART_GetByte
    ********************************************************************************
    *
    * Summary:
    *  Reads UART RX buffer immediately, returns received character and error
    *  condition.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  MSB contains status and LSB contains UART RX data. If the MSB is nonzero,
    *  an error has occurred.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 BluetoothUART_GetByte(void) 
    {
        
    #if (BluetoothUART_RX_INTERRUPT_ENABLED)
        uint16 locErrorStatus;
        /* Protect variables that could change on interrupt */
        BluetoothUART_DisableRxInt();
        locErrorStatus = (uint16)BluetoothUART_errorStatus;
        BluetoothUART_errorStatus = 0u;
        BluetoothUART_EnableRxInt();
        return ( (uint16)(locErrorStatus << 8u) | BluetoothUART_ReadRxData() );
    #else
        return ( ((uint16)BluetoothUART_ReadRxStatus() << 8u) | BluetoothUART_ReadRxData() );
    #endif /* BluetoothUART_RX_INTERRUPT_ENABLED */
        
    }


    /*******************************************************************************
    * Function Name: BluetoothUART_GetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received bytes available in the RX buffer.
    *  * RX software buffer is disabled (RX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty RX FIFO or 1 for not empty RX FIFO.
    *  * RX software buffer is enabled: returns the number of bytes available in 
    *    the RX software buffer. Bytes available in the RX FIFO do not take to 
    *    account.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  uint8: Number of bytes in the RX buffer. 
    *    Return value type depends on RX Buffer Size parameter.
    *
    * Global Variables:
    *  BluetoothUART_rxBufferWrite - used to calculate left bytes.
    *  BluetoothUART_rxBufferRead - used to calculate left bytes.
    *  BluetoothUART_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 BluetoothUART_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (BluetoothUART_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt */
        BluetoothUART_DisableRxInt();

        if(BluetoothUART_rxBufferRead == BluetoothUART_rxBufferWrite)
        {
            if(BluetoothUART_rxBufferLoopDetect != 0u)
            {
                size = BluetoothUART_RX_BUFFER_SIZE;
            }
            else
            {
                size = 0u;
            }
        }
        else if(BluetoothUART_rxBufferRead < BluetoothUART_rxBufferWrite)
        {
            size = (BluetoothUART_rxBufferWrite - BluetoothUART_rxBufferRead);
        }
        else
        {
            size = (BluetoothUART_RX_BUFFER_SIZE - BluetoothUART_rxBufferRead) + BluetoothUART_rxBufferWrite;
        }

        BluetoothUART_EnableRxInt();

    #else

        /* We can only know if there is data in the fifo. */
        size = ((BluetoothUART_RXSTATUS_REG & BluetoothUART_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

    #endif /* (BluetoothUART_RX_INTERRUPT_ENABLED) */

        return(size);
    }


    /*******************************************************************************
    * Function Name: BluetoothUART_ClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the receiver memory buffer and hardware RX FIFO of all received data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BluetoothUART_rxBufferWrite - cleared to zero.
    *  BluetoothUART_rxBufferRead - cleared to zero.
    *  BluetoothUART_rxBufferLoopDetect - cleared to zero.
    *  BluetoothUART_rxBufferOverflow - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may
    *  have remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM or FIFO buffer will be lost.
    *
    *******************************************************************************/
    void BluetoothUART_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Clear the HW FIFO */
        enableInterrupts = CyEnterCriticalSection();
        BluetoothUART_RXDATA_AUX_CTL_REG |= (uint8)  BluetoothUART_RX_FIFO_CLR;
        BluetoothUART_RXDATA_AUX_CTL_REG &= (uint8) ~BluetoothUART_RX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (BluetoothUART_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        BluetoothUART_DisableRxInt();

        BluetoothUART_rxBufferRead = 0u;
        BluetoothUART_rxBufferWrite = 0u;
        BluetoothUART_rxBufferLoopDetect = 0u;
        BluetoothUART_rxBufferOverflow = 0u;

        BluetoothUART_EnableRxInt();

    #endif /* (BluetoothUART_RX_INTERRUPT_ENABLED) */

    }


    /*******************************************************************************
    * Function Name: BluetoothUART_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the software controlled Addressing mode used by the RX portion of the
    *  UART.
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  BluetoothUART__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  BluetoothUART__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  BluetoothUART__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  BluetoothUART__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  BluetoothUART__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BluetoothUART_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  BluetoothUART_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void BluetoothUART_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(BluetoothUART_RXHW_ADDRESS_ENABLED)
            #if(BluetoothUART_CONTROL_REG_REMOVED)
                if(0u != addressMode)
                {
                    /* Suppress compiler warning */
                }
            #else /* BluetoothUART_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = BluetoothUART_CONTROL_REG & (uint8)~BluetoothUART_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << BluetoothUART_CTRL_RXADDR_MODE0_SHIFT);
                BluetoothUART_CONTROL_REG = tmpCtrl;

                #if(BluetoothUART_RX_INTERRUPT_ENABLED && \
                   (BluetoothUART_RXBUFFERSIZE > BluetoothUART_FIFO_LENGTH) )
                    BluetoothUART_rxAddressMode = addressMode;
                    BluetoothUART_rxAddressDetected = 0u;
                #endif /* End BluetoothUART_RXBUFFERSIZE > BluetoothUART_FIFO_LENGTH*/
            #endif /* End BluetoothUART_CONTROL_REG_REMOVED */
        #else /* BluetoothUART_RXHW_ADDRESS_ENABLED */
            if(0u != addressMode)
            {
                /* Suppress compiler warning */
            }
        #endif /* End BluetoothUART_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: BluetoothUART_SetRxAddress1
    ********************************************************************************
    *
    * Summary:
    *  Sets the first of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #1 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void BluetoothUART_SetRxAddress1(uint8 address) 
    {
        BluetoothUART_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: BluetoothUART_SetRxAddress2
    ********************************************************************************
    *
    * Summary:
    *  Sets the second of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #2 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void BluetoothUART_SetRxAddress2(uint8 address) 
    {
        BluetoothUART_RXADDRESS2_REG = address;
    }

#endif  /* BluetoothUART_RX_ENABLED || BluetoothUART_HD_ENABLED*/


#if( (BluetoothUART_TX_ENABLED) || (BluetoothUART_HD_ENABLED) )
    /*******************************************************************************
    * Function Name: BluetoothUART_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the TX interrupt sources to be enabled, but does not enable the
    *  interrupt.
    *
    * Parameters:
    *  intSrc: Bit field containing the TX interrupt sources to enable
    *   BluetoothUART_TX_STS_COMPLETE        Interrupt on TX byte complete
    *   BluetoothUART_TX_STS_FIFO_EMPTY      Interrupt when TX FIFO is empty
    *   BluetoothUART_TX_STS_FIFO_FULL       Interrupt when TX FIFO is full
    *   BluetoothUART_TX_STS_FIFO_NOT_FULL   Interrupt when TX FIFO is not full
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void BluetoothUART_SetTxInterruptMode(uint8 intSrc) 
    {
        BluetoothUART_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: BluetoothUART_WriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data into the transmit buffer to be sent when the bus is
    *  available without checking the TX status register. You must check status
    *  separately.
    *
    * Parameters:
    *  txDataByte: data byte
    *
    * Return:
    * None.
    *
    * Global Variables:
    *  BluetoothUART_txBuffer - RAM buffer pointer for save data for transmission
    *  BluetoothUART_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  BluetoothUART_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  BluetoothUART_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void BluetoothUART_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(BluetoothUART_initVar != 0u)
        {
        #if (BluetoothUART_TX_INTERRUPT_ENABLED)

            /* Protect variables that could change on interrupt. */
            BluetoothUART_DisableTxInt();

            if( (BluetoothUART_txBufferRead == BluetoothUART_txBufferWrite) &&
                ((BluetoothUART_TXSTATUS_REG & BluetoothUART_TX_STS_FIFO_FULL) == 0u) )
            {
                /* Add directly to the FIFO. */
                BluetoothUART_TXDATA_REG = txDataByte;
            }
            else
            {
                if(BluetoothUART_txBufferWrite >= BluetoothUART_TX_BUFFER_SIZE)
                {
                    BluetoothUART_txBufferWrite = 0u;
                }

                BluetoothUART_txBuffer[BluetoothUART_txBufferWrite] = txDataByte;

                /* Add to the software buffer. */
                BluetoothUART_txBufferWrite++;
            }

            BluetoothUART_EnableTxInt();

        #else

            /* Add directly to the FIFO. */
            BluetoothUART_TXDATA_REG = txDataByte;

        #endif /*(BluetoothUART_TX_INTERRUPT_ENABLED) */
        }
    }


    /*******************************************************************************
    * Function Name: BluetoothUART_ReadTxStatus
    ********************************************************************************
    *
    * Summary:
    *  Reads the status register for the TX portion of the UART.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Contents of the status register
    *
    * Theory:
    *  This function reads the TX status register, which is cleared on read.
    *  It is up to the user to handle all bits in this return value accordingly,
    *  even if the bit was not enabled as an interrupt source the event happened
    *  and must be handled accordingly.
    *
    *******************************************************************************/
    uint8 BluetoothUART_ReadTxStatus(void) 
    {
        return(BluetoothUART_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: BluetoothUART_PutChar
    ********************************************************************************
    *
    * Summary:
    *  Puts a byte of data into the transmit buffer to be sent when the bus is
    *  available. This is a blocking API that waits until the TX buffer has room to
    *  hold the data.
    *
    * Parameters:
    *  txDataByte: Byte containing the data to transmit
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BluetoothUART_txBuffer - RAM buffer pointer for save data for transmission
    *  BluetoothUART_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  BluetoothUART_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  BluetoothUART_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void BluetoothUART_PutChar(uint8 txDataByte) 
    {
    #if (BluetoothUART_TX_INTERRUPT_ENABLED)
        /* The temporary output pointer is used since it takes two instructions
        *  to increment with a wrap, and we can't risk doing that with the real
        *  pointer and getting an interrupt in between instructions.
        */
        uint8 locTxBufferWrite;
        uint8 locTxBufferRead;

        do
        { /* Block if software buffer is full, so we don't overwrite. */

        #if ((BluetoothUART_TX_BUFFER_SIZE > BluetoothUART_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Disable TX interrupt to protect variables from modification */
            BluetoothUART_DisableTxInt();
        #endif /* (BluetoothUART_TX_BUFFER_SIZE > BluetoothUART_MAX_BYTE_VALUE) && (CY_PSOC3) */

            locTxBufferWrite = BluetoothUART_txBufferWrite;
            locTxBufferRead  = BluetoothUART_txBufferRead;

        #if ((BluetoothUART_TX_BUFFER_SIZE > BluetoothUART_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Enable interrupt to continue transmission */
            BluetoothUART_EnableTxInt();
        #endif /* (BluetoothUART_TX_BUFFER_SIZE > BluetoothUART_MAX_BYTE_VALUE) && (CY_PSOC3) */
        }
        while( (locTxBufferWrite < locTxBufferRead) ? (locTxBufferWrite == (locTxBufferRead - 1u)) :
                                ((locTxBufferWrite - locTxBufferRead) ==
                                (uint8)(BluetoothUART_TX_BUFFER_SIZE - 1u)) );

        if( (locTxBufferRead == locTxBufferWrite) &&
            ((BluetoothUART_TXSTATUS_REG & BluetoothUART_TX_STS_FIFO_FULL) == 0u) )
        {
            /* Add directly to the FIFO */
            BluetoothUART_TXDATA_REG = txDataByte;
        }
        else
        {
            if(locTxBufferWrite >= BluetoothUART_TX_BUFFER_SIZE)
            {
                locTxBufferWrite = 0u;
            }
            /* Add to the software buffer. */
            BluetoothUART_txBuffer[locTxBufferWrite] = txDataByte;
            locTxBufferWrite++;

            /* Finally, update the real output pointer */
        #if ((BluetoothUART_TX_BUFFER_SIZE > BluetoothUART_MAX_BYTE_VALUE) && (CY_PSOC3))
            BluetoothUART_DisableTxInt();
        #endif /* (BluetoothUART_TX_BUFFER_SIZE > BluetoothUART_MAX_BYTE_VALUE) && (CY_PSOC3) */

            BluetoothUART_txBufferWrite = locTxBufferWrite;

        #if ((BluetoothUART_TX_BUFFER_SIZE > BluetoothUART_MAX_BYTE_VALUE) && (CY_PSOC3))
            BluetoothUART_EnableTxInt();
        #endif /* (BluetoothUART_TX_BUFFER_SIZE > BluetoothUART_MAX_BYTE_VALUE) && (CY_PSOC3) */

            if(0u != (BluetoothUART_TXSTATUS_REG & BluetoothUART_TX_STS_FIFO_EMPTY))
            {
                /* Trigger TX interrupt to send software buffer */
                BluetoothUART_SetPendingTxInt();
            }
        }

    #else

        while((BluetoothUART_TXSTATUS_REG & BluetoothUART_TX_STS_FIFO_FULL) != 0u)
        {
            /* Wait for room in the FIFO */
        }

        /* Add directly to the FIFO */
        BluetoothUART_TXDATA_REG = txDataByte;

    #endif /* BluetoothUART_TX_INTERRUPT_ENABLED */
    }


    /*******************************************************************************
    * Function Name: BluetoothUART_PutString
    ********************************************************************************
    *
    * Summary:
    *  Sends a NULL terminated string to the TX buffer for transmission.
    *
    * Parameters:
    *  string[]: Pointer to the null terminated string array residing in RAM or ROM
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BluetoothUART_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void BluetoothUART_PutString(const char8 string[]) 
    {
        uint16 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(BluetoothUART_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent */
            while(string[bufIndex] != (char8) 0)
            {
                BluetoothUART_PutChar((uint8)string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: BluetoothUART_PutArray
    ********************************************************************************
    *
    * Summary:
    *  Places N bytes of data from a memory array into the TX buffer for
    *  transmission.
    *
    * Parameters:
    *  string[]: Address of the memory array residing in RAM or ROM.
    *  byteCount: Number of bytes to be transmitted. The type depends on TX Buffer
    *             Size parameter.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BluetoothUART_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void BluetoothUART_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(BluetoothUART_initVar != 0u)
        {
            while(bufIndex < byteCount)
            {
                BluetoothUART_PutChar(string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: BluetoothUART_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Writes a byte of data followed by a carriage return (0x0D) and line feed
    *  (0x0A) to the transmit buffer.
    *
    * Parameters:
    *  txDataByte: Data byte to transmit before the carriage return and line feed.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BluetoothUART_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void BluetoothUART_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function */
        if(BluetoothUART_initVar != 0u)
        {
            BluetoothUART_PutChar(txDataByte);
            BluetoothUART_PutChar(0x0Du);
            BluetoothUART_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: BluetoothUART_GetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of bytes in the TX buffer which are waiting to be 
    *  transmitted.
    *  * TX software buffer is disabled (TX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty TX FIFO, 1 for not full TX FIFO or 4 for full TX FIFO.
    *  * TX software buffer is enabled: returns the number of bytes in the TX 
    *    software buffer which are waiting to be transmitted. Bytes available in the
    *    TX FIFO do not count.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Number of bytes used in the TX buffer. Return value type depends on the TX 
    *  Buffer Size parameter.
    *
    * Global Variables:
    *  BluetoothUART_txBufferWrite - used to calculate left space.
    *  BluetoothUART_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 BluetoothUART_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (BluetoothUART_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        BluetoothUART_DisableTxInt();

        if(BluetoothUART_txBufferRead == BluetoothUART_txBufferWrite)
        {
            size = 0u;
        }
        else if(BluetoothUART_txBufferRead < BluetoothUART_txBufferWrite)
        {
            size = (BluetoothUART_txBufferWrite - BluetoothUART_txBufferRead);
        }
        else
        {
            size = (BluetoothUART_TX_BUFFER_SIZE - BluetoothUART_txBufferRead) +
                    BluetoothUART_txBufferWrite;
        }

        BluetoothUART_EnableTxInt();

    #else

        size = BluetoothUART_TXSTATUS_REG;

        /* Is the fifo is full. */
        if((size & BluetoothUART_TX_STS_FIFO_FULL) != 0u)
        {
            size = BluetoothUART_FIFO_LENGTH;
        }
        else if((size & BluetoothUART_TX_STS_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else
        {
            /* We only know there is data in the fifo. */
            size = 1u;
        }

    #endif /* (BluetoothUART_TX_INTERRUPT_ENABLED) */

    return(size);
    }


    /*******************************************************************************
    * Function Name: BluetoothUART_ClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears all data from the TX buffer and hardware TX FIFO.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BluetoothUART_txBufferWrite - cleared to zero.
    *  BluetoothUART_txBufferRead - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may have
    *  remained in the RAM.
    *
    * Side Effects:
    *  Data waiting in the transmit buffer is not sent; a byte that is currently
    *  transmitting finishes transmitting.
    *
    *******************************************************************************/
    void BluetoothUART_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Clear the HW FIFO */
        BluetoothUART_TXDATA_AUX_CTL_REG |= (uint8)  BluetoothUART_TX_FIFO_CLR;
        BluetoothUART_TXDATA_AUX_CTL_REG &= (uint8) ~BluetoothUART_TX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (BluetoothUART_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        BluetoothUART_DisableTxInt();

        BluetoothUART_txBufferRead = 0u;
        BluetoothUART_txBufferWrite = 0u;

        /* Enable Tx interrupt. */
        BluetoothUART_EnableTxInt();

    #endif /* (BluetoothUART_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: BluetoothUART_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Transmits a break signal on the bus.
    *
    * Parameters:
    *  uint8 retMode:  Send Break return mode. See the following table for options.
    *   BluetoothUART_SEND_BREAK - Initialize registers for break, send the Break
    *       signal and return immediately.
    *   BluetoothUART_WAIT_FOR_COMPLETE_REINIT - Wait until break transmission is
    *       complete, reinitialize registers to normal transmission mode then return
    *   BluetoothUART_REINIT - Reinitialize registers to normal transmission mode
    *       then return.
    *   BluetoothUART_SEND_WAIT_REINIT - Performs both options: 
    *      BluetoothUART_SEND_BREAK and BluetoothUART_WAIT_FOR_COMPLETE_REINIT.
    *      This option is recommended for most cases.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BluetoothUART_initVar - checked to identify that the component has been
    *     initialized.
    *  txPeriod - static variable, used for keeping TX period configuration.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  SendBreak function initializes registers to send 13-bit break signal. It is
    *  important to return the registers configuration to normal for continue 8-bit
    *  operation.
    *  There are 3 variants for this API usage:
    *  1) SendBreak(3) - function will send the Break signal and take care on the
    *     configuration returning. Function will block CPU until transmission
    *     complete.
    *  2) User may want to use blocking time if UART configured to the low speed
    *     operation
    *     Example for this case:
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     SendBreak(1);     - complete Break operation
    *  3) Same to 2) but user may want to initialize and use the interrupt to
    *     complete break operation.
    *     Example for this case:
    *     Initialize TX interrupt with "TX - On TX Complete" parameter
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     When interrupt appear with BluetoothUART_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *  The BluetoothUART_SendBreak() function initializes registers to send a
    *  break signal.
    *  Break signal length depends on the break signal bits configuration.
    *  The register configuration should be reinitialized before normal 8-bit
    *  communication can continue.
    *
    *******************************************************************************/
    void BluetoothUART_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(BluetoothUART_initVar != 0u)
        {
            /* Set the Counter to 13-bits and transmit a 00 byte */
            /* When that is done then reset the counter value back */
            uint8 tmpStat;

        #if(BluetoothUART_HD_ENABLED) /* Half Duplex mode*/

            if( (retMode == BluetoothUART_SEND_BREAK) ||
                (retMode == BluetoothUART_SEND_WAIT_REINIT ) )
            {
                /* CTRL_HD_SEND_BREAK - sends break bits in HD mode */
                BluetoothUART_WriteControlRegister(BluetoothUART_ReadControlRegister() |
                                                      BluetoothUART_CTRL_HD_SEND_BREAK);
                /* Send zeros */
                BluetoothUART_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = BluetoothUART_TXSTATUS_REG;
                }
                while((tmpStat & BluetoothUART_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == BluetoothUART_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == BluetoothUART_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = BluetoothUART_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & BluetoothUART_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == BluetoothUART_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == BluetoothUART_REINIT) ||
                (retMode == BluetoothUART_SEND_WAIT_REINIT) )
            {
                BluetoothUART_WriteControlRegister(BluetoothUART_ReadControlRegister() &
                                              (uint8)~BluetoothUART_CTRL_HD_SEND_BREAK);
            }

        #else /* BluetoothUART_HD_ENABLED Full Duplex mode */

            static uint8 txPeriod;

            if( (retMode == BluetoothUART_SEND_BREAK) ||
                (retMode == BluetoothUART_SEND_WAIT_REINIT) )
            {
                /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode */
                #if( (BluetoothUART_PARITY_TYPE != BluetoothUART__B_UART__NONE_REVB) || \
                                    (BluetoothUART_PARITY_TYPE_SW != 0u) )
                    BluetoothUART_WriteControlRegister(BluetoothUART_ReadControlRegister() |
                                                          BluetoothUART_CTRL_HD_SEND_BREAK);
                #endif /* End BluetoothUART_PARITY_TYPE != BluetoothUART__B_UART__NONE_REVB  */

                #if(BluetoothUART_TXCLKGEN_DP)
                    txPeriod = BluetoothUART_TXBITCLKTX_COMPLETE_REG;
                    BluetoothUART_TXBITCLKTX_COMPLETE_REG = BluetoothUART_TXBITCTR_BREAKBITS;
                #else
                    txPeriod = BluetoothUART_TXBITCTR_PERIOD_REG;
                    BluetoothUART_TXBITCTR_PERIOD_REG = BluetoothUART_TXBITCTR_BREAKBITS8X;
                #endif /* End BluetoothUART_TXCLKGEN_DP */

                /* Send zeros */
                BluetoothUART_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = BluetoothUART_TXSTATUS_REG;
                }
                while((tmpStat & BluetoothUART_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == BluetoothUART_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == BluetoothUART_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = BluetoothUART_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & BluetoothUART_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == BluetoothUART_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == BluetoothUART_REINIT) ||
                (retMode == BluetoothUART_SEND_WAIT_REINIT) )
            {

            #if(BluetoothUART_TXCLKGEN_DP)
                BluetoothUART_TXBITCLKTX_COMPLETE_REG = txPeriod;
            #else
                BluetoothUART_TXBITCTR_PERIOD_REG = txPeriod;
            #endif /* End BluetoothUART_TXCLKGEN_DP */

            #if( (BluetoothUART_PARITY_TYPE != BluetoothUART__B_UART__NONE_REVB) || \
                 (BluetoothUART_PARITY_TYPE_SW != 0u) )
                BluetoothUART_WriteControlRegister(BluetoothUART_ReadControlRegister() &
                                                      (uint8) ~BluetoothUART_CTRL_HD_SEND_BREAK);
            #endif /* End BluetoothUART_PARITY_TYPE != NONE */
            }
        #endif    /* End BluetoothUART_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: BluetoothUART_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the transmitter to signal the next bytes is address or data.
    *
    * Parameters:
    *  addressMode: 
    *       BluetoothUART_SET_SPACE - Configure the transmitter to send the next
    *                                    byte as a data.
    *       BluetoothUART_SET_MARK  - Configure the transmitter to send the next
    *                                    byte as an address.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function sets and clears BluetoothUART_CTRL_MARK bit in the Control
    *  register.
    *
    *******************************************************************************/
    void BluetoothUART_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable */
        if(addressMode != 0u)
        {
        #if( BluetoothUART_CONTROL_REG_REMOVED == 0u )
            BluetoothUART_WriteControlRegister(BluetoothUART_ReadControlRegister() |
                                                  BluetoothUART_CTRL_MARK);
        #endif /* End BluetoothUART_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
        #if( BluetoothUART_CONTROL_REG_REMOVED == 0u )
            BluetoothUART_WriteControlRegister(BluetoothUART_ReadControlRegister() &
                                                  (uint8) ~BluetoothUART_CTRL_MARK);
        #endif /* End BluetoothUART_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* EndBluetoothUART_TX_ENABLED */

#if(BluetoothUART_HD_ENABLED)


    /*******************************************************************************
    * Function Name: BluetoothUART_LoadRxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the receiver configuration in half duplex mode. After calling this
    *  function, the UART is ready to receive data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the transmitter
    *  configuration.
    *
    *******************************************************************************/
    void BluetoothUART_LoadRxConfig(void) 
    {
        BluetoothUART_WriteControlRegister(BluetoothUART_ReadControlRegister() &
                                                (uint8)~BluetoothUART_CTRL_HD_SEND);
        BluetoothUART_RXBITCTR_PERIOD_REG = BluetoothUART_HD_RXBITCTR_INIT;

    #if (BluetoothUART_RX_INTERRUPT_ENABLED)
        /* Enable RX interrupt after set RX configuration */
        BluetoothUART_SetRxInterruptMode(BluetoothUART_INIT_RX_INTERRUPTS_MASK);
    #endif /* (BluetoothUART_RX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: BluetoothUART_LoadTxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the transmitter configuration in half duplex mode. After calling this
    *  function, the UART is ready to transmit data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the receiver configuration.
    *
    *******************************************************************************/
    void BluetoothUART_LoadTxConfig(void) 
    {
    #if (BluetoothUART_RX_INTERRUPT_ENABLED)
        /* Disable RX interrupts before set TX configuration */
        BluetoothUART_SetRxInterruptMode(0u);
    #endif /* (BluetoothUART_RX_INTERRUPT_ENABLED) */

        BluetoothUART_WriteControlRegister(BluetoothUART_ReadControlRegister() | BluetoothUART_CTRL_HD_SEND);
        BluetoothUART_RXBITCTR_PERIOD_REG = BluetoothUART_HD_TXBITCTR_INIT;
    }

#endif  /* BluetoothUART_HD_ENABLED */


/* [] END OF FILE */
