/*******************************************************************************
* File Name: PowerEnableBatt.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_PowerEnableBatt_ALIASES_H) /* Pins PowerEnableBatt_ALIASES_H */
#define CY_PINS_PowerEnableBatt_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define PowerEnableBatt_0			(PowerEnableBatt__0__PC)
#define PowerEnableBatt_0_INTR	((uint16)((uint16)0x0001u << PowerEnableBatt__0__SHIFT))

#define PowerEnableBatt_INTR_ALL	 ((uint16)(PowerEnableBatt_0_INTR))

#endif /* End Pins PowerEnableBatt_ALIASES_H */


/* [] END OF FILE */
