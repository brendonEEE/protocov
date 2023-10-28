/***************************************************************************
* File Name: BluetoothUartDma_dma.c  
* Version 1.70
*
*  Description:
*   Provides an API for the DMAC component. The API includes functions
*   for the DMA controller, DMA channels and Transfer Descriptors.
*
*
*   Note:
*     This module requires the developer to finish or fill in the auto
*     generated funcions and setup the dma channel and TD's.
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
#include <CYLIB.H>
#include <CYDMAC.H>
#include <BluetoothUartDma_dma.H>



/****************************************************************************
* 
* The following defines are available in Cyfitter.h
* 
* 
* 
* BluetoothUartDma__DRQ_CTL_REG
* 
* 
* BluetoothUartDma__DRQ_NUMBER
* 
* Number of TD's used by this channel.
* BluetoothUartDma__NUMBEROF_TDS
* 
* Priority of this channel.
* BluetoothUartDma__PRIORITY
* 
* True if BluetoothUartDma_TERMIN_SEL is used.
* BluetoothUartDma__TERMIN_EN
* 
* TERMIN interrupt line to signal terminate.
* BluetoothUartDma__TERMIN_SEL
* 
* 
* True if BluetoothUartDma_TERMOUT0_SEL is used.
* BluetoothUartDma__TERMOUT0_EN
* 
* 
* TERMOUT0 interrupt line to signal completion.
* BluetoothUartDma__TERMOUT0_SEL
* 
* 
* True if BluetoothUartDma_TERMOUT1_SEL is used.
* BluetoothUartDma__TERMOUT1_EN
* 
* 
* TERMOUT1 interrupt line to signal completion.
* BluetoothUartDma__TERMOUT1_SEL
* 
****************************************************************************/


/* Zero based index of BluetoothUartDma dma channel */
uint8 BluetoothUartDma_DmaHandle = DMA_INVALID_CHANNEL;

/*********************************************************************
* Function Name: uint8 BluetoothUartDma_DmaInitalize
**********************************************************************
* Summary:
*   Allocates and initialises a channel of the DMAC to be used by the
*   caller.
*
* Parameters:
*   BurstCount.
*       
*       
*   ReqestPerBurst.
*       
*       
*   UpperSrcAddress.
*       
*       
*   UpperDestAddress.
*       
*
* Return:
*   The channel that can be used by the caller for DMA activity.
*   DMA_INVALID_CHANNEL (0xFF) if there are no channels left. 
*
*
*******************************************************************/
uint8 BluetoothUartDma_DmaInitialize(uint8 BurstCount, uint8 ReqestPerBurst, uint16 UpperSrcAddress, uint16 UpperDestAddress) 
{

    /* Allocate a DMA channel. */
    BluetoothUartDma_DmaHandle = (uint8)BluetoothUartDma__DRQ_NUMBER;

    /* Configure the channel. */
    (void)CyDmaChSetConfiguration(BluetoothUartDma_DmaHandle,
                                  BurstCount,
                                  ReqestPerBurst,
                                  (uint8)BluetoothUartDma__TERMOUT0_SEL,
                                  (uint8)BluetoothUartDma__TERMOUT1_SEL,
                                  (uint8)BluetoothUartDma__TERMIN_SEL);

    /* Set the extended address for the transfers */
    (void)CyDmaChSetExtendedAddress(BluetoothUartDma_DmaHandle, UpperSrcAddress, UpperDestAddress);

    /* Set the priority for this channel */
    (void)CyDmaChPriority(BluetoothUartDma_DmaHandle, (uint8)BluetoothUartDma__PRIORITY);
    
    return BluetoothUartDma_DmaHandle;
}

/*********************************************************************
* Function Name: void BluetoothUartDma_DmaRelease
**********************************************************************
* Summary:
*   Frees the channel associated with BluetoothUartDma.
*
*
* Parameters:
*   void.
*
*
*
* Return:
*   void.
*
*******************************************************************/
void BluetoothUartDma_DmaRelease(void) 
{
    /* Disable the channel */
    (void)CyDmaChDisable(BluetoothUartDma_DmaHandle);
}

