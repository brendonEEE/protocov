/*******************************************************************************
* File Name: IntBluetoothUART.c  
* Version 1.71
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <cydevice_trm.h>
#include <CyLib.h>
#include <IntBluetoothUART.h>
#include "cyapicallbacks.h"

#if !defined(IntBluetoothUART__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START IntBluetoothUART_intc` */
    #include "BluetoothComms.h"
    
    BluetoothUartMsg_t message;
    uint8_t bluetoothDataAvailable = 0;
    uint64_t bluetoothMsgCount = 0;
    BluetoothUartMsg_t bluetoothISRDataBuff[64];
    volatile uint16_t readData;
    
    extern TickType_t bluetoothRecTimeout_ms;
    
    uint64_t bluetoothLastRecMsg_ms;
    
    TickType_t oldTickCount = 0;
    TickType_t newTickCount = 0;
    
/* `#END` */

#ifndef CYINT_IRQ_BASE
#define CYINT_IRQ_BASE      16
#endif /* CYINT_IRQ_BASE */
#ifndef CYINT_VECT_TABLE
#define CYINT_VECT_TABLE    ((cyisraddress **) CYREG_NVIC_VECT_OFFSET)
#endif /* CYINT_VECT_TABLE */

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: IntBluetoothUART_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it. This function disables the interrupt, 
*  sets the default interrupt vector, sets the priority from the value in the
*  Design Wide Resources Interrupt Editor, then enables the interrupt to the 
*  interrupt controller.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void IntBluetoothUART_Start(void)
{
    /* For all we know the interrupt is active. */
    IntBluetoothUART_Disable();

    /* Set the ISR to point to the IntBluetoothUART Interrupt. */
    IntBluetoothUART_SetVector(&IntBluetoothUART_Interrupt);

    /* Set the priority. */
    IntBluetoothUART_SetPriority((uint8)IntBluetoothUART_INTC_PRIOR_NUMBER);

    /* Enable it. */
    IntBluetoothUART_Enable();
}


/*******************************************************************************
* Function Name: IntBluetoothUART_StartEx
********************************************************************************
*
* Summary:
*  Sets up the interrupt and enables it. This function disables the interrupt,
*  sets the interrupt vector based on the address passed in, sets the priority 
*  from the value in the Design Wide Resources Interrupt Editor, then enables 
*  the interrupt to the interrupt controller.
*  
*  When defining ISR functions, the CY_ISR and CY_ISR_PROTO macros should be 
*  used to provide consistent definition across compilers:
*  
*  Function definition example:
*   CY_ISR(MyISR)
*   {
*   }
*   Function prototype example:
*   CY_ISR_PROTO(MyISR);
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void IntBluetoothUART_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    IntBluetoothUART_Disable();

    /* Set the ISR to point to the IntBluetoothUART Interrupt. */
    IntBluetoothUART_SetVector(address);

    /* Set the priority. */
    IntBluetoothUART_SetPriority((uint8)IntBluetoothUART_INTC_PRIOR_NUMBER);

    /* Enable it. */
    IntBluetoothUART_Enable();
}


/*******************************************************************************
* Function Name: IntBluetoothUART_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void IntBluetoothUART_Stop(void)
{
    /* Disable this interrupt. */
    IntBluetoothUART_Disable();

    /* Set the ISR to point to the passive one. */
    IntBluetoothUART_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: IntBluetoothUART_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for IntBluetoothUART.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(IntBluetoothUART_Interrupt)
{
    #ifdef IntBluetoothUART_INTERRUPT_INTERRUPT_CALLBACK
        IntBluetoothUART_Interrupt_InterruptCallback();
    #endif /* IntBluetoothUART_INTERRUPT_INTERRUPT_CALLBACK */ 

    /*  Place your Interrupt code here. */
    /* `#START IntBluetoothUART_Interrupt` */
    
        Counter_1_ReadStatusRegister();
        
        volatile uint8_t readStatus = BluetoothUART_RXSTATUS_REG ;
        
        if ( ( readStatus & BluetoothUART_RX_STS_FIFO_NOTEMPTY ) == 0 )
        {
            memset(bluetoothISRDataBuff, 0, sizeof(bluetoothISRDataBuff)/sizeof(BluetoothUartMsg_t) );
            bluetoothMsgCount = 0;
            oldTickCount = xTaskGetTickCountFromISR();
            return;
        }
        
        
        message.newTickCount = xTaskGetTickCountFromISR();
        message.oldTickCount = oldTickCount;
        
        
       
        bluetoothLastRecMsg_ms = (message.newTickCount - message.oldTickCount) / portTICK_PERIOD_MS;
        
        if( bluetoothLastRecMsg_ms >= bluetoothRecTimeout_ms  )
        {
            
            bluetoothMsgCount = 0; 
            memset(bluetoothISRDataBuff, 0, sizeof(bluetoothISRDataBuff)/sizeof(BluetoothUartMsg_t) );
        }
        
        message.msg = BluetoothUART_RXDATA_REG;
        bluetoothISRDataBuff[bluetoothMsgCount] = message;
        
        oldTickCount = xTaskGetTickCountFromISR();
        
        bluetoothMsgCount++;
            
        if( bluetoothMsgCount >= sizeof(bluetoothISRDataBuff) ) bluetoothMsgCount = 0;
        
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;  
  
        xTaskHandle temp = getBluetoothCommsTaskHandle();
  
        if(temp == NULL) return;
        
        bluetoothDataAvailable = 1;  
       
        vTaskNotifyGiveFromISR(temp, &xHigherPriorityTaskWoken);
       
    
    /* `#END` */
}


/*******************************************************************************
* Function Name: IntBluetoothUART_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling IntBluetoothUART_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use IntBluetoothUART_StartEx instead.
* 
*   When defining ISR functions, the CY_ISR and CY_ISR_PROTO macros should be 
*   used to provide consistent definition across compilers:
*
*   Function definition example:
*   CY_ISR(MyISR)
*   {
*   }
*
*   Function prototype example:
*     CY_ISR_PROTO(MyISR);
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void IntBluetoothUART_SetVector(cyisraddress address)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + (uint32)IntBluetoothUART__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: IntBluetoothUART_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress IntBluetoothUART_GetVector(void)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + (uint32)IntBluetoothUART__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: IntBluetoothUART_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. 
*
*   Note calling IntBluetoothUART_Start or IntBluetoothUART_StartEx will 
*   override any effect this API would have had. This API should only be called
*   after IntBluetoothUART_Start or IntBluetoothUART_StartEx has been called. 
*   To set the initial priority for the component, use the Design-Wide Resources
*   Interrupt Editor.
*
*   Note This API has no effect on Non-maskable interrupt NMI).
*
* Parameters:
*   priority: Priority of the interrupt, 0 being the highest priority
*             PSoC 3 and PSoC 5LP: Priority is from 0 to 7.
*             PSoC 4: Priority is from 0 to 3.
*
* Return:
*   None
*
*******************************************************************************/
void IntBluetoothUART_SetPriority(uint8 priority)
{
    *IntBluetoothUART_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: IntBluetoothUART_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt, 0 being the highest priority
*    PSoC 3 and PSoC 5LP: Priority is from 0 to 7.
*    PSoC 4: Priority is from 0 to 3.
*
*******************************************************************************/
uint8 IntBluetoothUART_GetPriority(void)
{
    uint8 priority;


    priority = *IntBluetoothUART_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: IntBluetoothUART_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt to the interrupt controller. Do not call this function
*   unless ISR_Start() has been called or the functionality of the ISR_Start() 
*   function, which sets the vector and the priority, has been called.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void IntBluetoothUART_Enable(void)
{
    /* Enable the general interrupt. */
    *IntBluetoothUART_INTC_SET_EN = IntBluetoothUART__INTC_MASK;
}


/*******************************************************************************
* Function Name: IntBluetoothUART_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 IntBluetoothUART_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*IntBluetoothUART_INTC_SET_EN & (uint32)IntBluetoothUART__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: IntBluetoothUART_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt in the interrupt controller.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void IntBluetoothUART_Disable(void)
{
    /* Disable the general interrupt. */
    *IntBluetoothUART_INTC_CLR_EN = IntBluetoothUART__INTC_MASK;
}


/*******************************************************************************
* Function Name: IntBluetoothUART_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
* Side Effects:
*   If interrupts are enabled and the interrupt is set up properly, the ISR is
*   entered (depending on the priority of this interrupt and other pending 
*   interrupts).
*
*******************************************************************************/
void IntBluetoothUART_SetPending(void)
{
    *IntBluetoothUART_INTC_SET_PD = IntBluetoothUART__INTC_MASK;
}


/*******************************************************************************
* Function Name: IntBluetoothUART_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt in the interrupt controller.
*
*   Note Some interrupt sources are clear-on-read and require the block 
*   interrupt/status register to be read/cleared with the appropriate block API 
*   (GPIO, UART, and so on). Otherwise the ISR will continue to remain in 
*   pending state even though the interrupt itself is cleared using this API.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void IntBluetoothUART_ClearPending(void)
{
    *IntBluetoothUART_INTC_CLR_PD = IntBluetoothUART__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
