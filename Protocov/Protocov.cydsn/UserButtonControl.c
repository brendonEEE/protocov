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

#include "UserButtonControl.h"

static void TaskUserButtonControl( void *pvParameters )
{
	
    (void)pvParameters;
    
    PowerEnableBatt_Write( 1 );
    PowerEnableSelf_Write( 1 );
    PowerEnableACC_Write( 1 );
    
    PlayPauseButton_SetDriveMode ( PIN_DM_DIG_HIZ  );
    //PlayPauseButton_Write ( 0 );
    
	for( ;; )
	{
		
        vTaskDelay(1);
	}
	
}


void startTaskUserButtonControl()
{
    TaskHandle_t xHandle = NULL; 
 	/* Create the task, storing the handle. */ 
	xTaskCreate(
		TaskUserButtonControl,    /* Function that implements the task. */ 
		"UserButtonControl",  /* Text name for the task. */ 
		128,                        /* Stack size in words, not bytes. */ 
		( void * ) 1,               /* Parameter passed into the task. */ 
		tskIDLE_PRIORITY,           /* Priority at which the task is created. */ 
	&xHandle );                     /* Used to pass out the created task's handle. */ 
    
    
}



/* [] END OF FILE */
