/*******************************************************************************
* File Name: VehicleCarBattVoltage.h  
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

#if !defined(CY_PINS_VehicleCarBattVoltage_H) /* Pins VehicleCarBattVoltage_H */
#define CY_PINS_VehicleCarBattVoltage_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "VehicleCarBattVoltage_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 VehicleCarBattVoltage__PORT == 15 && ((VehicleCarBattVoltage__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    VehicleCarBattVoltage_Write(uint8 value);
void    VehicleCarBattVoltage_SetDriveMode(uint8 mode);
uint8   VehicleCarBattVoltage_ReadDataReg(void);
uint8   VehicleCarBattVoltage_Read(void);
void    VehicleCarBattVoltage_SetInterruptMode(uint16 position, uint16 mode);
uint8   VehicleCarBattVoltage_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the VehicleCarBattVoltage_SetDriveMode() function.
     *  @{
     */
        #define VehicleCarBattVoltage_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define VehicleCarBattVoltage_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define VehicleCarBattVoltage_DM_RES_UP          PIN_DM_RES_UP
        #define VehicleCarBattVoltage_DM_RES_DWN         PIN_DM_RES_DWN
        #define VehicleCarBattVoltage_DM_OD_LO           PIN_DM_OD_LO
        #define VehicleCarBattVoltage_DM_OD_HI           PIN_DM_OD_HI
        #define VehicleCarBattVoltage_DM_STRONG          PIN_DM_STRONG
        #define VehicleCarBattVoltage_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define VehicleCarBattVoltage_MASK               VehicleCarBattVoltage__MASK
#define VehicleCarBattVoltage_SHIFT              VehicleCarBattVoltage__SHIFT
#define VehicleCarBattVoltage_WIDTH              1u

/* Interrupt constants */
#if defined(VehicleCarBattVoltage__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VehicleCarBattVoltage_SetInterruptMode() function.
     *  @{
     */
        #define VehicleCarBattVoltage_INTR_NONE      (uint16)(0x0000u)
        #define VehicleCarBattVoltage_INTR_RISING    (uint16)(0x0001u)
        #define VehicleCarBattVoltage_INTR_FALLING   (uint16)(0x0002u)
        #define VehicleCarBattVoltage_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define VehicleCarBattVoltage_INTR_MASK      (0x01u) 
#endif /* (VehicleCarBattVoltage__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define VehicleCarBattVoltage_PS                     (* (reg8 *) VehicleCarBattVoltage__PS)
/* Data Register */
#define VehicleCarBattVoltage_DR                     (* (reg8 *) VehicleCarBattVoltage__DR)
/* Port Number */
#define VehicleCarBattVoltage_PRT_NUM                (* (reg8 *) VehicleCarBattVoltage__PRT) 
/* Connect to Analog Globals */                                                  
#define VehicleCarBattVoltage_AG                     (* (reg8 *) VehicleCarBattVoltage__AG)                       
/* Analog MUX bux enable */
#define VehicleCarBattVoltage_AMUX                   (* (reg8 *) VehicleCarBattVoltage__AMUX) 
/* Bidirectional Enable */                                                        
#define VehicleCarBattVoltage_BIE                    (* (reg8 *) VehicleCarBattVoltage__BIE)
/* Bit-mask for Aliased Register Access */
#define VehicleCarBattVoltage_BIT_MASK               (* (reg8 *) VehicleCarBattVoltage__BIT_MASK)
/* Bypass Enable */
#define VehicleCarBattVoltage_BYP                    (* (reg8 *) VehicleCarBattVoltage__BYP)
/* Port wide control signals */                                                   
#define VehicleCarBattVoltage_CTL                    (* (reg8 *) VehicleCarBattVoltage__CTL)
/* Drive Modes */
#define VehicleCarBattVoltage_DM0                    (* (reg8 *) VehicleCarBattVoltage__DM0) 
#define VehicleCarBattVoltage_DM1                    (* (reg8 *) VehicleCarBattVoltage__DM1)
#define VehicleCarBattVoltage_DM2                    (* (reg8 *) VehicleCarBattVoltage__DM2) 
/* Input Buffer Disable Override */
#define VehicleCarBattVoltage_INP_DIS                (* (reg8 *) VehicleCarBattVoltage__INP_DIS)
/* LCD Common or Segment Drive */
#define VehicleCarBattVoltage_LCD_COM_SEG            (* (reg8 *) VehicleCarBattVoltage__LCD_COM_SEG)
/* Enable Segment LCD */
#define VehicleCarBattVoltage_LCD_EN                 (* (reg8 *) VehicleCarBattVoltage__LCD_EN)
/* Slew Rate Control */
#define VehicleCarBattVoltage_SLW                    (* (reg8 *) VehicleCarBattVoltage__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define VehicleCarBattVoltage_PRTDSI__CAPS_SEL       (* (reg8 *) VehicleCarBattVoltage__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define VehicleCarBattVoltage_PRTDSI__DBL_SYNC_IN    (* (reg8 *) VehicleCarBattVoltage__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define VehicleCarBattVoltage_PRTDSI__OE_SEL0        (* (reg8 *) VehicleCarBattVoltage__PRTDSI__OE_SEL0) 
#define VehicleCarBattVoltage_PRTDSI__OE_SEL1        (* (reg8 *) VehicleCarBattVoltage__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define VehicleCarBattVoltage_PRTDSI__OUT_SEL0       (* (reg8 *) VehicleCarBattVoltage__PRTDSI__OUT_SEL0) 
#define VehicleCarBattVoltage_PRTDSI__OUT_SEL1       (* (reg8 *) VehicleCarBattVoltage__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define VehicleCarBattVoltage_PRTDSI__SYNC_OUT       (* (reg8 *) VehicleCarBattVoltage__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(VehicleCarBattVoltage__SIO_CFG)
    #define VehicleCarBattVoltage_SIO_HYST_EN        (* (reg8 *) VehicleCarBattVoltage__SIO_HYST_EN)
    #define VehicleCarBattVoltage_SIO_REG_HIFREQ     (* (reg8 *) VehicleCarBattVoltage__SIO_REG_HIFREQ)
    #define VehicleCarBattVoltage_SIO_CFG            (* (reg8 *) VehicleCarBattVoltage__SIO_CFG)
    #define VehicleCarBattVoltage_SIO_DIFF           (* (reg8 *) VehicleCarBattVoltage__SIO_DIFF)
#endif /* (VehicleCarBattVoltage__SIO_CFG) */

/* Interrupt Registers */
#if defined(VehicleCarBattVoltage__INTSTAT)
    #define VehicleCarBattVoltage_INTSTAT            (* (reg8 *) VehicleCarBattVoltage__INTSTAT)
    #define VehicleCarBattVoltage_SNAP               (* (reg8 *) VehicleCarBattVoltage__SNAP)
    
	#define VehicleCarBattVoltage_0_INTTYPE_REG 		(* (reg8 *) VehicleCarBattVoltage__0__INTTYPE)
#endif /* (VehicleCarBattVoltage__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_VehicleCarBattVoltage_H */


/* [] END OF FILE */
