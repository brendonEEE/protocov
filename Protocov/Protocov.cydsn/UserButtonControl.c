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

static TaskHandle_t xHandle;

static void TaskUserButtonControl( void *pvParameters )
{
	
    (void)pvParameters;
    
    PlayPauseButton_SetDriveMode ( PIN_DM_DIG_HIZ  );
    
    uint8_t playPauseButton = 0;
    uint8_t nextButton = 0;
    uint8_t previousButton = 0;
    
    uint8_t volumePlusButton = 0;
    uint8_t volumeMinusButton = 0;
    uint8_t callButton = 0;
    uint8_t talkButton = 0;
    uint8_t airRecirculationButton = 0;
    uint8_t upArrowButton = 0;
    uint8_t downArrowButton = 0;
    uint8_t inputChangeButton = 0;
  
	for( ;; )
	{
		
        vTaskDelay(1);
	}
	
}


void startTaskUserButtonControl()
{
    xHandle = NULL; 
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
