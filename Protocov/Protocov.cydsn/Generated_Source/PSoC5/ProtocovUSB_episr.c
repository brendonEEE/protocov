/***************************************************************************//**
* \file ProtocovUSB_episr.c
* \version 3.20
*
* \brief
*  This file contains the Data endpoint Interrupt Service Routines.
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ProtocovUSB_pvt.h"
#include "ProtocovUSB_cydmac.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


#if (ProtocovUSB_EP1_ISR_ACTIVE)
    /******************************************************************************
    * Function Name: ProtocovUSB_EP_1_ISR
    ***************************************************************************//**
    *
    *  Endpoint 1 Interrupt Service Routine
    *
    ******************************************************************************/
    CY_ISR(ProtocovUSB_EP_1_ISR)
    {

    #ifdef ProtocovUSB_EP_1_ISR_ENTRY_CALLBACK
        ProtocovUSB_EP_1_ISR_EntryCallback();
    #endif /* (ProtocovUSB_EP_1_ISR_ENTRY_CALLBACK) */

        /* `#START EP1_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && \
        !defined(ProtocovUSB_MAIN_SERVICE_MIDI_OUT) && ProtocovUSB_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && ProtocovUSB_ISR_SERVICE_MIDI_OUT) */
    
        ProtocovUSB_ClearSieEpInterruptSource(ProtocovUSB_SIE_INT_EP1_INTR);
            
        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to be read from endpoint buffer. 
        */
    #if (CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (ProtocovUSB_EP[ProtocovUSB_EP1].addr & ProtocovUSB_DIR_IN))
    #endif /* (CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO) */
        {
            /* Read CR0 register to clear SIE lock. */
            (void) ProtocovUSB_SIE_EP_BASE.sieEp[ProtocovUSB_EP1].epCr0;
            
            /* Toggle all endpoint types except ISOC. */
            if (ProtocovUSB_GET_EP_TYPE(ProtocovUSB_EP1) != ProtocovUSB_EP_TYPE_ISOC)
            {
                ProtocovUSB_EP[ProtocovUSB_EP1].epToggle ^= ProtocovUSB_EPX_CNT_DATA_TOGGLE;
            }

            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            ProtocovUSB_EP[ProtocovUSB_EP1].apiEpState = ProtocovUSB_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && \
            !defined(ProtocovUSB_MAIN_SERVICE_MIDI_OUT) && ProtocovUSB_ISR_SERVICE_MIDI_OUT)
            if (ProtocovUSB_midi_out_ep == ProtocovUSB_EP1)
            {
                ProtocovUSB_MIDI_OUT_Service();
            }
        #endif /* (ProtocovUSB_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)) */
    
        /* `#START EP1_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef ProtocovUSB_EP_1_ISR_EXIT_CALLBACK
        ProtocovUSB_EP_1_ISR_ExitCallback();
    #endif /* (ProtocovUSB_EP_1_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && \
        !defined(ProtocovUSB_MAIN_SERVICE_MIDI_OUT) && ProtocovUSB_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && ProtocovUSB_ISR_SERVICE_MIDI_OUT) */
    }

#endif /* (ProtocovUSB_EP1_ISR_ACTIVE) */


#if (ProtocovUSB_EP2_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: ProtocovUSB_EP_2_ISR
    ****************************************************************************//**
    *
    *  Endpoint 2 Interrupt Service Routine.
    *
    *******************************************************************************/
    CY_ISR(ProtocovUSB_EP_2_ISR)
    {
    #ifdef ProtocovUSB_EP_2_ISR_ENTRY_CALLBACK
        ProtocovUSB_EP_2_ISR_EntryCallback();
    #endif /* (ProtocovUSB_EP_2_ISR_ENTRY_CALLBACK) */

        /* `#START EP2_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && \
        !defined(ProtocovUSB_MAIN_SERVICE_MIDI_OUT) && ProtocovUSB_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && ProtocovUSB_ISR_SERVICE_MIDI_OUT) */

        ProtocovUSB_ClearSieEpInterruptSource(ProtocovUSB_SIE_INT_EP2_INTR);

        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to be read from endpoint buffer. 
        */
    #if (CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (ProtocovUSB_EP[ProtocovUSB_EP2].addr & ProtocovUSB_DIR_IN))
    #endif /* (CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO) */
        {            
            /* Read CR0 register to clear SIE lock. */
            (void) ProtocovUSB_SIE_EP_BASE.sieEp[ProtocovUSB_EP2].epCr0;
            
            /* Toggle all endpoint types except ISOC. */
            if (ProtocovUSB_GET_EP_TYPE(ProtocovUSB_EP2) != ProtocovUSB_EP_TYPE_ISOC)
            {
                ProtocovUSB_EP[ProtocovUSB_EP2].epToggle ^= ProtocovUSB_EPX_CNT_DATA_TOGGLE;
            }

            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            ProtocovUSB_EP[ProtocovUSB_EP2].apiEpState = ProtocovUSB_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && \
            !defined(ProtocovUSB_MAIN_SERVICE_MIDI_OUT) && ProtocovUSB_ISR_SERVICE_MIDI_OUT)
            if (ProtocovUSB_midi_out_ep == ProtocovUSB_EP2)
            {
                ProtocovUSB_MIDI_OUT_Service();
            }
        #endif /* (ProtocovUSB_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)) */        
    
        /* `#START EP2_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef ProtocovUSB_EP_2_ISR_EXIT_CALLBACK
        ProtocovUSB_EP_2_ISR_ExitCallback();
    #endif /* (ProtocovUSB_EP_2_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && \
        !defined(ProtocovUSB_MAIN_SERVICE_MIDI_OUT) && ProtocovUSB_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && ProtocovUSB_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (ProtocovUSB_EP2_ISR_ACTIVE) */


#if (ProtocovUSB_EP3_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: ProtocovUSB_EP_3_ISR
    ****************************************************************************//**
    *
    *  Endpoint 3 Interrupt Service Routine.
    *
    *******************************************************************************/
    CY_ISR(ProtocovUSB_EP_3_ISR)
    {
    #ifdef ProtocovUSB_EP_3_ISR_ENTRY_CALLBACK
        ProtocovUSB_EP_3_ISR_EntryCallback();
    #endif /* (ProtocovUSB_EP_3_ISR_ENTRY_CALLBACK) */

        /* `#START EP3_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && \
        !defined(ProtocovUSB_MAIN_SERVICE_MIDI_OUT) && ProtocovUSB_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && ProtocovUSB_ISR_SERVICE_MIDI_OUT) */

        ProtocovUSB_ClearSieEpInterruptSource(ProtocovUSB_SIE_INT_EP3_INTR);    

        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to be read from endpoint buffer. 
        */
    #if (CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (ProtocovUSB_EP[ProtocovUSB_EP3].addr & ProtocovUSB_DIR_IN))
    #endif /* (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO) */
        {            
            /* Read CR0 register to clear SIE lock. */
            (void) ProtocovUSB_SIE_EP_BASE.sieEp[ProtocovUSB_EP3].epCr0;

            /* Toggle all endpoint types except ISOC. */
            if (ProtocovUSB_GET_EP_TYPE(ProtocovUSB_EP3) != ProtocovUSB_EP_TYPE_ISOC)
            {
                ProtocovUSB_EP[ProtocovUSB_EP3].epToggle ^= ProtocovUSB_EPX_CNT_DATA_TOGGLE;
            }

            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            ProtocovUSB_EP[ProtocovUSB_EP3].apiEpState = ProtocovUSB_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && \
            !defined(ProtocovUSB_MAIN_SERVICE_MIDI_OUT) && ProtocovUSB_ISR_SERVICE_MIDI_OUT)
            if (ProtocovUSB_midi_out_ep == ProtocovUSB_EP3)
            {
                ProtocovUSB_MIDI_OUT_Service();
            }
        #endif /* (ProtocovUSB_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)) */        

        /* `#START EP3_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef ProtocovUSB_EP_3_ISR_EXIT_CALLBACK
        ProtocovUSB_EP_3_ISR_ExitCallback();
    #endif /* (ProtocovUSB_EP_3_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && \
        !defined(ProtocovUSB_MAIN_SERVICE_MIDI_OUT) && ProtocovUSB_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && ProtocovUSB_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (ProtocovUSB_EP3_ISR_ACTIVE) */


#if (ProtocovUSB_EP4_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: ProtocovUSB_EP_4_ISR
    ****************************************************************************//**
    *
    *  Endpoint 4 Interrupt Service Routine.
    *
    *******************************************************************************/
    CY_ISR(ProtocovUSB_EP_4_ISR)
    {
    #ifdef ProtocovUSB_EP_4_ISR_ENTRY_CALLBACK
        ProtocovUSB_EP_4_ISR_EntryCallback();
    #endif /* (ProtocovUSB_EP_4_ISR_ENTRY_CALLBACK) */

        /* `#START EP4_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && \
        !defined(ProtocovUSB_MAIN_SERVICE_MIDI_OUT) && ProtocovUSB_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && ProtocovUSB_ISR_SERVICE_MIDI_OUT) */

        ProtocovUSB_ClearSieEpInterruptSource(ProtocovUSB_SIE_INT_EP4_INTR);
        
        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to read from endpoint buffer. 
        */
    #if (CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (ProtocovUSB_EP[ProtocovUSB_EP4].addr & ProtocovUSB_DIR_IN))
    #endif /* (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO) */
        {
            /* Read CR0 register to clear SIE lock. */
            (void) ProtocovUSB_SIE_EP_BASE.sieEp[ProtocovUSB_EP4].epCr0;

            /* Toggle all endpoint types except ISOC. */
            if (ProtocovUSB_GET_EP_TYPE(ProtocovUSB_EP4) != ProtocovUSB_EP_TYPE_ISOC)
            {
                ProtocovUSB_EP[ProtocovUSB_EP4].epToggle ^= ProtocovUSB_EPX_CNT_DATA_TOGGLE;
            }

            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            ProtocovUSB_EP[ProtocovUSB_EP4].apiEpState = ProtocovUSB_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && \
            !defined(ProtocovUSB_MAIN_SERVICE_MIDI_OUT) && ProtocovUSB_ISR_SERVICE_MIDI_OUT)
            if(ProtocovUSB_midi_out_ep == ProtocovUSB_EP4)
            {
                ProtocovUSB_MIDI_OUT_Service();
            }
        #endif /* (ProtocovUSB_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)) */        

        /* `#START EP4_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef ProtocovUSB_EP_4_ISR_EXIT_CALLBACK
        ProtocovUSB_EP_4_ISR_ExitCallback();
    #endif /* (ProtocovUSB_EP_4_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && \
        !defined(ProtocovUSB_MAIN_SERVICE_MIDI_OUT) && ProtocovUSB_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && ProtocovUSB_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (ProtocovUSB_EP4_ISR_ACTIVE) */


#if (ProtocovUSB_EP5_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: ProtocovUSB_EP_5_ISR
    ****************************************************************************//**
    *
    *  Endpoint 5 Interrupt Service Routine
    *
    *
    *******************************************************************************/
    CY_ISR(ProtocovUSB_EP_5_ISR)
    {
    #ifdef ProtocovUSB_EP_5_ISR_ENTRY_CALLBACK
        ProtocovUSB_EP_5_ISR_EntryCallback();
    #endif /* (ProtocovUSB_EP_5_ISR_ENTRY_CALLBACK) */

        /* `#START EP5_USER_CODE` Place your code here */

        /* `#END` */

    #if (defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && !defined(ProtocovUSB_MAIN_SERVICE_MIDI_OUT) && \
                 ProtocovUSB_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && ProtocovUSB_ISR_SERVICE_MIDI_OUT) */

        ProtocovUSB_ClearSieEpInterruptSource(ProtocovUSB_SIE_INT_EP5_INTR);
    
        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to read from endpoint buffer. 
        */
    #if (CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (ProtocovUSB_EP[ProtocovUSB_EP5].addr & ProtocovUSB_DIR_IN))
    #endif /* (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO) */
        {            
            /* Read CR0 register to clear SIE lock. */
            (void) ProtocovUSB_SIE_EP_BASE.sieEp[ProtocovUSB_EP5].epCr0;

            /* Toggle all endpoint types except ISOC. */
            if (ProtocovUSB_GET_EP_TYPE(ProtocovUSB_EP5) != ProtocovUSB_EP_TYPE_ISOC)
            {
                ProtocovUSB_EP[ProtocovUSB_EP5].epToggle ^= ProtocovUSB_EPX_CNT_DATA_TOGGLE;
            }

            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            ProtocovUSB_EP[ProtocovUSB_EP5].apiEpState = ProtocovUSB_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO))        
        #if (defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && \
            !defined(ProtocovUSB_MAIN_SERVICE_MIDI_OUT) && ProtocovUSB_ISR_SERVICE_MIDI_OUT)
            if (ProtocovUSB_midi_out_ep == ProtocovUSB_EP5)
            {
                ProtocovUSB_MIDI_OUT_Service();
            }
        #endif /* (ProtocovUSB_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)) */

        /* `#START EP5_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef ProtocovUSB_EP_5_ISR_EXIT_CALLBACK
        ProtocovUSB_EP_5_ISR_ExitCallback();
    #endif /* (ProtocovUSB_EP_5_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && \
        !defined(ProtocovUSB_MAIN_SERVICE_MIDI_OUT) && ProtocovUSB_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && ProtocovUSB_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (ProtocovUSB_EP5_ISR_ACTIVE) */


#if (ProtocovUSB_EP6_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: ProtocovUSB_EP_6_ISR
    ****************************************************************************//**
    *
    *  Endpoint 6 Interrupt Service Routine.
    *
    *
    *******************************************************************************/
    CY_ISR(ProtocovUSB_EP_6_ISR)
    {
    #ifdef ProtocovUSB_EP_6_ISR_ENTRY_CALLBACK
        ProtocovUSB_EP_6_ISR_EntryCallback();
    #endif /* (ProtocovUSB_EP_6_ISR_ENTRY_CALLBACK) */

        /* `#START EP6_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && \
        !defined(ProtocovUSB_MAIN_SERVICE_MIDI_OUT) && ProtocovUSB_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && ProtocovUSB_ISR_SERVICE_MIDI_OUT) */

        ProtocovUSB_ClearSieEpInterruptSource(ProtocovUSB_SIE_INT_EP6_INTR);
        
        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to read from endpoint buffer. 
        */
    #if (CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (ProtocovUSB_EP[ProtocovUSB_EP6].addr & ProtocovUSB_DIR_IN))
    #endif /* (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO) */
        {
            /* Read CR0 register to clear SIE lock. */
            (void) ProtocovUSB_SIE_EP_BASE.sieEp[ProtocovUSB_EP6].epCr0;

            /* Toggle all endpoint types except ISOC. */
            if (ProtocovUSB_GET_EP_TYPE(ProtocovUSB_EP6) != ProtocovUSB_EP_TYPE_ISOC)
            {
                ProtocovUSB_EP[ProtocovUSB_EP6].epToggle ^= ProtocovUSB_EPX_CNT_DATA_TOGGLE;
            }
            
            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            ProtocovUSB_EP[ProtocovUSB_EP6].apiEpState = ProtocovUSB_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && \
            !defined(ProtocovUSB_MAIN_SERVICE_MIDI_OUT) && ProtocovUSB_ISR_SERVICE_MIDI_OUT)
            if (ProtocovUSB_midi_out_ep == ProtocovUSB_EP6)
            {
                ProtocovUSB_MIDI_OUT_Service();
            }
        #endif /* (ProtocovUSB_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)) */

        /* `#START EP6_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef ProtocovUSB_EP_6_ISR_EXIT_CALLBACK
        ProtocovUSB_EP_6_ISR_ExitCallback();
    #endif /* (ProtocovUSB_EP_6_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && \
        !defined(ProtocovUSB_MAIN_SERVICE_MIDI_OUT) && ProtocovUSB_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && ProtocovUSB_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (ProtocovUSB_EP6_ISR_ACTIVE) */


#if (ProtocovUSB_EP7_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: ProtocovUSB_EP_7_ISR
    ****************************************************************************//**
    *
    *  Endpoint 7 Interrupt Service Routine.
    *
    *
    *******************************************************************************/
    CY_ISR(ProtocovUSB_EP_7_ISR)
    {
    #ifdef ProtocovUSB_EP_7_ISR_ENTRY_CALLBACK
        ProtocovUSB_EP_7_ISR_EntryCallback();
    #endif /* (ProtocovUSB_EP_7_ISR_ENTRY_CALLBACK) */

        /* `#START EP7_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && \
        !defined(ProtocovUSB_MAIN_SERVICE_MIDI_OUT) && ProtocovUSB_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && ProtocovUSB_ISR_SERVICE_MIDI_OUT) */
    
        ProtocovUSB_ClearSieEpInterruptSource(ProtocovUSB_SIE_INT_EP7_INTR);
        
        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to read from endpoint buffer. 
        */
    #if (CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (ProtocovUSB_EP[ProtocovUSB_EP7].addr & ProtocovUSB_DIR_IN))
    #endif /* (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO) */
        {           
            /* Read CR0 register to clear SIE lock. */
            (void) ProtocovUSB_SIE_EP_BASE.sieEp[ProtocovUSB_EP7].epCr0;

            /* Toggle all endpoint types except ISOC. */
            if (ProtocovUSB_GET_EP_TYPE(ProtocovUSB_EP7) != ProtocovUSB_EP_TYPE_ISOC)
            {
                ProtocovUSB_EP[ProtocovUSB_EP7].epToggle ^= ProtocovUSB_EPX_CNT_DATA_TOGGLE;
            }
            
            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            ProtocovUSB_EP[ProtocovUSB_EP7].apiEpState = ProtocovUSB_EVENT_PENDING;
        }


    #if (!(CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && \
            !defined(ProtocovUSB_MAIN_SERVICE_MIDI_OUT) && ProtocovUSB_ISR_SERVICE_MIDI_OUT)
            if(ProtocovUSB_midi_out_ep == ProtocovUSB_EP7)
            {
                ProtocovUSB_MIDI_OUT_Service();
            }
        #endif /* (ProtocovUSB_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)) */

        /* `#START EP7_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef ProtocovUSB_EP_7_ISR_EXIT_CALLBACK
        ProtocovUSB_EP_7_ISR_ExitCallback();
    #endif /* (ProtocovUSB_EP_7_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && \
        !defined(ProtocovUSB_MAIN_SERVICE_MIDI_OUT) && ProtocovUSB_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && ProtocovUSB_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (ProtocovUSB_EP7_ISR_ACTIVE) */


#if (ProtocovUSB_EP8_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: ProtocovUSB_EP_8_ISR
    ****************************************************************************//**
    *
    *  Endpoint 8 Interrupt Service Routine
    *
    *
    *******************************************************************************/
    CY_ISR(ProtocovUSB_EP_8_ISR)
    {
    #ifdef ProtocovUSB_EP_8_ISR_ENTRY_CALLBACK
        ProtocovUSB_EP_8_ISR_EntryCallback();
    #endif /* (ProtocovUSB_EP_8_ISR_ENTRY_CALLBACK) */

        /* `#START EP8_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && \
        !defined(ProtocovUSB_MAIN_SERVICE_MIDI_OUT) && ProtocovUSB_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && ProtocovUSB_ISR_SERVICE_MIDI_OUT) */

        ProtocovUSB_ClearSieEpInterruptSource(ProtocovUSB_SIE_INT_EP8_INTR);
        
        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to read from endpoint buffer. 
        */
    #if (CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (ProtocovUSB_EP[ProtocovUSB_EP8].addr & ProtocovUSB_DIR_IN))
    #endif /* (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO) */
        {
            /* Read CR0 register to clear SIE lock. */
            (void) ProtocovUSB_SIE_EP_BASE.sieEp[ProtocovUSB_EP8].epCr0;

            /* Toggle all endpoint types except ISOC. */
            if (ProtocovUSB_GET_EP_TYPE(ProtocovUSB_EP8) != ProtocovUSB_EP_TYPE_ISOC)
            {
                ProtocovUSB_EP[ProtocovUSB_EP8].epToggle ^= ProtocovUSB_EPX_CNT_DATA_TOGGLE;
            }

            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            ProtocovUSB_EP[ProtocovUSB_EP8].apiEpState = ProtocovUSB_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && \
            !defined(ProtocovUSB_MAIN_SERVICE_MIDI_OUT) && ProtocovUSB_ISR_SERVICE_MIDI_OUT)
            if (ProtocovUSB_midi_out_ep == ProtocovUSB_EP8)
            {
                ProtocovUSB_MIDI_OUT_Service();
            }
        #endif /* (ProtocovUSB_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)) */

        /* `#START EP8_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef ProtocovUSB_EP_8_ISR_EXIT_CALLBACK
        ProtocovUSB_EP_8_ISR_ExitCallback();
    #endif /* (ProtocovUSB_EP_8_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && \
        !defined(ProtocovUSB_MAIN_SERVICE_MIDI_OUT) && ProtocovUSB_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && ProtocovUSB_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (ProtocovUSB_EP8_ISR_ACTIVE) */


#if (ProtocovUSB_SOF_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: ProtocovUSB_SOF_ISR
    ****************************************************************************//**
    *
    *  Start of Frame Interrupt Service Routine.
    *
    *
    *******************************************************************************/
    CY_ISR(ProtocovUSB_SOF_ISR)
    {
    #ifdef ProtocovUSB_SOF_ISR_ENTRY_CALLBACK
        ProtocovUSB_SOF_ISR_EntryCallback();
    #endif /* (ProtocovUSB_SOF_ISR_ENTRY_CALLBACK) */

        /* `#START SOF_USER_CODE` Place your code here */

        /* `#END` */

        ProtocovUSB_ClearSieInterruptSource(ProtocovUSB_INTR_SIE_SOF_INTR);

    #ifdef ProtocovUSB_SOF_ISR_EXIT_CALLBACK
        ProtocovUSB_SOF_ISR_ExitCallback();
    #endif /* (ProtocovUSB_SOF_ISR_EXIT_CALLBACK) */
    }
#endif /* (ProtocovUSB_SOF_ISR_ACTIVE) */


#if (ProtocovUSB_BUS_RESET_ISR_ACTIVE)
/*******************************************************************************
* Function Name: ProtocovUSB_BUS_RESET_ISR
****************************************************************************//**
*
*  USB Bus Reset Interrupt Service Routine.  Calls _Start with the same
*  parameters as the last USER call to _Start
*
*
*******************************************************************************/
CY_ISR(ProtocovUSB_BUS_RESET_ISR)
{
#ifdef ProtocovUSB_BUS_RESET_ISR_ENTRY_CALLBACK
    ProtocovUSB_BUS_RESET_ISR_EntryCallback();
#endif /* (ProtocovUSB_BUS_RESET_ISR_ENTRY_CALLBACK) */

    /* `#START BUS_RESET_USER_CODE` Place your code here */

    /* `#END` */

    ProtocovUSB_ClearSieInterruptSource(ProtocovUSB_INTR_SIE_BUS_RESET_INTR);

    ProtocovUSB_ReInitComponent();

#ifdef ProtocovUSB_BUS_RESET_ISR_EXIT_CALLBACK
    ProtocovUSB_BUS_RESET_ISR_ExitCallback();
#endif /* (ProtocovUSB_BUS_RESET_ISR_EXIT_CALLBACK) */
}
#endif /* (ProtocovUSB_BUS_RESET_ISR_ACTIVE) */


#if (ProtocovUSB_LPM_ACTIVE)
/***************************************************************************
* Function Name: ProtocovUSB_INTR_LPM_ISR
************************************************************************//**
*
*   Interrupt Service Routine for LPM of the interrupt sources.
*
*
***************************************************************************/
CY_ISR(ProtocovUSB_LPM_ISR)
{
#ifdef ProtocovUSB_LPM_ISR_ENTRY_CALLBACK
    ProtocovUSB_LPM_ISR_EntryCallback();
#endif /* (ProtocovUSB_LPM_ISR_ENTRY_CALLBACK) */

    /* `#START LPM_BEGIN_USER_CODE` Place your code here */

    /* `#END` */

    ProtocovUSB_ClearSieInterruptSource(ProtocovUSB_INTR_SIE_LPM_INTR);

    /* `#START LPM_END_USER_CODE` Place your code here */

    /* `#END` */

#ifdef ProtocovUSB_LPM_ISR_EXIT_CALLBACK
    ProtocovUSB_LPM_ISR_ExitCallback();
#endif /* (ProtocovUSB_LPM_ISR_EXIT_CALLBACK) */
}
#endif /* (ProtocovUSB_LPM_ACTIVE) */


#if (ProtocovUSB_EP_MANAGEMENT_DMA && ProtocovUSB_ARB_ISR_ACTIVE)
    /***************************************************************************
    * Function Name: ProtocovUSB_ARB_ISR
    ************************************************************************//**
    *
    *  Arbiter Interrupt Service Routine.
    *
    *
    ***************************************************************************/
    CY_ISR(ProtocovUSB_ARB_ISR)
    {
        uint8 arbIntrStatus;
        uint8 epStatus;
        uint8 ep = ProtocovUSB_EP1;

    #ifdef ProtocovUSB_ARB_ISR_ENTRY_CALLBACK
        ProtocovUSB_ARB_ISR_EntryCallback();
    #endif /* (ProtocovUSB_ARB_ISR_ENTRY_CALLBACK) */

        /* `#START ARB_BEGIN_USER_CODE` Place your code here */

        /* `#END` */

        /* Get pending ARB interrupt sources. */
        arbIntrStatus = ProtocovUSB_ARB_INT_SR_REG;

        while (0u != arbIntrStatus)
        {
            /* Check which EP is interrupt source. */
            if (0u != (arbIntrStatus & 0x01u))
            {
                /* Get endpoint enable interrupt sources. */
                epStatus = (ProtocovUSB_ARB_EP_BASE.arbEp[ep].epSr & ProtocovUSB_ARB_EP_BASE.arbEp[ep].epIntEn);

                /* Handle IN endpoint buffer full event: happens only once when endpoint buffer is loaded. */
                if (0u != (epStatus & ProtocovUSB_ARB_EPX_INT_IN_BUF_FULL))
                {
                    if (0u != (ProtocovUSB_EP[ep].addr & ProtocovUSB_DIR_IN))
                    {
                        /* Clear data ready status. */
                        ProtocovUSB_ARB_EP_BASE.arbEp[ep].epCfg &= (uint8) ~ProtocovUSB_ARB_EPX_CFG_IN_DATA_RDY;

                    #if (CY_PSOC3 || CY_PSOC5LP)
                        #if (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO && (ProtocovUSB_EP_DMA_AUTO_OPT == 0u))
                            /* Set up common area DMA with rest of data. */
                            if(ProtocovUSB_inLength[ep] > ProtocovUSB_DMA_BYTES_PER_BURST)
                            {
                                ProtocovUSB_LoadNextInEP(ep, 0u);
                            }
                            else
                            {
                                ProtocovUSB_inBufFull[ep] = 1u;
                            }
                        #endif /* (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO && (ProtocovUSB_EP_DMA_AUTO_OPT == 0u)) */
                    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

                        /* Arm IN endpoint. */
                        ProtocovUSB_SIE_EP_BASE.sieEp[ep].epCr0 = ProtocovUSB_EP[ep].epMode;

                    #if (defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && ProtocovUSB_ISR_SERVICE_MIDI_IN)
                        if (ep == ProtocovUSB_midi_in_ep)
                        {
                            /* Clear MIDI input pointer. */
                            ProtocovUSB_midiInPointer = 0u;
                        }
                    #endif /* (ProtocovUSB_ENABLE_MIDI_STREAMING) */
                    }
                }

            #if (ProtocovUSB_EP_MANAGEMENT_DMA_MANUAL)
                /* Handle DMA completion event for OUT endpoints. */
                if (0u != (epStatus & ProtocovUSB_ARB_EPX_SR_DMA_GNT))
                {
                    if (0u == (ProtocovUSB_EP[ep].addr & ProtocovUSB_DIR_IN))
                    {
                        /* Notify user that data has been copied from endpoint buffer. */
                        ProtocovUSB_EP[ep].apiEpState = ProtocovUSB_NO_EVENT_PENDING;

                        /* DMA done coping data: OUT endpoint has to be re-armed by user. */
                    }
                }
            #endif /* (ProtocovUSB_EP_MANAGEMENT_DMA_MANUAL) */

            #if (CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)
                /* Handle DMA completion event for OUT endpoints. */
                if (0u != (epStatus & ProtocovUSB_ARB_EPX_INT_DMA_TERMIN))
                {
                    uint32 channelNum = ProtocovUSB_DmaChan[ep];

                    /* Restore burst counter for endpoint. */
                    ProtocovUSB_DmaEpBurstCnt[ep] = ProtocovUSB_DMA_GET_BURST_CNT(ProtocovUSB_DmaEpBurstCntBackup[ep]);

                    /* Disable DMA channel to restore descriptor configuration. The on-going transfer is aborted. */
                    ProtocovUSB_CyDmaChDisable(channelNum);

                    /* Generate DMA tr_out signal to notify USB IP that DMA is done. This signal is not generated
                    * when transfer was aborted (it occurs when host writes less bytes than buffer size).
                    */
                    ProtocovUSB_CyDmaTriggerOut(ProtocovUSB_DmaBurstEndOut[ep]);

                    /* Restore destination address for output endpoint. */
                    ProtocovUSB_CyDmaSetDstAddress(channelNum, ProtocovUSB_DMA_DESCR0, (void*) ((uint32) ProtocovUSB_DmaEpBufferAddrBackup[ep]));
                    ProtocovUSB_CyDmaSetDstAddress(channelNum, ProtocovUSB_DMA_DESCR1, (void*) ((uint32) ProtocovUSB_DmaEpBufferAddrBackup[ep] +
                                                                                                                   ProtocovUSB_DMA_BYTES_PER_BURST));

                    /* Restore number of data elements to transfer which was adjusted for last burst. */
                    if (0u != (ProtocovUSB_DmaEpLastBurstEl[ep] & ProtocovUSB_DMA_DESCR_REVERT))
                    {
                        ProtocovUSB_CyDmaSetNumDataElements(channelNum, (ProtocovUSB_DmaEpLastBurstEl[ep] >> ProtocovUSB_DMA_DESCR_SHIFT),
                                                                             ProtocovUSB_DMA_GET_MAX_ELEM_PER_BURST(ProtocovUSB_DmaEpLastBurstEl[ep]));
                    }

                    /* Validate descriptor 0 and 1 (also reset current state). Command to start with descriptor 0. */
                    ProtocovUSB_CyDmaValidateDescriptor(channelNum, ProtocovUSB_DMA_DESCR0);
                    if (ProtocovUSB_DmaEpBurstCntBackup[ep] > 1u)
                    {
                        ProtocovUSB_CyDmaValidateDescriptor(channelNum, ProtocovUSB_DMA_DESCR1);
                    }
                    ProtocovUSB_CyDmaSetDescriptor0Next(channelNum);

                    /* Enable DMA channel: configuration complete. */
                    ProtocovUSB_CyDmaChEnable(channelNum);
                    
                    
                    /* Read CR0 register to clear SIE lock. */
                    (void) ProtocovUSB_SIE_EP_BASE.sieEp[ep].epCr0;
                    
                    /* Toggle all endpoint types except ISOC. */
                    if (ProtocovUSB_GET_EP_TYPE(ep) != ProtocovUSB_EP_TYPE_ISOC)
                    {
                        ProtocovUSB_EP[ep].epToggle ^= ProtocovUSB_EPX_CNT_DATA_TOGGLE;
                    }
            
                    /* Notify user that data has been copied from endpoint buffer. */
                    ProtocovUSB_EP[ep].apiEpState = ProtocovUSB_EVENT_PENDING;
                    
                #if (defined(ProtocovUSB_ENABLE_MIDI_STREAMING) && \
                    !defined(ProtocovUSB_MAIN_SERVICE_MIDI_OUT) && ProtocovUSB_ISR_SERVICE_MIDI_OUT)
                    if (ProtocovUSB_midi_out_ep == ep)
                    {
                        ProtocovUSB_MIDI_OUT_Service();
                    }
                #endif /* (ProtocovUSB_ISR_SERVICE_MIDI_OUT) */
                }
            #endif /* (CY_PSOC4 && ProtocovUSB_EP_MANAGEMENT_DMA_AUTO) */


                /* `#START ARB_USER_CODE` Place your code here for handle Buffer Underflow/Overflow */

                /* `#END` */

            #ifdef ProtocovUSB_ARB_ISR_CALLBACK
                ProtocovUSB_ARB_ISR_Callback(ep, epStatus);
            #endif /* (ProtocovUSB_ARB_ISR_CALLBACK) */

                /* Clear serviced endpoint interrupt sources. */
                ProtocovUSB_ARB_EP_BASE.arbEp[ep].epSr = epStatus;
            }

            ++ep;
            arbIntrStatus >>= 1u;
        }

        /* `#START ARB_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef ProtocovUSB_ARB_ISR_EXIT_CALLBACK
        ProtocovUSB_ARB_ISR_ExitCallback();
    #endif /* (ProtocovUSB_ARB_ISR_EXIT_CALLBACK) */
    }

#endif /*  (ProtocovUSB_ARB_ISR_ACTIVE && ProtocovUSB_EP_MANAGEMENT_DMA) */


#if (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO)
#if (CY_PSOC4)

    /******************************************************************************
    * Function Name: ProtocovUSB_EPxDmaDone
    ***************************************************************************//**
    *
    * \internal
    *  Endpoint  DMA Done Interrupt Service Routine basic function .
    *  
    *  \param dmaCh
    *  number of DMA channel
    *  
    *  \param ep
    *  number of USB end point
    *  
    *  \param dmaDone
    *  transfer completion flag
    *  
    *  \return
    *   updated transfer completion flag
    *
    ******************************************************************************/
    CY_INLINE static void ProtocovUSB_EPxDmaDone(uint8 dmaCh, uint8 ep)
    {
        uint32 nextAddr;

        /* Manage data elements which remain to transfer. */
        if (0u != ProtocovUSB_DmaEpBurstCnt[ep])
        {
            if(ProtocovUSB_DmaEpBurstCnt[ep] <= 2u)
            {
                /* Adjust length of last burst. */
                ProtocovUSB_CyDmaSetNumDataElements(dmaCh,
                                                    ((uint32) ProtocovUSB_DmaEpLastBurstEl[ep] >> ProtocovUSB_DMA_DESCR_SHIFT),
                                                    ((uint32) ProtocovUSB_DmaEpLastBurstEl[ep] &  ProtocovUSB_DMA_BURST_BYTES_MASK));
            }
            

            /* Advance source for input endpoint or destination for output endpoint. */
            if (0u != (ProtocovUSB_EP[ep].addr & ProtocovUSB_DIR_IN))
            {
                /* Change source for descriptor 0. */
                nextAddr = (uint32) ProtocovUSB_CyDmaGetSrcAddress(dmaCh, ProtocovUSB_DMA_DESCR0);
                nextAddr += (2u * ProtocovUSB_DMA_BYTES_PER_BURST);
                ProtocovUSB_CyDmaSetSrcAddress(dmaCh, ProtocovUSB_DMA_DESCR0, (void *) nextAddr);

                /* Change source for descriptor 1. */
                nextAddr += ProtocovUSB_DMA_BYTES_PER_BURST;
                ProtocovUSB_CyDmaSetSrcAddress(dmaCh, ProtocovUSB_DMA_DESCR1, (void *) nextAddr);
            }
            else
            {
                /* Change destination for descriptor 0. */
                nextAddr  = (uint32) ProtocovUSB_CyDmaGetDstAddress(dmaCh, ProtocovUSB_DMA_DESCR0);
                nextAddr += (2u * ProtocovUSB_DMA_BYTES_PER_BURST);
                ProtocovUSB_CyDmaSetDstAddress(dmaCh, ProtocovUSB_DMA_DESCR0, (void *) nextAddr);

                /* Change destination for descriptor 1. */
                nextAddr += ProtocovUSB_DMA_BYTES_PER_BURST;
                ProtocovUSB_CyDmaSetDstAddress(dmaCh, ProtocovUSB_DMA_DESCR1, (void *) nextAddr);
            }

            /* Enable DMA to execute transfer as it was disabled because there were no valid descriptor. */
            ProtocovUSB_CyDmaValidateDescriptor(dmaCh, ProtocovUSB_DMA_DESCR0);
            
            --ProtocovUSB_DmaEpBurstCnt[ep];
            if (0u != ProtocovUSB_DmaEpBurstCnt[ep])
            {
                ProtocovUSB_CyDmaValidateDescriptor(dmaCh, ProtocovUSB_DMA_DESCR1);
                --ProtocovUSB_DmaEpBurstCnt[ep];
            }
            
            ProtocovUSB_CyDmaChEnable (dmaCh);
            ProtocovUSB_CyDmaTriggerIn(ProtocovUSB_DmaReqOut[ep]);
        }
        else
        {
            /* No data to transfer. False DMA trig. Ignore.  */
        }

    }

    #if (ProtocovUSB_DMA1_ACTIVE)
        /******************************************************************************
        * Function Name: ProtocovUSB_EP1_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 1 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void ProtocovUSB_EP1_DMA_DONE_ISR(void)
        {

            ProtocovUSB_EPxDmaDone((uint8)ProtocovUSB_EP1_DMA_CH,
                                                  ProtocovUSB_EP1);
                
        }
    #endif /* (ProtocovUSB_DMA1_ACTIVE) */


    #if (ProtocovUSB_DMA2_ACTIVE)
        /******************************************************************************
        * Function Name: ProtocovUSB_EP2_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 2 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void ProtocovUSB_EP2_DMA_DONE_ISR(void)
        {

            ProtocovUSB_EPxDmaDone((uint8)ProtocovUSB_EP2_DMA_CH,
                                                  ProtocovUSB_EP2);
        }
    #endif /* (ProtocovUSB_DMA2_ACTIVE) */


    #if (ProtocovUSB_DMA3_ACTIVE)
        /******************************************************************************
        * Function Name: ProtocovUSB_EP3_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 3 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void ProtocovUSB_EP3_DMA_DONE_ISR(void)
        {

            ProtocovUSB_EPxDmaDone((uint8)ProtocovUSB_EP3_DMA_CH,
                                                  ProtocovUSB_EP3);
        }
    #endif /* (ProtocovUSB_DMA3_ACTIVE) */


    #if (ProtocovUSB_DMA4_ACTIVE)
        /******************************************************************************
        * Function Name: ProtocovUSB_EP4_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 4 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void ProtocovUSB_EP4_DMA_DONE_ISR(void)
        {

            ProtocovUSB_EPxDmaDone((uint8)ProtocovUSB_EP4_DMA_CH,
                                                  ProtocovUSB_EP4);
        }
    #endif /* (ProtocovUSB_DMA4_ACTIVE) */


    #if (ProtocovUSB_DMA5_ACTIVE)
        /******************************************************************************
        * Function Name: ProtocovUSB_EP5_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 5 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void ProtocovUSB_EP5_DMA_DONE_ISR(void)
        {

            ProtocovUSB_EPxDmaDone((uint8)ProtocovUSB_EP5_DMA_CH,
                                                  ProtocovUSB_EP5);
        }
    #endif /* (ProtocovUSB_DMA5_ACTIVE) */


    #if (ProtocovUSB_DMA6_ACTIVE)
        /******************************************************************************
        * Function Name: ProtocovUSB_EP6_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 6 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void ProtocovUSB_EP6_DMA_DONE_ISR(void)
        {

            ProtocovUSB_EPxDmaDone((uint8)ProtocovUSB_EP6_DMA_CH,
                                                  ProtocovUSB_EP6);
        }
    #endif /* (ProtocovUSB_DMA6_ACTIVE) */


    #if (ProtocovUSB_DMA7_ACTIVE)
        /******************************************************************************
        * Function Name: ProtocovUSB_EP7_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 7 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void ProtocovUSB_EP7_DMA_DONE_ISR(void)
        {

            ProtocovUSB_EPxDmaDone((uint8)ProtocovUSB_EP7_DMA_CH,
                                                  ProtocovUSB_EP7);
        }
    #endif /* (ProtocovUSB_DMA7_ACTIVE) */


    #if (ProtocovUSB_DMA8_ACTIVE)
        /******************************************************************************
        * Function Name: ProtocovUSB_EP8_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 8 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void ProtocovUSB_EP8_DMA_DONE_ISR(void)
        {

            ProtocovUSB_EPxDmaDone((uint8)ProtocovUSB_EP8_DMA_CH,
                                                  ProtocovUSB_EP8);
        }
    #endif /* (ProtocovUSB_DMA8_ACTIVE) */


#else
    #if (ProtocovUSB_EP_DMA_AUTO_OPT == 0u)
        /******************************************************************************
        * Function Name: ProtocovUSB_EP_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        CY_ISR(ProtocovUSB_EP_DMA_DONE_ISR)
        {
            uint8 int8Status;
            uint8 int17Status;
            uint8 ep_status;
            uint8 ep = ProtocovUSB_EP1;

        #ifdef ProtocovUSB_EP_DMA_DONE_ISR_ENTRY_CALLBACK
            ProtocovUSB_EP_DMA_DONE_ISR_EntryCallback();
        #endif /* (ProtocovUSB_EP_DMA_DONE_ISR_ENTRY_CALLBACK) */

            /* `#START EP_DMA_DONE_BEGIN_USER_CODE` Place your code here */

            /* `#END` */

            /* Read clear on read status register with EP source of interrupt. */
            int17Status = ProtocovUSB_EP17_DMA_Done_SR_Read() & ProtocovUSB_EP17_SR_MASK;
            int8Status  = ProtocovUSB_EP8_DMA_Done_SR_Read()  & ProtocovUSB_EP8_SR_MASK;

            while (int8Status != 0u)
            {
                while (int17Status != 0u)
                {
                    if ((int17Status & 1u) != 0u)  /* If EpX interrupt present. */
                    {
                        /* Read Endpoint Status Register. */
                        ep_status = ProtocovUSB_ARB_EP_BASE.arbEp[ep].epSr;

                        if ((0u == (ep_status & ProtocovUSB_ARB_EPX_SR_IN_BUF_FULL)) &&
                            (0u ==ProtocovUSB_inBufFull[ep]))
                        {
                            /* `#START EP_DMA_DONE_USER_CODE` Place your code here */

                            /* `#END` */

                        #ifdef ProtocovUSB_EP_DMA_DONE_ISR_CALLBACK
                            ProtocovUSB_EP_DMA_DONE_ISR_Callback();
                        #endif /* (ProtocovUSB_EP_DMA_DONE_ISR_CALLBACK) */

                            /* Transfer again 2 last bytes into pre-fetch endpoint area. */
                            ProtocovUSB_ARB_EP_BASE.arbEp[ep].rwWaMsb = 0u;
                            ProtocovUSB_ARB_EP_BASE.arbEp[ep].rwWa = (ProtocovUSB_DMA_BYTES_PER_BURST * ep) - ProtocovUSB_DMA_BYTES_REPEAT;
                            ProtocovUSB_LoadNextInEP(ep, 1u);

                            /* Set Data ready status to generate DMA request. */
                            ProtocovUSB_ARB_EP_BASE.arbEp[ep].epCfg |= ProtocovUSB_ARB_EPX_CFG_IN_DATA_RDY;
                        }
                    }

                    ep++;
                    int17Status >>= 1u;
                }

                int8Status >>= 1u;

                if (int8Status != 0u)
                {
                    /* Prepare pointer for EP8. */
                    ep = ProtocovUSB_EP8;
                    int17Status = int8Status & 0x01u;
                }
            }

            /* `#START EP_DMA_DONE_END_USER_CODE` Place your code here */

            /* `#END` */

    #ifdef ProtocovUSB_EP_DMA_DONE_ISR_EXIT_CALLBACK
        ProtocovUSB_EP_DMA_DONE_ISR_ExitCallback();
    #endif /* (ProtocovUSB_EP_DMA_DONE_ISR_EXIT_CALLBACK) */
        }
    #endif /* (ProtocovUSB_EP_DMA_AUTO_OPT == 0u) */
#endif /* (CY_PSOC4) */
#endif /* (ProtocovUSB_EP_MANAGEMENT_DMA_AUTO) */


#if (CY_PSOC4)
    /***************************************************************************
    * Function Name: ProtocovUSB_IntrHandler
    ************************************************************************//**
    *
    *   Interrupt handler for Hi/Mid/Low ISRs.
    *
    *  regCause - The cause register of interrupt. One of the three variants:
    *       ProtocovUSB_INTR_CAUSE_LO_REG - Low interrupts.
    *       ProtocovUSB_INTR_CAUSE_MED_REG - Med interrupts.
    *       ProtocovUSB_INTR_CAUSE_HI_REG - - High interrupts.
    *
    *
    ***************************************************************************/
    CY_INLINE static void ProtocovUSB_IntrHandler(uint32 intrCause)
    {
        /* Array of pointers to component interrupt handlers. */
        static const cyisraddress ProtocovUSB_isrCallbacks[] =
        {

        };

        uint32 cbIdx = 0u;

        /* Check arbiter interrupt source first. */
        if (0u != (intrCause & ProtocovUSB_INTR_CAUSE_ARB_INTR))
        {
            ProtocovUSB_isrCallbacks[ProtocovUSB_ARB_EP_INTR_NUM]();
        }

        /* Check all other interrupt sources (except arbiter and resume). */
        intrCause = (intrCause  & ProtocovUSB_INTR_CAUSE_CTRL_INTR_MASK) |
                    ((intrCause & ProtocovUSB_INTR_CAUSE_EP1_8_INTR_MASK) >>
                                  ProtocovUSB_INTR_CAUSE_EP_INTR_SHIFT);

        /* Call interrupt handlers for active interrupt sources. */
        while (0u != intrCause)
        {
            if (0u != (intrCause & 0x1u))
            {
                 ProtocovUSB_isrCallbacks[cbIdx]();
            }

            intrCause >>= 1u;
            ++cbIdx;
        }
    }


    /***************************************************************************
    * Function Name: ProtocovUSB_INTR_HI_ISR
    ************************************************************************//**
    *
    *   Interrupt Service Routine for the high group of the interrupt sources.
    *
    *
    ***************************************************************************/
    CY_ISR(ProtocovUSB_INTR_HI_ISR)
    {
        ProtocovUSB_IntrHandler(ProtocovUSB_INTR_CAUSE_HI_REG);
    }

    /***************************************************************************
    * Function Name: ProtocovUSB_INTR_MED_ISR
    ************************************************************************//**
    *
    *   Interrupt Service Routine for the medium group of the interrupt sources.
    *
    *
    ***************************************************************************/
    CY_ISR(ProtocovUSB_INTR_MED_ISR)
    {
       ProtocovUSB_IntrHandler(ProtocovUSB_INTR_CAUSE_MED_REG);
    }

    /***************************************************************************
    * Function Name: ProtocovUSB_INTR_LO_ISR
    ************************************************************************//**
    *
    *   Interrupt Service Routine for the low group of the interrupt sources.
    *
    *
    ***************************************************************************/
    CY_ISR(ProtocovUSB_INTR_LO_ISR)
    {
        ProtocovUSB_IntrHandler(ProtocovUSB_INTR_CAUSE_LO_REG);
    }
#endif /* (CY_PSOC4) */


/* [] END OF FILE */
