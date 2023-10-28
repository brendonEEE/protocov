/*******************************************************************************
* File Name: VehicleCAN_INT.c
* Version 3.0
*
* Description:
*  This file contains Interrupt Service Routine (ISR) for CAN Component.
*  The Interrupt handlers functions are generated accordingly to the PSoC
*  Creator Customizer inputs.
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

#include "VehicleCAN.h"
#include "cyapicallbacks.h"

/* `#START CAN_INT_C_CODE_DEFINITION` */

/* `#END` */

#if (VehicleCAN_ARB_LOST)
    /*******************************************************************************
    * FUNCTION NAME:   VehicleCAN_ArbLostIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Arbitration Lost Interrupt. Clears
    *  Arbitration Lost interrupt flag. Only generated if Arbitration Lost
    *  Interrupt enable in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void VehicleCAN_ArbLostIsr(void) 
    {
        /* Clear Arbitration Lost flag */
        VehicleCAN_INT_SR_REG.byte[0u] = VehicleCAN_ARBITRATION_LOST_MASK;

        /* `#START ARBITRATION_LOST_ISR` */

        /* `#END` */

        #ifdef VehicleCAN_ARB_LOST_ISR_CALLBACK
            VehicleCAN_ArbLostIsr_Callback();
        #endif /* VehicleCAN_ARB_LOST_ISR_CALLBACK */
    }
#endif /* VehicleCAN_ARB_LOST */


#if (VehicleCAN_OVERLOAD)
    /*******************************************************************************
    * FUNCTION NAME:   VehicleCAN_OvrLdErrorIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Overload Error Interrupt. Clears Overload
    *  Error interrupt flag. Only generated if Overload Error Interrupt enable
    *  in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void VehicleCAN_OvrLdErrorIsr(void) 
    {
        /* Clear Overload Error flag */
        VehicleCAN_INT_SR_REG.byte[0u] = VehicleCAN_OVERLOAD_ERROR_MASK;

        /* `#START OVER_LOAD_ERROR_ISR` */

        /* `#END` */

        #ifdef VehicleCAN_OVR_LD_ERROR_ISR_CALLBACK
            VehicleCAN_OvrLdErrorIsr_Callback();
        #endif /* VehicleCAN_OVR_LD_ERROR_ISR_CALLBACK */
    }
#endif /* VehicleCAN_OVERLOAD */


#if (VehicleCAN_BIT_ERR)
    /*******************************************************************************
    * FUNCTION NAME:   VehicleCAN_BitErrorIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Bit Error Interrupt. Clears Bit Error
    *  interrupt flag. Only generated if Bit Error Interrupt enable in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void VehicleCAN_BitErrorIsr(void) 
    {
        /* Clear Bit Error flag */
        VehicleCAN_INT_SR_REG.byte[0u] = VehicleCAN_BIT_ERROR_MASK;

        /* `#START BIT_ERROR_ISR` */

        /* `#END` */

        #ifdef VehicleCAN_BIT_ERROR_ISR_CALLBACK
            VehicleCAN_BitErrorIsr_Callback();
        #endif /* VehicleCAN_BIT_ERROR_ISR_CALLBACK */
    }
#endif /* VehicleCAN_BIT_ERR */


#if (VehicleCAN_STUFF_ERR)
    /*******************************************************************************
    * FUNCTION NAME:   VehicleCAN_BitStuffErrorIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Bit Stuff Error Interrupt. Clears Bit Stuff
    *  Error interrupt flag. Only generated if Bit Stuff Error Interrupt enable
    *  in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void VehicleCAN_BitStuffErrorIsr(void) 
    {
        /* Clear Stuff Error flag */
        VehicleCAN_INT_SR_REG.byte[0u] = VehicleCAN_STUFF_ERROR_MASK;

        /* `#START BIT_STUFF_ERROR_ISR` */

        /* `#END` */

        #ifdef VehicleCAN_BIT_STUFF_ERROR_ISR_CALLBACK
            VehicleCAN_BitStuffErrorIsr_Callback();
        #endif /* VehicleCAN_BIT_STUFF_ERROR_ISR_CALLBACK */
    }
#endif /* VehicleCAN_STUFF_ERR */


#if (VehicleCAN_ACK_ERR)
    /*******************************************************************************
    * FUNCTION NAME:   VehicleCAN_AckErrorIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Acknowledge Error Interrupt. Clears
    *  Acknowledge Error interrupt flag. Only generated if Acknowledge Error
    *  Interrupt enable in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void VehicleCAN_AckErrorIsr(void) 
    {
        /* Clear Acknoledge Error flag */
        VehicleCAN_INT_SR_REG.byte[0u] = VehicleCAN_ACK_ERROR_MASK;

        /* `#START ACKNOWLEDGE_ERROR_ISR` */

        /* `#END` */

        #ifdef VehicleCAN_ACK_ERROR_ISR_CALLBACK
            VehicleCAN_AckErrorIsr_Callback();
        #endif /* VehicleCAN_ACK_ERROR_ISR_CALLBACK */
    }
#endif /* VehicleCAN_ACK_ERR */


#if (VehicleCAN_FORM_ERR)
    /*******************************************************************************
    * FUNCTION NAME:   VehicleCAN_MsgErrorIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Form Error Interrupt. Clears Form Error
    *  interrupt flag. Only generated if Form Error Interrupt enable in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void VehicleCAN_MsgErrorIsr(void) 
    {
        /* Clear Form Error flag */
        VehicleCAN_INT_SR_REG.byte[0u] = VehicleCAN_FORM_ERROR_MASK;

        /* `#START MESSAGE_ERROR_ISR` */

        /* `#END` */

        #ifdef VehicleCAN_MSG_ERROR_ISR_CALLBACK
            VehicleCAN_MsgErrorIsr_Callback();
        #endif /* VehicleCAN_MSG_ERROR_ISR_CALLBACK */
    }
#endif /* VehicleCAN_FORM_ERR */


#if (VehicleCAN_CRC_ERR)
    /*******************************************************************************
    * FUNCTION NAME:   VehicleCAN_CrcErrorIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to CRC Error Interrupt. Clears CRC Error
    *  interrupt flag. Only generated if CRC Error Interrupt enable in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void VehicleCAN_CrcErrorIsr(void) 
    {
        /* Clear CRC Error flag */
        VehicleCAN_INT_SR_REG.byte[1u] = VehicleCAN_CRC_ERROR_MASK;

        /* `#START CRC_ERROR_ISR` */

        /* `#END` */

        #ifdef VehicleCAN_CRC_ERROR_ISR_CALLBACK
            VehicleCAN_CrcErrorIsr_Callback();
        #endif /* VehicleCAN_CRC_ERROR_ISR_CALLBACK */
    }
#endif /* VehicleCAN_CRC_ERR */


#if (VehicleCAN_BUS_OFF)
    /*******************************************************************************
    * FUNCTION NAME:   VehicleCAN_BusOffIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Bus Off Interrupt. Places CAN Component
    *  to Stop mode. Only generated if Bus Off Interrupt enable in Customizer.
    *  Recommended setting to enable this interrupt.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Stops CAN component operation.
    *
    *******************************************************************************/
    void VehicleCAN_BusOffIsr(void) 
    {
        /* Clear Bus Off flag */
        VehicleCAN_INT_SR_REG.byte[1u] = VehicleCAN_BUS_OFF_MASK;
        (void) VehicleCAN_GlobalIntDisable();

        /* `#START BUS_OFF_ISR` */

        /* `#END` */

        #ifdef VehicleCAN_BUS_OFF_ISR_CALLBACK
            VehicleCAN_BusOffIsr_Callback();
        #endif /* VehicleCAN_BUS_OFF_ISR_CALLBACK */

        (void) VehicleCAN_Stop();
    }
#endif /* VehicleCAN_BUS_OFF */


#if (VehicleCAN_RX_MSG_LOST)
    /*******************************************************************************
    * FUNCTION NAME:   VehicleCAN_MsgLostIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Message Lost Interrupt. Clears Message Lost
    *  interrupt flag. Only generated if Message Lost Interrupt enable in Customizer
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void VehicleCAN_MsgLostIsr(void) 
    {
        /* Clear Receive Message Lost flag */
        VehicleCAN_INT_SR_REG.byte[1u] = VehicleCAN_RX_MSG_LOST_MASK;

        /* `#START MESSAGE_LOST_ISR` */

        /* `#END` */

        #ifdef VehicleCAN_MSG_LOST_ISR_CALLBACK
            VehicleCAN_MsgLostIsr_Callback();
        #endif /* VehicleCAN_MSG_LOST_ISR_CALLBACK */
    }
#endif /* VehicleCAN_RX_MSG_LOST */


#if (VehicleCAN_TX_MESSAGE)
    /*******************************************************************************
    * FUNCTION NAME:   VehicleCAN_MsgTXIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Transmit Message Interrupt. Clears Transmit
    *  Message interrupt flag. Only generated if Transmit Message Interrupt enable
    *  in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void VehicleCAN_MsgTXIsr(void) 
    {
        /* Clear Transmit Message flag */
        VehicleCAN_INT_SR_REG.byte[1u] = VehicleCAN_TX_MESSAGE_MASK;

        /* `#START MESSAGE_TRANSMITTED_ISR` */

        /* `#END` */

        #ifdef VehicleCAN_MSG_TX_ISR_CALLBACK
            VehicleCAN_MsgTXIsr_Callback();
        #endif /* VehicleCAN_MSG_TX_ISR_CALLBACK */
    }
#endif /* VehicleCAN_TX_MESSAGE */


#if (VehicleCAN_RX_MESSAGE)
    /*******************************************************************************
    * FUNCTION NAME:   VehicleCAN_MsgRXIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Receive Message Interrupt. Clears Receive
    *  Message interrupt flag and call appropriate handlers for Basic and Full
    *  interrupt based mailboxes. Only generated if Receive Message Interrupt
    *  enable in Customizer. Recommended setting to enable this interrupt.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void VehicleCAN_MsgRXIsr(void) 
    {
        uint8 mailboxNumber;
        uint16 shift = 0x01u;

        /* Clear Receive Message flag */
        VehicleCAN_INT_SR_REG.byte[1u] = VehicleCAN_RX_MESSAGE_MASK;

        /* `#START MESSAGE_RECEIVE_ISR` */

        /* `#END` */

        #ifdef VehicleCAN_MSG_RX_ISR_CALLBACK
            VehicleCAN_MsgRXIsr_Callback();
        #endif /* VehicleCAN_MSG_RX_ISR_CALLBACK */

        for (mailboxNumber = 0u; mailboxNumber < VehicleCAN_NUMBER_OF_RX_MAILBOXES; mailboxNumber++)
        {
            if ((CY_GET_REG16((reg16 *) &VehicleCAN_BUF_SR_REG.byte[0u]) & shift) != 0u)
            {
                if ((VehicleCAN_RX[mailboxNumber].rxcmd.byte[0u] & VehicleCAN_RX_INT_ENABLE_MASK) != 0u)
                {
                    if ((VehicleCAN_RX_MAILBOX_TYPE & shift) != 0u)
                    {
                        /* RX Full mailboxes handler */
                    }
                    else
                    {
                        /* RX Basic mailbox handler */
                        VehicleCAN_ReceiveMsg(mailboxNumber);
                    }
                }
            }
            shift <<= 1u;
        }
    }
#endif /* VehicleCAN_RX_MESSAGE */


/*******************************************************************************
* Function Name: VehicleCAN_ISR
********************************************************************************
*
* Summary:
*  This ISR is executed when CAN Core generates and interrupt on one of events:
*  Arb_lost, Overload, Bit_err, Stuff_err, Ack_err, Form_err, Crc_err,
*  Buss_off, Rx_msg_lost, Tx_msg or Rx_msg. The interrupt sources depends
*  on the Customizer inputs.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
CY_ISR(VehicleCAN_ISR)
{
    #ifdef VehicleCAN_ISR_INTERRUPT_CALLBACK
        VehicleCAN_ISR_InterruptCallback();
    #endif /* VehicleCAN_ISR_INTERRUPT_CALLBACK */
    
    /* Place your Interrupt code here. */
    /* `#START CAN_ISR` */

    /* `#END` */
    
    /* Arbitration */
    #if (VehicleCAN_ARB_LOST && (VehicleCAN_ARB_LOST_USE_HELPER || \
        (!VehicleCAN_ADVANCED_INTERRUPT_CFG)))
        if ((VehicleCAN_INT_SR_REG.byte[0u] & VehicleCAN_ARBITRATION_LOST_MASK) != 0u)
        {
            VehicleCAN_ArbLostIsr();
        }
    #endif /* VehicleCAN_ARB_LOST && VehicleCAN_ARB_LOST_USE_HELPER */

    /* Overload Error */
    #if (VehicleCAN_OVERLOAD && (VehicleCAN_OVERLOAD_USE_HELPER || \
        (!VehicleCAN_ADVANCED_INTERRUPT_CFG)))
        if ((VehicleCAN_INT_SR_REG.byte[0u] & VehicleCAN_OVERLOAD_ERROR_MASK) != 0u)
        {
            VehicleCAN_OvrLdErrorIsr();
        }
    #endif /* VehicleCAN_OVERLOAD && VehicleCAN_OVERLOAD_USE_HELPER */

    /* Bit Error */
    #if (VehicleCAN_BIT_ERR && (VehicleCAN_BIT_ERR_USE_HELPER || \
        (!VehicleCAN_ADVANCED_INTERRUPT_CFG)))
        if ((VehicleCAN_INT_SR_REG.byte[0u] & VehicleCAN_BIT_ERROR_MASK) != 0u)
        {
            VehicleCAN_BitErrorIsr();
        }
    #endif /* VehicleCAN_BIT_ERR && VehicleCAN_BIT_ERR_USE_HELPER */

    /* Bit Staff Error */
    #if (VehicleCAN_STUFF_ERR && (VehicleCAN_STUFF_ERR_USE_HELPER || \
        (!VehicleCAN_ADVANCED_INTERRUPT_CFG)))
        if ((VehicleCAN_INT_SR_REG.byte[0u] & VehicleCAN_STUFF_ERROR_MASK) != 0u)
        {
            VehicleCAN_BitStuffErrorIsr();
        }
    #endif /* VehicleCAN_STUFF_ERR && VehicleCAN_STUFF_ERR_USE_HELPER */

    /* ACK Error */
    #if (VehicleCAN_ACK_ERR && (VehicleCAN_ACK_ERR_USE_HELPER || \
        (!VehicleCAN_ADVANCED_INTERRUPT_CFG)))
        if ((VehicleCAN_INT_SR_REG.byte[0u] & VehicleCAN_ACK_ERROR_MASK) != 0u)
        {
            VehicleCAN_AckErrorIsr();
        }
    #endif /* VehicleCAN_ACK_ERR && VehicleCAN_ACK_ERR_USE_HELPER */

    /* Form(msg) Error */
    #if (VehicleCAN_FORM_ERR && (VehicleCAN_FORM_ERR_USE_HELPER || \
        (!VehicleCAN_ADVANCED_INTERRUPT_CFG)))
        if ((VehicleCAN_INT_SR_REG.byte[0u] & VehicleCAN_FORM_ERROR_MASK) != 0u)
        {
            VehicleCAN_MsgErrorIsr();
        }
    #endif /* VehicleCAN_FORM_ERR && VehicleCAN_FORM_ERR_USE_HELPER */

    /* CRC Error */
    #if (VehicleCAN_CRC_ERR && (VehicleCAN_CRC_ERR_USE_HELPER || \
        (!VehicleCAN_ADVANCED_INTERRUPT_CFG)))
        if ((VehicleCAN_INT_SR_REG.byte[1u] & VehicleCAN_CRC_ERROR_MASK) != 0u)
        {
            VehicleCAN_CrcErrorIsr();
        }
    #endif /* VehicleCAN_CRC_ERR && VehicleCAN_CRC_ERR_USE_HELPER */

    /* Bus Off state */
    #if (VehicleCAN_BUS_OFF && (VehicleCAN_BUS_OFF_USE_HELPER || \
        (!VehicleCAN_ADVANCED_INTERRUPT_CFG)))
        if ((VehicleCAN_INT_SR_REG.byte[1u] & VehicleCAN_BUS_OFF_MASK) != 0u)
        {
            VehicleCAN_BusOffIsr();
        }
    #endif /* VehicleCAN_BUS_OFF && VehicleCAN_BUS_OFF_USE_HELPER */

    /* Message Lost */
    #if (VehicleCAN_RX_MSG_LOST && (VehicleCAN_RX_MSG_LOST_USE_HELPER || \
        (!VehicleCAN_ADVANCED_INTERRUPT_CFG)))
        if ((VehicleCAN_INT_SR_REG.byte[1u] & VehicleCAN_RX_MSG_LOST_MASK) != 0u)
        {
            VehicleCAN_MsgLostIsr();
        }
    #endif /* VehicleCAN_RX_MSG_LOST && VehicleCAN_RX_MSG_LOST_USE_HELPER */

    /* TX Message Send */
    #if (VehicleCAN_TX_MESSAGE && (VehicleCAN_TX_MESSAGE_USE_HELPER || \
        (!VehicleCAN_ADVANCED_INTERRUPT_CFG)))
        if ((VehicleCAN_INT_SR_REG.byte[1u] & VehicleCAN_TX_MESSAGE_MASK) != 0u)
        {
            VehicleCAN_MsgTXIsr();
        }
    #endif /* VehicleCAN_TX_MESSAGE && VehicleCAN_TX_MESSAGE_USE_HELPER */

    /* RX Message Available */
    #if (VehicleCAN_RX_MESSAGE && (VehicleCAN_RX_MESSAGE_USE_HELPER || \
        (!VehicleCAN_ADVANCED_INTERRUPT_CFG)))
        if ((VehicleCAN_INT_SR_REG.byte[1u] & VehicleCAN_RX_MESSAGE_MASK) != 0u)
        {
            VehicleCAN_MsgRXIsr();
        }
    #endif /* VehicleCAN_RX_MESSAGE && VehicleCAN_RX_MESSAGE_USE_HELPER */
}


/* [] END OF FILE */
