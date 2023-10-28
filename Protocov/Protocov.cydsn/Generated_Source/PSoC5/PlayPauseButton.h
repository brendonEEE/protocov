/*******************************************************************************
* File Name: PlayPauseButton.h  
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

#if !defined(CY_PINS_PlayPauseButton_H) /* Pins PlayPauseButton_H */
#define CY_PINS_PlayPauseButton_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PlayPauseButton_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PlayPauseButton__PORT == 15 && ((PlayPauseButton__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PlayPauseButton_Write(uint8 value);
void    PlayPauseButton_SetDriveMode(uint8 mode);
uint8   PlayPauseButton_ReadDataReg(void);
uint8   PlayPauseButton_Read(void);
void    PlayPauseButton_SetInterruptMode(uint16 position, uint16 mode);
uint8   PlayPauseButton_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PlayPauseButton_SetDriveMode() function.
     *  @{
     */
        #define PlayPauseButton_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PlayPauseButton_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PlayPauseButton_DM_RES_UP          PIN_DM_RES_UP
        #define PlayPauseButton_DM_RES_DWN         PIN_DM_RES_DWN
        #define PlayPauseButton_DM_OD_LO           PIN_DM_OD_LO
        #define PlayPauseButton_DM_OD_HI           PIN_DM_OD_HI
        #define PlayPauseButton_DM_STRONG          PIN_DM_STRONG
        #define PlayPauseButton_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PlayPauseButton_MASK               PlayPauseButton__MASK
#define PlayPauseButton_SHIFT              PlayPauseButton__SHIFT
#define PlayPauseButton_WIDTH              1u

/* Interrupt constants */
#if defined(PlayPauseButton__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PlayPauseButton_SetInterruptMode() function.
     *  @{
     */
        #define PlayPauseButton_INTR_NONE      (uint16)(0x0000u)
        #define PlayPauseButton_INTR_RISING    (uint16)(0x0001u)
        #define PlayPauseButton_INTR_FALLING   (uint16)(0x0002u)
        #define PlayPauseButton_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PlayPauseButton_INTR_MASK      (0x01u) 
#endif /* (PlayPauseButton__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PlayPauseButton_PS                     (* (reg8 *) PlayPauseButton__PS)
/* Data Register */
#define PlayPauseButton_DR                     (* (reg8 *) PlayPauseButton__DR)
/* Port Number */
#define PlayPauseButton_PRT_NUM                (* (reg8 *) PlayPauseButton__PRT) 
/* Connect to Analog Globals */                                                  
#define PlayPauseButton_AG                     (* (reg8 *) PlayPauseButton__AG)                       
/* Analog MUX bux enable */
#define PlayPauseButton_AMUX                   (* (reg8 *) PlayPauseButton__AMUX) 
/* Bidirectional Enable */                                                        
#define PlayPauseButton_BIE                    (* (reg8 *) PlayPauseButton__BIE)
/* Bit-mask for Aliased Register Access */
#define PlayPauseButton_BIT_MASK               (* (reg8 *) PlayPauseButton__BIT_MASK)
/* Bypass Enable */
#define PlayPauseButton_BYP                    (* (reg8 *) PlayPauseButton__BYP)
/* Port wide control signals */                                                   
#define PlayPauseButton_CTL                    (* (reg8 *) PlayPauseButton__CTL)
/* Drive Modes */
#define PlayPauseButton_DM0                    (* (reg8 *) PlayPauseButton__DM0) 
#define PlayPauseButton_DM1                    (* (reg8 *) PlayPauseButton__DM1)
#define PlayPauseButton_DM2                    (* (reg8 *) PlayPauseButton__DM2) 
/* Input Buffer Disable Override */
#define PlayPauseButton_INP_DIS                (* (reg8 *) PlayPauseButton__INP_DIS)
/* LCD Common or Segment Drive */
#define PlayPauseButton_LCD_COM_SEG            (* (reg8 *) PlayPauseButton__LCD_COM_SEG)
/* Enable Segment LCD */
#define PlayPauseButton_LCD_EN                 (* (reg8 *) PlayPauseButton__LCD_EN)
/* Slew Rate Control */
#define PlayPauseButton_SLW                    (* (reg8 *) PlayPauseButton__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PlayPauseButton_PRTDSI__CAPS_SEL       (* (reg8 *) PlayPauseButton__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PlayPauseButton_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PlayPauseButton__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PlayPauseButton_PRTDSI__OE_SEL0        (* (reg8 *) PlayPauseButton__PRTDSI__OE_SEL0) 
#define PlayPauseButton_PRTDSI__OE_SEL1        (* (reg8 *) PlayPauseButton__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PlayPauseButton_PRTDSI__OUT_SEL0       (* (reg8 *) PlayPauseButton__PRTDSI__OUT_SEL0) 
#define PlayPauseButton_PRTDSI__OUT_SEL1       (* (reg8 *) PlayPauseButton__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PlayPauseButton_PRTDSI__SYNC_OUT       (* (reg8 *) PlayPauseButton__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PlayPauseButton__SIO_CFG)
    #define PlayPauseButton_SIO_HYST_EN        (* (reg8 *) PlayPauseButton__SIO_HYST_EN)
    #define PlayPauseButton_SIO_REG_HIFREQ     (* (reg8 *) PlayPauseButton__SIO_REG_HIFREQ)
    #define PlayPauseButton_SIO_CFG            (* (reg8 *) PlayPauseButton__SIO_CFG)
    #define PlayPauseButton_SIO_DIFF           (* (reg8 *) PlayPauseButton__SIO_DIFF)
#endif /* (PlayPauseButton__SIO_CFG) */

/* Interrupt Registers */
#if defined(PlayPauseButton__INTSTAT)
    #define PlayPauseButton_INTSTAT            (* (reg8 *) PlayPauseButton__INTSTAT)
    #define PlayPauseButton_SNAP               (* (reg8 *) PlayPauseButton__SNAP)
    
	#define PlayPauseButton_0_INTTYPE_REG 		(* (reg8 *) PlayPauseButton__0__INTTYPE)
#endif /* (PlayPauseButton__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PlayPauseButton_H */


/* [] END OF FILE */
