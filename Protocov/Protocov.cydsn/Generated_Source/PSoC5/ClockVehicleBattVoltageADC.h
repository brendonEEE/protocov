/*******************************************************************************
* File Name: ClockVehicleBattVoltageADC.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_ClockVehicleBattVoltageADC_H)
#define CY_CLOCK_ClockVehicleBattVoltageADC_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void ClockVehicleBattVoltageADC_Start(void) ;
void ClockVehicleBattVoltageADC_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void ClockVehicleBattVoltageADC_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void ClockVehicleBattVoltageADC_StandbyPower(uint8 state) ;
void ClockVehicleBattVoltageADC_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 ClockVehicleBattVoltageADC_GetDividerRegister(void) ;
void ClockVehicleBattVoltageADC_SetModeRegister(uint8 modeBitMask) ;
void ClockVehicleBattVoltageADC_ClearModeRegister(uint8 modeBitMask) ;
uint8 ClockVehicleBattVoltageADC_GetModeRegister(void) ;
void ClockVehicleBattVoltageADC_SetSourceRegister(uint8 clkSource) ;
uint8 ClockVehicleBattVoltageADC_GetSourceRegister(void) ;
#if defined(ClockVehicleBattVoltageADC__CFG3)
void ClockVehicleBattVoltageADC_SetPhaseRegister(uint8 clkPhase) ;
uint8 ClockVehicleBattVoltageADC_GetPhaseRegister(void) ;
#endif /* defined(ClockVehicleBattVoltageADC__CFG3) */

#define ClockVehicleBattVoltageADC_Enable()                       ClockVehicleBattVoltageADC_Start()
#define ClockVehicleBattVoltageADC_Disable()                      ClockVehicleBattVoltageADC_Stop()
#define ClockVehicleBattVoltageADC_SetDivider(clkDivider)         ClockVehicleBattVoltageADC_SetDividerRegister(clkDivider, 1u)
#define ClockVehicleBattVoltageADC_SetDividerValue(clkDivider)    ClockVehicleBattVoltageADC_SetDividerRegister((clkDivider) - 1u, 1u)
#define ClockVehicleBattVoltageADC_SetMode(clkMode)               ClockVehicleBattVoltageADC_SetModeRegister(clkMode)
#define ClockVehicleBattVoltageADC_SetSource(clkSource)           ClockVehicleBattVoltageADC_SetSourceRegister(clkSource)
#if defined(ClockVehicleBattVoltageADC__CFG3)
#define ClockVehicleBattVoltageADC_SetPhase(clkPhase)             ClockVehicleBattVoltageADC_SetPhaseRegister(clkPhase)
#define ClockVehicleBattVoltageADC_SetPhaseValue(clkPhase)        ClockVehicleBattVoltageADC_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(ClockVehicleBattVoltageADC__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define ClockVehicleBattVoltageADC_CLKEN              (* (reg8 *) ClockVehicleBattVoltageADC__PM_ACT_CFG)
#define ClockVehicleBattVoltageADC_CLKEN_PTR          ((reg8 *) ClockVehicleBattVoltageADC__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define ClockVehicleBattVoltageADC_CLKSTBY            (* (reg8 *) ClockVehicleBattVoltageADC__PM_STBY_CFG)
#define ClockVehicleBattVoltageADC_CLKSTBY_PTR        ((reg8 *) ClockVehicleBattVoltageADC__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define ClockVehicleBattVoltageADC_DIV_LSB            (* (reg8 *) ClockVehicleBattVoltageADC__CFG0)
#define ClockVehicleBattVoltageADC_DIV_LSB_PTR        ((reg8 *) ClockVehicleBattVoltageADC__CFG0)
#define ClockVehicleBattVoltageADC_DIV_PTR            ((reg16 *) ClockVehicleBattVoltageADC__CFG0)

/* Clock MSB divider configuration register. */
#define ClockVehicleBattVoltageADC_DIV_MSB            (* (reg8 *) ClockVehicleBattVoltageADC__CFG1)
#define ClockVehicleBattVoltageADC_DIV_MSB_PTR        ((reg8 *) ClockVehicleBattVoltageADC__CFG1)

/* Mode and source configuration register */
#define ClockVehicleBattVoltageADC_MOD_SRC            (* (reg8 *) ClockVehicleBattVoltageADC__CFG2)
#define ClockVehicleBattVoltageADC_MOD_SRC_PTR        ((reg8 *) ClockVehicleBattVoltageADC__CFG2)

#if defined(ClockVehicleBattVoltageADC__CFG3)
/* Analog clock phase configuration register */
#define ClockVehicleBattVoltageADC_PHASE              (* (reg8 *) ClockVehicleBattVoltageADC__CFG3)
#define ClockVehicleBattVoltageADC_PHASE_PTR          ((reg8 *) ClockVehicleBattVoltageADC__CFG3)
#endif /* defined(ClockVehicleBattVoltageADC__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define ClockVehicleBattVoltageADC_CLKEN_MASK         ClockVehicleBattVoltageADC__PM_ACT_MSK
#define ClockVehicleBattVoltageADC_CLKSTBY_MASK       ClockVehicleBattVoltageADC__PM_STBY_MSK

/* CFG2 field masks */
#define ClockVehicleBattVoltageADC_SRC_SEL_MSK        ClockVehicleBattVoltageADC__CFG2_SRC_SEL_MASK
#define ClockVehicleBattVoltageADC_MODE_MASK          (~(ClockVehicleBattVoltageADC_SRC_SEL_MSK))

#if defined(ClockVehicleBattVoltageADC__CFG3)
/* CFG3 phase mask */
#define ClockVehicleBattVoltageADC_PHASE_MASK         ClockVehicleBattVoltageADC__CFG3_PHASE_DLY_MASK
#endif /* defined(ClockVehicleBattVoltageADC__CFG3) */

#endif /* CY_CLOCK_ClockVehicleBattVoltageADC_H */


/* [] END OF FILE */
