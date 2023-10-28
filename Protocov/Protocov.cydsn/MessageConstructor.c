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

//CAN_1_RX[rxMailbox].rxdata ;
#include "MessageConstructor.h"

static TaskHandle_t xHandle = NULL;

static void TaskMessageConstructor( void *pvParameters )
{
	
    (void)pvParameters;
    
	for( ;; )
	{
		//ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
        
       
        
	}
	
	/* Tasks must not attempt to return from their implementing
		function or otherwise exit.  In newer FreeRTOS port
		attempting to do so will result in an configASSERT() being
		called if it is defined.  If it is necessary for a task to
		exit then have the task call vTaskDelete( NULL ) to ensure
	its exit is clean. */
	vTaskDelete( NULL );
}



TaskHandle_t getMessageConstructorTaskHandle()
{
    
    return xHandle; 
}

void startTaskMessageConstructor()
{
    
    /* Create the task, storing the handle. */ 
	xTaskCreate(
		TaskMessageConstructor,      /* Function that implements the task. */ 
		"TaskMessageConstructor",    /* Text name for the task. */ 
		128,                        /* Stack size in words, not bytes. */ 
		( void * ) 1,               /* Parameter passed into the task. */ 
		tskIDLE_PRIORITY,           /* Priority at which the task is created. */ 
	&xHandle );                     /* Used to pass out the created task's handle. */ 
    
}



/* [] END OF FILE */
