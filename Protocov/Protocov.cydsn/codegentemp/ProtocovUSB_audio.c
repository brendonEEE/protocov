/***************************************************************************//**
* \file ProtocovUSB_audio.c
* \version 3.20
*
* \brief
*  This file contains the USB AUDIO Class request handler.
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

#include "ProtocovUSB_audio.h"
#include "ProtocovUSB_pvt.h"
#include "cyapicallbacks.h"

#if defined(ProtocovUSB_ENABLE_AUDIO_CLASS)

/***************************************
* Custom Declarations
***************************************/

/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


#if !defined(USER_SUPPLIED_AUDIO_HANDLER)

/***************************************
*    AUDIO Variables
***************************************/

#if defined(ProtocovUSB_ENABLE_AUDIO_STREAMING)
    /** Contains the current audio sample frequency. It is set by the host using a SET_CUR request to the endpoint.*/
    volatile uint8 ProtocovUSB_currentSampleFrequency[ProtocovUSB_MAX_EP][ProtocovUSB_SAMPLE_FREQ_LEN];
    /** Used as a flag for the user code, to inform it that the host has been sent a request 
     * to change the sample frequency. The sample frequency will be sent on the next OUT transaction. 
     * It contains the endpoint address when set. The following code is recommended for 
     * detecting new sample frequency in main code:
     * \snippet  /USBFS_sut_02.cydsn/main.c Detecting new Sample Frequency
     *     
     * The USBFS_transferState variable is checked to make sure that the transfer completes. */
    volatile uint8 ProtocovUSB_frequencyChanged;
    /** Contains the mute configuration set by the host.*/
    volatile uint8 ProtocovUSB_currentMute;
    /** Contains the volume level set by the host.*/
    volatile uint8 ProtocovUSB_currentVolume[ProtocovUSB_VOLUME_LEN];
    volatile uint8 ProtocovUSB_minimumVolume[ProtocovUSB_VOLUME_LEN] = {ProtocovUSB_VOL_MIN_LSB,
                                                                                  ProtocovUSB_VOL_MIN_MSB};
    volatile uint8 ProtocovUSB_maximumVolume[ProtocovUSB_VOLUME_LEN] = {ProtocovUSB_VOL_MAX_LSB,
                                                                                  ProtocovUSB_VOL_MAX_MSB};
    volatile uint8 ProtocovUSB_resolutionVolume[ProtocovUSB_VOLUME_LEN] = {ProtocovUSB_VOL_RES_LSB,
                                                                                     ProtocovUSB_VOL_RES_MSB};
#endif /*  ProtocovUSB_ENABLE_AUDIO_STREAMING */


/*******************************************************************************
* Function Name: ProtocovUSB_DispatchAUDIOClassRqst
****************************************************************************//**
*
*  This routine dispatches class requests
*
* \return
*  Results of Audio Class request handling: 
*  - ProtocovUSB_TRUE  - request was handled without errors
*  - ProtocovUSB_FALSE - error occurs during handling of request     
*
* \globalvars
*   ProtocovUSB_currentSampleFrequency: Contains the current audio Sample
*       Frequency. It is set by the Host using SET_CUR request to the endpoint.
*   ProtocovUSB_frequencyChanged: This variable is used as a flag for the
*       user code, to be aware that Host has been sent request for changing
*       Sample Frequency. Sample frequency will be sent on the next OUT
*       transaction. It is contains endpoint address when set. The following
*       code is recommended for detecting new Sample Frequency in main code:
*       
*  \snippet  /USBFS_sut_02.cydsn/main.c Detecting new Sample Frequency
*      
*   ProtocovUSB_transferState variable is checked to be sure that transfer
*              completes.
*   ProtocovUSB_currentMute: Contains mute configuration set by Host.
*   ProtocovUSB_currentVolume: Contains volume level set by Host.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 ProtocovUSB_DispatchAUDIOClassRqst(void) 
{
    uint8 requestHandled = ProtocovUSB_FALSE;
    
    uint8 RqstRcpt = (uint8)(ProtocovUSB_bmRequestTypeReg & ProtocovUSB_RQST_RCPT_MASK);
#if defined(ProtocovUSB_ENABLE_AUDIO_STREAMING)
    uint8 wValueHi = (uint8) ProtocovUSB_wValueHiReg;
    uint8 epNumber = (uint8) ProtocovUSB_wIndexLoReg & ProtocovUSB_DIR_UNUSED;
#endif /* (ProtocovUSB_ENABLE_AUDIO_STREAMING) */
    
    /* Check request direction: D2H or H2D. */
    if (0u != (ProtocovUSB_bmRequestTypeReg & ProtocovUSB_RQST_DIR_D2H))
    {
        /* Handle direction from device to host. */
        
        if (ProtocovUSB_RQST_RCPT_EP == RqstRcpt)
        {
            /* Request recipient is to endpoint. */
            switch (ProtocovUSB_bRequestReg)
            {
                case ProtocovUSB_GET_CUR:
                #if defined(ProtocovUSB_ENABLE_AUDIO_STREAMING)
                    if (wValueHi == ProtocovUSB_SAMPLING_FREQ_CONTROL)
                    {
                         /* point Control Selector is Sampling Frequency */
                        ProtocovUSB_currentTD.wCount = ProtocovUSB_SAMPLE_FREQ_LEN;
                        ProtocovUSB_currentTD.pData  = ProtocovUSB_currentSampleFrequency[epNumber];
                        
                        requestHandled   = ProtocovUSB_InitControlRead();
                    }
                #endif /* (ProtocovUSB_ENABLE_AUDIO_STREAMING) */
                
                    /* `#START AUDIO_READ_REQUESTS` Place other request handler here */

                    /* `#END` */
                
                #ifdef ProtocovUSB_DISPATCH_AUDIO_CLASS_AUDIO_READ_REQUESTS_CALLBACK    
                    ProtocovUSB_DispatchAUDIOClass_AUDIO_READ_REQUESTS_Callback();
                #endif /* (ProtocovUSB_DISPATCH_AUDIO_CLASS_AUDIO_READ_REQUESTS_CALLBACK) */                   
                break;
                
                default:
                    /* Do not handle this request unless callback is defined. */
                    break;
            }
        
        }
        else if (ProtocovUSB_RQST_RCPT_IFC == RqstRcpt)
        {
            /* Request recipient is interface or entity ID. */
            switch (ProtocovUSB_bRequestReg)
            {
                case ProtocovUSB_GET_CUR:
                #if defined(ProtocovUSB_ENABLE_AUDIO_STREAMING)
                    if (wValueHi == ProtocovUSB_MUTE_CONTROL)
                    {
                        /* `#START MUTE_CONTROL_GET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                    #ifdef ProtocovUSB_DISPATCH_AUDIO_CLASS_MUTE_CONTROL_GET_REQUEST_CALLBACK
                        ProtocovUSB_DispatchAUDIOClass_MUTE_CONTROL_GET_REQUEST_Callback();
                    #endif /* (ProtocovUSB_DISPATCH_AUDIO_CLASS_MUTE_CONTROL_GET_REQUEST_CALLBACK) */

                        /* Entity ID Control Selector is MUTE */
                        ProtocovUSB_currentTD.wCount = 1u;
                        ProtocovUSB_currentTD.pData  = &ProtocovUSB_currentMute;
                        
                        requestHandled = ProtocovUSB_InitControlRead();
                    }
                    else if (wValueHi == ProtocovUSB_VOLUME_CONTROL)
                    {
                        /* `#START VOLUME_CONTROL_GET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                    #ifdef ProtocovUSB_DISPATCH_AUDIO_CLASS_VOLUME_CONTROL_GET_REQUEST_CALLBACK
                        ProtocovUSB_DispatchAUDIOClass_VOLUME_CONTROL_GET_REQUEST_Callback();
                    #endif /* (ProtocovUSB_DISPATCH_AUDIO_CLASS_VOLUME_CONTROL_GET_REQUEST_CALLBACK) */

                        /* Entity ID Control Selector is VOLUME, */
                        ProtocovUSB_currentTD.wCount = ProtocovUSB_VOLUME_LEN;
                        ProtocovUSB_currentTD.pData  = ProtocovUSB_currentVolume;
                        
                        requestHandled = ProtocovUSB_InitControlRead();
                    }
                    else
                    {
                        /* `#START OTHER_GET_CUR_REQUESTS` Place other request handler here */

                        /* `#END` */

                    #ifdef ProtocovUSB_DISPATCH_AUDIO_CLASS_OTHER_GET_CUR_REQUESTS_CALLBACK
                        ProtocovUSB_DispatchAUDIOClass_OTHER_GET_CUR_REQUESTS_Callback();
                    #endif /* (ProtocovUSB_DISPATCH_AUDIO_CLASS_OTHER_GET_CUR_REQUESTS_CALLBACK) */
                    }
                    break;
                    
                case ProtocovUSB_GET_MIN:
                    if (wValueHi == ProtocovUSB_VOLUME_CONTROL)
                    {
                        /* Entity ID Control Selector is VOLUME, */
                        ProtocovUSB_currentTD.wCount = ProtocovUSB_VOLUME_LEN;
                        ProtocovUSB_currentTD.pData  = &ProtocovUSB_minimumVolume[0];
                        
                        requestHandled = ProtocovUSB_InitControlRead();
                    }
                    break;
                    
                case ProtocovUSB_GET_MAX:
                    if (wValueHi == ProtocovUSB_VOLUME_CONTROL)
                    {
                        /* Entity ID Control Selector is VOLUME, */
                        ProtocovUSB_currentTD.wCount = ProtocovUSB_VOLUME_LEN;
                        ProtocovUSB_currentTD.pData  = &ProtocovUSB_maximumVolume[0];
                        
                        requestHandled = ProtocovUSB_InitControlRead();
                    }
                    break;
                    
                case ProtocovUSB_GET_RES:
                    if (wValueHi == ProtocovUSB_VOLUME_CONTROL)
                    {
                         /* Entity ID Control Selector is VOLUME, */
                        ProtocovUSB_currentTD.wCount = ProtocovUSB_VOLUME_LEN;
                        ProtocovUSB_currentTD.pData  = &ProtocovUSB_resolutionVolume[0];
                        
                        requestHandled   = ProtocovUSB_InitControlRead();
                    }
                    break;
                    
                /* The contents of the status message is reserved for future use.
                * For the time being, a null packet should be returned in the data stage of the
                * control transfer, and the received null packet should be ACKed.
                */
                case ProtocovUSB_GET_STAT:
                    ProtocovUSB_currentTD.wCount = 0u;    
                    
                    requestHandled = ProtocovUSB_InitControlWrite();

                #endif /* (ProtocovUSB_ENABLE_AUDIO_STREAMING) */
                
                    /* `#START AUDIO_WRITE_REQUESTS` Place other request handler here */

                    /* `#END` */
                
                #ifdef ProtocovUSB_DISPATCH_AUDIO_CLASS_AUDIO_WRITE_REQUESTS_CALLBACK
                    ProtocovUSB_DispatchAUDIOClass_AUDIO_WRITE_REQUESTS_Callback();
                #endif /* (ProtocovUSB_DISPATCH_AUDIO_CLASS_AUDIO_WRITE_REQUESTS_CALLBACK) */
                    break;
                
                default:
                    /* Do not handle this request. */
                    break;
            }
        }
        else
        {   
            /* Do not handle other requests recipients. */
        }
    }
    else
    {
        /* Handle direction from host to device. */
        
        if (ProtocovUSB_RQST_RCPT_EP == RqstRcpt)
        {
            /* Request recipient is endpoint. */
            switch (ProtocovUSB_bRequestReg)
            {
                case ProtocovUSB_SET_CUR:
                #if defined(ProtocovUSB_ENABLE_AUDIO_STREAMING)
                    if (wValueHi == ProtocovUSB_SAMPLING_FREQ_CONTROL)
                    {
                         /* point Control Selector is Sampling Frequency */
                        ProtocovUSB_currentTD.wCount = ProtocovUSB_SAMPLE_FREQ_LEN;
                        ProtocovUSB_currentTD.pData  = ProtocovUSB_currentSampleFrequency[epNumber];
                        ProtocovUSB_frequencyChanged = (uint8) epNumber;
                        
                        requestHandled   = ProtocovUSB_InitControlWrite();
                    }
                #endif /* (ProtocovUSB_ENABLE_AUDIO_STREAMING) */

                    /* `#START AUDIO_SAMPLING_FREQ_REQUESTS` Place other request handler here */

                    /* `#END` */

                #ifdef ProtocovUSB_DISPATCH_AUDIO_CLASS_AUDIO_SAMPLING_FREQ_REQUESTS_CALLBACK
                    ProtocovUSB_DispatchAUDIOClass_AUDIO_SAMPLING_FREQ_REQUESTS_Callback();
                #endif /* (ProtocovUSB_DISPATCH_AUDIO_CLASS_AUDIO_SAMPLING_FREQ_REQUESTS_CALLBACK) */
                    break;
                
                default:
                    /* Do not handle this request. */
                    break;
            }
        }
        else if(ProtocovUSB_RQST_RCPT_IFC == RqstRcpt)
        {
            /* Request recipient is interface or entity ID. */
            switch (ProtocovUSB_bRequestReg)
            {
                case ProtocovUSB_SET_CUR:
                #if defined(ProtocovUSB_ENABLE_AUDIO_STREAMING)
                    if (wValueHi == ProtocovUSB_MUTE_CONTROL)
                    {
                        /* `#START MUTE_SET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                    #ifdef ProtocovUSB_DISPATCH_AUDIO_CLASS_MUTE_SET_REQUEST_CALLBACK
                        ProtocovUSB_DispatchAUDIOClass_MUTE_SET_REQUEST_Callback();
                    #endif /* (ProtocovUSB_DISPATCH_AUDIO_CLASS_MUTE_SET_REQUEST_CALLBACK) */

                        /* Entity ID Control Selector is MUTE */
                        ProtocovUSB_currentTD.wCount = 1u;
                        ProtocovUSB_currentTD.pData  = &ProtocovUSB_currentMute;
                        
                        requestHandled = ProtocovUSB_InitControlWrite();
                    }
                    else if (wValueHi == ProtocovUSB_VOLUME_CONTROL)
                    {
                        /* `#START VOLUME_CONTROL_SET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                    #ifdef ProtocovUSB_DISPATCH_AUDIO_CLASS_VOLUME_CONTROL_SET_REQUEST_CALLBACK
                        ProtocovUSB_DispatchAUDIOClass_VOLUME_CONTROL_SET_REQUEST_Callback();
                    #endif /* (ProtocovUSB_DISPATCH_AUDIO_CLASS_VOLUME_CONTROL_SET_REQUEST_CALLBACK) */

                        /* Entity ID Control Selector is VOLUME */
                        ProtocovUSB_currentTD.wCount = ProtocovUSB_VOLUME_LEN;
                        ProtocovUSB_currentTD.pData  = ProtocovUSB_currentVolume;
                        
                        requestHandled = ProtocovUSB_InitControlWrite();
                    }
                    else
                    {
                        /* `#START OTHER_SET_CUR_REQUESTS` Place other request handler here */

                        /* `#END` */

                    #ifdef ProtocovUSB_DISPATCH_AUDIO_CLASS_OTHER_SET_CUR_REQUESTS_CALLBACK
                        ProtocovUSB_DispatchAUDIOClass_OTHER_SET_CUR_REQUESTS_Callback();
                    #endif /* (ProtocovUSB_DISPATCH_AUDIO_CLASS_OTHER_SET_CUR_REQUESTS_CALLBACK) */
                    }
                #endif /*  ProtocovUSB_ENABLE_AUDIO_STREAMING */
                
                
                    /* `#START AUDIO_CONTROL_SEL_REQUESTS` Place other request handler here */

                    /* `#END` */
                    
                #ifdef ProtocovUSB_DISPATCH_AUDIO_CLASS_AUDIO_CONTROL_SEL_REQUESTS_CALLBACK
                    ProtocovUSB_DispatchAUDIOClass_AUDIO_CONTROL_SEL_REQUESTS_Callback();
                #endif /* (ProtocovUSB_DISPATCH_AUDIO_CLASS_AUDIO_CONTROL_SEL_REQUESTS_CALLBACK) */
                break;

                default:
                    /* Do not handle this request. */
                break;
            }
        }
        else
        {
            /* Do not handle other requests recipients. */
        }
    }

    return (requestHandled);
}
#endif /* (USER_SUPPLIED_AUDIO_HANDLER) */


/*******************************************************************************
* Additional user functions supporting AUDIO Requests
********************************************************************************/

/* `#START AUDIO_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif  /* (ProtocovUSB_ENABLE_AUDIO_CLASS) */


/* [] END OF FILE */
