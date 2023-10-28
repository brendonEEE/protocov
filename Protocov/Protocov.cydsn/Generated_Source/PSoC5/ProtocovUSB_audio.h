/***************************************************************************//**
* \file ProtocovUSB_audio.h
* \version 3.20
*
* \brief
*  This file provides function prototypes and constants for the USBFS component 
*  Audio class.
*
* Related Document:
*  Universal Serial Bus Device Class Definition for Audio Devices Release 1.0
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_ProtocovUSB_audio_H)
#define CY_USBFS_ProtocovUSB_audio_H

#include "ProtocovUSB.h"


/***************************************
* Custom Declarations
***************************************/

/* `#START CUSTOM_CONSTANTS` Place your declaration here */

/* `#END` */


/***************************************
*  Constants for ProtocovUSB_audio API.
***************************************/

/* Audio Class-Specific Request Codes (AUDIO Table A-9) */
#define ProtocovUSB_REQUEST_CODE_UNDEFINED     (0x00u)
#define ProtocovUSB_SET_CUR                    (0x01u)
#define ProtocovUSB_GET_CUR                    (0x81u)
#define ProtocovUSB_SET_MIN                    (0x02u)
#define ProtocovUSB_GET_MIN                    (0x82u)
#define ProtocovUSB_SET_MAX                    (0x03u)
#define ProtocovUSB_GET_MAX                    (0x83u)
#define ProtocovUSB_SET_RES                    (0x04u)
#define ProtocovUSB_GET_RES                    (0x84u)
#define ProtocovUSB_SET_MEM                    (0x05u)
#define ProtocovUSB_GET_MEM                    (0x85u)
#define ProtocovUSB_GET_STAT                   (0xFFu)

/* point Control Selectors (AUDIO Table A-19) */
#define ProtocovUSB_EP_CONTROL_UNDEFINED       (0x00u)
#define ProtocovUSB_SAMPLING_FREQ_CONTROL      (0x01u)
#define ProtocovUSB_PITCH_CONTROL              (0x02u)

/* Feature Unit Control Selectors (AUDIO Table A-11) */
#define ProtocovUSB_FU_CONTROL_UNDEFINED       (0x00u)
#define ProtocovUSB_MUTE_CONTROL               (0x01u)
#define ProtocovUSB_VOLUME_CONTROL             (0x02u)
#define ProtocovUSB_BASS_CONTROL               (0x03u)
#define ProtocovUSB_MID_CONTROL                (0x04u)
#define ProtocovUSB_TREBLE_CONTROL             (0x05u)
#define ProtocovUSB_GRAPHIC_EQUALIZER_CONTROL  (0x06u)
#define ProtocovUSB_AUTOMATIC_GAIN_CONTROL     (0x07u)
#define ProtocovUSB_DELAY_CONTROL              (0x08u)
#define ProtocovUSB_BASS_BOOST_CONTROL         (0x09u)
#define ProtocovUSB_LOUDNESS_CONTROL           (0x0Au)

#define ProtocovUSB_SAMPLE_FREQ_LEN            (3u)
#define ProtocovUSB_VOLUME_LEN                 (2u)

#if !defined(USER_SUPPLIED_DEFAULT_VOLUME_VALUE)
    #define ProtocovUSB_VOL_MIN_MSB            (0x80u)
    #define ProtocovUSB_VOL_MIN_LSB            (0x01u)
    #define ProtocovUSB_VOL_MAX_MSB            (0x7Fu)
    #define ProtocovUSB_VOL_MAX_LSB            (0xFFu)
    #define ProtocovUSB_VOL_RES_MSB            (0x00u)
    #define ProtocovUSB_VOL_RES_LSB            (0x01u)
#endif /* USER_SUPPLIED_DEFAULT_VOLUME_VALUE */


/***************************************
* External data references
***************************************/
/**
* \addtogroup group_audio
* @{
*/
extern volatile uint8 ProtocovUSB_currentSampleFrequency[ProtocovUSB_MAX_EP][ProtocovUSB_SAMPLE_FREQ_LEN];
extern volatile uint8 ProtocovUSB_frequencyChanged;
extern volatile uint8 ProtocovUSB_currentMute;
extern volatile uint8 ProtocovUSB_currentVolume[ProtocovUSB_VOLUME_LEN];
/** @} audio */

extern volatile uint8 ProtocovUSB_minimumVolume[ProtocovUSB_VOLUME_LEN];
extern volatile uint8 ProtocovUSB_maximumVolume[ProtocovUSB_VOLUME_LEN];
extern volatile uint8 ProtocovUSB_resolutionVolume[ProtocovUSB_VOLUME_LEN];

#endif /*  CY_USBFS_ProtocovUSB_audio_H */


/* [] END OF FILE */
