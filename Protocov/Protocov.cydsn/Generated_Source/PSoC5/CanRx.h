/*******************************************************************************
* File Name: CanRx.h  
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

#if !defined(CY_PINS_CanRx_H) /* Pins CanRx_H */
#define CY_PINS_CanRx_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "CanRx_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 CanRx__PORT == 15 && ((CanRx__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    CanRx_Write(uint8 value);
void    CanRx_SetDriveMode(uint8 mode);
uint8   CanRx_ReadDataReg(void);
uint8   CanRx_Read(void);
void    CanRx_SetInterruptMode(uint16 position, uint16 mode);
uint8   CanRx_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the CanRx_SetDriveMode() function.
     *  @{
     */
        #define CanRx_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define CanRx_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define CanRx_DM_RES_UP          PIN_DM_RES_UP
        #define CanRx_DM_RES_DWN         PIN_DM_RES_DWN
        #define CanRx_DM_OD_LO           PIN_DM_OD_LO
        #define CanRx_DM_OD_HI           PIN_DM_OD_HI
        #define CanRx_DM_STRONG          PIN_DM_STRONG
        #define CanRx_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define CanRx_MASK               CanRx__MASK
#define CanRx_SHIFT              CanRx__SHIFT
#define CanRx_WIDTH              1u

/* Interrupt constants */
#if defined(CanRx__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CanRx_SetInterruptMode() function.
     *  @{
     */
        #define CanRx_INTR_NONE      (uint16)(0x0000u)
        #define CanRx_INTR_RISING    (uint16)(0x0001u)
        #define CanRx_INTR_FALLING   (uint16)(0x0002u)
        #define CanRx_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define CanRx_INTR_MASK      (0x01u) 
#endif /* (CanRx__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CanRx_PS                     (* (reg8 *) CanRx__PS)
/* Data Register */
#define CanRx_DR                     (* (reg8 *) CanRx__DR)
/* Port Number */
#define CanRx_PRT_NUM                (* (reg8 *) CanRx__PRT) 
/* Connect to Analog Globals */                                                  
#define CanRx_AG                     (* (reg8 *) CanRx__AG)                       
/* Analog MUX bux enable */
#define CanRx_AMUX                   (* (reg8 *) CanRx__AMUX) 
/* Bidirectional Enable */                                                        
#define CanRx_BIE                    (* (reg8 *) CanRx__BIE)
/* Bit-mask for Aliased Register Access */
#define CanRx_BIT_MASK               (* (reg8 *) CanRx__BIT_MASK)
/* Bypass Enable */
#define CanRx_BYP                    (* (reg8 *) CanRx__BYP)
/* Port wide control signals */                                                   
#define CanRx_CTL                    (* (reg8 *) CanRx__CTL)
/* Drive Modes */
#define CanRx_DM0                    (* (reg8 *) CanRx__DM0) 
#define CanRx_DM1                    (* (reg8 *) CanRx__DM1)
#define CanRx_DM2                    (* (reg8 *) CanRx__DM2) 
/* Input Buffer Disable Override */
#define CanRx_INP_DIS                (* (reg8 *) CanRx__INP_DIS)
/* LCD Common or Segment Drive */
#define CanRx_LCD_COM_SEG            (* (reg8 *) CanRx__LCD_COM_SEG)
/* Enable Segment LCD */
#define CanRx_LCD_EN                 (* (reg8 *) CanRx__LCD_EN)
/* Slew Rate Control */
#define CanRx_SLW                    (* (reg8 *) CanRx__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define CanRx_PRTDSI__CAPS_SEL       (* (reg8 *) CanRx__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define CanRx_PRTDSI__DBL_SYNC_IN    (* (reg8 *) CanRx__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define CanRx_PRTDSI__OE_SEL0        (* (reg8 *) CanRx__PRTDSI__OE_SEL0) 
#define CanRx_PRTDSI__OE_SEL1        (* (reg8 *) CanRx__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define CanRx_PRTDSI__OUT_SEL0       (* (reg8 *) CanRx__PRTDSI__OUT_SEL0) 
#define CanRx_PRTDSI__OUT_SEL1       (* (reg8 *) CanRx__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define CanRx_PRTDSI__SYNC_OUT       (* (reg8 *) CanRx__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(CanRx__SIO_CFG)
    #define CanRx_SIO_HYST_EN        (* (reg8 *) CanRx__SIO_HYST_EN)
    #define CanRx_SIO_REG_HIFREQ     (* (reg8 *) CanRx__SIO_REG_HIFREQ)
    #define CanRx_SIO_CFG            (* (reg8 *) CanRx__SIO_CFG)
    #define CanRx_SIO_DIFF           (* (reg8 *) CanRx__SIO_DIFF)
#endif /* (CanRx__SIO_CFG) */

/* Interrupt Registers */
#if defined(CanRx__INTSTAT)
    #define CanRx_INTSTAT            (* (reg8 *) CanRx__INTSTAT)
    #define CanRx_SNAP               (* (reg8 *) CanRx__SNAP)
    
	#define CanRx_0_INTTYPE_REG 		(* (reg8 *) CanRx__0__INTTYPE)
#endif /* (CanRx__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_CanRx_H */


/* [] END OF FILE */
