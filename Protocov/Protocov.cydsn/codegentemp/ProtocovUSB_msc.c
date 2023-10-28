/***************************************************************************//**
* \file ProtocovUSB_cdc.c
* \version 3.20
*
* \brief
*  This file contains the USB MSC Class request handler and global API for MSC 
*  class.
*
* Related Document:
*  Universal Serial Bus Class Definitions for Communication Devices Version 1.1
*
********************************************************************************
* \copyright
* Copyright 2012-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ProtocovUSB_msc.h"
#include "ProtocovUSB_pvt.h"
#include "cyapicallbacks.h"

#if (ProtocovUSB_HANDLE_MSC_REQUESTS)

/***************************************
*          Internal variables
***************************************/

static uint8 ProtocovUSB_lunCount = ProtocovUSB_MSC_LUN_NUMBER;


/*******************************************************************************
* Function Name: ProtocovUSB_DispatchMSCClassRqst
****************************************************************************//**
*   
*  \internal 
*  This routine dispatches MSC class requests.
*
* \return
*  Status of request processing: handled or not handled.
*
* \globalvars
*  ProtocovUSB_lunCount - stores number of LUN (logical units).
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 ProtocovUSB_DispatchMSCClassRqst(void) 
{
    uint8 requestHandled = ProtocovUSB_FALSE;
    
    /* Get request data. */
    uint16 value  = ProtocovUSB_GET_UINT16(ProtocovUSB_wValueHiReg,  ProtocovUSB_wValueLoReg);
    uint16 dataLength = ProtocovUSB_GET_UINT16(ProtocovUSB_wLengthHiReg, ProtocovUSB_wLengthLoReg);
       
    /* Check request direction: D2H or H2D. */
    if (0u != (ProtocovUSB_bmRequestTypeReg & ProtocovUSB_RQST_DIR_D2H))
    {
        /* Handle direction from device to host. */
        
        if (ProtocovUSB_MSC_GET_MAX_LUN == ProtocovUSB_bRequestReg)
        {
            /* Check request fields. */
            if ((value  == ProtocovUSB_MSC_GET_MAX_LUN_WVALUE) &&
                (dataLength == ProtocovUSB_MSC_GET_MAX_LUN_WLENGTH))
            {
                /* Reply to Get Max LUN request: setup control read. */
                ProtocovUSB_currentTD.pData = &ProtocovUSB_lunCount;
                ProtocovUSB_currentTD.count =  ProtocovUSB_MSC_GET_MAX_LUN_WLENGTH;
                
                requestHandled  = ProtocovUSB_InitControlRead();
            }
        }
    }
    else
    {
        /* Handle direction from host to device. */
        
        if (ProtocovUSB_MSC_RESET == ProtocovUSB_bRequestReg)
        {
            /* Check request fields. */
            if ((value  == ProtocovUSB_MSC_RESET_WVALUE) &&
                (dataLength == ProtocovUSB_MSC_RESET_WLENGTH))
            {
                /* Handle to Bulk-Only Reset request: no data control transfer. */
                ProtocovUSB_currentTD.count = ProtocovUSB_MSC_RESET_WLENGTH;
                
            #ifdef ProtocovUSB_DISPATCH_MSC_CLASS_MSC_RESET_RQST_CALLBACK
                ProtocovUSB_DispatchMSCClass_MSC_RESET_RQST_Callback();
            #endif /* (ProtocovUSB_DISPATCH_MSC_CLASS_MSC_RESET_RQST_CALLBACK) */
                
                requestHandled = ProtocovUSB_InitNoDataControlTransfer();
            }
        }
    }
    
    return (requestHandled);
}


/*******************************************************************************
* Function Name: ProtocovUSB_MSC_SetLunCount
****************************************************************************//**
*
*  This function sets the number of logical units supported in the application. 
*  The default number of logical units is set in the component customizer.
*
*  \param lunCount: Count of the logical units. Valid range is between 1 and 16.
*
*
* \globalvars
*  ProtocovUSB_lunCount - stores number of LUN (logical units).
*
* \reentrant
*  No.
*
*******************************************************************************/
void ProtocovUSB_MSC_SetLunCount(uint8 lunCount) 
{
    ProtocovUSB_lunCount = (lunCount - 1u);
}


/*******************************************************************************
* Function Name: ProtocovUSB_MSC_GetLunCount
****************************************************************************//**
*
*  This function returns the number of logical units.
*
* \return
*   Number of the logical units.
*
* \globalvars
*  ProtocovUSB_lunCount - stores number of LUN (logical units).
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 ProtocovUSB_MSC_GetLunCount(void) 
{
    return (ProtocovUSB_lunCount + 1u);
}   

#endif /* (ProtocovUSB_HANDLE_MSC_REQUESTS) */


/* [] END OF FILE */
