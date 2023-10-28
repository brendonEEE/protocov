/*******************************************************************************
* File Name: IntBluetoothUART.h
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
#if !defined(CY_ISR_IntBluetoothUART_H)
#define CY_ISR_IntBluetoothUART_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void IntBluetoothUART_Start(void);
void IntBluetoothUART_StartEx(cyisraddress address);
void IntBluetoothUART_Stop(void);

CY_ISR_PROTO(IntBluetoothUART_Interrupt);

void IntBluetoothUART_SetVector(cyisraddress address);
cyisraddress IntBluetoothUART_GetVector(void);

void IntBluetoothUART_SetPriority(uint8 priority);
uint8 IntBluetoothUART_GetPriority(void);

void IntBluetoothUART_Enable(void);
uint8 IntBluetoothUART_GetState(void);
void IntBluetoothUART_Disable(void);

void IntBluetoothUART_SetPending(void);
void IntBluetoothUART_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the IntBluetoothUART ISR. */
#define IntBluetoothUART_INTC_VECTOR            ((reg32 *) IntBluetoothUART__INTC_VECT)

/* Address of the IntBluetoothUART ISR priority. */
#define IntBluetoothUART_INTC_PRIOR             ((reg8 *) IntBluetoothUART__INTC_PRIOR_REG)

/* Priority of the IntBluetoothUART interrupt. */
#define IntBluetoothUART_INTC_PRIOR_NUMBER      IntBluetoothUART__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable IntBluetoothUART interrupt. */
#define IntBluetoothUART_INTC_SET_EN            ((reg32 *) IntBluetoothUART__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the IntBluetoothUART interrupt. */
#define IntBluetoothUART_INTC_CLR_EN            ((reg32 *) IntBluetoothUART__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the IntBluetoothUART interrupt state to pending. */
#define IntBluetoothUART_INTC_SET_PD            ((reg32 *) IntBluetoothUART__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the IntBluetoothUART interrupt. */
#define IntBluetoothUART_INTC_CLR_PD            ((reg32 *) IntBluetoothUART__INTC_CLR_PD_REG)


#endif /* CY_ISR_IntBluetoothUART_H */


/* [] END OF FILE */
