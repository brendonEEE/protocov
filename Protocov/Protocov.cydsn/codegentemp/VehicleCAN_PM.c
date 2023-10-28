/*******************************************************************************
* File Name: VehicleCAN_PM.c
* Version 3.0
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in the low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "VehicleCAN.h"

static VehicleCAN_BACKUP_STRUCT VehicleCAN_backup =
{
    0u,
    #if (CY_PSOC3 || CY_PSOC5)
        0u,
        VehicleCAN_INIT_INTERRUPT_MASK,
        VehicleCAN_MODE_MASK,
        (((uint32) ((uint32) VehicleCAN_SYNC_EDGE    << VehicleCAN_EDGE_MODE_SHIFT))     |
        ((uint32) ((uint32) VehicleCAN_SAMPLING_MODE << VehicleCAN_SAMPLE_MODE_SHIFT))   |
        ((uint32) ((uint32) VehicleCAN_CFG_REG_SJW   << VehicleCAN_CFG_REG_SJW_SHIFT))   |
        ((uint32) ((uint32) VehicleCAN_RESET_TYPE    << VehicleCAN_RESET_SHIFT))         |
        ((uint32) ((uint32) VehicleCAN_CFG_REG_TSEG2 << VehicleCAN_CFG_REG_TSEG2_SHIFT)) |
        ((uint32) ((uint32) VehicleCAN_CFG_REG_TSEG1 << VehicleCAN_CFG_REG_TSEG1_SHIFT)) |
        ((uint32) ((uint32) VehicleCAN_ARBITER       << VehicleCAN_ARBITER_SHIFT))       |
        ((uint32) ((uint32) VehicleCAN_BITRATE       << VehicleCAN_BITRATE_SHIFT)))
    #endif /* CY_PSOC3 || CY_PSOC5 */
};


/*******************************************************************************
* Function Name: VehicleCAN_SaveConfig
********************************************************************************
*
* Summary:
*  Save the CAN configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  VehicleCAN_backup - Modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void VehicleCAN_SaveConfig(void) 
{
    #if (CY_PSOC3 || CY_PSOC5)
        VehicleCAN_backup.intSr = (CY_GET_REG32(VehicleCAN_INT_SR_PTR));
        VehicleCAN_backup.intEn = (CY_GET_REG32(VehicleCAN_INT_EN_PTR));
        VehicleCAN_backup.cmd = (CY_GET_REG32(VehicleCAN_CMD_PTR));
        VehicleCAN_backup.cfg = (CY_GET_REG32(VehicleCAN_CFG_PTR));
    #endif /* CY_PSOC3 || CY_PSOC5 */
}


/*******************************************************************************
* Function Name: VehicleCAN_RestoreConfig
********************************************************************************
*
* Summary:
*  Restore the CAN configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  VehicleCAN_backup - Used when non-retention registers are restored.
*
* Side Effects:
*  If this API is called without first calling SaveConfig then default values
*  from Customizer will be in the following registers: VehicleCAN_INT_SR,
*  VehicleCAN_INT_EN, VehicleCAN_CMD, VehicleCAN_CFG.
*
*******************************************************************************/
void VehicleCAN_RestoreConfig(void) 
{
    #if (CY_PSOC3 || CY_PSOC5)
        CY_SET_REG32(VehicleCAN_INT_SR_PTR, VehicleCAN_backup.intSr);
        CY_SET_REG32(VehicleCAN_INT_EN_PTR, VehicleCAN_backup.intEn);
        CY_SET_REG32(VehicleCAN_CMD_PTR, VehicleCAN_backup.cmd);
        CY_SET_REG32(VehicleCAN_CFG_PTR, VehicleCAN_backup.cfg);
    #endif /* CY_PSOC3 || CY_PSOC5 */
}


/*******************************************************************************
* Function Name: VehicleCAN_Sleep
********************************************************************************
*
* Summary:
*  Prepares CAN Component to go to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  VehicleCAN_backup - Modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void VehicleCAN_Sleep(void) 
{
    #if (!(CY_PSOC3 || CY_PSOC5))
        uint8 i;
    #endif /* (!(CY_PSOC3 || CY_PSOC5)) */

    if (0u != (CY_GET_REG32(VehicleCAN_CMD_PTR) & VehicleCAN_MODE_MASK))
    {
        VehicleCAN_backup.enableState = 1u;
    }
    else /* CAN block is disabled */
    {
        VehicleCAN_backup.enableState = 0u;
    }

    #if (CY_PSOC3 || CY_PSOC5)
        VehicleCAN_SaveConfig();
        (void) VehicleCAN_Stop();
    #else /* CY_PSOC4 */
        /* Abort respective pending TX message requests */
        for (i = 0u; i < VehicleCAN_NUMBER_OF_TX_MAILBOXES; i++)
        {
            VehicleCAN_TX_ABORT_MESSAGE(i);
        }

        /* Sets CAN controller to Stop mode */
        (void) VehicleCAN_Stop();

        /* Clear Global Interrupt enable Flag */
        (void) VehicleCAN_GlobalIntDisable();
    #endif /* CY_PSOC3 || CY_PSOC5 */
}


/*******************************************************************************
* Function Name: VehicleCAN_Wakeup
********************************************************************************
*
* Summary:
*  Prepares CAN Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  VehicleCAN_backup - Used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void VehicleCAN_Wakeup(void) 
{
    #if (CY_PSOC3 || CY_PSOC5)
        /* Enable CAN block in Active mode */
        VehicleCAN_PM_ACT_CFG_REG |= VehicleCAN_ACT_PWR_EN;
        /* Enable CAN block in Alternate Active (Standby) mode */
        VehicleCAN_PM_STBY_CFG_REG |= VehicleCAN_STBY_PWR_EN;

        VehicleCAN_RestoreConfig();

        /* Reconfigure Rx and Tx Buffers control registers */
        (void) VehicleCAN_RxTxBuffersConfig();

        if (VehicleCAN_backup.enableState != 0u)
        {
            /* Enable component's operation */
            (void) VehicleCAN_Enable();
        } /* Do nothing if component's block was disabled before */
    #else /* CY_PSOC4 */
        /* Clear all INT_STATUS bits */
        VehicleCAN_INT_SR_REG = VehicleCAN_INT_STATUS_MASK;

        /* Set Global Interrupt enable Flag */
        (void) VehicleCAN_GlobalIntEnable();

        if (VehicleCAN_backup.enableState != 0u)
        {
            (void) VehicleCAN_Enable();
        } /* Do nothing if component's block was disabled before */
    #endif /* CY_PSOC3 || CY_PSOC5 */
}


/* [] END OF FILE */
