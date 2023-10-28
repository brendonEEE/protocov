/*******************************************************************************
* File Name: BluetoothUART_PM.c
* Version 2.50
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
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


/***************************************
* Local data allocation
***************************************/

static BluetoothUART_BACKUP_STRUCT  BluetoothUART_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: BluetoothUART_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the BluetoothUART_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  BluetoothUART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void BluetoothUART_SaveConfig(void)
{
    #if(BluetoothUART_CONTROL_REG_REMOVED == 0u)
        BluetoothUART_backup.cr = BluetoothUART_CONTROL_REG;
    #endif /* End BluetoothUART_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: BluetoothUART_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the nonretention control register except FIFO.
*  Does not restore the FIFO which is a set of nonretention registers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  BluetoothUART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling BluetoothUART_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void BluetoothUART_RestoreConfig(void)
{
    #if(BluetoothUART_CONTROL_REG_REMOVED == 0u)
        BluetoothUART_CONTROL_REG = BluetoothUART_backup.cr;
    #endif /* End BluetoothUART_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: BluetoothUART_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The BluetoothUART_Sleep() API saves the current component state. Then it
*  calls the BluetoothUART_Stop() function and calls 
*  BluetoothUART_SaveConfig() to save the hardware configuration.
*  Call the BluetoothUART_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  BluetoothUART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void BluetoothUART_Sleep(void)
{
    #if(BluetoothUART_RX_ENABLED || BluetoothUART_HD_ENABLED)
        if((BluetoothUART_RXSTATUS_ACTL_REG  & BluetoothUART_INT_ENABLE) != 0u)
        {
            BluetoothUART_backup.enableState = 1u;
        }
        else
        {
            BluetoothUART_backup.enableState = 0u;
        }
    #else
        if((BluetoothUART_TXSTATUS_ACTL_REG  & BluetoothUART_INT_ENABLE) !=0u)
        {
            BluetoothUART_backup.enableState = 1u;
        }
        else
        {
            BluetoothUART_backup.enableState = 0u;
        }
    #endif /* End BluetoothUART_RX_ENABLED || BluetoothUART_HD_ENABLED*/

    BluetoothUART_Stop();
    BluetoothUART_SaveConfig();
}


/*******************************************************************************
* Function Name: BluetoothUART_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  BluetoothUART_Sleep() was called. The BluetoothUART_Wakeup() function
*  calls the BluetoothUART_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  BluetoothUART_Sleep() function was called, the BluetoothUART_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  BluetoothUART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void BluetoothUART_Wakeup(void)
{
    BluetoothUART_RestoreConfig();
    #if( (BluetoothUART_RX_ENABLED) || (BluetoothUART_HD_ENABLED) )
        BluetoothUART_ClearRxBuffer();
    #endif /* End (BluetoothUART_RX_ENABLED) || (BluetoothUART_HD_ENABLED) */
    #if(BluetoothUART_TX_ENABLED || BluetoothUART_HD_ENABLED)
        BluetoothUART_ClearTxBuffer();
    #endif /* End BluetoothUART_TX_ENABLED || BluetoothUART_HD_ENABLED */

    if(BluetoothUART_backup.enableState != 0u)
    {
        BluetoothUART_Enable();
    }
}


/* [] END OF FILE */
