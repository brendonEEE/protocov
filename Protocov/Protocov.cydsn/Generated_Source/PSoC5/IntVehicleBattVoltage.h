/*******************************************************************************
* File Name: IntVehicleBattVoltage.h
* Version 1.71
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_IntVehicleBattVoltage_H)
#define CY_ISR_IntVehicleBattVoltage_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void IntVehicleBattVoltage_Start(void);
void IntVehicleBattVoltage_StartEx(cyisraddress address);
void IntVehicleBattVoltage_Stop(void);

CY_ISR_PROTO(IntVehicleBattVoltage_Interrupt);

void IntVehicleBattVoltage_SetVector(cyisraddress address);
cyisraddress IntVehicleBattVoltage_GetVector(void);

void IntVehicleBattVoltage_SetPriority(uint8 priority);
uint8 IntVehicleBattVoltage_GetPriority(void);

void IntVehicleBattVoltage_Enable(void);
uint8 IntVehicleBattVoltage_GetState(void);
void IntVehicleBattVoltage_Disable(void);

void IntVehicleBattVoltage_SetPending(void);
void IntVehicleBattVoltage_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the IntVehicleBattVoltage ISR. */
#define IntVehicleBattVoltage_INTC_VECTOR            ((reg32 *) IntVehicleBattVoltage__INTC_VECT)

/* Address of the IntVehicleBattVoltage ISR priority. */
#define IntVehicleBattVoltage_INTC_PRIOR             ((reg8 *) IntVehicleBattVoltage__INTC_PRIOR_REG)

/* Priority of the IntVehicleBattVoltage interrupt. */
#define IntVehicleBattVoltage_INTC_PRIOR_NUMBER      IntVehicleBattVoltage__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable IntVehicleBattVoltage interrupt. */
#define IntVehicleBattVoltage_INTC_SET_EN            ((reg32 *) IntVehicleBattVoltage__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the IntVehicleBattVoltage interrupt. */
#define IntVehicleBattVoltage_INTC_CLR_EN            ((reg32 *) IntVehicleBattVoltage__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the IntVehicleBattVoltage interrupt state to pending. */
#define IntVehicleBattVoltage_INTC_SET_PD            ((reg32 *) IntVehicleBattVoltage__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the IntVehicleBattVoltage interrupt. */
#define IntVehicleBattVoltage_INTC_CLR_PD            ((reg32 *) IntVehicleBattVoltage__INTC_CLR_PD_REG)


#endif /* CY_ISR_IntVehicleBattVoltage_H */


/* [] END OF FILE */
