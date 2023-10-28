/*******************************************************************************
* File Name: PowerEnableSelf.h  
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

#if !defined(CY_PINS_PowerEnableSelf_H) /* Pins PowerEnableSelf_H */
#define CY_PINS_PowerEnableSelf_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PowerEnableSelf_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PowerEnableSelf__PORT == 15 && ((PowerEnableSelf__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PowerEnableSelf_Write(uint8 value);
void    PowerEnableSelf_SetDriveMode(uint8 mode);
uint8   PowerEnableSelf_ReadDataReg(void);
uint8   PowerEnableSelf_Read(void);
void    PowerEnableSelf_SetInterruptMode(uint16 position, uint16 mode);
uint8   PowerEnableSelf_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PowerEnableSelf_SetDriveMode() function.
     *  @{
     */
        #define PowerEnableSelf_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PowerEnableSelf_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PowerEnableSelf_DM_RES_UP          PIN_DM_RES_UP
        #define PowerEnableSelf_DM_RES_DWN         PIN_DM_RES_DWN
        #define PowerEnableSelf_DM_OD_LO           PIN_DM_OD_LO
        #define PowerEnableSelf_DM_OD_HI           PIN_DM_OD_HI
        #define PowerEnableSelf_DM_STRONG          PIN_DM_STRONG
        #define PowerEnableSelf_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PowerEnableSelf_MASK               PowerEnableSelf__MASK
#define PowerEnableSelf_SHIFT              PowerEnableSelf__SHIFT
#define PowerEnableSelf_WIDTH              1u

/* Interrupt constants */
#if defined(PowerEnableSelf__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PowerEnableSelf_SetInterruptMode() function.
     *  @{
     */
        #define PowerEnableSelf_INTR_NONE      (uint16)(0x0000u)
        #define PowerEnableSelf_INTR_RISING    (uint16)(0x0001u)
        #define PowerEnableSelf_INTR_FALLING   (uint16)(0x0002u)
        #define PowerEnableSelf_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PowerEnableSelf_INTR_MASK      (0x01u) 
#endif /* (PowerEnableSelf__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PowerEnableSelf_PS                     (* (reg8 *) PowerEnableSelf__PS)
/* Data Register */
#define PowerEnableSelf_DR                     (* (reg8 *) PowerEnableSelf__DR)
/* Port Number */
#define PowerEnableSelf_PRT_NUM                (* (reg8 *) PowerEnableSelf__PRT) 
/* Connect to Analog Globals */                                                  
#define PowerEnableSelf_AG                     (* (reg8 *) PowerEnableSelf__AG)                       
/* Analog MUX bux enable */
#define PowerEnableSelf_AMUX                   (* (reg8 *) PowerEnableSelf__AMUX) 
/* Bidirectional Enable */                                                        
#define PowerEnableSelf_BIE                    (* (reg8 *) PowerEnableSelf__BIE)
/* Bit-mask for Aliased Register Access */
#define PowerEnableSelf_BIT_MASK               (* (reg8 *) PowerEnableSelf__BIT_MASK)
/* Bypass Enable */
#define PowerEnableSelf_BYP                    (* (reg8 *) PowerEnableSelf__BYP)
/* Port wide control signals */                                                   
#define PowerEnableSelf_CTL                    (* (reg8 *) PowerEnableSelf__CTL)
/* Drive Modes */
#define PowerEnableSelf_DM0                    (* (reg8 *) PowerEnableSelf__DM0) 
#define PowerEnableSelf_DM1                    (* (reg8 *) PowerEnableSelf__DM1)
#define PowerEnableSelf_DM2                    (* (reg8 *) PowerEnableSelf__DM2) 
/* Input Buffer Disable Override */
#define PowerEnableSelf_INP_DIS                (* (reg8 *) PowerEnableSelf__INP_DIS)
/* LCD Common or Segment Drive */
#define PowerEnableSelf_LCD_COM_SEG            (* (reg8 *) PowerEnableSelf__LCD_COM_SEG)
/* Enable Segment LCD */
#define PowerEnableSelf_LCD_EN                 (* (reg8 *) PowerEnableSelf__LCD_EN)
/* Slew Rate Control */
#define PowerEnableSelf_SLW                    (* (reg8 *) PowerEnableSelf__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PowerEnableSelf_PRTDSI__CAPS_SEL       (* (reg8 *) PowerEnableSelf__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PowerEnableSelf_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PowerEnableSelf__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PowerEnableSelf_PRTDSI__OE_SEL0        (* (reg8 *) PowerEnableSelf__PRTDSI__OE_SEL0) 
#define PowerEnableSelf_PRTDSI__OE_SEL1        (* (reg8 *) PowerEnableSelf__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PowerEnableSelf_PRTDSI__OUT_SEL0       (* (reg8 *) PowerEnableSelf__PRTDSI__OUT_SEL0) 
#define PowerEnableSelf_PRTDSI__OUT_SEL1       (* (reg8 *) PowerEnableSelf__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PowerEnableSelf_PRTDSI__SYNC_OUT       (* (reg8 *) PowerEnableSelf__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PowerEnableSelf__SIO_CFG)
    #define PowerEnableSelf_SIO_HYST_EN        (* (reg8 *) PowerEnableSelf__SIO_HYST_EN)
    #define PowerEnableSelf_SIO_REG_HIFREQ     (* (reg8 *) PowerEnableSelf__SIO_REG_HIFREQ)
    #define PowerEnableSelf_SIO_CFG            (* (reg8 *) PowerEnableSelf__SIO_CFG)
    #define PowerEnableSelf_SIO_DIFF           (* (reg8 *) PowerEnableSelf__SIO_DIFF)
#endif /* (PowerEnableSelf__SIO_CFG) */

/* Interrupt Registers */
#if defined(PowerEnableSelf__INTSTAT)
    #define PowerEnableSelf_INTSTAT            (* (reg8 *) PowerEnableSelf__INTSTAT)
    #define PowerEnableSelf_SNAP               (* (reg8 *) PowerEnableSelf__SNAP)
    
	#define PowerEnableSelf_0_INTTYPE_REG 		(* (reg8 *) PowerEnableSelf__0__INTTYPE)
#endif /* (PowerEnableSelf__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PowerEnableSelf_H */


/* [] END OF FILE */
