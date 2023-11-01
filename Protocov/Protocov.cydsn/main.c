/* ========================================
	*
	* Copyright YOUR COMPANY, THE YEAR
	* All Rights Reserved
	* UNPUBLISHED, LICENSED SOFTWARE.
	*
	* CONFIDENTIAL AND PROPRIETARY INFORMATION
	* WHICH IS THE PROPERTY OF your company.
	*
	* ========================================
*/
#include "project.h"
#include "FreeRTOS.h"
#include "task.h"

#include "BluetoothComms.h"
#include "UserButtonControl.h"
#include "VehicleBatteryVoltage.h"
#include "SystemMessenger.h"
#include "PowerMonitoringAndControl.h"

static void prvHardwareSetup( void );



static void startSystemTasks();

int main(void)


{
    CyDelay(500);
    
    BlueLedd_Write(1);
    
	CyGlobalIntEnable; /* Enable global interrupts. */
	
	prvHardwareSetup();
	
    /*Place all stasts to run in this function*/
    startSystemTasks();
	
	vTaskStartScheduler();
	
	
	for(;;)
	
	{
		/* Place your application code here. */
		
	}
}

static void prvHardwareSetup( void )
{
	
	/* Port layer functions that need to be copied into the vector table. */
	
	extern void xPortPendSVHandler( void );
	extern void xPortSysTickHandler( void );
	extern void vPortSVCHandler( void );
	extern cyisraddress CyRamVectors[];
	
	/* Install the OS Interrupt Handlers. */
	CyRamVectors[ 11 ] = ( cyisraddress ) vPortSVCHandler;
	CyRamVectors[ 14 ] = ( cyisraddress ) xPortPendSVHandler;
	CyRamVectors[ 15 ] = ( cyisraddress ) xPortSysTickHandler;
	
	/* Start-up the peripherals. */
	
	
}
/*---------------------------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	/* The stack space has been exceeded for a task, considering allocating more. */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
/*---------------------------------------------------------------------------*/


static void startSystemTasks()
{
    startTaskBluetoothComms();
    startTaskUserButtonControl();
    startTaskVehicleBatteryVoltage();
    startTaskSystemMessenger();
    startTaskPowerMonitoringAndControl();
}


/* [] END OF FILE */
