/*******************************************************************************
* File Name: PreviousButton.h  
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

#if !defined(CY_PINS_PreviousButton_H) /* Pins PreviousButton_H */
#define CY_PINS_PreviousButton_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PreviousButton_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PreviousButton__PORT == 15 && ((PreviousButton__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PreviousButton_Write(uint8 value);
void    PreviousButton_SetDriveMode(uint8 mode);
uint8   PreviousButton_ReadDataReg(void);
uint8   PreviousButton_Read(void);
void    PreviousButton_SetInterruptMode(uint16 position, uint16 mode);
uint8   PreviousButton_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PreviousButton_SetDriveMode() function.
     *  @{
     */
        #define PreviousButton_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PreviousButton_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PreviousButton_DM_RES_UP          PIN_DM_RES_UP
        #define PreviousButton_DM_RES_DWN         PIN_DM_RES_DWN
        #define PreviousButton_DM_OD_LO           PIN_DM_OD_LO
        #define PreviousButton_DM_OD_HI           PIN_DM_OD_HI
        #define PreviousButton_DM_STRONG          PIN_DM_STRONG
        #define PreviousButton_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PreviousButton_MASK               PreviousButton__MASK
#define PreviousButton_SHIFT              PreviousButton__SHIFT
#define PreviousButton_WIDTH              1u

/* Interrupt constants */
#if defined(PreviousButton__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PreviousButton_SetInterruptMode() function.
     *  @{
     */
        #define PreviousButton_INTR_NONE      (uint16)(0x0000u)
        #define PreviousButton_INTR_RISING    (uint16)(0x0001u)
        #define PreviousButton_INTR_FALLING   (uint16)(0x0002u)
        #define PreviousButton_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PreviousButton_INTR_MASK      (0x01u) 
#endif /* (PreviousButton__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PreviousButton_PS                     (* (reg8 *) PreviousButton__PS)
/* Data Register */
#define PreviousButton_DR                     (* (reg8 *) PreviousButton__DR)
/* Port Number */
#define PreviousButton_PRT_NUM                (* (reg8 *) PreviousButton__PRT) 
/* Connect to Analog Globals */                                                  
#define PreviousButton_AG                     (* (reg8 *) PreviousButton__AG)                       
/* Analog MUX bux enable */
#define PreviousButton_AMUX                   (* (reg8 *) PreviousButton__AMUX) 
/* Bidirectional Enable */                                                        
#define PreviousButton_BIE                    (* (reg8 *) PreviousButton__BIE)
/* Bit-mask for Aliased Register Access */
#define PreviousButton_BIT_MASK               (* (reg8 *) PreviousButton__BIT_MASK)
/* Bypass Enable */
#define PreviousButton_BYP                    (* (reg8 *) PreviousButton__BYP)
/* Port wide control signals */                                                   
#define PreviousButton_CTL                    (* (reg8 *) PreviousButton__CTL)
/* Drive Modes */
#define PreviousButton_DM0                    (* (reg8 *) PreviousButton__DM0) 
#define PreviousButton_DM1                    (* (reg8 *) PreviousButton__DM1)
#define PreviousButton_DM2                    (* (reg8 *) PreviousButton__DM2) 
/* Input Buffer Disable Override */
#define PreviousButton_INP_DIS                (* (reg8 *) PreviousButton__INP_DIS)
/* LCD Common or Segment Drive */
#define PreviousButton_LCD_COM_SEG            (* (reg8 *) PreviousButton__LCD_COM_SEG)
/* Enable Segment LCD */
#define PreviousButton_LCD_EN                 (* (reg8 *) PreviousButton__LCD_EN)
/* Slew Rate Control */
#define PreviousButton_SLW                    (* (reg8 *) PreviousButton__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PreviousButton_PRTDSI__CAPS_SEL       (* (reg8 *) PreviousButton__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PreviousButton_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PreviousButton__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PreviousButton_PRTDSI__OE_SEL0        (* (reg8 *) PreviousButton__PRTDSI__OE_SEL0) 
#define PreviousButton_PRTDSI__OE_SEL1        (* (reg8 *) PreviousButton__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PreviousButton_PRTDSI__OUT_SEL0       (* (reg8 *) PreviousButton__PRTDSI__OUT_SEL0) 
#define PreviousButton_PRTDSI__OUT_SEL1       (* (reg8 *) PreviousButton__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PreviousButton_PRTDSI__SYNC_OUT       (* (reg8 *) PreviousButton__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PreviousButton__SIO_CFG)
    #define PreviousButton_SIO_HYST_EN        (* (reg8 *) PreviousButton__SIO_HYST_EN)
    #define PreviousButton_SIO_REG_HIFREQ     (* (reg8 *) PreviousButton__SIO_REG_HIFREQ)
    #define PreviousButton_SIO_CFG            (* (reg8 *) PreviousButton__SIO_CFG)
    #define PreviousButton_SIO_DIFF           (* (reg8 *) PreviousButton__SIO_DIFF)
#endif /* (PreviousButton__SIO_CFG) */

/* Interrupt Registers */
#if defined(PreviousButton__INTSTAT)
    #define PreviousButton_INTSTAT            (* (reg8 *) PreviousButton__INTSTAT)
    #define PreviousButton_SNAP               (* (reg8 *) PreviousButton__SNAP)
    
	#define PreviousButton_0_INTTYPE_REG 		(* (reg8 *) PreviousButton__0__INTTYPE)
#endif /* (PreviousButton__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PreviousButton_H */


/* [] END OF FILE */
