/*******************************************************************************
* File Name: CarBattVoltage.h  
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

#if !defined(CY_PINS_CarBattVoltage_H) /* Pins CarBattVoltage_H */
#define CY_PINS_CarBattVoltage_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "CarBattVoltage_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 CarBattVoltage__PORT == 15 && ((CarBattVoltage__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    CarBattVoltage_Write(uint8 value);
void    CarBattVoltage_SetDriveMode(uint8 mode);
uint8   CarBattVoltage_ReadDataReg(void);
uint8   CarBattVoltage_Read(void);
void    CarBattVoltage_SetInterruptMode(uint16 position, uint16 mode);
uint8   CarBattVoltage_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the CarBattVoltage_SetDriveMode() function.
     *  @{
     */
        #define CarBattVoltage_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define CarBattVoltage_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define CarBattVoltage_DM_RES_UP          PIN_DM_RES_UP
        #define CarBattVoltage_DM_RES_DWN         PIN_DM_RES_DWN
        #define CarBattVoltage_DM_OD_LO           PIN_DM_OD_LO
        #define CarBattVoltage_DM_OD_HI           PIN_DM_OD_HI
        #define CarBattVoltage_DM_STRONG          PIN_DM_STRONG
        #define CarBattVoltage_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define CarBattVoltage_MASK               CarBattVoltage__MASK
#define CarBattVoltage_SHIFT              CarBattVoltage__SHIFT
#define CarBattVoltage_WIDTH              1u

/* Interrupt constants */
#if defined(CarBattVoltage__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CarBattVoltage_SetInterruptMode() function.
     *  @{
     */
        #define CarBattVoltage_INTR_NONE      (uint16)(0x0000u)
        #define CarBattVoltage_INTR_RISING    (uint16)(0x0001u)
        #define CarBattVoltage_INTR_FALLING   (uint16)(0x0002u)
        #define CarBattVoltage_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define CarBattVoltage_INTR_MASK      (0x01u) 
#endif /* (CarBattVoltage__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CarBattVoltage_PS                     (* (reg8 *) CarBattVoltage__PS)
/* Data Register */
#define CarBattVoltage_DR                     (* (reg8 *) CarBattVoltage__DR)
/* Port Number */
#define CarBattVoltage_PRT_NUM                (* (reg8 *) CarBattVoltage__PRT) 
/* Connect to Analog Globals */                                                  
#define CarBattVoltage_AG                     (* (reg8 *) CarBattVoltage__AG)                       
/* Analog MUX bux enable */
#define CarBattVoltage_AMUX                   (* (reg8 *) CarBattVoltage__AMUX) 
/* Bidirectional Enable */                                                        
#define CarBattVoltage_BIE                    (* (reg8 *) CarBattVoltage__BIE)
/* Bit-mask for Aliased Register Access */
#define CarBattVoltage_BIT_MASK               (* (reg8 *) CarBattVoltage__BIT_MASK)
/* Bypass Enable */
#define CarBattVoltage_BYP                    (* (reg8 *) CarBattVoltage__BYP)
/* Port wide control signals */                                                   
#define CarBattVoltage_CTL                    (* (reg8 *) CarBattVoltage__CTL)
/* Drive Modes */
#define CarBattVoltage_DM0                    (* (reg8 *) CarBattVoltage__DM0) 
#define CarBattVoltage_DM1                    (* (reg8 *) CarBattVoltage__DM1)
#define CarBattVoltage_DM2                    (* (reg8 *) CarBattVoltage__DM2) 
/* Input Buffer Disable Override */
#define CarBattVoltage_INP_DIS                (* (reg8 *) CarBattVoltage__INP_DIS)
/* LCD Common or Segment Drive */
#define CarBattVoltage_LCD_COM_SEG            (* (reg8 *) CarBattVoltage__LCD_COM_SEG)
/* Enable Segment LCD */
#define CarBattVoltage_LCD_EN                 (* (reg8 *) CarBattVoltage__LCD_EN)
/* Slew Rate Control */
#define CarBattVoltage_SLW                    (* (reg8 *) CarBattVoltage__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define CarBattVoltage_PRTDSI__CAPS_SEL       (* (reg8 *) CarBattVoltage__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define CarBattVoltage_PRTDSI__DBL_SYNC_IN    (* (reg8 *) CarBattVoltage__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define CarBattVoltage_PRTDSI__OE_SEL0        (* (reg8 *) CarBattVoltage__PRTDSI__OE_SEL0) 
#define CarBattVoltage_PRTDSI__OE_SEL1        (* (reg8 *) CarBattVoltage__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define CarBattVoltage_PRTDSI__OUT_SEL0       (* (reg8 *) CarBattVoltage__PRTDSI__OUT_SEL0) 
#define CarBattVoltage_PRTDSI__OUT_SEL1       (* (reg8 *) CarBattVoltage__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define CarBattVoltage_PRTDSI__SYNC_OUT       (* (reg8 *) CarBattVoltage__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(CarBattVoltage__SIO_CFG)
    #define CarBattVoltage_SIO_HYST_EN        (* (reg8 *) CarBattVoltage__SIO_HYST_EN)
    #define CarBattVoltage_SIO_REG_HIFREQ     (* (reg8 *) CarBattVoltage__SIO_REG_HIFREQ)
    #define CarBattVoltage_SIO_CFG            (* (reg8 *) CarBattVoltage__SIO_CFG)
    #define CarBattVoltage_SIO_DIFF           (* (reg8 *) CarBattVoltage__SIO_DIFF)
#endif /* (CarBattVoltage__SIO_CFG) */

/* Interrupt Registers */
#if defined(CarBattVoltage__INTSTAT)
    #define CarBattVoltage_INTSTAT            (* (reg8 *) CarBattVoltage__INTSTAT)
    #define CarBattVoltage_SNAP               (* (reg8 *) CarBattVoltage__SNAP)
    
	#define CarBattVoltage_0_INTTYPE_REG 		(* (reg8 *) CarBattVoltage__0__INTTYPE)
#endif /* (CarBattVoltage__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_CarBattVoltage_H */


/* [] END OF FILE */
