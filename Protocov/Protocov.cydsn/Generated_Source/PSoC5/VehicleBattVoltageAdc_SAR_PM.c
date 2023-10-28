/*******************************************************************************
* File Name: VehicleBattVoltageAdc_SAR_PM.c
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

#include "VehicleBattVoltageAdc_SAR.h"


/***************************************
* Local data allocation
***************************************/

static VehicleBattVoltageAdc_SAR_BACKUP_STRUCT  VehicleBattVoltageAdc_SAR_backup =
{
    VehicleBattVoltageAdc_SAR_DISABLED
};


/*******************************************************************************
* Function Name: VehicleBattVoltageAdc_SAR_SaveConfig
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
void VehicleBattVoltageAdc_SAR_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: VehicleBattVoltageAdc_SAR_RestoreConfig
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
void VehicleBattVoltageAdc_SAR_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: VehicleBattVoltageAdc_SAR_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep.
*  The VehicleBattVoltageAdc_SAR_Sleep() routine saves the current component state,
*  then it calls the ADC_Stop() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  VehicleBattVoltageAdc_SAR_backup - The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void VehicleBattVoltageAdc_SAR_Sleep(void)
{
    if((VehicleBattVoltageAdc_SAR_PWRMGR_SAR_REG  & VehicleBattVoltageAdc_SAR_ACT_PWR_SAR_EN) != 0u)
    {
        if((VehicleBattVoltageAdc_SAR_SAR_CSR0_REG & VehicleBattVoltageAdc_SAR_SAR_SOF_START_CONV) != 0u)
        {
            VehicleBattVoltageAdc_SAR_backup.enableState = VehicleBattVoltageAdc_SAR_ENABLED | VehicleBattVoltageAdc_SAR_STARTED;
        }
        else
        {
            VehicleBattVoltageAdc_SAR_backup.enableState = VehicleBattVoltageAdc_SAR_ENABLED;
        }
        VehicleBattVoltageAdc_SAR_Stop();
    }
    else
    {
        VehicleBattVoltageAdc_SAR_backup.enableState = VehicleBattVoltageAdc_SAR_DISABLED;
    }
}


/*******************************************************************************
* Function Name: VehicleBattVoltageAdc_SAR_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  VehicleBattVoltageAdc_SAR_Sleep() was called. If the component was enabled before the
*  VehicleBattVoltageAdc_SAR_Sleep() function was called, the
*  VehicleBattVoltageAdc_SAR_Wakeup() function also re-enables the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  VehicleBattVoltageAdc_SAR_backup - The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void VehicleBattVoltageAdc_SAR_Wakeup(void)
{
    if(VehicleBattVoltageAdc_SAR_backup.enableState != VehicleBattVoltageAdc_SAR_DISABLED)
    {
        VehicleBattVoltageAdc_SAR_Enable();
        #if(VehicleBattVoltageAdc_SAR_DEFAULT_CONV_MODE != VehicleBattVoltageAdc_SAR__HARDWARE_TRIGGER)
            if((VehicleBattVoltageAdc_SAR_backup.enableState & VehicleBattVoltageAdc_SAR_STARTED) != 0u)
            {
                VehicleBattVoltageAdc_SAR_StartConvert();
            }
        #endif /* End VehicleBattVoltageAdc_SAR_DEFAULT_CONV_MODE != VehicleBattVoltageAdc_SAR__HARDWARE_TRIGGER */
    }
}


/* [] END OF FILE */
