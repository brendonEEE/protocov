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


#include "ExampleTasks.h"
#include <time.h>
#include <stdlib.h>

#define MIN(a,b) (((a)<(b))?(a):(b))

static volatile int pushButtonInterruptCounter = 0;

static void ledControlFunction();
static void taskLedBlink( void *pvParameters );
static void taskPushButtonInterrupt( void *pvParameters );
static void taskUserCodeGenerator( void *pvParameters );

CY_ISR(pushButtonInterrupt){
    
    
    if(pushButtonInterruptCounter % 2 == 0 )
    {
        
        pushButtonInterruptCounter = 1;
    }
    else
    {
        pushButtonInterruptCounter = 0;    
    }
    
}

static void taskLedBlink( void *pvParameters )
{
	
    (void)pvParameters;
    
	for( ;; )
	{
		ledControlFunction();
        vTaskDelay(1);
	}
	
	/* Tasks must not attempt to return from their implementing
		function or otherwise exit.  In newer FreeRTOS port
		attempting to do so will result in an configASSERT() being
		called if it is defined.  If it is necessary for a task to
		exit then have the task call vTaskDelete( NULL ) to ensure
	its exit is clean. */
	vTaskDelete( NULL );
}

static void taskPushButtonInterrupt( void *pvParameters )
{
	
    (void)pvParameters;
    
    for( ;; )
	{
        
        vTaskDelay(1);
		        
    }
		
	vTaskDelete( NULL );
}

static void ledControlFunction()
{

}

void startTaskLedBlink()
{
    
    TaskHandle_t xHandle = NULL;
 	/* Create the task, storing the handle. */ 
	xTaskCreate(
		taskLedBlink,               /* Function that implements the task. */ 
		"LedBlink",                 /* Text name for the task. */ 
		128,                        /* Stack size in words, not bytes. */ 
		( void * ) 1,               /* Parameter passed into the task. */ 
		tskIDLE_PRIORITY,           /* Priority at which the task is created. */ 
	&xHandle );                     /* Used to pass out the created task's handle. */
    
  
}



/* [] END OF FILE */
