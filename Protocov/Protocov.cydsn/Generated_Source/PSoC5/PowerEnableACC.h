/*******************************************************************************
* File Name: PowerEnableACC.h  
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

#if !defined(CY_PINS_PowerEnableACC_H) /* Pins PowerEnableACC_H */
#define CY_PINS_PowerEnableACC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PowerEnableACC_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PowerEnableACC__PORT == 15 && ((PowerEnableACC__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PowerEnableACC_Write(uint8 value);
void    PowerEnableACC_SetDriveMode(uint8 mode);
uint8   PowerEnableACC_ReadDataReg(void);
uint8   PowerEnableACC_Read(void);
void    PowerEnableACC_SetInterruptMode(uint16 position, uint16 mode);
uint8   PowerEnableACC_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PowerEnableACC_SetDriveMode() function.
     *  @{
     */
        #define PowerEnableACC_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PowerEnableACC_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PowerEnableACC_DM_RES_UP          PIN_DM_RES_UP
        #define PowerEnableACC_DM_RES_DWN         PIN_DM_RES_DWN
        #define PowerEnableACC_DM_OD_LO           PIN_DM_OD_LO
        #define PowerEnableACC_DM_OD_HI           PIN_DM_OD_HI
        #define PowerEnableACC_DM_STRONG          PIN_DM_STRONG
        #define PowerEnableACC_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PowerEnableACC_MASK               PowerEnableACC__MASK
#define PowerEnableACC_SHIFT              PowerEnableACC__SHIFT
#define PowerEnableACC_WIDTH              1u

/* Interrupt constants */
#if defined(PowerEnableACC__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PowerEnableACC_SetInterruptMode() function.
     *  @{
     */
        #define PowerEnableACC_INTR_NONE      (uint16)(0x0000u)
        #define PowerEnableACC_INTR_RISING    (uint16)(0x0001u)
        #define PowerEnableACC_INTR_FALLING   (uint16)(0x0002u)
        #define PowerEnableACC_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PowerEnableACC_INTR_MASK      (0x01u) 
#endif /* (PowerEnableACC__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PowerEnableACC_PS                     (* (reg8 *) PowerEnableACC__PS)
/* Data Register */
#define PowerEnableACC_DR                     (* (reg8 *) PowerEnableACC__DR)
/* Port Number */
#define PowerEnableACC_PRT_NUM                (* (reg8 *) PowerEnableACC__PRT) 
/* Connect to Analog Globals */                                                  
#define PowerEnableACC_AG                     (* (reg8 *) PowerEnableACC__AG)                       
/* Analog MUX bux enable */
#define PowerEnableACC_AMUX                   (* (reg8 *) PowerEnableACC__AMUX) 
/* Bidirectional Enable */                                                        
#define PowerEnableACC_BIE                    (* (reg8 *) PowerEnableACC__BIE)
/* Bit-mask for Aliased Register Access */
#define PowerEnableACC_BIT_MASK               (* (reg8 *) PowerEnableACC__BIT_MASK)
/* Bypass Enable */
#define PowerEnableACC_BYP                    (* (reg8 *) PowerEnableACC__BYP)
/* Port wide control signals */                                                   
#define PowerEnableACC_CTL                    (* (reg8 *) PowerEnableACC__CTL)
/* Drive Modes */
#define PowerEnableACC_DM0                    (* (reg8 *) PowerEnableACC__DM0) 
#define PowerEnableACC_DM1                    (* (reg8 *) PowerEnableACC__DM1)
#define PowerEnableACC_DM2                    (* (reg8 *) PowerEnableACC__DM2) 
/* Input Buffer Disable Override */
#define PowerEnableACC_INP_DIS                (* (reg8 *) PowerEnableACC__INP_DIS)
/* LCD Common or Segment Drive */
#define PowerEnableACC_LCD_COM_SEG            (* (reg8 *) PowerEnableACC__LCD_COM_SEG)
/* Enable Segment LCD */
#define PowerEnableACC_LCD_EN                 (* (reg8 *) PowerEnableACC__LCD_EN)
/* Slew Rate Control */
#define PowerEnableACC_SLW                    (* (reg8 *) PowerEnableACC__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PowerEnableACC_PRTDSI__CAPS_SEL       (* (reg8 *) PowerEnableACC__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PowerEnableACC_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PowerEnableACC__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PowerEnableACC_PRTDSI__OE_SEL0        (* (reg8 *) PowerEnableACC__PRTDSI__OE_SEL0) 
#define PowerEnableACC_PRTDSI__OE_SEL1        (* (reg8 *) PowerEnableACC__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PowerEnableACC_PRTDSI__OUT_SEL0       (* (reg8 *) PowerEnableACC__PRTDSI__OUT_SEL0) 
#define PowerEnableACC_PRTDSI__OUT_SEL1       (* (reg8 *) PowerEnableACC__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PowerEnableACC_PRTDSI__SYNC_OUT       (* (reg8 *) PowerEnableACC__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PowerEnableACC__SIO_CFG)
    #define PowerEnableACC_SIO_HYST_EN        (* (reg8 *) PowerEnableACC__SIO_HYST_EN)
    #define PowerEnableACC_SIO_REG_HIFREQ     (* (reg8 *) PowerEnableACC__SIO_REG_HIFREQ)
    #define PowerEnableACC_SIO_CFG            (* (reg8 *) PowerEnableACC__SIO_CFG)
    #define PowerEnableACC_SIO_DIFF           (* (reg8 *) PowerEnableACC__SIO_DIFF)
#endif /* (PowerEnableACC__SIO_CFG) */

/* Interrupt Registers */
#if defined(PowerEnableACC__INTSTAT)
    #define PowerEnableACC_INTSTAT            (* (reg8 *) PowerEnableACC__INTSTAT)
    #define PowerEnableACC_SNAP               (* (reg8 *) PowerEnableACC__SNAP)
    
	#define PowerEnableACC_0_INTTYPE_REG 		(* (reg8 *) PowerEnableACC__0__INTTYPE)
#endif /* (PowerEnableACC__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PowerEnableACC_H */


/* [] END OF FILE */
