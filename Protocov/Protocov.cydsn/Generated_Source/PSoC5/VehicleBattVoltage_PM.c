/*******************************************************************************
* File Name: VehicleBattVoltage_PM.c
* Version 3.10
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

#include "VehicleBattVoltage.h"


/***************************************
* Local data allocation
***************************************/

static VehicleBattVoltage_BACKUP_STRUCT  VehicleBattVoltage_backup =
{
    VehicleBattVoltage_DISABLED
};


/*******************************************************************************
* Function Name: VehicleBattVoltage_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void VehicleBattVoltage_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: VehicleBattVoltage_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void VehicleBattVoltage_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: VehicleBattVoltage_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep.
*  The VehicleBattVoltage_Sleep() routine saves the current component state,
*  then it calls the ADC_Stop() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  VehicleBattVoltage_backup - The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void VehicleBattVoltage_Sleep(void)
{
    if((VehicleBattVoltage_PWRMGR_SAR_REG  & VehicleBattVoltage_ACT_PWR_SAR_EN) != 0u)
    {
        if((VehicleBattVoltage_SAR_CSR0_REG & VehicleBattVoltage_SAR_SOF_START_CONV) != 0u)
        {
            VehicleBattVoltage_backup.enableState = VehicleBattVoltage_ENABLED | VehicleBattVoltage_STARTED;
        }
        else
        {
            VehicleBattVoltage_backup.enableState = VehicleBattVoltage_ENABLED;
        }
        VehicleBattVoltage_Stop();
    }
    else
    {
        VehicleBattVoltage_backup.enableState = VehicleBattVoltage_DISABLED;
    }
}


/*******************************************************************************
* Function Name: VehicleBattVoltage_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  VehicleBattVoltage_Sleep() was called. If the component was enabled before the
*  VehicleBattVoltage_Sleep() function was called, the
*  VehicleBattVoltage_Wakeup() function also re-enables the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  VehicleBattVoltage_backup - The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void VehicleBattVoltage_Wakeup(void)
{
    if(VehicleBattVoltage_backup.enableState != VehicleBattVoltage_DISABLED)
    {
        VehicleBattVoltage_Enable();
        #if(VehicleBattVoltage_DEFAULT_CONV_MODE != VehicleBattVoltage__HARDWARE_TRIGGER)
            if((VehicleBattVoltage_backup.enableState & VehicleBattVoltage_STARTED) != 0u)
            {
                VehicleBattVoltage_StartConvert();
            }
        #endif /* End VehicleBattVoltage_DEFAULT_CONV_MODE != VehicleBattVoltage__HARDWARE_TRIGGER */
    }
}


/* [] END OF FILE */
