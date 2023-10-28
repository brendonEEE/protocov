/***************************************************************************//**
* \file ProtocovUSB_std.c
* \version 3.20
*
* \brief
*  This file contains the USB Standard request handler.
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ProtocovUSB_pvt.h"

/***************************************
*   Static data allocation
***************************************/

#if defined(ProtocovUSB_ENABLE_FWSN_STRING)
    static volatile uint8* ProtocovUSB_fwSerialNumberStringDescriptor;
    static volatile uint8  ProtocovUSB_snStringConfirm = ProtocovUSB_FALSE;
#endif  /* (ProtocovUSB_ENABLE_FWSN_STRING) */

#if defined(ProtocovUSB_ENABLE_FWSN_STRING)
    /***************************************************************************
    * Function Name: ProtocovUSB_SerialNumString
    ************************************************************************//**
    *
    *  This function is available only when the User Call Back option in the 
    *  Serial Number String descriptor properties is selected. Application 
    *  firmware can provide the source of the USB device serial number string 
    *  descriptor during run time. The default string is used if the application 
    *  firmware does not use this function or sets the wrong string descriptor.
    *
    *  \param snString:  Pointer to the user-defined string descriptor. The 
    *  string descriptor should meet the Universal Serial Bus Specification 
    *  revision 2.0 chapter 9.6.7
    *  Offset|Size|Value|Description
    *  ------|----|------|---------------------------------
    *  0     |1   |N     |Size of this descriptor in bytes
    *  1     |1   |0x03  |STRING Descriptor Type
    *  2     |N-2 |Number|UNICODE encoded string
    *  
    * *For example:* uint8 snString[16]={0x0E,0x03,'F',0,'W',0,'S',0,'N',0,'0',0,'1',0};
    *
    * \reentrant
    *  No.
    *
    ***************************************************************************/
    void  ProtocovUSB_SerialNumString(uint8 snString[]) 
    {
        ProtocovUSB_snStringConfirm = ProtocovUSB_FALSE;
        
        if (snString != NULL)
        {
            /* Check descriptor validation */
            if ((snString[0u] > 1u) && (snString[1u] == ProtocovUSB_DESCR_STRING))
            {
                ProtocovUSB_fwSerialNumberStringDescriptor = snString;
                ProtocovUSB_snStringConfirm = ProtocovUSB_TRUE;
            }
        }
    }
#endif  /* ProtocovUSB_ENABLE_FWSN_STRING */


/*******************************************************************************
* Function Name: ProtocovUSB_HandleStandardRqst
****************************************************************************//**
*
*  This Routine dispatches standard requests
*
*
* \return
*  TRUE if request handled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 ProtocovUSB_HandleStandardRqst(void) 
{
    uint8 requestHandled = ProtocovUSB_FALSE;
    uint8 interfaceNumber;
    uint8 configurationN;
    uint8 bmRequestType = ProtocovUSB_bmRequestTypeReg;

#if defined(ProtocovUSB_ENABLE_STRINGS)
    volatile uint8 *pStr = 0u;
    #if defined(ProtocovUSB_ENABLE_DESCRIPTOR_STRINGS)
        uint8 nStr;
        uint8 descrLength;
    #endif /* (ProtocovUSB_ENABLE_DESCRIPTOR_STRINGS) */
#endif /* (ProtocovUSB_ENABLE_STRINGS) */
    
    static volatile uint8 ProtocovUSB_tBuffer[ProtocovUSB_STATUS_LENGTH_MAX];
    const T_ProtocovUSB_LUT CYCODE *pTmp;

    ProtocovUSB_currentTD.count = 0u;

    if (ProtocovUSB_RQST_DIR_D2H == (bmRequestType & ProtocovUSB_RQST_DIR_MASK))
    {
        /* Control Read */
        switch (ProtocovUSB_bRequestReg)
        {
            case ProtocovUSB_GET_DESCRIPTOR:
                if (ProtocovUSB_DESCR_DEVICE ==ProtocovUSB_wValueHiReg)
                {
                    pTmp = ProtocovUSB_GetDeviceTablePtr();
                    ProtocovUSB_currentTD.pData = (volatile uint8 *)pTmp->p_list;
                    ProtocovUSB_currentTD.count = ProtocovUSB_DEVICE_DESCR_LENGTH;
                    
                    requestHandled  = ProtocovUSB_InitControlRead();
                }
                else if (ProtocovUSB_DESCR_CONFIG == ProtocovUSB_wValueHiReg)
                {
                    pTmp = ProtocovUSB_GetConfigTablePtr((uint8) ProtocovUSB_wValueLoReg);
                    
                    /* Verify that requested descriptor exists */
                    if (pTmp != NULL)
                    {
                        ProtocovUSB_currentTD.pData = (volatile uint8 *)pTmp->p_list;
                        ProtocovUSB_currentTD.count = (uint16)((uint16)(ProtocovUSB_currentTD.pData)[ProtocovUSB_CONFIG_DESCR_TOTAL_LENGTH_HI] << 8u) | \
                                                                            (ProtocovUSB_currentTD.pData)[ProtocovUSB_CONFIG_DESCR_TOTAL_LENGTH_LOW];
                        requestHandled  = ProtocovUSB_InitControlRead();
                    }
                }
                
            #if(ProtocovUSB_BOS_ENABLE)
                else if (ProtocovUSB_DESCR_BOS == ProtocovUSB_wValueHiReg)
                {
                    pTmp = ProtocovUSB_GetBOSPtr();
                    
                    /* Verify that requested descriptor exists */
                    if (pTmp != NULL)
                    {
                        ProtocovUSB_currentTD.pData = (volatile uint8 *)pTmp;
                        ProtocovUSB_currentTD.count = ((uint16)((uint16)(ProtocovUSB_currentTD.pData)[ProtocovUSB_BOS_DESCR_TOTAL_LENGTH_HI] << 8u)) | \
                                                                             (ProtocovUSB_currentTD.pData)[ProtocovUSB_BOS_DESCR_TOTAL_LENGTH_LOW];
                        requestHandled  = ProtocovUSB_InitControlRead();
                    }
                }
            #endif /*(ProtocovUSB_BOS_ENABLE)*/
            
            #if defined(ProtocovUSB_ENABLE_STRINGS)
                else if (ProtocovUSB_DESCR_STRING == ProtocovUSB_wValueHiReg)
                {
                /* Descriptor Strings */
                #if defined(ProtocovUSB_ENABLE_DESCRIPTOR_STRINGS)
                    nStr = 0u;
                    pStr = (volatile uint8 *) &ProtocovUSB_STRING_DESCRIPTORS[0u];
                    
                    while ((ProtocovUSB_wValueLoReg > nStr) && (*pStr != 0u))
                    {
                        /* Read descriptor length from 1st byte */
                        descrLength = *pStr;
                        /* Move to next string descriptor */
                        pStr = &pStr[descrLength];
                        nStr++;
                    }
                #endif /* (ProtocovUSB_ENABLE_DESCRIPTOR_STRINGS) */
                
                /* Microsoft OS String */
                #if defined(ProtocovUSB_ENABLE_MSOS_STRING)
                    if (ProtocovUSB_STRING_MSOS == ProtocovUSB_wValueLoReg)
                    {
                        pStr = (volatile uint8 *)& ProtocovUSB_MSOS_DESCRIPTOR[0u];
                    }
                #endif /* (ProtocovUSB_ENABLE_MSOS_STRING) */
                
                /* SN string */
                #if defined(ProtocovUSB_ENABLE_SN_STRING)
                    if ((ProtocovUSB_wValueLoReg != 0u) && 
                        (ProtocovUSB_wValueLoReg == ProtocovUSB_DEVICE0_DESCR[ProtocovUSB_DEVICE_DESCR_SN_SHIFT]))
                    {
                    #if defined(ProtocovUSB_ENABLE_IDSN_STRING)
                        /* Read DIE ID and generate string descriptor in RAM */
                        ProtocovUSB_ReadDieID(ProtocovUSB_idSerialNumberStringDescriptor);
                        pStr = ProtocovUSB_idSerialNumberStringDescriptor;
                    #elif defined(ProtocovUSB_ENABLE_FWSN_STRING)
                        
                        if(ProtocovUSB_snStringConfirm != ProtocovUSB_FALSE)
                        {
                            pStr = ProtocovUSB_fwSerialNumberStringDescriptor;
                        }
                        else
                        {
                            pStr = (volatile uint8 *)&ProtocovUSB_SN_STRING_DESCRIPTOR[0u];
                        }
                    #else
                        pStr = (volatile uint8 *)&ProtocovUSB_SN_STRING_DESCRIPTOR[0u];
                    #endif  /* (ProtocovUSB_ENABLE_IDSN_STRING) */
                    }
                #endif /* (ProtocovUSB_ENABLE_SN_STRING) */
                
                    if (*pStr != 0u)
                    {
                        ProtocovUSB_currentTD.count = *pStr;
                        ProtocovUSB_currentTD.pData = pStr;
                        requestHandled  = ProtocovUSB_InitControlRead();
                    }
                }
            #endif /*  ProtocovUSB_ENABLE_STRINGS */
                else
                {
                    requestHandled = ProtocovUSB_DispatchClassRqst();
                }
                break;
                
            case ProtocovUSB_GET_STATUS:
                switch (bmRequestType & ProtocovUSB_RQST_RCPT_MASK)
                {
                    case ProtocovUSB_RQST_RCPT_EP:
                        ProtocovUSB_currentTD.count = ProtocovUSB_EP_STATUS_LENGTH;
                        ProtocovUSB_tBuffer[0u]     = ProtocovUSB_EP[ProtocovUSB_wIndexLoReg & ProtocovUSB_DIR_UNUSED].hwEpState;
                        ProtocovUSB_tBuffer[1u]     = 0u;
                        ProtocovUSB_currentTD.pData = &ProtocovUSB_tBuffer[0u];
                        
                        requestHandled  = ProtocovUSB_InitControlRead();
                        break;
                    case ProtocovUSB_RQST_RCPT_DEV:
                        ProtocovUSB_currentTD.count = ProtocovUSB_DEVICE_STATUS_LENGTH;
                        ProtocovUSB_tBuffer[0u]     = ProtocovUSB_deviceStatus;
                        ProtocovUSB_tBuffer[1u]     = 0u;
                        ProtocovUSB_currentTD.pData = &ProtocovUSB_tBuffer[0u];
                        
                        requestHandled  = ProtocovUSB_InitControlRead();
                        break;
                    default:    /* requestHandled is initialized as FALSE by default */
                        break;
                }
                break;
                
            case ProtocovUSB_GET_CONFIGURATION:
                ProtocovUSB_currentTD.count = 1u;
                ProtocovUSB_currentTD.pData = (volatile uint8 *) &ProtocovUSB_configuration;
                requestHandled  = ProtocovUSB_InitControlRead();
                break;
                
            case ProtocovUSB_GET_INTERFACE:
                ProtocovUSB_currentTD.count = 1u;
                ProtocovUSB_currentTD.pData = (volatile uint8 *) &ProtocovUSB_interfaceSetting[ProtocovUSB_wIndexLoReg];
                requestHandled  = ProtocovUSB_InitControlRead();
                break;
                
            default: /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    else
    {
        /* Control Write */
        switch (ProtocovUSB_bRequestReg)
        {
            case ProtocovUSB_SET_ADDRESS:
                /* Store address to be set in ProtocovUSB_NoDataControlStatusStage(). */
                ProtocovUSB_deviceAddress = (uint8) ProtocovUSB_wValueLoReg;
                requestHandled = ProtocovUSB_InitNoDataControlTransfer();
                break;
                
            case ProtocovUSB_SET_CONFIGURATION:
                configurationN = ProtocovUSB_wValueLoReg;
                
                /* Verify that configuration descriptor exists */
                if(configurationN > 0u)
                {
                    pTmp = ProtocovUSB_GetConfigTablePtr((uint8) configurationN - 1u);
                }
                
                /* Responds with a Request Error when configuration number is invalid */
                if (((configurationN > 0u) && (pTmp != NULL)) || (configurationN == 0u))
                {
                    /* Set new configuration if it has been changed */
                    if(configurationN != ProtocovUSB_configuration)
                    {
                        ProtocovUSB_configuration = (uint8) configurationN;
                        ProtocovUSB_configurationChanged = ProtocovUSB_TRUE;
                        ProtocovUSB_Config(ProtocovUSB_TRUE);
                    }
                    requestHandled = ProtocovUSB_InitNoDataControlTransfer();
                }
                break;
                
            case ProtocovUSB_SET_INTERFACE:
                if (0u != ProtocovUSB_ValidateAlternateSetting())
                {
                    /* Get interface number from the request. */
                    interfaceNumber = ProtocovUSB_wIndexLoReg;
                    ProtocovUSB_interfaceNumber = (uint8) ProtocovUSB_wIndexLoReg;
                     
                    /* Check if alternate settings is changed for interface. */
                    if (ProtocovUSB_interfaceSettingLast[interfaceNumber] != ProtocovUSB_interfaceSetting[interfaceNumber])
                    {
                        ProtocovUSB_configurationChanged = ProtocovUSB_TRUE;
                    
                        /* Change alternate setting for the endpoints. */
                    #if (ProtocovUSB_EP_MANAGEMENT_MANUAL && ProtocovUSB_EP_ALLOC_DYNAMIC)
                        ProtocovUSB_Config(ProtocovUSB_FALSE);
                    #else
                        ProtocovUSB_ConfigAltChanged();
                    #endif /* (ProtocovUSB_EP_MANAGEMENT_MANUAL && ProtocovUSB_EP_ALLOC_DYNAMIC) */
                    }
                    
                    requestHandled = ProtocovUSB_InitNoDataControlTransfer();
                }
                break;
                
            case ProtocovUSB_CLEAR_FEATURE:
                switch (bmRequestType & ProtocovUSB_RQST_RCPT_MASK)
                {
                    case ProtocovUSB_RQST_RCPT_EP:
                        if (ProtocovUSB_wValueLoReg == ProtocovUSB_ENDPOINT_HALT)
                        {
                            requestHandled = ProtocovUSB_ClearEndpointHalt();
                        }
                        break;
                    case ProtocovUSB_RQST_RCPT_DEV:
                        /* Clear device REMOTE_WAKEUP */
                        if (ProtocovUSB_wValueLoReg == ProtocovUSB_DEVICE_REMOTE_WAKEUP)
                        {
                            ProtocovUSB_deviceStatus &= (uint8)~ProtocovUSB_DEVICE_STATUS_REMOTE_WAKEUP;
                            requestHandled = ProtocovUSB_InitNoDataControlTransfer();
                        }
                        break;
                    case ProtocovUSB_RQST_RCPT_IFC:
                        /* Validate interfaceNumber */
                        if (ProtocovUSB_wIndexLoReg < ProtocovUSB_MAX_INTERFACES_NUMBER)
                        {
                            ProtocovUSB_interfaceStatus[ProtocovUSB_wIndexLoReg] &= (uint8) ~ProtocovUSB_wValueLoReg;
                            requestHandled = ProtocovUSB_InitNoDataControlTransfer();
                        }
                        break;
                    default:    /* requestHandled is initialized as FALSE by default */
                        break;
                }
                break;
                
            case ProtocovUSB_SET_FEATURE:
                switch (bmRequestType & ProtocovUSB_RQST_RCPT_MASK)
                {
                    case ProtocovUSB_RQST_RCPT_EP:
                        if (ProtocovUSB_wValueLoReg == ProtocovUSB_ENDPOINT_HALT)
                        {
                            requestHandled = ProtocovUSB_SetEndpointHalt();
                        }
                        break;
                        
                    case ProtocovUSB_RQST_RCPT_DEV:
                        /* Set device REMOTE_WAKEUP */
                        if (ProtocovUSB_wValueLoReg == ProtocovUSB_DEVICE_REMOTE_WAKEUP)
                        {
                            ProtocovUSB_deviceStatus |= ProtocovUSB_DEVICE_STATUS_REMOTE_WAKEUP;
                            requestHandled = ProtocovUSB_InitNoDataControlTransfer();
                        }
                        break;
                        
                    case ProtocovUSB_RQST_RCPT_IFC:
                        /* Validate interfaceNumber */
                        if (ProtocovUSB_wIndexLoReg < ProtocovUSB_MAX_INTERFACES_NUMBER)
                        {
                            ProtocovUSB_interfaceStatus[ProtocovUSB_wIndexLoReg] &= (uint8) ~ProtocovUSB_wValueLoReg;
                            requestHandled = ProtocovUSB_InitNoDataControlTransfer();
                        }
                        break;
                    
                    default:    /* requestHandled is initialized as FALSE by default */
                        break;
                }
                break;
                
            default:    /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    
    return (requestHandled);
}


#if defined(ProtocovUSB_ENABLE_IDSN_STRING)
    /***************************************************************************
    * Function Name: ProtocovUSB_ReadDieID
    ************************************************************************//**
    *
    *  This routine read Die ID and generate Serial Number string descriptor.
    *
    *  \param descr:  pointer on string descriptor. This string size has to be equal or
    *          greater than ProtocovUSB_IDSN_DESCR_LENGTH.
    *
    *
    * \reentrant
    *  No.
    *
    ***************************************************************************/
    void ProtocovUSB_ReadDieID(uint8 descr[]) 
    {
        const char8 CYCODE hex[] = "0123456789ABCDEF";
        uint8 i;
        uint8 j = 0u;
        uint8 uniqueId[8u];

        if (NULL != descr)
        {
            /* Initialize descriptor header. */
            descr[0u] = ProtocovUSB_IDSN_DESCR_LENGTH;
            descr[1u] = ProtocovUSB_DESCR_STRING;
            
            /* Unique ID size is 8 bytes. */
            CyGetUniqueId((uint32 *) uniqueId);

            /* Fill descriptor with unique device ID. */
            for (i = 2u; i < ProtocovUSB_IDSN_DESCR_LENGTH; i += 4u)
            {
                descr[i]      = (uint8) hex[(uniqueId[j] >> 4u)];
                descr[i + 1u] = 0u;
                descr[i + 2u] = (uint8) hex[(uniqueId[j] & 0x0Fu)];
                descr[i + 3u] = 0u;
                ++j;
            }
        }
    }
#endif /* (ProtocovUSB_ENABLE_IDSN_STRING) */


/*******************************************************************************
* Function Name: ProtocovUSB_ConfigReg
****************************************************************************//**
*
*  This routine configures hardware registers from the variables.
*  It is called from ProtocovUSB_Config() function and from RestoreConfig
*  after Wakeup.
*
*******************************************************************************/
void ProtocovUSB_ConfigReg(void) 
{
    uint8 ep;

#if (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)
    uint8 epType = 0u;
#endif /* (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO) */

    /* Go thought all endpoints and set hardware configuration */
    for (ep = ProtocovUSB_EP1; ep < ProtocovUSB_MAX_EP; ++ep)
    {
        ProtocovUSB_ARB_EP_BASE.arbEp[ep].epCfg = ProtocovUSB_ARB_EPX_CFG_DEFAULT;
        
    #if (ProtocovUSB_EP_MANAGEMENT_DMA)
        /* Enable arbiter endpoint interrupt sources */
        ProtocovUSB_ARB_EP_BASE.arbEp[ep].epIntEn = ProtocovUSB_ARB_EPX_INT_MASK;
    #endif /* (ProtocovUSB_EP_MANAGEMENT_DMA) */
    
        if (ProtocovUSB_EP[ep].epMode != ProtocovUSB_MODE_DISABLE)
        {
            if (0u != (ProtocovUSB_EP[ep].addr & ProtocovUSB_DIR_IN))
            {
                ProtocovUSB_SIE_EP_BASE.sieEp[ep].epCr0 = ProtocovUSB_MODE_NAK_IN;
                
            #if (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO && CY_PSOC4)
                /* Clear DMA_TERMIN for IN endpoint. */
                ProtocovUSB_ARB_EP_BASE.arbEp[ep].epIntEn &= (uint32) ~ProtocovUSB_ARB_EPX_INT_DMA_TERMIN;
            #endif /* (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO && CY_PSOC4) */
            }
            else
            {
                ProtocovUSB_SIE_EP_BASE.sieEp[ep].epCr0 = ProtocovUSB_MODE_NAK_OUT;

            #if (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)
                /* (CY_PSOC4): DMA_TERMIN for OUT endpoint is set above. */
                
                /* Prepare endpoint type mask. */
                epType |= (uint8) (0x01u << (ep - ProtocovUSB_EP1));
            #endif /* (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO) */
            }
        }
        else
        {
            ProtocovUSB_SIE_EP_BASE.sieEp[ep].epCr0 = ProtocovUSB_MODE_STALL_DATA_EP;
        }
        
    #if (!ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)
        #if (CY_PSOC4)
            ProtocovUSB_ARB_EP16_BASE.arbEp[ep].rwRa16  = (uint32) ProtocovUSB_EP[ep].buffOffset;
            ProtocovUSB_ARB_EP16_BASE.arbEp[ep].rwWa16  = (uint32) ProtocovUSB_EP[ep].buffOffset;
        #else
            ProtocovUSB_ARB_EP_BASE.arbEp[ep].rwRa    = LO8(ProtocovUSB_EP[ep].buffOffset);
            ProtocovUSB_ARB_EP_BASE.arbEp[ep].rwRaMsb = HI8(ProtocovUSB_EP[ep].buffOffset);
            ProtocovUSB_ARB_EP_BASE.arbEp[ep].rwWa    = LO8(ProtocovUSB_EP[ep].buffOffset);
            ProtocovUSB_ARB_EP_BASE.arbEp[ep].rwWaMsb = HI8(ProtocovUSB_EP[ep].buffOffset);
        #endif /* (CY_PSOC4) */
    #endif /* (!ProtocovUSB_EP_MANAGEMENT_DMA_AUTO) */
    }

#if (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)
     /* BUF_SIZE depend on DMA_THRESS value:0x55-32 bytes  0x44-16 bytes 0x33-8 bytes 0x22-4 bytes 0x11-2 bytes */
    ProtocovUSB_BUF_SIZE_REG = ProtocovUSB_DMA_BUF_SIZE;

    /* Configure DMA burst threshold */
#if (CY_PSOC4)
    ProtocovUSB_DMA_THRES16_REG   = ProtocovUSB_DMA_BYTES_PER_BURST;
#else
    ProtocovUSB_DMA_THRES_REG     = ProtocovUSB_DMA_BYTES_PER_BURST;
    ProtocovUSB_DMA_THRES_MSB_REG = 0u;
#endif /* (CY_PSOC4) */
    ProtocovUSB_EP_ACTIVE_REG = ProtocovUSB_DEFAULT_ARB_INT_EN;
    ProtocovUSB_EP_TYPE_REG   = epType;
    
    /* Cfg_cmp bit set to 1 once configuration is complete. */
    /* Lock arbiter configtuation */
    ProtocovUSB_ARB_CFG_REG |= (uint8)  ProtocovUSB_ARB_CFG_CFG_CMP;
    /* Cfg_cmp bit set to 0 during configuration of PFSUSB Registers. */
    ProtocovUSB_ARB_CFG_REG &= (uint8) ~ProtocovUSB_ARB_CFG_CFG_CMP;

#endif /* (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO) */

    /* Enable interrupt SIE interurpt source from EP0-EP1 */
    ProtocovUSB_SIE_EP_INT_EN_REG = (uint8) ProtocovUSB_DEFAULT_SIE_EP_INT_EN;
}


/*******************************************************************************
* Function Name: ProtocovUSB_EpStateInit
****************************************************************************//**
*
*  This routine initialize state of Data end points based of its type: 
*   IN  - ProtocovUSB_IN_BUFFER_EMPTY (ProtocovUSB_EVENT_PENDING)
*   OUT - ProtocovUSB_OUT_BUFFER_EMPTY (ProtocovUSB_NO_EVENT_PENDING)
*
*******************************************************************************/
void ProtocovUSB_EpStateInit(void) 
{
    uint8 i;

    for (i = ProtocovUSB_EP1; i < ProtocovUSB_MAX_EP; i++)
    { 
        if (0u != (ProtocovUSB_EP[i].addr & ProtocovUSB_DIR_IN))
        {
            /* IN Endpoint */
            ProtocovUSB_EP[i].apiEpState = ProtocovUSB_EVENT_PENDING;
        }
        else
        {
            /* OUT Endpoint */
            ProtocovUSB_EP[i].apiEpState = ProtocovUSB_NO_EVENT_PENDING;
        }
    }
                    
}


/*******************************************************************************
* Function Name: ProtocovUSB_Config
****************************************************************************//**
*
*  This routine configures endpoints for the entire configuration by scanning
*  the configuration descriptor.
*
*  \param clearAltSetting: It configures the bAlternateSetting 0 for each interface.
*
* ProtocovUSB_interfaceClass - Initialized class array for each interface.
*   It is used for handling Class specific requests depend on interface class.
*   Different classes in multiple Alternate settings does not supported.
*
* \reentrant
*  No.
*
*******************************************************************************/
void ProtocovUSB_Config(uint8 clearAltSetting) 
{
    uint8 ep;
    uint8 curEp;
    uint8 i;
    uint8 epType;
    const uint8 *pDescr;
    
    #if (!ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)
        uint16 buffCount = 0u;
    #endif /* (!ProtocovUSB_EP_MANAGEMENT_DMA_AUTO) */

    const T_ProtocovUSB_LUT CYCODE *pTmp;
    const T_ProtocovUSB_EP_SETTINGS_BLOCK CYCODE *pEP;

    /* Clear endpoints settings */
    for (ep = 0u; ep < ProtocovUSB_MAX_EP; ++ep)
    {
        ProtocovUSB_EP[ep].attrib     = 0u;
        ProtocovUSB_EP[ep].hwEpState  = 0u;
        ProtocovUSB_EP[ep].epToggle   = 0u;
        ProtocovUSB_EP[ep].bufferSize = 0u;
        ProtocovUSB_EP[ep].interface  = 0u;
        ProtocovUSB_EP[ep].apiEpState = ProtocovUSB_NO_EVENT_PENDING;
        ProtocovUSB_EP[ep].epMode     = ProtocovUSB_MODE_DISABLE;   
    }

    /* Clear Alternate settings for all interfaces. */
    if (0u != clearAltSetting)
    {
        for (i = 0u; i < ProtocovUSB_MAX_INTERFACES_NUMBER; ++i)
        {
            ProtocovUSB_interfaceSetting[i]     = 0u;
            ProtocovUSB_interfaceSettingLast[i] = 0u;
        }
    }

    /* Init Endpoints and Device Status if configured */
    if (ProtocovUSB_configuration > 0u)
    {
        #if defined(ProtocovUSB_ENABLE_CDC_CLASS)
            uint8 cdcComNums = 0u;
        #endif  /* (ProtocovUSB_ENABLE_CDC_CLASS) */  

        pTmp = ProtocovUSB_GetConfigTablePtr(ProtocovUSB_configuration - 1u);
        
        /* Set Power status for current configuration */
        pDescr = (const uint8 *)pTmp->p_list;
        if ((pDescr[ProtocovUSB_CONFIG_DESCR_ATTRIB] & ProtocovUSB_CONFIG_DESCR_ATTRIB_SELF_POWERED) != 0u)
        {
            ProtocovUSB_deviceStatus |= (uint8)  ProtocovUSB_DEVICE_STATUS_SELF_POWERED;
        }
        else
        {
            ProtocovUSB_deviceStatus &= (uint8) ~ProtocovUSB_DEVICE_STATUS_SELF_POWERED;
        }
        
        /* Move to next element */
        pTmp = &pTmp[1u];
        ep = pTmp->c;  /* For this table, c is the number of endpoints configurations  */

        #if (ProtocovUSB_EP_MANAGEMENT_MANUAL && ProtocovUSB_EP_ALLOC_DYNAMIC)
            /* Configure for dynamic EP memory allocation */
            /* p_list points the endpoint setting table. */
            pEP = (T_ProtocovUSB_EP_SETTINGS_BLOCK *) pTmp->p_list;
            
            for (i = 0u; i < ep; i++)
            {     
                /* Compare current Alternate setting with EP Alt */
                if (ProtocovUSB_interfaceSetting[pEP->interface] == pEP->altSetting)
                {                                                          
                    curEp  = pEP->addr & ProtocovUSB_DIR_UNUSED;
                    epType = pEP->attributes & ProtocovUSB_EP_TYPE_MASK;
                    
                    ProtocovUSB_EP[curEp].addr       = pEP->addr;
                    ProtocovUSB_EP[curEp].attrib     = pEP->attributes;
                    ProtocovUSB_EP[curEp].bufferSize = pEP->bufferSize;

                    if (0u != (pEP->addr & ProtocovUSB_DIR_IN))
                    {
                        /* IN Endpoint */
                        ProtocovUSB_EP[curEp].epMode     = ProtocovUSB_GET_ACTIVE_IN_EP_CR0_MODE(epType);
                        ProtocovUSB_EP[curEp].apiEpState = ProtocovUSB_EVENT_PENDING;
                    
                    #if (defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && (ProtocovUSB_MIDI_IN_BUFF_SIZE > 0))
                        if ((pEP->bMisc == ProtocovUSB_CLASS_AUDIO) && (epType == ProtocovUSB_EP_TYPE_BULK))
                        {
                            ProtocovUSB_midi_in_ep = curEp;
                        }
                    #endif  /* (ProtocovUSB_ENABLE_MIDI_STREAMING) */
                    }
                    else
                    {
                        /* OUT Endpoint */
                        ProtocovUSB_EP[curEp].epMode     = ProtocovUSB_GET_ACTIVE_OUT_EP_CR0_MODE(epType);
                        ProtocovUSB_EP[curEp].apiEpState = ProtocovUSB_NO_EVENT_PENDING;
                        
                    #if (defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && (ProtocovUSB_MIDI_OUT_BUFF_SIZE > 0))
                        if ((pEP->bMisc == ProtocovUSB_CLASS_AUDIO) && (epType == ProtocovUSB_EP_TYPE_BULK))
                        {
                            ProtocovUSB_midi_out_ep = curEp;
                        }
                    #endif  /* (ProtocovUSB_ENABLE_MIDI_STREAMING) */
                    }

                #if(defined (ProtocovUSB_ENABLE_CDC_CLASS))
                    if((pEP->bMisc == ProtocovUSB_CLASS_CDC_DATA) ||(pEP->bMisc == ProtocovUSB_CLASS_CDC))
                    {
                        cdcComNums = ProtocovUSB_Cdc_EpInit(pEP, curEp, cdcComNums);
                    }
                #endif  /* (ProtocovUSB_ENABLE_CDC_CLASS) */
                }
                
                pEP = &pEP[1u];
            }
            
        #else
            for (i = ProtocovUSB_EP1; i < ProtocovUSB_MAX_EP; ++i)
            {
                /* p_list points the endpoint setting table. */
                pEP = (const T_ProtocovUSB_EP_SETTINGS_BLOCK CYCODE *) pTmp->p_list;
                /* Find max length for each EP and select it (length could be different in different Alt settings) */
                /* but other settings should be correct with regards to Interface alt Setting */
                
                for (curEp = 0u; curEp < ep; ++curEp)
                {
                    if (i == (pEP->addr & ProtocovUSB_DIR_UNUSED))
                    {
                        /* Compare endpoint buffers size with current size to find greater. */
                        if (ProtocovUSB_EP[i].bufferSize < pEP->bufferSize)
                        {
                            ProtocovUSB_EP[i].bufferSize = pEP->bufferSize;
                        }
                        
                        /* Compare current Alternate setting with EP Alt */
                        if (ProtocovUSB_interfaceSetting[pEP->interface] == pEP->altSetting)
                        {                            
                            ProtocovUSB_EP[i].addr = pEP->addr;
                            ProtocovUSB_EP[i].attrib = pEP->attributes;
                            
                            epType = pEP->attributes & ProtocovUSB_EP_TYPE_MASK;
                            
                            if (0u != (pEP->addr & ProtocovUSB_DIR_IN))
                            {
                                /* IN Endpoint */
                                ProtocovUSB_EP[i].epMode     = ProtocovUSB_GET_ACTIVE_IN_EP_CR0_MODE(epType);
                                ProtocovUSB_EP[i].apiEpState = ProtocovUSB_EVENT_PENDING;
                                
                            #if (defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && (ProtocovUSB_MIDI_IN_BUFF_SIZE > 0))
                                if ((pEP->bMisc == ProtocovUSB_CLASS_AUDIO) && (epType == ProtocovUSB_EP_TYPE_BULK))
                                {
                                    ProtocovUSB_midi_in_ep = i;
                                }
                            #endif  /* (ProtocovUSB_ENABLE_MIDI_STREAMING) */
                            }
                            else
                            {
                                /* OUT Endpoint */
                                ProtocovUSB_EP[i].epMode     = ProtocovUSB_GET_ACTIVE_OUT_EP_CR0_MODE(epType);
                                ProtocovUSB_EP[i].apiEpState = ProtocovUSB_NO_EVENT_PENDING;
                                
                            #if (defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && (ProtocovUSB_MIDI_OUT_BUFF_SIZE > 0))
                                if ((pEP->bMisc == ProtocovUSB_CLASS_AUDIO) && (epType == ProtocovUSB_EP_TYPE_BULK))
                                {
                                    ProtocovUSB_midi_out_ep = i;
                                }
                            #endif  /* (ProtocovUSB_ENABLE_MIDI_STREAMING) */
                            }

                        #if (defined(ProtocovUSB_ENABLE_CDC_CLASS))
                            if((pEP->bMisc == ProtocovUSB_CLASS_CDC_DATA) ||(pEP->bMisc == ProtocovUSB_CLASS_CDC))
                            {
                                cdcComNums = ProtocovUSB_Cdc_EpInit(pEP, i, cdcComNums);
                            }
                        #endif  /* (ProtocovUSB_ENABLE_CDC_CLASS) */

                            #if (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)
                                break;  /* Use first EP setting in Auto memory management */
                            #endif /* (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO) */
                        }
                    }
                    
                    pEP = &pEP[1u];
                }
            }
        #endif /*  (ProtocovUSB_EP_MANAGEMENT_MANUAL && ProtocovUSB_EP_ALLOC_DYNAMIC) */

        /* Init class array for each interface and interface number for each EP.
        *  It is used for handling Class specific requests directed to either an
        *  interface or the endpoint.
        */
        /* p_list points the endpoint setting table. */
        pEP = (const T_ProtocovUSB_EP_SETTINGS_BLOCK CYCODE *) pTmp->p_list;
        for (i = 0u; i < ep; i++)
        {
            /* Configure interface number for each EP */
            ProtocovUSB_EP[pEP->addr & ProtocovUSB_DIR_UNUSED].interface = pEP->interface;
            pEP = &pEP[1u];
        }
        
        /* Init pointer on interface class table */
        ProtocovUSB_interfaceClass = ProtocovUSB_GetInterfaceClassTablePtr();
        
    /* Set the endpoint buffer addresses */
    #if (!ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)
        buffCount = 0u;
        for (ep = ProtocovUSB_EP1; ep < ProtocovUSB_MAX_EP; ++ep)
        {
            ProtocovUSB_EP[ep].buffOffset = buffCount;        
            buffCount += ProtocovUSB_EP[ep].bufferSize;
            
        #if (ProtocovUSB_GEN_16BITS_EP_ACCESS)
            /* Align EP buffers to be event size to access 16-bits DR register. */
            buffCount += (0u != (buffCount & 0x01u)) ? 1u : 0u;
        #endif /* (ProtocovUSB_GEN_16BITS_EP_ACCESS) */            
        }
    #endif /* (!ProtocovUSB_EP_MANAGEMENT_DMA_AUTO) */

        /* Configure hardware registers */
        ProtocovUSB_ConfigReg();
    }
}


/*******************************************************************************
* Function Name: ProtocovUSB_ConfigAltChanged
****************************************************************************//**
*
*  This routine update configuration for the required endpoints only.
*  It is called after SET_INTERFACE request when Static memory allocation used.
*
* \reentrant
*  No.
*
*******************************************************************************/
void ProtocovUSB_ConfigAltChanged(void) 
{
    uint8 ep;
    uint8 curEp;
    uint8 epType;
    uint8 i;
    uint8 interfaceNum;

    const T_ProtocovUSB_LUT CYCODE *pTmp;
    const T_ProtocovUSB_EP_SETTINGS_BLOCK CYCODE *pEP;

    /* Init Endpoints and Device Status if configured */
    if (ProtocovUSB_configuration > 0u)
    {
        /* Get number of endpoints configurations (ep). */
        pTmp = ProtocovUSB_GetConfigTablePtr(ProtocovUSB_configuration - 1u);
        pTmp = &pTmp[1u];
        ep = pTmp->c;

        /* Get pointer to endpoints setting table (pEP). */
        pEP = (const T_ProtocovUSB_EP_SETTINGS_BLOCK CYCODE *) pTmp->p_list;
        
        /* Look through all possible endpoint configurations. Find endpoints 
        * which belong to current interface and alternate settings for 
        * re-configuration.
        */
        interfaceNum = ProtocovUSB_interfaceNumber;
        for (i = 0u; i < ep; i++)
        {
            /* Find endpoints which belong to current interface and alternate settings. */
            if ((interfaceNum == pEP->interface) && 
                (ProtocovUSB_interfaceSetting[interfaceNum] == pEP->altSetting))
            {
                curEp  = ((uint8) pEP->addr & ProtocovUSB_DIR_UNUSED);
                epType = ((uint8) pEP->attributes & ProtocovUSB_EP_TYPE_MASK);
                
                /* Change the SIE mode for the selected EP to NAK ALL */
                ProtocovUSB_EP[curEp].epToggle   = 0u;
                ProtocovUSB_EP[curEp].addr       = pEP->addr;
                ProtocovUSB_EP[curEp].attrib     = pEP->attributes;
                ProtocovUSB_EP[curEp].bufferSize = pEP->bufferSize;

                if (0u != (pEP->addr & ProtocovUSB_DIR_IN))
                {
                    /* IN Endpoint */
                    ProtocovUSB_EP[curEp].epMode     = ProtocovUSB_GET_ACTIVE_IN_EP_CR0_MODE(epType);
                    ProtocovUSB_EP[curEp].apiEpState = ProtocovUSB_EVENT_PENDING;
                }
                else
                {
                    /* OUT Endpoint */
                    ProtocovUSB_EP[curEp].epMode     = ProtocovUSB_GET_ACTIVE_OUT_EP_CR0_MODE(epType);
                    ProtocovUSB_EP[curEp].apiEpState = ProtocovUSB_NO_EVENT_PENDING;
                }
                
                /* Make SIE to NAK any endpoint requests */
                ProtocovUSB_SIE_EP_BASE.sieEp[curEp].epCr0 = ProtocovUSB_MODE_NAK_IN_OUT;

            #if (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)
                /* Clear IN data ready. */
                ProtocovUSB_ARB_EP_BASE.arbEp[curEp].epCfg &= (uint8) ~ProtocovUSB_ARB_EPX_CFG_IN_DATA_RDY;

                /* Select endpoint number of reconfiguration */
                ProtocovUSB_DYN_RECONFIG_REG = (uint8) ((curEp - 1u) << ProtocovUSB_DYN_RECONFIG_EP_SHIFT);
                
                /* Request for dynamic re-configuration of endpoint. */
                ProtocovUSB_DYN_RECONFIG_REG |= ProtocovUSB_DYN_RECONFIG_ENABLE;
                
                /* Wait until block is ready for re-configuration */
                while (0u == (ProtocovUSB_DYN_RECONFIG_REG & ProtocovUSB_DYN_RECONFIG_RDY_STS))
                {
                }
                
                /* Once DYN_RECONFIG_RDY_STS bit is set, FW can change the EP configuration. */
                /* Change EP Type with new direction */
                if (0u != (pEP->addr & ProtocovUSB_DIR_IN))
                {
                    /* Set endpoint type: 0 - IN and 1 - OUT. */
                    ProtocovUSB_EP_TYPE_REG &= (uint8) ~(uint8)((uint8) 0x01u << (curEp - 1u));
                    
                #if (CY_PSOC4)
                    /* Clear DMA_TERMIN for IN endpoint */
                    ProtocovUSB_ARB_EP_BASE.arbEp[curEp].epIntEn &= (uint32) ~ProtocovUSB_ARB_EPX_INT_DMA_TERMIN;
                #endif /* (CY_PSOC4) */
                }
                else
                {
                    /* Set endpoint type: 0 - IN and 1- OUT. */
                    ProtocovUSB_EP_TYPE_REG |= (uint8) ((uint8) 0x01u << (curEp - 1u));
                    
                #if (CY_PSOC4)
                    /* Set DMA_TERMIN for OUT endpoint */
                    ProtocovUSB_ARB_EP_BASE.arbEp[curEp].epIntEn |= (uint32) ProtocovUSB_ARB_EPX_INT_DMA_TERMIN;
                #endif /* (CY_PSOC4) */
                }
                
                /* Complete dynamic re-configuration: all endpoint related status and signals 
                * are set into the default state.
                */
                ProtocovUSB_DYN_RECONFIG_REG &= (uint8) ~ProtocovUSB_DYN_RECONFIG_ENABLE;

            #else
                ProtocovUSB_SIE_EP_BASE.sieEp[curEp].epCnt0 = HI8(ProtocovUSB_EP[curEp].bufferSize);
                ProtocovUSB_SIE_EP_BASE.sieEp[curEp].epCnt1 = LO8(ProtocovUSB_EP[curEp].bufferSize);
                
                #if (CY_PSOC4)
                    ProtocovUSB_ARB_EP16_BASE.arbEp[curEp].rwRa16  = (uint32) ProtocovUSB_EP[curEp].buffOffset;
                    ProtocovUSB_ARB_EP16_BASE.arbEp[curEp].rwWa16  = (uint32) ProtocovUSB_EP[curEp].buffOffset;
                #else
                    ProtocovUSB_ARB_EP_BASE.arbEp[curEp].rwRa    = LO8(ProtocovUSB_EP[curEp].buffOffset);
                    ProtocovUSB_ARB_EP_BASE.arbEp[curEp].rwRaMsb = HI8(ProtocovUSB_EP[curEp].buffOffset);
                    ProtocovUSB_ARB_EP_BASE.arbEp[curEp].rwWa    = LO8(ProtocovUSB_EP[curEp].buffOffset);
                    ProtocovUSB_ARB_EP_BASE.arbEp[curEp].rwWaMsb = HI8(ProtocovUSB_EP[curEp].buffOffset);
                #endif /* (CY_PSOC4) */                
            #endif /* (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO) */
            }
            
            pEP = &pEP[1u]; /* Get next EP element */
        }
        
        /* The main loop has to re-enable DMA and OUT endpoint */
    }
}


/*******************************************************************************
* Function Name: ProtocovUSB_GetConfigTablePtr
****************************************************************************//**
*
*  This routine returns a pointer a configuration table entry
*
*  \param confIndex:  Configuration Index
*
* \return
*  Device Descriptor pointer or NULL when descriptor does not exist.
*
*******************************************************************************/
const T_ProtocovUSB_LUT CYCODE *ProtocovUSB_GetConfigTablePtr(uint8 confIndex)
                                                        
{
    /* Device Table */
    const T_ProtocovUSB_LUT CYCODE *pTmp;

    pTmp = (const T_ProtocovUSB_LUT CYCODE *) ProtocovUSB_TABLE[ProtocovUSB_device].p_list;

    /* The first entry points to the Device Descriptor,
    *  the second entry point to the BOS Descriptor
    *  the rest configuration entries.
    *  Set pointer to the first Configuration Descriptor
    */
    pTmp = &pTmp[2u];
    /* For this table, c is the number of configuration descriptors  */
    if(confIndex >= pTmp->c)   /* Verify that required configuration descriptor exists */
    {
        pTmp = (const T_ProtocovUSB_LUT CYCODE *) NULL;
    }
    else
    {
        pTmp = (const T_ProtocovUSB_LUT CYCODE *) pTmp[confIndex].p_list;
    }

    return (pTmp);
}


#if (ProtocovUSB_BOS_ENABLE)
    /*******************************************************************************
    * Function Name: ProtocovUSB_GetBOSPtr
    ****************************************************************************//**
    *
    *  This routine returns a pointer a BOS table entry
    *
    *  
    *
    * \return
    *  BOS Descriptor pointer or NULL when descriptor does not exist.
    *
    *******************************************************************************/
    const T_ProtocovUSB_LUT CYCODE *ProtocovUSB_GetBOSPtr(void)
                                                            
    {
        /* Device Table */
        const T_ProtocovUSB_LUT CYCODE *pTmp;

        pTmp = (const T_ProtocovUSB_LUT CYCODE *) ProtocovUSB_TABLE[ProtocovUSB_device].p_list;

        /* The first entry points to the Device Descriptor,
        *  the second entry points to the BOS Descriptor
        */
        pTmp = &pTmp[1u];
        pTmp = (const T_ProtocovUSB_LUT CYCODE *) pTmp->p_list;
        return (pTmp);
    }
#endif /* (ProtocovUSB_BOS_ENABLE) */


/*******************************************************************************
* Function Name: ProtocovUSB_GetDeviceTablePtr
****************************************************************************//**
*
*  This routine returns a pointer to the Device table
*
* \return
*  Device Table pointer
*
*******************************************************************************/
const T_ProtocovUSB_LUT CYCODE *ProtocovUSB_GetDeviceTablePtr(void)
                                                            
{
    /* Device Table */
    return( (const T_ProtocovUSB_LUT CYCODE *) ProtocovUSB_TABLE[ProtocovUSB_device].p_list );
}


/*******************************************************************************
* Function Name: USB_GetInterfaceClassTablePtr
****************************************************************************//**
*
*  This routine returns Interface Class table pointer, which contains
*  the relation between interface number and interface class.
*
* \return
*  Interface Class table pointer.
*
*******************************************************************************/
const uint8 CYCODE *ProtocovUSB_GetInterfaceClassTablePtr(void)
                                                        
{
    const T_ProtocovUSB_LUT CYCODE *pTmp;
    const uint8 CYCODE *pInterfaceClass;
    uint8 currentInterfacesNum;

    pTmp = ProtocovUSB_GetConfigTablePtr(ProtocovUSB_configuration - 1u);
    if (pTmp != NULL)
    {
        currentInterfacesNum  = ((const uint8 *) pTmp->p_list)[ProtocovUSB_CONFIG_DESCR_NUM_INTERFACES];
        /* Third entry in the LUT starts the Interface Table pointers */
        /* The INTERFACE_CLASS table is located after all interfaces */
        pTmp = &pTmp[currentInterfacesNum + 2u];
        pInterfaceClass = (const uint8 CYCODE *) pTmp->p_list;
    }
    else
    {
        pInterfaceClass = (const uint8 CYCODE *) NULL;
    }

    return (pInterfaceClass);
}


/*******************************************************************************
* Function Name: ProtocovUSB_TerminateEP
****************************************************************************//**
*
*  This function terminates the specified USBFS endpoint.
*  This function should be used before endpoint reconfiguration.
*
*  \param ep Contains the data endpoint number.
*
*  \reentrant
*  No.
*
* \sideeffect
* 
* The device responds with a NAK for any transactions on the selected endpoint.
*   
*******************************************************************************/
void ProtocovUSB_TerminateEP(uint8 epNumber) 
{
    /* Get endpoint number */
    epNumber &= ProtocovUSB_DIR_UNUSED;

    if ((epNumber > ProtocovUSB_EP0) && (epNumber < ProtocovUSB_MAX_EP))
    {
        /* Set the endpoint Halt */
        ProtocovUSB_EP[epNumber].hwEpState |= ProtocovUSB_ENDPOINT_STATUS_HALT;

        /* Clear the data toggle */
        ProtocovUSB_EP[epNumber].epToggle = 0u;
        ProtocovUSB_EP[epNumber].apiEpState = ProtocovUSB_NO_EVENT_ALLOWED;

        if ((ProtocovUSB_EP[epNumber].addr & ProtocovUSB_DIR_IN) != 0u)
        {   
            /* IN Endpoint */
            ProtocovUSB_SIE_EP_BASE.sieEp[epNumber].epCr0 = ProtocovUSB_MODE_NAK_IN;
        }
        else
        {
            /* OUT Endpoint */
            ProtocovUSB_SIE_EP_BASE.sieEp[epNumber].epCr0 = ProtocovUSB_MODE_NAK_OUT;
        }
    }
}


/*******************************************************************************
* Function Name: ProtocovUSB_SetEndpointHalt
****************************************************************************//**
*
*  This routine handles set endpoint halt.
*
* \return
*  requestHandled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 ProtocovUSB_SetEndpointHalt(void) 
{
    uint8 requestHandled = ProtocovUSB_FALSE;
    uint8 ep;
    
    /* Set endpoint halt */
    ep = ProtocovUSB_wIndexLoReg & ProtocovUSB_DIR_UNUSED;

    if ((ep > ProtocovUSB_EP0) && (ep < ProtocovUSB_MAX_EP))
    {
        /* Set the endpoint Halt */
        ProtocovUSB_EP[ep].hwEpState |= (ProtocovUSB_ENDPOINT_STATUS_HALT);

        /* Clear the data toggle */
        ProtocovUSB_EP[ep].epToggle = 0u;
        ProtocovUSB_EP[ep].apiEpState |= ProtocovUSB_NO_EVENT_ALLOWED;

        if ((ProtocovUSB_EP[ep].addr & ProtocovUSB_DIR_IN) != 0u)
        {
            /* IN Endpoint */
            ProtocovUSB_SIE_EP_BASE.sieEp[ep].epCr0 = (ProtocovUSB_MODE_STALL_DATA_EP | 
                                                            ProtocovUSB_MODE_ACK_IN);
        }
        else
        {
            /* OUT Endpoint */
            ProtocovUSB_SIE_EP_BASE.sieEp[ep].epCr0 = (ProtocovUSB_MODE_STALL_DATA_EP | 
                                                            ProtocovUSB_MODE_ACK_OUT);
        }
        requestHandled = ProtocovUSB_InitNoDataControlTransfer();
    }

    return (requestHandled);
}


/*******************************************************************************
* Function Name: ProtocovUSB_ClearEndpointHalt
****************************************************************************//**
*
*  This routine handles clear endpoint halt.
*
* \return
*  requestHandled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 ProtocovUSB_ClearEndpointHalt(void) 
{
    uint8 requestHandled = ProtocovUSB_FALSE;
    uint8 ep;

    /* Clear endpoint halt */
    ep = ProtocovUSB_wIndexLoReg & ProtocovUSB_DIR_UNUSED;

    if ((ep > ProtocovUSB_EP0) && (ep < ProtocovUSB_MAX_EP))
    {
        /* Clear the endpoint Halt */
        ProtocovUSB_EP[ep].hwEpState &= (uint8) ~ProtocovUSB_ENDPOINT_STATUS_HALT;

        /* Clear the data toggle */
        ProtocovUSB_EP[ep].epToggle = 0u;
        
        /* Clear toggle bit for already armed packet */
        ProtocovUSB_SIE_EP_BASE.sieEp[ep].epCnt0 &= (uint8) ~(uint8)ProtocovUSB_EPX_CNT_DATA_TOGGLE;
        
        /* Return API State as it was defined before */
        ProtocovUSB_EP[ep].apiEpState &= (uint8) ~ProtocovUSB_NO_EVENT_ALLOWED;

        if ((ProtocovUSB_EP[ep].addr & ProtocovUSB_DIR_IN) != 0u)
        {
            /* IN Endpoint */
            if(ProtocovUSB_EP[ep].apiEpState == ProtocovUSB_IN_BUFFER_EMPTY)
            {       
                /* Wait for next packet from application */
                ProtocovUSB_SIE_EP_BASE.sieEp[ep].epCr0 = ProtocovUSB_MODE_NAK_IN;
            }
            else    /* Continue armed transfer */
            {
                ProtocovUSB_SIE_EP_BASE.sieEp[ep].epCr0 = ProtocovUSB_MODE_ACK_IN;
            }
        }
        else
        {
            /* OUT Endpoint */
            if (ProtocovUSB_EP[ep].apiEpState == ProtocovUSB_OUT_BUFFER_FULL)
            {       
                /* Allow application to read full buffer */
                ProtocovUSB_SIE_EP_BASE.sieEp[ep].epCr0 = ProtocovUSB_MODE_NAK_OUT;
            }
            else    /* Mark endpoint as empty, so it will be reloaded */
            {
                ProtocovUSB_SIE_EP_BASE.sieEp[ep].epCr0 = ProtocovUSB_MODE_ACK_OUT;
            }
        }
        
        requestHandled = ProtocovUSB_InitNoDataControlTransfer();
    }

    return(requestHandled);
}


/*******************************************************************************
* Function Name: ProtocovUSB_ValidateAlternateSetting
****************************************************************************//**
*
*  Validates (and records) a SET INTERFACE request.
*
* \return
*  requestHandled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 ProtocovUSB_ValidateAlternateSetting(void) 
{
    uint8 requestHandled = ProtocovUSB_FALSE;
    
    uint8 interfaceNum;
    uint8 curInterfacesNum;
    const T_ProtocovUSB_LUT CYCODE *pTmp;
    
    /* Get interface number from the request. */
    interfaceNum = (uint8) ProtocovUSB_wIndexLoReg;
    
    /* Get number of interfaces for current configuration. */
    pTmp = ProtocovUSB_GetConfigTablePtr(ProtocovUSB_configuration - 1u);
    curInterfacesNum  = ((const uint8 *) pTmp->p_list)[ProtocovUSB_CONFIG_DESCR_NUM_INTERFACES];

    /* Validate that interface number is within range. */
    if ((interfaceNum <= curInterfacesNum) || (interfaceNum <= ProtocovUSB_MAX_INTERFACES_NUMBER))
    {
        /* Save current and new alternate settings (come with request) to make 
        * desicion about following endpoint re-configuration.
        */
        ProtocovUSB_interfaceSettingLast[interfaceNum] = ProtocovUSB_interfaceSetting[interfaceNum];
        ProtocovUSB_interfaceSetting[interfaceNum]     = (uint8) ProtocovUSB_wValueLoReg;
        
        requestHandled = ProtocovUSB_TRUE;
    }

    return (requestHandled);
}


/* [] END OF FILE */
