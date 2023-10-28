/*******************************************************************************
* File Name: CanTx.h  
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

#if !defined(CY_PINS_CanTx_H) /* Pins CanTx_H */
#define CY_PINS_CanTx_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "CanTx_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 CanTx__PORT == 15 && ((CanTx__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    CanTx_Write(uint8 value);
void    CanTx_SetDriveMode(uint8 mode);
uint8   CanTx_ReadDataReg(void);
uint8   CanTx_Read(void);
void    CanTx_SetInterruptMode(uint16 position, uint16 mode);
uint8   CanTx_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the CanTx_SetDriveMode() function.
     *  @{
     */
        #define CanTx_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define CanTx_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define CanTx_DM_RES_UP          PIN_DM_RES_UP
        #define CanTx_DM_RES_DWN         PIN_DM_RES_DWN
        #define CanTx_DM_OD_LO           PIN_DM_OD_LO
        #define CanTx_DM_OD_HI           PIN_DM_OD_HI
        #define CanTx_DM_STRONG          PIN_DM_STRONG
        #define CanTx_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define CanTx_MASK               CanTx__MASK
#define CanTx_SHIFT              CanTx__SHIFT
#define CanTx_WIDTH              1u

/* Interrupt constants */
#if defined(CanTx__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CanTx_SetInterruptMode() function.
     *  @{
     */
        #define CanTx_INTR_NONE      (uint16)(0x0000u)
        #define CanTx_INTR_RISING    (uint16)(0x0001u)
        #define CanTx_INTR_FALLING   (uint16)(0x0002u)
        #define CanTx_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define CanTx_INTR_MASK      (0x01u) 
#endif /* (CanTx__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CanTx_PS                     (* (reg8 *) CanTx__PS)
/* Data Register */
#define CanTx_DR                     (* (reg8 *) CanTx__DR)
/* Port Number */
#define CanTx_PRT_NUM                (* (reg8 *) CanTx__PRT) 
/* Connect to Analog Globals */                                                  
#define CanTx_AG                     (* (reg8 *) CanTx__AG)                       
/* Analog MUX bux enable */
#define CanTx_AMUX                   (* (reg8 *) CanTx__AMUX) 
/* Bidirectional Enable */                                                        
#define CanTx_BIE                    (* (reg8 *) CanTx__BIE)
/* Bit-mask for Aliased Register Access */
#define CanTx_BIT_MASK               (* (reg8 *) CanTx__BIT_MASK)
/* Bypass Enable */
#define CanTx_BYP                    (* (reg8 *) CanTx__BYP)
/* Port wide control signals */                                                   
#define CanTx_CTL                    (* (reg8 *) CanTx__CTL)
/* Drive Modes */
#define CanTx_DM0                    (* (reg8 *) CanTx__DM0) 
#define CanTx_DM1                    (* (reg8 *) CanTx__DM1)
#define CanTx_DM2                    (* (reg8 *) CanTx__DM2) 
/* Input Buffer Disable Override */
#define CanTx_INP_DIS                (* (reg8 *) CanTx__INP_DIS)
/* LCD Common or Segment Drive */
#define CanTx_LCD_COM_SEG            (* (reg8 *) CanTx__LCD_COM_SEG)
/* Enable Segment LCD */
#define CanTx_LCD_EN                 (* (reg8 *) CanTx__LCD_EN)
/* Slew Rate Control */
#define CanTx_SLW                    (* (reg8 *) CanTx__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define CanTx_PRTDSI__CAPS_SEL       (* (reg8 *) CanTx__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define CanTx_PRTDSI__DBL_SYNC_IN    (* (reg8 *) CanTx__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define CanTx_PRTDSI__OE_SEL0        (* (reg8 *) CanTx__PRTDSI__OE_SEL0) 
#define CanTx_PRTDSI__OE_SEL1        (* (reg8 *) CanTx__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define CanTx_PRTDSI__OUT_SEL0       (* (reg8 *) CanTx__PRTDSI__OUT_SEL0) 
#define CanTx_PRTDSI__OUT_SEL1       (* (reg8 *) CanTx__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define CanTx_PRTDSI__SYNC_OUT       (* (reg8 *) CanTx__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(CanTx__SIO_CFG)
    #define CanTx_SIO_HYST_EN        (* (reg8 *) CanTx__SIO_HYST_EN)
    #define CanTx_SIO_REG_HIFREQ     (* (reg8 *) CanTx__SIO_REG_HIFREQ)
    #define CanTx_SIO_CFG            (* (reg8 *) CanTx__SIO_CFG)
    #define CanTx_SIO_DIFF           (* (reg8 *) CanTx__SIO_DIFF)
#endif /* (CanTx__SIO_CFG) */

/* Interrupt Registers */
#if defined(CanTx__INTSTAT)
    #define CanTx_INTSTAT            (* (reg8 *) CanTx__INTSTAT)
    #define CanTx_SNAP               (* (reg8 *) CanTx__SNAP)
    
	#define CanTx_0_INTTYPE_REG 		(* (reg8 *) CanTx__0__INTTYPE)
#endif /* (CanTx__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_CanTx_H */


/* [] END OF FILE */
