/*******************************************************************************
* File Name: blueLed.h  
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

#if !defined(CY_PINS_blueLed_H) /* Pins blueLed_H */
#define CY_PINS_blueLed_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "blueLed_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 blueLed__PORT == 15 && ((blueLed__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    blueLed_Write(uint8 value);
void    blueLed_SetDriveMode(uint8 mode);
uint8   blueLed_ReadDataReg(void);
uint8   blueLed_Read(void);
void    blueLed_SetInterruptMode(uint16 position, uint16 mode);
uint8   blueLed_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the blueLed_SetDriveMode() function.
     *  @{
     */
        #define blueLed_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define blueLed_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define blueLed_DM_RES_UP          PIN_DM_RES_UP
        #define blueLed_DM_RES_DWN         PIN_DM_RES_DWN
        #define blueLed_DM_OD_LO           PIN_DM_OD_LO
        #define blueLed_DM_OD_HI           PIN_DM_OD_HI
        #define blueLed_DM_STRONG          PIN_DM_STRONG
        #define blueLed_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define blueLed_MASK               blueLed__MASK
#define blueLed_SHIFT              blueLed__SHIFT
#define blueLed_WIDTH              1u

/* Interrupt constants */
#if defined(blueLed__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in blueLed_SetInterruptMode() function.
     *  @{
     */
        #define blueLed_INTR_NONE      (uint16)(0x0000u)
        #define blueLed_INTR_RISING    (uint16)(0x0001u)
        #define blueLed_INTR_FALLING   (uint16)(0x0002u)
        #define blueLed_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define blueLed_INTR_MASK      (0x01u) 
#endif /* (blueLed__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define blueLed_PS                     (* (reg8 *) blueLed__PS)
/* Data Register */
#define blueLed_DR                     (* (reg8 *) blueLed__DR)
/* Port Number */
#define blueLed_PRT_NUM                (* (reg8 *) blueLed__PRT) 
/* Connect to Analog Globals */                                                  
#define blueLed_AG                     (* (reg8 *) blueLed__AG)                       
/* Analog MUX bux enable */
#define blueLed_AMUX                   (* (reg8 *) blueLed__AMUX) 
/* Bidirectional Enable */                                                        
#define blueLed_BIE                    (* (reg8 *) blueLed__BIE)
/* Bit-mask for Aliased Register Access */
#define blueLed_BIT_MASK               (* (reg8 *) blueLed__BIT_MASK)
/* Bypass Enable */
#define blueLed_BYP                    (* (reg8 *) blueLed__BYP)
/* Port wide control signals */                                                   
#define blueLed_CTL                    (* (reg8 *) blueLed__CTL)
/* Drive Modes */
#define blueLed_DM0                    (* (reg8 *) blueLed__DM0) 
#define blueLed_DM1                    (* (reg8 *) blueLed__DM1)
#define blueLed_DM2                    (* (reg8 *) blueLed__DM2) 
/* Input Buffer Disable Override */
#define blueLed_INP_DIS                (* (reg8 *) blueLed__INP_DIS)
/* LCD Common or Segment Drive */
#define blueLed_LCD_COM_SEG            (* (reg8 *) blueLed__LCD_COM_SEG)
/* Enable Segment LCD */
#define blueLed_LCD_EN                 (* (reg8 *) blueLed__LCD_EN)
/* Slew Rate Control */
#define blueLed_SLW                    (* (reg8 *) blueLed__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define blueLed_PRTDSI__CAPS_SEL       (* (reg8 *) blueLed__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define blueLed_PRTDSI__DBL_SYNC_IN    (* (reg8 *) blueLed__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define blueLed_PRTDSI__OE_SEL0        (* (reg8 *) blueLed__PRTDSI__OE_SEL0) 
#define blueLed_PRTDSI__OE_SEL1        (* (reg8 *) blueLed__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define blueLed_PRTDSI__OUT_SEL0       (* (reg8 *) blueLed__PRTDSI__OUT_SEL0) 
#define blueLed_PRTDSI__OUT_SEL1       (* (reg8 *) blueLed__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define blueLed_PRTDSI__SYNC_OUT       (* (reg8 *) blueLed__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(blueLed__SIO_CFG)
    #define blueLed_SIO_HYST_EN        (* (reg8 *) blueLed__SIO_HYST_EN)
    #define blueLed_SIO_REG_HIFREQ     (* (reg8 *) blueLed__SIO_REG_HIFREQ)
    #define blueLed_SIO_CFG            (* (reg8 *) blueLed__SIO_CFG)
    #define blueLed_SIO_DIFF           (* (reg8 *) blueLed__SIO_DIFF)
#endif /* (blueLed__SIO_CFG) */

/* Interrupt Registers */
#if defined(blueLed__INTSTAT)
    #define blueLed_INTSTAT            (* (reg8 *) blueLed__INTSTAT)
    #define blueLed_SNAP               (* (reg8 *) blueLed__SNAP)
    
	#define blueLed_0_INTTYPE_REG 		(* (reg8 *) blueLed__0__INTTYPE)
#endif /* (blueLed__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_blueLed_H */


/* [] END OF FILE */
