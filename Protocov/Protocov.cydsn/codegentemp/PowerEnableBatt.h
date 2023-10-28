/*******************************************************************************
* File Name: PowerEnableBatt.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_PowerEnableBatt_H) /* Pins PowerEnableBatt_H */
#define CY_PINS_PowerEnableBatt_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PowerEnableBatt_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PowerEnableBatt__PORT == 15 && ((PowerEnableBatt__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PowerEnableBatt_Write(uint8 value);
void    PowerEnableBatt_SetDriveMode(uint8 mode);
uint8   PowerEnableBatt_ReadDataReg(void);
uint8   PowerEnableBatt_Read(void);
void    PowerEnableBatt_SetInterruptMode(uint16 position, uint16 mode);
uint8   PowerEnableBatt_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PowerEnableBatt_SetDriveMode() function.
     *  @{
     */
        #define PowerEnableBatt_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PowerEnableBatt_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PowerEnableBatt_DM_RES_UP          PIN_DM_RES_UP
        #define PowerEnableBatt_DM_RES_DWN         PIN_DM_RES_DWN
        #define PowerEnableBatt_DM_OD_LO           PIN_DM_OD_LO
        #define PowerEnableBatt_DM_OD_HI           PIN_DM_OD_HI
        #define PowerEnableBatt_DM_STRONG          PIN_DM_STRONG
        #define PowerEnableBatt_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PowerEnableBatt_MASK               PowerEnableBatt__MASK
#define PowerEnableBatt_SHIFT              PowerEnableBatt__SHIFT
#define PowerEnableBatt_WIDTH              1u

/* Interrupt constants */
#if defined(PowerEnableBatt__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PowerEnableBatt_SetInterruptMode() function.
     *  @{
     */
        #define PowerEnableBatt_INTR_NONE      (uint16)(0x0000u)
        #define PowerEnableBatt_INTR_RISING    (uint16)(0x0001u)
        #define PowerEnableBatt_INTR_FALLING   (uint16)(0x0002u)
        #define PowerEnableBatt_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PowerEnableBatt_INTR_MASK      (0x01u) 
#endif /* (PowerEnableBatt__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PowerEnableBatt_PS                     (* (reg8 *) PowerEnableBatt__PS)
/* Data Register */
#define PowerEnableBatt_DR                     (* (reg8 *) PowerEnableBatt__DR)
/* Port Number */
#define PowerEnableBatt_PRT_NUM                (* (reg8 *) PowerEnableBatt__PRT) 
/* Connect to Analog Globals */                                                  
#define PowerEnableBatt_AG                     (* (reg8 *) PowerEnableBatt__AG)                       
/* Analog MUX bux enable */
#define PowerEnableBatt_AMUX                   (* (reg8 *) PowerEnableBatt__AMUX) 
/* Bidirectional Enable */                                                        
#define PowerEnableBatt_BIE                    (* (reg8 *) PowerEnableBatt__BIE)
/* Bit-mask for Aliased Register Access */
#define PowerEnableBatt_BIT_MASK               (* (reg8 *) PowerEnableBatt__BIT_MASK)
/* Bypass Enable */
#define PowerEnableBatt_BYP                    (* (reg8 *) PowerEnableBatt__BYP)
/* Port wide control signals */                                                   
#define PowerEnableBatt_CTL                    (* (reg8 *) PowerEnableBatt__CTL)
/* Drive Modes */
#define PowerEnableBatt_DM0                    (* (reg8 *) PowerEnableBatt__DM0) 
#define PowerEnableBatt_DM1                    (* (reg8 *) PowerEnableBatt__DM1)
#define PowerEnableBatt_DM2                    (* (reg8 *) PowerEnableBatt__DM2) 
/* Input Buffer Disable Override */
#define PowerEnableBatt_INP_DIS                (* (reg8 *) PowerEnableBatt__INP_DIS)
/* LCD Common or Segment Drive */
#define PowerEnableBatt_LCD_COM_SEG            (* (reg8 *) PowerEnableBatt__LCD_COM_SEG)
/* Enable Segment LCD */
#define PowerEnableBatt_LCD_EN                 (* (reg8 *) PowerEnableBatt__LCD_EN)
/* Slew Rate Control */
#define PowerEnableBatt_SLW                    (* (reg8 *) PowerEnableBatt__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PowerEnableBatt_PRTDSI__CAPS_SEL       (* (reg8 *) PowerEnableBatt__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PowerEnableBatt_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PowerEnableBatt__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PowerEnableBatt_PRTDSI__OE_SEL0        (* (reg8 *) PowerEnableBatt__PRTDSI__OE_SEL0) 
#define PowerEnableBatt_PRTDSI__OE_SEL1        (* (reg8 *) PowerEnableBatt__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PowerEnableBatt_PRTDSI__OUT_SEL0       (* (reg8 *) PowerEnableBatt__PRTDSI__OUT_SEL0) 
#define PowerEnableBatt_PRTDSI__OUT_SEL1       (* (reg8 *) PowerEnableBatt__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PowerEnableBatt_PRTDSI__SYNC_OUT       (* (reg8 *) PowerEnableBatt__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PowerEnableBatt__SIO_CFG)
    #define PowerEnableBatt_SIO_HYST_EN        (* (reg8 *) PowerEnableBatt__SIO_HYST_EN)
    #define PowerEnableBatt_SIO_REG_HIFREQ     (* (reg8 *) PowerEnableBatt__SIO_REG_HIFREQ)
    #define PowerEnableBatt_SIO_CFG            (* (reg8 *) PowerEnableBatt__SIO_CFG)
    #define PowerEnableBatt_SIO_DIFF           (* (reg8 *) PowerEnableBatt__SIO_DIFF)
#endif /* (PowerEnableBatt__SIO_CFG) */

/* Interrupt Registers */
#if defined(PowerEnableBatt__INTSTAT)
    #define PowerEnableBatt_INTSTAT            (* (reg8 *) PowerEnableBatt__INTSTAT)
    #define PowerEnableBatt_SNAP               (* (reg8 *) PowerEnableBatt__SNAP)
    
	#define PowerEnableBatt_0_INTTYPE_REG 		(* (reg8 *) PowerEnableBatt__0__INTTYPE)
#endif /* (PowerEnableBatt__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PowerEnableBatt_H */


/* [] END OF FILE */
