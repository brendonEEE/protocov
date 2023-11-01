/*******************************************************************************
* File Name: BlueLed.h  
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

#if !defined(CY_PINS_BlueLed_H) /* Pins BlueLed_H */
#define CY_PINS_BlueLed_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "BlueLed_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 BlueLed__PORT == 15 && ((BlueLed__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    BlueLed_Write(uint8 value);
void    BlueLed_SetDriveMode(uint8 mode);
uint8   BlueLed_ReadDataReg(void);
uint8   BlueLed_Read(void);
void    BlueLed_SetInterruptMode(uint16 position, uint16 mode);
uint8   BlueLed_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the BlueLed_SetDriveMode() function.
     *  @{
     */
        #define BlueLed_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define BlueLed_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define BlueLed_DM_RES_UP          PIN_DM_RES_UP
        #define BlueLed_DM_RES_DWN         PIN_DM_RES_DWN
        #define BlueLed_DM_OD_LO           PIN_DM_OD_LO
        #define BlueLed_DM_OD_HI           PIN_DM_OD_HI
        #define BlueLed_DM_STRONG          PIN_DM_STRONG
        #define BlueLed_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define BlueLed_MASK               BlueLed__MASK
#define BlueLed_SHIFT              BlueLed__SHIFT
#define BlueLed_WIDTH              1u

/* Interrupt constants */
#if defined(BlueLed__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BlueLed_SetInterruptMode() function.
     *  @{
     */
        #define BlueLed_INTR_NONE      (uint16)(0x0000u)
        #define BlueLed_INTR_RISING    (uint16)(0x0001u)
        #define BlueLed_INTR_FALLING   (uint16)(0x0002u)
        #define BlueLed_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define BlueLed_INTR_MASK      (0x01u) 
#endif /* (BlueLed__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BlueLed_PS                     (* (reg8 *) BlueLed__PS)
/* Data Register */
#define BlueLed_DR                     (* (reg8 *) BlueLed__DR)
/* Port Number */
#define BlueLed_PRT_NUM                (* (reg8 *) BlueLed__PRT) 
/* Connect to Analog Globals */                                                  
#define BlueLed_AG                     (* (reg8 *) BlueLed__AG)                       
/* Analog MUX bux enable */
#define BlueLed_AMUX                   (* (reg8 *) BlueLed__AMUX) 
/* Bidirectional Enable */                                                        
#define BlueLed_BIE                    (* (reg8 *) BlueLed__BIE)
/* Bit-mask for Aliased Register Access */
#define BlueLed_BIT_MASK               (* (reg8 *) BlueLed__BIT_MASK)
/* Bypass Enable */
#define BlueLed_BYP                    (* (reg8 *) BlueLed__BYP)
/* Port wide control signals */                                                   
#define BlueLed_CTL                    (* (reg8 *) BlueLed__CTL)
/* Drive Modes */
#define BlueLed_DM0                    (* (reg8 *) BlueLed__DM0) 
#define BlueLed_DM1                    (* (reg8 *) BlueLed__DM1)
#define BlueLed_DM2                    (* (reg8 *) BlueLed__DM2) 
/* Input Buffer Disable Override */
#define BlueLed_INP_DIS                (* (reg8 *) BlueLed__INP_DIS)
/* LCD Common or Segment Drive */
#define BlueLed_LCD_COM_SEG            (* (reg8 *) BlueLed__LCD_COM_SEG)
/* Enable Segment LCD */
#define BlueLed_LCD_EN                 (* (reg8 *) BlueLed__LCD_EN)
/* Slew Rate Control */
#define BlueLed_SLW                    (* (reg8 *) BlueLed__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define BlueLed_PRTDSI__CAPS_SEL       (* (reg8 *) BlueLed__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define BlueLed_PRTDSI__DBL_SYNC_IN    (* (reg8 *) BlueLed__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define BlueLed_PRTDSI__OE_SEL0        (* (reg8 *) BlueLed__PRTDSI__OE_SEL0) 
#define BlueLed_PRTDSI__OE_SEL1        (* (reg8 *) BlueLed__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define BlueLed_PRTDSI__OUT_SEL0       (* (reg8 *) BlueLed__PRTDSI__OUT_SEL0) 
#define BlueLed_PRTDSI__OUT_SEL1       (* (reg8 *) BlueLed__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define BlueLed_PRTDSI__SYNC_OUT       (* (reg8 *) BlueLed__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(BlueLed__SIO_CFG)
    #define BlueLed_SIO_HYST_EN        (* (reg8 *) BlueLed__SIO_HYST_EN)
    #define BlueLed_SIO_REG_HIFREQ     (* (reg8 *) BlueLed__SIO_REG_HIFREQ)
    #define BlueLed_SIO_CFG            (* (reg8 *) BlueLed__SIO_CFG)
    #define BlueLed_SIO_DIFF           (* (reg8 *) BlueLed__SIO_DIFF)
#endif /* (BlueLed__SIO_CFG) */

/* Interrupt Registers */
#if defined(BlueLed__INTSTAT)
    #define BlueLed_INTSTAT            (* (reg8 *) BlueLed__INTSTAT)
    #define BlueLed_SNAP               (* (reg8 *) BlueLed__SNAP)
    
	#define BlueLed_0_INTTYPE_REG 		(* (reg8 *) BlueLed__0__INTTYPE)
#endif /* (BlueLed__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_BlueLed_H */


/* [] END OF FILE */
