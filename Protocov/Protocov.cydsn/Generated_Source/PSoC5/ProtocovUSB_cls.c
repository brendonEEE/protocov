/***************************************************************************//**
* \file ProtocovUSB_cls.c
* \version 3.20
*
* \brief
*  This file contains the USB Class request handler.
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ProtocovUSB_pvt.h"
#include "cyapicallbacks.h"

#if(ProtocovUSB_EXTERN_CLS == ProtocovUSB_FALSE)

/***************************************
* User Implemented Class Driver Declarations.
***************************************/
/* `#START USER_DEFINED_CLASS_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: ProtocovUSB_DispatchClassRqst
****************************************************************************//**
*  This routine dispatches class specific requests depend on interface class.
*
* \return
*  requestHandled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 ProtocovUSB_DispatchClassRqst(void) 
{
    uint8 interfaceNumber;
    uint8 requestHandled = ProtocovUSB_FALSE;

    /* Get interface to which request is intended. */
    switch (ProtocovUSB_bmRequestTypeReg & ProtocovUSB_RQST_RCPT_MASK)
    {
        case ProtocovUSB_RQST_RCPT_IFC:
            /* Class-specific request directed to interface: wIndexLoReg 
            * contains interface number.
            */
            interfaceNumber = (uint8) ProtocovUSB_wIndexLoReg;
            break;
        
        case ProtocovUSB_RQST_RCPT_EP:
            /* Class-specific request directed to endpoint: wIndexLoReg contains 
            * endpoint number. Find interface related to endpoint. 
            */
            interfaceNumber = ProtocovUSB_EP[ProtocovUSB_wIndexLoReg & ProtocovUSB_DIR_UNUSED].interface;
            break;
            
        default:
            /* Default interface is zero. */
            interfaceNumber = 0u;
            break;
    }
    
    /* Check that interface is within acceptable range */
    if (interfaceNumber <= ProtocovUSB_MAX_INTERFACES_NUMBER)
    {
    #if (defined(ProtocovUSB_ENABLE_HID_CLASS)   || \
         defined(ProtocovUSB_ENABLE_AUDIO_CLASS) || \
         defined(ProtocovUSB_ENABLE_CDC_CLASS)   || \
         ProtocovUSB_ENABLE_MSC_CLASS)

        /* Handle class request depends on interface type. */
        switch (ProtocovUSB_interfaceClass[interfaceNumber])
        {
        #if defined(ProtocovUSB_ENABLE_HID_CLASS)
            case ProtocovUSB_CLASS_HID:
                requestHandled = ProtocovUSB_DispatchHIDClassRqst();
                break;
        #endif /* (ProtocovUSB_ENABLE_HID_CLASS) */
                
        #if defined(ProtocovUSB_ENABLE_AUDIO_CLASS)
            case ProtocovUSB_CLASS_AUDIO:
                requestHandled = ProtocovUSB_DispatchAUDIOClassRqst();
                break;
        #endif /* (ProtocovUSB_CLASS_AUDIO) */
                
        #if defined(ProtocovUSB_ENABLE_CDC_CLASS)
            case ProtocovUSB_CLASS_CDC:
                requestHandled = ProtocovUSB_DispatchCDCClassRqst();
                break;
        #endif /* (ProtocovUSB_ENABLE_CDC_CLASS) */
            
        #if (ProtocovUSB_ENABLE_MSC_CLASS)
            case ProtocovUSB_CLASS_MSD:
            #if (ProtocovUSB_HANDLE_MSC_REQUESTS)
                /* MSC requests are handled by the component. */
                requestHandled = ProtocovUSB_DispatchMSCClassRqst();
            #elif defined(ProtocovUSB_DISPATCH_MSC_CLASS_RQST_CALLBACK)
                /* MSC requests are handled by user defined callbcak. */
                requestHandled = ProtocovUSB_DispatchMSCClassRqst_Callback();
            #else
                /* MSC requests are not handled. */
                requestHandled = ProtocovUSB_FALSE;
            #endif /* (ProtocovUSB_HANDLE_MSC_REQUESTS) */
                break;
        #endif /* (ProtocovUSB_ENABLE_MSC_CLASS) */
            
            default:
                /* Request is not handled: unknown class request type. */
                requestHandled = ProtocovUSB_FALSE;
                break;
        }
    #endif /* Class support is enabled */
    }
    
    /* `#START USER_DEFINED_CLASS_CODE` Place your Class request here */

    /* `#END` */

#ifdef ProtocovUSB_DISPATCH_CLASS_RQST_CALLBACK
    if (ProtocovUSB_FALSE == requestHandled)
    {
        requestHandled = ProtocovUSB_DispatchClassRqst_Callback(interfaceNumber);
    }
#endif /* (ProtocovUSB_DISPATCH_CLASS_RQST_CALLBACK) */

    return (requestHandled);
}


/*******************************************************************************
* Additional user functions supporting Class Specific Requests
********************************************************************************/

/* `#START CLASS_SPECIFIC_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif /* ProtocovUSB_EXTERN_CLS */


/* [] END OF FILE */
