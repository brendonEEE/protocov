/*******************************************************************************
* File Name: VehicleBattVoltageAdc_SAR_Bypass.h  
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

#if !defined(CY_PINS_VehicleBattVoltageAdc_SAR_Bypass_H) /* Pins VehicleBattVoltageAdc_SAR_Bypass_H */
#define CY_PINS_VehicleBattVoltageAdc_SAR_Bypass_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "VehicleBattVoltageAdc_SAR_Bypass_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 VehicleBattVoltageAdc_SAR_Bypass__PORT == 15 && ((VehicleBattVoltageAdc_SAR_Bypass__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    VehicleBattVoltageAdc_SAR_Bypass_Write(uint8 value);
void    VehicleBattVoltageAdc_SAR_Bypass_SetDriveMode(uint8 mode);
uint8   VehicleBattVoltageAdc_SAR_Bypass_ReadDataReg(void);
uint8   VehicleBattVoltageAdc_SAR_Bypass_Read(void);
void    VehicleBattVoltageAdc_SAR_Bypass_SetInterruptMode(uint16 position, uint16 mode);
uint8   VehicleBattVoltageAdc_SAR_Bypass_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the VehicleBattVoltageAdc_SAR_Bypass_SetDriveMode() function.
     *  @{
     */
        #define VehicleBattVoltageAdc_SAR_Bypass_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define VehicleBattVoltageAdc_SAR_Bypass_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define VehicleBattVoltageAdc_SAR_Bypass_DM_RES_UP          PIN_DM_RES_UP
        #define VehicleBattVoltageAdc_SAR_Bypass_DM_RES_DWN         PIN_DM_RES_DWN
        #define VehicleBattVoltageAdc_SAR_Bypass_DM_OD_LO           PIN_DM_OD_LO
        #define VehicleBattVoltageAdc_SAR_Bypass_DM_OD_HI           PIN_DM_OD_HI
        #define VehicleBattVoltageAdc_SAR_Bypass_DM_STRONG          PIN_DM_STRONG
        #define VehicleBattVoltageAdc_SAR_Bypass_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define VehicleBattVoltageAdc_SAR_Bypass_MASK               VehicleBattVoltageAdc_SAR_Bypass__MASK
#define VehicleBattVoltageAdc_SAR_Bypass_SHIFT              VehicleBattVoltageAdc_SAR_Bypass__SHIFT
#define VehicleBattVoltageAdc_SAR_Bypass_WIDTH              1u

/* Interrupt constants */
#if defined(VehicleBattVoltageAdc_SAR_Bypass__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VehicleBattVoltageAdc_SAR_Bypass_SetInterruptMode() function.
     *  @{
     */
        #define VehicleBattVoltageAdc_SAR_Bypass_INTR_NONE      (uint16)(0x0000u)
        #define VehicleBattVoltageAdc_SAR_Bypass_INTR_RISING    (uint16)(0x0001u)
        #define VehicleBattVoltageAdc_SAR_Bypass_INTR_FALLING   (uint16)(0x0002u)
        #define VehicleBattVoltageAdc_SAR_Bypass_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define VehicleBattVoltageAdc_SAR_Bypass_INTR_MASK      (0x01u) 
#endif /* (VehicleBattVoltageAdc_SAR_Bypass__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define VehicleBattVoltageAdc_SAR_Bypass_PS                     (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__PS)
/* Data Register */
#define VehicleBattVoltageAdc_SAR_Bypass_DR                     (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__DR)
/* Port Number */
#define VehicleBattVoltageAdc_SAR_Bypass_PRT_NUM                (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__PRT) 
/* Connect to Analog Globals */                                                  
#define VehicleBattVoltageAdc_SAR_Bypass_AG                     (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__AG)                       
/* Analog MUX bux enable */
#define VehicleBattVoltageAdc_SAR_Bypass_AMUX                   (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__AMUX) 
/* Bidirectional Enable */                                                        
#define VehicleBattVoltageAdc_SAR_Bypass_BIE                    (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__BIE)
/* Bit-mask for Aliased Register Access */
#define VehicleBattVoltageAdc_SAR_Bypass_BIT_MASK               (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__BIT_MASK)
/* Bypass Enable */
#define VehicleBattVoltageAdc_SAR_Bypass_BYP                    (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__BYP)
/* Port wide control signals */                                                   
#define VehicleBattVoltageAdc_SAR_Bypass_CTL                    (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__CTL)
/* Drive Modes */
#define VehicleBattVoltageAdc_SAR_Bypass_DM0                    (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__DM0) 
#define VehicleBattVoltageAdc_SAR_Bypass_DM1                    (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__DM1)
#define VehicleBattVoltageAdc_SAR_Bypass_DM2                    (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__DM2) 
/* Input Buffer Disable Override */
#define VehicleBattVoltageAdc_SAR_Bypass_INP_DIS                (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__INP_DIS)
/* LCD Common or Segment Drive */
#define VehicleBattVoltageAdc_SAR_Bypass_LCD_COM_SEG            (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__LCD_COM_SEG)
/* Enable Segment LCD */
#define VehicleBattVoltageAdc_SAR_Bypass_LCD_EN                 (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__LCD_EN)
/* Slew Rate Control */
#define VehicleBattVoltageAdc_SAR_Bypass_SLW                    (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define VehicleBattVoltageAdc_SAR_Bypass_PRTDSI__CAPS_SEL       (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define VehicleBattVoltageAdc_SAR_Bypass_PRTDSI__DBL_SYNC_IN    (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define VehicleBattVoltageAdc_SAR_Bypass_PRTDSI__OE_SEL0        (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__PRTDSI__OE_SEL0) 
#define VehicleBattVoltageAdc_SAR_Bypass_PRTDSI__OE_SEL1        (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define VehicleBattVoltageAdc_SAR_Bypass_PRTDSI__OUT_SEL0       (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__PRTDSI__OUT_SEL0) 
#define VehicleBattVoltageAdc_SAR_Bypass_PRTDSI__OUT_SEL1       (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define VehicleBattVoltageAdc_SAR_Bypass_PRTDSI__SYNC_OUT       (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(VehicleBattVoltageAdc_SAR_Bypass__SIO_CFG)
    #define VehicleBattVoltageAdc_SAR_Bypass_SIO_HYST_EN        (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__SIO_HYST_EN)
    #define VehicleBattVoltageAdc_SAR_Bypass_SIO_REG_HIFREQ     (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__SIO_REG_HIFREQ)
    #define VehicleBattVoltageAdc_SAR_Bypass_SIO_CFG            (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__SIO_CFG)
    #define VehicleBattVoltageAdc_SAR_Bypass_SIO_DIFF           (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__SIO_DIFF)
#endif /* (VehicleBattVoltageAdc_SAR_Bypass__SIO_CFG) */

/* Interrupt Registers */
#if defined(VehicleBattVoltageAdc_SAR_Bypass__INTSTAT)
    #define VehicleBattVoltageAdc_SAR_Bypass_INTSTAT            (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__INTSTAT)
    #define VehicleBattVoltageAdc_SAR_Bypass_SNAP               (* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__SNAP)
    
	#define VehicleBattVoltageAdc_SAR_Bypass_0_INTTYPE_REG 		(* (reg8 *) VehicleBattVoltageAdc_SAR_Bypass__0__INTTYPE)
#endif /* (VehicleBattVoltageAdc_SAR_Bypass__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_VehicleBattVoltageAdc_SAR_Bypass_H */


/* [] END OF FILE */
