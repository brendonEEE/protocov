/***************************************************************************//**
* \file ProtocovUSB_drv.c
* \version 3.20
*
* \brief
*  This file contains the Endpoint 0 Driver for the USBFS Component.  
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ProtocovUSB_pvt.h"
#include "cyapicallbacks.h"


/***************************************
* Global data allocation
***************************************/

volatile T_ProtocovUSB_EP_CTL_BLOCK ProtocovUSB_EP[ProtocovUSB_MAX_EP];

/** Contains the current configuration number, which is set by the host using a 
 * SET_CONFIGURATION request. This variable is initialized to zero in 
 * USBFS_InitComponent() API and can be read by the USBFS_GetConfiguration() 
 * API.*/
volatile uint8 ProtocovUSB_configuration;

/** Contains the current interface number.*/
volatile uint8 ProtocovUSB_interfaceNumber;

/** This variable is set to one after SET_CONFIGURATION and SET_INTERFACE 
 *requests. It can be read by the USBFS_IsConfigurationChanged() API */
volatile uint8 ProtocovUSB_configurationChanged;

/** Contains the current device address.*/
volatile uint8 ProtocovUSB_deviceAddress;

/** This is a two-bit variable that contains power status in the bit 0 
 * (DEVICE_STATUS_BUS_POWERED or DEVICE_STATUS_SELF_POWERED) and remote wakeup 
 * status (DEVICE_STATUS_REMOTE_WAKEUP) in the bit 1. This variable is 
 * initialized to zero in USBFS_InitComponent() API, configured by the 
 * USBFS_SetPowerStatus() API. The remote wakeup status cannot be set using the 
 * API SetPowerStatus(). */
volatile uint8 ProtocovUSB_deviceStatus;

volatile uint8 ProtocovUSB_interfaceSetting[ProtocovUSB_MAX_INTERFACES_NUMBER];
volatile uint8 ProtocovUSB_interfaceSetting_last[ProtocovUSB_MAX_INTERFACES_NUMBER];
volatile uint8 ProtocovUSB_interfaceStatus[ProtocovUSB_MAX_INTERFACES_NUMBER];

/** Contains the started device number. This variable is set by the 
 * USBFS_Start() or USBFS_InitComponent() APIs.*/
volatile uint8 ProtocovUSB_device;

/** Initialized class array for each interface. It is used for handling Class 
 * specific requests depend on interface class. Different classes in multiple 
 * alternate settings are not supported.*/
const uint8 CYCODE *ProtocovUSB_interfaceClass;


/***************************************
* Local data allocation
***************************************/

volatile uint8  ProtocovUSB_ep0Toggle;
volatile uint8  ProtocovUSB_lastPacketSize;

/** This variable is used by the communication functions to handle the current 
* transfer state.
* Initialized to TRANS_STATE_IDLE in the USBFS_InitComponent() API and after a 
* complete transfer in the status stage.
* Changed to the TRANS_STATE_CONTROL_READ or TRANS_STATE_CONTROL_WRITE in setup 
* transaction depending on the request type.
*/
volatile uint8  ProtocovUSB_transferState;
volatile T_ProtocovUSB_TD ProtocovUSB_currentTD;
volatile uint8  ProtocovUSB_ep0Mode;
volatile uint8  ProtocovUSB_ep0Count;
volatile uint16 ProtocovUSB_transferByteCount;


/*******************************************************************************
* Function Name: ProtocovUSB_ep_0_Interrupt
****************************************************************************//**
*
*  This Interrupt Service Routine handles Endpoint 0 (Control Pipe) traffic.
*  It dispatches setup requests and handles the data and status stages.
*
*
*******************************************************************************/
CY_ISR(ProtocovUSB_EP_0_ISR)
{
    uint8 tempReg;
    uint8 modifyReg;

#ifdef ProtocovUSB_EP_0_ISR_ENTRY_CALLBACK
    ProtocovUSB_EP_0_ISR_EntryCallback();
#endif /* (ProtocovUSB_EP_0_ISR_ENTRY_CALLBACK) */
    
    tempReg = ProtocovUSB_EP0_CR_REG;
    if ((tempReg & ProtocovUSB_MODE_ACKD) != 0u)
    {
        modifyReg = 1u;
        if ((tempReg & ProtocovUSB_MODE_SETUP_RCVD) != 0u)
        {
            if ((tempReg & ProtocovUSB_MODE_MASK) != ProtocovUSB_MODE_NAK_IN_OUT)
            {
                /* Mode not equal to NAK_IN_OUT: invalid setup */
                modifyReg = 0u;
            }
            else
            {
                ProtocovUSB_HandleSetup();
                
                if ((ProtocovUSB_ep0Mode & ProtocovUSB_MODE_SETUP_RCVD) != 0u)
                {
                    /* SETUP bit set: exit without mode modificaiton */
                    modifyReg = 0u;
                }
            }
        }
        else if ((tempReg & ProtocovUSB_MODE_IN_RCVD) != 0u)
        {
            ProtocovUSB_HandleIN();
        }
        else if ((tempReg & ProtocovUSB_MODE_OUT_RCVD) != 0u)
        {
            ProtocovUSB_HandleOUT();
        }
        else
        {
            modifyReg = 0u;
        }
        
        /* Modify the EP0_CR register */
        if (modifyReg != 0u)
        {
            
            tempReg = ProtocovUSB_EP0_CR_REG;
            
            /* Make sure that SETUP bit is cleared before modification */
            if ((tempReg & ProtocovUSB_MODE_SETUP_RCVD) == 0u)
            {
                /* Update count register */
                tempReg = (uint8) ProtocovUSB_ep0Toggle | ProtocovUSB_ep0Count;
                ProtocovUSB_EP0_CNT_REG = tempReg;
               
                /* Make sure that previous write operaiton was successful */
                if (tempReg == ProtocovUSB_EP0_CNT_REG)
                {
                    /* Repeat until next successful write operation */
                    do
                    {
                        /* Init temporary variable */
                        modifyReg = ProtocovUSB_ep0Mode;
                        
                        /* Unlock register */
                        tempReg = (uint8) (ProtocovUSB_EP0_CR_REG & ProtocovUSB_MODE_SETUP_RCVD);
                        
                        /* Check if SETUP bit is not set */
                        if (0u == tempReg)
                        {
                            /* Set the Mode Register  */
                            ProtocovUSB_EP0_CR_REG = ProtocovUSB_ep0Mode;
                            
                            /* Writing check */
                            modifyReg = ProtocovUSB_EP0_CR_REG & ProtocovUSB_MODE_MASK;
                        }
                    }
                    while (modifyReg != ProtocovUSB_ep0Mode);
                }
            }
        }
    }

    ProtocovUSB_ClearSieInterruptSource(ProtocovUSB_INTR_SIE_EP0_INTR);
	
#ifdef ProtocovUSB_EP_0_ISR_EXIT_CALLBACK
    ProtocovUSB_EP_0_ISR_ExitCallback();
#endif /* (ProtocovUSB_EP_0_ISR_EXIT_CALLBACK) */
}


/*******************************************************************************
* Function Name: ProtocovUSB_HandleSetup
****************************************************************************//**
*
*  This Routine dispatches requests for the four USB request types
*
*
* \reentrant
*  No.
*
*******************************************************************************/
void ProtocovUSB_HandleSetup(void) 
{
    uint8 requestHandled;
    
    /* Clear register lock by SIE (read register) and clear setup bit 
    * (write any value in register).
    */
    requestHandled = (uint8) ProtocovUSB_EP0_CR_REG;
    ProtocovUSB_EP0_CR_REG = (uint8) requestHandled;
    requestHandled = (uint8) ProtocovUSB_EP0_CR_REG;

    if ((requestHandled & ProtocovUSB_MODE_SETUP_RCVD) != 0u)
    {
        /* SETUP bit is set: exit without mode modification. */
        ProtocovUSB_ep0Mode = requestHandled;
    }
    else
    {
        /* In case the previous transfer did not complete, close it out */
        ProtocovUSB_UpdateStatusBlock(ProtocovUSB_XFER_PREMATURE);

        /* Check request type. */
        switch (ProtocovUSB_bmRequestTypeReg & ProtocovUSB_RQST_TYPE_MASK)
        {
            case ProtocovUSB_RQST_TYPE_STD:
                requestHandled = ProtocovUSB_HandleStandardRqst();
                break;
                
            case ProtocovUSB_RQST_TYPE_CLS:
                requestHandled = ProtocovUSB_DispatchClassRqst();
                break;
                
            case ProtocovUSB_RQST_TYPE_VND:
                requestHandled = ProtocovUSB_HandleVendorRqst();
                break;
                
            default:
                requestHandled = ProtocovUSB_FALSE;
                break;
        }
        
        /* If request is not recognized. Stall endpoint 0 IN and OUT. */
        if (requestHandled == ProtocovUSB_FALSE)
        {
            ProtocovUSB_ep0Mode = ProtocovUSB_MODE_STALL_IN_OUT;
        }
    }
}


/*******************************************************************************
* Function Name: ProtocovUSB_HandleIN
****************************************************************************//**
*
*  This routine handles EP0 IN transfers.
*
*
* \reentrant
*  No.
*
*******************************************************************************/
void ProtocovUSB_HandleIN(void) 
{
    switch (ProtocovUSB_transferState)
    {
        case ProtocovUSB_TRANS_STATE_IDLE:
            break;
        
        case ProtocovUSB_TRANS_STATE_CONTROL_READ:
            ProtocovUSB_ControlReadDataStage();
            break;
            
        case ProtocovUSB_TRANS_STATE_CONTROL_WRITE:
            ProtocovUSB_ControlWriteStatusStage();
            break;
            
        case ProtocovUSB_TRANS_STATE_NO_DATA_CONTROL:
            ProtocovUSB_NoDataControlStatusStage();
            break;
            
        default:    /* there are no more states */
            break;
    }
}


/*******************************************************************************
* Function Name: ProtocovUSB_HandleOUT
****************************************************************************//**
*
*  This routine handles EP0 OUT transfers.
*
*
* \reentrant
*  No.
*
*******************************************************************************/
void ProtocovUSB_HandleOUT(void) 
{
    switch (ProtocovUSB_transferState)
    {
        case ProtocovUSB_TRANS_STATE_IDLE:
            break;
        
        case ProtocovUSB_TRANS_STATE_CONTROL_READ:
            ProtocovUSB_ControlReadStatusStage();
            break;
            
        case ProtocovUSB_TRANS_STATE_CONTROL_WRITE:
            ProtocovUSB_ControlWriteDataStage();
            break;
            
        case ProtocovUSB_TRANS_STATE_NO_DATA_CONTROL:
            /* Update the completion block */
            ProtocovUSB_UpdateStatusBlock(ProtocovUSB_XFER_ERROR);
            
            /* We expect no more data, so stall INs and OUTs */
            ProtocovUSB_ep0Mode = ProtocovUSB_MODE_STALL_IN_OUT;
            break;
            
        default:    
            /* There are no more states */
            break;
    }
}


/*******************************************************************************
* Function Name: ProtocovUSB_LoadEP0
****************************************************************************//**
*
*  This routine loads the EP0 data registers for OUT transfers. It uses the
*  currentTD (previously initialized by the _InitControlWrite function and
*  updated for each OUT transfer, and the bLastPacketSize) to determine how
*  many uint8s to transfer on the current OUT.
*
*  If the number of uint8s remaining is zero and the last transfer was full,
*  we need to send a zero length packet.  Otherwise we send the minimum
*  of the control endpoint size (8) or remaining number of uint8s for the
*  transaction.
*
*
* \globalvars
*  ProtocovUSB_transferByteCount - Update the transfer byte count from the
*     last transaction.
*  ProtocovUSB_ep0Count - counts the data loaded to the SIE memory in
*     current packet.
*  ProtocovUSB_lastPacketSize - remembers the USBFS_ep0Count value for the
*     next packet.
*  ProtocovUSB_transferByteCount - sum of the previous bytes transferred
*     on previous packets(sum of USBFS_lastPacketSize)
*  ProtocovUSB_ep0Toggle - inverted
*  ProtocovUSB_ep0Mode  - prepare for mode register content.
*  ProtocovUSB_transferState - set to TRANS_STATE_CONTROL_READ
*
* \reentrant
*  No.
*
*******************************************************************************/
void ProtocovUSB_LoadEP0(void) 
{
    uint8 ep0Count = 0u;

    /* Update the transfer byte count from the last transaction */
    ProtocovUSB_transferByteCount += ProtocovUSB_lastPacketSize;

    /* Now load the next transaction */
    while ((ProtocovUSB_currentTD.count > 0u) && (ep0Count < 8u))
    {
        ProtocovUSB_EP0_DR_BASE.epData[ep0Count] = (uint8) *ProtocovUSB_currentTD.pData;
        ProtocovUSB_currentTD.pData = &ProtocovUSB_currentTD.pData[1u];
        ep0Count++;
        ProtocovUSB_currentTD.count--;
    }

    /* Support zero-length packet */
    if ((ProtocovUSB_lastPacketSize == 8u) || (ep0Count > 0u))
    {
        /* Update the data toggle */
        ProtocovUSB_ep0Toggle ^= ProtocovUSB_EP0_CNT_DATA_TOGGLE;
        /* Set the Mode Register  */
        ProtocovUSB_ep0Mode = ProtocovUSB_MODE_ACK_IN_STATUS_OUT;
        /* Update the state (or stay the same) */
        ProtocovUSB_transferState = ProtocovUSB_TRANS_STATE_CONTROL_READ;
    }
    else
    {
        /* Expect Status Stage Out */
        ProtocovUSB_ep0Mode = ProtocovUSB_MODE_STATUS_OUT_ONLY;
        /* Update the state (or stay the same) */
        ProtocovUSB_transferState = ProtocovUSB_TRANS_STATE_CONTROL_READ;
    }

    /* Save the packet size for next time */
    ProtocovUSB_ep0Count =       (uint8) ep0Count;
    ProtocovUSB_lastPacketSize = (uint8) ep0Count;
}


/*******************************************************************************
* Function Name: ProtocovUSB_InitControlRead
****************************************************************************//**
*
*  Initialize a control read transaction. It is used to send data to the host.
*  The following global variables should be initialized before this function
*  called. To send zero length packet use InitZeroLengthControlTransfer
*  function.
*
*
* \return
*  requestHandled state.
*
* \globalvars
*  ProtocovUSB_currentTD.count - counts of data to be sent.
*  ProtocovUSB_currentTD.pData - data pointer.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 ProtocovUSB_InitControlRead(void) 
{
    uint16 xferCount;

    if (ProtocovUSB_currentTD.count == 0u)
    {
        (void) ProtocovUSB_InitZeroLengthControlTransfer();
    }
    else
    {
        /* Set up the state machine */
        ProtocovUSB_transferState = ProtocovUSB_TRANS_STATE_CONTROL_READ;
        
        /* Set the toggle, it gets updated in LoadEP */
        ProtocovUSB_ep0Toggle = 0u;
        
        /* Initialize the Status Block */
        ProtocovUSB_InitializeStatusBlock();
        
        xferCount = ((uint16)((uint16) ProtocovUSB_lengthHiReg << 8u) | ((uint16) ProtocovUSB_lengthLoReg));

        if (ProtocovUSB_currentTD.count > xferCount)
        {
            ProtocovUSB_currentTD.count = xferCount;
        }
        
        ProtocovUSB_LoadEP0();
    }

    return (ProtocovUSB_TRUE);
}


/*******************************************************************************
* Function Name: ProtocovUSB_InitZeroLengthControlTransfer
****************************************************************************//**
*
*  Initialize a zero length data IN transfer.
*
* \return
*  requestHandled state.
*
* \globalvars
*  ProtocovUSB_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  ProtocovUSB_ep0Mode  - prepare for mode register content.
*  ProtocovUSB_transferState - set to TRANS_STATE_CONTROL_READ
*  ProtocovUSB_ep0Count - cleared, means the zero-length packet.
*  ProtocovUSB_lastPacketSize - cleared.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 ProtocovUSB_InitZeroLengthControlTransfer(void)
                                                
{
    /* Update the state */
    ProtocovUSB_transferState = ProtocovUSB_TRANS_STATE_CONTROL_READ;
    
    /* Set the data toggle */
    ProtocovUSB_ep0Toggle = ProtocovUSB_EP0_CNT_DATA_TOGGLE;
    
    /* Set the Mode Register  */
    ProtocovUSB_ep0Mode = ProtocovUSB_MODE_ACK_IN_STATUS_OUT;
    
    /* Save the packet size for next time */
    ProtocovUSB_lastPacketSize = 0u;
    
    ProtocovUSB_ep0Count = 0u;

    return (ProtocovUSB_TRUE);
}


/*******************************************************************************
* Function Name: ProtocovUSB_ControlReadDataStage
****************************************************************************//**
*
*  Handle the Data Stage of a control read transfer.
*
*
* \reentrant
*  No.
*
*******************************************************************************/
void ProtocovUSB_ControlReadDataStage(void) 

{
    ProtocovUSB_LoadEP0();
}


/*******************************************************************************
* Function Name: ProtocovUSB_ControlReadStatusStage
****************************************************************************//**
*
*  Handle the Status Stage of a control read transfer.
*
*
* \globalvars
*  ProtocovUSB_USBFS_transferByteCount - updated with last packet size.
*  ProtocovUSB_transferState - set to TRANS_STATE_IDLE.
*  ProtocovUSB_ep0Mode  - set to MODE_STALL_IN_OUT.
*
* \reentrant
*  No.
*
*******************************************************************************/
void ProtocovUSB_ControlReadStatusStage(void) 
{
    /* Update the transfer byte count */
    ProtocovUSB_transferByteCount += ProtocovUSB_lastPacketSize;
    
    /* Go Idle */
    ProtocovUSB_transferState = ProtocovUSB_TRANS_STATE_IDLE;
    
    /* Update the completion block */
    ProtocovUSB_UpdateStatusBlock(ProtocovUSB_XFER_STATUS_ACK);
    
    /* We expect no more data, so stall INs and OUTs */
    ProtocovUSB_ep0Mode = ProtocovUSB_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: ProtocovUSB_InitControlWrite
****************************************************************************//**
*
*  Initialize a control write transaction
*
* \return
*  requestHandled state.
*
* \globalvars
*  ProtocovUSB_USBFS_transferState - set to TRANS_STATE_CONTROL_WRITE
*  ProtocovUSB_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  ProtocovUSB_ep0Mode  - set to MODE_ACK_OUT_STATUS_IN
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 ProtocovUSB_InitControlWrite(void) 
{
    uint16 xferCount;

    /* Set up the state machine */
    ProtocovUSB_transferState = ProtocovUSB_TRANS_STATE_CONTROL_WRITE;
    
    /* This might not be necessary */
    ProtocovUSB_ep0Toggle = ProtocovUSB_EP0_CNT_DATA_TOGGLE;
    
    /* Initialize the Status Block */
    ProtocovUSB_InitializeStatusBlock();

    xferCount = ((uint16)((uint16) ProtocovUSB_lengthHiReg << 8u) | ((uint16) ProtocovUSB_lengthLoReg));

    if (ProtocovUSB_currentTD.count > xferCount)
    {
        ProtocovUSB_currentTD.count = xferCount;
    }

    /* Expect Data or Status Stage */
    ProtocovUSB_ep0Mode = ProtocovUSB_MODE_ACK_OUT_STATUS_IN;

    return(ProtocovUSB_TRUE);
}


/*******************************************************************************
* Function Name: ProtocovUSB_ControlWriteDataStage
****************************************************************************//**
*
*  Handle the Data Stage of a control write transfer
*       1. Get the data (We assume the destination was validated previously)
*       2. Update the count and data toggle
*       3. Update the mode register for the next transaction
*
*
* \globalvars
*  ProtocovUSB_transferByteCount - Update the transfer byte count from the
*    last transaction.
*  ProtocovUSB_ep0Count - counts the data loaded from the SIE memory
*    in current packet.
*  ProtocovUSB_transferByteCount - sum of the previous bytes transferred
*    on previous packets(sum of USBFS_lastPacketSize)
*  ProtocovUSB_ep0Toggle - inverted
*  ProtocovUSB_ep0Mode  - set to MODE_ACK_OUT_STATUS_IN.
*
* \reentrant
*  No.
*
*******************************************************************************/
void ProtocovUSB_ControlWriteDataStage(void) 
{
    uint8 ep0Count;
    uint8 regIndex = 0u;

    ep0Count = (ProtocovUSB_EP0_CNT_REG & ProtocovUSB_EPX_CNT0_MASK) - ProtocovUSB_EPX_CNTX_CRC_COUNT;

    ProtocovUSB_transferByteCount += (uint8)ep0Count;

    while ((ProtocovUSB_currentTD.count > 0u) && (ep0Count > 0u))
    {
        *ProtocovUSB_currentTD.pData = (uint8) ProtocovUSB_EP0_DR_BASE.epData[regIndex];
        ProtocovUSB_currentTD.pData = &ProtocovUSB_currentTD.pData[1u];
        regIndex++;
        ep0Count--;
        ProtocovUSB_currentTD.count--;
    }
    
    ProtocovUSB_ep0Count = (uint8)ep0Count;
    
    /* Update the data toggle */
    ProtocovUSB_ep0Toggle ^= ProtocovUSB_EP0_CNT_DATA_TOGGLE;
    
    /* Expect Data or Status Stage */
    ProtocovUSB_ep0Mode = ProtocovUSB_MODE_ACK_OUT_STATUS_IN;
}


/*******************************************************************************
* Function Name: ProtocovUSB_ControlWriteStatusStage
****************************************************************************//**
*
*  Handle the Status Stage of a control write transfer
*
* \globalvars
*  ProtocovUSB_transferState - set to TRANS_STATE_IDLE.
*  ProtocovUSB_USBFS_ep0Mode  - set to MODE_STALL_IN_OUT.
*
* \reentrant
*  No.
*
*******************************************************************************/
void ProtocovUSB_ControlWriteStatusStage(void) 
{
    /* Go Idle */
    ProtocovUSB_transferState = ProtocovUSB_TRANS_STATE_IDLE;
    
    /* Update the completion block */    
    ProtocovUSB_UpdateStatusBlock(ProtocovUSB_XFER_STATUS_ACK);
    
    /* We expect no more data, so stall INs and OUTs */
    ProtocovUSB_ep0Mode = ProtocovUSB_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: ProtocovUSB_InitNoDataControlTransfer
****************************************************************************//**
*
*  Initialize a no data control transfer
*
* \return
*  requestHandled state.
*
* \globalvars
*  ProtocovUSB_transferState - set to TRANS_STATE_NO_DATA_CONTROL.
*  ProtocovUSB_ep0Mode  - set to MODE_STATUS_IN_ONLY.
*  ProtocovUSB_ep0Count - cleared.
*  ProtocovUSB_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 ProtocovUSB_InitNoDataControlTransfer(void) 
{
    ProtocovUSB_transferState = ProtocovUSB_TRANS_STATE_NO_DATA_CONTROL;
    ProtocovUSB_ep0Mode       = ProtocovUSB_MODE_STATUS_IN_ONLY;
    ProtocovUSB_ep0Toggle     = ProtocovUSB_EP0_CNT_DATA_TOGGLE;
    ProtocovUSB_ep0Count      = 0u;

    return (ProtocovUSB_TRUE);
}


/*******************************************************************************
* Function Name: ProtocovUSB_NoDataControlStatusStage
****************************************************************************//**
*  Handle the Status Stage of a no data control transfer.
*
*  SET_ADDRESS is special, since we need to receive the status stage with
*  the old address.
*
* \globalvars
*  ProtocovUSB_transferState - set to TRANS_STATE_IDLE.
*  ProtocovUSB_ep0Mode  - set to MODE_STALL_IN_OUT.
*  ProtocovUSB_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  ProtocovUSB_deviceAddress - used to set new address and cleared
*
* \reentrant
*  No.
*
*******************************************************************************/
void ProtocovUSB_NoDataControlStatusStage(void) 
{
    if (0u != ProtocovUSB_deviceAddress)
    {
        /* Update device address if we got new address. */
        ProtocovUSB_CR0_REG = (uint8) ProtocovUSB_deviceAddress | ProtocovUSB_CR0_ENABLE;
        ProtocovUSB_deviceAddress = 0u;
    }

    ProtocovUSB_transferState = ProtocovUSB_TRANS_STATE_IDLE;
    
    /* Update the completion block. */
    ProtocovUSB_UpdateStatusBlock(ProtocovUSB_XFER_STATUS_ACK);
    
    /* Stall IN and OUT, no more data is expected. */
    ProtocovUSB_ep0Mode = ProtocovUSB_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: ProtocovUSB_UpdateStatusBlock
****************************************************************************//**
*
*  Update the Completion Status Block for a Request.  The block is updated
*  with the completion code the ProtocovUSB_transferByteCount.  The
*  StatusBlock Pointer is set to NULL.
*
*  completionCode - status.
*
*
* \globalvars
*  ProtocovUSB_currentTD.pStatusBlock->status - updated by the
*    completionCode parameter.
*  ProtocovUSB_currentTD.pStatusBlock->length - updated.
*  ProtocovUSB_currentTD.pStatusBlock - cleared.
*
* \reentrant
*  No.
*
*******************************************************************************/
void ProtocovUSB_UpdateStatusBlock(uint8 completionCode) 
{
    if (ProtocovUSB_currentTD.pStatusBlock != NULL)
    {
        ProtocovUSB_currentTD.pStatusBlock->status = completionCode;
        ProtocovUSB_currentTD.pStatusBlock->length = ProtocovUSB_transferByteCount;
        ProtocovUSB_currentTD.pStatusBlock = NULL;
    }
}


/*******************************************************************************
* Function Name: ProtocovUSB_InitializeStatusBlock
****************************************************************************//**
*
*  Initialize the Completion Status Block for a Request.  The completion
*  code is set to USB_XFER_IDLE.
*
*  Also, initializes ProtocovUSB_transferByteCount.  Save some space,
*  this is the only consumer.
*
* \globalvars
*  ProtocovUSB_currentTD.pStatusBlock->status - set to XFER_IDLE.
*  ProtocovUSB_currentTD.pStatusBlock->length - cleared.
*  ProtocovUSB_transferByteCount - cleared.
*
* \reentrant
*  No.
*
*******************************************************************************/
void ProtocovUSB_InitializeStatusBlock(void) 
{
    ProtocovUSB_transferByteCount = 0u;
    
    if (ProtocovUSB_currentTD.pStatusBlock != NULL)
    {
        ProtocovUSB_currentTD.pStatusBlock->status = ProtocovUSB_XFER_IDLE;
        ProtocovUSB_currentTD.pStatusBlock->length = 0u;
    }
}


/* [] END OF FILE */
