/*******************************************************************************
* File Name: NextButton.h  
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

#if !defined(CY_PINS_NextButton_H) /* Pins NextButton_H */
#define CY_PINS_NextButton_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "NextButton_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 NextButton__PORT == 15 && ((NextButton__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    NextButton_Write(uint8 value);
void    NextButton_SetDriveMode(uint8 mode);
uint8   NextButton_ReadDataReg(void);
uint8   NextButton_Read(void);
void    NextButton_SetInterruptMode(uint16 position, uint16 mode);
uint8   NextButton_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the NextButton_SetDriveMode() function.
     *  @{
     */
        #define NextButton_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define NextButton_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define NextButton_DM_RES_UP          PIN_DM_RES_UP
        #define NextButton_DM_RES_DWN         PIN_DM_RES_DWN
        #define NextButton_DM_OD_LO           PIN_DM_OD_LO
        #define NextButton_DM_OD_HI           PIN_DM_OD_HI
        #define NextButton_DM_STRONG          PIN_DM_STRONG
        #define NextButton_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define NextButton_MASK               NextButton__MASK
#define NextButton_SHIFT              NextButton__SHIFT
#define NextButton_WIDTH              1u

/* Interrupt constants */
#if defined(NextButton__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in NextButton_SetInterruptMode() function.
     *  @{
     */
        #define NextButton_INTR_NONE      (uint16)(0x0000u)
        #define NextButton_INTR_RISING    (uint16)(0x0001u)
        #define NextButton_INTR_FALLING   (uint16)(0x0002u)
        #define NextButton_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define NextButton_INTR_MASK      (0x01u) 
#endif /* (NextButton__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define NextButton_PS                     (* (reg8 *) NextButton__PS)
/* Data Register */
#define NextButton_DR                     (* (reg8 *) NextButton__DR)
/* Port Number */
#define NextButton_PRT_NUM                (* (reg8 *) NextButton__PRT) 
/* Connect to Analog Globals */                                                  
#define NextButton_AG                     (* (reg8 *) NextButton__AG)                       
/* Analog MUX bux enable */
#define NextButton_AMUX                   (* (reg8 *) NextButton__AMUX) 
/* Bidirectional Enable */                                                        
#define NextButton_BIE                    (* (reg8 *) NextButton__BIE)
/* Bit-mask for Aliased Register Access */
#define NextButton_BIT_MASK               (* (reg8 *) NextButton__BIT_MASK)
/* Bypass Enable */
#define NextButton_BYP                    (* (reg8 *) NextButton__BYP)
/* Port wide control signals */                                                   
#define NextButton_CTL                    (* (reg8 *) NextButton__CTL)
/* Drive Modes */
#define NextButton_DM0                    (* (reg8 *) NextButton__DM0) 
#define NextButton_DM1                    (* (reg8 *) NextButton__DM1)
#define NextButton_DM2                    (* (reg8 *) NextButton__DM2) 
/* Input Buffer Disable Override */
#define NextButton_INP_DIS                (* (reg8 *) NextButton__INP_DIS)
/* LCD Common or Segment Drive */
#define NextButton_LCD_COM_SEG            (* (reg8 *) NextButton__LCD_COM_SEG)
/* Enable Segment LCD */
#define NextButton_LCD_EN                 (* (reg8 *) NextButton__LCD_EN)
/* Slew Rate Control */
#define NextButton_SLW                    (* (reg8 *) NextButton__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define NextButton_PRTDSI__CAPS_SEL       (* (reg8 *) NextButton__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define NextButton_PRTDSI__DBL_SYNC_IN    (* (reg8 *) NextButton__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define NextButton_PRTDSI__OE_SEL0        (* (reg8 *) NextButton__PRTDSI__OE_SEL0) 
#define NextButton_PRTDSI__OE_SEL1        (* (reg8 *) NextButton__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define NextButton_PRTDSI__OUT_SEL0       (* (reg8 *) NextButton__PRTDSI__OUT_SEL0) 
#define NextButton_PRTDSI__OUT_SEL1       (* (reg8 *) NextButton__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define NextButton_PRTDSI__SYNC_OUT       (* (reg8 *) NextButton__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(NextButton__SIO_CFG)
    #define NextButton_SIO_HYST_EN        (* (reg8 *) NextButton__SIO_HYST_EN)
    #define NextButton_SIO_REG_HIFREQ     (* (reg8 *) NextButton__SIO_REG_HIFREQ)
    #define NextButton_SIO_CFG            (* (reg8 *) NextButton__SIO_CFG)
    #define NextButton_SIO_DIFF           (* (reg8 *) NextButton__SIO_DIFF)
#endif /* (NextButton__SIO_CFG) */

/* Interrupt Registers */
#if defined(NextButton__INTSTAT)
    #define NextButton_INTSTAT            (* (reg8 *) NextButton__INTSTAT)
    #define NextButton_SNAP               (* (reg8 *) NextButton__SNAP)
    
	#define NextButton_0_INTTYPE_REG 		(* (reg8 *) NextButton__0__INTTYPE)
#endif /* (NextButton__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_NextButton_H */


/* [] END OF FILE */
