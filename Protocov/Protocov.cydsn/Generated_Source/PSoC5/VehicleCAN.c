/*******************************************************************************
* File Name: VehicleCAN.c
* Version 3.0
*
* Description:
*  The CAN Component provides functionality of Control Area Network.
*  The two types of mailbox configuration available are "Full" and "Basic".
*
* Note:
*  The CAN configuration is put as constant to ROM and can be changed
*  only directly by the registers written by the user.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "VehicleCAN.h"

uint8 VehicleCAN_initVar = 0u;


/*******************************************************************************
* FUNCTION NAME:   VehicleCAN_RxTxBuffersConfig
********************************************************************************
*
* Summary:
*  Inits/Restores default CAN Rx and Tx Buffers control registers configuration
*  provided by the customizer.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the configuration has been accepted or rejected.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    VehicleCAN_FAIL              The function failed
*
* Side Effects:
*  All the Rx and Tx Buffers control registers will be reset to their initial
*  values.
*
*******************************************************************************/
uint8 VehicleCAN_RxTxBuffersConfig(void) 
{
    /* Initial values of CAN RX and TX registers */
    static const VehicleCAN_RX_CFG CYCODE VehicleCAN_RXConfigStruct[] =
    {
        { 0u, 0x8000A8u, 0xFFFFFFFFu, 0x0u },
        { 1u, 0x0u, 0x0u, 0x0u },
        { 2u, 0x0u, 0x0u, 0x0u },
        { 3u, 0x0u, 0x0u, 0x0u },
        { 4u, 0x0u, 0x0u, 0x0u },
        { 5u, 0x0u, 0x0u, 0x0u },
        { 6u, 0x0u, 0x0u, 0x0u },
        { 7u, 0x0u, 0x0u, 0x0u },
        { 8u, 0x0u, 0x0u, 0x0u },
        { 9u, 0x0u, 0x0u, 0x0u },
        { 10u, 0x0u, 0x0u, 0x0u },
        { 11u, 0x0u, 0x0u, 0x0u },
        { 12u, 0x0u, 0x0u, 0x0u },
        { 13u, 0x0u, 0x0u, 0x0u },
        { 14u, 0x0u, 0x0u, 0x0u },
        { 15u, 0x0u, 0x0u, 0x0u }
    };

    static const VehicleCAN_TX_CFG CYCODE VehicleCAN_TXConfigStruct[] =
    {
        { 0u, 0x880008u, 0x0u },
        { 1u, 0x880008u, 0x0u },
        { 2u, 0x880008u, 0x0u },
        { 3u, 0x880008u, 0x0u },
        { 4u, 0x880008u, 0x0u },
        { 5u, 0x880008u, 0x0u },
        { 6u, 0x880008u, 0x0u },
        { 7u, 0x880008u, 0x0u }
    };

    uint8 result = CYRET_SUCCESS;
    uint8 i;

    /* Initialize TX mailboxes */
    for (i = 0u; i < VehicleCAN_NUMBER_OF_TX_MAILBOXES; i++)
    {
        if (VehicleCAN_TxBufConfig((const VehicleCAN_TX_CFG *)
            (&VehicleCAN_TXConfigStruct[i])) != CYRET_SUCCESS)
        {
            result = VehicleCAN_FAIL;
            break;
        }
    }

    if (result == CYRET_SUCCESS)
    {
        /* Initialize RX mailboxes */
        for (i = 0u; i < VehicleCAN_NUMBER_OF_RX_MAILBOXES; i++)
        {
            if (VehicleCAN_RxBufConfig((const VehicleCAN_RX_CFG *)
                (&VehicleCAN_RXConfigStruct[i])) != CYRET_SUCCESS)
            {
                result = VehicleCAN_FAIL;
                break;
            }
        }
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   VehicleCAN_Init
********************************************************************************
*
* Summary:
*  Inits/Restores default CAN configuration provided by the customizer.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the configuration has been accepted or rejected.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    VehicleCAN_FAIL              The function failed
*
* Side Effects:
*  All the registers will be reset to their initial values. This will
*  re-initialize the component with the following exceptions - it will not clear
*  data from the mailboxes.
*  Enable power to the CAN Core.
*
*******************************************************************************/
uint8 VehicleCAN_Init(void) 
{
    uint32 timeout = VehicleCAN_MODE_STATE_STOP_TIMEOUT;
    uint8 result = VehicleCAN_FAIL;
    uint8 localResult = VehicleCAN_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Enable CAN block in Active mode */
        VehicleCAN_PM_ACT_CFG_REG |= VehicleCAN_ACT_PWR_EN;
        /* Enable CAN block in Alternate Active (Standby) mode */
        VehicleCAN_PM_STBY_CFG_REG |= VehicleCAN_STBY_PWR_EN;
        CyExitCriticalSection(enableInterrupts);

        /* Sets CAN controller to stop mode */
        VehicleCAN_CMD_REG.byte[0u] &= (uint8) (~VehicleCAN_MODE_MASK);

        /* Timeout for CAN state machine to switch mode to Stop */
        while ((timeout != 0u) && ((VehicleCAN_CMD_REG.byte[0u] & VehicleCAN_MODE_MASK) != 0u))
        {
            timeout--;
        }
    #else  /* CY_PSOC4 */
        /* Enable CAN IP Block */
        VehicleCAN_CNTL_REG = VehicleCAN_IP_ENABLE;

        /* Sets CAN controller to stop mode */
        VehicleCAN_CMD_REG &= (uint32) (~((uint32) VehicleCAN_MODE_MASK));

        /* Timeout for CAN state machine to switch mode to Stop */
        while ((timeout != 0u) && ((VehicleCAN_CMD_REG & VehicleCAN_MODE_MASK) != 0u))
        {
            timeout--;
        }
    #endif /* CY_PSOC3 || CY_PSOC5 */
        if (timeout != 0u)
        {
            /* Disable Interrupt. */
        CyIntDisable(VehicleCAN_ISR_NUMBER);

        /* Set the ISR to point to the VehicleCAN_ISR Interrupt. */
        (void) CyIntSetVector(VehicleCAN_ISR_NUMBER, & VehicleCAN_ISR);

        /* Set the priority. */
        CyIntSetPriority(VehicleCAN_ISR_NUMBER, VehicleCAN_ISR_PRIORITY);

            if (VehicleCAN_SetPreScaler(VehicleCAN_BITRATE) == CYRET_SUCCESS)
            {
                if (VehicleCAN_SetArbiter(VehicleCAN_ARBITER) == CYRET_SUCCESS)
                {
                    #if (!(CY_PSOC3 || CY_PSOC5))
                        if (VehicleCAN_SetSwapDataEndianness(VehicleCAN_SWAP_DATA_END) == CYRET_SUCCESS)
                    #endif /* (!(CY_PSOC3 || CY_PSOC5)) */
                        {
                            if (VehicleCAN_SetTsegSample(VehicleCAN_CFG_REG_TSEG1,
                                VehicleCAN_CFG_REG_TSEG2, VehicleCAN_CFG_REG_SJW,
                                VehicleCAN_SAMPLING_MODE) == CYRET_SUCCESS)
                            {
                                if (VehicleCAN_SetRestartType(VehicleCAN_RESET_TYPE) == CYRET_SUCCESS)
                                {
                                    if (VehicleCAN_SetEdgeMode(VehicleCAN_SYNC_EDGE) == CYRET_SUCCESS)
                                    {
                                        localResult = CYRET_SUCCESS;
                                    }
                                }
                            }
                        }
                }
            }

            if (localResult == CYRET_SUCCESS)
            {
                if (VehicleCAN_RxTxBuffersConfig() == CYRET_SUCCESS)
                {
                    /* Write IRQ Mask */
                    if (VehicleCAN_SetIrqMask(VehicleCAN_INIT_INTERRUPT_MASK) ==
                        CYRET_SUCCESS)
                    {
                        /* Set CAN Operation Mode to Active mode always */
                        #if (CY_PSOC3 || CY_PSOC5)
                            VehicleCAN_CMD_REG.byte[0u] = VehicleCAN_INITIAL_MODE;
                            if ((VehicleCAN_CMD_REG.byte[0u] & VehicleCAN_MODE_MASK) == 0u)
                        #else  /* CY_PSOC4 */
                            VehicleCAN_CMD_REG &= (uint32) (~((uint32) VehicleCAN_OPMODE_FIELD_MASK));
                            if ((VehicleCAN_CMD_REG & VehicleCAN_OPMODE_FIELD_MASK) == 0u)
                        #endif /* CY_PSOC3 || CY_PSOC5 */
                            {
                                result = CYRET_SUCCESS;
                            }
                    }
                }
            }
        }

    return (result);
}


/*******************************************************************************
* Function Name: VehicleCAN_Enable
********************************************************************************
*
* Summary:
*  This function enables the CAN Component and ISR of CAN Component.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    VehicleCAN_FAIL              The function failed
*
*******************************************************************************/
uint8 VehicleCAN_Enable(void) 
{
    uint32 timeout = VehicleCAN_MODE_STATE_RUN_TIMEOUT;
    uint8 result = VehicleCAN_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();

        /* Enable CAN block in Active mode */
        VehicleCAN_PM_ACT_CFG_REG |= VehicleCAN_ACT_PWR_EN;

        /* Enable CAN block in Alternate Active (Standby) mode */
        VehicleCAN_PM_STBY_CFG_REG |= VehicleCAN_STBY_PWR_EN;

        CyExitCriticalSection(enableInterrupts);
    #endif /* CY_PSOC3 || CY_PSOC5 */

    /* Clear interrupts status */
    CY_SET_REG32(VehicleCAN_INT_SR_PTR, VehicleCAN_INIT_INTERRUPT_MASK);
    (void) VehicleCAN_GlobalIntEnable();

    /* Enable isr */
    CyIntEnable(VehicleCAN_ISR_NUMBER);

    /* Sets CAN controller to run mode */
    CY_SET_REG32(VehicleCAN_CMD_PTR, CY_GET_REG32(VehicleCAN_CMD_PTR) | VehicleCAN_MODE_MASK);

    /* Timeout for CAN state machine to switch mode to Run */
    while ((timeout != 0u) && ((CY_GET_REG32(VehicleCAN_CMD_PTR) & VehicleCAN_MODE_MASK) == 0u))
    {
        timeout--;
    }

    if (timeout != 0u)
    {
        result = CYRET_SUCCESS;
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   VehicleCAN_Start
********************************************************************************
*
* Summary:
*  This function sets CAN Component into the Run mode. Starts Rate Counter if
*  polling mailboxes are available.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    VehicleCAN_FAIL              The function failed
*
* Global variables:
*  VehicleCAN_initVar - used to check the initial configuration, modified
*  on the first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 VehicleCAN_Start(void) 
{
    uint8 result = CYRET_SUCCESS;

    if (VehicleCAN_initVar == 0u)
    {
        result = VehicleCAN_Init();
    }

    if (result == CYRET_SUCCESS)
    {
        VehicleCAN_initVar = 1u;
        result = VehicleCAN_Enable();
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   VehicleCAN_Stop
********************************************************************************
*
* Summary:
*  This function sets CAN Component into the Stop mode.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    VehicleCAN_FAIL              The function failed
*
* Side Effects:
*  Disable power to CAN Core in case of PSoC 3/5.
*  Pending message in the Tx buffer of PSoC 3/5 will not be aborted on calling
*  the VehicleCAN_Stop() API. User has to abort all pending messages
*  before calling the VehicleCAN_Stop() function to make sure that the
*  block stops all the message transmission immediately.
*
*******************************************************************************/
uint8 VehicleCAN_Stop(void) 
{
    uint32 timeout = VehicleCAN_MODE_STATE_STOP_TIMEOUT;
    uint8 result = VehicleCAN_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        uint8 enableInterrupts;
    #endif /* CY_PSOC3 || CY_PSOC5 */

    /* Set CAN controller to stop mode */
    CY_SET_REG32(VehicleCAN_CMD_PTR, (CY_GET_REG32(VehicleCAN_CMD_PTR) &
                                            ((uint32) (~((uint32)VehicleCAN_MODE_MASK)))));

    /* Timeout for CAN state machine to switch mode to Stop */
    while ((timeout != 0u) && ((CY_GET_REG32(VehicleCAN_CMD_PTR) & VehicleCAN_MODE_MASK) != 0u))
    {
        timeout--;
    }

    /* Verify that bit is cleared */
    if (timeout != 0u)
    {
        result = CYRET_SUCCESS;

        /* Disable isr */
    CyIntDisable(VehicleCAN_ISR_NUMBER);

        #if (CY_PSOC3 || CY_PSOC5)
            enableInterrupts = CyEnterCriticalSection();

            /* Disable CAN block in Active mode */
            VehicleCAN_PM_ACT_CFG_REG &= (uint8) (~VehicleCAN_ACT_PWR_EN);

            /* Disable CAN block in Alternate Active (Standby) mode template */
            VehicleCAN_PM_STBY_CFG_REG &= (uint8) (~VehicleCAN_STBY_PWR_EN);

            CyExitCriticalSection(enableInterrupts);
        #endif /* CY_PSOC3 || CY_PSOC5 */
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   VehicleCAN_GlobalIntEnable
********************************************************************************
*
* Summary:
*  This function enables Global Interrupts from CAN Core.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    VehicleCAN_FAIL              The function failed
*
*******************************************************************************/
uint8 VehicleCAN_GlobalIntEnable(void) 
{
    uint8 result = VehicleCAN_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        VehicleCAN_INT_EN_REG.byte[0u] |= VehicleCAN_GLOBAL_INT_MASK;

        /* Verify that bit is set */
        if ((VehicleCAN_INT_EN_REG.byte[0u] & VehicleCAN_GLOBAL_INT_MASK) != 0u)
        {
            result = CYRET_SUCCESS;
        }
    #else  /* CY_PSOC4 */
        VehicleCAN_INT_EN_REG |= VehicleCAN_GLOBAL_INT_MASK;
        /* Verify that bit is set */
        if ((VehicleCAN_INT_EN_REG & VehicleCAN_GLOBAL_INT_MASK) != 0u)
        {
            result = CYRET_SUCCESS;
        }
    #endif /* CY_PSOC3 || CY_PSOC5 */

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   VehicleCAN_GlobalIntDisable
********************************************************************************
*
* Summary:
*  This function disables Global Interrupts from CAN Core.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    VehicleCAN_FAIL              The function failed
*
*******************************************************************************/
uint8 VehicleCAN_GlobalIntDisable(void) 
{
    uint8 result = VehicleCAN_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        VehicleCAN_INT_EN_REG.byte[0u] &= (uint8) (~VehicleCAN_GLOBAL_INT_MASK);

        /* Verify that bit is cleared */
        if ((VehicleCAN_INT_EN_REG.byte[0u] & VehicleCAN_GLOBAL_INT_MASK) == 0u)
        {
            result = CYRET_SUCCESS;
        }
    #else  /* CY_PSOC4 */
        VehicleCAN_INT_EN_REG &= (uint32) (~((uint32) VehicleCAN_GLOBAL_INT_MASK));

        /* Verify that bit is cleared */
        if ((VehicleCAN_INT_EN_REG & VehicleCAN_GLOBAL_INT_MASK) == 0u)
        {
            result = CYRET_SUCCESS;
        }
    #endif /* CY_PSOC3 || CY_PSOC5 */

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   VehicleCAN_SetPreScaler
********************************************************************************
*
* Summary:
*  This function sets PreScaler for generating the time quantum which defines
*  the time quanta. The values between 0x0 and 0x7FFF are valid.
*
* Parameters:
*  bitrate: PreScaler value.
*   Value           Description
*    0               One time quantum equals 1 clock cycle
*    1               One time quantum equals 2 clock cycles
*    ...             ...
*    32767           One time quantum equals 32768 clock cycles
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    VehicleCAN_FAIL              The function failed
*    VehicleCAN_OUT_OF_RANGE      The function parameter is out of range
*
*******************************************************************************/
uint8 VehicleCAN_SetPreScaler(uint16 bitrate) 
{
    uint8 result = VehicleCAN_OUT_OF_RANGE;

    if (bitrate <= VehicleCAN_BITRATE_MASK)
    {
        result = VehicleCAN_FAIL;

        #if (CY_PSOC3 || CY_PSOC5)
            /* Set prescaler */
            CY_SET_REG16((reg16 *) (&VehicleCAN_CFG_REG.byte[2u]), bitrate);

            /* Verify that prescaler is set */
            if (CY_GET_REG16((reg16 *) (&VehicleCAN_CFG_REG.byte[2u])) == bitrate)
            {
                result = CYRET_SUCCESS;
            }
        #else  /* CY_PSOC4 */
            /* Set prescaler */
            VehicleCAN_CFG_REG = (VehicleCAN_CFG_REG & (uint32) (~VehicleCAN_BITRATE_MASK_SHIFTED)) |
            (uint32) ((uint32) bitrate << VehicleCAN_BITRATE_SHIFT);

            /* Verify that prescaler is set */
            if ((VehicleCAN_CFG_REG & VehicleCAN_BITRATE_MASK_SHIFTED) ==
               ((uint32) ((uint32) bitrate << VehicleCAN_BITRATE_SHIFT)))
            {
                result = CYRET_SUCCESS;
            }
        #endif /* CY_PSOC3 || CY_PSOC5 */
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   VehicleCAN_SetArbiter
********************************************************************************
*
* Summary:
*  This function sets the arbitration type for transmit mailboxes. The types of
*  the arbiters are Round Robin and Fixed Priority. Values 0 and 1 are valid.
*
* Parameters:
*  arbiter: The arbitration type for transmit mailboxes.
*   Value                              Description
*    VehicleCAN_ROUND_ROBIN       The Round Robin arbitration
*    VehicleCAN_FIXED_PRIORITY    The Fixed Priority arbitration.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    VehicleCAN_FAIL              The function failed
*
*******************************************************************************/
uint8 VehicleCAN_SetArbiter(uint8 arbiter) 
{
    uint8 result = VehicleCAN_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        if (arbiter == VehicleCAN_ROUND_ROBIN)
        {
            VehicleCAN_CFG_REG.byte[1u] &= (uint8) (~VehicleCAN_ARBITRATION_MASK);

            /* Verify that bit is cleared */
            if ((VehicleCAN_CFG_REG.byte[1u] & VehicleCAN_ARBITRATION_MASK) == 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
        else    /* Fixed Priority */
        {
            VehicleCAN_CFG_REG.byte[1u] |= VehicleCAN_ARBITRATION_MASK;

            /* Verify that bit is set */
            if ((VehicleCAN_CFG_REG.byte[1u] & VehicleCAN_ARBITRATION_MASK) != 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
    #else  /* CY_PSOC4 */
        if (arbiter == VehicleCAN_ROUND_ROBIN)
        {
            VehicleCAN_CFG_REG &= (uint32) (~VehicleCAN_ARBITRATION_MASK);

            /* Verify that bit is cleared */
            if ((VehicleCAN_CFG_REG & VehicleCAN_ARBITRATION_MASK) == 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
        else    /* Fixed priority */
        {
            VehicleCAN_CFG_REG |= VehicleCAN_ARBITRATION_MASK;

            /* Verify that bit is set */
            if ((VehicleCAN_CFG_REG & VehicleCAN_ARBITRATION_MASK) != 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
    #endif /* CY_PSOC3 || CY_PSOC5 */

    return (result);
}


/*******************************************************************************
* FUNCTION NAME: VehicleCAN_SetTsegSample
********************************************************************************
*
* Summary:
*  This function configures: Time segment 1, Time segment 2, Sampling Mode
*  and Synchronization Jump Width.
*
* Parameters:
*  cfgTseg1: The length of time segment 1, values between 0x2 and 0xF are valid;
*  cfgTseg2: The length of time segment 2, values between 0x1 and 0x7 are valid;
*  sjw: Synchronization Jump Width, value between 0x0 and 0x3 are valid;
*  sm: Sampling Mode.
*   Define                               Description
*   VehicleCAN_ONE_SAMPLE_POINT     One sampling point is used
*   VehicleCAN_THREE_SAMPLE_POINTS  Three sampling points are used
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    VehicleCAN_FAIL              The function failed
*    VehicleCAN_OUT_OF_RANGE      The function parameter is out of range
*
*******************************************************************************/
uint8 VehicleCAN_SetTsegSample(uint8 cfgTseg1, uint8 cfgTseg2, uint8 sjw, uint8 sm)
                                     
{
    uint8 result = VehicleCAN_OUT_OF_RANGE;
    uint8 cfgTemp;

    if ((cfgTseg1 >= VehicleCAN_CFG_REG_TSEG1_LOWER_LIMIT) && (cfgTseg1 <=
         VehicleCAN_CFG_REG_TSEG1_UPPER_LIMIT))
    {
        if (((cfgTseg2 >= VehicleCAN_CFG_REG_TSEG2_LOWER_LIMIT) &&
             (cfgTseg2 <= VehicleCAN_CFG_REG_TSEG2_UPPER_LIMIT)) || ((sm == VehicleCAN_ONE_SAMPLE_POINT) &&
             (cfgTseg2 == VehicleCAN_CFG_REG_TSEG2_EXCEPTION)))
        {
            if ((sjw <= VehicleCAN_CFG_REG_SJW_LOWER_LIMIT) && (sjw <= cfgTseg1) && (sjw <= cfgTseg2))
            {
                result = VehicleCAN_FAIL;

                #if (CY_PSOC3 || CY_PSOC5)
                    cfgTemp = VehicleCAN_CFG_REG.byte[1];
                    cfgTemp &= (uint8) (~VehicleCAN_CFG_REG_TSEG1_MASK);
                    cfgTemp |= cfgTseg1;

                    /* Write register byte 1 */
                    VehicleCAN_CFG_REG.byte[1u] = cfgTemp;

                    /* Verify 1st byte of VehicleCAN_CFG_REG register */
                    if (VehicleCAN_CFG_REG.byte[1u] == cfgTemp)
                    {
                        cfgTemp = 0u;
                        /* Set appropriate bits */
                        if (sm != VehicleCAN_ONE_SAMPLE_POINT)
                        {
                            cfgTemp = VehicleCAN_SAMPLE_MODE_MASK;
                        }
                        cfgTemp |= ((uint8) (cfgTseg2 << VehicleCAN_CFG_REG_TSEG2_SHIFT)) |
                                   ((uint8) (sjw << VehicleCAN_CFG_REG_SJW_SHIFT));

                        /* Write register byte 0 */
                        VehicleCAN_CFG_REG.byte[0u] = cfgTemp;

                        /* Verify 1st byte of VehicleCAN_CFG_REG register */
                        if (VehicleCAN_CFG_REG.byte[0u] == cfgTemp)
                        {
                            result = CYRET_SUCCESS;
                        }
                    }
                #else  /* CY_PSOC4 */
                    cfgTemp = (uint8) (VehicleCAN_CFG_REG >> VehicleCAN_CFG_REG_TSEG1_SHIFT);
                    cfgTemp &= (uint8) (~VehicleCAN_CFG_REG_TSEG1_MASK);
                    cfgTemp |= cfgTseg1;

                    /* Write register byte 1 */
                    VehicleCAN_CFG_REG =
                    (VehicleCAN_CFG_REG & (uint32) (~((uint32) ((uint32) VehicleCAN_CFG_REG_TSEG1_MASK <<
                    VehicleCAN_CFG_REG_TSEG1_SHIFT)))) |
                    (uint32) ((uint32) cfgTemp << VehicleCAN_CFG_REG_TSEG1_SHIFT);

                    /* Verify 1st byte of VehicleCAN_CFG_REG register */
                    if ((VehicleCAN_CFG_REG & (uint32) ((uint32) VehicleCAN_CFG_REG_TSEG1_MASK <<
                       VehicleCAN_CFG_REG_TSEG1_SHIFT)) == (uint32) ((uint32) ((uint32) cfgTemp &
                       VehicleCAN_CFG_REG_TSEG1_MASK) << VehicleCAN_CFG_REG_TSEG1_SHIFT))
                    {
                        cfgTemp = 0u;
                        /* Set appropriate bits */
                        if (sm != VehicleCAN_ONE_SAMPLE_POINT)
                        {
                            cfgTemp = VehicleCAN_SAMPLE_MODE_MASK;
                        }
                        cfgTemp |= ((uint8) (cfgTseg2 << VehicleCAN_CFG_REG_TSEG2_SHIFT)) |
                                   ((uint8) (sjw << VehicleCAN_CFG_REG_SJW_SHIFT));

                        /* Write register byte 0 */
                        VehicleCAN_CFG_REG = (VehicleCAN_CFG_REG &
                        (uint32) (~((uint32) (VehicleCAN_CFG_REG_TSEG2_MASK | VehicleCAN_CFG_REG_SJW_MASK |
                        VehicleCAN_SAMPLE_MODE_MASK)))) | cfgTemp;

                        /* Verify 1st byte of VehicleCAN_CFG_REG register */
                        if ((VehicleCAN_CFG_REG & (VehicleCAN_CFG_REG_TSEG2_MASK |
                           VehicleCAN_CFG_REG_SJW_MASK | VehicleCAN_SAMPLE_MODE_MASK)) == cfgTemp)
                        {
                            result = CYRET_SUCCESS;
                        }
                    }
                #endif /* CY_PSOC3 || CY_PSOC5 */
            }
        }
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   VehicleCAN_SetRestartType
********************************************************************************
*
* Summary:
*  This function sets the Reset type. The types of Reset are Automatic and
*  Manual. Manual Reset is the recommended setting.
*
* Parameters:
*  reset: Reset Type.
*   Define                             Description
*    VehicleCAN_MANUAL_RESTART    After Bus-Off, CAN must be restarted
*                                       manually. This is the recommended
*                                       setting.
*    VehicleCAN_AUTO_RESTART      After Bus-Off, CAN restarts
*                                       automatically after 128 groups of 11
*                                       recessive bits.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    VehicleCAN_FAIL              The function failed
*
*******************************************************************************/
uint8 VehicleCAN_SetRestartType(uint8 reset) 
{
    uint8 result = VehicleCAN_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        if (reset == VehicleCAN_MANUAL_RESTART)
        {
            VehicleCAN_CFG_REG.byte[0u] &= (uint8) (~VehicleCAN_RESET_MASK);

            /* Verify that bit is cleared */
            if ((VehicleCAN_CFG_REG.byte[0u] & VehicleCAN_RESET_MASK) == 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
        else    /* Automatic restart */
        {
            VehicleCAN_CFG_REG.byte[0u] |= VehicleCAN_RESET_MASK;

            /* Verify that bit is set */
            if ((VehicleCAN_CFG_REG.byte[0u] & VehicleCAN_RESET_MASK) != 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
    #else  /* CY_PSOC4 */
        if (reset == VehicleCAN_MANUAL_RESTART)
        {
            VehicleCAN_CFG_REG &= (uint32) (~((uint32) VehicleCAN_RESET_MASK));

            /* Verify that bit is cleared */
            if ((VehicleCAN_CFG_REG & VehicleCAN_RESET_MASK) == 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
        else    /* Automatic restart */
        {
            VehicleCAN_CFG_REG |= VehicleCAN_RESET_MASK;

            /* Verify that bit is set */
            if ((VehicleCAN_CFG_REG & VehicleCAN_RESET_MASK) != 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
    #endif /* CY_PSOC3 || CY_PSOC5 */

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   VehicleCAN_SetEdgeMode
********************************************************************************
*
* Summary:
*  This function sets Edge Mode. The modes are 'R' to 'D'(Recessive to Dominant)
*  and Both edges are used.
*
* Parameters:
*  edge: Edge Mode.
*   Define                             Description
*    VehicleCAN_EDGE_R_TO_D       The edge from R to D is used for
*                                       synchronization
*    VehicleCAN_BOTH_EDGES        Both edges are used
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    VehicleCAN_FAIL              The function failed
*
*******************************************************************************/
uint8 VehicleCAN_SetEdgeMode(uint8 edge) 
{
    uint8 result = VehicleCAN_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        if (edge == VehicleCAN_EDGE_R_TO_D)
        {
            /* Recessive to Dominant is used for synchronization */
            VehicleCAN_CFG_REG.byte[0u] &= (uint8) (~VehicleCAN_EDGE_MODE_MASK);

            /* Verify that bit is cleared */
            if ((VehicleCAN_CFG_REG.byte[0u] & VehicleCAN_EDGE_MODE_MASK) == 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
        else
        {
            /* Both edges to be used */
            VehicleCAN_CFG_REG.byte[0u] |= VehicleCAN_EDGE_MODE_MASK;

            /* Verify that bit is set */
            if ((VehicleCAN_CFG_REG.byte[0u] & VehicleCAN_EDGE_MODE_MASK) != 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
    #else  /* CY_PSOC4 */
        if (edge == VehicleCAN_EDGE_R_TO_D)
        {
            /* Recessive to Dominant is used for synchronization */
            VehicleCAN_CFG_REG &= (uint32) (~((uint32) VehicleCAN_EDGE_MODE_MASK));

            /* Verify that bit is cleared */
            if ((VehicleCAN_CFG_REG & VehicleCAN_EDGE_MODE_MASK) == 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
        else
        {
            /* Both edges to be used */
            VehicleCAN_CFG_REG |= VehicleCAN_EDGE_MODE_MASK;

            /* Verify that bit is set */
            if ((VehicleCAN_CFG_REG & VehicleCAN_EDGE_MODE_MASK) != 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
    #endif /* CY_PSOC3 || CY_PSOC5 */

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   VehicleCAN_SetOpMode
********************************************************************************
*
* Summary:
*  This function sets Operation Mode.
*
* Parameters:
*  opMode: Operation Mode value.
*   Define                              Description
*    VehicleCAN_STOP_MODE          The CAN controller is in the Stop mode
*    VehicleCAN_ACTIVE_RUN_MODE    The CAN controller is in the Active
*                                        mode
*    VehicleCAN_LISTEN_ONLY_MODE   The CAN controller is in the Listen
*                                        Only mode: The output is held at the
*                                        'R' level.
*    VehicleCAN_INTERNAL_LOOP_BACK The CAN controller is in the Internal
*                                        Loopback mode. This mode is used for
*                                        the testing purpose and the transmitted
*                                        transactions are internally routed
*                                        back to the receiver logic and
*                                        processed by the controller in this
*                                        mode. Not available for PSoC3/5.
*    VehicleCAN_EXTERNAL_LOOP_BACK This mode is used for the testing
*                                        purpose by connecting Tx and Rx lines
*                                        externally. The transmitted messages
*                                        are received back and processed by the
*                                        CAN controller in this mode.
*                                        Not available for PSoC3/5.
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    VehicleCAN_FAIL              The function failed
*
* Side Effects:
*  For PSoC 4 device family the function re-initializes the CAN registers.
*
*******************************************************************************/
uint8 VehicleCAN_SetOpMode(uint8 opMode) 
{
    #if (CY_PSOC3 || CY_PSOC5)
        uint32 timeout;
    #endif /* CY_PSOC3 || CY_PSOC5 */
    uint8 result = VehicleCAN_FAIL;
    uint8 runState = VehicleCAN_STOP_MODE;

    #if (CY_PSOC3 || CY_PSOC5)
        if (((VehicleCAN_CMD_REG.byte[0u] & VehicleCAN_ACTIVE_RUN_MODE) != 0u) ||
            (opMode == VehicleCAN_ACTIVE_RUN_MODE))
        {
            runState = VehicleCAN_ACTIVE_RUN_MODE;
        }

        /* Set CAN to the Stop Mode */
        VehicleCAN_CMD_REG.byte[0u] = VehicleCAN_STOP_MODE;

        /* Timeout for CAN state machine to switch mode to Stop */
        for (timeout = VehicleCAN_MODE_STATE_STOP_TIMEOUT;
            (timeout != 0u) && ((VehicleCAN_CMD_REG.byte[0u] & VehicleCAN_ACTIVE_RUN_MODE) != 0u);
             timeout--)
        {
        }

        if (timeout != 0u)
        {
            result = CYRET_SUCCESS;
        }

        if ((result == CYRET_SUCCESS) && (opMode != VehicleCAN_STOP_MODE))
        {
            if (opMode == VehicleCAN_LISTEN_ONLY_MODE)
            {
                VehicleCAN_CMD_REG.byte[0u] = VehicleCAN_LISTEN_ONLY_MODE;
            }

            if (runState == VehicleCAN_ACTIVE_RUN_MODE)
            {
                VehicleCAN_CMD_REG.byte[0u] |= VehicleCAN_ACTIVE_RUN_MODE;

                /* Timeout for CAN state machine to switch mode to Run */
                for (timeout = VehicleCAN_MODE_STATE_RUN_TIMEOUT;
                    (timeout != 0u) && ((VehicleCAN_CMD_REG.byte[0u] & VehicleCAN_MODE_MASK) == 0u);
                     timeout--)
                {
                }

                if (timeout == 0u)
                {
                    result = VehicleCAN_FAIL;
                }
            }
        }
    #else  /* CY_PSOC4 */
        if (((VehicleCAN_CMD_REG & VehicleCAN_MODE_MASK) != 0u) ||
            (opMode == VehicleCAN_ACTIVE_RUN_MODE))
        {
            runState = VehicleCAN_ACTIVE_RUN_MODE;
        }

        /* Sets CAN Component into the Stop mode */
        if (VehicleCAN_Stop() == CYRET_SUCCESS)
        {
            /* Disable CAN IP Block to reset configuration before sets Operation Mode */
            VehicleCAN_CNTL_REG = (uint32) (~VehicleCAN_IP_ENABLE);

            /* Enable CAN IP Block */
            VehicleCAN_CNTL_REG = VehicleCAN_IP_ENABLE;

            result = VehicleCAN_Init();

            if ((result == CYRET_SUCCESS) && (opMode != VehicleCAN_STOP_MODE))
            {
                if (opMode != VehicleCAN_ACTIVE_RUN_MODE)
                {
                    /* Set CAN Operation Mode */
                    VehicleCAN_CMD_REG |= opMode;
                }

                if (runState == VehicleCAN_ACTIVE_RUN_MODE)
                {
                    /* Enable component's operation */
                    result = VehicleCAN_Enable();
                }
            }
        }
    #endif /* CY_PSOC3 || CY_PSOC5 */

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   VehicleCAN_RXRegisterInit
********************************************************************************
*
* Summary:
*  This function writes only receive CAN registers.
*
* Parameters:
*  regAddr: The pointer to a CAN receive register;
*  config:  The value that will be written in the register.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    VehicleCAN_FAIL              The function failed
*    VehicleCAN_OUT_OF_RANGE      The function parameter is out of range
*
*******************************************************************************/
uint8 VehicleCAN_RXRegisterInit(reg32 *regAddr, uint32 config)
                                      
{
    uint8 result = VehicleCAN_OUT_OF_RANGE;

    if ((((uint32) regAddr & VehicleCAN_REG_ADDR_MASK) >=
        ((uint32) VehicleCAN_RX_FIRST_REGISTER_PTR & VehicleCAN_REG_ADDR_MASK)) &&
        ((((uint32) regAddr & VehicleCAN_REG_ADDR_MASK)) <=
        ((uint32) VehicleCAN_RX_LAST_REGISTER_PTR & VehicleCAN_REG_ADDR_MASK)))
    {
        result = VehicleCAN_FAIL;

        if ((((uint32) regAddr & VehicleCAN_REG_ADDR_MASK) % VehicleCAN_RX_CMD_REG_WIDTH) == 0u)
        {
            config |= VehicleCAN_RX_WPN_SET;

    /* Disable isr */
    CyIntDisable(VehicleCAN_ISR_NUMBER);

            /* Write defined RX CMD registers */
            CY_SET_REG32(regAddr, config);

    /* Enable isr */
    CyIntEnable(VehicleCAN_ISR_NUMBER);

            /* Verify register */
            if ((CY_GET_REG32(regAddr) & VehicleCAN_RX_READ_BACK_MASK) ==
                (config & VehicleCAN_RX_READ_BACK_MASK))
            {
                result = CYRET_SUCCESS;
            }
        }
        /* All registers except RX CMD*/
        else
        {
    /* Disable isr */
    CyIntDisable(VehicleCAN_ISR_NUMBER);

            /* Write defined CAN receive register */
            CY_SET_REG32(regAddr, config);

    /* Enable isr */
    CyIntEnable(VehicleCAN_ISR_NUMBER);

            /* Verify register */
            if (CY_GET_REG32(regAddr) == config)
            {
                result = CYRET_SUCCESS;
            }
        }
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   VehicleCAN_SetIrqMask
********************************************************************************
*
* Summary:
*  This function sets to enable/disable particular interrupt sources. Interrupt
*  Mask directly write to the CAN Interrupt Enable register. A particular
*  interrupt source is enabled by setting its respective flag to 1.
*
* Parameters:
*  mask: Interrupt enable/disable request. 1 bit per interrupt source.
*   Define                                    Description
*    VehicleCAN_GLOBAL_INT_ENABLE        Global Interrupt Enable Flag
*    VehicleCAN_ARBITRATION_LOST_ENABLE  Arbitration Loss Interrupt Enable
*    VehicleCAN_OVERLOAD_ERROR_ENABLE    Overload Interrupt Enable
*    VehicleCAN_BIT_ERROR_ENABLE         Bit Error Interrupt Enable
*    VehicleCAN_STUFF_ERROR_ENABLE       Stuff Error Interrupt Enable
*    VehicleCAN_ACK_ERROR_ENABLE         Ack Error Interrupt Enable
*    VehicleCAN_FORM_ERROR_ENABLE        Form Error Interrupt Enable
*    VehicleCAN_CRC_ERROR_ENABLE         CRC Error Interrupt Enable
*    VehicleCAN_BUS_OFF_ENABLE           Bus-Off State Interrupt Enable
*    VehicleCAN_RX_MSG_LOST_ENABLE       Rx Msg Loss Interrupt Enable
*    VehicleCAN_TX_MESSAGE_ENABLE        Tx Msg Sent Interrupt Enable
*    VehicleCAN_RX_MESSAGE_ENABLE        Msg Received Interrupt Enable
*    VehicleCAN_RTR_MESSAGE_ENABLE       RTR Auto-reply Interrupt Enable
*    VehicleCAN_STUCK_AT_ZERO_ENABLE     Stuck at dominant error Interrupt
*                                              Enable
*    VehicleCAN_SST_FAILURE_ENABLE       SST failure Interrupt Enable
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    VehicleCAN_FAIL              The function failed
*
*******************************************************************************/
uint8 VehicleCAN_SetIrqMask(uint16 mask) 
{
    uint8 result = VehicleCAN_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        /* Write byte 0 and 1 of VehicleCAN_INT_EN_REG register */
        CY_SET_REG16((reg16 *) (&VehicleCAN_INT_EN_REG), mask);

        /* Verify VehicleCAN_INT_EN_REG register */
        if (CY_GET_REG16((reg16 *) (&VehicleCAN_INT_EN_REG)) == mask)
        {
            result = CYRET_SUCCESS;
        }
    #else  /* CY_PSOC4 */
        /* Write byte 0 and 1 of VehicleCAN_INT_EN_REG register */
        VehicleCAN_INT_EN_REG = mask;

        /* Verify VehicleCAN_INT_EN_REG register */
        if ((VehicleCAN_INT_EN_REG & VehicleCAN_REG_ADDR_MASK) == mask)
        {
            result = CYRET_SUCCESS;
        }
    #endif /* CY_PSOC3 || CY_PSOC5 */

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   VehicleCAN_GetTXErrorFlag
********************************************************************************
*
* Summary:
*  This function returns the bit that indicates if the number of TX errors
*  exceeds 0x60.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the number of TX errors exceeds 0x60.
*
*******************************************************************************/
uint8 VehicleCAN_GetTXErrorFlag(void) 
{
    #if (CY_PSOC3 || CY_PSOC5)
        /* Get state of transmit error flag */
        return (((VehicleCAN_ERR_SR_REG.byte[2u] & VehicleCAN_TX_ERROR_FLAG_MASK) ==
                  VehicleCAN_TX_ERROR_FLAG_MASK) ? 1u : 0u);
    #else  /* CY_PSOC4 */
        /* Get state of transmit error flag */
        return (((VehicleCAN_ERR_SR_REG & VehicleCAN_TX_ERROR_FLAG_MASK) ==
                  VehicleCAN_TX_ERROR_FLAG_MASK) ? 1u : 0u);
    #endif /* CY_PSOC3 || CY_PSOC5 */

}


/*******************************************************************************
* FUNCTION NAME:   VehicleCAN_GetRXErrorFlag
********************************************************************************
*
* Summary:
*  This function returns the bit that indicates if the number of RX errors
*  exceeds 0x60.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the number of TX errors exceeds 0x60.
*
*******************************************************************************/
uint8 VehicleCAN_GetRXErrorFlag(void) 
{
    #if (CY_PSOC3 || CY_PSOC5)
        /* Get state of receive error flag */
        return (((VehicleCAN_ERR_SR_REG.byte[2u] & VehicleCAN_RX_ERROR_FLAG_MASK) ==
                  VehicleCAN_RX_ERROR_FLAG_MASK) ? 1u : 0u);
    #else  /* CY_PSOC4 */
        /* Get state of receive error flag */
        return (((VehicleCAN_ERR_SR_REG & VehicleCAN_RX_ERROR_FLAG_MASK) ==
                  VehicleCAN_RX_ERROR_FLAG_MASK) ? 1u : 0u);
    #endif /* CY_PSOC3 || CY_PSOC5 */

}


/*******************************************************************************
* FUNCTION NAME:   VehicleCAN_GetTXErrorCount
********************************************************************************
*
* Summary:
*  This function returns the number of Transmit Errors.
*
* Parameters:
*  None.
*
* Return:
*  The number of Transmit Errors.
*
*******************************************************************************/
uint8 VehicleCAN_GetTXErrorCount(void) 
{
    #if (CY_PSOC3 || CY_PSOC5)
        /* Get state of transmit error count */
        return (VehicleCAN_ERR_SR_REG.byte[0u]);    /* bits 7-0 */
    #else  /* CY_PSOC4 */
        /* Get state of transmit error count */
        return ((uint8) VehicleCAN_ERR_SR_REG);    /* bits 7-0 */
    #endif /* CY_PSOC3 || CY_PSOC5 */
}


/*******************************************************************************
* FUNCTION NAME:   VehicleCAN_GetRXErrorCount
********************************************************************************
*
* Summary:
*  This function returns the number of Receive Errors.
*
* Parameters:
*  None.
*
* Return:
*  The number of Receive Errors.
*
*******************************************************************************/
uint8 VehicleCAN_GetRXErrorCount(void) 
{
    #if (CY_PSOC3 || CY_PSOC5)
        /* Get state of receive error count */
        return (VehicleCAN_ERR_SR_REG.byte[1u]);    /* bits 15-8 */
    #else  /* CY_PSOC4 */
        /* Get state of receive error count (bits 15-8) */
        return ((uint8) (VehicleCAN_ERR_SR_REG >> VehicleCAN_ONE_BYTE_OFFSET));
    #endif /* CY_PSOC3 || CY_PSOC5 */

}


/*******************************************************************************
* FUNCTION NAME:   VehicleCAN_GetErrorState
********************************************************************************
*
* Summary:
*  This function returns the error status of CAN Component.
*
* Parameters:
*  None.
*
* Return:
*  The error status.
*
*******************************************************************************/
uint8 VehicleCAN_GetErrorState(void) 
{
    #if (CY_PSOC3 || CY_PSOC5)
        /* Get error state of receiver */
        return (VehicleCAN_ERR_SR_REG.byte[2u] & VehicleCAN_ERROR_STATE_MASK);
    #else  /* CY_PSOC4 */
        /* Get error state of receiver */
        return ((uint8) ((VehicleCAN_ERR_SR_REG >> VehicleCAN_TWO_BYTE_OFFSET) &
                VehicleCAN_ERROR_STATE_MASK));
    #endif /* CY_PSOC3 || CY_PSOC5 */
}


/*******************************************************************************
* FUNCTION NAME:   VehicleCAN_RxBufConfig
********************************************************************************
*
* Summary:
*  This function configures all receive registers for a particular mailbox.
*
* Parameters:
*  rxConfig: The pointer to a structure that contain all required values to
*  configure all receive registers for a particular mailbox.
*
* Return:
*  The indication if particular configuration has been accepted or rejected.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    VehicleCAN_FAIL              The function failed
*
*******************************************************************************/
uint8 VehicleCAN_RxBufConfig(const VehicleCAN_RX_CFG *rxConfig)
                                   
{
    uint8 result = VehicleCAN_FAIL;

    /* Write RX CMD Register */
    CY_SET_REG32((reg32 *) (&VehicleCAN_RX[rxConfig->rxmailbox].rxcmd), (rxConfig->rxcmd |
                 VehicleCAN_RX_WPN_SET));
    if ((CY_GET_REG32((reg32 *) (&VehicleCAN_RX[rxConfig->rxmailbox].rxcmd)) &
         VehicleCAN_RX_READ_BACK_MASK) == (rxConfig->rxcmd & VehicleCAN_RX_WPN_CLEAR))
    {
        /* Write RX AMR Register */
        CY_SET_REG32((reg32 *) (&VehicleCAN_RX[rxConfig->rxmailbox].rxamr), rxConfig->rxamr);
        if (CY_GET_REG32((reg32 *) (&VehicleCAN_RX[rxConfig->rxmailbox].rxamr)) == rxConfig->rxamr)
        {
            /* Write RX ACR Register */
            CY_SET_REG32((reg32 *) (&VehicleCAN_RX[rxConfig->rxmailbox].rxacr), rxConfig->rxacr);
            if (CY_GET_REG32((reg32 *) (&VehicleCAN_RX[rxConfig->rxmailbox].rxacr)) == rxConfig->rxacr)
            {
                /* Write RX AMRD Register */
                CY_SET_REG32((reg32 *) (&VehicleCAN_RX[rxConfig->rxmailbox].rxamrd), 0xFFFFFFFFu);
                if (CY_GET_REG32((reg32 *) (&VehicleCAN_RX[rxConfig->rxmailbox].rxamrd)) == 0xFFFFFFFFu)
                {
                    /* Write RX ACRD Register */
                    CY_SET_REG32((reg32 *) (&VehicleCAN_RX[rxConfig->rxmailbox].rxacrd), 0x00000000u);
                    if (CY_GET_REG32((reg32 *) (&VehicleCAN_RX[rxConfig->rxmailbox].rxacrd)) == 0x00000000u)
                    {
                        result = CYRET_SUCCESS;
                    }
                }
            }
        }
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   VehicleCAN_TxBufConfig
********************************************************************************
*
* Summary:
*  This function configures all transmit registers for a particular mailbox.
*  Mailbox number contains VehicleCAN_TX_CFG structure.
*
* Parameters:
*  txConfig: The pointer to structure that contain all required values to
*  configure all transmit registers for a particular mailbox.
*
* Return:
*  The indication if particular configuration has been accepted or rejected.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    VehicleCAN_FAIL              The function failed
*
*******************************************************************************/
uint8 VehicleCAN_TxBufConfig(const VehicleCAN_TX_CFG *txConfig)
                                   
{
    uint8 result = VehicleCAN_FAIL;

    /* Write TX CMD Register */
    CY_SET_REG32(VehicleCAN_TX_CMD_PTR(txConfig->txmailbox), (txConfig->txcmd | VehicleCAN_TX_WPN_SET));
    if ((CY_GET_REG32(VehicleCAN_TX_CMD_PTR(txConfig->txmailbox)) &
        VehicleCAN_TX_READ_BACK_MASK) == (txConfig->txcmd & VehicleCAN_TX_WPN_CLEAR))
    {
        /* Write TX ID Register */
        CY_SET_REG32(VehicleCAN_TX_ID_PTR(txConfig->txmailbox), txConfig->txid);
        if (CY_GET_REG32(VehicleCAN_TX_ID_PTR(txConfig->txmailbox)) == txConfig->txid)
        {
            result = CYRET_SUCCESS;
        }
    }

    return (result);
}


#if (!(CY_PSOC3 || CY_PSOC5))

/*******************************************************************************
* FUNCTION NAME:   VehicleCAN_SetSwapDataEndianness
********************************************************************************
*
* Summary:
*  This function selects whether the data byte endianness of the CAN receive and
*  transmit data fields has to be swapped or not swapped. This is useful to
*  match the data byte endianness to the endian setting of the processor or the
*  used CAN protocol.
*
* Parameters:
*  swap: Swap Enable/Disable setting.
*   Define                                   Description
*   VehicleCAN_SWAP_ENDIANNESS_ENABLE   The endianness of transmitted/
*                                             received data byte fields (Big
*                                             endian) is not swapped during
*                                             multibyte data transmission.
*   VehicleCAN_SWAP_ENDIANNESS_DISABLE  The endianness of transmitted/
*                                             received data byte fields is
*                                             swapped (Little endian) during
*                                             multi byte data transmission.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    VehicleCAN_FAIL              The function failed
*
*******************************************************************************/
uint8 VehicleCAN_SetSwapDataEndianness(uint8 swap)
{
    uint8 result = VehicleCAN_FAIL;

    if (swap == VehicleCAN_SWAP_ENDIANNESS_DISABLE)    /* Big endian */
    {
        VehicleCAN_CFG_REG &= (uint32) (~VehicleCAN_ENDIANNESS_MASK);

        /* Verify that bit is cleared */
        if ((VehicleCAN_CFG_REG & VehicleCAN_ENDIANNESS_MASK) == 0u)
        {
            result = CYRET_SUCCESS;
        }
    }
    else    /* Little endian */
    {
        VehicleCAN_CFG_REG |= VehicleCAN_ENDIANNESS_MASK;

        /* Verify that bit is set */
        if ((VehicleCAN_CFG_REG & VehicleCAN_ENDIANNESS_MASK) != 0u)
        {
            result = CYRET_SUCCESS;
        }
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   VehicleCAN_SetErrorCaptureRegisterMode
********************************************************************************
*
* Summary:
*  This function sets the Error Capture register mode. The two modes are
*  possible: Free Running and Error Capture.
*
* Parameters:
*  ecrMode: The Error Capture register mode setting.
*   Define                               Description
*   VehicleCAN_ECR_FREE_RUNNING     The ECR captures the field and bit
*                                         position within the current CAN frame.
*   VehicleCAN_ECR_ERROR_CAPTURE    In this mode the ECR register only
*                                         captures an error event. For
*                                         successive error captures, the ECR
*                                         needs to be armed again by writing
*                                         to the ECR register.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    VehicleCAN_FAIL              The function failed
*
*******************************************************************************/
uint8 VehicleCAN_SetErrorCaptureRegisterMode(uint8 ecrMode)
{
    uint8 result = VehicleCAN_FAIL;

    if (ecrMode == VehicleCAN_ECR_FREE_RUNNING)
    {
        VehicleCAN_CFG_REG &= (uint32) (~VehicleCAN_ECR_MODE_MASK);

        /* Verify that bit is cleared */
        if ((VehicleCAN_CFG_REG & VehicleCAN_ECR_MODE_MASK) == 0u)
        {
            result = CYRET_SUCCESS;
        }
    }
    else    /* Capture mode */
    {
        VehicleCAN_CFG_REG |= VehicleCAN_ECR_MODE_MASK;

        /* Verify that bit is set */
        if ((VehicleCAN_CFG_REG & VehicleCAN_ECR_MODE_MASK) != 0u)
        {
            result = CYRET_SUCCESS;
        }
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   VehicleCAN_ReadErrorCaptureRegister
********************************************************************************
*
* Summary:
*  This function returns the value of the Error Capture register.
*
* Parameters:
*  None.
*
* Return:
*  The value of the Error Capture register.
*   Bit  Name          Values
*    0    ECR_STATUS    0: The ECR register captured an error or it is a free
*                          running mode
*                       1: The ECR register is armed
*   3:1   ERROR_TYPE    000 : Arbitration loss
*                       001 : Bit Error
*                       010 : Bit Stuffing Error
*                       011 : Acknowledge Error
*                       100 : Form Error
*                       101 : CRC Error
*                       Others : N/A
*    4    TX_MODE       0: No status
*                       1: CAN Controller is the transmitter
*    5    RX_MODE       0: No status
*                       1: CAN Controller is the receiver
*  11:6   BIT           Bit number inside of Field
*  12:16  Field         0x00 : Stopped
*                       0x01 : Synchronize
*                       0x05 : Interframe
*                       0x06 : Bus Idle
*                       0x07 : Start of Frame
*                       0x08 : Arbitration
*                       0x09 : Control
*                       0x0A : Data
*                       0x0B : CRC
*                       0x0C : ACK
*                       0x0D : End of frame
*                       0x10 : Error flag
*                       0x11 : Error echo
*                       0x12 : Error delimiter
*                       0x18 : Overload flag
*                       0x19 : Overload echo
*                       0x1A : Overload delimiter
*                       Others : N/A
*
*******************************************************************************/
uint32 VehicleCAN_ReadErrorCaptureRegister(void)
{
    return (VehicleCAN_ECR_REG);
}


/*******************************************************************************
* FUNCTION NAME:   VehicleCAN_ArmErrorCaptureRegister
********************************************************************************
*
* Summary:
*  This function arms the Error Capture register when the ECR is in the Error
*  Capture mode, by setting the ECR_STATUS bit in the ECR register.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    VehicleCAN_FAIL              The function failed
*
*******************************************************************************/
uint8 VehicleCAN_ArmErrorCaptureRegister(void)
{
    uint8 result = VehicleCAN_FAIL;

    VehicleCAN_ECR_REG |= VehicleCAN_ECR_STATUS_ARM;

    /* Verify that bit is set */
    if ((VehicleCAN_ECR_REG & VehicleCAN_ECR_STATUS_ARM) != 0u)
    {
        result = CYRET_SUCCESS;
    }

    return (result);
}

#endif /* (!(CY_PSOC3 || CY_PSOC5)) */


/* [] END OF FILE */
