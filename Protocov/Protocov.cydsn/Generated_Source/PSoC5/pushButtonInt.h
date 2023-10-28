/*******************************************************************************
* File Name: pushButtonInt.h
* Version 1.70
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
#if !defined(CY_ISR_pushButtonInt_H)
#define CY_ISR_pushButtonInt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void pushButtonInt_Start(void);
void pushButtonInt_StartEx(cyisraddress address);
void pushButtonInt_Stop(void);

CY_ISR_PROTO(pushButtonInt_Interrupt);

void pushButtonInt_SetVector(cyisraddress address);
cyisraddress pushButtonInt_GetVector(void);

void pushButtonInt_SetPriority(uint8 priority);
uint8 pushButtonInt_GetPriority(void);

void pushButtonInt_Enable(void);
uint8 pushButtonInt_GetState(void);
void pushButtonInt_Disable(void);

void pushButtonInt_SetPending(void);
void pushButtonInt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the pushButtonInt ISR. */
#define pushButtonInt_INTC_VECTOR            ((reg32 *) pushButtonInt__INTC_VECT)

/* Address of the pushButtonInt ISR priority. */
#define pushButtonInt_INTC_PRIOR             ((reg8 *) pushButtonInt__INTC_PRIOR_REG)

/* Priority of the pushButtonInt interrupt. */
#define pushButtonInt_INTC_PRIOR_NUMBER      pushButtonInt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable pushButtonInt interrupt. */
#define pushButtonInt_INTC_SET_EN            ((reg32 *) pushButtonInt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the pushButtonInt interrupt. */
#define pushButtonInt_INTC_CLR_EN            ((reg32 *) pushButtonInt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the pushButtonInt interrupt state to pending. */
#define pushButtonInt_INTC_SET_PD            ((reg32 *) pushButtonInt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the pushButtonInt interrupt. */
#define pushButtonInt_INTC_CLR_PD            ((reg32 *) pushButtonInt__INTC_CLR_PD_REG)


#endif /* CY_ISR_pushButtonInt_H */


/* [] END OF FILE */
