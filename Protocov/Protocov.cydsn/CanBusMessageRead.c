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


 /*SG_ Telephone : 0|1@0+ (1,0) [0|1] "" RAD
 SG_ IncVolume : 2|1@0+ (1,0) [0|1] "" RAD
 SG_ DecVolume : 3|1@0+ (1,0) [0|1] "" RAD
 SG_ PrevArrow : 4|1@0+ (1,0) [0|1] "" RAD
 SG_ NextArrow : 5|1@0+ (1,0) [0|1] "" RAD
 SG_ VoiceCmd : 8|1@0+ (1,0) [0|1] "" TEL
 SG_ AirRecirc : 12|1@0+ (1,0) [0|1] ""  IHKA
 SG_ RT_button : 14|1@0+ (1,0) [0|1] "" RAD

CM_ BO_ 470 "0x1D6 MFL (SZL): Steering Wheel Controls";
CM_  SG_ 470 Telephone "Telephone Button (answer/end call)";
CM_  SG_ 470 IncVolume "Increase Volume";
CM_  SG_ 470 DecVolume "Decrease Volume";
CM_  SG_ 470 NextArrow "Previous Track";
CM_  SG_ 470 PrevArrow "Next Track";
CM_  SG_ 470 VoiceCmd "Voice Command Button";
CM_  SG_ 470 AirRecirc "Air Recirculation Control (IHKA)";
CM_  SG_ 470 RT_button "Radio/Telephone Button";
*/


#include "CanbusMessageRead.h"
#include "VehicleCAN.h"

extern CANBusRXMessage_t canbusRecMgsBuffer[20];

static void TaskCanbusMessageRead( void *pvParameters )
{
	
    (void)pvParameters;
    
    VehicleCAN_Start();
    
    uint8_t recMsgBufferPos = 0;
    
	for( ;; )
	{
		
        if( (uint16_t)canbusRecMgsBuffer[recMsgBufferPos].rxid.byte == 0 )
        {
 
            recMsgBufferPos++; 
            continue;  
        }
        
        
        
        if( recMsgBufferPos < ( sizeof(canbusRecMgsBuffer)/sizeof(CANBusRXMessage_t)) -1 )
        {
           recMsgBufferPos++; 
        }
        else
        {
           recMsgBufferPos = 0;
        }
        
        vTaskDelay(10);
	}

}


void startTasCanbusMessageRead()
{
    TaskHandle_t xHandle = NULL; 
 	/* Create the task, storing the handle. */ 
	xTaskCreate(
		TaskCanbusMessageRead,    /* Function that implements the task. */ 
		"rrupt",  /* Text name for the task. */ 
		128,                        /* Stack size in words, not bytes. */ 
		( void * ) 1,               /* Parameter passed into the task. */ 
		tskIDLE_PRIORITY,           /* Priority at which the task is created. */ 
	&xHandle );                     /* Used to pass out the created task's handle. */ 
    
    
}



/* [] END OF FILE */
